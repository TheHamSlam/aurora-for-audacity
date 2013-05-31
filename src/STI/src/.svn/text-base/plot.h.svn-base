/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator
  
  plot.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_STI_PLOT_H__
#define __AURORA_STI_PLOT_H__

#include <afcharts.h>

#include "data.h"

//----------------------------------------------------------------------------
// OctaveBandsPlot
//----------------------------------------------------------------------------
class OctaveBandsPlot : public AFBarPlot<TArrayOfOctaveBandsDataSerie, OctaveBandsDataSerie>
{
  public:
	void ToggleSerieVisibility(const int nIdx) { m_aDataSeries[nIdx].ToggleVisibility(); }

    void AddSerie(OctaveBandsDataSerie* pSerie,
                  wxColour& wxcolLine = wxNullColour, wxColour& wxcolBrush = wxNullColour);
    void AddSerie(const double* adbData, const size_t unLength,
                  wxColour& wxcolLine = wxNullColour, wxColour& wxcolBrush = wxNullColour);
    
    void ReplaceSerie(const size_t nIdx, const double* adbData, const size_t unLength);


    // A sort of alias, just to make things easier...
    AFCategoriesAxis* GetBandsAxis () { return GetCategoriesAxis(); }


    OctaveBandsPlot(wxWindow* pParent, wxWindowID id,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize)
    : AFBarPlot<TArrayOfOctaveBandsDataSerie, OctaveBandsDataSerie>(pParent, id, pos, size)
    {}
};

//----------------------------------------------------------------------------
// STIPlot
//----------------------------------------------------------------------------
class STIPlot : public AFLinePlot<TArrayOfAFDataSerie, AFDataSerie>
{
  public:

   void AddSerie(AFDataSerie* pSerie) { AFDataPlot<TArrayOfAFDataSerie, AFDataSerie>::AddSerie(pSerie); } // Bah...

   AFAxis*           GetSTIAxis() { return GetLevelAxis(); }
   AFCategoriesAxis* GetFrqAxis() { return GetCategoriesAxis(); }


   STIPlot(wxWindow *pParent, wxWindowID id,
           const wxPoint& pos = wxDefaultPosition,
           const wxSize& size = wxDefaultSize)
    : AFLinePlot<TArrayOfAFDataSerie, AFDataSerie>(pParent, id, pos, size)
   {}

};

#endif  //__AURORA_STI_PLOT_H__

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


