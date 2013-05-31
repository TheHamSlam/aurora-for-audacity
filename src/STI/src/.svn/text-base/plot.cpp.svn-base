/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  plot.cpp

  Simone Campanini

*******************************************************************//**

\class OctaveBandsPlot
\brief The octave band bars graphic chart

*//*******************************************************************/

#include <gpfuncts.h>

#include "plot.h"

//----------------------------------------------------------------------------
// OctaveBandsPlot implementation
//----------------------------------------------------------------------------
void OctaveBandsPlot::AddSerie(OctaveBandsDataSerie* pSerie,
                               wxColour& wxcolLine, wxColour& wxcolBrush)
{
    int nIdx = int(m_aDataSeries.GetCount());
    m_aDataSeries.Add(pSerie);
    if(int(m_aDataSeries.GetCount()) > nIdx)
    {
		wxColour wxcolAuto;
		if(wxcolLine != wxNullColour)
		{
			m_aDataSeries[nIdx].SetLineColour(wxcolLine);
		}
		else
		{   // Choose color automatically
			::AuroraChooseColour(wxcolAuto, nIdx);
			m_aDataSeries[nIdx].SetLineColour(wxcolAuto);
		}

		if(wxcolBrush != wxNullColour)
		{
			m_aDataSeries[nIdx].SetFillColour(wxcolBrush);
		}
		else
		{
			::AuroraChooseColour(wxcolAuto, nIdx);
			m_aDataSeries[nIdx].SetFillColour(wxcolAuto);
		}
    }
}

void OctaveBandsPlot::AddSerie(const double* adbData, const size_t unLength,
                               wxColour& wxcolLine, wxColour& wxcolBrush)
{
    wxASSERT_MSG(unLength == 12, wxT("OctaveBandsPlot: wrong array size"));
    int nIdx = int(m_aDataSeries.GetCount());
    m_aDataSeries.Add(new OctaveBandsDataSerie(adbData));
    if(int(m_aDataSeries.GetCount()) > nIdx)
    {
		wxColour wxcolAuto;
		if(wxcolLine != wxNullColour)
		{
			m_aDataSeries[nIdx].SetLineColour(wxcolLine);
		}
		else
		{   // Choose color automatically
			::AuroraChooseColour(wxcolAuto, nIdx);
			m_aDataSeries[nIdx].SetLineColour(wxcolAuto);
		}

		if(wxcolBrush != wxNullColour)
		{
			m_aDataSeries[nIdx].SetFillColour(wxcolBrush);
		}
		else
		{
			::AuroraChooseColour(wxcolAuto, nIdx);
			m_aDataSeries[nIdx].SetFillColour(wxcolAuto);
		}
    }
}

void OctaveBandsPlot::ReplaceSerie(const size_t nIdx, const double* adbData, const size_t unLength)
{
	wxASSERT_MSG(nIdx < m_aDataSeries.GetCount(),
				 wxT("OctaveBandsPlot: Replacement unexistent serie (check the index)."));
	wxASSERT_MSG(unLength == m_aDataSeries[nIdx].GetLength(),
			     wxT("OctaveBandsPlot: Replacement serie lenght different than existing one."));
	m_aDataSeries[nIdx].SetData(adbData);
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
