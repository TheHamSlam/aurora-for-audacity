/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions
  
  correlator.h

  Simone Campanini

**********************************************************************/
#ifndef __AURORA_XFUNCTIONS_CORRELATOR_H__
#define __AURORA_XFUNCTIONS_CORRELATOR_H__

// ---------------------------------------------
// a correlation calculation library
// ---------------------------------------------


#include <commdefs.h>
#include <fftw3.h>

class OutputTrack
{
   
 public:
    enum { // Track types
        
      NONE = 0,
      AUTO_CORRELATION_L, 
      AUTO_CORRELATION_R ,
      CROSS_CORRELATION,
      WHITE_CORRELATION,
      CROSS_POWER,
      TF_H1,
      TF_H2,
      TF_H3,
      ALPHA,
      COHERENCE,
      DIRAC_DELTA,
      PU_CAL_SW_TUBE,
      PU_CAL_FREE_FIELD
    };
 
  private:
    int mType;
    AFSample* mpTrack;
    
  public:  
    int GetType()        const { return mType; }
    AFSample* GetTrack() const { return mpTrack; }
    
    void SetType(const int type)         { mType = type; }
    void SetTrack(AFSample* track) { mpTrack = track; }
      
    OutputTrack(const int type = NONE, AFSample* track = 0) 
      : mType(type), mpTrack(track)
    {}
    
};

class Correlator
{

  public:
     enum XFunctionsType {

        XFT_AUTO_CORRELATION = 0X00,
        XFT_CROSS_CORRELATION,
        XFT_WHITE_CORRELATION,
        XFT_CROSS_POWER,
        XFT_TF_H1,
        XFT_TF_H2,
        XFT_TF_H3,
        XFT_ALPHA,
        _N_XFUNCTIONS_,
        
        XFT_COHERENCE = 11,
        XFT_DIRAC_DELTA 
     };
     
     enum PUProbeCalibrations {
         
        XFT_PU_CALIBRATION_SW_TUBE = 9,
        XFT_PU_CALIBRATION_FREE_FIELD
     };

   enum Channels {
    
//        CH_LEFT = 0x00,
//        CH_RIGHT,
        CH_CROSS = 2,
        CHANNELS_COUNT = 2
    };

    enum OutputChnls {

        CH_ALPHA = 0,
        CH_DIRAC = 0,
        CH_CALIBRATION = 1,
        CH_CROSSCORRELATION = 0,
        CH_COHERENCE = 1
    };

    enum WindowType {

        WT_RECTANGULAR = 0X00,
        WT_HANNING,
        WT_BLACKMANN_HARRIS,
        WT_FLAT_TOP,
        WT_TRIANGULAR,
        WT_HALF_SINE,
        WINDOWS_COUNT
    };

    enum Options {
        
        X_NORMALIZE = 0x00,
        X_SHIFT_TO_HALF_WINDOW,
        X_COHERENCE_WEIGHTING,
        X_SQUARED_HILBERT_TRANSFORM,
        X_TIME_REVERSAL,
        X_SAVE_MULTISPECTRUM,
        X_DIRAC_PULSE,
        X_REMOVE_DC,
        X_DEFAULT,
        OPTIONS_COUNT
    };
    
  protected:
    int m_nXFnTypeId;

    AFSample m_smpRate;

    int mChannelsToExport;
   
    bool *m_abOptions;
    
    AFSampleCount  m_smpcVectorLength,
                   m_smpcBlockLength,   // fft_length and block_length are the same thing!
                   m_smpcFftLength,     // Is the fft logical length
                   m_smpcSpectrumLength; //(m_smpcFftLength/2+1)
    
    AFSampleCount  m_smpcBlocksCount;
    
    AFSampleCount m_smpcLowerBound,
                  m_smpcHigherBound;

    // I/0 vectors/structs
    AFSample    *m_aasmpIn[2];
    OutputTrack m_aotOut[4]; // can be more than four..

    // RMS data vector
    double  m_adbRMS[3];

    AFSample      m_asmpGMax[2];
    AFSampleCount m_smpcGMaxIdx; // CrossCorrelation peak index
    
    AFSample m_smpGlrMax;  // MaxCC
    double   m_dbDelay;   // flytime??
    double   m_dbTriggerLevel;
    double   m_dbTriggerTime;

    // shaping window vector
    AFSample *m_asmpWindow;

    // blocks vectors
    AFSample *m_asmpLeft,
             *m_asmpRight,
             *m_asmpGll,
             *m_asmpGrr,
             *m_asmpGlr;

    // fftw3 stuffs
    fftwf_complex *m_acpxLeft,
                  *m_acpxRight,
                  *m_acpxGll,
                  *m_acpxGrr,
                  *m_acpxGlr;

    AFSample      *m_asmpC;   // Coherence
    fftwf_complex *m_acpxC;
    
    AFSample      *m_asmpHx;  // Hx filter
    fftwf_complex *m_acpxHx;

    AFSample      *m_asmpDelta;   // Dirac's delta spectrum
    fftwf_complex *m_acpxDelta;
    
    AFSample      *m_asmpAlpha;   // Alpha / PU calibration
    fftwf_complex *m_acpxAlpha;

    AFSample      *m_asmpWlr;
    fftwf_complex *m_acpxWlr; // Cross-Power Spectrum Phase

    AFSample      *m_aasmpHilbert[2]; // Hilbert transformed time domain vectors
    fftwf_complex *m_aacpxHilbert[2]; // Hilbert transformed frequency domain vectors

    fftwf_plan m_fftplanForward,
               m_fftplanBackward;

    // various
    int m_nWindowType;

    //Following filter variables
    bool   m_bIsFollowingFilterOn;
    int    m_nFollowChn;
    double m_dbFollowBW;
    
    // PUProbe variables
    double m_dbSoundSpeed,
           m_dbMicsDistance,
           m_dbFmax;
    bool   m_bIsFreeField,
           m_bIsSwTube;

    // processing flag
    bool m_bIsProcessed;

    // --- init methods
    void InitWindow(const AFSampleCount size);
    void InitInputVector(const int ch);
    void InitInputVectors();
    void DeleteInputVector(const int ch);
    void DeleteInputVectors();
    void InitVectors();
    void DeleteVectors();
  
    // --- math methods
    void ComplexRatio(fftwf_complex& q, fftwf_complex& n, fftwf_complex& d);
    
    // --- fft methods
    void FFT(fftwf_complex* Vf, AFSample* vt);
    void IFFT(AFSample* vt, fftwf_complex* Vf);

    // -- vector ops methods
    AFSample FindModMax(fftwf_complex* Xf);
    AFSample SquareRms(AFSample* x, AFSample* y, AFSampleCount length);
    AFSampleCount FindImax(const fftwf_complex* Xf);
    void   FindMax(const AFSample* x, const AFSampleCount length, AFSample* max, AFSampleCount* max_idx);
    void   RemoveDC(AFSample* x, AFSampleCount length);
    void   Normalize(AFSample* x, AFSample max, AFSampleCount length);
    void   CircularShift(AFSample* xt, AFSampleCount half_length);
    double Delay(const AFSampleCount max_idx);
    double Trigger(const AFSample* x);
    
    // --- transformation & filtering methods    
    void HilbertTransform(fftwf_complex* Xf, fftwf_complex* HXf);
    void HFilter(fftwf_complex* Xf, fftwf_complex* Yf);
    void H3Filter(fftwf_complex* Xf, fftwf_complex* Yf);
    
    // --- signal generation methods
    void Dirac();
    
    // --- alpha & PU probe calibration methods
    void Alpha(); 
    void PUCalibrationSWTube();    // -> CalibPU
    void PUCalibrationFreeField(); // -> CalibPU2

    /// --- correlation methods
    void AutoSpectrum(fftwf_complex* Gf, fftwf_complex* Xf, AFSampleCount current_block);
    void CrossSpectrum(AFSampleCount current_block);
    void Coherence();    // -> COHFilter
    void WhitenedCrossSpectrumPhase();  // -> COHFilter2 
    void CoherenceWeighting(fftwf_complex* Xf, fftwf_complex* Yf);
    void CrossPowerSpectrumPhase(AFSampleCount current_block);

     // --- processing methods    
    bool DoCrossCorrelation();  // -> ReadAndAverageData;
    
    void PostProcessAutocorrelation();
    void PostProcessCrossFunction(AFSample* xt, fftwf_complex* Xf);
    
 public:
    bool Process();
 
 public:
    // --- checkers, get-setters
    bool IsNormalizeSet()          const { return m_abOptions[X_NORMALIZE]; }
    bool IsShiftToHalfWindowSet()  const { return m_abOptions[X_SHIFT_TO_HALF_WINDOW]; }
    bool IsCoherenceWeightingSet() const { return m_abOptions[X_COHERENCE_WEIGHTING]; }
    bool IsHilbertTransformSet()   const { return m_abOptions[X_SQUARED_HILBERT_TRANSFORM]; }
    bool IsTimeReversalSet()       const { return m_abOptions[X_TIME_REVERSAL]; }
    bool IsSaveMultispectrumSet()  const { return m_abOptions[X_SAVE_MULTISPECTRUM]; }
    bool IsDiracPulseSet()         const { return m_abOptions[X_DIRAC_PULSE]; }
    bool IsRemoveDcSet()           const { return m_abOptions[X_REMOVE_DC]; }
    bool IsDefaultSet()            const { return m_abOptions[X_DEFAULT]; }
    bool GetOption(const int opt)  const { return m_abOptions[opt]; }
    
    int      GetXFunctionType()       const { return m_nXFnTypeId;  }
    AFSample GetSamplerate()          const { return m_smpRate; }
    int      GetChannelsToExport()    const { return mChannelsToExport; }
    int      GetWindowType()          const { return m_nWindowType; }
    AFSampleCount GetFFTLength()      const { return m_smpcFftLength; }
    AFSampleCount GetSpectrumLength() const { return m_smpcSpectrumLength; }
    AFSampleCount GetBlocksNumber()   const { return m_smpcBlocksCount; }
    double  GetRMS(const int ch)      const { return m_adbRMS[ch]; }
    
    double  GetXCorrelationMax()      const { return m_smpGlrMax; }
    double  GetXCorrelationMaxDelay() const { return m_dbDelay; }
    
    double GetTriggerLevel() const { return m_dbTriggerLevel; }
    double GetTriggerTime()  const { return m_dbTriggerTime; }
    
    // following filter
    bool   IsFollowingFilterEnabled() const { return m_bIsFollowingFilterOn; }
    int    GetFollowingChannel()      const { return m_nFollowChn; }
    double GetFollowingBandwidth()    const { return m_dbFollowBW; }
    
    // PUProbe 
    bool   IsProbeFreeField()       const { return m_bIsFreeField; }
    bool   IsProbeRigidTerminated() const { return m_bIsSwTube; }
    double GetSoundSpeed()    const { return m_dbSoundSpeed; }
    double GetProbeDistance() const { return m_dbMicsDistance; }
    double GetProbeMaxFreq()  const { return m_dbFmax; }
    
    // Input 
    AFSampleCount GetInputVectorsLength() const { return m_smpcVectorLength; }
    AFSample* GetInputVector(const int chn)  { return m_aasmpIn[chn]; }
    
    // Results
    AFSampleCount GetResultsVectorLength() const { return m_smpcBlockLength; }
    void GetResultsVector(AFSample* v, const int chn);
    AFSample* GetResultsVector(const int chn) const { return m_aotOut[chn].GetTrack(); }
    
    fftwf_complex* GetAutocorrelationSpectrum(const int ch) const { return (ch == 0) ? m_acpxGll : m_acpxGrr; }
    fftwf_complex* GetCrosscorrelationSpectrum() const { return m_acpxGlr; }
    fftwf_complex* GetCoherenceSpectrum()        const { return m_acpxC; }
    fftwf_complex* GetCrossPowerSpectrum()       const { return m_acpxWlr; }
    fftwf_complex* GetH1FunctionSpectrum()       const { return m_acpxHx; }
    fftwf_complex* GetH2FunctionSpectrum()       const { return m_acpxHx; }
    fftwf_complex* GetH3FunctionSpectrum()       const { return m_acpxHx; }
    fftwf_complex* GetDiracPulseSpectrum()       const { return m_acpxDelta; }
    fftwf_complex* GetAlphaSpectrum()                     const { return m_acpxAlpha; }
    fftwf_complex* GetProbeFreeFieldCalibrationSpectrum() const { return m_acpxAlpha; }
    fftwf_complex* GetProbeSWTubeCalibrationSpectrum()    const { return m_acpxAlpha; }
    fftwf_complex* GetHilbertTransform(const int ch)      const { return m_aacpxHilbert[ch]; }
    fftwf_complex* GetFunctionSpectrum(const int xfn, const int ch = 0);
    fftwf_complex* GetFunctionSpectrum(const int nCh = 0) { return GetFunctionSpectrum(m_nXFnTypeId, nCh); }
    
    // - setters
    void SetNormalize(const bool value)             { m_abOptions[X_NORMALIZE] = value; }
    void SetShiftToHalfWindow(const bool value)     { m_abOptions[X_SHIFT_TO_HALF_WINDOW] = value; }
    void SetCoherenceWeighting(const bool value)    { m_abOptions[X_COHERENCE_WEIGHTING] = value; }
    void SetHilbertTransform(const bool value)      { m_abOptions[X_SQUARED_HILBERT_TRANSFORM] = value; }
    void SetTimeReversal(const bool value)          { m_abOptions[X_TIME_REVERSAL] = value; }
    void SetSaveMultispectrum(const bool value)     { m_abOptions[X_SAVE_MULTISPECTRUM] = value; }
    void SetDiracPulse(const bool value)            { m_abOptions[X_DIRAC_PULSE] = value; }
    void SetRemoveDc(const bool value)              { m_abOptions[X_REMOVE_DC] = value; }
    void SetDefault(const bool value)               { m_abOptions[X_DEFAULT] = value; }
    void SetOption(const int opt, const bool value) { m_abOptions[opt] = value; }

    void SetInputVectorLength(const AFSampleCount len, const int ch, const bool init = true);
    void SetInputVectorsLength(const AFSampleCount len, const bool init = true);
      
    void SetXFunctionType(const int type)        { m_nXFnTypeId = type; }
    void SetSamplerate(const AFSample value)     { m_smpRate = value; }
    void SetWindowType(const int type)           { m_nWindowType = type; }
    void SetFFTLength(const AFSampleCount value) { m_smpcFftLength = value; m_smpcBlockLength = value;
                                                   m_smpcSpectrumLength = 1 + value/2; }
    
    void SetTriggerLevel(const double value) { m_dbTriggerLevel = value; }
    void SetTriggerTime(const double value)  { m_dbTriggerTime = value; }
    
    // following filter
    void SetBounds();
    void SetFollowingFilter(const bool value)      { m_bIsFollowingFilterOn = value; }
    void SetFollowingChannel(const int value)      { m_nFollowChn = (value == CH_RIGHT) ? CH_RIGHT : CH_LEFT; }
    void SetFollowingBandwidth(const double value) { m_dbFollowBW = value; }
    
    // PUProbe 
    void SetProbeFreeField(const bool value)       { if((m_bIsFreeField = value)) m_bIsSwTube = false; }
    void SetProbeRigidTerminated(const bool value) { if((m_bIsSwTube = value)) m_bIsFreeField = false; }
    void SetSoundSpeed(const double value)         { m_dbSoundSpeed = value; }
    void SetProbeDistance(const double value)      { m_dbMicsDistance = value; }
    void SetProbeMaxFreq(const double value)       { m_dbFmax = value; }
    
    
    // Progress meter
#ifdef __WXWINDOWS__    
    virtual void InitProgressMeter(const wxString& msg) = 0;
#else
    virtual void InitProgressMeter(const char* msg) = 0;
#endif
    virtual bool UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total) = 0;
    virtual void DestroyProgressMeter() = 0;

    // ---'ctors 
    Correlator();
    ~Correlator();
};

#endif //__AURORA_XFUNCTIONS_CORRELATOR_H__

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
