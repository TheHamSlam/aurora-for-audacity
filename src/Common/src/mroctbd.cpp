#include <stdio.h>

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <assert.h>


#include <audtypes.h>
#include <commdefs.h>

#include "afaudio.h"
#include "sigwin.h"
#include "firwin.h"
#include "octfir.h"
#include "octfilt.h"
#include "mroctbd.h"

float g_aflOctaveBandFc[] = {   31.5,   63.0,  100.0,  50.0,   500.0,
                              1000.0, 2000.0, 4000.0, 8000.0, 16000.0 };

float g_aflThirdOctaveBandFc[] = {   25.0,    31.5,    40.0,    50.0,    63.0,
                                     80.0,   100.0,   125.0,   160.0,   200.0,
                                    250.0,   315.0,   400.0,   500.0,   630.0,
                                    800.0,  1000.0,  1250.0,  1600.0,  2000.0,
                                   2500.0,  3150.0,  4000.0,  5000.0,  6300.0,
                                   8000.0, 10000.0, 12500.0, 16000.0, 20000.0 };

// ----------------------------------------------------------------------------
// scipy: signal.firwin(31, 1.0/2.0, window='hamming')
AFSample g_adbLpFilterTaps_48[] = {  -1.700396903673608018e-03, 1.757971997228029832e-18,
                                   2.937331570890679838e-03, -3.276763392097393135e-18,
                                   -6.730091366404413432e-03, 6.051733351876545153e-18,
                                   1.409388790399193625e-02, -9.603064360709015505e-18,
                                   -2.678503582005385686e-02, 1.331669902433829708e-17,
                                   4.909896059357541503e-02, -1.655051617211110519e-17,
                                   -9.693833277630080347e-02, 1.874535944087102577e-17,
                                   3.156195633244823218e-01, 5.008082269469846803e-01,
                                   3.156195633244823218e-01, 1.874535944087102268e-17,
                                   -9.693833277630083123e-02, -1.655051617211110827e-17,
                                   4.909896059357543585e-02, 1.331669902433830170e-17,
                                   -2.678503582005387768e-02, -9.603064360709020128e-18,
                                   1.409388790399193972e-02, 6.051733351876545153e-18,
                                   -6.730091366404411697e-03, -3.276763392097394291e-18,
                                   2.937331570890678537e-03, 1.757971997228029832e-18,
                                   -1.700396903673608018e-03 };

AFSample g_adbLpFilterB_48[] = { 0.0053233 ,
                               0.04258637,  0.14905228,  
                               0.29810456,  0.3726307 ,  
                               0.29810456,  0.14905228,  
                               0.04258637,  0.0053233  };
                            
AFSample g_adbLpFilterA_48[] = {  1.0,
                               -0.94338214,  2.00431824, 
                               -1.60880355,  1.45032361, 
                               -0.83004411,  0.39328284, 
                               -0.12313816,  0.0217768  };

// ----------------------------------------------------------------------------

void Dump(AFSample* data, const int length, const int id, const char* tag)
{
    FILE* f;
    int k;
    
    char str[32];
    if(data != 0)
    {
        sprintf(str, "/tmp/%s_%d", tag, id);
        std::cout << "Dumping Lp " << id << " to " << str << std::endl;
        if((f = fopen(str, "w")) != 0)
        {
            k = 0;
            
            while(k < length)
            {
                fprintf(f, "%.18e\n", data[k++]);
            }
            fclose(f);
        }
    }
}

void SCOctaveBandAnalysisBase::ChooseLPFilterSet()
{

	if(m_bIsPreFilteringFIR)
	{
		// Parameter used in the SciPy 'Decimate' function
		m_pLpFilter = new SCFilter(31, 0.5, SCSignalWindows::WT_HAMMING);
	}
	else
	{
		// IIR stuffs ... to be removed ....
		AFSample* a;
		AFSample* b;
		int order;

		if(m_dbRate == 48000.0)
		{
			a = g_adbLpFilterA_48;
			b = g_adbLpFilterB_48;
			order = sizeof(g_adbLpFilterB_48);
		}
//                if(m_dbRate == 44100.0)
//                    return g_adbLpFilterB_44k1;

		order /= sizeof(AFSample);
		m_pLpFilter = new SCFilter((const int)order, b, a, m_dbRate);
	}

}

void SCOctaveBandAnalysisBase::Decimate(const unsigned int N,
                                        AFSample* dest,
                                        AFSample* src,
                                        AFSampleCount  length)
{
    AFSampleCount k, i;
    for(k = 0, i = 0; k < length; k += N, i++)
    {
        dest[i] = src[k];
    }   
}

SCOctaveBandAnalysisBase::SCOctaveBandAnalysisBase(const double rate,
                                                   const bool   firPreFiltering,
                                                   const unsigned int bandsCount)
: m_dbRate(rate),
  m_bIsPreFilteringFIR(firPreFiltering),
  m_unCurrentBand(10000),
  m_unBandsCount(bandsCount),
  m_pTrack(0),
  m_psmpXtLP(0),
  m_psmpXtRes(0),
  m_nDecimationFactor(0),
  m_dbG(12.0),
  m_pLpFilter(0),
  m_vFilterBank(0)
{ }

SCOctaveBandAnalysisBase::~SCOctaveBandAnalysisBase()
{
    if(m_psmpXtLP)  delete [] m_psmpXtLP;
    if(m_psmpXtRes) delete [] m_psmpXtRes;
    if(m_pLpFilter) delete m_pLpFilter;
}

// ----------------------------------------------------------------------------
bool SCOctaveBandAnalysis::Init(AFAudioTrack* track)
{
    // 0. Init filters
#ifdef __AUDEBUG__
    std::cout << "Initializing filters..." << std::endl;
#endif
    if(m_pLpFilter) delete m_pLpFilter;
    
    ChooseLPFilterSet();
    
    m_vFilterBank[FBP_16k]->Create(m_dbRate, 12.0);
    m_vFilterBank[FBP_8k]->Create(m_dbRate,   9.0);

    m_pTrack = track;
    m_unCurrentBand = BD_16k + 1;

    if(m_psmpXtLP)  delete [] m_psmpXtLP;
    if(m_psmpXtRes) delete [] m_psmpXtRes;
    AFSampleCount length = m_pTrack->GetLength();

    m_psmpXtLP  = new AFSample [length];
    m_psmpXtRes = new AFSample [length];

    m_nDecimationFactor = 2;
    m_dbG = 12.0;

    m_pLpFilter->Dump(0, "ap_lp");
    m_vFilterBank[FBP_16k]->Dump(0, "ap_bp16k");
    m_vFilterBank[FBP_8k]->Dump(0, "ap_bp8k");

    return true;
}

int SCOctaveBandAnalysis::Filter(const int id)
{
	if(m_unCurrentBand == 0 || m_unCurrentBand == 10000)
	{
		return -1;
	}

    AFSample* xt = 0;
    AFSample* yt = 0;
    AFSampleCount length    = 0;
    AFSampleCount lengthRes = 0;

    AFSampleCount minLength = (AFSampleCount)( (m_dbRate/m_nDecimationFactor)/
    		                                   (2000.0*pow(10.0, (m_dbG-3.0)/10.0)) );
    m_unCurrentBand--;
    
    switch(m_unCurrentBand)
    {
        case BD_16k:
            xt = m_pTrack->GetData();
            yt = m_pTrack->GetFilteredData();
            length = m_pTrack->GetLength();
            m_vFilterBank[FBP_16k]->Apply(yt, xt, length);

            m_pTrack->SetFilteredDataLength(length);
            m_dbG -= 3.0;
            break;

        case BD_8k:
            xt = m_pTrack->GetData();
            yt = m_pTrack->GetFilteredData();
            length = m_pTrack->GetLength();
            m_vFilterBank[FBP_8k]->Apply(yt, xt, length);

            m_pTrack->SetFilteredDataLength(length);
            m_dbG -= 3.0;
            break;
    
        case BD_4k:
        	memcpy(m_psmpXtRes,
        		   m_pTrack->GetData(), m_pTrack->GetLength()*sizeof(AFSample));

        default:
        	yt = m_pTrack->GetFilteredData();
        	length = m_pTrack->GetFilteredDataLength();

            lengthRes = length;
    
            if( (m_dbG < -15.0) || (lengthRes / 2 < minLength) )
            {
         	   return -2;
            }
			// 2. Decimate
			m_pLpFilter->Apply(m_psmpXtLP, m_psmpXtRes, lengthRes);
//			if(id > -1)
//			    Dump(m_psmpXtLP, (unsigned int)lengthRes, id, "ap_postlp");

			Decimate(2, m_psmpXtRes, m_psmpXtLP, lengthRes);
//			if(id > -1)
//			    Dump(m_psmpXtRes, (unsigned int)lengthRes/2, id, "ap_postdec");

			lengthRes /= 2;
			m_dbRate  /= 2;
			memset(m_psmpXtRes + lengthRes, 0, length - lengthRes);

			// 3. Analyze next band
			m_pTrack->SetFilteredDataLength(lengthRes);
			m_pTrack->SetFilteredDataRate(m_dbRate);
			m_vFilterBank[FBP_8k]->Apply(yt, m_psmpXtRes, lengthRes);

			// 4. prepare for next
			m_nDecimationFactor *= 2;
			m_dbG -= 3.0;
            break;
    }
    return int(m_unCurrentBand);
}

int SCOctaveBandAnalysis::FilterForBand(const int targetBand)
{
	if((targetBand < BD_31_5) || (targetBand > BD_16k))
	{
		return -1;
	}

	if(!m_pTrack)
	{
		return -1;
	}

    AFSample* xt = m_pTrack->GetData();
    AFSample* yt = m_pTrack->GetFilteredData();
    AFSampleCount length    = m_pTrack->GetLength();
    AFSampleCount lengthRes = length;

    double rate = m_pTrack->GetRate();

#ifdef __AUDEBUG__
    std::cout << "Requested band: " << targetBand;
#endif

    switch(targetBand)
    {
        case BD_16k:
            m_vFilterBank[FBP_16k]->Apply(yt, xt, length);
            m_pTrack->SetFilteredDataLength(length);
			m_pTrack->SetFilteredDataRate(rate);

            return BD_16k;

        case BD_8k:
            m_vFilterBank[FBP_8k]->Apply(yt, xt, length);
            m_pTrack->SetFilteredDataLength(length);
            m_pTrack->SetFilteredDataRate(rate);
            return BD_8k;

        default:
        {
        	AFSampleCount minLength = 0;

            double decFactor = pow(2.0, double(BD_8k - targetBand));
            double         g = 3 * double(targetBand) - 15.0;

            rate /= decFactor;
        	minLength = (AFSampleCount)( rate/ (1000.0*pow(10.0, g/10.0)) );

			if( AFSampleCount(lengthRes / decFactor) < minLength )
			{
#ifdef __AUDEBUG__
				std::cout << "IR too short for band" << targetBand
				          << " should be at least"   <<  int(decFactor*minLength)
						  << "\n";
#endif
				return -2;
			}

        	SCFilter LpFilter(31, 1.0/decFactor, SCSignalWindows::WT_HAMMING);

        	memcpy(m_psmpXtRes,
        	       m_pTrack->GetData(), length*sizeof(AFSample));

			LpFilter.Apply(m_psmpXtLP, m_psmpXtRes, lengthRes);
			Decimate(int(decFactor), m_psmpXtRes, m_psmpXtLP, lengthRes);

			lengthRes = AFSampleCount(double(length) / decFactor); //n
			memset(m_psmpXtRes + lengthRes, 0, length - lengthRes);

#ifdef __AUDEBUG__
        	std::cout << "filtering...";
#endif
			m_pTrack->SetFilteredDataLength(lengthRes);
			m_pTrack->SetFilteredDataRate(rate);
			m_vFilterBank[FBP_8k]->Apply(yt, m_psmpXtRes, lengthRes);
#ifdef __AUDEBUG__
            std::cout << "done\n";
#endif
            break;
        }
    }

    return targetBand;
}

SCOctaveBandAnalysis::SCOctaveBandAnalysis(const double rate,
                                           const bool   firPreFiltering)
: SCOctaveBandAnalysisBase(rate, firPreFiltering, 10)
{
	for(int i = 0; i < 2; i++)
	    m_vFilterBank.push_back(dynamic_cast<SCOctaveBandFilterBase*>(new SCOctaveBandFilter));
}

SCOctaveBandAnalysis::~SCOctaveBandAnalysis()
{
	for(int i = 0; i < 2; i++)
		delete m_vFilterBank[i];
}
// ----------------------------------------------------------------------------
bool SCThirdOctaveBandAnalysis::Init(AFAudioTrack* track)
{
    // 0. Init filters
    if(m_pLpFilter) delete m_pLpFilter;
    ChooseLPFilterSet();

    m_vFilterBank[FBP_20k]->Create(m_dbRate,  13.0);
    m_vFilterBank[FBP_16k]->Create(m_dbRate,  12.0);
    m_vFilterBank[FBP_12k5]->Create(m_dbRate, 11.0);
    m_vFilterBank[FBP_10k]->Create(m_dbRate,  10.0);

    m_pTrack = track;
    m_unCurrentBand = BD_20k + 1;

    if(m_psmpXtLP)  delete [] m_psmpXtLP;
    if(m_psmpXtRes) delete [] m_psmpXtRes;
    AFSampleCount length = m_pTrack->GetLength();

    m_psmpXtLP  = new AFSample [length];
    m_psmpXtRes = new AFSample [length];

    m_nDecimationFactor = 2;
    m_dbG = 12.0;

    return true;
            
}

int SCThirdOctaveBandAnalysis::Filter(const int id)
{
	if(m_unCurrentBand == 0 || m_unCurrentBand == 10000)
	{
		return -1;
	}

    AFSample* xt = 0;
    AFSample* yt = 0;
    AFSampleCount length    = 0;
    AFSampleCount lengthRes = 0;

    AFSampleCount minLength = (AFSampleCount)( (m_dbRate/m_nDecimationFactor)/
    		                                   (2000.0*pow(10.0, (m_dbG-3.0)/10.0)) );
    m_unCurrentBand--;

    switch(m_unCurrentBand)
    {
        case BD_20k:
            xt = m_pTrack->GetData();
			yt = m_pTrack->GetFilteredData();
			length = m_pTrack->GetLength();
			m_vFilterBank[FBP_20k]->Apply(yt, xt, length);
			//m_vFilterBank[FBP_20k]->Dump(48, "ap_bp_20k");
			m_dbG -= 1.0;
			break;

        case BD_16k:
            xt = m_pTrack->GetData();
			yt = m_pTrack->GetFilteredData();
			length = m_pTrack->GetLength();
			m_vFilterBank[FBP_16k]->Apply(yt, xt, length);
			//m_vFilterBank[FBP_16k]->Dump(48, "ap_bp_16k");
			m_dbG -= 1.0;
			break;

       case BD_12k5:
			xt = m_pTrack->GetData();
			yt = m_pTrack->GetFilteredData();
			length = m_pTrack->GetLength();
			m_vFilterBank[FBP_12k5]->Apply(yt, xt, length);
			//m_vFilterBank[FBP_12k5]->Dump(48, "ap_bp_12k5");
			m_dbG -= 1.0;
			break;

       case BD_10k:
			xt = m_pTrack->GetData();
			yt = m_pTrack->GetFilteredData();
			length = m_pTrack->GetLength();
			m_vFilterBank[FBP_10k]->Apply(yt, xt, length);
			//m_vFilterBank[FBP_10k]->Dump(48, "ap_bp_10k");
			m_dbG -= 1.0;

			break;

       case BD_8k:
       	memcpy(m_psmpXtRes,
       		   m_pTrack->GetData(), m_pTrack->GetLength()*sizeof(AFSample));

       case BD_4k:
       case BD_2k:
       case BD_1k:
       case BD_500:
       case BD_250:
       case BD_125:
       case BD_63:
       case BD_31_5:

       	   yt = m_pTrack->GetFilteredData();
       	   length = m_pTrack->GetFilteredDataLength();

           lengthRes = length;

           if( (m_dbG < -15.0) || (lengthRes / 2 < minLength) )
           {
        	   printf("----> %.3f %d %d\n", m_dbG,  (int)lengthRes/2,  (int)minLength);
        	   return -2;
           }

		   // 2. Decimate
		   m_pLpFilter->Apply(m_psmpXtLP, m_psmpXtRes, lengthRes);
		   //Dump(xtLP, (unsigned int)lengthRes, band, "cp_postlp");

		   Decimate(2, m_psmpXtRes, m_psmpXtLP, lengthRes);
		   //Dump(xtRes, (unsigned int)lengthRes/2, band, "cp_postdec");

		   lengthRes /= 2;
		   memset(m_psmpXtRes + lengthRes, 0, length - lengthRes);

		   // 3. Analyze next band
		   m_pTrack->SetFilteredDataLength(lengthRes);
		   m_pTrack->SetFilteredDataRate(m_dbRate / m_nDecimationFactor);
		   m_vFilterBank[FBP_16k]->Apply(yt, m_psmpXtRes, lengthRes);

		   // 4. prepare for next
		   printf("---------------------------------------------------------->\n");
		   m_dbG -= 1.0;

    	   break;

       case BD_6k3:
       case BD_3k15:
       case BD_1k6:
       case BD_800:
       case BD_400:
       case BD_200:
       case BD_100:
       case BD_50:
       case BD_25:

       	   yt = m_pTrack->GetFilteredData();
       	   length = m_pTrack->GetFilteredDataLength();

           lengthRes = length;

           if( (m_dbG < -15.0) || (lengthRes / 2 < minLength) )
           {
#ifdef __AUDEBUG__
        	   printf("----> %.3f %d %d\n", m_dbG, (int)lengthRes/2,  (int)minLength);
#endif
        	   return -2;
           }
		   m_pTrack->SetFilteredDataLength(lengthRes);
		   m_pTrack->SetFilteredDataRate(m_dbRate / m_nDecimationFactor);
		   m_vFilterBank[FBP_12k5]->Apply(yt, m_psmpXtRes, lengthRes);
           m_dbG -= 1.0;
    	   break;

       case BD_5k:
       case BD_2k5:
       case BD_1k25:
       case BD_630:
       case BD_315:
       case BD_160:
       case BD_80:
       case BD_40:

       	   yt = m_pTrack->GetFilteredData();
       	   length = m_pTrack->GetFilteredDataLength();

           lengthRes = length;

           if( (m_dbG < -15.0) || (lengthRes / 2 < minLength) )
           {
#ifdef __AUDEBUG__
        	   printf("----> %.3f %d %d\n", m_dbG,  (int)lengthRes/2,  (int)minLength);
#endif
        	   return -2;
           }
		   m_pTrack->SetFilteredDataLength(lengthRes);
		   m_pTrack->SetFilteredDataRate(m_dbRate / m_nDecimationFactor);
		   m_vFilterBank[FBP_10k]->Apply(yt, m_psmpXtRes, lengthRes);

		   m_nDecimationFactor *= 2;
		   m_dbG -= 1.0;
    	   break;
    }
        
    return int(m_unCurrentBand);
}
 
int SCThirdOctaveBandAnalysis::FilterForBand(const int targetBand)
{
	if((targetBand < BD_25) || (targetBand > BD_20k))
	{
		return -1;
	}

	if(!m_pTrack)
	{
		return -1;
	}

    AFSample* xt = m_pTrack->GetData();
    AFSample* yt = m_pTrack->GetFilteredData();
    AFSampleCount length    = m_pTrack->GetLength();
    AFSampleCount lengthRes = length;

    double rate = m_pTrack->GetRate();

    switch(targetBand)
    {
        case BD_16k:
            m_vFilterBank[FBP_16k]->Apply(yt, xt, length);
            m_pTrack->SetFilteredDataLength(length);
            m_pTrack->SetFilteredDataRate(rate);
            return BD_16k;

        case BD_12k5:
            m_vFilterBank[FBP_12k5]->Apply(yt, xt, length);
            m_pTrack->SetFilteredDataLength(length);
            m_pTrack->SetFilteredDataRate(rate);
            return BD_8k;

        case BD_10k:
            m_vFilterBank[FBP_10k]->Apply(yt, xt, length);
            m_pTrack->SetFilteredDataLength(length);
            m_pTrack->SetFilteredDataRate(rate);
            return BD_10k;

        default:
        {
            AFSampleCount minLength = 0;

            int targetBandGroup = 0;
            int filterIdx       = 0;

        	if((targetBand - 2) < 0)
        	{
        		targetBandGroup = 0;
        		filterIdx = targetBand + 1;
        	}
        	else
        	{
        		targetBandGroup = (targetBand-2)/3 + 1;
        	    filterIdx = (3*targetBandGroup - targetBand) + 2;
        	}

            double decFactor = pow(2.0, double(9 - targetBandGroup));
            double         g = double(targetBand) - 16.0;

            rate /= decFactor;
         	minLength = (AFSampleCount)( rate/ (1000.0*pow(10.0, g/10.0)) );

 			if( AFSampleCount(lengthRes / decFactor) < minLength )
 			{
#ifdef __AUDEBUG__
 				std::cout << "IR too short for band" << targetBand
 				          << " should be at least"   <<  int(decFactor*minLength)
 						  << "\n";
#endif
 				return -2;
 			}

         	SCFilter LpFilter(31, 1.0/decFactor, SCSignalWindows::WT_HAMMING);

         	memcpy(m_psmpXtRes,
         	       m_pTrack->GetData(), length*sizeof(AFSample));

 			LpFilter.Apply(m_psmpXtLP, m_psmpXtRes, lengthRes);
 			Decimate(int(decFactor), m_psmpXtRes, m_psmpXtLP, lengthRes);

 			lengthRes = AFSampleCount(double(length) / decFactor); //n
 			memset(m_psmpXtRes + lengthRes, 0, length - lengthRes);

#ifdef __AUDEBUG__
         	std::cout << "filtering (" << filterIdx << ")...";
#endif
 			m_pTrack->SetFilteredDataLength(lengthRes);
 			m_pTrack->SetFilteredDataRate(rate);
 			m_vFilterBank[filterIdx]->Apply(yt, m_psmpXtRes, lengthRes);
#ifdef __AUDEBUG__
            std::cout << "done\n";
#endif
            break;
        }
    }

    return targetBand;
}

SCThirdOctaveBandAnalysis::SCThirdOctaveBandAnalysis(const double rate, 
                                                     const bool   firPreFiltering)
  : SCOctaveBandAnalysisBase(rate, firPreFiltering, 30)
{
	for(int i = 0; i < 4; i++)
	    m_vFilterBank.push_back(dynamic_cast<SCOctaveBandFilterBase*>(new SCThirdOctaveBandFilter));
}

SCThirdOctaveBandAnalysis::~SCThirdOctaveBandAnalysis()
{
	for(int i = 0; i < 4; i++)
		delete m_vFilterBank[i];
}

// ----------------------------------------------------------------------------
void SCOctaveBandData::Init(const unsigned int length, const bool zeroFill)
{
    if(length > 0)
        m_unLength = length;
    
    if(m_adbData)  
        delete [] m_adbData;
        
    assert(m_unLength > 0);
    m_adbData = new double [m_unLength];
    
    if(zeroFill)
        memset(m_adbData, 0, length * sizeof(double));    
}

void SCOctaveBandData::SetData(double* data, const unsigned int length)
{    
    Init(length);
    memcpy(m_adbData, data, length * sizeof(double));
}
    
SCOctaveBandData::SCOctaveBandData(const double rate)
 : m_dbRate(rate),
   m_adbData(0),
   m_unLength(0),
   m_flFm(0.0)
{}

SCOctaveBandData::SCOctaveBandData(double* data,
                                   const unsigned int length,
                                   const float fm,
                                   const double rate)
 : m_dbRate(rate),
   m_adbData(0),
   m_unLength(length),
   m_flFm(fm)
{
    SetData(data);
}

SCOctaveBandData::~SCOctaveBandData()
{
    if(m_adbData) 
        delete [] m_adbData;
}
