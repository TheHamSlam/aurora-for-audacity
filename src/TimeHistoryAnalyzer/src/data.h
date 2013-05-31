/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
 Time History Analyzer
  
  data.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_ITUP56_DATA_H__
#define __AURORA_ITUP56_DATA_H__

#include <afdata.h>

//----------------------------------------------------------------------------
// AFTimeDataSerie declaration
//----------------------------------------------------------------------------

class AFTimeDataSerie : public TTimeDataSerie<double>
{
  public:
    enum { HT_RMS = 100, HT_DECIMATE };

  private:
    double m_dbFullScale;

    // Data handlers
    void Rms(const size_t unWindowLength, double& dbTLo, double& dbTHi) { }
    void Decimate(const size_t unWindowLength, double& dbTLo, double& dbTHi);

  public:
    void CalculateDataSerie(const size_t nWindowLength, double& dbTLo, double& dbTHi);

    bool IsOk(const double dbTLo, const double dbTHi);

    void   SetFullScale(const double dbValue) { m_dbFullScale = dbValue; }
    double GetFullScale() const { return m_dbFullScale; }

    AFTimeDataSerie(const double dbRate = 44100.0, const int nHandlerType = HT_DECIMATE)
     : TTimeDataSerie<double>(dbRate, nHandlerType)
    {}

    AFTimeDataSerie(const size_t unVectorLength, const double dbRate = 44100.0, const int nHandlerType = HT_DECIMATE)
     : TTimeDataSerie<double>(unVectorLength, dbRate, nHandlerType)
    {}

    AFTimeDataSerie(const size_t unVectorLength, double* pdbVector, const double dbRate = 44100.0,
                    const double dbFullScale = 120.0, const int nHandlerType = HT_DECIMATE)
     : TTimeDataSerie<double>(unVectorLength, pdbVector, dbRate, nHandlerType),
       m_dbFullScale(dbFullScale)
    {}

};
WX_DECLARE_OBJARRAY(AFTimeDataSerie, TArrayOfAFTimeDataSerie);

#endif  // __AURORA_ITUP56_DATA_H__

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