/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  afthan.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_ITUP56_AFTHAN_H__
#define __AURORA_ITUP56_AFTHAN_H__

#include <commdefs.h>

#include "track.h"


class AFTimeHistoryAnalyzer
{
  public:
      
     enum Channel { //CH_LEFT, CH_RIGHT, 
		            CH_AVG = 2 };

     enum Sizes 
     {
         N_CHANNELS     = 2,
         N_BANDS        = 12,
         N_CHANNELS_EXT = 3  // 2 + avg channel
     };

     enum TimeConstants
     {
         TC_PEAK = 0, // 1 sample (local peak)
         TC_RMS,      // 1 ms  (TC_INST)
         TC_ITU,      // 30 ms
         TC_IMP,      // 35 ms up, 1.5 s down
         TC_FAST,     // 125 ms
         TC_SLOW,     // 1 s
         N_TIME_CONST
     };

     enum THAParameters 
     {
         THA_FSL,   // Full Scale level
         THA_AVG,   // Average level
         THA_SEL,   // Single Event level
         THA_TDU,   // Total Duration
         THA_ASL,   // Active Speech level
         THA_THS,   // Threshold level
         THA_ACT,   // Activity factor
         THA_MPK,   // Max Peak level
         THA_MIM,   // MaxSPL Impulse
         THA_MFS,   // MaxSPL Fast
         THA_MSL,   // MaxSPL Slow
         THA_DUR,   // Duration of the impulsive event
         THA_IMP,   // Impulsive event??
         N_PARAMETERS
     };

     struct TResults
     {
         double  m_adbParameters [N_PARAMETERS];
         double* m_aadbBuffers   [N_TIME_CONST];
         size_t  m_unBuffersLength;

         bool    IsImpulsive() const { return (m_adbParameters[THA_IMP] == 1.0) ? true : false; }

         double  GetParameter(const int nIdx) const { return m_adbParameters[nIdx]; }
         double* GetBuffer   (const int nIdx) const { return m_aadbBuffers[nIdx]; }
         size_t  GetBufferLength()            const { return m_unBuffersLength; }

         void SetBuffersLength(size_t unBuffersLength);

         void Init();
         void Destroy();

         TResults(size_t unBuffersLength = 0);
         ~TResults();

     };

  private:

     struct TITUFactors
     {
    	 const double m_dbG,
    	              m_dbFast,
    	              m_dbSlow,
    	              m_dbImpRaising,
    	              m_dbImpFalling;

    	 TITUFactors(const double dbG, const double dbFast, const double dbSlow,
    			     const double dbImpRaising, const double dbImpFalling)
    	 : m_dbG(dbG),
	       m_dbFast(dbFast),
	       m_dbSlow(dbSlow),
	       m_dbImpRaising(dbImpRaising),
	       m_dbImpFalling(dbImpFalling)
    	 {}
     };

     struct TITULevels
     {
    	 double m_dbRunFast,
    	        m_dbRunSlow,
    	        m_dbRunImp,
    	        m_dbRun35ms,
    	        m_dbMaxFast,
    	        m_dbMaxSlow,
    	        m_dbMaxImp,
    	        m_dbMax1ms;

    	 TITULevels()
    	 : m_dbRunFast(0.0),
    	   m_dbRunSlow(0.0),
    	   m_dbRunImp(0.0),
    	   m_dbRun35ms(0.0),
    	   m_dbMaxFast(0.0),
    	   m_dbMaxSlow(0.0),
    	   m_dbMaxImp(0.0),
    	   m_dbMax1ms(0.0)
    	 {}
     };

     int   m_nChnlsCount;
     bool  m_bRemoveDC;

     TArrayOfTHASignalAudioTrack*  m_paSignalTracks;
     TResults *m_aResults;

     //--- private methods
     double Average  (const int nParam);
     double dBAverage(const int nParam);
     void   FillAvgParameters();

  protected:
     virtual void InitProgressMeter() = 0;
     virtual void SetProgressMeterMessage(const wxString& wxszMsg) = 0;
     virtual bool UpdateProgressMeter(const int nStep, const int nTotal) = 0;
     virtual void DestroyProgressMeter() = 0;
     
  public:
     
    /// Processing method
    bool Analyze();
    bool AnalyzeTrack(const int nCh);

    // --- Get/Setters
    int     GetChannelsCount()  const { return m_nChnlsCount; }

    double  GetFullScaleValue(int nCh = 0)     const { return m_paSignalTracks->Item(nCh).GetFullScale(); } // TODO REMOVE IT (used in export.cpp and gui.cpp)
    size_t GetBuffersLength(const int nCh = 0) const { return m_aResults[nCh].GetBufferLength(); } // TODO REMOVE IT (used in export.cpp)

    double GetParameterValue(const int nCh, const int nIdx) const { return m_aResults[nCh].GetParameter(nIdx); } // TODO REMOVE IT (used in export.cpp and gui.cpp)
    
    void SetRemoveDC(bool bValue) { m_bRemoveDC = bValue; }
    
    void SetTracksArray(TArrayOfTHASignalAudioTrack*  m_paSignalTracks);

    TResults* GetResults() { return m_aResults; }

  private:
    void Init();
    void Destroy();

  public:
    // --- ctors
    AFTimeHistoryAnalyzer(const int nChannels = 1);
    virtual ~AFTimeHistoryAnalyzer();

};

#endif // __AURORA_ITUP56_AFTHAN_H__
