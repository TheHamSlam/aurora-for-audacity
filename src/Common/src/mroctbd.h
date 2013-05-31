/******************************
 *
 *  Third Octave Band Analysis
 *
 ******************************/

class AFAudioTrack;
class SCFilter;
class SCOctaveBandFilter;
class SCThirdOctaveBandFilter;

class SCOctaveBandAnalysisBase
{
  public:
    enum { IIR_B = 0, IIR_A };
    
  protected:
    
    // Attributes
    double        m_dbRate;
    bool          m_bIsPreFilteringFIR;
    unsigned int  m_unCurrentBand;
    unsigned int  m_unBandsCount;
    
    AFAudioTrack* m_pTrack;
    
    AFSample* m_psmpXtLP;
    AFSample* m_psmpXtRes;
    int       m_nDecimationFactor;
    AFSampleCount m_smpcMinLength;
    double    m_dbG;

    SCFilter* m_pLpFilter;
    std::vector<SCOctaveBandFilterBase*> m_vFilterBank;

    virtual void ChooseLPFilterSet();
    
    void Decimate(const unsigned int N, AFSample* dest, AFSample* src, AFSampleCount length);
    
public:
    
    // Interface
    virtual bool Init(AFAudioTrack* track)    { return false; }
    virtual int  Filter(const int id = -1)    { return -1; }
    virtual int FilterForBand(const int band) { return -1; }

    unsigned int GetBandsCount() const { return m_unBandsCount; }
    
    // 'ctors
    SCOctaveBandAnalysisBase(const double       rate,
                             const bool         firPreFiltering,
                             const unsigned int bandsCount);
    virtual ~SCOctaveBandAnalysisBase();

};

class SCOctaveBandAnalysis : public SCOctaveBandAnalysisBase
{
private:
	enum { FBP_16k = 0, FBP_8k };
    //SCOctaveBandFilter m_vFilterBank[2];

public:
    
    enum { BD_31_5 = 0,  BD_63,   BD_100,  BD_250,  BD_500,
           BD_1k,        BD_2k,   BD_4k,   BD_8k,   BD_16k,
           N_BANDS
    };
    
    
    // Interface
    bool Init(AFAudioTrack* track);
    int  Filter(const int id = -1);
    int  FilterForBand(const int targetBand);
    
    // 'ctors
    SCOctaveBandAnalysis(const double rate            = 48000.0,
                         const bool   firPreFiltering = true);
    ~SCOctaveBandAnalysis();

};

class SCThirdOctaveBandAnalysis : public SCOctaveBandAnalysisBase
{
  private:
	enum { FBP_20k = 0, FBP_16k, FBP_12k5, FBP_10k };
	//SCThirdOctaveBandFilter m_vFilterBank[4];

  public: 
    
    enum { BD_25 = 0, BD_31_5, 
           BD_40,     BD_50,   BD_63,   
           BD_80,     BD_100,  BD_125,  
           BD_160,    BD_200,  BD_250,  
           BD_315,    BD_400,  BD_500,  
           BD_630,    BD_800,  BD_1k,
           BD_1k25,   BD_1k6,  BD_2k,   
           BD_2k5,    BD_3k15, BD_4k,   
           BD_5k,     BD_6k3,  BD_8k,   
           BD_10k,    BD_12k5, BD_16k,  
           BD_20k, 
           
           N_BANDS 
    };
          
    // Interface
    bool Init(AFAudioTrack* track);
    int  Filter(const int id = -1);
    int  FilterForBand(const int targetBand);

    // 'ctors
    SCThirdOctaveBandAnalysis(const double rate            = 48000.0, 
                              const bool   firPreFiltering = true);
    ~SCThirdOctaveBandAnalysis();
};

// ----------------------------------------------------------------------------
class SCOctaveBandData
{
  private:
    double       m_dbRate;
    double*      m_adbData;    
    unsigned int m_unLength;
    float        m_flFm;
    
  public:
    void Init(const unsigned int length, const bool zeroFill = false);
    
    double  GetRate() const { return m_dbRate; }
    double* GetData() const { return m_adbData; }
    unsigned int GetLength() const { return m_unLength; }
    float GetNominalFm() const { return m_flFm; }
    
    void SetRate(const double rate) { m_dbRate = rate; }
    void SetData(double* data, const unsigned int length = 0);
    void SetLength(const unsigned int length) { m_unLength = length; }
    void SetNominalFm(const float fm) { m_flFm = fm; }

    // 'ctors    
    SCOctaveBandData(const double rate = 48000.0);
    SCOctaveBandData(double* data, 
                     const unsigned int length,
                     const float fm,
                     const double rate = 48000.0);
    ~SCOctaveBandData();
};
