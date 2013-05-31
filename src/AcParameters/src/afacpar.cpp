/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters

  afacpar.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AFAcousticalParameters
\brief A powerful analizing tool for room acoustics

  This class is an acoustical parameter evaluation tool:
  given a room's impulse response, it evaluates the most important
  parameter, like reverberation time, clarity index, and so on.
  It uses the Schroeder's integral technique, and is a port for
  Audacity of the original Angelo Farina's plug-in for Adobe
  Audition.

*//*******************************************************************/
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

#include <commdefs.h>
#include <audtypes.h>
#include <gpfuncts.h>
#include <octfilt.h>
#include <mroctbd.h>

#include "afacpar.h"

#define DELTA_T(ch, a) AFSampleCount(m_paAudioTracks->Item(ch).GetFilteredDataRate() * (a + dbDelay))

#ifdef MULTIRATE_FILTERING
#    define FAT_IN_SAMPLES(ch) m_vDecay[ch].GetFirstArrivalTimeInSamples()
#else
#    define FAT_IN_SAMPLES(ch) AFSampleCount(m_paAudioTracks->Item(ch).GetFirstArrivalTime() *\
	                                         m_paAudioTracks->Item(ch).GetFilteredDataRate())
#endif

#define LENGTH_FROM_FAT_IN_SAMPLES(ch) AFSampleCount(m_paAudioTracks->Item(ch).GetFilteredDataLength() -\
                                                     FAT_IN_SAMPLES(ch))

void DumpData(AFSample* data, const int length, const int id, const char* tag)
{
    FILE* f;
    int k;

    char str[32];
    if(data != 0)
    {
        sprintf(str, "/tmp/%s_%d", tag, id);
        std::cout << "AcParameters dump data " << id << " to " << str << std::endl;
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

//----------------------------------------------------------------------------
// TSchroederDecay implementation
//----------------------------------------------------------------------------

void TSchroederDecay::SetData(AFSample* psmpSrc, const AFSampleCount smpcSrcLength)
{
	memcpy(m_asmpData, psmpSrc, m_smpcLength*sizeof(AFSample));
}

void TSchroederDecay::FindFirstArrivalTime()
{
	AFSample last = m_asmpData[0]; // should be the max too...
	AFSample threshold = last * 1.0e-4;
	AFSampleCount decayStart = 1;

	while(decayStart < m_smpcLength)
	{
	   if((last -m_asmpData[decayStart]) > threshold)
		   break;

	   last = m_asmpData[decayStart];
	   decayStart++;
	}

	printf("Decay start: %d\n", int(decayStart));

	m_smpcFAT = decayStart;
}

void TSchroederDecay::Process(APAudioTrack& track)
{
	// Calculate Schroeder Integral.
	// The resulting decay will be stored in m_apsmpDecay vector.
	// It returns the short factor t*p^2, useful for TS determination.
	// TO DO: negative returns on error.

	AFSampleCount i = 0;
	AFSampleCount smpcI2 = AFSampleCount(track.GetFilteredDataLength() -
										track.GetFirstArrivalTime() *
										track.GetFilteredDataRate());
	AFSample*   psmpData = track.GetFilteredData();
	AFSampleCount length = track.GetFilteredDataLength();

	m_dbRate = track.GetFilteredDataRate();

	double dbSqTot = 0.0,
		  dbNoiseCorr = track.GetNoiseCorrFactor(),
		  dbSample;

	if(length != m_smpcLength)
	{  Init(length); }

	m_dbTP2 = 0.0;

	for(i = length-1; i > 0; i--)
	{
	  // Amplitude square. If noise correction is deactivated,
	  //  the correction factor is set to 0.0.
	  dbSample = psmpData[i]*psmpData[i] - dbNoiseCorr;

	  // if FAT is not reached, update smpcI2 and dbTP2
	  if(smpcI2)
		  m_dbTP2 += dbSample * (smpcI2--);

	  // update squares' total
	  dbSqTot += dbSample;

	  // store actual integral value.
	  m_asmpData[i] = AFSample(dbSqTot);
	}

	// to avoid rollover segfaults ('i' is unsigned)
	dbSample = psmpData[0]*psmpData[0] - dbNoiseCorr;
	if(smpcI2)
	   m_dbTP2 += dbSample * smpcI2;

	dbSqTot += dbSample;
	m_asmpData[0] = AFSample(dbSqTot);

	// samples to seconds conversion
	m_dbTP2 /= track.GetFilteredDataRate();

	// Find decay real start
	FindFirstArrivalTime();
}

void TSchroederDecay::Init(APAudioTrack& track)
{
    Init(track.GetFilteredDataLength());
    Process(track);
}

void TSchroederDecay::Init(const AFSampleCount smpcLength = 0)
{
	if(smpcLength > 0)
		m_smpcLength = smpcLength;

	if(m_asmpData) delete [] m_asmpData;

	m_asmpData = new AFSample [m_smpcLength];
	memset(m_asmpData, 0, m_smpcLength*sizeof(AFSample));
}

// *** 'ctors
TSchroederDecay::TSchroederDecay()
  : m_asmpData(0),
    m_smpcLength(0),
    m_smpcFAT(0),
    m_dbTP2(0.0),
    m_dbRate(0.0)
{ }

TSchroederDecay::TSchroederDecay(const AFSampleCount smpcLength)
 : m_asmpData(0),
   m_smpcLength(smpcLength),
   m_smpcFAT(0),
   m_dbTP2(0.0),
   m_dbRate(0.0)
{ Init(); }

TSchroederDecay::~TSchroederDecay()
{
	if(m_asmpData) delete [] m_asmpData;
}

//----------------------------------------------------------------------------
// AFAcousticalParameters::TResults implementation
//----------------------------------------------------------------------------


void AFAcousticalParameters::TResults::SetBandsCount(const size_t count)
{
	if(count != m_unBandsCount)
	{
		m_unBandsCount = count;
		Init();
	}
}

void AFAcousticalParameters::TResults::Init()
{
	size_t i = m_aaParametersTable.size();

	if(i == m_unBandsCount)
		return;

	m_aaParametersTable.resize(m_unBandsCount);

	while(i < m_unBandsCount)
	{
		m_aaParametersTable[i].resize(N_PARAMETERS);
		i++;
	}
}

AFAcousticalParameters::TResults::TResults()
: m_unBandsCount(N_OCTAVE_BANDS),
  m_aaParametersTable(N_OCTAVE_BANDS, std::vector<TParameter>(N_PARAMETERS))
{ Init(); }


//----------------------------------------------------------------------------
// AFAcousticalParameters implementation
//----------------------------------------------------------------------------

double AFAcousticalParameters::ReverberationTime(const int nCh,
		                                         const double dbStart,
		                                         const double dbDelta)
{
   // Code by Angelo Farina

   APAudioTrack& track = m_paAudioTracks->Item(nCh);

   // The time immediately after the direct wave
   AFSampleCount smpcI1 = AFSampleCount( track.GetFirstArrivalTime() *
		                                 track.GetFilteredDataRate() ),
                 smpcDecayLength = m_vDecay[nCh].GetLength();

   double dbSmpl1     = dB(m_vDecay[nCh][smpcI1]), // first sample (dB)
          dbSmpl0     = dbSmpl1 - dbStart,         // Reverberation time start sample (dB value)
          dbEnd       = -dbStart - dbDelta;        // Reverberation time end sample (dB value)

   double dbY     = 0.0,
          dbSumX  = 0.0,
          dbSumY  = 0.0,
          dbSumX2 = 0.0,
          dbSumY2 = 0.0,
          dbSumXY = 0.0;

   // find the decay start time
   while( (smpcI1 < smpcDecayLength) && (dbSmpl0 < dB(m_vDecay[nCh][smpcI1])) )
       smpcI1++;

   if(smpcI1 == track.GetFilteredDataLength())
   {
	   return -1.0; // failed
   }

	double dbY1 = 0.0,
		   dbY2 = 0.0;

	// initialize x
	int nX = 1;
	dbY1 = dB(m_vDecay[nCh][smpcI1]) - dbSmpl1;

	// search and sum cycle
	do
	{
		dbY = dB(m_vDecay[nCh][smpcI1]) - dbSmpl1;

		if ((dbY >= dbEnd) && (smpcI1 < smpcDecayLength))
		{
			dbSumX  += double(nX);
			dbSumY  += dbY;
			dbSumXY += dbY * double(nX);
			dbSumX2 += double(nX) * double(nX);
			dbSumY2 += dbY * dbY;
			dbY2 = dbY;
			nX++;
		}
		smpcI1++;
	} while ((dbY >= dbEnd) && (smpcI1 < smpcDecayLength));

	// Parameters' limit validity: it should be lower in
	// noise correction case
	AFSampleCount smpcIValid;
	if(m_bNoiseCorrection)
	  smpcIValid = (smpcDecayLength - smpcDecayLength/16);
	else
	  smpcIValid = (smpcDecayLength - smpcDecayLength/64);


	if(smpcI1 > smpcIValid)
	{
		return -1.0; // failed
	}
	// regression calculation
	 AFSampleCount smpcN = nX - 1;
	 double dbDenom = (smpcN * dbSumX2 - (dbSumX * dbSumX));
	 if(dbDenom == 0.0)
	 {
		 return -1.0;
	 }

     double dbB = (smpcN * dbSumXY - dbSumX * dbSumY) / dbDenom;

	 if(m_bEDT) dbB = (dbY2-dbY1)/(smpcN-1);

	 if(dbB == 0.0)
	 {
		 return -1.0;
	 }

	 // Sabine's reverberation time
	 double dbT = (-60.0 / dbB / track.GetFilteredDataRate());

	 double dbDenom1 = (smpcN*dbSumX2 - dbSumX*dbSumX) * (smpcN*dbSumY2 - dbSumY*dbSumY);
	 if(dbDenom1 == 0.0)
	 {
		 return -1.0;
	 }

	 double dbR = fabs( (smpcN*dbSumXY - dbSumX*dbSumY) * (smpcN*dbSumXY - dbSumX*dbSumY)  / dbDenom1);

	 if( (dbR < 0.85) && (dbStart > 0.5) )
	 {
		//Insufficient correlation coefficient for rev. time
		// calculation, but not for EDT
		return -1.0;
	 }
   
	 return dbT;
}

AFSampleCount AFAcousticalParameters::GetShorterFAT()
{
	int nChr = (m_nMode != APM_SOUNDFIELD_WXYZ ) ? 1 : 2;

	AFSampleCount lfat = 0,
			      rfat = 0;

#ifdef MULTIRATE_FILTERING
	lfat = m_vDecay[CH_LEFT].GetFirstArrivalTimeInSamples();
	rfat = m_vDecay[nChr].GetFirstArrivalTimeInSamples();
#else
	lfat = FAT_IN_SAMPLES(CH_LEFT);
	rfat = FAT_IN_SAMPLES(nChr);
#endif

	return (lfat < rfat) ? lfat : rfat;
}

//------------------------- Parameters methods -------------------------

double AFAcousticalParameters::Clarity(const int nCh, const double dbWidth, const double dbDelay)
{
   //Clarity index calculation (C50, C80, ...)
   //NB: width must be in seconds!
   double rate = AFSampleCount(m_paAudioTracks->Item(nCh).GetFilteredDataRate());

   AFSampleCount delta = 0,
                 fat   = 0;

   delta = rate *(dbWidth + dbDelay),

#ifdef MULTIRATE_FILTERING
   fat = m_vDecay[nCh].GetFirstArrivalTimeInSamples();
#else
   fat = AFSampleCount(m_paAudioTracks->Item(nCh).GetFirstArrivalTime() * rate);
#endif

   printf("c50: delta %d, fat %d, dec_fat %f, dec_fat_delta %f\n",
		     (int)delta, (int)fat,
		      m_vDecay[nCh][fat],m_vDecay[nCh][fat + delta]);
   // result in dB
   return ( 10.0 *log10((m_vDecay[nCh][fat] - m_vDecay[nCh][fat + delta]) /
                         m_vDecay[nCh][fat + delta]));
}

double AFAcousticalParameters::Definition(const int nCh, const double dbWidth, const double dbDelay)
{
   //Definition index calculation (D50, ...)
   //NB: width must be in seconds!
   double rate = AFSampleCount(m_paAudioTracks->Item(nCh).GetFilteredDataRate());

   AFSampleCount delta = 0,
				 fat   = 0;

   delta = rate *(dbWidth + dbDelay),

#ifdef MULTIRATE_FILTERING
   fat = m_vDecay[nCh].GetFirstArrivalTimeInSamples();
#else
   fat = AFSampleCount(m_paAudioTracks->Item(nCh).GetFirstArrivalTime() * rate);
#endif

   // result in %
   return (100.0 * (( m_vDecay[nCh][fat] - m_vDecay[nCh][fat + delta] ) /
                      m_vDecay[nCh][fat] ));
}

double AFAcousticalParameters::EarlyLateralFraction(const double dbDelay)
{
   // aka: JLF
   AFSampleCount smpcDelta_5  = DELTA_T(CH_LEFT, 0.005),
		         smpcDelta_80 = DELTA_T(CH_LEFT, 0.080),
                 lfat     = 0,
                 rfat     = 0;
   
   double dbGain = 1.0;
   int nChl = 0, nChr = 1;

   switch(m_nMode)
   {
       case APM_SOUNDFIELD_WY:
           dbGain = 0.5;  // It's a Soundfield: need double W energy
           break;

       case APM_SOUNDFIELD_WXYZ:
           dbGain = 0.5; nChr = 2;
           break;

       case APM_SOUNDFIELD_WYXZ:
           dbGain = 0.5; nChr = 1;
           break;
   }
#ifdef MULTIRATE_FILTERING
   lfat = m_vDecay[nChl].GetFirstArrivalTimeInSamples();
   rfat = m_vDecay[nChr].GetFirstArrivalTimeInSamples();
#else
   lfat = AFSampleCount(m_paAudioTracks->Item(nChl).GetFirstArrivalTime() *
		                m_paAudioTracks->Item(nChl).GetFilteredDataRate());
   rfat = AFSampleCount(m_paAudioTracks->Item(nChr).GetFirstArrivalTime() *
                        m_paAudioTracks->Item(nChr).GetFilteredDataRate());
#endif

   return dbGain * ( (m_vDecay[nChr][rfat + smpcDelta_5] -
		              m_vDecay[nChr][rfat + smpcDelta_80]) /
                     (m_vDecay[nChl][lfat] -
                      m_vDecay[nChl][lfat + smpcDelta_80]) );
}

double AFAcousticalParameters::EarlyLateralFractionCosine(const double dbDelay)
{
   // aka: JLFC
   AFSampleCount i,
                 smpcDelta_5  = DELTA_T(CH_LEFT, 0.005),
                 smpcDelta_80 = DELTA_T(CH_LEFT, 0.080),
	             smpcFAT      = GetShorterFAT();

   double dbSumL = 0.0,
		  dbSumR = 0.0,
		  dbGain = 1.0;

   AFSample *psmpLeft  = m_paAudioTracks->Item(CH_LEFT).GetFilteredData(),
		    *psmpRight = 0;
   
   switch(m_nMode)
   {
       case APM_SOUNDFIELD_WY:
           dbGain = M_SQRT1_2;  // It's a Soundfield: need double W energy
           psmpRight = m_paAudioTracks->Item(1).GetFilteredData(); //Y
           break;

       case APM_SOUNDFIELD_WXYZ:
           dbGain = M_SQRT1_2;
           psmpRight = m_paAudioTracks->Item(2).GetFilteredData(); //Y
           break;

       case APM_SOUNDFIELD_WYXZ:
           dbGain = M_SQRT1_2;
           psmpRight = m_paAudioTracks->Item(1).GetFilteredData(); //Y
           break;

       default:
    	   psmpRight = m_paAudioTracks->Item(1).GetFilteredData();
    	   break;
   }
   

   for( i = smpcFAT + smpcDelta_5; i < (smpcFAT + smpcDelta_80); i++)
       dbSumR += psmpRight[i]*psmpRight[i];
   
   for( i = smpcFAT; i < (smpcFAT + smpcDelta_80); i++)
       dbSumL += psmpLeft[i]*psmpLeft[i];
   
   return dbGain * (dbSumR/dbSumL);
}

double AFAcousticalParameters::LateLateralSoundLevel(const int nBand, const double dbDelay)
{
   AFSampleCount delta_80 = 0,
		         fat      = 0;

   delta_80 = AFSampleCount(m_paAudioTracks->Item(CH_LEFT).GetSamplerate()*(0.080 + dbDelay)),
   fat      = GetShorterFAT();

   // aka LJ is given
   // by the logarithmic ratio between the late energy of the left
   // channel (after the first 80 ms) and the 10 m reference value.
   // Result in dB
   return ( dB(m_vDecay[CH_LEFT][fat + delta_80]) - m_adbReferenceLevels[nBand]);
}

double AFAcousticalParameters::InterAuralCrossCorrelation(const double dbDelay,
		                                                  double* pdbTauIACC,
		                                                  double* pdbWidthIACC)
{
   APAudioTrack& left  = m_paAudioTracks->Item(CH_LEFT);
   APAudioTrack& right = m_paAudioTracks->Item(CH_RIGHT);

   AFSampleCount smpcDelta_1  = DELTA_T(CH_LEFT, 0.001);
   AFSampleCount smpcDelta_80 = DELTA_T(CH_LEFT, 0.080);
   
   // Integration limits definition (smpcT1 and smpcT2)
   AFSampleCount smpcT1, smpcT2,
                 smpcFAT = GetShorterFAT();
   
   switch (m_nIaccSpan)
   {
        case IS_EARLY: // 0-80 ms
            smpcT1 = smpcFAT;
            smpcT2 = smpcFAT + smpcDelta_80;
            break;
        case IS_LATE: // 80-inf ms
            smpcT1 = smpcFAT   + smpcDelta_80;
            smpcT2 = left.GetFilteredDataLength() - smpcDelta_1;
            break;
        case IS_ALL: // 0-inf ms
            smpcT1 = smpcFAT;
            smpcT2 = left.GetFilteredDataLength() - smpcDelta_1;
            break;
        default: // error, force 0
            m_nIaccSpan = IS_EARLY;
            smpcT1 = smpcFAT;
            smpcT2 = smpcFAT + smpcDelta_80;
            break;
    }
   
    if ((smpcT1 - smpcDelta_1) < 0) smpcT1 = smpcDelta_1; // prevents negative index ?????
   
   // istantiate buffer to store the crosscorrelation 
    AFSampleCount smpcRLen = 2*smpcDelta_1 + 1;
    double *pdbR = new double [smpcRLen];
    memset(pdbR, 0, smpcRLen*sizeof(double));


   AFSample *psmpLeft  = left.GetFilteredData(),
		    *psmpRight = right.GetFilteredData();

   double dbSumL  = 0.0,
          dbSumR  = 0.0;
   
   // Denominator calculation
   for (AFSampleCount smpcT = smpcT1; smpcT < smpcT2; smpcT++)
   {
      dbSumL += psmpLeft[smpcT]*psmpLeft[smpcT];
      dbSumR += psmpRight[smpcT]*psmpRight[smpcT];
   }
   double dbDen = sqrt(dbSumL*dbSumR);
   
   // Numerator calculation
   int nT, nTplusTau;
   double dbSumLR = 0.0;
   for(int nTau = -smpcDelta_1; nTau < int(smpcDelta_1); nTau++)
   {
      dbSumLR = 0.0;
      for(nT = int(smpcT1); (nT < (smpcT2)) && (nT <= int(left.GetFilteredDataLength())); nT++ )
      {
         nTplusTau = nT + nTau;
         if( (nTplusTau > 0) && (nTplusTau < int(left.GetFilteredDataLength())) )
            dbSumLR += psmpLeft[nT] * psmpRight[nTplusTau];
         
      }
      // CrossCorrelation function storage
      pdbR[nTau + smpcDelta_1] = dbSumLR/dbDen;
   }
   
   //find r maximum
   double dbIACC  = 0.0;
   int    nTauMax = 0;
   for(nT = 0; nT < int(smpcRLen); nT++)
   {
       if(fabs(pdbR[nT]) > dbIACC)
      {
         dbIACC = fabs(pdbR[nT]);
         nTauMax = nT;
      }
   }
   
   //find peak side width
   double dbThreshold = 0.9 * dbIACC;
   nT = nTauMax;
   while( (nT >= 0) &&  (fabs(pdbR[nT]) > dbThreshold)) nT--;
   int nLeftSide  = nT;
   
   nT = nTauMax;
   while( (nT <= long(smpcRLen)) && (fabs(pdbR[nT]) > dbThreshold)) nT++;
   int nRightSide = nT;
   
   // This is the maximum peak's delay (ms)
   *pdbTauIACC = 1000.0 *(nTauMax - int(smpcDelta_1)) / left.GetFilteredDataRate();

   if( (nRightSide - nLeftSide) < int(smpcRLen - 1) )
      // This is the maximum peak's width (ms)
      *pdbWidthIACC   = 1000.0 *(nRightSide - nLeftSide) / left.GetFilteredDataRate();
   else 
      *pdbWidthIACC = -1; //means not valid (r is monotone, i.e.)

   delete [] pdbR;

   return dbIACC;
}

double AFAcousticalParameters::Peakiness(const int nCh)
{
   double sq;
   double max = 0.0;
   double sum = 0.0;

   AFSample *data = m_paAudioTracks->Item(nCh).GetFilteredData();

   for(AFSampleCount i=0;
	   i < m_paAudioTracks->Item(nCh).GetFilteredDataLength();
	   i++)
   {
      if((sq = data[i]*data[i]) > max)
          max = sq;

      sum += sq;
   }
   
   sum /= m_paAudioTracks->Item(nCh).GetFilteredDataLength(); // Samples RMS value

   return 10.0*log10(max/sum);
}


double AFAcousticalParameters::Millisecondness(const int nCh,
		                                       const int nBand,
		                                       double* pdbImpulsivs)
{
   APAudioTrack& track = m_paAudioTracks->Item(nCh);
   AFSampleCount i, j;

   // Build 1 ms RMS data vector
   AFSample *psmpData = track.GetFilteredData();

   AFSampleCount smpcDecimationStep = AFSampleCount(track.GetFilteredDataRate() /
		                                            1000.0); // 1 ms rate
   if(smpcDecimationStep == 0)
	   return -200.0;

   AFSampleCount smpcUndersDataLength  = (track.GetFilteredDataLength() /
		                                  smpcDecimationStep) + 1;

   double* adbUndersIr = new double [smpcUndersDataLength];
   memset(adbUndersIr, 0, smpcUndersDataLength*sizeof(double));

   for(i = track.GetFirstArrivalTime(); i < track.GetFilteredDataLength(); i++)
   {
      j = AFSampleCount( i / smpcDecimationStep );
      adbUndersIr[j] += psmpData[i] * psmpData[i];
   }

   // Rescale buffer values to obtain correct dB levels
   double dbScaleFactor  = pow( 10.0, m_dbFullScale/10.0) / m_dbRate;
   for(i = 0; i < smpcUndersDataLength; i++)
	   adbUndersIr[i] *= dbScaleFactor;

   double dbVal,
          dbMax = 0.0,
          dbSum = 0.0,
          dbImpVal = 0.0,
          dbImpValMax = 0.0;

   for(i = 0; i < (smpcUndersDataLength - 35); i++)
   {
      if( (dbVal = adbUndersIr[i]) > dbMax )
	       dbMax = dbVal;

      dbSum += dbVal;
        
      dbImpVal = 0.0;
      for(j = 0; j < 35 ; j++)
         //Impx is the mean value over 35 ms: it's the Impulse value
         dbImpVal += adbUndersIr[i + j];

      if(dbImpVal > dbImpValMax) dbImpValMax = dbImpVal;
   }
   delete [] adbUndersIr;

   dbSum /= (double(smpcUndersDataLength) - 35.0); // RMS of Millisecondness buffer

   // This is the Impulsiveness value (maximum of Impulse means over 35 ms)...
   *pdbImpulsivs = 10.0 * log10( dbImpValMax/(35.0 * dbSum) );

   // ...and this the millisecondness one.
   return 10.0 * log10(dbMax/dbSum);
}

double AFAcousticalParameters::Stage(const int nPar, const int nCh, const double dbDelay)
{
	APAudioTrack& track = m_paAudioTracks->Item(nCh);

   AFSampleCount smpcDeltaT1 = 0;
   AFSampleCount smpcDeltaT2 = 0;
   AFSampleCount smpcDelta_10 = DELTA_T(nCh, 0.010);

    double rate = track.GetFilteredDataRate();

    switch(nPar)
    {
        case AP_ST1:
            smpcDeltaT1 = DELTA_T(nCh, 0.020);
            smpcDeltaT2 = DELTA_T(nCh, 0.100);
            break;
        case AP_ST2: 
            smpcDeltaT1 = DELTA_T(nCh, 0.020);
            smpcDeltaT2 = DELTA_T(nCh, 0.200);
            break;
        case AP_STL: 
            smpcDeltaT1 = DELTA_T(nCh, 0.100);
            smpcDeltaT2 = DELTA_T(nCh, 1.000);
            break;
    }

    smpcDeltaT1 += AFSampleCount(rate * dbDelay);
    smpcDeltaT2 += AFSampleCount(rate * dbDelay);

    // 5: St1, need IR lenght (from FAT) of almost 100 ms
    // 6: St2, need IR lenght (from FAT) of almost 200 ms
    // 7: StL, need IR lenght (from FAT) of almost 1000 ms

#ifdef MULTIRATE_FILTERING
    AFSampleCount fat = m_vDecay[nCh].GetFirstArrivalTimeInSamples();
#else
    AFSampleCount fat = AFSampleCount(track.GetFirstArrivalTime() * rate);
#endif

    AFSampleCount d = track.GetFilteredDataLength() - fat;

    if( d < smpcDeltaT2)
        return 0.0;

	return  dB( (m_vDecay[nCh][fat + smpcDeltaT1] -
			     m_vDecay[nCh][fat + smpcDeltaT2]) /
                (m_vDecay[nCh][fat] -
                 m_vDecay[nCh][fat + smpcDelta_10]) );
}

double AFAcousticalParameters::Strength(const int nCh, const int nBand) 
{
   // StrenGth: It's given by the subtraction from Signal of the 
   //           10 m reference value (function of frequency)
   return m_vResults[nCh].GetSignalLevel(nBand) - m_adbReferenceLevels[nBand];

}

void AFAcousticalParameters::PreProcessIntensimetricSignal(APAudioTrack& left)
{
	if(m_nChnlsCount < 2) return;

	APAudioTrack& right = m_paAudioTracks->Item(CH_RIGHT);

	double dbPressure,dbVelocity = 0.0,
		   dbDt  = 1.0 / m_dbRate,  // sampling time interval in seconds
		   dbFactor = m_dbSoundSpeed * dbDt / m_dbProbeMicsDistance;

	// Copy Ir to IrFiltered: this is the work buffer. (MAYBE UNUSEFUL: check program flux !!)
	left.ResetFilteredTrack();
	right.ResetFilteredTrack();

	// Now applying band pass filtering
	left.LFilter();
	right.LFilter();

	AFSample *psmpLeft  = left.GetFilteredData(),
			 *psmpRight = right.GetFilteredData();

	// Evaluating pressure (p) and velocity (v)
	for(AFSampleCount i=0; i< left.GetLength(); i++)
	{
		// dbPressure = (p1+p2)/2
		dbPressure  = 0.5 * (psmpLeft[i] + psmpRight[i]);
		// dbVelocity = Integral((p2-p1)/d*c*dbDt) - Euler's law
		dbVelocity += dbFactor* (psmpRight[i] - psmpLeft[i]);

		psmpLeft [i] = AFSample(dbPressure); // left  = dbPressure
		psmpRight[i] = AFSample(dbVelocity); // right = dbVelocity
	}

	// Now removing DC component
	left.RemoveMean();
	right.RemoveMean();

	// Re-applying 20-20kHz band pass filtering
	left.LFilter();
	right.LFilter();

	// Copy back processed Irs.
	left.ReplaceTrackWithFiltered();
	right.ReplaceTrackWithFiltered();
}

bool AFAcousticalParameters::CalculateAcousticParameters()
{
	APAudioTrack& left  = m_paAudioTracks->Item(CH_LEFT);


    //Create progress bar.
	int nProg = 0;
    InitProgressMeter(1 + 2*m_unBandsCount*m_nChnlsCount); //PP probe filtering, mono & stereo

	m_dbRate = left.GetRate();

   // Intensimetric Probe (P-P) elaboration
   if ( IsAnIntensityProbe() )  // PP probe
   {
	   PreProcessIntensimetricSignal(left);
   }

   UpdateProgressMeter(++nProg);

   //First Arrival Time search: start with left channel (is this the correct place??)
   int nCh;
   for(nCh = 0; nCh < m_nChnlsCount; nCh++)
   {
	   // With multirate filtering code, this doesn't work very well [SC]
	   if(m_paAudioTracks->Item(nCh).FindFirstArrivalTime(m_dbDirectSoundTrig) <= 0.0)
	   {
	      ShowErrorMessage(ERR_NO_FAT);
	      return false;
	   }
	   m_vResults[nCh].SetBandsCount((size_t)m_unBandsCount);
   }
   
#ifdef MULTIRATE_FILTERING
   for(nCh = 0; nCh < m_nChnlsCount; nCh++)
   {
	   switch(m_nAnalysisType)
	   {
		   case AP_OCTAVE_BANDS:

			   m_vOba.push_back(dynamic_cast<SCOctaveBandAnalysisBase*>(new SCOctaveBandAnalysis(m_dbRate)));
			   break;

		   case AP_ONE_THIRD_OCTAVE_BANDS:
			   m_vOba.push_back(dynamic_cast<SCOctaveBandAnalysisBase*>(new SCThirdOctaveBandAnalysis(m_dbRate)));
			   break;
	   }
	   m_vOba[nCh]->Init(&(m_paAudioTracks->Item(nCh)));
   }
#endif

   // Noise correction and acoustical parameters calculation for bands 1-10 
   double dbDelay = 0.0;
   //double dbHalfRate = m_dbRate / 2.1;

   //const float dbGain = 12.8825f; // to be verified..... = 22.2 dB ???    
   double dbGain;

   const int bdLin = (int)m_unBandsCount - 1;
   const int bdA   = bdLin -1;

   int nBand  = bdLin;
   double exp = (m_nAnalysisType == AP_ONE_THIRD_OCTAVE_BANDS) ? 13.0 : 12.0;

   // -------------------- Parameters loop ----------------------

   while(nBand >= 0)
   {
	   //if(g_adbOctaveBandFcb[nBand] > dbHalfRate) // ???? REMOVE IT
	   //{ continue; }

       for(nCh = 0; nCh < m_nChnlsCount; nCh++)
	   {
#ifdef __AUDEBUG__
    	   printf("PROCESSING BAND %d , CHANNEL %d\n", nBand, nCh+1);
#endif
	       if( (nBand == bdA) && (m_bAvgMode) )
	       {
				// If m_bAvgMode is set, every Band A parameter value is
				//  the mean of bands 250 to 2000 Hz parameters values
				CalculateBandAParametersAvg(nCh);
				continue;
	       }

		   // Apply dbGain to mIrFiltered
	       dbGain = (nBand < bdA) ? 12.8825 : 1.0; // to be verified..... = 22.2 dB ???

		   // if(White2Pink)
		   //    dbGain *= pow(10.0, ( (5.0 - g_adbOctaveBandFcb[m_nActiveBand]) * 3.0102999566398119521373889472449)/20 );

		   dbDelay = 0.0;

#ifdef MULTIRATE_FILTERING

           //Applying appropriate filter
           if(nBand == bdA)
           {
			   m_paAudioTracks->Item(nCh).ResetFilteredTrack(0, dbGain);
			   m_paAudioTracks->Item(nCh).AFilter();
           }
           else if(nBand == bdLin)
           {
			   m_paAudioTracks->Item(nCh).ResetFilteredTrack(0, dbGain);
			   m_paAudioTracks->Item(nCh).LFilter();
		   }
           else
           {
			   if(m_vOba[nCh]->Filter() < 0)
			   {
				   printf("Filtering failed!\n");
				   continue;
			   }

#    ifdef __AUDEBUG__
			   printf("Chanl %d, band %d data filtered at %.1f Hz (%d samples)\n",    // <---
					   nCh, nBand,
					   (double)m_paAudioTracks->Item(nCh).GetFilteredDataRate(),
					   (int)m_paAudioTracks->Item(nCh).GetFilteredDataLength());      // REMOVE BEFORE FLIGHT
//			  DumpData(m_paAudioTracks->Item(nCh).GetFilteredData(),
//					    (const int)m_paAudioTracks->Item(nCh).GetFilteredDataLength(),
//					    (nCh+1)*100 + nBand, "ap_band");                               // <---
#    endif

			   // Definition of the dbDelay for current octave filter group
			   dbDelay = 0.05; // 50 ms @ 31.5 Hz
			   for (int i = 1; i <= nBand; i++)
			   	   dbDelay *= 0.5;  // for every octave divide by two
           }

#else
           m_paAudioTracks->Item(nCh).ResetFilteredTrack(0, dbGain);

            //Applying appropriate filter
           switch(nBand)
           {
           	   case bdA:   m_paAudioTracks->Item(nCh).AFilter(); break;
			   case bdLin: m_paAudioTracks->Item(nCh).LFilter(); break;
			   default:
				   m_paAudioTracks->Item(nCh).OctaveFilter(0, g_adbOctaveBandFcb[nBand]);

				   // Definition of the dbDelay for current octave filter group
				   dbDelay = 0.05; // 50 ms @ 31.5 Hz
				   for (int i = 1; i <= nBand; i++)
					   dbDelay *= 0.5;  // for every octave divide by two

				   break;
            }
#endif

           //Subctracting mean value
           m_paAudioTracks->Item(nCh).RemoveMean();
            
           // If is the case, do noise correction factor evaluation
           // otherwise, set it to 0.0
           if(m_bNoiseCorrection)
               m_paAudioTracks->Item(nCh).NoiseCorrection();
                        
           // Schroeder Integral calculation
           m_vDecay[nCh].Process(m_paAudioTracks->Item(nCh));
//         DumpData(m_vDecay[nCh].Get(), (const int)m_vDecay[nCh].GetLength(), (nCh+1)*100 + nBand, "ap_decay");
           CalculateBandMonoParameters(nCh, nBand, dbDelay);

           // Update progress meter
           if(!UpdateProgressMeter(++nProg))
           {
               DestroyProgressMeter();
               return false;
           }

           // Evaluating Acoustic Parameters for the current band (remember: band 11 is WIDE)
           if( ( IsStereo()         ||
                 IsSoundfieldWY()   ||
                 IsSoundfieldWXYZ() ||
                 IsSoundfieldWYXZ() )&& nCh == 1)
               CalculateSpatialParameters(nBand, dbDelay);

           // Update progress meter
           if(!UpdateProgressMeter(++nProg))
           {
           	   DestroyProgressMeter();
               return false;
           }
       }

       nBand--;
       exp -= (m_nAnalysisType == AP_ONE_THIRD_OCTAVE_BANDS) ? 1.0 : 3.0;

   }
   DestroyProgressMeter();

   //   PostProcess();
   return true;
}


void AFAcousticalParameters::CalculateBandMonoParameters(const int nCh,
		                                                 const int nBand,
		                                                 const double dbDelay)
{

   AFSampleCount smpcDelta_50 = DELTA_T(nCh, 0.050);  // 50 ms + dbDelay delta
   AFSampleCount smpcDelta_80 = DELTA_T(nCh, 0.080);  // 80 ms + dbDelay delta
   AFSampleCount smpcFAT      = FAT_IN_SAMPLES(nCh);

   APAudioTrack& track = m_paAudioTracks->Item(nCh);

   double dbImpulsivs;

   printf("Calculating MONO parameters for band %d\n", nBand);

   // 0: Signal
   // The result is a SEL - FS (= m_dbFullScale [dB]) diluted on 1 s.
   m_vResults[nCh].SetSignalLevel( dB(m_vDecay[nCh][0]) +
		                           track.GetFullScale() -
		                           dB(track.GetFilteredDataRate()),
		                           nBand );
   m_vResults[nCh].ValidateParameter(AP_SIGNAL, nBand);
   
   // 1: Noise
   if(track.GetNoiseCorrFactor() > 0.0)
   {
      // m_adbNoiseCorrFactor is a Leq, so it has to be multiplied by the number of samples, then
      // diluted on 1 s.
	  m_vResults[nCh].SetNoiseLevel( dB(track.GetNoiseCorrFactor() *
			                            m_vDecay[nCh].GetLength()) +
                                     m_dbFullScale -
                                     dB(track.GetFilteredDataRate()),
                                     nBand );
	  m_vResults[nCh].ValidateParameter(AP_NOISE, nBand);
   }
   else
   {
	   m_vResults[nCh].SetNoiseLevel(0.0, nBand);
   }
//------------------------------------------------------------------------------------------------!!!!
   printf("Lsg(%d) = %.1f + %.1f - %.1f = %.1f dB\n", nBand,
		                                              dB(m_vDecay[nCh][0]),
                                                      track.GetFullScale(),
                                                      dB(track.GetFilteredDataRate()),
                                                    		  dB(m_vDecay[nCh][0]) +
                                                      track.GetFullScale() -
                                                      dB(track.GetFilteredDataRate() ));

   // 2: strength;
   m_vResults[nCh].SetStrength( Strength(nCh, nBand), nBand);
   m_vResults[nCh].ValidateParameter(AP_G, nBand);

   if( (m_vDecay[nCh].GetLength() - smpcFAT) > smpcDelta_50 )
   {
      // 3: C50, needs IR lenght of 50 ms (starting from FAT)
	   m_vResults[nCh].SetC50( Clarity(nCh, 0.05, dbDelay), nBand );
	   m_vResults[nCh].ValidateParameter(AP_C50, nBand);

      // 5: D50, idem c.s.
	   m_vResults[nCh].SetD50( Definition(nCh, 0.05, dbDelay), nBand );
	   m_vResults[nCh].ValidateParameter(AP_D50, nBand);
   }

   // 4: C80, needs IR lenght of 80 ms (starting from FAT)
   if( (m_vDecay[nCh].GetLength() - smpcFAT) > smpcDelta_80 )
   {
	   m_vResults[nCh].SetC80( Clarity(nCh, 0.08, dbDelay), nBand );
	   m_vResults[nCh].ValidateParameter(AP_C80, nBand);
   }

   // 6: TS, it exist always (N.B. in ms, not in s!!!)   
   m_vResults[nCh].SetTs( m_vDecay[nCh].GetTP2() * 1000.0/m_vDecay[nCh][smpcFAT], nBand );
   m_vResults[nCh].ValidateParameter(AP_Ts, nBand);

   //7: EDT - 10dB
   if( (m_vResults[nCh].GetEDT(nBand) = ReverberationTime(nCh, 0.1, 10.0)) > 0.0 )
	   m_vResults[nCh].ValidateParameter(AP_EDT, nBand);

   // If m_bStageMode is true, evaluate Stage Parameters, that subsitutes
   //  D50, Ts and EDT
    if(m_bStageMode) 
    {
        //5->14: ST1
        if( (m_vResults[nCh].GetSt1(nBand) = Stage(AP_ST1, nCh, dbDelay)) != 0.0 )
        	m_vResults[nCh].ValidateParameter(AP_ST1, nBand);

        //6->15: ST2 ->
        if( (m_vResults[nCh].GetSt2(nBand) = Stage(AP_ST2, nCh, dbDelay)) != 0.0 )
        	m_vResults[nCh].ValidateParameter(AP_ST2, nBand);

        //7->16: STL
        if( (m_vResults[nCh].GetStL(nBand) = Stage(AP_STL, nCh, dbDelay)) != 0.0 )
        	m_vResults[nCh].ValidateParameter(AP_STL, nBand);
          
    }

    //8: RT-USER
    if( (m_vResults[nCh].GetTuser(nBand) =
    		ReverberationTime(nCh, fabs(m_dbUserMinLevel),
                                   fabs(m_dbUserMaxLevel-m_dbUserMinLevel))) > 0.0 )
    	m_vResults[nCh].ValidateParameter(AP_Tuser, nBand);

    //9: RT-20dB
    if( (m_vResults[nCh].GetT20(nBand) = ReverberationTime(nCh, 5.0, 20.0)) > 0.0 )
    	m_vResults[nCh].ValidateParameter(AP_T20, nBand);

    //10: RT-30dB
    if( (m_vResults[nCh].GetT30(nBand) = ReverberationTime(nCh, 5.0, 30.0)) > 0.0 )
    	m_vResults[nCh].ValidateParameter(AP_T30, nBand);

        // 11: Peakiness calculation (only if mono or 2 indep. omni input signal)
    m_vResults[nCh].GetPeakiness(nBand) =  Peakiness(nCh);
    m_vResults[nCh].ValidateParameter(AP_PEAKINESS, nBand);

    // 12: Millisecondness calculation (only if mono or 2 indep. omni input signal)
    if((m_vResults[nCh].GetMillisecs(nBand) =
    		Millisecondness(nCh, nBand, &dbImpulsivs) ) > -200.0)
    {
 	    m_vResults[nCh].ValidateParameter(AP_MILLISECS, nBand);

        // 13: Impulsiveness
        m_vResults[nCh].SetImpulsiveness( dbImpulsivs, nBand );
 	    m_vResults[nCh].ValidateParameter(AP_IMPULSIVS, nBand);
    }
}

void AFAcousticalParameters::CalculateSpatialParameters(int nBand, double dbDelay)  
{
   double dbWidthIACC, dbTauIACC;
   AFSampleCount smpcDelta_80 = DELTA_T(CH_LEFT, 0.080);

   AFSampleCount ld = LENGTH_FROM_FAT_IN_SAMPLES(CH_LEFT);
   AFSampleCount rd = LENGTH_FROM_FAT_IN_SAMPLES(CH_RIGHT);

   //For all these calcules, need Ir length of almost 80 ms (from FAT)
	if( (ld  < smpcDelta_80) && (rd < smpcDelta_80) )
    {
    	ShowErrorMessage(ERR_SPATIAL_IR_TOO_SHORT);
    	return;
    }

	if( (m_nMode == APM_SOUNDFIELD_WY)   ||
		(m_nMode == APM_PU_PROBE)        ||
		(m_nMode == APM_INTENSITY_PROBE) ||
		(m_nMode == APM_SOUNDFIELD_WXYZ) ||
		(m_nMode == APM_SOUNDFIELD_WYXZ) )
	{
		// 20: Lateral Fraction, needs IR lenght of 80 ms (starting from FAT)
		m_vResults[CH_LEFT].SetJlf( EarlyLateralFraction(dbDelay), nBand );
		m_vResults[CH_RIGHT].GetJlf(nBand) =  m_vResults[CH_LEFT].GetJlf(nBand);

		// 21: LFC, needs at least 80ms IR lenght starting from FAT
		m_vResults[CH_LEFT].SetJlfc( EarlyLateralFractionCosine(dbDelay), nBand );
		m_vResults[CH_RIGHT].GetJlfc(nBand) =  m_vResults[CH_LEFT].GetJlfc(nBand);

		// 22: LG, needs at least 80ms IR lenght starting from FAT
		m_vResults[CH_LEFT].SetLj( LateLateralSoundLevel(nBand, dbDelay), nBand );

		// *****FIXIT**** in the soundfield case it needs a correction***************************************FIXIT*****
		m_vResults[CH_RIGHT].GetLj(nBand) =  m_vResults[CH_LEFT].GetLj(nBand);

		m_vResults[CH_LEFT].ValidateParameter(AP_JLF, nBand);
		m_vResults[CH_LEFT].ValidateParameter(AP_JLFC, nBand);
		m_vResults[CH_LEFT].ValidateParameter(AP_LJ, nBand);

		m_vResults[CH_RIGHT].ValidateParameter(AP_JLF, nBand);
		m_vResults[CH_RIGHT].ValidateParameter(AP_JLFC, nBand);
		m_vResults[CH_RIGHT].ValidateParameter(AP_LJ, nBand);
	}
	else if(m_nMode == APM_BINAURAL)
	{
		// IACC=17, Tau IACC=18, w IACC=19 evaluation
		// 14, etc., needs at least 80ms IR lenght starting from FAT

		m_vResults[CH_LEFT].SetIACC( InterAuralCrossCorrelation(dbDelay, &dbTauIACC, &dbWidthIACC), nBand );
		m_vResults[CH_LEFT].SetIACC_time( dbTauIACC, nBand );

		m_vResults[CH_RIGHT].GetIACC(nBand)      =  m_vResults[CH_LEFT].GetIACC(nBand);
		m_vResults[CH_RIGHT].GetIACC_time(nBand) =  m_vResults[CH_LEFT].GetIACC_time(nBand);

		if(dbWidthIACC > 0)
		{
			m_vResults[CH_LEFT].SetIACC_width( dbWidthIACC, nBand );
			m_vResults[CH_RIGHT].GetIACC_width(nBand) =  m_vResults[CH_LEFT].GetIACC_width(nBand);

			m_vResults[CH_LEFT].ValidateParameter(AP_IACC, nBand);
			m_vResults[CH_LEFT].ValidateParameter(AP_T_IACC, nBand);
			m_vResults[CH_LEFT].ValidateParameter(AP_W_IACC, nBand);

			m_vResults[CH_RIGHT].ValidateParameter(AP_IACC, nBand);
			m_vResults[CH_RIGHT].ValidateParameter(AP_W_IACC, nBand);
			m_vResults[CH_RIGHT].ValidateParameter(AP_T_IACC, nBand);
		}
    }
}

void  AFAcousticalParameters::CalculateBandAParametersAvg(int nCh)
{
   double dbValue;

   // Calculate Band A parameters as the mean of 250 to 2000 Hz
   // bands parameters.
   for(int nPar = 0; nPar < N_PARAMETERS; nPar++)
   {
      dbValue = 0.0;
      for(int nBand = BD_250; nBand <= BD_2k; nBand++) 
      {
         if(m_vResults[nCh].IsParameterValid(nPar, nBand))
               dbValue += m_vResults[nCh].GetParameter(nPar, nBand);
         
      }
      dbValue /= 4.0;

      if((m_vResults[nCh].GetParameter(nPar, BD_A) = dbValue) > 0.0)
          m_vResults[nCh].ValidateParameter(nPar, BD_A);
   }
}     


//------------------------- Class user interface -------------------------   
// --- 2nd part: get acustic parameters values (post processing)

void AFAcousticalParameters::UpdateFilteredTrack(const int nChnl, const int nBand)
{
#ifdef MULTIRATE_FILTERING
	if((nBand != BD_A) && (nBand != BD_Lin))
	{
	     m_vOba[nChnl]->FilterForBand(nBand);
	}
	else
	{
		m_paAudioTracks->Item(nChnl).ApplyFilter(nBand);
	}
#else
	m_paAudioTracks->Item(nChnl).ApplyFilter(nBand);
#endif

    if(m_bNoiseCorrection)
	    m_paAudioTracks->Item(nChnl).NoiseCorrection();
	else
		m_paAudioTracks->Item(nChnl).GetNoiseCorrFactor() = 0.0;

    m_vDecay[nChnl].Process(m_paAudioTracks->Item(nChnl));
}

void AFAcousticalParameters::ReplaceGReferenceValues()
{
   for(size_t nBd = 0; nBd < m_unBandsCount; nBd++)
   {
      if(m_vResults[CH_LEFT].IsParameterValid(AP_SIGNAL, nBd))
      {
         // the reference signal MUST be stored on channel 0 (Left)
         m_adbReferenceLevels[nBd] = m_vResults[CH_LEFT].GetSignalLevel(nBd) +
                                     dB20(m_dbSoundSourceDistance / 10.0);

         //Update parameters table
         for(int nCh = 0; nCh < m_nChnlsCount; nCh++)
        	 m_vResults[nCh].GetStrength(nBd) = Strength(nCh, nBd);
      }
   }
}

void AFAcousticalParameters::RestoreDefaultReferenceLevels()
{
	int nBands = 0;
	while(nBands < (int)m_unBandsCount)
	{
	  m_adbReferenceLevels[nBands] = 69.0;   // Source ref. lev. @ 10m - Lw=100 dB
	  nBands++;
	}
	m_adbReferenceLevels[nBands-2] = 79.0;     // Source ref. lev. @ 10m - Lw=110 dB(Lin)
	m_adbReferenceLevels[nBands-1] = 77.0;     // Source ref. lev. @ 10m - Lw=108 dB(A)
}


void AFAcousticalParameters:: SetAnalysisType(const int type)
{
    if(type >= 0)
    {
    	m_nAnalysisType = type;
    }

    switch(m_nAnalysisType)
    {
        case AP_OCTAVE_BANDS:
    	    m_unBandsCount = N_OCTAVE_BANDS;
    	    break;

        case AP_ONE_THIRD_OCTAVE_BANDS:
    	    m_unBandsCount = N_THIRD_OCTAVE_BANDS;
    	    break;
    }

    if(m_adbReferenceLevels.size() != m_unBandsCount)
    {
        m_adbReferenceLevels.resize(m_unBandsCount);
    }
}

bool AFAcousticalParameters::Init()
{
	if((m_nChnlsCount = m_paAudioTracks->GetCount()) == 0)
		return false;

	m_vResults.resize(m_nChnlsCount);
	m_vDecay.resize(m_nChnlsCount);

	SetAnalysisType();

	// ------------- Initialize strength reference levels vector
	RestoreDefaultReferenceLevels();

	return true;
}

void AFAcousticalParameters::Destroy()
{
#ifdef MULTIRATE_FILTERING
   if(m_vOba.size() > 0)
   for(int nCh = 0; nCh < m_nChnlsCount; nCh++)
       delete m_vOba[nCh];
#endif

}

// --- Ctors
AFAcousticalParameters::AFAcousticalParameters()
: m_nChnlsCount(0),
  m_dbRate(48000.0),            // Hz
  m_dbFullScale(120.0),         // dB
  m_dbUserMinLevel(-5.0),       // dB
  m_dbUserMaxLevel(-15.0),      // dB
  m_dbDirectSoundTrig(-20.0),   // dB
  m_dbProbeMicsDistance(0.012), // m
  m_dbSoundSpeed(340.0),        // m/s
  m_bNoiseCorrection(true),
  m_bEDT(false),
  m_bStageMode(false),
  m_bAvgMode(false),
  m_nMode(APM_MONO),
  m_nIaccSpan(IS_ALL),
  m_nAnalysisType(AP_OCTAVE_BANDS),
  m_unBandsCount(N_OCTAVE_BANDS),
  m_dbSoundSourceDistance(10.0), // cm
  m_paAudioTracks(0),
  m_adbReferenceLevels(N_OCTAVE_BANDS)
{}

AFAcousticalParameters::AFAcousticalParameters(TArrayOfAPAudioTracks* paAudioTracks,
                                                            const int analysisType)
: m_nChnlsCount(0),
  m_dbRate(48000.0),            // Hz
  m_dbFullScale(120.0),         // dB
  m_dbUserMinLevel(-5.0),       // dB
  m_dbUserMaxLevel(-15.0),      // dB
  m_dbDirectSoundTrig(-20.0),   // dB
  m_dbProbeMicsDistance(0.012), // m
  m_dbSoundSpeed(340.0),        // m/s
  m_bNoiseCorrection(true),
  m_bEDT(false),
  m_bStageMode(false),
  m_bAvgMode(false),
  m_nMode(APM_MONO),
  m_nIaccSpan(IS_ALL),
  m_nAnalysisType(0),
  m_unBandsCount(0),
  m_dbSoundSourceDistance(10.0), // cm
  m_paAudioTracks(paAudioTracks),
  m_adbReferenceLevels(N_OCTAVE_BANDS),
  m_vOba(),
  m_vDecay(),
  m_vResults()
{
	Init();
}

AFAcousticalParameters::~AFAcousticalParameters()
{
	Destroy();
}

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: c05d7383-e7cd-410e-b7b8-f45f47c9e283
