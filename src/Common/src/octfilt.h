/******************************
 *
 *  Third Octave Band Filter
 *
 ******************************/
 
#ifndef __octfilt_h__
#define __octfilt_h__

#define DUMP_TAPS

class SCFilter
{
  public:
    enum Errors { NO_ERR = 0,
    	          ERR_FM = 700,        ERR_RATE,
    	          ERR_CREATING_FILTER, ERR_NOT_IMPL };
    
  protected:
      
    // Attributes
    int    m_nErr;
    
    double m_dbRate;
    double m_dbFnyq;
    int    m_nOrder;
                
    AFSample* m_adbB;
    AFSample* m_adbA;

    bool   m_bIsFir;

    // Private methods

    virtual void IIR(AFSample* yt, AFSample* xt, const AFSampleCount length);
    virtual void FIR(AFSample* yt, AFSample* xt, const AFSampleCount length);
   
    void init(const AFSample* b,
              const AFSample* a = 0);
    
    virtual void init() {}

  public:
#ifdef DUMP_TAPS      
    void Dump(const int id, const char* tag);
#endif
    
    void UseFIR() { m_bIsFir = true;  init(); }
    void UseIIR() { m_bIsFir = false; init(); }

    bool IsOk() const { return (m_nErr == NO_ERR) ? true : false; }
    int  GetError() const { return m_nErr; }
    
    bool Apply(AFSample* yt, AFSample* xt, const AFSampleCount length);

    void SetRate(const double rate) { m_dbRate  = rate; init();  }

    // Firwin like constructor
    SCFilter(const int    N,
             double       cutoff,
             const int    window   = 10,
             const double width    = 0.0,
             const bool   passZero = true,
             const bool   scale    = true,
             const double fnyq     = 1.0);
    SCFilter(const int N,
             AFSample* b,
             AFSample* a = 0,
             const bool   isFir = true,
             const double rate  = 48000.0);
    virtual ~SCFilter();
};

class SCOctaveBandFilterBase : public SCFilter
{
protected:
    double m_dbFmExp;

public:
    virtual void Create(const double rate,
                        const double fmExp,
                        const bool   isFir = true) {}

    SCOctaveBandFilterBase();
    SCOctaveBandFilterBase(const double rate,
                           const double fmExp,
                           const bool   isFir = true);

	virtual ~SCOctaveBandFilterBase() {}
};

class SCOctaveBandFilter : public SCOctaveBandFilterBase
{
  public:
    void Create(const double rate,
                const double fmExp,
                const bool   isFir = true);

    SCOctaveBandFilter();
    SCOctaveBandFilter(const double rate,
                       const double fmExp,
                       const bool   isFir = true);
};

class SCThirdOctaveBandFilter : public SCOctaveBandFilterBase
{
  public:
    void Create(const double rate,
                const double fmExp,
                const bool   isFir = true);

    SCThirdOctaveBandFilter();
    SCThirdOctaveBandFilter(const double rate,
                            const double fmExp,
                            const bool   isFir = true);
};
 
 
#endif //__octfilt_h__
