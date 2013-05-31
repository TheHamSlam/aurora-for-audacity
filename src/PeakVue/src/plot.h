/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  PeakVue

  plot.h

  Simone Campanini

**********************************************************************/
#ifndef __AURORA_PEAKVUE_PLOT_H__
#define __AURORA_PEAKVUE_PLOT_H__

#include <afscope.h>

#include "data.h"

class PVRealDataPlot :public AFSScope<TArrayOfPVRealDataSerie, PVRealDataSerie>
{
  public:
    void AddSerie(PVRealDataSerie* pDataSerie) { AFDataPlot<TArrayOfPVRealDataSerie, PVRealDataSerie>::AddSerie(pDataSerie); } // Bah...

	TArrayOfPVRealDataSerie& GetDataSeriesArray() { return m_aDataSeries; }

	PVRealDataPlot(wxWindow *pParent, wxWindowID id )
	: AFSScope<TArrayOfPVRealDataSerie, PVRealDataSerie>(pParent, id)
	{}
};


class PVSpectrumMagnitudePlot :public AFSScope<TArrayOfPVSpectrumMagnitudeDataSerie, PVSpectrumMagnitudeDataSerie>
{
  public:
    void AddSerie(PVSpectrumMagnitudeDataSerie* pDataSerie) { AFDataPlot<TArrayOfPVSpectrumMagnitudeDataSerie, PVSpectrumMagnitudeDataSerie>::AddSerie(pDataSerie); } // Bah...

	TArrayOfPVSpectrumMagnitudeDataSerie& GetDataSeriesArray() { return m_aDataSeries; }

	PVSpectrumMagnitudePlot(wxWindow *pParent, wxWindowID id )
	: AFSScope<TArrayOfPVSpectrumMagnitudeDataSerie, PVSpectrumMagnitudeDataSerie>(pParent, id)
	{}
};

#endif //__AURORA_PEAKVUE_PLOT_H__


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
