/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  PeakVue

  peakvue.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_PEAKVUE_H__
#define __AURORA_PEAKVUE_H__

#include <afcomplex.h>

#include "data.h"


////////////////////////////////////////////////////////////////////////////////
//
// PVSpectrum declaration
//
////////////////////////////////////////////////////////////////////////////////

class PVSpectrum
{
  protected:
	PVDataShuttle* m_pDataShuttle;

	size_t       m_unLength;

	TTimeVector  m_Real;
	TFreqVector  m_Complex;
	fftw_plan    m_FwdPlan;
	bool         m_bPlanExist;

	// methods
	void Init();
	void Destroy();

  public:
	// interface
	void Compute();

	// 'ctors
    PVSpectrum(PVDataShuttle* pDataShuttle);
    ~PVSpectrum();
};

////////////////////////////////////////////////////////////////////////////////
//
// PVAutocorrelation declaration
//
////////////////////////////////////////////////////////////////////////////////

class PVAutocorrelation
{
protected:
	PVDataShuttle& m_DataShuttle;

	size_t       m_unLength;

	TTimeVector  m_Real;
	TFreqVector  m_Complex;
	fftw_plan    m_FwdPlan,
	             m_RwdPlan;

	size_t       m_unLowerBound,
	             m_unHigherBound;

	bool         m_bPlanExist;

	// methods
	void Init();
	void Destroy();

	void DoAutoSpectrum(TFreqVector& out, TFreqVector& in, const size_t block);

  public:
	// interface
	void Compute();

	PVAutocorrelation(PVDataShuttle& dataShuttle);
	~PVAutocorrelation();
};

#endif //__AURORA_PEAKVUE_H__

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
