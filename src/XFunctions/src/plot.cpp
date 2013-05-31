
/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  plot.cpp

  Simone Campanini

*******************************************************************//**

\class XFPlot
\brief The result window plot

*//*******************************************************************/

#include <string.h>

#include <gpfuncts.h>
#include "plot.h"


//----------------------------------------------------------------------------
// XFPlot implementation
//----------------------------------------------------------------------------
bool XFPlot::SetPlotType(const int nPlotType)
{
	// No data serie present
	if(m_aDataSeries.GetCount() == 0)
		return false;

	// Invalid plot type
	if((nPlotType < 0) || (nPlotType > XPT_COHERENCE))
		return false;

	bool bFound = false;
	for(size_t un = 0; un < m_aDataSeries.GetCount(); un++)
	{
		if(m_aDataSeries[un].GetHandlerId() == nPlotType)
		{
			m_aDataSeries[un].Show(true);
			bFound = true;
		}
		else
		{
			m_aDataSeries[un].Show(false);
		}
	}

#ifdef __AUDEBUG__
	if(bFound) printf("[plot] Handler %d found\n", nPlotType);
	else       printf("[plot] Handler %d NOT found\n", nPlotType);
#endif

	return bFound;
}

bool XFPlot::SetPlotTypeByString(wxString& wxszPlotType)
{
    //Search for plot type
    if(wxszPlotType.Find(wxT("Magn"))       != wxNOT_FOUND)
    	return SetPlotType(XPT_MAGNITUDE);
    else if(wxszPlotType.Find(wxT("Phase")) != wxNOT_FOUND)
    	return SetPlotType(XPT_PHASE);
    else if(wxszPlotType.Find(wxT("Real"))  != wxNOT_FOUND)
    	return SetPlotType(XPT_REAL);
    else if(wxszPlotType.Find(wxT("Imag"))  != wxNOT_FOUND)
    	return SetPlotType(XPT_IMAGINARY);
    else if(wxszPlotType.Find(wxT("Left"))  != wxNOT_FOUND)
    	return SetPlotType(XPT_AUTOCORR_L);
    else if(wxszPlotType.Find(wxT("Right")) != wxNOT_FOUND)
    	return SetPlotType(XPT_AUTOCORR_R);
    else if(wxszPlotType.Find(wxT("Coher")) != wxNOT_FOUND)
    	return SetPlotType(XPT_COHERENCE);
    else if(wxszPlotType.Find(wxT("Alpha")) != wxNOT_FOUND)
    	return SetPlotType(XPT_ALPHA);

    return false;
}

bool XFPlot::SetPlotTypeByString(wxString& wxszPlotType, int& nPlotType)
{
	bool bRetVal = SetPlotTypeByString(wxszPlotType);
	if(bRetVal)
	{
		int n = 0;
		while(!m_aDataSeries[n].IsShown()) n++;
        nPlotType = n;
	}
	return bRetVal;
}

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
