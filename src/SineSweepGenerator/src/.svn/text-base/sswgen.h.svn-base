/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Sine Sweep Signal Generator

  sswgen.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_SSWGEN_H__
#define __AURORA_SSWGEN_H__

#include <commdefs.h>

class SineSweepGenerator
{
   public:
      enum Channels   { //CH_LEFT, CH_RIGHT, 
	                    CH_INV_FILT = 2, CH_PULSES, _N_TRACKS_ };
      enum SweepTypes { ST_LINEAR, ST_LOG, ST_PINK };
      enum FadeTypes  { FT_RECT, FT_HAMMING, FT_HANN, FT_QUARTER_SINE, FT_LINEAR, 
                        FT_GAUSSIAN, FT_BLACKMANN, FT_BLACK_HARRIS, FT_LOG };

      enum ErrorCodes { ERR_OK = 0,
    	                ERR_SWEEP_LIMITS = 5000, ERR_DURATION, ERR_AMPLITUDE, ERR_CHANNELS_N,
    	                ERR_FADE_IN,             ERR_FADE_OUT, ERR_SILENCE,   ERR_CYCLES_N };
       
   private:

      int    m_nErrNo;

      double m_dbRate;
      double m_dbHighFrq;
      double m_dbLowFrq;
      double m_dbSweepDuration;
      double m_dbAmplitude;
      double m_dbSilenceDuration;
      long   m_lCycles;
      double m_dbFadeInDuration;
      double m_dbFadeOutDuration;
      int    m_nFadeInType;
      int    m_nFadeOutType;
      double m_dbDeltaL;
      int    m_nChnlsCount;
      int    m_nSweepChnlsCount;
      int    m_nFilterChnlIdx;
      int    m_nPulsesChnlIdx;
      
      AFSample** m_aasmpBuffers;
      
      AFSampleCount m_smpcBuffersLength;
      AFSampleCount m_smpcSweepLength;
      AFSampleCount m_smpcFilterLength;
      
      int m_nSweepType;
     
      bool m_bControlPulses;
      
      //--- private methods
      bool InitBuffers(int nCh = 0);
      void InitDataBuffers();
      void DeleteDataBuffers();
      
   public:
     // Check for input errors
     int ErrorCheck();
      
     /// Processing method
     bool Generate();

     /// Fill data block (module interface)
     void FillBlock(AFSample* psmpData, AFSampleCount smpcLen, AFSampleCount smpcWritten, int nTrack);
     
    // --- Checkers
    bool IsControlPulsesSet()     const { return m_bControlPulses; }

    // --- Get/Setters
    int   GetErrorCode()         const { return m_nErrNo; }
    void  GetErrorMessage(wxString& wxszMsg);

    double GetSamplerate()        const { return m_dbRate; }
    double GetStartFrequency()    const { return m_dbLowFrq; }
    double GetEndFrequency()      const { return m_dbHighFrq; }
    double GetHighFrequency()     const { return m_dbHighFrq; }
    double GetLowFrequency()      const { return m_dbLowFrq; }
    double GetSweepDuration()     const { return m_dbSweepDuration; }
    double GetSilenceDuration()   const { return m_dbSilenceDuration; }
    double GetAmplitude()         const { return m_dbAmplitude; }
    int    GetCyclesNumber()      const { return m_lCycles; }
    int    GetRepetitionsNumber() const { return m_lCycles; }
    int    GetSweepType()         const { return m_nSweepType; }
    int    GetNeededTracks()      const { return m_nChnlsCount; }
    double GetFadeInDuration()    const { return m_dbFadeInDuration; }
    double GetFadeOutDuration()   const { return m_dbFadeOutDuration; }
    int    GetFadeInType()        const { return m_nFadeInType; }
    int    GetFadeOutType()       const { return m_nFadeOutType; }
    double GetDeltaL()            const { return m_dbDeltaL; }
    int    GetChannelsNumber()    const { return m_nChnlsCount; }
    int    GetSweepChnlsNumber()  const { return m_nSweepChnlsCount; }
    int    GetFilterChannel()     const { return m_nFilterChnlIdx; }
    int    GetPulsesChannel()     const { return m_nPulsesChnlIdx; }
    double GetTotalDuration()     const { return m_smpcBuffersLength/m_dbRate; }
    
    AFSample* GetBuffer(int nCh)      const { return m_aasmpBuffers[nCh]; }
    AFSampleCount GetBuffersLength() const { return m_smpcBuffersLength; }
    AFSample* GetFilter(int nCh)      const { return m_aasmpBuffers[m_nFilterChnlIdx]; }
    AFSampleCount GetFilterLength()  const { return m_smpcFilterLength; }
    
    void SetSamplerate(double dbValue)      { m_dbRate = dbValue; }
    void SetStartFrequency(double dbValue)  { m_dbLowFrq = dbValue; }
    void SetEndFrequency(double dbValue)    { m_dbHighFrq = dbValue; }
    void SetHighFrequency(double dbValue)   { m_dbHighFrq = dbValue; }
    void SetLowFrequency(double dbValue)    { m_dbLowFrq = dbValue; }
    void SetSweepDuration(double dbValue)   { m_dbSweepDuration   = (dbValue < 100) ? dbValue : dbValue*m_dbRate; }
    void SetSilenceDuration(double dbValue) { m_dbSilenceDuration = (dbValue < 100) ? dbValue : dbValue*m_dbRate; }
    void SetAmplitude(double dbValue)       { m_dbAmplitude = dbValue; }
    void SetCyclesNumber(int nValue)       { m_lCycles = nValue; }
    void SetRepetitionsNumber(int nValue)  { m_lCycles = nValue; }
    void SetSweepType(int nValue)          { m_nSweepType = nValue; }
    void SetControlPulses(bool bValue);
    void SetFadeInDuration(double dbValue)  { m_dbFadeInDuration  = (dbValue < 100) ? dbValue : dbValue*m_dbRate; }
    void SetFadeOutDuration(double dbValue) { m_dbFadeOutDuration = (dbValue < 100) ? dbValue : dbValue*m_dbRate; }
    void SetFadeInType(int nValue)         { m_nFadeInType = nValue; }
    void SetFadeOutType(int nValue)        { m_nFadeOutType = nValue; }
    void SetDeltaL(double dbValue)          { m_dbDeltaL = dbValue; }
    void SetChannelsNumber(int nValue)     { m_nChnlsCount = nValue; }
    void SetSweepChnlsNumber(int nValue);
    
    void SetBuffersLength(AFSampleCount smpcLen, const bool bInitBuffer = false, int nCh = 0);    
    
     // --- ctors
     SineSweepGenerator();
     ~SineSweepGenerator();

};

#endif // __AURORA_SSWGEN_H__
