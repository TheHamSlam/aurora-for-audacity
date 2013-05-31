/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  PeakVue

  peakvue.h

  Simone Campanini

**********************************************************************/

#include <gpfuncts.h>

#include "peakvue.h"

////////////////////////////////////////////////////////////////////////////////
//
// PVSpectrum implementation
//
////////////////////////////////////////////////////////////////////////////////
void PVSpectrum::Init()
{
	m_Real.Create(m_unLength);
	m_Complex.Create(1 + m_unLength/2);
	m_pDataShuttle->GetSpectralData().Create(1 + m_unLength/2);

	m_FwdPlan    = fftw_plan_dft_r2c_1d(m_unLength, m_Real.GetData(), m_Complex.GetData(), FFTW_ESTIMATE);
    m_bPlanExist = true;
}

void PVSpectrum::Destroy()
{
	if(m_bPlanExist)
	    fftw_destroy_plan(m_FwdPlan);
}

void PVSpectrum::Compute()
{
	TTimeVector tmpMagnitude(1 + m_unLength/2);

	TTimeVector window(m_unLength);
    ::AuroraGenerateWindow(window.GetData(), m_unLength, m_pDataShuttle->GetWindowType());

    m_Complex.Clear();
    m_pDataShuttle->GetSpectralData().Clear();

    size_t dataLength = m_pDataShuttle->GetAudioData().GetLength(),
    	   count = 0, i = 0,
    	   length;

    while(i < dataLength)
    {
    	m_Real.Clear();

    	length = (i + m_unLength < dataLength) ? m_unLength
    			                               : dataLength - i - 1;
    	m_pDataShuttle->GetAudioData().Store(m_Real, length, i);

    	m_Real *= window;

        fftw_execute_dft_r2c(m_FwdPlan, m_Real.GetData(), m_Complex.GetData());

        m_Complex.StoreModule(tmpMagnitude.GetData());
        m_pDataShuttle->GetSpectralData() += tmpMagnitude;

        i += m_unLength/2; // one half overlap TODO: should be parametrized
        count++;
    }
    m_pDataShuttle->GetSpectralData() /= double(count); // this is the average from all spectral samples

}


PVSpectrum::PVSpectrum(PVDataShuttle* pDataShuttle)
: m_pDataShuttle(pDataShuttle),
  m_unLength(size_t(m_pDataShuttle->GetFftLength())),
  m_Complex(),
  m_bPlanExist(false)
{
	Init();
}

PVSpectrum::~PVSpectrum()
{
    Destroy();
}


////////////////////////////////////////////////////////////////////////////////
//
// PVAutocorrelation implementation
//
////////////////////////////////////////////////////////////////////////////////
void PVAutocorrelation::Init()
{
	m_Real.Create(m_unLength);
	m_Complex.Create(1 + m_unLength/2);
	m_DataShuttle.GetAutoCorrelation().Create(1 + m_unLength/2);

	m_FwdPlan = fftw_plan_dft_r2c_1d(m_unLength, m_Real.GetData(),
			                                     m_Complex.GetData(), FFTW_ESTIMATE);
	m_RwdPlan = fftw_plan_dft_c2r_1d(m_unLength, m_Complex.GetData(),
			                                     m_Real.GetData(),    FFTW_ESTIMATE);
    m_bPlanExist = true;

}

void PVAutocorrelation::Destroy()
{
	if(m_bPlanExist)
	{
	    fftw_destroy_plan(m_FwdPlan);
	    fftw_destroy_plan(m_RwdPlan);
	}
}

void PVAutocorrelation::DoAutoSpectrum(TFreqVector& out, TFreqVector& in, const size_t block)
{
    // It applies Welch's method
    //  https://ccrma.stanford.edu/~jos/sasp/Welch_s_Method.html#sec:pwelch
    double dbNorm  = double(block);
    double dbDNorm = double(block + 1);

    fftw_complex *pcpxIn  = in.GetData(),
                 *pcpxOut = out.GetData();

    out.SetDC( (out.GetDC() * dbNorm + in.GetDC() * in.GetDC()) / dbDNorm );
    out.SetNy( (out.GetNy() * dbNorm + in.GetNy() * in.GetNy()) / dbDNorm );

    for(size_t i = 1; i < m_unLength/2; i++)
    {
       // pcpxOut = pfcpxIn * conj(pfcpxIn)
       Re(pcpxOut[i]) = (Re(pcpxOut[i]) * dbNorm +
    		             Re(pcpxIn[i])*Re(pcpxIn[i]) + Im(pcpxIn[i])*Im(pcpxIn[i])) / dbDNorm; //Real
       //Imag. always 0 in the auto-spectrum
    }
}

void PVAutocorrelation::Compute()
{
	TFreqVector autoSpectrum(1 + m_unLength/2); // Autocorrelation vector

	TTimeVector window(m_unLength);
    ::AuroraGenerateWindow(window.GetData(), m_unLength, m_DataShuttle.GetWindowType());

    m_Complex.Clear();
    m_DataShuttle.GetSpectralData().Clear();

    size_t dataLength = m_DataShuttle.GetAudioData().GetLength(),
    	   i = 0, count = 0,
    	   length;

    // TODO fix block stuffs, overlaps
    while(i < dataLength)
    {
    	m_Real.Clear();

    	length = (i + m_unLength < dataLength) ? m_unLength
    			                               : dataLength - i - 1;
    	m_DataShuttle.GetAudioData().Store(m_Real, length, i);

    	m_Real *= window;

        fftw_execute_dft_r2c(m_FwdPlan, m_Real.GetData(), m_Complex.GetData());

        DoAutoSpectrum(autoSpectrum, m_Complex, count);

        i += m_unLength/2; // one half overlap TODO: should be parametrized
        count++;
    }

    fftw_execute_dft_c2r(m_RwdPlan, autoSpectrum.GetData(),
    		                    m_DataShuttle.GetAutoCorrelation().GetData());
    m_DataShuttle.GetAutoCorrelation() /= double(m_unLength);
}

PVAutocorrelation::PVAutocorrelation(PVDataShuttle& dataShuttle)
: m_DataShuttle(dataShuttle),
  m_unLength(size_t(dataShuttle.GetFftLength())),
  m_Complex(),
  m_unLowerBound(0),
  m_unHigherBound(0),
  m_bPlanExist(false)
{
	Init();
}

PVAutocorrelation::~PVAutocorrelation()
{
	Destroy();
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
