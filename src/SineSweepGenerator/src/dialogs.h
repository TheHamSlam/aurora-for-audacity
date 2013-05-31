///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dialogs__
#define __dialogs__

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class SsgDlg
///////////////////////////////////////////////////////////////////////////////
class SsgDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_LOGO_PANEL = 1000,
			ID_START_FREQ_TEXT,
			ID_END_FREQ_TEXT,
			ID_DURATION_TEXT,
			ID_AMPLITUDE_TEXT,
			ID_CHANNELS_TEXT,
			ID_LINEAR_SWEEP_RADIO,
			ID_LOG_SWEEP_RADIO,
			ID_PINK_SWEEP_RADIO,
			ID_FADE_IN_TEXT,
			ID_FADE_IN_CHOICE,
			ID_FADE_OUT_TEXT,
			ID_FADE_OUT_CHOICE,
			ID_SILENCE_TEXT,
			ID_REPETITIONS_TEXT,
			ID_DELTA_L_TEXT,
			ID_CTRL_PULSES_CHECK,
		};
		
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline1;
		wxPanel* m_panel1;
		wxStaticText* m_pwxstFrom;
		wxTextCtrl* m_pwxtcFrom;
		wxStaticText* m_pwxstHzTo;
		wxTextCtrl* m_pwxtcTo;
		wxStaticText* m_pwxtcHz;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_pwxtcDuration;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_pwxtcAmplitude;
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_pwxtcChnlsCount;
		wxStaticText* m_staticText18;
		wxRadioButton* m_radioBtn1;
		wxRadioButton* m_radioBtn2;
		wxRadioButton* m_radioBtn3;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_pwxtcFadeIn;
		wxChoice* m_pwxchoiceFadeIn;
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_pwxtcFadeOut;
		wxChoice* m_pwxchoiceFadeOut;
		wxPanel* m_panel3;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_pwxtcSilenceDur;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_pwxtcCyclesCount;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_pwxtcDeltaL;
		wxPanel* m_panel2;
		wxCheckBox* m_pwxchkPulses;
		wxStaticLine* m_staticline2;
		wxPanel* m_pwxpnlBottom;
		wxButton* m_pwxbtnHelp;
		
		wxButton* m_pwxbtnCancel;
		wxButton* m_pwxbtnGenerate;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnStartFrequencyText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEndFrequencyText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSweepDurationText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAmplitudeText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLinearSweepRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLogSweepRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPinkSweepRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFadeInText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFadeInChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFadeOutText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFadeOutChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSilenceDurationText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRepetitionsText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnDeltaLText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnControlPulsesCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		SsgDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Generate Sine Sweep"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~SsgDlg();
	
};

#endif //__dialogs__
