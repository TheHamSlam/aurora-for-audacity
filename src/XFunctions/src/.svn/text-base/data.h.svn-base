/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions
  
  data.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_XFUNCTIONS_DATA_H__
#define __AURORA_XFUNCTIONS_DATA_H__

#include <afdata.h>

//----------------------------------------------------------------------------
// XFSpectrumDataHandler function pointer typedef
//----------------------------------------------------------------------------
class XFSpectrumDataSerie;
typedef double (XFSpectrumDataSerie::*TXFAvgFunction)(const int nF0, const int nF1);

//----------------------------------------------------------------------------
// XFSpectrumDataSerie
//----------------------------------------------------------------------------
class XFSpectrumDataSerie : public TSpectrumDataSerie<fftwf_complex>
{
  public:

    enum
    {
        HT_AUTOCORR_L = 0,
        HT_AUTOCORR_R,
        HT_MAGNITUDE,
        HT_PHASE,
        HT_REAL,
        HT_IMAGINARY,
        HT_ALPHA,
        HT_COHERENCE
    };

  protected:
    fftwf_complex *m_pfcpxGll,
                  *m_pfcpxGrr,
                  *m_pfcpxGlr,
                  *m_pfcpxC;   // coherence...just for export functions

    TXFAvgFunction m_fpAverage;

    double Rll      (const int nF0, const int nF1);
    double Rrr      (const int nF0, const int nF1);
    double Magn     (const int nF0, const int nF1);
    double Phaze    (const int nF0, const int nF1);
    double SqrReal  (const int nF0, const int nF1);
    double SqrImag  (const int nF0, const int nF1);
    double Alpha    (const int nF0, const int nF1);
    double Coherence(const int nF0, const int nF1);

  public:
    void CalculateDataSerie(const size_t nWindowLength, const double dbLo, const double dbHi, const bool bIsLog);

    bool IsOk(const double dbFLo, const double dbFHi);

    void SetAutocorrelationLeft (fftwf_complex* pfcpxGll) { m_pfcpxGll = pfcpxGll; }
    void SetAutocorrelationRight(fftwf_complex* pfcpxGrr) { m_pfcpxGrr = pfcpxGrr; }
    void SetCrosscorrelation    (fftwf_complex* pfcpxGlr) { m_pfcpxGlr = pfcpxGlr; }
    void SetCoherence           (fftwf_complex* pfcpxC)   { m_pfcpxC   = pfcpxC; }

    fftwf_complex* Gll() const { return m_pfcpxGll; }
    fftwf_complex* Grr() const { return m_pfcpxGrr; }
    fftwf_complex* Glr() const { return m_pfcpxGlr; }
    fftwf_complex* C  () const { return m_pfcpxC; }

    fftwf_complex* GetAutocorrelationLeft () const { return m_pfcpxGll; }
    fftwf_complex* GetAutocorrelationRight() const { return m_pfcpxGrr; }
    fftwf_complex* GetCrosscorrelation    () const { return m_pfcpxGlr; }
    fftwf_complex* GetCoherence           () const { return m_pfcpxC; }

    double GetCorrelationLag() const { return m_unSpectrumLength/(2.0*m_dbRate); }

    void SetHandlerId(const int nTypeId);

// copy operators & methods
    XFSpectrumDataSerie& operator=(XFSpectrumDataSerie& Right);
    XFSpectrumDataSerie* Clone();

 // --- 'ctors
    XFSpectrumDataSerie(const double dbRate = 44100.0, const int nHandlerType = HT_AUTOCORR_L)
     : TSpectrumDataSerie<fftwf_complex>(dbRate, nHandlerType),
       m_pfcpxGll(0), m_pfcpxGrr(0), m_pfcpxGlr(0), m_pfcpxC(0)
    { SetHandlerId(nHandlerType); }

    XFSpectrumDataSerie(const size_t unSpectrumLength, const double dbRate = 44100.0, const int nHandlerType = HT_AUTOCORR_L)
     : TSpectrumDataSerie<fftwf_complex>(unSpectrumLength, dbRate, nHandlerType),
       m_pfcpxGll(0), m_pfcpxGrr(0), m_pfcpxGlr(0), m_pfcpxC(0)
    { SetHandlerId(nHandlerType); }

    XFSpectrumDataSerie(fftwf_complex* pfcpxSpectrum, const size_t unSpectrumLength, const double dbRate = 44100.0, const int nHandlerType = HT_AUTOCORR_L)
     : TSpectrumDataSerie<fftwf_complex>(pfcpxSpectrum, unSpectrumLength, dbRate, nHandlerType),
       m_pfcpxGll(0), m_pfcpxGrr(0), m_pfcpxGlr(0), m_pfcpxC(0)
    { SetHandlerId(nHandlerType); }

};
WX_DECLARE_OBJARRAY(XFSpectrumDataSerie, TArrayOfXFSpectrumDataSerie);

#endif  // __AURORA_XFUNCTIONS_DATA_H__

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
