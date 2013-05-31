/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common Libraries
  
  afdata.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_AFDATA_H__
#define __AURORA_AFDATA_H__

#include <wxcmn.h>
#include <commdefs.h>

//----------------------------------------------------------------------------
// AFDataHolder
/// Data container base class.
//----------------------------------------------------------------------------
template <class T>
class AFDataHolder
{
  private:
    bool     m_bIsShown;
    wxString m_wxszLabel;
    wxColour m_wxcolPen;
    wxColour m_wxcolBrush;
    
  protected:
    size_t  m_unLength;
    T*      m_aTData;

    virtual void Init() { m_aTData = new T [m_unLength];
                          memset(m_aTData, 0, m_unLength*sizeof(T)); }
    virtual void Destroy() { if(m_aTData) delete [] m_aTData; }

  public:
    virtual T        GetData(const size_t nIdx) { return m_aTData[nIdx]; }
    virtual const T* GetData()                  { return m_aTData; }

    virtual void SetData(const T TValue, const size_t nIdx) { m_aTData[nIdx] = TValue; }
    virtual void SetData(const T* pTSerie)                  { memcpy(m_aTData, pTSerie, m_unLength*sizeof(T)); }

    virtual const size_t  GetLength()  { return m_unLength; }

    bool IsShown() const                { return m_bIsShown; }
    void Show(const bool bValue = true) { m_bIsShown = bValue; }
    
    void ToggleVisibility() { m_bIsShown = !m_bIsShown; }
    
    wxString& GetLabel() { return m_wxszLabel; }
    void SetLabel(const wxString& wxszLabel) { m_wxszLabel = wxszLabel; }
    void SetLabel(const wxChar* pwxchLabel)  { m_wxszLabel = pwxchLabel; }

    void SetLineColour(const wxColour& colour)  { m_wxcolPen = colour; }
    void SetLineColour( const unsigned char r,
                        const unsigned char g,
                        const unsigned char b ) { m_wxcolPen.Set(r,g,b); }

    void SetFillColour(const wxColour& colour)  { m_wxcolBrush = colour; }
    void SetFillColour( const unsigned char r,
                        const unsigned char g,
                        const unsigned char b ) { m_wxcolBrush.Set(r,g,b); }

    const wxColour& GetLineColour() { return m_wxcolPen; }
    const wxColour& GetFillColour() { return m_wxcolBrush; }

    AFDataHolder()
     : m_bIsShown(true),
       m_wxszLabel(wxT("NoName")),
       m_wxcolPen(0,0,0),          // default border: black
       m_wxcolBrush(255,255,255),  // default fill: white;
       m_unLength(0),
       m_aTData(0)
    { }

    AFDataHolder(const size_t unLength)
     : m_bIsShown(true),
       m_wxcolPen(0,0,0),          // default border: black
       m_wxcolBrush(255,255,255),  // default fill: white;
       m_unLength(unLength),
       m_aTData(0)
    { Init(); }

    virtual ~AFDataHolder()
    { Destroy(); }
};

//----------------------------------------------------------------------------
// AFDataSerie
//----------------------------------------------------------------------------
class AFDataSerie : public AFDataHolder<double>
{
  public:
    void SetData(const double dbValue, const size_t nIdx) { m_aTData[nIdx] = dbValue; }
    void SetData(const double* pdbSerie)  { memcpy(m_aTData,
    		                                       pdbSerie,
    		                                       m_unLength*sizeof(double)); }
    void SetData(const float*  pflSerie)  { for(size_t un = 0; un < m_unLength; un++)
                                                m_aTData[un] =  double(pflSerie[un]); }

    AFDataSerie(const size_t unLength)
      : AFDataHolder<double>(unLength)
    { /* wxASSERT_MSG(m_unLength > 0, wxT("AFDataSerie: Zero length array!")); */ }

    AFDataSerie(const size_t unLength, const double* pdbSerie)
      : AFDataHolder<double>(unLength)
    { // wxASSERT_MSG(m_unLength > 0, wxT("AFDataSerie: Zero length array!"));
      SetData(pdbSerie); }

    AFDataSerie(const size_t unLength, const float* pflSerie)
      : AFDataHolder<double>(unLength)
    { SetData(pflSerie);  }
};

//----------------------------------------------------------------------------
// TTimeDataSerie template
//----------------------------------------------------------------------------
template <class T>
class TTimeDataSerie : public AFDataHolder<double>
{
  protected:
    T*     m_pTVector;
    size_t m_unVectorLength;
    int    m_nHandlerType;
    double m_dbRate;    

  public:

    virtual void CalculateDataSerie(const size_t nWindowLength, double& dbTLo, double& dbTHi) = 0;

    void SetData(T* pTVector) { m_pTVector = pTVector; }

    void SetLength(const size_t length) { m_unVectorLength = length; }
    void SetRate(const double dbRate)   { m_dbRate = dbRate; }

    const size_t GetSamplesCount()  { return m_unVectorLength; }
    double GetRate() const { return m_dbRate; }

    void SetHandler(const int nValue) { m_nHandlerType = nValue; }
    int  GetHandler() const { return m_nHandlerType; }

    double GetMax() const { return double(m_unVectorLength)/m_dbRate; }


    TTimeDataSerie(const double dbRate = 44100.0, const int nHandlerType = 0)
     : AFDataHolder<double>(),
       m_pTVector(0),
       m_unVectorLength(0),
       m_nHandlerType(nHandlerType),
       m_dbRate(dbRate)
    {}

    TTimeDataSerie(const size_t unVectorLength, const double dbRate = 44100.0, const int nHandlerType = 0)
    : AFDataHolder<double>(),
      m_pTVector(0),
      m_unVectorLength(unVectorLength),
      m_nHandlerType(nHandlerType),
      m_dbRate(dbRate)
    {}

    TTimeDataSerie(const size_t unVectorLength, T* pTVector, const double dbRate = 44100.0, const int nHandlerType = 0)
    : AFDataHolder<double>(),
      m_pTVector(0),
      m_unVectorLength(unVectorLength),
      m_nHandlerType(nHandlerType),
      m_dbRate(dbRate)
    { SetData(pTVector); }

};

//----------------------------------------------------------------------------
// TSpectrumDataSerie template
//----------------------------------------------------------------------------
template <class TComplex>
class TSpectrumDataSerie : public AFDataHolder<double>
{
  protected:
    TComplex* m_pTCpxSpectrum;
    size_t    m_unSpectrumLength;
    int       m_nHandlerType;
    double    m_dbRate;

  public:

    virtual void CalculateDataSerie(const size_t nWindowLength, const double dbLo, const double dbHi, const bool bIsLog) = 0;

    void SetData(TComplex* pTCpxSpectrum) { m_pTCpxSpectrum = pTCpxSpectrum; }
    void SetRate(const double dbRate) { m_dbRate = dbRate; }

    TComplex* Y() const { return m_pTCpxSpectrum; }
    TComplex* GetSpectrumItem(const size_t unIdx) const { return &(m_pTCpxSpectrum[unIdx]); }

    const size_t GetSpectrumLength()  { return m_unSpectrumLength; }
    double GetRate() const { return m_dbRate; }

    virtual void SetHandlerId(const int nTypeId) { m_nHandlerType = nTypeId; }
    int  GetHandlerId() const { return m_nHandlerType; }

    double GetMax() const { return m_dbRate/2.0; }

// 'ctors ---------
    TSpectrumDataSerie(const double dbRate = 44100.0, const int nHandlerType = 0)
     : AFDataHolder<double>(),
       m_nHandlerType(nHandlerType),
       m_dbRate(dbRate)
    {}

    TSpectrumDataSerie(const size_t unSpectrumLength, const double dbRate = 44100.0, const int nHandlerType = 0)
    : AFDataHolder<double>(),
      m_unSpectrumLength(unSpectrumLength),
      m_nHandlerType(nHandlerType),
      m_dbRate(dbRate)
    {}

    TSpectrumDataSerie(TComplex* pTCpxSpectrum, const size_t unSpectrumLength, const double dbRate = 44100.0, const int nHandlerType = 0)
    : AFDataHolder<double>(),
      m_unSpectrumLength(unSpectrumLength),
      m_nHandlerType(nHandlerType),
      m_dbRate(dbRate)
    { SetData(pTCpxSpectrum); }

};

#endif  // __AURORA_AFDATA_H__

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
