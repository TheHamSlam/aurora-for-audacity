/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  PeakVue

  gui.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_PEAKVUE_GUI_H__
#define __AURORA_PEAKVUE_GUI_H__

#include "dialogs.h"
#include "data.h"
#include "module.h"

class PeakVueDialog : public PeakVueSetupDlg
{
  private:
	EffectPeakVue*     m_pEpv;
	PVDataShuttle&  m_DataShuttle;

    wxStaticBitmap *m_pwxbmpAuroraLogo,
                   *m_pwxbmpLogo;

  protected:
	virtual void OnCloseDialog( wxCloseEvent& event );
	virtual void OnAnalyze( wxCommandEvent& event );
    virtual void OnHelp( wxCommandEvent& event );
    virtual void OnCloseBtn( wxCommandEvent& event );


  public:
    PeakVueDialog( wxWindow* parent,
    		       wxWindowID id,
    		       EffectPeakVue* pEpv,
    		       PVDataShuttle& dataShuttle);
	~PeakVueDialog();

};

#endif //__AURORA_PEAKVUE_GUI_H__


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
