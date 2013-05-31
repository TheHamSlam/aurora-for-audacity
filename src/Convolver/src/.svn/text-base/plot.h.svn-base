/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Aurora Convolver
  
  plot.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_CONVOLVER_PLOT_H__
#define __AURORA_CONVOLVER_PLOT_H__

#include <afdata.h>
#include <afscope.h>

class AFTimeDataSerie : public TTimeDataSerie<AFSample>
{
  public:
	enum { HT_RMS = 100 };

  private:
    bool m_bIsTimeReversed;

	// Data handlers
	void Rms(const size_t unWindowLength, double& dbTLo, double& dbTHi);

  public:
	void CalculateDataSerie(const size_t nWindowLength, double& dbTLo, double& dbTHi);

	bool IsOk(const double dbTLo, const double dbTHi);

	bool IsTimeReversed() const { return m_bIsTimeReversed; }
	void SetTimeReversed(const bool bValue) { m_bIsTimeReversed = bValue; }

	AFTimeDataSerie(const double dbRate = 44100.0)
	 : TTimeDataSerie<AFSample>(dbRate, HT_RMS)
    {}

	AFTimeDataSerie(const size_t unVectorLength, const double dbRate = 44100.0)
	 : TTimeDataSerie<AFSample>(unVectorLength, dbRate, HT_RMS)
    {}

	AFTimeDataSerie(const size_t unVectorLength, AFSample* psmpVector, const double dbRate = 44100.0)
	 : TTimeDataSerie<AFSample>(unVectorLength, psmpVector, dbRate, HT_RMS)
    {}

};
WX_DECLARE_OBJARRAY(AFTimeDataSerie, TArrayOfAFTimeDataSerie);

//----------------------------------------------------------------------------
// ConvPlot
//----------------------------------------------------------------------------

class ConvPlot: public AFScope <TArrayOfAFTimeDataSerie, AFTimeDataSerie>
{
  public:
//   void SetTimeReversed(const bool bValue);

   void AddTimeSerie(AFSample* psmpData, const size_t unLength, const double dbRate, const bool bIsTimeReversed,
                     wxColour& wxcolLine = wxNullColour, wxColour& wxcolBrush = wxNullColour);
   void ReplaceTimeSerie(const size_t nIdx, AFSample* psmpData, const size_t unLength, const bool bIsTimeReversed);

   // --- ctors
   ConvPlot(  wxWindow *parent, wxWindowID id ); // on vc++ the inlined constructor doesn't link
};

#endif  // __AURORA_CONVOLVER_PLOT__

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
