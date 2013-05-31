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
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_LOGO_PANEL 1000
#define ID_RATE_ST 1001
#define ID_CHNLS_LBL_ST 1002
#define ID_CHNLS_LBL 1003
#define ID_LENGTH_ST 1004
#define ID_MONO_FILTERING_RADIO 1005
#define ID_STEREO_FILTERING_RADIO 1006
#define ID_DIPOLE_FILTERING_RADIO 1007
#define ID_CROSSTALK_CHECK 1008
#define ID_MULTI_IR_CHECK 1009
#define ID_IR_NUMBER_LABEL_STEXT 1010
#define ID_MULTI_IR_TEXT 1011
#define ID_FILTER_LENGTH_TEXT 1012
#define ID_IRP_TEXT 1013
#define ID_ORP_TEXT 1014
#define ID_LOWER_CUT_FRQ_TEXT 1015
#define ID_HIGHER_CUT_FRQ_TEXT 1016
#define ID_TRANSITION_WIDTH_TEXT 1017
#define ID_FADE_IN_TEXT 1018
#define ID_FADE_OUT_TEXT 1019
#define ID_AVERAGE_MODE_CHOICE 1020
#define ID_AVERAGE_TYPE_LABEL_STEXT 1021
#define ID_AVERAGE_WIDTH_LABEL_STEXT 1022
#define ID_AVERAGE_WIDTH_TEXT 1023
#define ID_AVG_WIDTH_MU_STEXT 1024
#define ID_AUTORANGE_CHECK 1025
#define ID_GAIN_LABEL_STEXT 1026
#define ID_GAIN_MU_STEXT 1027

///////////////////////////////////////////////////////////////////////////////
/// Class KirkebyDlg
///////////////////////////////////////////////////////////////////////////////
class KirkebyDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline2;
		wxPanel* m_panel1;
		wxStaticText* m_pwxstRateLbl;
		wxStaticText* m_pwxstRate;
		wxStaticText* m_pwxstHz;
		wxStaticText* m_pwxstChnlsLbl;
		wxStaticText* m_pwxstChnls;
		wxStaticText* m_pwxstSpc;
		wxStaticText* m_pwxstLengthLbl;
		wxStaticText* m_pwxstLength;
		wxStaticText* m_pwxstSamples;
		wxRadioButton* m_pwxrbMonoFiltering;
		wxRadioButton* m_pwxrbStereoFiltering;
		wxRadioButton* m_pwxrbDipoleFiltering;
		wxCheckBox* mCrossTalkCheck;
		wxCheckBox* mMultiIRsCheck;
		
		wxStaticText* mMultiIRNumberLabelStext;
		wxTextCtrl* mMultiIRText;
		wxPanel* m_panel2;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_pwxtcFilterLength;
		wxStaticText* m_staticText18;
		wxStaticText* m_staticText9;
		wxTextCtrl* mIRPText;
		wxStaticText* m_staticText19;
		wxStaticText* m_staticText10;
		wxTextCtrl* mORPText;
		wxStaticText* m_staticText20;
		wxStaticText* m_staticText11;
		wxTextCtrl* mLowerCutFrqText;
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText12;
		wxTextCtrl* mHigherCutFrqText;
		wxStaticText* m_staticText22;
		wxStaticText* m_staticText13;
		wxTextCtrl* mTransWidthText;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText14;
		wxTextCtrl* mFadeInText;
		wxStaticText* m_staticText24;
		wxStaticText* m_staticText15;
		wxTextCtrl* mFadeOutText;
		wxStaticText* m_staticText25;
		wxPanel* m_panel3;
		wxChoice* mAverageModeChoice;
		wxStaticText* mAverageTypeLabelStext;
		wxChoice* mAverageTypeChoice;
		wxStaticText* m_staticText26;
		wxStaticText* mAverageWidthLabelStext;
		wxTextCtrl* mAverageWidthText;
		wxStaticText* mAvgWidthMUStext;
		wxCheckBox* mAutorangeCheck;
		
		wxStaticText* mGainLabelStext;
		wxTextCtrl* mGainText;
		wxStaticText* mGainMUStext;
		wxStaticLine* m_staticline1;
		wxPanel* m_panel5;
		wxButton* mHelpBtn;
		
		wxButton* mCancelBtn;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnMonoFilteringRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnStereoFilteringRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnDipoleFilteringRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCrossTalkCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMultiIRCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMultiIrText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnIRPText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnORPText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLowerCutFrqText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHigherCutFrqText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnTransitionWidthText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFadeInText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFadeOutText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAverageModeChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAverageTypeChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAverageWidthText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAutorangeCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnGainText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		KirkebyDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aurora Invert Kirkeby"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~KirkebyDlg();
	
};

#endif //__dialogs__
