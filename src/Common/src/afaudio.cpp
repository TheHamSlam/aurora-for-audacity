/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  afaudio.h

  Angelo Farina - Simone Campanini

***********************************************************************/

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "afaudio.h"

bool AFAudioTrackBase::Init(const int nCh)
{
    if(m_smpcLen == 0) return false;

    m_apsmpTrack[nCh] = new AFSample[m_smpcLen];
   
    return true;
}

void AFAudioTrackBase::Destroy(const int nCh)
{
   if(m_apsmpTrack[nCh]) 
       delete [] m_apsmpTrack[nCh];
}

void AFAudioTrackBase::Copy(AFSample *src, AFSample *dest, AFSampleCount len, double gain)
{ for(AFSampleCount i=0; i < len; i++) dest[i] = AFSample(gain * src[i]); }

//---------------------------- Utils------------------------------


double AFAudioTrackBase::FindMax(const int nCh)
{
    // TODO: This is absolute max...the name should be changed
    double max = 0.0;
    for(AFSampleCount i = 0; i < m_smpcLen; i++) 
        max = (fabs(m_apsmpTrack[nCh][i]) > max) ? fabs(m_apsmpTrack[nCh][i]) : max;    
    return (m_pdbMax[nCh] = max);
}

double AFAudioTrackBase::FindMin(const int nCh)
{
    // TODO: This is not absolute min...a coherence work must be done
    double min = 0.0;
    for(AFSampleCount i = 0; i < m_smpcLen; i++) 
        min = (m_apsmpTrack[nCh][i] < min) ? m_apsmpTrack[nCh][i] : min;
    return (m_pdbMin[nCh] = min);
}

bool AFAudioTrackBase::FindFirstArrivalTime(const double dbThreshold, const int nCh)
{
    if(m_pdbMax[nCh] == 0.0) FindMax(nCh);
    
    double dbRelativeThreshold = dbThreshold * m_pdbMax[nCh];
    
    m_psmpcFAT[nCh] = 0;
    while( (m_psmpcFAT[nCh] < m_smpcLen) && 
           (fabs(m_apsmpTrack[nCh][m_psmpcFAT[nCh]++]) < dbRelativeThreshold) );
    
    if(m_psmpcFAT[nCh] == m_smpcLen) return false;
    return true;
}

void AFAudioTrackBase::Dump(const int idx)
{
    char fn[32];
    if(idx < 0)
    {
    	sprintf(fn, "ap_track");
    }
    else
    {
    	sprintf(fn, "ap_track_%d", idx);

    }

    FILE* f = fopen(fn, "w");
    if(f == 0)
        return;

    for(AFSampleCount i = 0; i < m_smpcLen; i++)
    {
    	fprintf(f, "%.18e\n", m_apsmpTrack[0][i]);
    }

    fclose(f);
}



double AFAudioTrackBase::RMS(const int nCh)
{
    double dbRMS = 0;
    for(AFSampleCount i = 0; i < m_smpcLen; i++)
        dbRMS += double(m_apsmpTrack[nCh][i] * m_apsmpTrack[nCh][i]);

    return dbRMS/double(m_smpcLen);
}

void AFAudioTrackBase::SetTrack(int nCh, AFSample *psmpSrc, bool bInitTrack)
{
    if(m_smpcLen > 0)
    {
        if(bInitTrack) Init(nCh);

        memcpy(m_apsmpTrack[nCh], psmpSrc, m_smpcLen * sizeof(AFSample));
    }
}


void AFAudioTrackBase::SetTrack(const int nCh, AFSample *psmpSrc, const AFSampleCount smpcLen, const bool bInitTrack)
{
    SetTrackLength(smpcLen, bInitTrack, nCh);

    memcpy(m_apsmpTrack[nCh], psmpSrc, m_smpcLen * sizeof(AFSample));
}

void AFAudioTrackBase::SetTrack(const int nCh, double *pdbSrc, bool const bInitTrack)
{
    if(m_smpcLen > 0)
    {
        if(bInitTrack) Init(nCh);

        for(AFSampleCount i = 0; i < m_smpcLen; i++)
            m_apsmpTrack[nCh][i] = pdbSrc[i];
    }
}


void AFAudioTrackBase::SetTrack(const int nCh, double* pdbSrc, const AFSampleCount smpcLen, const bool bInitTrack)
{
    SetTrackLength(smpcLen, bInitTrack, nCh);

    for(AFSampleCount i = 0; i < m_smpcLen; i++)
        m_apsmpTrack[nCh][i] = pdbSrc[i];
}

void AFAudioTrackBase::SetTrackLength(const AFSampleCount smpcLen, const bool bInitTrack, int nCh)
{
    m_smpcLen = smpcLen;
    if(bInitTrack) Init(nCh);
}


AFAudioTrackBase::AFAudioTrackBase(const double dbRate, const int nChannels)
  : m_nMode(AFM_MONO),
    m_dbRate(dbRate),
    m_nChannels(nChannels),
    m_dbFullScale(120.0),  // dB
    m_smpcLen(0)
{
#ifdef __AUDEBUG__
   printf("afaudio: istantiated for %d tracks\n", m_nChannels); fflush(stdout);
#endif
   m_apsmpTrack = new AFSample* [m_nChannels];
   m_pdbMin     = new double    [m_nChannels];
   m_pdbMax     = new double    [m_nChannels];
   m_psmpcFAT   = new AFSampleCount [m_nChannels];
   
   for(int nCh = 0; nCh < m_nChannels; nCh++)
   {
       m_apsmpTrack[nCh] = 0;
       m_pdbMin    [nCh] = 0;
       m_pdbMax    [nCh] = 0;
       m_psmpcFAT  [nCh] = 0;
   }
   
   switch(m_nChannels) {
       case 2: m_nMode = AFM_STEREO; break;
       case 4: m_nMode = AFM_TETRA;  break;
   }
}

AFAudioTrackBase::~AFAudioTrackBase()
{
    for(int nCh = 0; nCh < m_nChannels; nCh++)
        Destroy(nCh);
   
    delete [] m_apsmpTrack;
    delete [] m_pdbMin;
    delete [] m_pdbMax;
    delete [] m_psmpcFAT;
}


//----------------------------------------------------------------------------
// AFAudioTrack implementation
//----------------------------------------------------------------------------

bool AFAudioTrack::Init(const int nCh)
{
    if(m_smpcLen == 0) return false;

    Destroy(nCh);

    m_apsmpTrack[nCh]         = new AFSample[m_smpcLen];
    m_apsmpFilteredTrack[nCh] = new AFSample[m_smpcLen];

    return true;
}

void AFAudioTrack::Destroy(const int nCh)
{
   if(m_apsmpTrack[nCh])
       delete [] m_apsmpTrack[nCh];

   if(m_apsmpFilteredTrack[nCh])
       delete [] m_apsmpFilteredTrack[nCh];
}

void AFAudioTrack::ResetFilteredTrack(const int nCh, const double dbGain)
{
    Copy(m_apsmpTrack[nCh], m_apsmpFilteredTrack[nCh], m_smpcLen, dbGain);
    m_smpcFilteredTrackLength = m_smpcLen;
    m_dbFilteredTrackRate     = m_dbRate;
}

void AFAudioTrack::ReplaceTrackWithFiltered(const int nCh, const double dbGain)
{
    Copy(m_apsmpFilteredTrack[nCh], m_apsmpTrack[nCh], m_smpcLen, dbGain);
    //Copy(m_apsmpFilteredTrack[nCh], m_apsmpTrack[nCh], m_smpcFilteredTrackLength, m_dbGain);
    m_smpcLen = m_smpcFilteredTrackLength;
    m_dbRate  = m_dbFilteredTrackRate;
}

void AFAudioTrack::IIR(const int nCh,
                       const double dbAlpha, const double dbBeta, const double dbGamma,
                       const double dbMu, const double dbSigma)
{
   // code by Angelo Farina
   AFSampleCount n = 0;
   double x_n;
   double x_nm1 = 0.0;
   double x_nm2 = 0.0;
   double y_nm1 = 0.0;
   double y_nm2 = 0.0;

   x_n = m_apsmpFilteredTrack[nCh][n];
   // x_(n) = 2 * (Alfa * (x_n + Mu * x_nm1 + dbSigma * x_nm2) + dbGamma * y_nm1 - dbBeta * y_nm2) - Basic
   m_apsmpFilteredTrack[nCh][n] = AFSample( 2.0 * (dbAlpha * (x_n + dbMu*x_nm1 + dbSigma*x_nm2) + dbGamma*y_nm1 - dbBeta*y_nm2) );
   x_nm2 = x_nm1;
   x_nm1 = x_n;

   n = 1;
   x_n = m_apsmpFilteredTrack[nCh][n];
   y_nm1=m_apsmpFilteredTrack[nCh][n-1];
   m_apsmpFilteredTrack[nCh][n] = AFSample( 2.0 * (dbAlpha * (x_n + dbMu*x_nm1 + dbSigma*x_nm2) + dbGamma*y_nm1 - dbBeta*y_nm2) );
   x_nm2 = x_nm1;
   x_nm1 = x_n;

   for(n = 2;n < m_smpcFilteredTrackLength; n++)
   {
      x_n   = m_apsmpFilteredTrack[nCh][n];
      y_nm1 = m_apsmpFilteredTrack[nCh][n-1];
      y_nm2 = m_apsmpFilteredTrack[nCh][n-2];
      // WARNING: feedback components should have minus sign: -> -dbGamma*y_nm1 ???
      m_apsmpFilteredTrack[nCh][n] = AFSample( 2.0 * (dbAlpha * (x_n + dbMu*x_nm1 + dbSigma*x_nm2) + dbGamma*y_nm1 - dbBeta*y_nm2) );
      x_nm2 = x_nm1;
      x_nm1 = x_n;
   }
}


void AFAudioTrack::Gain(const int nCh, const double G)
{
   // G [dB] -> g
   double g = pow(10.0, G/20.0);
   for(AFSampleCount k=1; k < m_smpcFilteredTrackLength; k++)
	   m_apsmpFilteredTrack[nCh][k] *= g;
}

void AFAudioTrack::Filter(const int nType, const int nCh, const double dbF0, const double dbFq)
{
   // code by Angelo Farina

   // Two poles IIR filter
   double dbAlpha = 0.0;
   double dbMu    = 0.0;
   double dbSigma = 0.0;
      
   double dbTheta0 = 2.0 * M_PI * dbF0 / m_dbFilteredTrackRate;
   double dbD      = 2.0 * tan(dbTheta0 / 2.0 / dbFq) / sin(dbTheta0);
   double dbBeta   = 0.5 * (1.0 - 0.5*dbD*sin(dbTheta0)) / (1.0 + 0.5*dbD*sin(dbTheta0));
   double dbGamma  = (0.5 + dbBeta) * cos(dbTheta0);

   switch(nType)
   {
   case BPF:
      dbMu    = 0.0;
      dbAlpha = (0.5 - dbBeta) / 2.0;
      dbSigma = -1.0;
      break;
   case LPF:
      dbMu    = 2.0;
      dbAlpha = (0.5 + dbBeta - dbGamma) / 4.0;
      dbSigma = 1.0;
      break;
   case HPF:
      dbMu    = -2.0;
      dbAlpha = (0.5 + dbBeta + dbGamma) / 4.0;
      dbSigma = 1.0;
      break;
   case NotchF: 
      dbMu    = -2.0 * cos(dbTheta0);
      dbAlpha = (0.5 + dbBeta) / 2.0;
      dbSigma = 1.0;
      break;
   } 

   IIR(nCh, dbAlpha, dbBeta, dbGamma, dbMu, dbSigma);
}


void AFAudioTrack::AFilter(const int nCh)
{
   // code by Angelo Farina
   // IIR two-poles filter
 
   //  filter 1 - high pass 20.6 Hz
   double c_1 =  1.0 - exp(-2.0 * M_PI * (20.6) / m_dbFilteredTrackRate);
   double c_1m = 1.0 - c_1;
   //  filter 2 - high pass 20.6 Hz
   double c_2 =  1.0 - exp(-2.0 * M_PI * (20.6) / m_dbFilteredTrackRate);
   double c_2m = 1.0 - c_2;
   //  filter 3 - high pass 107.7 Hz
   double c_3 =  1.0 - exp(-2.0 * M_PI * (107.7) / m_dbFilteredTrackRate);
   double c_3m = 1.0 - c_3;
   //  filter 4 - high pass 737.9 Hz
   double c_4 =  1.0 - exp(-2.0 * M_PI * (737.9) / m_dbFilteredTrackRate);
   double c_4m = 1.0 - c_4;
   //  filter 5 - low pass 12200 Hz
   double c_5 =  1.0 - exp(-2.0 * M_PI * (12200.0) / m_dbFilteredTrackRate);
   double c_5m = 1.0 - c_5;
   //  filter 6 - low pass 12200 Hz
   double c_6 =  1.0 - exp(-2.0 * M_PI * (12200.0) / m_dbFilteredTrackRate);
   double c_6m = 1.0 - c_6;

   // the following are delays
   double delta_1 = 0.0;
   double delta_2 = 0.0;
   double delta_3 = 0.0;
   double delta_4 = 0.0;

   double A,B,C,D,E,F;

   AFSampleCount k = 0;
   // The first sample is elaborated separately.
   //   first 4 high pass filters 
   A = m_apsmpFilteredTrack[nCh][k] - delta_1;
   delta_1 = m_apsmpFilteredTrack[nCh][k] * c_1 + delta_1 * c_1m;
   B = A - delta_2;
   delta_2 = A * c_2 + delta_2 * c_2m;
   C = B - delta_3;
   delta_3 = B * c_3 + delta_3 * c_3m;
   D = C - delta_4;
   delta_4 = C * c_4 + delta_4 * c_4m;
   
   E=D;
   F=D;
   //   2 last low pass filters
   E = D * c_5 + E * c_5m;
   F = E * c_6 + F * c_6m;
   m_apsmpFilteredTrack[nCh][k] = AFSample(F/0.858);
   
   for(k = 1;k < m_smpcFilteredTrackLength; k++)
   {
      //    first 4 high pass filters
      A = m_apsmpFilteredTrack[nCh][k] - delta_1;
      delta_1 = m_apsmpFilteredTrack[nCh][k] * c_1 + delta_1 * c_1m;
      B = A - delta_2;
      delta_2 = A * c_2 + delta_2 * c_2m;
      C = B - delta_3;
      delta_3 = B * c_3 + delta_3 * c_3m;
      D = C - delta_4;
      delta_4 = C * c_4 + delta_4 * c_4m;
      
      //    2 last low pass filters
      E = D * c_5 + E * c_5m;
      F = E * c_6 + F * c_6m;
      m_apsmpFilteredTrack[nCh][k] = AFSample(F/0.858); // correction to make 1kHz gain  0 dB
   }
}

void AFAudioTrack::LFilter(const int nCh)
{
   // code by Angelo Farina
 
   double dbF0,dbFq;

   //  filter 1 - high pass 10 Hz
   dbF0 = 10.0f; // Hz
   dbFq = 0.707f;
   Filter(HPF, nCh, dbF0, dbFq);
   //  filter 2 - high pass 14 Hz
   dbF0 = 14.0f; // Hz
   dbFq = 0.707f;
   Filter(HPF, nCh, dbF0, dbFq);
   //  filter 3 - high pass  20 Hz
   dbF0 = 20.0f; // Hz
   dbFq = 0.707f;
   Filter(HPF, nCh, dbF0, dbFq);
   /*
   //  filter 4 - low pass 20 kHz
   dbF0 = 20000.0f; // Hz
   dbFq = 0.707f;
   Filter(LPF, nCh, dbF0, dbFq);
   //  filter 5 - low pass 20.4 kHz
   dbF0 = 20400.0f; // Hz
   dbFq = 0.707f;
   Filter(LPF, nCh, dbF0, dbFq);
   //  filter 6 - low pass 20.9 kHz
   dbF0 = 20900.0f; // Hz
   dbFq = 0.707f;
   Filter(LPF, nCh, dbF0, dbFq);
   */
}

void AFAudioTrack::ISO_8041_Filter(const int nCh)
{
   // Ponderazione Accelerazione Asse Generico secondo norma ISO-8041
   //void AccFilter(float  *X,float fSamp,long IRL)
    
// filtro 1 - passa alto 0.7943 Hz
   const double c_1 =  1.0 - exp(-2.0 * M_PI * (0.7943) / m_dbFilteredTrackRate);
   const double c_1m = 1.0 - c_1;
// filtro 2 - passa alto 0.7943 Hz
   const double c_2 =  1.0 - exp(-2.0 * M_PI * (0.7943) / m_dbFilteredTrackRate);
   const double c_2m = 1.0 - c_2;
// filtro 3 - passa basso 5.684 Hz
   const double c_3 =  1.0 - exp(-2.0 * M_PI * (5.684) / m_dbFilteredTrackRate);
   const double c_3m = 1.0 - c_3;
// filtro 4 - passa basso 100 Hz
   const double c_4 =  1.0 - exp(-2.0 * M_PI * (100.0) / m_dbFilteredTrackRate);
   const double c_4m = 1.0 - c_4;
// filtro 5 - passa basso 100 Hz
   const double c_5 =  1.0 - exp(-2.0 * M_PI * (100.0) / m_dbFilteredTrackRate);
   const double c_5m = 1.0 - c_5;

   AFSampleCount k;
   double delta_1 = 0.0;
   double delta_2 = 0.0;
   double A,B,C=0.0, D=0.0, E=0.0;

   for(k = 0; k < m_smpcFilteredTrackLength; k++) {
        
//      primi 2 filtri passa alto in cascata
      A = m_apsmpFilteredTrack[nCh][k] - delta_1;
      delta_1 = m_apsmpFilteredTrack[nCh][k] * c_1 + delta_1 * c_1m;
      B = A - delta_2;
      delta_2 = A * c_2 + delta_2 * c_2m;

//      3 filtri passa basso conclusivi
      C = B * c_3 + C * c_3m;
      D = C * c_4 + D * c_4m;
      E = D * c_5 + E * c_5m;
      m_apsmpFilteredTrack[nCh][k] = AFSample(E*1.19); // correzione per rendere il guadagno ad 1 Hz = 0 dB
   }
}

void AFAudioTrack::ITU_P56_Filter(const int nCh)
{
   // code by Angelo Farina
   // Filtro passa-banda secondo ITU-P56 (160-5500 Hz)
   double dbF0,dbFq;
   
//  filtro 1 - passa alto 110 Hz
   dbF0=110.0; // Hz
   dbFq=0.7;   // Butterworth
   Filter(HPF, nCh, dbF0, dbFq);
//  filtro 2 - passa alto 90 Hz
   dbF0=90.0;  // Hz
   dbFq=1.5;
   Filter(HPF, nCh, dbF0, dbFq);
//  filtro 3 - passa basso 6500 Hz
   dbF0=6500.0; // Hz
   dbFq=0.8;
   Filter(LPF, nCh, dbF0, dbFq);
//  filtro 4 - passa basso 7500 Hz
   dbF0=7500.0; // Hz
   dbFq=1.8;     //era 1.9
   Filter(LPF, nCh, dbF0, dbFq);
//  filtro 5 - passa banda 1100 Hz
   dbF0=1100.0; // Hz
   dbFq=0.11;
   Filter(BPF, nCh, dbF0, dbFq);

// Correzione guadagno -0.11 dB
   Gain(nCh, -0.15);

}

void AFAudioTrack::UNI_9916_Filter(const int nCh)
{
   // Filtro passa basso a 250 Hz - UNI 9916
   double dbF0,dbFq;
   
//  filtro 1 - passa basso 250 Hz
   dbF0=320.0; // Hz
   dbFq=1.0;   // Butterworth
   Filter(LPF, nCh, dbF0, dbFq);
//  filtro 2 - passa basso 260 Hz
   dbF0=360.0;  // Hz
   dbFq=0.6;
   Filter(LPF, nCh, dbF0, dbFq);
//  filtro 3 - passa basso 270 Hz
   dbF0=400.0; // Hz
   dbFq=1.1;
   Filter(LPF, nCh, dbF0, dbFq);
//  filtro 4 - passa basso 280 Hz
   dbF0=500.0; // Hz
   dbFq=0.5;     //era 1.9
   Filter(LPF, nCh, dbF0, dbFq);

// Correzione guadagno 0.0 dB
   Gain(nCh, 0.0);

}

void AFAudioTrack::OctaveFilter(const int nCh, const double dbFc)
{   
   // code by Angelo Farina

   double dbF0, dbFq;
   // Band filtering with six-poles IIR filter
   // first filter (2 poles)
   dbF0 = 0.755f * dbFc;
   dbFq = 6.0f;
   Filter(BPF, nCh, dbF0, dbFq);
   // second filter (2 poles)
   dbF0 = dbFc;
   dbFq = 3.0f;
   Filter(BPF, nCh, dbF0, dbFq);
   // third filter (2 poles)
   dbF0 = 1.33f * dbFc;
   dbFq = 6.0f;
   Filter(BPF, nCh, dbF0, dbFq);
}


void AFAudioTrack::RemoveMean(const int nCh)
{
   // code by Angelo Farina

   double dbMean = 0.0;
   AFSampleCount i;

   for(i = 0; i < m_smpcLen; i++)
      dbMean += m_apsmpFilteredTrack[nCh][i];

   dbMean /= double(m_smpcLen);

   for(i = 0; i < m_smpcFilteredTrackLength; i++)
      m_apsmpFilteredTrack[nCh][i] -= AFSample(dbMean);

}

void  AFAudioTrack::NoiseCorrection(const int nCh)
{
   double dbFactor = 0.0;
   double dbSample = 0.0;
   
   // Now will calculate the mean of the IR's last 16th energy
   for(AFSampleCount i = (m_smpcFilteredTrackLength - (AFSampleCount)(m_smpcFilteredTrackLength/16));
       i < m_smpcFilteredTrackLength; i++)
   {

         dbSample  = m_apsmpFilteredTrack[nCh][i];
         dbSample *= dbSample;
         dbFactor += dbSample; 
   }

   m_dbNoiseCorrFactor = dbFactor / double(m_smpcFilteredTrackLength/16); // Square of the noise RMS value
}

double AFAudioTrack::RMS(const int nCh)
{
    double dbRMS = 0;
    for(AFSampleCount i = 0; i < m_smpcFilteredTrackLength; i++)
        dbRMS += double(m_apsmpFilteredTrack[nCh][i] * m_apsmpFilteredTrack[nCh][i]);

    return dbRMS/double(m_smpcFilteredTrackLength);
}

void AFAudioTrack::SetTrack(int nCh, AFSample *psmpSrc, bool bInitTrack)
{
    if(m_smpcLen > 0)
    {
        if(bInitTrack) Init(nCh);
        m_smpcFilteredTrackLength = m_smpcLen;

        memcpy(m_apsmpTrack[nCh], psmpSrc, m_smpcLen * sizeof(AFSample));
        ResetFilteredTrack(nCh);
//        FindMin(nCh);    FindMax(nCh);
    }
}


void AFAudioTrack::SetTrack(const int nCh, AFSample *psmpSrc, const AFSampleCount smpcLen, const bool bInitTrack)
{
    SetTrackLength(smpcLen, bInitTrack, nCh);
    m_smpcFilteredTrackLength = smpcLen;

    memcpy(m_apsmpTrack[nCh], psmpSrc, m_smpcLen * sizeof(AFSample));
    ResetFilteredTrack(nCh);
//    FindMin(nCh); FindMax(nCh);
}

void AFAudioTrack::SetTrack(const int nCh, double *pdbSrc, bool const bInitTrack)
{
    if(m_smpcLen > 0)
    {
        if(bInitTrack) Init(nCh);
        m_smpcFilteredTrackLength = m_smpcLen;

        for(AFSampleCount i = 0; i < m_smpcLen; i++)
            m_apsmpTrack[nCh][i] = pdbSrc[i];

        ResetFilteredTrack(nCh);
//        FindMin(nCh);  FindMax(nCh);
    }
}


void AFAudioTrack::SetTrack(const int nCh, double* pdbSrc, const AFSampleCount smpcLen, const bool bInitTrack)
{
    SetTrackLength(smpcLen, bInitTrack, nCh);
    m_smpcFilteredTrackLength = smpcLen;

    for(AFSampleCount i = 0; i < m_smpcLen; i++)
        m_apsmpTrack[nCh][i] = pdbSrc[i];

    ResetFilteredTrack(nCh);
//    FindMin(nCh);  FindMax(nCh);
}

AFAudioTrack::AFAudioTrack(const double dbRate, const int nChannels)
  : AFAudioTrackBase(dbRate, nChannels),
    m_apsmpFilteredTrack(0),
    m_dbNoiseCorrFactor(0),
    m_nSelectedFilter(0),
    m_smpcFilteredTrackLength(0),
    m_dbFilteredTrackRate(dbRate)
{
#ifdef __AUDEBUG__
   printf("afaudiotrack: istantiated for %d tracks\n", m_nChannels); fflush(stdout);
#endif
   m_apsmpFilteredTrack = new AFSample* [m_nChannels];

   for(int nCh = 0; nCh < m_nChannels; nCh++)
       m_apsmpFilteredTrack[nCh] = 0;
}

AFAudioTrack::~AFAudioTrack()
{
    delete [] m_apsmpFilteredTrack;
}
