/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  sti.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AuroraSTI
\brief The Audacity module for Aurora STI class.

  This class calculates the Speech Transmission Index, given a
  a room Impulse Response, a Background Noise recording and
  the artificial mouth probe signal recording.

*//*******************************************************************/
#include <string.h>

#include "sti.h"

double AuroraSTI::Flatten(double& dbValue, const double dbFlat)
{
    if(dbValue < -dbFlat)
        dbValue = -dbFlat;
    else if(dbValue > dbFlat)
        dbValue = dbFlat;
    
    return dbValue;
}

void AuroraSTI::CalibrateFullscale(STIAudioTrack* pCalibrationSignal, const int nChnl)
{
    // Farina's
    pCalibrationSignal->ResetFilteredTrack(nChnl);
    m_dbFullScaleLevel[nChnl] = m_dbCalibLevel[nChnl] - pCalibrationSignal->Leq(nChnl);            
}

void AuroraSTI::ComputeOctaveSpectrum(STIAudioTrack* pTrack, double* adbOctaveSpectrum, const int nChnl)
{
    double adbCenterBandFrq[] = { 31.5, 63.0, 125.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0, 8000.0, 16000.0 };
    
    for(int nBand = 0; nBand < N_BANDS; nBand++)
    {
        // Needed before every filtering to restore unfiltered vector
        pTrack->ResetFilteredTrack(nChnl); 
        pTrack->OctaveFilter(nChnl, adbCenterBandFrq[nBand]);
        adbOctaveSpectrum[nBand] = pTrack->Leq(nChnl) + m_dbFullScaleLevel[nChnl];
        UpdateProgressMeter(nBand+1);
    }
    
    // A band (11th)
    pTrack->ResetFilteredTrack(nChnl); 
    pTrack->AFilter(nChnl);
    adbOctaveSpectrum[BD_A] = pTrack->Leq(nChnl) + m_dbFullScaleLevel[nChnl];
    UpdateProgressMeter(11);

    // Lin band (12th)
    pTrack->ResetFilteredTrack(nChnl);
    adbOctaveSpectrum[BD_Lin] = pTrack->Leq(nChnl) + m_dbFullScaleLevel[nChnl];
    UpdateProgressMeter(12);

//    m_pProgDlg = 0;
}

bool AuroraSTI::StoreSpectrums(STIAudioTrack* pSignal, STIAudioTrack* pNoise, const int nChnl)
{ 
    int nBand;
    double adbOctaveSpectrum[12];

    SetProgressMeterMessage(wxString::Format(wxT("Background Noise: processing %s channel."),
                                             nChnl ? wxT("right") : wxT("left")));

    // Store noise
    ComputeOctaveSpectrum(pNoise, adbOctaveSpectrum, nChnl);
    for(nBand = 0; nBand < 12; nBand++)
    {
        m_aadbNoiseSpectrum[nChnl][nBand] = adbOctaveSpectrum [nBand];
    }
    SetProgressMeterMessage(wxString::Format(wxT("Test Signal: processing %s channel."),
                                             nChnl ? wxT("right") : wxT("left")) );
   
    // Store signal
    ComputeOctaveSpectrum(pSignal, adbOctaveSpectrum, nChnl);
    if(m_bIsSignalPlusNoise)
    {
        for(nBand = 0; nBand < 12; nBand++)
        {
            m_aadbSigNoiseSpectrum[nChnl][nBand] = adbOctaveSpectrum[nBand];
            if(adbOctaveSpectrum[nBand] - m_aadbNoiseSpectrum[nChnl][nBand] > 0.0)
            {
                m_aadbSignalSpectrum[nChnl][nBand] = dB( pow(10.0, adbOctaveSpectrum[nBand]/10.0) - 
                                                         pow(10.0, m_aadbNoiseSpectrum[nChnl][nBand]/10.0) );
            } 
            else
            {
                m_aadbSignalSpectrum[nChnl][nBand] = 0.0;
                m_bErrorFlag = true;
            }
        }
    }
    else
    {
        for(nBand = 0; nBand < 12; nBand++)
            SetSignalLevel(adbOctaveSpectrum[nBand], nBand, nChnl, true); // Update Signal and SigNoise
    }
    //m_pProgDlg->Destroy(); m_pProgDlg = 0;

    return !m_bErrorFlag;
}

bool AuroraSTI::CalculateMatrix(STIAudioTrack* pIR, const int nChnl)
{
    double adbCenterBandFrq[] = { 31.5, 63.0, 125.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0, 8000.0, 16000.0 };

    //InitProgressMeter(7, wxString(wxT("Aurora - Speech Transmission Index")));
    SetProgressMeterMessage(wxString::Format(wxT("Processing %s channel."),
    		                                 nChnl ? wxT("right") : wxT("left")));
    
    pIR->ResetFilteredTrack(nChnl);
    if(!pIR->FindFirstArrivalTime(m_dbFAT, nChnl))
    {
        // Maybe some things to do on ERROR state...
        return false;                
    }
    
    for(int nBand = 2; nBand < 9; nBand++)
    {
        pIR->STIOctaveFilter(nChnl, adbCenterBandFrq[nBand]);
        
        pIR->CalculateMTF(nChnl, m_aaadbMTF[nChnl][nBand-2]);
        pIR->CalculateMTF_STItel(nChnl, nBand, m_aadbSTItel[nChnl]);
        
        if(nBand == BD_2k)
            pIR->CalculateMTF_RaSTI(nChnl, m_aadbRaSTI[nChnl]);
        
        pIR->ResetFilteredTrack(nChnl);

        if(!UpdateProgressMeter(nBand-1))
        {
        	DestroyProgressMeter();
        	return false;
        }
    }

    DestroyProgressMeter();
    return true; 
}

bool AuroraSTI::CalculateSTI(const int nChnl)
{
    // A.Farina
    double adbMaskingRange[] = {0.0, 45.5, 55.5, 65.5, 75.5, 85.5, 95.5, 200.0};
    double adbMaskingSlope[] = {0.0, 0.0001, 0.000316, 0.003162, 0.01, 0.031622, 0.1};
    double adbAMF [7]; //Auditory Masking Factor, dipende dal livello sonoro secondo la tabella sovrastante
    double adbFemaleCorrection[] = {0.0, 2.4, -1.1, -2.3, -3.0, 2.1, 6.8};   //correzione allo spettro del segnale Female rispetto al segnale Male
    
    double adbSigNoiseLevelDiff [7];
    double adbSigPlusNoiseLevel [7];

    int nBand, nParam, n;
    for(int nSex = 0; nSex < 2; nSex++)
    {
        for(nBand = 0; nBand < 7; nBand++)
        {
            if(nSex == SG_FEMALE)
            {
                //SNR con correzione (caso 'female')
                adbSigNoiseLevelDiff[nBand] = (m_aadbSignalSpectrum[nChnl][nBand+2] + adbFemaleCorrection[nBand]) - 
                                               m_aadbNoiseSpectrum[nChnl][nBand+2];
                // calcolo livello totale segnale + rumore con correzione (caso 'female')
                adbSigPlusNoiseLevel[nBand] = dBsum((m_aadbSignalSpectrum[nChnl][nBand+2] + adbFemaleCorrection[nBand]), 
                                                     m_aadbNoiseSpectrum[nChnl][nBand+2]);
            }
            else
            {
                //SNR senza correzione (caso 'male')
                adbSigNoiseLevelDiff[nBand] = m_aadbSignalSpectrum[nChnl][nBand+2] - m_aadbNoiseSpectrum[nChnl][nBand+2];
                // calcolo livello totale segnale + rumore senza correzione (caso 'male')
                adbSigPlusNoiseLevel[nBand] = dBsum(m_aadbSignalSpectrum[nChnl][nBand+2], m_aadbNoiseSpectrum[nChnl][nBand+2]);
            }
            
            // calcolo Auditory Masking Factor (AMF)
            for(n = 0; n < 7; n++)
            {
                if( (adbSigPlusNoiseLevel[nBand] >= adbMaskingRange[n]) &&
                    (adbSigPlusNoiseLevel[nBand] <  adbMaskingRange[n+1]) )
                {
                    adbAMF[nBand] = adbMaskingSlope[n];
                    break;
                }
            }
        }

        for(nParam = 0; nParam < 14; nParam++)
        {
            for(nBand = 0; nBand < 7; nBand++)
            {
                if(m_bSNCorrection)
                    m_aaadbMTFf[nChnl][nBand][nParam] = m_aaadbMTF[nChnl][nBand][nParam] /  
                                                        ( 1.0 + pow(10.0, (-adbSigNoiseLevelDiff[nBand]/10.0)) );
                else
                    m_aaadbMTFf[nChnl][nBand][nParam] = m_aaadbMTF[nChnl][nBand][nParam];
            }
        }
        
        for(nBand = 0; nBand < 5; nBand++)
        {
            if(m_bSNCorrection)
                m_aadbRaSTIf[nChnl][nBand] = m_aadbRaSTI[nChnl][nBand] /
                                             ( 1.0 + pow(10.0, (-adbSigNoiseLevelDiff[RBD_2k]/10.0)) );
            else
                m_aadbRaSTIf[nChnl][nBand] = m_aadbRaSTI[nChnl][nBand];
        }
        
        for(nBand = 0; nBand < 7; nBand++)
        {
            if(m_bSNCorrection)
                m_aadbSTItelf[nChnl][nBand] = m_aadbSTItel[nChnl][nBand] /
                                              ( 1.0 + pow(10.0, (-adbSigNoiseLevelDiff[nBand]/10.0)) );
            else
                m_aadbSTItelf[nChnl][nBand] = m_aadbSTItel[nChnl][nBand];
        }        

        //applico le correzioni (masking and threshold) all'mtf per ottenere il valore finale 
        if(m_bMaskingCorrection)
            ApplyMaskingCorrection(nChnl, adbSigPlusNoiseLevel, adbAMF);

        SNR(nChnl);
        STI(nChnl, nSex);
        RaSTI(nChnl);
    }
    //These are only for males...
    STItel(nChnl);
    STIPa(nChnl);

    return true;
}

void AuroraSTI::ApplyMaskingCorrection(const int nChnl, const double adbSigPlusNoiseLevel[], const double adbAMF[])
{
    double adbThresholdFactor[] = {46.0, 27.0, 12.0, 6.5, 7.5, 8.0, 12.0};

    int nBand, nParam;
    for(nParam = 0; nParam < 14; nParam++)
    {
        // la prima banda ha solo Threshold, non ha Masking
        m_aaadbMTFf[nChnl][RBD_125][nParam] *=  pow(10.0, adbSigPlusNoiseLevel[RBD_125]/10.0) / 
                                                (pow(10.0, adbSigPlusNoiseLevel[RBD_125]/10.0) + adbThresholdFactor[RBD_125]);
        // le altre 6 bande hanno sia Threshold che Masking
        for(nBand = RBD_250; nBand < 7; nBand++)
        {
            m_aaadbMTFf[nChnl][nBand][nParam] *=  pow(10.0, adbSigPlusNoiseLevel[nBand]/10.0) / 
                                                  (pow(10.0, adbSigPlusNoiseLevel[nBand]/10.0) +  adbAMF[nBand]*adbSigPlusNoiseLevel[nBand-1] + adbThresholdFactor[nBand]);
        }
    }
    // No masking for RaSTI
    
    // la prima banda ha solo Threshold, non ha Masking
    m_aadbSTItelf[nChnl][RBD_125] *=  pow(10.0, adbSigPlusNoiseLevel[RBD_125]/10.0) / 
                                      (pow(10.0, adbSigPlusNoiseLevel[RBD_125]/10.0) + adbThresholdFactor[RBD_125]);
    // le altre 6 bande hanno sia Threshold che Masking
    for(nBand = RBD_250; nBand < 7; nBand++)
    {
        m_aadbSTItelf[nChnl][nBand] *=  pow(10.0, adbSigPlusNoiseLevel[nBand]/10.0) / 
                                        (pow(10.0, adbSigPlusNoiseLevel[nBand]/10.0) +  adbAMF[nBand]*adbSigPlusNoiseLevel[nBand-1] + adbThresholdFactor[nBand]);
    }
}   

void AuroraSTI::SNR(const int nChnl)
{
   int nBand, nParam;
   double dbSNRtmp = 0.0,
          dbTItmp  = 0.0,
          adbSNR [14][7],
          adbTI  [14][7];
 
    //----------------------------------------------------------------------------- Calcolo SNR   
    for(nBand = 0; nBand < 7; nBand++)
    {
        dbTItmp = 0.0;
        for(nParam = 0; nParam < 14; nParam++)
        {
            dbSNRtmp = dB( m_aaadbMTFf[nChnl][nBand][nParam] / 
                          (1.0 - m_aaadbMTFf[nChnl][nBand][nParam]) );
            Flatten(dbSNRtmp, 15.0);                
            
            adbSNR[nParam][nBand] = dbSNRtmp;
            
            //calcolo TI
            adbTI[nParam][nBand] = (adbSNR[nParam][nBand] + 15.0) / 30.0;
            
            //calcolo l'MTI medio di ciascuna banda
            dbTItmp += adbTI[nParam][nBand];
        }
        m_aadbMTI[nChnl][nBand] = dbTItmp / 14.0; // Valori STI di banda
    }

}

void AuroraSTI::STI(const int nChnl, const int nSex)
{
    double adbAlphaM[] = {0.085, 0.127, 0.230, 0.233, 0.309, 0.224, 0.173};  //coeff di peso voce maschile
    double adbBetaM[]  = {0.085, 0.078, 0.065, 0.011, 0.047, 0.095, 0.000};  //coeff di peso voce maschile
    double adbAlphaF[] = {0.000, 0.117, 0.223, 0.216, 0.328, 0.250, 0.194};  //coeff di peso voce femminile
    double adbBetaF[]  = {0.000, 0.099, 0.066, 0.062, 0.025, 0.076, 0.000};  //coeff di peso voce femminile

    int nBand;
    double dbAlphaTmp = 0.0,
           dbBetaTmp  = 0.0;
   //-----------------------------------------------------------------------------calcolo STI    
    if(nSex == SG_MALE)
    {
        for(nBand = 0; nBand < 7; nBand++) 
            dbAlphaTmp += adbAlphaM[nBand]*m_aadbMTI[nChnl][nBand];

        for(nBand = 0; nBand < 6; nBand++) 
            dbBetaTmp  += adbBetaM[nBand] * sqrt(m_aadbMTI[nChnl][nBand]*m_aadbMTI[nChnl][nBand+1]);

        m_adbSTImale[nChnl] = dbAlphaTmp - dbBetaTmp;
    }
    else
    {
        for(nBand = 0; nBand < 7; nBand++) 
            dbAlphaTmp += adbAlphaF[nBand]*m_aadbMTI[nChnl][nBand];

        for(nBand = 0; nBand < 6; nBand++)
            dbBetaTmp  += adbBetaF[nBand] * sqrt(m_aadbMTI[nChnl][nBand]*m_aadbMTI[nChnl][nBand+1]);

        m_adbSTIfemale[nChnl] = dbAlphaTmp - dbBetaTmp;
    }
}

void AuroraSTI::RaSTI(const int nChnl)
{
   int nBand, nParam;
   double dbSNRtmp = 0.0;

   //----------------------------------------------------------------------------- calcolo RaSTI
    double dbTIRaSTI_1 = 0.0;
    for(nParam = 2; nParam < 14; nParam += 3)
    {
        // 500 Hz band
        dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_500][nParam] / 
                       (1.0 - m_aaadbMTFf[nChnl][RBD_500][nParam]) );
        Flatten(dbSNRtmp, 15.0);            
        
        //calcolo TI
        dbTIRaSTI_1 += (dbSNRtmp + 15.0) / 30.0;
    }
    dbTIRaSTI_1 /= 4.0; // Valore STI di banda 500 Hz, media di 4 Mod.freq.
    
    double dbTIRaSTI_2 = 0.0; // 2000 Hz
    for(nBand = 0; nBand < 5; nBand++)
    {
        dbSNRtmp = dB( m_aadbRaSTIf[nChnl][nBand] /
                       (1.0 - m_aadbRaSTIf[nChnl][nBand]) );
        Flatten(dbSNRtmp, 15.0);
        
        //calcolo TI
        dbTIRaSTI_2 += (dbSNRtmp + 15.0) / 30.0;
    }
    dbTIRaSTI_2 /= 5.0; // Valore STI di banda 500 Hz, media di 5 Mod.freq.
    m_adbRaSTI[nChnl] = 4.0 / 9.0 * dbTIRaSTI_1 + 5.0 / 9.0 * dbTIRaSTI_2;
}

void AuroraSTI::STItel(const int nChnl)
{
   double adbAlphaM[] = {0.085, 0.127, 0.230, 0.233, 0.309, 0.224, 0.173};  //coeff di peso voce maschile
   double adbBetaM[]  = {0.085, 0.078, 0.065, 0.011, 0.047, 0.095, 0.000};  //coeff di peso voce maschile

   double adbTISTItel [7];
   double dbSNRtmp = 0.0,
          dbTItmp  = 0.0;

    // ---------------------------------------------------------------------------- calcolo STItel
   int nBand;
    for(nBand = 0; nBand < 7; nBand++)
    {
        dbTItmp = 0.0;
        dbSNRtmp = dB( m_aadbSTItelf[nChnl][nBand] /
                       (1.0 - m_aadbSTItelf[nChnl][nBand]) );
        Flatten(dbSNRtmp, 15.0);           
        
        //calcolo STItel di banda
        adbTISTItel[nBand] = (dbSNRtmp + 15.0) / 30.0;
    }
    
    //calcolo valore finale di STItel
    double dbAlphaTmp = 0.0,
           dbBetaTmp  = 0.0;
    for(nBand = 0; nBand < 7; nBand++) 
        dbAlphaTmp += adbAlphaM[nBand]*adbTISTItel[nBand];

    for(nBand = 0; nBand < 6; nBand++) 
        dbBetaTmp  += adbBetaM[nBand] * sqrt(adbTISTItel[nBand]*adbTISTItel[nBand+1]);
    
    m_adbSTItel[nChnl] = dbAlphaTmp - dbBetaTmp;

}

void AuroraSTI::STIPa(const int nChnl)
{
   double adbAlphaM[] = {0.085, 0.127, 0.230, 0.233, 0.309, 0.224, 0.173};  //coeff di peso voce maschile
   double adbBetaM[]  = {0.085, 0.078, 0.065, 0.011, 0.047, 0.095, 0.000};  //coeff di peso voce maschile

    double adbMTIpa [7];
    double dbSNRtmp = 0.0,
           dbTItmp  = 0.0;

    memset(adbMTIpa, 0, 7*sizeof(double));
    //----------------------------------------------------------------------------- calcolo STIPa
    // 250 Hz (con media anche su 125 Hz)
    // 1.0 Hz
    dbSNRtmp = dB( ((m_aaadbMTFf[nChnl][RBD_250][SP_1_0] + m_aaadbMTFf[nChnl][RBD_125][SP_1_0]) / 2.0) /
                   (1.0 - (m_aaadbMTFf[nChnl][RBD_250][SP_1_0] - m_aaadbMTFf[nChnl][RBD_125][SP_1_0]) / 2.0) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp = (dbSNRtmp + 15.0) / 30.0;
    // 5.0 Hz
    dbSNRtmp = dB( ((m_aaadbMTFf[nChnl][RBD_250][SP_5_0] + m_aaadbMTFf[nChnl][RBD_125][SP_5_0]) / 2.0) /
                   (1.0 - (m_aaadbMTFf[nChnl][RBD_250][SP_5_0] - m_aaadbMTFf[nChnl][RBD_125][SP_5_0]) / 2.0)  );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp += (dbSNRtmp + 15.0) / 30.0;
    adbMTIpa[RBD_250] = dbTItmp / 2.0; // Valore STI di banda 125/250 Hz, media di 2 Mod.freq.
    
    // 500 Hz
    // 0.63 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_500][SP_0_63] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_500][SP_0_63]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp = (dbSNRtmp + 15.0) / 30.0;
    // 3.15 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_500][SP_3_15] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_500][SP_3_15]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp += (dbSNRtmp + 15.0) / 30.0;
    adbMTIpa[RBD_500] = dbTItmp / 2.0; // Valore STI di banda 500 Hz, media di 2 Mod.freq.
    
    // 1000 Hz
    // 2.0 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_1k][SP_2_0] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_1k][SP_2_0]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp = (dbSNRtmp + 15.0) / 30.0;
    // 10 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_1k][SP_10_0] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_1k][SP_10_0]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp += (dbSNRtmp + 15.0) / 30.0;
    adbMTIpa[RBD_1k] = dbTItmp / 2.0; // Valore STI di banda 1000 Hz, media di 2 Mod.freq.
    
    // 2000 Hz
    // 1.25 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_2k][SP_1_25] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_2k][SP_1_25]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp = (dbSNRtmp + 15.0) / 30.0;
    // 6.25 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_2k][SP_6_3] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_2k][SP_6_3]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp += (dbSNRtmp + 15.0) / 30.0;
    adbMTIpa[RBD_2k] = dbTItmp / 2.0; // Valore STI di banda 2000 Hz, media di 2 Mod.freq.

    // 4000 Hz
    // 0.8 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_4k][SP_0_8] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_4k][SP_0_8]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp = (dbSNRtmp + 15.0) / 30.0;
    // 4.0 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_4k][SP_4_0] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_4k][SP_4_0]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp += (dbSNRtmp + 15.0) / 30.0;
    adbMTIpa[RBD_4k] = dbTItmp / 2.0; // Valore STI di banda 4000 Hz, media di 2 Mod.freq.
    
    // 8000 Hz
    // 2.5 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_8k][SP_2_5] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_8k][SP_2_5]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp = (dbSNRtmp + 15.0) / 30.0;
    // 12.5 Hz
    dbSNRtmp = dB( m_aaadbMTFf[nChnl][RBD_8k][SP_12_5] / 
                   (1.0 - m_aaadbMTFf[nChnl][RBD_8k][SP_12_5]) );
    Flatten(dbSNRtmp, 15.0);
    //calcolo TI
    dbTItmp += (dbSNRtmp + 15.0) / 30.0;
    adbMTIpa[RBD_8k] = dbTItmp / 2.0; // Valore STI di banda 8000 Hz, media di 2 Mod.freq.
    
    //calcolo finale di STIpa male
    int nBand;
    double dbAlphaTmp = 0.0,
           dbBetaTmp  = 0.0;
    for(nBand = 0; nBand < 7; nBand++)
    {
        dbAlphaTmp += adbAlphaM[nBand] * adbMTIpa[nBand];
    }
    for(nBand = 1; nBand < 6; nBand++)
    {
        dbBetaTmp += adbBetaM[nBand] * sqrt(adbMTIpa[nBand]*adbMTIpa[nBand+1]);
    }
    m_adbSTIpa[nChnl] = dbAlphaTmp - dbBetaTmp;
}


void AuroraSTI::ReadConfigurationValues()
{
   // Read parameter from stored configuration
   double dbValue;
   wxString wxszPath;
   wxszPath.Printf(wxT("/Aurora/STI/FullScale_Ch_1"));
   if(m_pCfg->Read(wxszPath, &dbValue))  SetFullScaleLevel(dbValue, CH_LEFT);
   wxszPath.Printf(wxT("/Aurora/STI/FullScale_Ch_2"));
   if(m_pCfg->Read(wxszPath, &dbValue))  SetFullScaleLevel(dbValue, CH_RIGHT);
   wxszPath.Printf(wxT("/Aurora/STI/Calibration_Ch_1"));
   if(m_pCfg->Read(wxszPath, &dbValue))  SetCalibrationLevel(dbValue, CH_LEFT);
   wxszPath.Printf(wxT("/Aurora/STI/Calibration_Ch_2"));
   if(m_pCfg->Read(wxszPath, &dbValue))  SetCalibrationLevel(dbValue, CH_RIGHT);

   int nBand;
   int anFcb[] = { 31, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000 };

   for(int nChnl = CH_LEFT; nChnl < 2; nChnl++)
   {
	   for(nBand = BD_31_5; nBand < N_BANDS; nBand++)
	   {
		   wxszPath.Printf(wxT("/Aurora/STI/SignalLevel_Bd_%d_Ch_%d"), anFcb[nBand], nChnl+1);
//		   printf("%s = %.1f -> ", (const char*)wxszPath.ToAscii(), GetSignalLevel(nBand, nChnl));
		   if(m_pCfg->Read(wxszPath, &dbValue))  SetSignalLevel(dbValue, nBand, nChnl);
//		   printf("%.1f\n", GetSignalLevel(nBand, nChnl));
	   }

	   for(nBand = BD_31_5; nBand < N_BANDS; nBand++)
	   {
		   wxszPath.Printf(wxT("/Aurora/STI/NoiseLevel_Bd_%d_Ch_%d"), anFcb[nBand], nChnl+1);
//		   printf("%s = %.1f -> ", (const char*)wxszPath.ToAscii(), GetNoiseLevel(nBand, nChnl));
		   if(m_pCfg->Read(wxszPath, &dbValue))  SetNoiseLevel(dbValue, nBand, nChnl, true); // Update SigNoise, too.
//		   printf("%.1f (%.1f)\n", GetNoiseLevel(nBand, nChnl), GetSigNoiseLevel(nBand, nChnl));
	   }
   }
}

void AuroraSTI::StoreConfigurationValues()
{
   wxString wxszPath;
   wxszPath.Printf(wxT("/Aurora/STI/FullScale_Ch_1"));
   m_pCfg->Write(wxszPath, GetFullScaleLevel(CH_LEFT));
   wxszPath.Printf(wxT("/Aurora/STI/FullScale_Ch_2"));
   m_pCfg->Write(wxszPath, GetFullScaleLevel(CH_RIGHT));

   wxszPath.Printf(wxT("/Aurora/STI/Calibration_Ch_1"));
   m_pCfg->Write(wxszPath, GetCalibrationLevel(CH_LEFT));
   wxszPath.Printf(wxT("/Aurora/STI/Calibration_Ch_2"));
   m_pCfg->Write(wxszPath, GetCalibrationLevel(CH_RIGHT));

   int nBand;
   int anFcb[] = { 31, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000 };

   for(int nChnl = CH_LEFT; nChnl < 2; nChnl++)
   {
	   for(nBand = BD_31_5; nBand < N_BANDS; nBand++)
	   {
		   wxszPath.Printf(wxT("/Aurora/STI/SignalLevel_Bd_%d_Ch_%d"), anFcb[nBand], nChnl+1);
		   m_pCfg->Write(wxszPath, GetSignalLevel(nBand, nChnl));
	   }

	   for(nBand = BD_31_5; nBand < N_BANDS; nBand++)
	   {
		   wxszPath.Printf(wxT("/Aurora/STI/NoiseLevel_Bd_%d_Ch_%d"), anFcb[nBand], nChnl+1);
		   m_pCfg->Write(wxszPath, GetNoiseLevel(nBand, nChnl));
	   }
   }

   m_pCfg->Flush();
}

void AuroraSTI::InitProgressMeter(const int nOverallTotal, const int nTotal, const wxString& wxszTitle)
{
/*	m_pProgDlg = new wxProgressDialog(wxszTitle,
                                      wxT("Calculating..."),
                                      nTotal,
                                      NULL,
                                      wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);
	wxSize sz = m_pProgDlg->GetSize();
	sz.x += 100;
	m_pProgDlg->SetSize(sz);*/
	m_pProgDlg = new GTProgressIndicator(wxszTitle, true, 2);
	m_pProgDlg->SetRange(nOverallTotal, 0);
	m_pProgDlg->SetRange(nTotal, 1);
}

void AuroraSTI::SetProgressMeterMessage(const wxString& wxszMsg)
{
	if(m_pProgDlg) m_pProgDlg->SetMessage(wxszMsg);
}

void AuroraSTI::SetProgressMeterRange(const int nTotal)
{
	if(m_pProgDlg) m_pProgDlg->SetRange(nTotal, 1);
}

bool AuroraSTI::UpdateProgressMeter(const int nStep)
{
//	if(m_pProgDlg)
//    	return (m_pProgDlg->Update(nStep, nTotal) == eProgressSuccess) ? true : false;
	if(m_pProgDlg)
		return m_pProgDlg->SetProgress(nStep, 1);
	return false;
}

void AuroraSTI::SetOverallProgressMeterRange(const int nTotal)
{
	if(m_pProgDlg) m_pProgDlg->SetRange(nTotal, 0);
}

bool AuroraSTI::UpdateOverallProgressMeter(const int nStep)
{
	if(m_pProgDlg)
		return m_pProgDlg->SetProgress(nStep, 0);
	return false;
}

void AuroraSTI::DestroyProgressMeter()
{
    delete m_pProgDlg; m_pProgDlg = 0;
}


// *** 'ctors

AuroraSTI::AuroraSTI(AFConfig* pCfg)
 : m_bErrorFlag(false),
   m_bIsSignalPlusNoise(true),
   m_dbFAT(0.20),               // First Arrive Threshold
   m_pProgDlg(0),
   m_pCfg(pCfg)
{
    m_dbCalibLevel [CH_LEFT]  = 94.0; // Calibration Level (dB)
    m_dbCalibLevel [CH_RIGHT] = 94.0;
    
    m_dbFullScaleLevel [CH_LEFT]  = 120.0; // FullScale Level (dB)
    m_dbFullScaleLevel [CH_RIGHT] = 120.0;

    // Spectrums
    memset(m_aadbNoiseSpectrum, 0, 2*12 * sizeof(double));
    memset(m_aadbSignalSpectrum, 0, 2*12 * sizeof(double));
    memset(m_aadbSigNoiseSpectrum, 0, 2*12 * sizeof(double));

    m_aadbNoiseSpectrum[CH_LEFT][BD_125]  = 48.0;
    m_aadbNoiseSpectrum[CH_LEFT][BD_250]  = 45.0;
    m_aadbNoiseSpectrum[CH_LEFT][BD_500]  = 42.0;
    m_aadbNoiseSpectrum[CH_LEFT][BD_1k]   = 39.0;
    m_aadbNoiseSpectrum[CH_LEFT][BD_2k]   = 36.0;
    m_aadbNoiseSpectrum[CH_LEFT][BD_4k]   = 33.0;
    m_aadbNoiseSpectrum[CH_LEFT][BD_8k]   = 30.0;

    m_aadbSignalSpectrum[CH_LEFT][BD_125]   = 70.9;
    m_aadbSignalSpectrum[CH_LEFT][BD_250]   = 70.9;
    m_aadbSignalSpectrum[CH_LEFT][BD_500]   = 67.2;
    m_aadbSignalSpectrum[CH_LEFT][BD_1k]    = 61.2;
    m_aadbSignalSpectrum[CH_LEFT][BD_2k]    = 55.2;
    m_aadbSignalSpectrum[CH_LEFT][BD_4k]    = 49.2;
    m_aadbSignalSpectrum[CH_LEFT][BD_8k]    = 43.2;
    

    m_aadbNoiseSpectrum[CH_RIGHT][BD_125]  = 48.0;
    m_aadbNoiseSpectrum[CH_RIGHT][BD_250]  = 45.0;
    m_aadbNoiseSpectrum[CH_RIGHT][BD_500]  = 42.0;
    m_aadbNoiseSpectrum[CH_RIGHT][BD_1k]   = 39.0;
    m_aadbNoiseSpectrum[CH_RIGHT][BD_2k]   = 36.0;
    m_aadbNoiseSpectrum[CH_RIGHT][BD_4k]   = 33.0;
    m_aadbNoiseSpectrum[CH_RIGHT][BD_8k]   = 30.0;

    m_aadbSignalSpectrum[CH_RIGHT][BD_125]  = 70.9;
    m_aadbSignalSpectrum[CH_RIGHT][BD_250]  = 70.9;
    m_aadbSignalSpectrum[CH_RIGHT][BD_500]  = 67.2;
    m_aadbSignalSpectrum[CH_RIGHT][BD_1k]   = 61.2;
    m_aadbSignalSpectrum[CH_RIGHT][BD_2k]   = 55.2;
    m_aadbSignalSpectrum[CH_RIGHT][BD_4k]   = 49.2;
    m_aadbSignalSpectrum[CH_RIGHT][BD_8k]   = 43.2;
    
    memset(m_aaadbMTF, 0, 2*14*7 * sizeof(double));
    memset(m_aadbSTItel, 0, 2*7 * sizeof(double));
    memset(m_aadbRaSTI,  0, 2*5 * sizeof(double));

    memset(m_aaadbMTFf, 0, 2*14*7 * sizeof(double));
    memset(m_aadbSTItelf, 0, 2*7 * sizeof(double));
    memset(m_aadbRaSTIf,  0, 2*5 * sizeof(double));

    memset(m_aadbMTI,    0, 2*7 * sizeof(double));
    
    m_adbSTImale   [CH_LEFT]  = 0;
    m_adbSTImale   [CH_RIGHT] = 0;
    m_adbSTIfemale [CH_LEFT]  = 0;
    m_adbSTIfemale [CH_RIGHT] = 0;
    m_adbSTIpa     [CH_LEFT]  = 0;
    m_adbSTIpa     [CH_RIGHT] = 0;
    m_adbRaSTI     [CH_LEFT]  = 0;
    m_adbRaSTI     [CH_RIGHT] = 0;
    m_adbSTItel    [CH_LEFT]  = 0;
    m_adbSTItel    [CH_RIGHT] = 0;
}


AuroraSTI::~AuroraSTI()
{}

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

