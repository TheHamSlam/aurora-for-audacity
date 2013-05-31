/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Aurora Convolver

  plot.cpp

  Simone Campanini

*******************************************************************//**

\class ConvPlot
\brief The decay graphic

*//*******************************************************************/

#include <string.h>

#include <commdefs.h>
#include <gpfuncts.h>

#include "plot.h"

//----------------------------------------------------------------------------
// ConvPlot implementation
//----------------------------------------------------------------------------
void AFTimeDataSerie::Rms(const size_t unWindowLength, double& dbTLo, double& dbTHi)
{
	//Samples that come in a single pixel
	AFSampleCount iMax = (AFSampleCount) floor( ((dbTHi - dbTLo) * m_dbRate)/unWindowLength );

	double dbRms;
	AFSampleCount k, i, smpcT0, smpcT1;
//	printf("\nLo : %f, Hi: %f\n", dbTLo, dbTHi);
	for(k = 0; k < unWindowLength; k++)
	{
		// RMS on 1 px calculation
		dbRms = 0.0;
		smpcT0 = k*iMax + dbTLo * m_dbRate;
		smpcT1 = smpcT0 + iMax;
        if(!m_bIsTimeReversed)
        {
			for(i = smpcT0; i < smpcT1; i++)
			{
			  if(i < m_unVectorLength)
				  dbRms += m_pTVector[i] * m_pTVector[i];
			}
        }
        else
        {
			for(i = smpcT0; i < smpcT1; i++)
			{
			  if(i < m_unVectorLength)
				  dbRms += m_pTVector[(m_unVectorLength-1)-i] * m_pTVector[(m_unVectorLength-1)-i];
			}
        }
		dbRms /= (smpcT1 - smpcT0);

		m_aTData[k] = dB(dbRms); // + m_dbFullScale; // this must be done when plotting!
//		printf("(%d, %d, %f)", int(smpcT0), int(smpcT1), m_aTData[k]);
	}
//    printf("\n"); fflush(stdout);
}

void AFTimeDataSerie::CalculateDataSerie(const size_t unWindowLength, double& dbTLo, double& dbTHi)
{
	// No calculation is needed: use existing datas.
	if(m_unLength != unWindowLength)
	{
		Destroy();
		m_unLength = unWindowLength;
		Init();
	}

    switch(m_nHandlerType)
    {
        case HT_RMS: Rms(unWindowLength, dbTLo, dbTHi); break;
        default:     Rms(unWindowLength, dbTLo, dbTHi); break;
    }

}

bool AFTimeDataSerie::IsOk(const double dbTLo, const double dbTHi)
{
	if((dbTLo < 0) || (dbTHi < 0))    // Time cannot be negative
		return false;

	if(dbTLo >= dbTHi)                // We cannot reverse time!
		return false;

	if((dbTHi-dbTLo) < 1.0/m_dbRate)  // Time interval smaller than
		return false;                 // sampling time are not accepted

	return true;
}

#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfAFTimeDataSerie);

//----------------------------------------------------------------------------
// ConvPlot
//----------------------------------------------------------------------------
void ConvPlot::AddTimeSerie(AFSample* psmpData, const size_t unLength, const double dbRate, const bool bIsTimeReversed,
                            wxColour& wxcolLine, wxColour& wxcolBrush)
{
	int nIdx = int(m_aDataSeries.GetCount());
	m_aDataSeries.Add(new AFTimeDataSerie(unLength, psmpData, dbRate));

	if(int(m_aDataSeries.GetCount()) > nIdx)
	{
		m_aDataSeries[nIdx].SetTimeReversed(bIsTimeReversed);

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

void ConvPlot::ReplaceTimeSerie(const size_t nIdx, AFSample* psmpData, const size_t unLength, const bool bIsTimeReversed)
{
	wxASSERT_MSG(nIdx < m_aDataSeries.GetCount(),
				 wxT("ConvPlot: Replacement unexistent serie (check the index)."));
	wxASSERT_MSG(unLength == m_aDataSeries[nIdx].GetSamplesCount(),
				 wxT("ConvPlot: Replacement serie lenght different than existing one."));
	m_aDataSeries[nIdx].SetData(psmpData);
	m_aDataSeries[nIdx].SetTimeReversed(bIsTimeReversed);
}

// *** constructor
ConvPlot::ConvPlot(  wxWindow *parent, wxWindowID id )
   : AFScope<TArrayOfAFTimeDataSerie, AFTimeDataSerie>(parent, id)
   {}

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
