/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  sti.h

  Angelo Farina - Simone Campanini

***********************************************************************/
#ifndef __AURORA_STI_H__
#define __AURORA_STI_H__


//#include <Audacity.h>
//#include <widgets/ProgressDialog.h>

#include <wxcmn.h>
#include <commdefs.h>
#include <afconfig.h>
#include <gtprogind.h>

#include "track.h"


class AuroraSTI
{
  public:
    enum OctaveBands { BD_31_5 = 0, BD_63, BD_125, BD_250, BD_500, 
                       BD_1k,       BD_2k, BD_4k,  BD_8k,  BD_16k, N_BANDS };
    
    enum LastBands   { BD_A = 10, BD_Lin, _N_BDS_ };

    enum ReducedOctaveBands { RBD_125 = 0, RBD_250, RBD_500, RBD_1k, 
                              RBD_2k,      RBD_4k,  RBD_8k,  N_RBANDS };
    
    enum STIParameters { SP_0_63 = 0, SP_0_8, SP_1_0, SP_1_25, SP_1_6, SP_2_0,  SP_2_5,  
                         SP_3_15,     SP_4_0, SP_5_0, SP_6_3,  SP_8_0, SP_10_0, SP_12_5, N_PARAMS } ;
    
    enum STIGenre { SG_FEMALE = 0, SG_MALE = 1 };

  private:
    bool   m_bErrorFlag;
    
    double m_dbSamplerate;
    double m_dbCalibLevel     [2];
    double m_dbFullScaleLevel [2];
    bool   m_bIsSignalPlusNoise;
    double m_dbFAT;               // 0 -> 1.0 NOT percentage!!
    bool   m_bSNCorrection;
    bool   m_bMaskingCorrection;
    
    // *** Results vectors & tables
    double m_aadbNoiseSpectrum    [2][12],
           m_aadbSignalSpectrum   [2][12],
           m_aadbSigNoiseSpectrum [2][12]; 
    
    double m_aaadbMTF      [2][7][14], // These are the original values
           m_aadbRaSTI     [2][5],
           m_aadbSTItel    [2][7];  

    double m_aaadbMTFf     [2][7][14], // These are final values, so it can be 
           m_aadbRaSTIf    [2][5],     // denoised, masked , etc.
           m_aadbSTItelf   [2][7];  

    double m_adbSTImale    [2],
           m_adbSTIfemale  [2],    
           m_adbSTIpa      [2];  
    
    double m_aadbMTI       [2][7], 
           m_adbRaSTI      [2],
           m_adbSTItel     [2];

    
    double Flatten(double& dbValue, const double dbFlat);
    
  public:
    
    void CalibrateFullscale(STIAudioTrack* pCalibrationSignal,const int nChnl = CH_LEFT);
    void ComputeOctaveSpectrum(STIAudioTrack* pTrack, double* adbOctaveSpectrum, const int nChnl = CH_LEFT);
    bool StoreSpectrums(STIAudioTrack* pSignal, STIAudioTrack* pNoise, const int nChnl = CH_LEFT);  
    bool CalculateMatrix(STIAudioTrack* pIR, const int nChnl = CH_LEFT);
    bool CalculateSTI(const int nChnl = CH_LEFT);

 private:
    void ApplyMaskingCorrection(const int nChnl, const double adbSigPlusNoiseLevel[], const double adbAMF[]);
    void SNR(const int nChnl);
    void STI(const int nChnl, const int nSex);
    void RaSTI(const int nChnl);
    void STItel(const int nChnl);
    void STIPa(const int nChnl);

  public:
    // checkers
    bool IsSignalPlusNoise() const { return m_bIsSignalPlusNoise; }
    bool IsSNCorrection() const { return m_bSNCorrection; }
    bool IsMaskingCorrection() const { return m_bMaskingCorrection; }
    
    // getters
    double GetSamplerate() const { return m_dbSamplerate; }
    double GetCalibrationLevel(const int nChnl = 0) const { return m_dbCalibLevel [nChnl]; }
    double GetFullScaleLevel(const int nChnl = 0) const { return m_dbFullScaleLevel [nChnl]; }
    
    double  GetFirstArriveThreshold() const { return m_dbFAT; }
    double  GetSignalLevel  (const int nBand, const int nChnl) const { return m_aadbSignalSpectrum[nChnl][nBand]; }
    double  GetNoiseLevel   (const int nBand, const int nChnl) const { return m_aadbNoiseSpectrum[nChnl][nBand]; }
    double  GetSigNoiseLevel(const int nBand, const int nChnl) const { return m_aadbSigNoiseSpectrum[nChnl][nBand]; }
    double* GetSignalSpectrumVector  (const int nChnl) { return m_aadbSignalSpectrum[nChnl]; }
    double* GetNoiseSpectrumVector   (const int nChnl) { return m_aadbNoiseSpectrum[nChnl]; }
    double* GetSigNoiseSpectrumVector(const int nChnl) { return m_aadbSigNoiseSpectrum[nChnl]; }

    double GetMtfTableValue(const int nParam, const int nBand, const int nChnl) const { return m_aaadbMTFf[nChnl][nBand][nParam]; } 
    double GetSTIValue (const int nBand, const int nChnl) const { return m_aadbMTI[nChnl][nBand]; }
    double GetSTIMale  (const int nChnl) const { return m_adbSTImale[nChnl]; }
    double GetSTIFemale(const int nChnl) const { return m_adbSTIfemale[nChnl]; }
    double GetRaSTI    (const int nChnl) const { return m_adbRaSTI[nChnl]; }
    double GetSTItel   (const int nChnl) const { return m_adbSTItel[nChnl]; }
    double GetSTIpa    (const int nChnl) const { return m_adbSTIpa[nChnl]; }
    double GetMTIValue (const int nChnl, const int nFrq) const { return m_aadbMTI[nChnl][nFrq]; }
    
    // setters    
    void SetSignalLevel(const double dbValue, const int nBand, const int nChnl, const bool bUpdateSigNoiseLevel = false) 
    { m_aadbSignalSpectrum[nChnl][nBand] = dbValue; 
      if(bUpdateSigNoiseLevel) 
          SetSigNoiseLevel(nChnl, nBand); }

    void SetNoiseLevel(const double dbValue, const int nBand, const int nChnl, const bool bUpdateSigNoiseLevel = false) 
    { m_aadbNoiseSpectrum[nChnl][nBand] = dbValue; 
      if(bUpdateSigNoiseLevel) 
          SetSigNoiseLevel(nChnl, nBand); }

    void SetSigNoiseLevel(const double dbValue, const int nBand, const int nChnl) 
    { m_aadbSigNoiseSpectrum[nChnl][nBand] = dbValue; } 

    void SetSigNoiseLevel(const int nBand, const int nChnl) 
    { m_aadbSigNoiseSpectrum [nChnl][nBand] = dBsum( m_aadbSignalSpectrum[nChnl][nBand],
                                                     m_aadbNoiseSpectrum[nChnl][nBand] ); }

    void SetSignalPlusNoise(const bool bValue) { m_bIsSignalPlusNoise = bValue; }
    void SetSNCorrection(const bool bValue)    { m_bSNCorrection = bValue; }
    void SetMaskingCorrection(const bool bValue) { m_bMaskingCorrection = bValue; }

    void SetSamplerate(const double dbValue) { m_dbSamplerate = dbValue; }
    void SetCalibrationLevel(const double dbValue, const int nChnl = 0) { m_dbCalibLevel [nChnl] = dbValue; }
    void SetFullScaleLevel(const double dbValue,const int nChnl = 0) { m_dbFullScaleLevel [nChnl] = dbValue; }
    void SetFirstArriveThreshold(const double dbValue) { m_dbFAT = dbValue; }

  private:
//    ProgressDialog*  m_pProgDlg;
//    wxProgressDialog* m_pProgDlg;
    GTProgressIndicator* m_pProgDlg;
    
  public:
    void InitProgressMeter(const int nOverallTotal = 0, const int nTotal = 0, const wxString& wxszTitle = wxT(""));
    void SetProgressMeterMessage(const wxString& wxszMsg);
    void SetProgressMeterRange(const int nTotal);
    bool UpdateProgressMeter(const int nStep);
    void SetOverallProgressMeterRange(const int nTotal);
    bool UpdateOverallProgressMeter(const int nStep);
    void DestroyProgressMeter();

//  public:
//    void SetProgressDlg(ProgressDialog* pProgDlg) { m_pProgDlg = pProgDlg; } // DO NOT USE!

  private:
    AFConfig*  m_pCfg;

  public:
    void ReadConfigurationValues();
    void StoreConfigurationValues();

    // 'ctors
    AuroraSTI(AFConfig* pCfg);
    ~AuroraSTI();
};



#endif //__AURORA_STI_H__
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

