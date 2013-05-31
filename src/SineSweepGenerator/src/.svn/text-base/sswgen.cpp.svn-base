/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Sine Sweep Signal Generator

  sswgen.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class SineSweepGenerator
\brief The Aurora's generator of logarithmic sine sweep signal

  blabla
*//*******************************************************************/

#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include <string.h>

#include "sswgen.h"

bool SineSweepGenerator::InitBuffers(int nCh)
{
    if(m_smpcBuffersLength == 0) return false;
    
    if(m_aasmpBuffers[nCh] != 0) delete [] m_aasmpBuffers[nCh];
       m_aasmpBuffers[nCh] = new AFSample[m_smpcBuffersLength];

    return true;
}

void SineSweepGenerator::InitDataBuffers()
{
   m_aasmpBuffers = new AFSample*[m_nChnlsCount];

   for(int i=0; i < m_nFilterChnlIdx; ++i)
   {
      m_aasmpBuffers[i] = new AFSample[m_smpcBuffersLength];
      memset(m_aasmpBuffers[i], 0, m_smpcBuffersLength * sizeof(AFSample));
   }
   
   m_aasmpBuffers[m_nFilterChnlIdx] = new AFSample[m_smpcFilterLength];
   memset(m_aasmpBuffers[m_nFilterChnlIdx], 0, m_smpcFilterLength * sizeof(AFSample));
   
   if(m_bControlPulses) 
   {    
      m_aasmpBuffers[m_nPulsesChnlIdx] = new AFSample[m_smpcBuffersLength];
      memset(m_aasmpBuffers[m_nPulsesChnlIdx], 0, m_smpcBuffersLength * sizeof(AFSample));
   }
   
   
}

void SineSweepGenerator::DeleteDataBuffers()
{
   for(int i=0; i<m_nChnlsCount; ++i)
     if(m_aasmpBuffers[i]) delete [] m_aasmpBuffers[i];
     
   if(m_aasmpBuffers) delete [] m_aasmpBuffers;
}


int SineSweepGenerator::ErrorCheck()
{
	if(m_dbLowFrq < 0.0 ||
	   m_dbHighFrq < 0.0 ||
	   m_dbLowFrq >= m_dbHighFrq )
		m_nErrNo = int(ERR_SWEEP_LIMITS);

	if(m_dbSweepDuration <= 0.0)
		m_nErrNo = int(ERR_DURATION);

	if(m_dbAmplitude < 0.0 ||
	   m_dbAmplitude > 1.0)
		m_nErrNo = int(ERR_AMPLITUDE);

	if(m_nChnlsCount <= 0)
		m_nErrNo = int(ERR_CHANNELS_N);

	if(m_dbFadeInDuration < 0.0 ||
	   m_dbFadeInDuration > m_dbSweepDuration)
		m_nErrNo = int(ERR_FADE_IN);

	if(m_dbFadeOutDuration < 0.0 ||
	   m_dbFadeOutDuration > m_dbSweepDuration)
		m_nErrNo = int(ERR_FADE_OUT);

	if(m_dbSilenceDuration < 0.0)
		m_nErrNo = int(ERR_SILENCE);

	if(m_lCycles < 0)
		m_nErrNo = int(ERR_CYCLES_N);

    return m_nErrNo;
}

void  SineSweepGenerator::GetErrorMessage(wxString& wxszMsg)
{
	switch(m_nErrNo)
	{
	    case SineSweepGenerator::ERR_SWEEP_LIMITS:
	    	wxszMsg = wxT("Error in sweep limits.\nCheck start and end frequencies.");
	        break;
	    case SineSweepGenerator::ERR_DURATION:
	    	wxszMsg = wxT("Error in sweep duration: can't be zero or < 0!!");
	        break;
	    case SineSweepGenerator::ERR_AMPLITUDE:
	    	wxszMsg = wxT("Error in sweep amplitude: must be between 0 and 1.");
	        break;
	    case SineSweepGenerator::ERR_CHANNELS_N:
	    	wxszMsg = wxT("Error in channels number: must be at least 1.");
	        break;
	    case SineSweepGenerator::ERR_FADE_IN:
	    	wxszMsg = wxT("Error in fade-in duration: must be shorter than sweep duration and not < 0.");
	        break;
	    case SineSweepGenerator::ERR_FADE_OUT:
	    	wxszMsg = wxT("Error in fade-out duration: must be shorter than sweep duration and not < 0.");
	        break;
	    case SineSweepGenerator::ERR_SILENCE:
	    	wxszMsg = wxT("Error in silence duration: can't be < 0.");
	        break;
	    case SineSweepGenerator::ERR_CYCLES_N:
	    	wxszMsg = wxT("Error in number of cycles: must be positive!");
	        break;
	}

}

bool SineSweepGenerator::Generate()
{
    if(m_dbSweepDuration == 0) return false;
    
     // inizializzazione
    const double dbLL          = m_dbSweepDuration * m_dbRate;
    const AFSampleCount smpcL2 = AFSampleCount(m_dbSweepDuration * m_dbRate + 0.5);
    const AFSampleCount smpcL0 = AFSampleCount(m_dbFadeInDuration * m_dbRate);           // primi  samples di fade-in
    const AFSampleCount smpcL1 = smpcL2 - AFSampleCount(m_dbFadeInDuration * m_dbRate);  // ultimi samples di fade-out
    const AFSampleCount smpcL  = AFSampleCount((m_dbSweepDuration + m_dbSilenceDuration)* m_dbRate + 0.5);

    m_smpcBuffersLength = AFSampleCount(smpcL * m_lCycles * m_nSweepChnlsCount);
    m_smpcFilterLength  = smpcL2;

    InitDataBuffers();
    
    const double dbOmega_1        = 2.0 * M_PI * m_dbLowFrq  / m_dbRate;
    const double dbOmega_2        = 2.0 * M_PI * m_dbHighFrq / m_dbRate;
    const double dbDeltaOmega     = dbOmega_2 - dbOmega_1;
    const double dbDeltaOmegaHalf = (dbOmega_2 - dbOmega_1)/2.0;
    const double dbNOctave        = log(dbOmega_2/dbOmega_1) / log(2.0);
    const double dbN              = dbLL/dbNOctave;
    const double dbOmega          = 2.0 * M_PI *pow(2.0,(-dbNOctave)) * dbN/log(2.0) * m_dbHighFrq/m_dbRate;

    // ciclo principale
    double a, g, x, xx;
    double s = 0, as = 0;
    double ii = 0;
    AFSampleCount i;
    int nCurrentCycle;
    for(nCurrentCycle = 0; nCurrentCycle < m_lCycles; nCurrentCycle++) 
    {
       g = m_dbAmplitude * pow(10.0, (m_dbDeltaL*nCurrentCycle/20.0));
       
      for(i = 0; i < smpcL2; i++)
      {
         ii = double(i);
         a = 1.0; 
         // ----------------------- fade-in
         if(i < smpcL0)
         {
            x = ii/double(smpcL0);
            switch(m_nFadeInType) 
             { 
                case FT_RECT:
                    break;
                case FT_HAMMING:
                    a *= 0.53836 - 0.46164 * cos(M_PI*x);
                    break;
                case FT_HANN:
                    a *= 0.5 * (1 - cos(M_PI*x));
                    break;
                case FT_QUARTER_SINE:
                    a *= sin(x*M_PI/2.0);
                    break;
                case FT_LINEAR:
                    a *= x;
                    break;
                case FT_GAUSSIAN:
                    xx = (x-1.0) * 4.5;
                    a *= exp(-0.5*xx*xx);
                    break;
                case FT_BLACKMANN:
                    a *= 0.42 - 0.5*cos(M_PI*x) + 0.08*cos(2.0*M_PI*x);
                    break;
                case FT_BLACK_HARRIS:
                    a *= 0.3635819 - 0.4891775*cos(M_PI*x) + 0.1365995*cos(2.0*M_PI*x) - 0.0106411*cos(3.0*M_PI*x);
                    break;
                case FT_LOG:
                    a *= log(1 + x*x*(M_E-1.0));
                    break;
            }
         }
        
         // ---------------------------------- fade-out
         if(i > smpcL1)
         {        
            x = (smpcL2-ii) / double(smpcL2-smpcL1);
            switch(m_nFadeOutType) 
             {            
                case FT_RECT:
                    break;
                case FT_HAMMING:
                    a *= 0.53836 - 0.46164*cos(M_PI*x);
                    break;
                case FT_HANN:
                    a *= 0.5*(1-cos(M_PI*x));
                    break;
                case FT_QUARTER_SINE:
                    a *= sin(x*M_PI/2.0);
                    break;
                case FT_LINEAR:
                    a *= x;
                    break;
                case FT_GAUSSIAN:
                    xx = 4.5*(x-1.0);
                    a *= exp(-0.5*xx*xx);
                    break;
                case FT_BLACKMANN:
                    a *= 0.42 - 0.5*cos(M_PI*x) + 0.08*cos(2.0*M_PI*x);
                    break;
                case FT_BLACK_HARRIS:
                    a *= 0.3635819 - 0.4891775*cos(M_PI*x) + 0.1365995*cos(2.0*M_PI*x) - 0.0106411*cos(3.0*M_PI*x);
                    break;
                case FT_LOG:
                    a *= log(1 + x*x*(M_E-1.0));
                break;
            }
         }
         
         // ------------------------------- choice of Sweep
         switch(m_nSweepType) 
          {        
            case ST_LINEAR:
                s  = sin(ii*(dbOmega_1 + dbDeltaOmegaHalf*ii/dbLL));
                as = a*s*g;
                break;
            case ST_LOG: 
                s   = sin(dbOmega * (pow(2.0, ii/dbN)-1.0));
                as  = a*s*g;
                s  *= pow(2.0, (-dbNOctave*(dbLL-ii-1.0)/dbLL));
                break;
            case ST_PINK:
                s  = sin(ii*(dbOmega_1 + dbDeltaOmegaHalf*ii/dbLL));
                as = a*s*g/sqrt((dbOmega_1 + dbDeltaOmega*ii/dbLL)/dbOmega_1);          //decrease amplitude with frequency/time
                s *= sqrt((dbOmega_1 + dbDeltaOmega*ii/dbLL)/dbOmega_1)/sqrt(dbOmega_2/dbOmega_1);  //Increase amplitude with frequency/time
                break;
         }

         // Store evaluated data
         for(int ch = 0; ch < m_nSweepChnlsCount; ch++)
         {                
           // Sweep Multi
            m_aasmpBuffers[ch][i + smpcL*nCurrentCycle + smpcL*m_lCycles*ch] = AFSample(as);
         }
        
         // filtro inverso 
         m_aasmpBuffers[m_nFilterChnlIdx][smpcL2-1-i] = AFSample(s);

      } // --------------------------- next i

      // ------------ generazione burst per avanzamento tavola rotante
      if(m_bControlPulses) 
      {       
         int Iniz = smpcL2 + (smpcL-smpcL2)/5;               // Posizionatore ad 1/5 del silenzio
         int ms7  = (int)ceil(0.007 * m_dbRate);    // n. campioni che corrisponde a 7 ms
         int Fin  = Iniz + ms7;                  // Durata burst = 7 ms

          if( (Fin > smpcL) || ((smpcL-smpcL2) < ms7) )
          {
             // Praticamente non c'? silenzio, metto il burst negli ultimi 7 ms del segnale
              Iniz = smpcL-ms7;
              Fin = smpcL;
          }
          for(i=Iniz; i<Fin; i++)   //burst 
          {
              m_aasmpBuffers[m_nPulsesChnlIdx][i + smpcL*nCurrentCycle] = 1.0; // segnale TTL tutto al FS superiore
          }
      }
      
   } // ---------------- next cycle
   
   return true;
}

void SineSweepGenerator::FillBlock(AFSample* psmpData, AFSampleCount smpcLen, AFSampleCount smpcWritten, int nTrack)
{
   
   memcpy(psmpData, m_aasmpBuffers[nTrack] + smpcWritten, smpcLen * sizeof(AFSample));
}

void SineSweepGenerator::SetControlPulses(bool bValue)
{ 
   if(m_bControlPulses) 
   {
     // m_bControlPulses is 'true': effect only if value is 'false'
     if(!bValue) 
     {
        m_nPulsesChnlIdx = -1;
        m_nChnlsCount--;
     }
   } 
   else 
   {    
      // m_bControlPulses is 'false': effect only if value is 'true'
      if(bValue) 
      {
        m_nPulsesChnlIdx = m_nFilterChnlIdx + 1;
        m_nChnlsCount++;
     } 
   }
   m_bControlPulses = bValue;
}

void SineSweepGenerator::SetSweepChnlsNumber(int nValue)   
{ 
   m_nSweepChnlsCount = nValue;
   m_nFilterChnlIdx = m_nSweepChnlsCount;
   if(m_bControlPulses) 
   {
       m_nPulsesChnlIdx = m_nFilterChnlIdx + 1;
       m_nChnlsCount    = m_nPulsesChnlIdx + 1;
   }
   else
   {
       m_nChnlsCount = m_nFilterChnlIdx + 1;
   }
}

void SineSweepGenerator::SetBuffersLength(AFSampleCount smpcLen, const bool bInitBuffers,  int nCh)
{
    m_smpcBuffersLength = smpcLen;
    // TODO....
}


// --- ctors
SineSweepGenerator::SineSweepGenerator()
  : m_nErrNo(ERR_OK),
    m_dbRate(48000),           // Hz
    m_dbHighFrq(22000.0),      // Hz
    m_dbLowFrq(22.0),          // Hz
    m_dbSweepDuration(10.0),   // s
    m_dbAmplitude(1.0),        // 
    m_dbSilenceDuration(8.0),  // s
    m_lCycles(1),
    m_dbFadeInDuration(0.1),   // s 
    m_dbFadeOutDuration(0.1),  // s 
    m_nFadeInType(FT_HANN),
    m_nFadeOutType(FT_HANN),
    m_dbDeltaL(0.0),
    m_nChnlsCount(2),          // Sweep Mono + Inverse filter
    m_nSweepChnlsCount(1),     // default mono
    m_nFilterChnlIdx(1),     // sweep on channel 0, filter on channel 1
    m_nPulsesChnlIdx(-1),    // by default no control pulses
    m_smpcBuffersLength(0),     // samples
    m_smpcSweepLength(0),       // samples
    m_smpcFilterLength(0),      // samples
    m_nSweepType(ST_LOG),
    m_bControlPulses(false)
    
{}
 

SineSweepGenerator::~SineSweepGenerator()
{
   DeleteDataBuffers();
}
