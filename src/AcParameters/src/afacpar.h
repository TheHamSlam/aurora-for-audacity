/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters
  
  afacpar.h

  Angelo Farina - Simone Campanini

**********************************************************************/

#ifndef __AURORA_AFACPAR_H__
#define __AURORA_AFACPAR_H__

#include "track.h"

#define FIND_VECTOR_MAX(x, max, bd) \
   for(unsigned long k = 0; k < bd; k++) \
       if(x > max) max = x;


class SCOctaveBandAnalysisBase;

//----------------------------------------------------------------------------
// TSchroederDecay
//
/// \brief The Schroeder decay holder
//
/// This code calculates the Schroeder decay from an impulse response and
/// holds it.

class TSchroederDecay
{
 private:
   AFSample*  m_asmpData;       // Decay calculated by Schroeder integration

   AFSampleCount m_smpcLength;  // Decay length
   AFSampleCount m_smpcFAT;
   double        m_dbTP2;
   double        m_dbRate;

 public:
   void Dump(const int idx = -1);

   AFSample  GetItem(const int nIdx) { return m_asmpData[nIdx]; }
   AFSample* Get()                   { return m_asmpData; }
   AFSample* GetVector()             { return m_asmpData; }
   AFSample& operator[](const AFSampleCount unIdx) { return m_asmpData[unIdx]; }

   AFSampleCount GetLength() const { return m_smpcLength; }
   double        GetTP2   () const { return m_dbTP2; }
   double        GetRate  () const { return m_dbRate; }

   void FindFirstArrivalTime();
   AFSampleCount GetFirstArrivalTimeInSamples() const { return m_smpcFAT; }

   void SetData(AFSample* psmpSrc, const AFSampleCount smpcSrcLength);

   void Process(APAudioTrack& track);
   void Init(APAudioTrack& track);
   void Init(const AFSampleCount smpcLength);

   TSchroederDecay();
   TSchroederDecay(const AFSampleCount smpcLength);
   ~TSchroederDecay();
};

//----------------------------------------------------------------------------
// AFAcousticalParameters
//
/// \brief The Acoustical Parameters calculation class.
//
/// The code of this class belongs directly from the original
/// Angelo Farina's Cool Edit/Audition plug-in code. In this
/// version many features has been added, like the multichannel
/// analysis.
//----------------------------------------------------------------------------

#define GSET_PARAM(name, idx)  double& Get##name   (const int band)\
		                       { return m_aaParametersTable[band][idx].dbValue; }\
                               \
                               void    Set##name  (const double value, \
		                                           const int band)\
		                       {  m_aaParametersTable[band][idx].dbValue = value; }

class AFAcousticalParameters
{
 public:   
 
   enum Mode {  APM_MONO = 0,

                // 2 channels modes
                APM_TWO_OMNI_MICS,    APM_SOUNDFIELD_WY,
                APM_PU_PROBE,         APM_INTENSITY_PROBE,
                APM_BINAURAL,
                      
                // 4 channels modes
                APM_FOUR_OMNI_MICS,
                APM_SOUNDFIELD_WXYZ, APM_SOUNDFIELD_WYXZ };
                      
   enum IACCSpan { IS_NONE, IS_EARLY, IS_LATE, IS_ALL };

   enum AnalysisMode { AP_OCTAVE_BANDS, AP_ONE_THIRD_OCTAVE_BANDS };

   enum OctaveBand {  BD_31_5, BD_63,  BD_125, BD_250, BD_500,
                      BD_1k,   BD_2k,  BD_4k,  BD_8k,  BD_16k,
                      BD_A,    BD_Lin, N_OCTAVE_BANDS  };

   enum ThirdOctaveBand { TO_BD_25,  TO_BD_31_5, TO_BD_40,  TO_BD_50,  TO_BD_63,
	                      TO_BD_80,  TO_BD_100,  TO_BD_125, TO_BD_160, TO_BD_200,
	                      TO_BD_250, TO_BD_315,  TO_BD_400, TO_BD_500, TO_BD_630,
	                      TO_BD_800, TO_BD_1k,   TO_BD_1k25,TO_BD_1k6, TO_BD_2k,
	                      TO_BD_2k5, TO_BD_3k15, TO_BD_4k,  TO_BD_5k,  TO_BD_6k3,
	                      TO_BD_8k,  TO_BD_10k,  TO_BD_12k5,TO_BD_16k, TO_BD_20k,
                          TO_BD_A,   TO_BD_Lin,  N_THIRD_OCTAVE_BANDS  };

   enum Parameters {  AP_SIGNAL,    AP_NOISE,      AP_G,        AP_C50,   AP_C80,
                      AP_D50,       AP_Ts,         AP_EDT,      AP_Tuser, AP_T20,
                      AP_T30,

                      AP_PEAKINESS,  AP_MILLISECS,  AP_IMPULSIVS,

                      AP_ST1,  AP_ST2,    AP_STL,     //StageParameters (14..)
                      AP_IACC, AP_T_IACC, AP_W_IACC,  // BinauralParameters (17..)
                      AP_JLF,  AP_JLFC,   AP_LJ,      // SpatialParameters  (20..)

                      N_PARAMETERS  }; // 23

   enum Errors { ERR_NO_FAT = 5000, ERR_SPATIAL_IR_TOO_SHORT, ERR_NO_CONFIG_SOURCE, ERR_UNKNOWN };

   // -------------------------- Data structures ----------------------------


   struct TResults
   {
	   struct TParameter { double dbValue; bool bIsValid; };

	   size_t m_unBandsCount;
	   std::vector< std::vector<TParameter> >  m_aaParametersTable;

	   void   SetBandsCount(const size_t count);
	   size_t GetBandsCount() const { return m_unBandsCount; }

	   double& GetParameter(const int nParameter, const int nBand)
	   { return m_aaParametersTable[nBand][nParameter].dbValue; }

	   void    SetParameter(const double dbValue, const int nParameter, const int nBand)
	   { m_aaParametersTable[nBand][nParameter].dbValue = dbValue; }

	   bool IsParameterValid(const int nParameter, const int nBand)
	   { return m_aaParametersTable[nBand][nParameter].bIsValid; }

	   void ValidateParameter(const int nParameter, const int nBand)
	   { m_aaParametersTable[nBand][nParameter].bIsValid = true; }

	   void InvalidateParameter(const int nParameter, const int nBand)
	   { m_aaParametersTable[nBand][nParameter].bIsValid = false; }

	   void SetParameterValidity(const bool bValue, const int nParameter, const int nBand)
	   { m_aaParametersTable[nBand][nParameter].bIsValid = bValue; }

	   GSET_PARAM(SignalLevel, AP_SIGNAL)  // Get/setters (see #define above...)
	   GSET_PARAM(NoiseLevel,  AP_NOISE)
	   GSET_PARAM(Strength,    AP_G)
	   GSET_PARAM(C50, AP_C50)
	   GSET_PARAM(C80, AP_C80)
	   GSET_PARAM(D50, AP_D50)
	   GSET_PARAM(Ts,    AP_Ts)
	   GSET_PARAM(EDT,   AP_EDT)
	   GSET_PARAM(Tuser, AP_Tuser)
	   GSET_PARAM(T20,   AP_T20)
	   GSET_PARAM(T30,   AP_T30)
	   GSET_PARAM(Peakiness,     AP_PEAKINESS)
	   GSET_PARAM(Millisecs,     AP_MILLISECS)
	   GSET_PARAM(Impulsiveness, AP_IMPULSIVS)
	   GSET_PARAM(St1, AP_ST1)
	   GSET_PARAM(St2, AP_ST2)
	   GSET_PARAM(StL, AP_STL)
	   GSET_PARAM(IACC,       AP_IACC)
	   GSET_PARAM(IACC_time,  AP_T_IACC)
	   GSET_PARAM(IACC_width, AP_W_IACC)
	   GSET_PARAM(Jlf,  AP_JLF)
	   GSET_PARAM(Jlfc, AP_JLFC)
	   GSET_PARAM(Lj,   AP_LJ)

       void Init();

	   TResults();
   };
    
   // -------------------------- Input parameters ----------------------------
 private:
   int    m_nChnlsCount;

   double m_dbRate,
          m_dbFullScale,
          m_dbUserMinLevel,
          m_dbUserMaxLevel,
          m_dbDirectSoundTrig,
          m_dbProbeMicsDistance,
          m_dbSoundSpeed;

 protected:
   bool m_bNoiseCorrection,
        m_bEDT,
        m_bStageMode,
        m_bAvgMode;
   
   int m_nMode,
       m_nIaccSpan,
       m_nAnalysisType;

   size_t m_unBandsCount;

   double m_dbSoundSourceDistance;

   //------------------------- Tracks data --------------------------------

   TArrayOfAPAudioTracks* m_paAudioTracks;

   //------------------------- Parameters attributes -------------------------
 private:


   std::vector<double> m_adbReferenceLevels; // strength reference levels vector;

   std::vector<SCOctaveBandAnalysisBase*> m_vOba;
   std::vector<TSchroederDecay>           m_vDecay;
   std::vector<TResults>                  m_vResults;

   double ReverberationTime(const int    nCh,
		                    const double dbStart,
		                    const double dbDelta);

   bool   GetFirstArrivalTime(); // deprecated
   AFSampleCount GetShorterFAT();

   double Clarity(const int nCh, const double dbWidth, const double dbDelay);
   double Definition(const int nCh, const double dbWidth, const double dbDelay);
   double EarlyLateralFraction(const double dbDelay);
   double EarlyLateralFractionCosine(const double dbDelay);
   double LateLateralSoundLevel(const int nBand, const double dbDelay);
   double InterAuralCrossCorrelation(const double  dbDelay,
		                                   double* pdbTauIACC,
		                                   double* pdbWidthIACC);
   double Peakiness(const int nCh);
   double Millisecondness(const int nCh, const int nBand, double* pdbImpulsivs);
   double Stage(const int nPar, const int nCh, const double dbDelay);
   double Strength(const int nCh, const int nBand);
   
   void   PreProcessIntensimetricSignal(APAudioTrack& left);

 protected:   
   virtual void ShowErrorMessage(const int nErrNo) = 0;
   
   virtual void InitProgressMeter(const int nTotal) = 0;
   virtual bool UpdateProgressMeter(const int nStep) = 0;
   virtual void DestroyProgressMeter() = 0;
     
   virtual void PreProcess() = 0;
   virtual void PostProcess() = 0;
   
 public: 
   bool CalculateAcousticParameters();
   void CalculateBandMonoParameters(const int nCh, const int nBand, const double dbDelay);
   void CalculateSpatialParameters(int nBand, double dbDelay);
   void CalculateBandAParametersAvg(int nCh);

   //------------------------- Class user interface -------------------------   
   // --- 1st part: user parameters status & setup (pre processing)

   // --- checkers
   bool IsNoiseCorrectionMode() const { return m_bNoiseCorrection; }
   bool IsEDTMode()             const { return m_bEDT; }
   bool IsStageMode()           const { return m_bStageMode; }
   bool IsAvgMode()             const { return m_bAvgMode; }

   bool IsMono()   const { return (m_nMode == APM_MONO); }
   bool IsStereo() const { return ( (m_nMode > int(APM_MONO)) && 
                                    (m_nMode < int(APM_FOUR_OMNI_MICS)) ); }
   bool IsTetra()  const { return (m_nMode > int(APM_BINAURAL)); }

   bool IsTwoOmniMics()         const { return (m_nMode == APM_TWO_OMNI_MICS); }
   bool IsASoundField()         const { return (m_nMode == APM_SOUNDFIELD_WY); }
   bool IsSoundfieldWY()        const { return (m_nMode == APM_SOUNDFIELD_WY); }
   bool IsAPUProbe()            const { return (m_nMode == APM_PU_PROBE); }
   bool IsAnIntensityProbe()    const { return (m_nMode == APM_INTENSITY_PROBE); }
   bool IsABinauralPair()       const { return (m_nMode == APM_BINAURAL); }
   bool IsFourOmniMics()        const { return (m_nMode == APM_FOUR_OMNI_MICS); }
   bool IsSoundfieldWXYZ()      const { return (m_nMode == APM_SOUNDFIELD_WXYZ); }
   bool IsSoundfieldWYXZ()      const { return (m_nMode == APM_SOUNDFIELD_WYXZ); }
   
   // --- togglers
   void ToggleNoiseCorrection() { m_bNoiseCorrection = (m_bNoiseCorrection) ? false :true; }
   void ToggleEDT()             { m_bEDT       = (m_bEDT) ? false :true; }
   void ToggleStageMode()       { m_bStageMode = (m_bStageMode) ? false :true; }
   void ToggleAverageMode()     { m_bAvgMode   = (m_bAvgMode)   ? false :true; }
   
   // --- getters
   std::vector<TSchroederDecay>& GetDecaysArray()          { return m_vDecay; }
   std::vector<TResults>&        GetResultsArray()         { return m_vResults; }

   int GetChannelsCount()        const { return m_nChnlsCount; }

   double& GetRate()                   { return m_dbRate; }
   double& GetFullScale()              { return m_dbFullScale; }
   double& GetUserMinLevel()           { return m_dbUserMinLevel; }
   double& GetUserMaxLevel()           { return m_dbUserMaxLevel; }
   double& GetProbeMicsDistance()      { return m_dbProbeMicsDistance; } // m
   double& GetSoundSpeedValue()        { return m_dbSoundSpeed; }
   double& GetDirectSoundTrigValue()   { return m_dbDirectSoundTrig; }

   int&    GetMode()                   { return m_nMode; }
   int&    GetIACCSpan()               { return m_nIaccSpan; }

   double& GetGSoundSourceDistance()           { return m_dbSoundSourceDistance; }
   double& GetGReferenceLevel(const int nBand) { return m_adbReferenceLevels[nBand]; }
   
   // --- setters
   void SetRate(const double dbValue)      { m_dbRate = dbValue; }
   void SetFullScale(const double dbValue) { m_dbFullScale = dbValue; }

   void SetUserMinLevel(const double dbValue) { m_dbUserMinLevel = dbValue; }
   void SetUserMaxLevel(const double dbValue) { m_dbUserMaxLevel = dbValue; }
   void SetNoiseCorrection(const bool bValue) { m_bNoiseCorrection = bValue; }
   void SetEDT(const bool bValue)             { m_bEDT = bValue; }
   void SetStageMode(const bool bValue)       { m_bStageMode = bValue; }
   void SetAverageMode(const bool bValue)     { m_bAvgMode = bValue; }
   
   void SetProbeMicsDistance(const double dist)    { m_dbProbeMicsDistance = dist; } // m
   void SetSoundSpeedValue(const double c)         { m_dbSoundSpeed = c; }
   void SetDirectSoundTrigValue(const double trig) {  if (trig > -1.0)  m_dbDirectSoundTrig = -1.0;  else
                                                      if (trig < -60.0) m_dbDirectSoundTrig = -60.0; else
                                                                        m_dbDirectSoundTrig = trig; }

   void SetMode(const int nValue)       { m_nMode = nValue; }
   void SetIACCSpan(const int nValue)   { m_nIaccSpan = nValue; }
   
   void SetGSoundSourceDistance(const double dbDist) { m_dbSoundSourceDistance = dbDist; }
   void SetGReferenceLevel(const double dbRefLevel,
		                   const int    nBand)       { m_adbReferenceLevels[nBand] = dbRefLevel; }
   
   void ReplaceGReferenceValues();

   size_t GetBandsCount()   const { return m_unBandsCount; }
   int    GetAnalysisType() const { return m_nAnalysisType; }
   void   SetAnalysisType(const int type = -1);

   //------------------------- Class user interface -------------------------   
   // --- 2nd part: get acustic parameters values (post processing)

   void UpdateFilteredTrack(const int nChnl, const int nBand);

   void RestoreDefaultReferenceLevels();

   // Init/Deinitialization method
   bool Init();
   void Destroy();

   // --- Ctors
   AFAcousticalParameters();
   AFAcousticalParameters(TArrayOfAPAudioTracks* paAudioTracks,
		                               const int analysisType = AP_OCTAVE_BANDS);
   virtual ~AFAcousticalParameters();
};

#endif // __AURORA_AFACPAR_H__

