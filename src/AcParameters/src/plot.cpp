/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters

  plot.cpp

  Simone Campanini

*******************************************************************//**

\class APDecayPlot
\brief The decay graphic

*//*******************************************************************/

#include <cstring>
#include <cmath>
#include <vector>

#include <commdefs.h>
#include <audtypes.h>
#include <gpfuncts.h>
#include <octfilt.h>
#include <mroctbd.h>

#include "afacpar.h"
#include "track.h"
#include "plot.h"

//----------------------------------------------------------------------------
// APDecayPlot
//----------------------------------------------------------------------------
void APDecayPlot::AddSerie(AFTimeDataSerie* pData)
{
    m_aDataSeries.Add(pData);
}

void APDecayPlot::AddSerie(AFSample* psmpData, const size_t unLength,
                           const double dbRate,const int nHandlerType,
                           wxColour& wxcolLine, wxColour& wxcolBrush)
{
	int nIdx = int(m_aDataSeries.GetCount());
	m_aDataSeries.Add(new AFTimeDataSerie(unLength, psmpData, dbRate, nHandlerType));

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
		{   // Choose color automatically
			::AuroraChooseColour(wxcolAuto, nIdx);
			m_aDataSeries[nIdx].SetFillColour(wxcolAuto);
		}
	}
}

void APDecayPlot::AddSerie(APAudioTrack& track,
		                   const int nHandlerType,
                           wxColour& wxcolLine,
                           wxColour& wxcolBrush)
{
	AddSerie(track.GetFilteredData(),
			(size_t)track.GetLength(),
	         track.GetFilteredDataRate(),
	         nHandlerType, wxcolLine, wxcolBrush);
}

void APDecayPlot::AddSerie(TSchroederDecay& decay,
		                   const int nHandlerType,
                           wxColour& wxcolLine,
                           wxColour& wxcolBrush)
{
	AddSerie(decay.Get(), (size_t)decay.GetLength(), decay.GetRate(),
			 nHandlerType, wxcolLine, wxcolBrush);
}

void APDecayPlot::ReplaceSerie(const size_t nIdx, AFSample* psmpData, const size_t unLength)
{
	wxASSERT_MSG(nIdx < m_aDataSeries.GetCount(),
				 wxT("APDecayPlot: Replacing unexistent serie (check the index)."));
	wxASSERT_MSG(unLength == m_aDataSeries[nIdx].GetSamplesCount(),
				 wxT("APDecayPlot: Replacement serie's lenght different than existing one."));
	m_aDataSeries[nIdx].SetData(psmpData);
}

void APDecayPlot::ReplaceSerie(const size_t nIdx, APAudioTrack& track)
{
	m_aDataSeries[nIdx].SetData(track.GetFilteredData());
	m_aDataSeries[nIdx].SetLength(size_t(track.GetFilteredDataLength()));
	m_aDataSeries[nIdx].SetRate(track.GetFilteredDataRate());
}

void APDecayPlot::ReplaceSerie(const size_t nIdx, TSchroederDecay& decay)
{
	m_aDataSeries[nIdx].SetData(decay.Get());
	m_aDataSeries[nIdx].SetLength(size_t(decay.GetLength()));
	m_aDataSeries[nIdx].SetRate(decay.GetRate());
}

//----------------------------------------------------------------------------
// APBarPlot implementation
//----------------------------------------------------------------------------

void APBarPlot::AddSerie(const double* adbData, const size_t unLength,
		                  wxColour& wxcolLine, wxColour& wxcolBrush)
{
    int nIdx = int(m_aDataSeries.GetCount());
    m_aDataSeries.Add(new AFDataSerie(unLength, adbData));

    if(int(m_aDataSeries.GetCount()) > nIdx)
    {
    	wxColour wxcolAuto;
    	if(wxcolLine != wxNullColour)
    	{
    		m_aDataSeries[nIdx].SetLineColour(wxcolLine);
    	}
    	else
    	{  // Choose color automatically
            ::AuroraChooseColour(wxcolAuto, nIdx);
            m_aDataSeries[nIdx].SetLineColour(wxcolAuto);
    	}

    	if(wxcolBrush != wxNullColour)
    	{
    		m_aDataSeries[nIdx].SetFillColour(wxcolBrush);
    	}
    	else
    	{	// Choose color automatically
            ::AuroraChooseColour(wxcolAuto, nIdx);
            m_aDataSeries[nIdx].SetFillColour(wxcolAuto);
    	}

    }
}

void APBarPlot::ReplaceSerie(const size_t nIdx, const double* adbData, const size_t unLength)
{
	wxASSERT_MSG(nIdx < m_aDataSeries.GetCount(),
				 wxT("APBarPlot: Replacement unexistent serie (check the index)."));
	wxASSERT_MSG(unLength == m_aDataSeries[nIdx].GetLength(),
			     wxT("APBarPlot: Replacement serie lenght different than existing one."));
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
