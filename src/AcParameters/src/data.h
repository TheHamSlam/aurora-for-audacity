/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters
  
  data.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_ACPARAM_DATA_H__
#define __AURORA_ACPARAM_DATA_H__

#include <wx/dynarray.h>

#include <afdata.h>

class APAudioTrack;
class TSchroederDecay;

//----------------------------------------------------------------------------
// AFTimeDataSerie
//----------------------------------------------------------------------------

class AFTimeDataSerie : public TTimeDataSerie<AFSample>
{
  public:
    enum { HT_RMS = 100, HT_DECIMATE };

  private:

    // Data handlers
    void Rms(const size_t unWindowLength, double& dbTLo, double& dbTHi);
    void Decimate(const size_t unWindowLength, double& dbTLo, double& dbTHi);

  public:
    void CalculateDataSerie(const size_t nWindowLength, double& dbTLo, double& dbTHi);

    bool IsOk(const double dbTLo, const double dbTHi);

    AFTimeDataSerie(const double dbRate = 44100.0, const int nHandlerType = HT_DECIMATE)
     : TTimeDataSerie<AFSample>(dbRate, nHandlerType)
    {}

    AFTimeDataSerie(const size_t unVectorLength, const double dbRate = 44100.0, const int nHandlerType = HT_DECIMATE)
     : TTimeDataSerie<AFSample>(unVectorLength, dbRate, nHandlerType)
    {}

    AFTimeDataSerie(const size_t unVectorLength, AFSample* psmpVector, const double dbRate = 44100.0, const int nHandlerType = HT_DECIMATE)
     : TTimeDataSerie<AFSample>(unVectorLength, psmpVector, dbRate, nHandlerType)
    {}

    AFTimeDataSerie(APAudioTrack& track, const int nHandlerType = HT_DECIMATE);
    AFTimeDataSerie(TSchroederDecay& decay, const int nHandlerType = HT_DECIMATE);

};
WX_DECLARE_OBJARRAY(AFTimeDataSerie, TArrayOfAFTimeDataSerie);

//----------------------------------------------------------------------------
// AFDataSerie
//----------------------------------------------------------------------------
WX_DECLARE_OBJARRAY(AFDataSerie, TArrayOfAFDataSerie);

#endif  // __AURORA_ACPARAM_DATA_H__

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
