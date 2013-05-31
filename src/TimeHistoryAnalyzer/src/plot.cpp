/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  plot.cpp

  Simone Campanini

*******************************************************************//**

\class THAPlot
\brief The decay graphic

*//*******************************************************************/

#include "plot.h"

//----------------------------------------------------------------------------
// THAPlot implementation
//----------------------------------------------------------------------------
void THAPlot::ShowSerie(const size_t unIdx)
{
	for(size_t un = 0; un < m_aDataSeries.GetCount(); un++)
	{
		if(un != unIdx)
		    m_aDataSeries[un].Show(false);
		else
			m_aDataSeries[un].Show(true);
	}
}

void THAPlot::ReplaceTimeSerie(const size_t nIdx, double* pdbData, const size_t unLength, const double dbFullScale,
                               wxColour& wxcolLine, wxColour& wxcolBrush)
{
	wxASSERT_MSG(nIdx < m_aDataSeries.GetCount(),
				 wxT("DecayPlot: Replacement unexistent serie (check the index)."));
	wxASSERT_MSG(unLength == m_aDataSeries[nIdx].GetSamplesCount(),
				 wxT("DecayPlot: Replacement serie lenght different than existing one."));
	m_aDataSeries[nIdx].SetData(pdbData);
	m_aDataSeries[nIdx].SetFullScale(dbFullScale);

	wxColour wxcolAuto;
	if(wxcolLine != wxNullColour)
	{
		m_aDataSeries[nIdx].SetLineColour(wxcolLine);
	}
	else
	{   // Choose color automatically
		::AuroraChooseColour(wxcolAuto, int(nIdx));
		m_aDataSeries[nIdx].SetLineColour(wxcolAuto);
	}

	if(wxcolBrush != wxNullColour)
	{
		m_aDataSeries[nIdx].SetFillColour(wxcolBrush);
	}
	else
	{   // Choose color automatically
		::AuroraChooseColour(wxcolAuto, int(nIdx));
		m_aDataSeries[nIdx].SetFillColour(wxcolAuto);
	}

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
