/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
 Time History Analyzer
  
  plot.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_ITUP56_PLOT_H__
#define __AURORA_ITUP56_PLOT_H__

#include <afscope.h>
#include "data.h"

//----------------------------------------------------------------------------
// THAPlot declaration
//----------------------------------------------------------------------------
class THAPlot: public AFScope <TArrayOfAFTimeDataSerie, AFTimeDataSerie>
{

 public:
   // --- set/getters
   void ShowSerie(const size_t nIdx);

   void ReplaceTimeSerie(const size_t nIdx, double* pdbData, const size_t unLength, const double dbFullScale,
                         wxColour& wxcolLine = wxNullColour, wxColour& wxcolBrush = wxNullColour);

   // --- ctors
   THAPlot(wxWindow *parent, wxWindowID id,
           const wxPoint& pos = wxDefaultPosition,
           const wxSize& size = wxDefaultSize)
    : AFScope<TArrayOfAFTimeDataSerie, AFTimeDataSerie>(parent, id, pos, size)
   {}
};

#endif  // __AURORA_ITUP56_PLOT__

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
