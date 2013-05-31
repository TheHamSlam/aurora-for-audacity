/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  data.cpp

  Simone Campanini

*******************************************************************//**

\class XFSpectrumDataSerie
\brief The result window plot

*//*******************************************************************/

#include <afplot.h>
#include "data.h"

/*
    Logarithmic axis formulae:
    
    fk= pow(fend/fstart, k/L) * fstart
    k = L*log10(fk/fstart)/log10(fend/fstart)
*/

void XFSpectrumDataSerie::SetHandlerId(const int nTypeId)
{
    wxASSERT_MSG(nTypeId >= 0 && nTypeId <= HT_COHERENCE,
                 wxT("XFSpectrumDataSerie::SetHandler: Id out of range."));

    switch(nTypeId)
    {
        case HT_AUTOCORR_L: m_fpAverage = &XFSpectrumDataSerie::Rll;       break;
        case HT_AUTOCORR_R: m_fpAverage = &XFSpectrumDataSerie::Rrr;       break;
        case HT_MAGNITUDE:  m_fpAverage = &XFSpectrumDataSerie::Magn;      break;
        case HT_PHASE:      m_fpAverage = &XFSpectrumDataSerie::Phaze;     break;
        case HT_REAL:       m_fpAverage = &XFSpectrumDataSerie::SqrReal;   break;
        case HT_IMAGINARY:  m_fpAverage = &XFSpectrumDataSerie::SqrImag;   break;
        case HT_ALPHA:      m_fpAverage = &XFSpectrumDataSerie::Alpha;     break;
        case HT_COHERENCE:  m_fpAverage = &XFSpectrumDataSerie::Coherence; break;
    }
    m_nHandlerType = nTypeId;
}

double XFSpectrumDataSerie::Rll(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return dB(SqrMod(m_pfcpxGll[nF0]));

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
            dbSum += SqrMod(m_pfcpxGll[i]);
    }
    return dB(dbSum/(nF1 - nF0));
}

double XFSpectrumDataSerie::Rrr(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return dB(SqrMod(m_pfcpxGrr[nF0]));

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
            dbSum += SqrMod(m_pfcpxGrr[i]);
    }
    return dB(dbSum/(nF1 - nF0));
}

double XFSpectrumDataSerie::Magn(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return dB(Magnitude(m_pTCpxSpectrum[nF0]));

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
            dbSum += Magnitude(m_pTCpxSpectrum[i]);
    }
    return dB(dbSum/(nF1 - nF0));
}

double XFSpectrumDataSerie::Phaze(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return DegPhase(m_pTCpxSpectrum[nF0]);

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
            dbSum += DegPhase(m_pTCpxSpectrum[i]);
    }
    return dbSum/(nF1 - nF0);
}

double XFSpectrumDataSerie::SqrReal(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return dB(Re(m_pTCpxSpectrum[nF0])*Re(m_pTCpxSpectrum[nF0]));

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
            dbSum += Re(m_pTCpxSpectrum[i])*Re(m_pTCpxSpectrum[i]);
    }
    return dB(dbSum/(nF1 - nF0));
}

double XFSpectrumDataSerie::SqrImag(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return dB(Im(m_pTCpxSpectrum[nF0])*Im(m_pTCpxSpectrum[nF0]));

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
            dbSum += Im(m_pTCpxSpectrum[i])*Im(m_pTCpxSpectrum[i]);
    }
    return dB(dbSum/(nF1 - nF0));
}

double XFSpectrumDataSerie::Alpha(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return 2.0*fabs(Re(m_pfcpxGlr[nF0])) /
                   ( (Re(m_pfcpxGll[nF0]) + Re(m_pfcpxGrr[nF0]))/2.0 + fabs(Re(m_pfcpxGlr[nF0])) );

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
            dbSum += 2.0*fabs(Re(m_pfcpxGlr[i])) /
                           ( (Re(m_pfcpxGll[i]) + Re(m_pfcpxGrr[i]))/2.0 + fabs(Re(m_pfcpxGlr[i])) );
    }
    return dbSum/(nF1 - nF0);
}

double XFSpectrumDataSerie::Coherence(const int nF0, const int nF1)
{
    if(nF0 == nF1)
        return Re(m_pTCpxSpectrum[nF0]);

    double dbSum = 0.0;
    for(int i = nF0; i < nF1; i++)
    {
        if(i < int(m_unSpectrumLength))
              dbSum += Re(m_pTCpxSpectrum[i]);
    }
    return dbSum/(nF1 - nF0);
}

void XFSpectrumDataSerie::CalculateDataSerie(const size_t unWindowLength, const double dbLo, const double dbHi, const bool bIsLog)
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

bool XFSpectrumDataSerie::IsOk(const double dbXLo, const double dbXHi)
{
    if(dbXLo >= dbXHi)               // We cannot reverse time or frequencies!
        return false;

    // In this case we have a frequency horizontal axis
    if(dbXLo < 0)                    // Frequencies cannot be negative
        return false;

    if((dbXHi-dbXLo) < m_dbRate/(2.0*m_unSpectrumLength))  // Frequency intervals smaller than
        return false;                                      // minimum frequency hop are not accepted

    if(dbXHi > (m_dbRate/2.0))      // Nyquist frequency  is the maximum accepted.
        return false;

    return true;
}

XFSpectrumDataSerie& XFSpectrumDataSerie::operator=(XFSpectrumDataSerie& Right)
{
    if(this == &Right) return *this;

    m_pTCpxSpectrum    = Right.m_pTCpxSpectrum;
    m_unSpectrumLength = Right.m_unSpectrumLength;
    m_nHandlerType     = Right.m_nHandlerType;
    m_dbRate           = Right.m_dbRate;

    m_pfcpxGll = Right.m_pfcpxGll;
    m_pfcpxGrr = Right.m_pfcpxGrr;
    m_pfcpxGlr = Right.m_pfcpxGlr;
    m_pfcpxC   = Right.m_pfcpxC;

    SetLineColour(Right.GetLineColour());
    SetFillColour(Right.GetFillColour());

    Show(Right.IsShown());

    return *this;
}

XFSpectrumDataSerie* XFSpectrumDataSerie::Clone()
{
    XFSpectrumDataSerie* pDataSerie = new XFSpectrumDataSerie();
    if(pDataSerie)
    {
        *pDataSerie = *this;
        return pDataSerie;
    }
    return 0;
}

#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfXFSpectrumDataSerie);

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
