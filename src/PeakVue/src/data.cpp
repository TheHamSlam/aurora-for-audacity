/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  PeakVue

  data.cpp

  Simone Campanini

**********************************************************************/

#include "data.h"

////////////////////////////////////////////////////////////////////////////////
//
// PVAudioData implementation
//
////////////////////////////////////////////////////////////////////////////////
bool PVAudioData::SetDownsampledData(AFSample* dataSource, AFSampleCount length, const double rate)
{
	wxASSERT_MSG(dataSource != 0,
			     wxT("PVAudioData::SetData() : Invalid data pointer."));
    wxASSERT_MSG(length > 0,
    		      wxT("PVAudioData::SetData() : Data lenght is zero."));
    wxASSERT_MSG(rate > 0.0,
    		      wxT("PVAudioData::SetData() :Sample rata less (or equal) than zero."));

    m_dbRate = 1.0 / (m_dbBlockDuration / 1000.0); // undersampled rate
    size_t blockLength = (size_t)floor((m_dbBlockDuration / 1000.0) * rate);

    Destroy();
    Create(length / blockLength);

    double* dataDest = m_pfUt;
    double peak, value;
    size_t i,j;

	switch(m_nPeakMethod)
	{
        case PM_IN_SIGNO:
        {
            for(i = 0; i < GetLength(); i++)
            {
    	        peak = 0.0;
    	        j = i*blockLength;
                while(j < (i+1)*blockLength)
                {
        		    value = double(dataSource[j]);
        		    peak = (peak > value) ? peak : value;
        		    j++;
        	    }
                dataDest[i] = peak;
            }
        }
        break;

	    case PM_ABSOLUTE:
	    {
	        for(i = 0; i < GetLength(); i++)
	        {
	    	    peak = 0.0;
	    	    j = i*blockLength;
	            while(j < (i+1)*blockLength)
	            {
        		    value = fabs(double(dataSource[j]));
        		    peak = (peak > value) ? peak : value;
        		    j++;
	            }
                dataDest[i] = peak;
	        }
	    }
	    break;

	    case PM_SQUARE:
	    {
	        for(i = 0; i < GetLength(); i++)
	        {
	    	    peak = 0.0;
	    	    j = i*blockLength;
	            while(j < (i+1)*blockLength)
	            {
		            value = double(dataSource[j]*dataSource[j]);
		            peak = (peak > value) ? peak : value;
		            j++;
                }
                dataDest[i] = peak;
            }
	    }
		break;
    }

    return true;
}

PVAudioData::PVAudioData()
: m_dbRate(0),
  m_nPeakMethod(PM_IN_SIGNO),
  m_dbBlockDuration(5.0) // ms
{}

PVAudioData::~PVAudioData()
{ }

////////////////////////////////////////////////////////////////////////////////
//
// PVRealDataSerie implementation
//
////////////////////////////////////////////////////////////////////////////////
/*void PVRealDataSerie::Decimate(const size_t unWindowLength, double& dbTLo, double& dbTHi)
{
    //Samples that come in a single pixel
    AFSampleCount iMax = (AFSampleCount) floor( ((dbTHi - dbTLo) * m_dbRate)/unWindowLength );
    AFSampleCount k, i;

    pVector = m_Data.GetData();
    for(k = 0; k < m_Data.GetLength(); k++)
    {
        if((i = k*iMax) > m_Data.GetLength())
            m_aTData[k] = -200.0; // -infty
        else
            m_aTData[k] = pVector[i] + m_dbFullScale;
    }
}*/

void PVRealDataSerie::SetHandler(const int nTypeId)
{
    wxASSERT_MSG(nTypeId >= HT_RMS && nTypeId <= HT_LINAVG,
                 wxT("PVRealDataSerie::SetHandler: Id out of range."));

    switch(nTypeId)
    {
        case HT_RMS:      m_fpAverage = &PVRealDataSerie::Rms;      break;
        case HT_DECIMATE: m_fpAverage = &PVRealDataSerie::Decimate; break;
        case HT_LINAVG:   m_fpAverage = &PVRealDataSerie::Average;  break;
    }
    m_nHandlerType = nTypeId;
}

double PVRealDataSerie::Rms(const int nLo, const int nHi)
{
	double sum = 0.0;
	for(int i = nLo; i < nHi; i++)
		sum += m_Data.GetData()[i] * m_Data.GetData()[i];

	return sum / double(nHi-nLo);
}

double PVRealDataSerie::Decimate(const int nLo, const int nHi)
{
    return m_Data.GetData()[nLo];
}

double PVRealDataSerie::Average(const int nLo, const int nHi)
{
	double sum = 0.0;
	for(int i = nLo; i < nHi; i++)
		sum += m_Data.GetData()[i];

	return sum / double(nHi-nLo);
}

void PVRealDataSerie::CalculateDataSerie(const size_t unWindowLength, double& dbLo, double& dbHi, const bool bIsLog)
{
    // No calculation is needed: use existing datas.
    if(m_unLength != unWindowLength)
    {
        Destroy();
        m_unLength = unWindowLength;
        Init();
    }

    int k, nT0, nT1;
    if(bIsLog)
	{
		double dbT0, dbT1;
		double dbTLo = (dbLo > 0) ? dbLo : 1.0;
		for(k = 0; k < int(unWindowLength-1); k++)
		{
			dbT0 = pow(dbHi/dbTLo,     k/double(unWindowLength)) * dbTLo;
			dbT1 = pow(dbHi/dbTLo, (k+1)/double(unWindowLength)) * dbTLo;

			nT0 = iround(dbT0 * m_dbRate);
			nT1 = iround(dbT1 * m_dbRate);

			m_aTData[k] = (this->*m_fpAverage)(nT0, nT1);
		}
	}
    else
	{
		// k = Fk * (2.0*L/Fs)
		int nStepWidth = (int) floor( (dbHi - dbLo) * m_dbRate / unWindowLength );

		for(k = 0; k < int(unWindowLength); k++)
		{
			nT0 = k*nStepWidth + dbLo * m_dbRate;
			nT1 = nT0 + nStepWidth;

			m_aTData[k] = (this->*m_fpAverage)(nT0, nT1);
		}
	}
}

bool PVRealDataSerie::IsOk(const double dbLo, const double dbHi)
{
	// Taken from TimeHistoryAnalyzer

    if((dbLo < 0) || (dbHi < 0))    // Time cannot be negative
        return false;

    if(dbLo >= dbHi)                // We cannot reverse time!
        return false;

    if((dbHi-dbLo) < 1.0/m_dbRate)  // Time interval smaller than
        return false;                 // sampling time are not accepted

    return true;
}

PVRealDataSerie::PVRealDataSerie(PVAudioData& data,
		                         const int    handlerType)
 : AFDataHolder<double>(),
   m_Data(dynamic_cast<TTimeVector&>(data)),
   m_dbRate(data.GetRate()),
   m_dbFullScale(120.0),
   m_nHandlerType(handlerType)
{
	SetHandler(handlerType);
}

PVRealDataSerie::PVRealDataSerie(TTimeVector& data,
		                         const double rate,
		                         const int    handlerType)
 : AFDataHolder<double>(),
   m_Data(data),
   m_dbRate(rate),
   m_dbFullScale(120.0),
   m_nHandlerType(handlerType)
{
	SetHandler(handlerType);
}

////////////////////////////////////////////////////////////////////////////////
//
// TArrayOfPVRealDataSerie implementation
//
////////////////////////////////////////////////////////////////////////////////
#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfPVRealDataSerie);

////////////////////////////////////////////////////////////////////////////////
//
// PVSpectrumMagnitudeDataSerie implementation
//
////////////////////////////////////////////////////////////////////////////////
void PVSpectrumMagnitudeDataSerie::CalculateDataSerie(const size_t unWindowLength, double& dbLo, double& dbHi, const bool bIsLog)
{
    // No calculation is needed: use existing datas.
    if(m_unLength != unWindowLength)
    {
        Destroy();
        m_unLength = unWindowLength;
        Init();
    }

    int k, nF0, nF1;
    if(bIsLog)
	{
		double dbF0, dbF1;
		double dbFLo = (dbLo > 0) ? dbLo : 1.0;
		for(k = 0; k < int(unWindowLength-1); k++)
		{
			dbF0 = pow(dbHi/dbFLo, k/double(unWindowLength)) * dbFLo;
			dbF1 = pow(dbHi/dbFLo, (k+1)/double(unWindowLength)) * dbFLo;

			nF0 = iround(dbF0 * m_unSpectrumLength / (m_dbRate/2.0));
			nF1 = iround(dbF1 * m_unSpectrumLength / (m_dbRate/2.0));

			m_aTData[k] = (this->*m_fpAverage)(nF0, nF1);
		}
	}
    else
	{
		// k = Fk * (2.0*L/Fs)
		int nStepWidth = (int) floor( ((dbHi - dbLo) * (2.0*m_unSpectrumLength/m_dbRate))/unWindowLength );

		for(k = 0; k < int(unWindowLength); k++)
		{
			nF0 = k*nStepWidth + dbLo * (2.0*m_unSpectrumLength/m_dbRate);
			nF1 = nF0 + nStepWidth;

			m_aTData[k] = (this->*m_fpAverage)(nF0, nF1);
		}
	}
}

bool PVSpectrumMagnitudeDataSerie::IsOk(const double dbLo, const double dbHi)
{
	// taken from XFunctions

    if(dbLo >= dbHi)               // We cannot reverse time or frequencies!
        return false;

    // In this case we have a frequency horizontal axis
    if(dbLo < 0)                    // Frequencies cannot be negative
        return false;

    if((dbHi-dbLo) < m_dbRate/(2.0*m_unSpectrumLength))  // Frequency intervals smaller than
        return false;                                      // minimum frequency hop are not accepted

    if(dbHi > (m_dbRate/2.0))      // Nyquist frequency  is the maximum accepted.
        return false;

    return true;
}

PVSpectrumMagnitudeDataSerie::PVSpectrumMagnitudeDataSerie(TTimeVector& data,
		                                                   const size_t spectrumLength,
		                                                   const double rate,
		                                                   const int handlerType)
 : PVRealDataSerie(data, rate, handlerType),
   m_unSpectrumLength(spectrumLength)
{  }

////////////////////////////////////////////////////////////////////////////////
//
// TArrayOfPVSpectrumMagnitudeDataSerie implementation
//
////////////////////////////////////////////////////////////////////////////////
#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfPVSpectrumMagnitudeDataSerie);

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
