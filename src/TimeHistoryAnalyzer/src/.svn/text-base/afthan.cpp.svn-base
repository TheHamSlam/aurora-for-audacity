/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  afthan.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AFTimeHistoryAnalyzer
\brief The Aurora's powerful analyzer of time history data

  blabla
*//*******************************************************************/

#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include "afthan.h"

//----------------------------------------------------------------------------
// AFTimeHistoryAnalyzer::TResults implementation
//----------------------------------------------------------------------------
void AFTimeHistoryAnalyzer::TResults::SetBuffersLength(size_t unBuffersLength)
{
    m_unBuffersLength = unBuffersLength;
    Init();
}

void AFTimeHistoryAnalyzer::TResults::Init()
{
    if(m_unBuffersLength == 0) return;
    Destroy();
    for(int n = 0; n < N_TIME_CONST; n++)
        m_aadbBuffers[n] = new double [m_unBuffersLength];
}

void AFTimeHistoryAnalyzer::TResults::Destroy()
{
    for(int n = 0; n < N_TIME_CONST; n++)
        if(m_aadbBuffers[n])
        {
	         delete [] m_aadbBuffers[n];
            m_aadbBuffers[n] = 0;
        }
}

AFTimeHistoryAnalyzer::TResults::TResults(size_t unBuffersLength)
{
	 for(int n = 0; n < N_TIME_CONST; n++)
        m_aadbBuffers[n] = 0;

    SetBuffersLength(unBuffersLength);
}

AFTimeHistoryAnalyzer::TResults::~TResults()
{ Destroy(); }


//----------------------------------------------------------------------------
// AFTimeHistoryAnalyzer implementation
//----------------------------------------------------------------------------
double AFTimeHistoryAnalyzer::Average(const int nParam)
{
   double dbSum = 0.0;
   for(int nCh = 0; nCh < m_nChnlsCount; nCh++)
      dbSum += m_aResults[nCh].GetParameter(nParam);

   return dbSum / double(m_nChnlsCount);
}

double AFTimeHistoryAnalyzer::dBAverage(const int nParam)
{
   double dbSum = 0.0;
   for(int nCh = 0; nCh < m_nChnlsCount; nCh++)
      dbSum += undB(m_aResults[nCh].GetParameter(nParam));

   return dB(dbSum/double(m_nChnlsCount));
}

void  AFTimeHistoryAnalyzer::FillAvgParameters()
{
    if(m_nChnlsCount > 1)
    {
    	double* adbAvgParameters = m_aResults[m_nChnlsCount].m_adbParameters;
    	double  dbTotalDuration  = m_aResults[0].m_adbParameters[THA_TDU];

        // AVG data is in the last place of m_aadbParameters vector
        adbAvgParameters[THA_AVG] = dBAverage(THA_AVG);
        adbAvgParameters[THA_SEL] = dBAverage(THA_AVG) + dB(dbTotalDuration);
        adbAvgParameters[THA_TDU] = dbTotalDuration;
        adbAvgParameters[THA_ASL] = dBAverage(THA_ASL);
        adbAvgParameters[THA_THS] = Average  (THA_THS);
        adbAvgParameters[THA_ACT] = Average  (THA_ACT);
        adbAvgParameters[THA_MPK] = dBAverage(THA_MPK);
        adbAvgParameters[THA_MIM] = dBAverage(THA_MIM);
        adbAvgParameters[THA_MFS] = dBAverage(THA_MFS);
        adbAvgParameters[THA_MSL] = dBAverage(THA_MSL);
        adbAvgParameters[THA_DUR] = Average  (THA_DUR);

        for(int nCh = 0; nCh < m_nChnlsCount; nCh++)
        {
            if(m_aResults[nCh].GetParameter(THA_IMP) > 0)
               adbAvgParameters[THA_IMP] =  1.0;
        }
    }
}

bool AFTimeHistoryAnalyzer::Analyze()
{
    if(!m_paSignalTracks)
    	return false;

    if(m_paSignalTracks->GetCount() == 0)
    	return false;

#ifdef __ITUP56_SINGLE_FRAME__
   InitProgressMeter();
#endif

    for(int nCh = 0; nCh < m_nChnlsCount; nCh++)
    {
        if(!AnalyzeTrack(nCh))
        {
#ifdef __ITUP56_SINGLE_FRAME__
            DestroyProgressMeter();
#endif
    	    return false;
        }
    }
    FillAvgParameters();

#ifdef __ITUP56_SINGLE_FRAME__
   DestroyProgressMeter();
#endif

    return true;
}

bool AFTimeHistoryAnalyzer::AnalyzeTrack(const int nCh)
{
   // Code by A.Farina
   
   // ********************* If requested, remove DC component ********************
   if(m_bRemoveDC)
	   m_paSignalTracks->Item(nCh).RemoveMean();
   
   // *************************** Apply selected filter ***************************
   m_paSignalTracks->Item(nCh).Filter();

   double dbRate = m_paSignalTracks->Item(nCh).GetSamplerate();

   AFSampleCount smpcTrackLength = m_paSignalTracks->Item(nCh).GetTrackLength(),
                 smpcStepLength  = AFSampleCount(dbRate/1000.0),                 // N. di campioni che fanno circa 1ms
                 smpcStepsCount  = smpcTrackLength/smpcStepLength;               // Numero di step

   if((smpcStepsCount*smpcStepLength) > smpcTrackLength)
	   smpcStepsCount -= 1;  // It prevents overflow
       
   const double dbStepDuration = smpcStepLength/dbRate;  // Lunghezza esatta di uno step, in s

   TITUFactors ituA( exp(-1.0/(0.03 * dbRate)),                            // Ag (cost. tempo ITU P56  dTau = 30 ms)
                     exp(-dbStepDuration/2.0/0.125) *dbStepDuration/0.125, // Fattore A per Fast = 0.125 s
                     exp(-dbStepDuration/2.0/1.0)   *dbStepDuration/1.0,   // Fattore A per Slow = 1 s
                     exp(-dbStepDuration/2.0/0.035) *dbStepDuration/0.035, // Fattore A per Impulse crescente
                     exp(-dbStepDuration/2.0/1.5)   *dbStepDuration/1.5 ); // Fattore A per Impulse decrescente

   TITUFactors ituB( 1.0 - ituA.m_dbG,
                     1.0 - ituA.m_dbFast,
                     1.0 - ituA.m_dbSlow,
                     1.0 - ituA.m_dbImpRaising,
                     1.0 - ituA.m_dbImpFalling );
   TITULevels ituL;

   long   iFast=0;
   
   AFSampleCount j;
   
   // preparazione vettori per ITU P56
   double adbLevelThresholds         [30]; //soglie di livello
   size_t aunSamplesOverThreshold    [30], //numero di campioni oltre la soglia
          aunLastSampleOverThreshold [30]; //memoria dall'ultimo campione sopra soglia
   
   const size_t unHangoverLength = unRound(0.2 / dbStepDuration); //hangover time in samples, rounded (H = 0.2)

   adbLevelThresholds        [0] = 1.0/M_SQRT2;
   aunSamplesOverThreshold   [0] = 0;
   aunLastSampleOverThreshold[0] = unHangoverLength;
   
   for(j = 1; j < 30; j++)    //scendo a passi di circa 3 dB
   {    
      adbLevelThresholds        [j] = adbLevelThresholds[j-1]/M_SQRT2;
      aunSamplesOverThreshold   [j] = 0;
      aunLastSampleOverThreshold[j] = unHangoverLength;
   }

   // ******************************** Parte 1 ********************************
   
   // inizializzo a zero il progress meter
#if defined __ITUP56_SINGLE_FRAME__ || !defined __WXGTK__
   SetProgressMeterMessage(wxString::Format(wxT("Analyzing channel %d Time History..."), nCh+1));
#endif
   
   AFSample* pTrack = m_paSignalTracks->Item(nCh).GetFilteredTrack();

   AFSampleCount smpcStep = 0, un = 0;
   double dbRmsOn1ms = 0.0, dbLocalMax = 0.0,
          dbMax      = 0.0,
          dbSample   = 0.0, dbSqrSample = 0.0,
          dbLeq      = 0.0,
          dbTotalSum = 0.0;

   double dbPi=0.0, dbEnvp=0.0;

   double** aadbBuffers = m_aResults[nCh].m_aadbBuffers; // Just for better readability...

   for(smpcStep=0; smpcStep < smpcStepsCount; smpcStep++)       // inizio il ciclo con smpcStep 1ms, parto da 0
   {
      dbRmsOn1ms = 0.0;
      dbLocalMax = 0.0;
      for(un=0; un < smpcStepLength; un++)   //ciclo interno sul blocchetto di 1ms
      {
         dbSample     = pTrack[un + smpcStep*smpcStepLength]; // campione corrente
         dbSqrSample  = dbSample*dbSample;                    // campione al quadrato
         dbRmsOn1ms  += dbSqrSample;                          // somma dei quadrati

         if(dbSqrSample > dbMax)
        	 dbMax = dbSqrSample; // ricerca del max peak istantaneo

         if(dbSqrSample > dbLocalMax)
        	 dbLocalMax = dbSqrSample; // ricerca del max peak istantaneo locale

         dbPi   = ituA.m_dbG * dbPi   + ituB.m_dbG * fabs(dbSample);  // valore intermedio
         dbEnvp = ituA.m_dbG * dbEnvp + ituB.m_dbG * fabs(dbPi);      // Envelope secondo ITU P56
      }
      // WARNING: In the original code the following lines are swapped!!!
      dbTotalSum += dbRmsOn1ms;     // Accumulo il totale generale per il Leq
      dbRmsOn1ms /= smpcStepLength; // Valore short-Leq di 1ms

      // Ciclo ricerca threshold ITU P56
      for(j = 1; j < 30; j++)
      {
          if(dbEnvp < adbLevelThresholds[j])
          {
             if(aunLastSampleOverThreshold[j] < unHangoverLength)
             {
                 aunSamplesOverThreshold   [j] += 1;
                 aunLastSampleOverThreshold[j] += 1;
             }
          }
          else
          {
             aunSamplesOverThreshold   [j] += 1;
             aunLastSampleOverThreshold[j]  = 0;
          }
      }
      // aunSamplesOverThreshold[j] è ora uguale al numero di campioni sopra il threshold j-esimo

      ituL.m_dbRunFast = ituA.m_dbFast * dbRmsOn1ms + ituB.m_dbFast * ituL.m_dbRunFast;
      ituL.m_dbRunSlow = ituA.m_dbFast * dbRmsOn1ms + ituB.m_dbSlow * ituL.m_dbRunSlow;

      // Costante di tempo Impulse (nuova versione), 
      ituL.m_dbRun35ms = ituA.m_dbImpRaising * dbRmsOn1ms + ituB.m_dbImpRaising * ituL.m_dbRun35ms; // questo è l'RMS 35ms corrente
      ituL.m_dbRunImp  = (ituL.m_dbRun35ms > ituL.m_dbRunImp) ? ituL.m_dbRun35ms
    		                                                  : ituL.m_dbRunImp * ituB.m_dbImpFalling;
 
      // memorizzo i valori max Fast, Slow, Impulse
      if (ituL.m_dbRunFast > ituL.m_dbMaxFast) { ituL.m_dbMaxFast = ituL.m_dbRunFast;
                                                 iFast = smpcStep; }
      if (ituL.m_dbRunSlow > ituL.m_dbMaxSlow)   ituL.m_dbMaxSlow = ituL.m_dbRunSlow;
      if (ituL.m_dbRunImp  > ituL.m_dbMaxImp)    ituL.m_dbMaxImp  = ituL.m_dbRunImp;
      if (dbRmsOn1ms       > ituL.m_dbMax1ms)    ituL.m_dbMax1ms  = dbRmsOn1ms;

      // dbAggiungo ai 5 buffers i valori RMS correnti, già in dB
      aadbBuffers[TC_PEAK][smpcStep] = dB(dbLocalMax);    // memorizzo per il grafico il Peak  corrente
      aadbBuffers[TC_RMS] [smpcStep] = dB(dbRmsOn1ms);    // memorizzo per il grafico il valore istantaneo
      aadbBuffers[TC_ITU] [smpcStep] = dB(dbEnvp*dbEnvp); // memorizzo per il grafico il valore Envelope ITU
      aadbBuffers[TC_FAST][smpcStep] = dB(ituL.m_dbRunFast);     // memorizzo per il grafico il Fast corrente
      aadbBuffers[TC_SLOW][smpcStep] = dB(ituL.m_dbRunSlow);     // memorizzo per il grafico il Slow corrente
      aadbBuffers[TC_IMP] [smpcStep] = dB(ituL.m_dbRunImp);      // memorizzo per il grafico il Imp  corrente

      // aggiorno il progress meter
#if defined __ITUP56_SINGLE_FRAME__ || !defined __WXGTK__
      if((smpcStep % 100) == 0)   // to speedup not update at every step
         if(!UpdateProgressMeter((nCh+1)*smpcStep, m_nChnlsCount*smpcStepsCount))
            return false;
#endif

    }
        
    // ******************************** Parte 2 ********************************    
        
    // Converto tutti i risultati in dB
    dbMax            = dB(dbMax);
    ituL.m_dbMaxFast = dB(ituL.m_dbMaxFast);
    ituL.m_dbMaxSlow = dB(ituL.m_dbMaxSlow);
    ituL.m_dbMaxImp  = dB(ituL.m_dbMaxImp);
    ituL.m_dbMax1ms  = dB(ituL.m_dbMax1ms);
    dbLeq            = dB(dbTotalSum/smpcTrackLength); // divido per il n. di blocchetti, ed ho l'energia media

    bool   bIsImpulsive = false;
    double dbPulseDuration = 0.0;
    AFSampleCount smpcLeftBound  = 0,
    		      smpcRightBound = 0;
    
    // Verifica componente impulsiva (ituL, iFast, smpcStepsCount) -> dbPulseDuration
    // Prima condizione: Lmax,imp - Lmax,slow >= 6 dB
    if((ituL.m_dbMaxImp - ituL.m_dbMaxSlow) >= 6.0)
    {        
        // Seconda condizione: dbPulseDuration < 1s
        for(smpcStep = iFast; smpcStep > 0; smpcStep--)          // inizio il ciclo con step 1ms
        {
        	if(aadbBuffers[TC_FAST][smpcStep] < (ituL.m_dbMaxFast - 10.0))
            {
            	smpcLeftBound = smpcStep;
                break;
            }
        }
        
        for(smpcStep = iFast; smpcStep < smpcStepsCount; smpcStep++)          // inizio il ciclo con step 1ms
        {
            if (aadbBuffers[TC_FAST][smpcStep] < (ituL.m_dbMaxFast - 10.0))
            {
            	smpcRightBound = smpcStep;
                break;
            }
        }
            
        if((smpcLeftBound > 0) && (smpcRightBound > 0))
            dbPulseDuration = dbStepDuration * (smpcRightBound - smpcLeftBound - 1);
        
        if(dbPulseDuration < 1.0)
            bIsImpulsive = true;
    }

    // ******************************** Parte 3 ********************************

    // Calcolo Active Speech level        TODO  ActiveSpeechLevel(dbTotalSum, a, c) => (Afin)
    const double M = 15.9; //Threshold standard secondo ITU P56
    double Aj,Cj;
    double Afin = 0, Jfin = 0;
    double Deltaj;
    double Deltajm1 = 50.0;     //tutta l'energia impaccata in un unico campione
    
    for(j=29; j>0; j--)         // inizio il ciclo sui 50 possibili valori di Threshold
    {
        if(aunSamplesOverThreshold[j] == 0)
        	aunSamplesOverThreshold[j] = 1;

        Aj = dB(dbTotalSum/aunSamplesOverThreshold[j]);
        Cj = dB20(adbLevelThresholds[j]);
        Deltaj = Aj-Cj;
        if(Deltaj <= M) 
        {
            Jfin = j + (M-Deltaj)/(Deltajm1-Deltaj);
            Afin = dB(dbTotalSum/aunSamplesOverThreshold[j]) + (Jfin-j) * (dB(dbTotalSum/aunSamplesOverThreshold[j+1]) - dB(dbTotalSum/aunSamplesOverThreshold[j]));
            break; // ho trovato la soluzione, esco dal ciclo.
        }
        Deltajm1 = Deltaj;
    }
    
    // ******************************** Parte 4 ********************************
    // Salvataggio Risultati
    double* adbParameters = m_aResults[nCh].m_adbParameters;

    double dbFullScale = m_paSignalTracks->Item(nCh).GetFullScale(),
    	   dbLeqFs     = dbLeq + dbFullScale; // Leq scaled

    adbParameters[THA_FSL] = dbFullScale;                          // Full Scale level
    adbParameters[THA_AVG] = dbLeqFs;                              // Average level
    adbParameters[THA_SEL] = dbLeqFs + dB(smpcTrackLength/dbRate); // Single Event level
    adbParameters[THA_TDU] = smpcTrackLength/dbRate;               // Total Duration
    adbParameters[THA_ASL] = Afin +  dbFullScale;                  // Active Speech level
    adbParameters[THA_THS] = Afin +  dbFullScale - M;              // Threshold level
    adbParameters[THA_ACT] = undB(dbLeq-Afin) * 100;               // Activity factor (%)
    adbParameters[THA_MPK] = dbMax + dbFullScale;                  // Max Peak level
    adbParameters[THA_MIM] = ituL.m_dbMaxImp  + dbFullScale;       // MaxSPL Impulse
    adbParameters[THA_MFS] = ituL.m_dbMaxFast + dbFullScale;       // MaxSPL Fast
    adbParameters[THA_MSL] = ituL.m_dbMaxSlow + dbFullScale;       // MaxSPL Slow
    adbParameters[THA_DUR] = dbPulseDuration;                      // Duration of the impulsive event
    adbParameters[THA_IMP] = (bIsImpulsive) ? 1.0 : 0.0;           // Impulsive event??
    
   // ritorno ok
   return true;
}

void AFTimeHistoryAnalyzer::SetTracksArray(TArrayOfTHASignalAudioTrack*  paSignalTracks)
{
	m_paSignalTracks = paSignalTracks;
	m_nChnlsCount = m_paSignalTracks->GetCount();

	Init();
}

void AFTimeHistoryAnalyzer::Init()
{
	Destroy();

	m_aResults = new TResults [m_nChnlsCount + 1];

	size_t unTrackLength = 0,
	       unStepLength;
	for(int nCh = 0; nCh < m_nChnlsCount; nCh++)
	{
		unTrackLength = m_paSignalTracks->Item(nCh).GetTrackLength();
		unStepLength  = m_paSignalTracks->Item(nCh).GetSamplerate() / 1000.0;
		m_aResults[nCh].SetBuffersLength(unTrackLength / unStepLength);
	}
}

void AFTimeHistoryAnalyzer::Destroy()
{
	if(m_aResults) delete [] m_aResults;
}

// --- ctors
AFTimeHistoryAnalyzer::AFTimeHistoryAnalyzer(const int nChannels)
   : m_bRemoveDC(true),
     m_paSignalTracks(0),
     m_aResults(0)
{}

AFTimeHistoryAnalyzer::~AFTimeHistoryAnalyzer()
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
