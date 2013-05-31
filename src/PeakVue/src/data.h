/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  PeakVue

  data.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_PEAKVUE_DATA_H__
#define __AURORA_PEAKVUE_DATA_H__

#include <commdefs.h>
#include <wxcmn.h>
#include <afvector.h>
#include <afcomplex.h>

//
// This file contains some useful data structures
//

////////////////////////////////////////////////////////////////////////////////
//
// enums & typedefs
//
////////////////////////////////////////////////////////////////////////////////
enum PeakMethods { PM_IN_SIGNO = 0,
	               PM_ABSOLUTE,
	               PM_SQUARE };

typedef AFVector<double>                      TTimeVector;
typedef AFComplexVector<fftw_complex, double> TFreqVector;

////////////////////////////////////////////////////////////////////////////////
//
// PVAudioData declaration
//
////////////////////////////////////////////////////////////////////////////////

class PVAudioData : public TTimeVector
{
  private:
    double  m_dbRate;
	int     m_nPeakMethod;
    double  m_dbBlockDuration;

  public:
    void SetPeakMethod(const int method)         { m_nPeakMethod     = method; }
    void SetBlockDuration(const double duration) { m_dbBlockDuration = duration; }
    void SetRate(const double rate)              { m_dbRate = rate; }

    bool SetDownsampledData(AFSample* data, AFSampleCount length, const double rate);

    int     GetPeakMethod()    const { return m_nPeakMethod; }
    double  GetBlockDuration() const { return m_dbBlockDuration; }
    double  GetRate()          const { return m_dbRate; }

    PVAudioData();
    ~PVAudioData();
};

////////////////////////////////////////////////////////////////////////////////
//
// PVDataShuttle declaration
//
////////////////////////////////////////////////////////////////////////////////

class PVDataShuttle
{
  private:
    int           m_nFftLength;
    int           m_nWindowType;
    PVAudioData   m_AudioData;
    TTimeVector   m_SpectralData;
    TTimeVector   m_AutoCorrelation;
    wxArrayString m_awxszTrackLabels;

  public:
    int  GetFftLength()  const { return m_nFftLength; }
	int  GetWindowType() const { return m_nWindowType; }

    void SetFftLength(const int length) { m_nFftLength = length; }
    void SetWindowType(const int type)  { m_nWindowType = type; }

    PVAudioData&   GetAudioData()       { return m_AudioData; }
    TTimeVector&   GetSpectralData()    { return m_SpectralData; }
    TTimeVector&   GetAutoCorrelation() { return m_AutoCorrelation; }
    wxArrayString& GetLabels()          { return m_awxszTrackLabels; }


	PVDataShuttle()
	: m_nFftLength(2048), m_nWindowType(WT_RECTANGULAR), m_AudioData(), m_SpectralData()
	{}
//	~PVDataShuttle() {}
};

////////////////////////////////////////////////////////////////////////////////
//
// Plot data structures
//
////////////////////////////////////////////////////////////////////////////////
#include <afdata.h>

//----------------------------------------------------------------------------
// PVDataHandler function pointer typedef
//----------------------------------------------------------------------------
class PVRealDataSerie;
typedef double (PVRealDataSerie::*TPVAvgFunction)(const int nLo, const int nHi);

////////////////////////////////////////////////////////////////////////////////
//
// PVRealDataSerie declaration
//
////////////////////////////////////////////////////////////////////////////////
class PVRealDataSerie : public AFDataHolder<double>
{
public:
    enum { HT_RMS = 100, HT_DECIMATE, HT_LINAVG };

  protected:
    TTimeVector& m_Data;

    double m_dbRate; // Duplicated data: it's stored in TTimeVector!!
    double m_dbFullScale;
    int    m_nHandlerType;

    TPVAvgFunction m_fpAverage;

    double Rms     (const int nLo, const int nHi);
    double Decimate(const int nLo, const int nHi);
    double Average (const int nLo, const int nHi);

  public:
    void SetHandler(const int nTypeId);

    virtual void CalculateDataSerie(const size_t nWindowLength,
    		                        double&      dbLo,
    		                        double&      dbHi,
    		                        const bool   bIsLog = false);

    virtual bool IsOk(const double dbTLo, const double dbTHi);

    void   SetFullScale(const double dbValue) { m_dbFullScale = dbValue; }
    double GetFullScale() const { return m_dbFullScale; }

    virtual double GetMax() const { return double(m_Data.GetLength())/m_dbRate; }

    // 'ctors
    PVRealDataSerie(PVAudioData& data,
    		        const int handlerType = HT_DECIMATE);

    PVRealDataSerie(TTimeVector& data,
    		        const double rate     = 44100.0,
    		        const int handlerType = HT_DECIMATE);
};
WX_DECLARE_OBJARRAY(PVRealDataSerie, TArrayOfPVRealDataSerie);

////////////////////////////////////////////////////////////////////////////////
//
// PVSpectrumMagnitudeDataSerie declaration
//
////////////////////////////////////////////////////////////////////////////////
class PVSpectrumMagnitudeDataSerie : public PVRealDataSerie
{
  private:
	size_t m_unSpectrumLength;

  public:
    virtual void CalculateDataSerie(const size_t unWindowLength,
    		                        double&      dbLo,
    		                        double&      dbHi,
    		                        const bool   bIsLog = true);

    virtual bool IsOk(const double dbFLo, const double dbFHi);

    virtual double GetMax() const { return m_dbRate/2.0; }

    // 'ctors
    PVSpectrumMagnitudeDataSerie(TTimeVector& data,
    		                     const size_t spectrumLength,
    		                     const double rate           = 44100.0,
    		                     const int    handlerType    = HT_DECIMATE);
};
WX_DECLARE_OBJARRAY(PVSpectrumMagnitudeDataSerie, TArrayOfPVSpectrumMagnitudeDataSerie);

#endif //__AURORA_PEAKVUE_DATA_H__

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
