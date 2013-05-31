/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions
  
  plot.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_XFUNCTIONS_PLOT_H__
#define __AURORA_XFUNCTIONS_PLOT_H__

#include <afscope.h>

#include "data.h"


//----------------------------------------------------------------------------
// XFPlot
//----------------------------------------------------------------------------
class XFPlot: public AFSScope<TArrayOfXFSpectrumDataSerie, XFSpectrumDataSerie>
{
  public:

    enum PlotTypes
    {
        XPT_AUTOCORR_L = XFSpectrumDataSerie::HT_AUTOCORR_L,
        XPT_AUTOCORR_R = XFSpectrumDataSerie::HT_AUTOCORR_R,
        XPT_MAGNITUDE  = XFSpectrumDataSerie::HT_MAGNITUDE,
        XPT_PHASE      = XFSpectrumDataSerie::HT_PHASE,
        XPT_REAL       = XFSpectrumDataSerie::HT_REAL,
        XPT_IMAGINARY  = XFSpectrumDataSerie::HT_IMAGINARY,
        XPT_ALPHA      = XFSpectrumDataSerie::HT_ALPHA,
        XPT_COHERENCE  = XFSpectrumDataSerie::HT_COHERENCE,

        XPT_ADHOC = 0xFFFF
    };

   // --- set/getters
   void AddSerie(XFSpectrumDataSerie* pDataSerie) { AFDataPlot<TArrayOfXFSpectrumDataSerie, XFSpectrumDataSerie>::AddSerie(pDataSerie); } // Bah...

   TArrayOfXFSpectrumDataSerie* GetDataSeriesArray() { return &m_aDataSeries; }

   bool SetPlotType        (const int nPlotType);
   bool SetPlotTypeByString(wxString& wxszPlotType);
   bool SetPlotTypeByString(wxString& wxszPlotType, int& nPlotType);

   // --- ctors
   XFPlot(wxWindow *pParent, wxWindowID id )
    : AFSScope<TArrayOfXFSpectrumDataSerie, XFSpectrumDataSerie>(pParent, id)
   {}
};


#endif  // __AURORA_XFUNCTIONS_PLOT_H__

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
