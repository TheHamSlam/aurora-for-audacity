/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Sine Sweep Signal Generator

  gui.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_SineSweepGEN_GUI_H__
#define __AURORA_SineSweepGEN_GUI_H__

#include <wx/wx.h>

#include "sswgen.h"
#include "dialogs.h"
#include "module.h"

//----------------------------------------------------------------------------
// SineSweepGeneratorDialog
//----------------------------------------------------------------------------
class SineSweepGeneratorDialog: public SsgDlg 
{ 
   private:
      SineSweepGenerator* m_pSsg;
     
      wxStaticBitmap *m_pwxbmpAuroraLogo,
                     *m_pwxbmpLogo;
      
   protected:
      // handlers
      // Handlers for SsgDlg events.
      void OnStartFrequencyText( wxCommandEvent& event );
      void OnEndFrequencyText( wxCommandEvent& event );
      void OnSweepDurationText( wxCommandEvent& event );
      void OnAmplitudeText( wxCommandEvent& event );
      void OnSweepChannelsChoice( wxCommandEvent& event );
      void OnLinearSweepRadio( wxCommandEvent& event );
      void OnLogSweepRadio( wxCommandEvent& event );
      void OnPinkSweepRadio( wxCommandEvent& event );
      void OnFadeInText( wxCommandEvent& event );
      void OnFadeInChoice( wxCommandEvent& event );
      void OnFadeOutText( wxCommandEvent& event );
      void OnFadeOutChoice( wxCommandEvent& event );
      void OnSilenceDurationText( wxCommandEvent& event );
      void OnRepetitionsText( wxCommandEvent& event );
      void OnDeltaLText( wxCommandEvent& event );
      void OnControlPulsesCheck( wxCommandEvent& event );
      void OnOk( wxCommandEvent& event );
      void OnCancel( wxCommandEvent& event );
      void OnHelp( wxCommandEvent& event );
    
      // -- Utilities ---

public:      
      // constructors and destructors 
      SineSweepGeneratorDialog(SineSweepGenerator* pSsg, wxWindow *pParent);
};

#endif // __AURORA_SineSweepGEN_GUI__

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
