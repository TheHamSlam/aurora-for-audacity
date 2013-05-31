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
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include "plot.h"
#include <wx/statbox.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class AFTrackSelectorDlg
///////////////////////////////////////////////////////////////////////////////
class AFTrackSelectorDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_LOGO_PANEL = 1000,
			ID_AVAIL_TRACKS_LIST,
			ID_TO_AUDIO_DATA_BTN,
			ID_TO_IRs_BTN,
			ID_AUDIO_DATA_LIST,
			ID_MOVE_UP_BTN,
			ID_TO_LEFT_BTN,
			ID_TO_RIGHT_BTN,
			ID_MOVE_DOWN_BTN,
			ID_REMOVE_BTN,
			ID_IR_LIST,
			ID_MATRIX_MODE_CHECK,
			ID_ONE_FOR_ALL_CHECK,
		};
		
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline5;
		wxPanel* m_panel9;
		wxStaticText* m_staticText12;
		wxStaticLine* m_staticline4;
		wxPanel* m_panel10;
		wxStaticText* m_staticText8;
		wxListCtrl* mAvailableList;
		wxButton* m_button6;
		wxButton* m_button5;
		wxPanel* m_panel4;
		wxStaticText* m_staticText11;
		wxListCtrl* mAudioDataList;
		wxBitmapButton* m_bpButton1;
		wxBitmapButton* m_bpButton2;
		
		wxBitmapButton* m_bpButton3;
		wxBitmapButton* m_bpButton4;
		
		wxButton* m_button9;
		wxStaticText* m_staticText9;
		wxListCtrl* mFilterList;
		wxPanel* m_panel11;
		wxCheckBox* mMatrixModeCheck;
		
		wxCheckBox* mOneForAllCheck;
		wxStaticLine* m_staticline1;
		wxPanel* m_panel5;
		wxPanel* m_panel6;
		wxButton* mHelpBtn;
		
		wxButton* mCancelBtn;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAvailableDragInit( wxListEvent& event ){ event.Skip(); }
		virtual void ToAudioDataBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnToIRsBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAudioDataDragInit( wxListEvent& event ){ event.Skip(); }
		virtual void OnMoveUpBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnToLeftBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnToRightBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMoveDownBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRemoveBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFilterDragInit( wxListEvent& event ){ event.Skip(); }
		virtual void OnMatrixModeCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOneForAllCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOK( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		AFTrackSelectorDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aurora Convolver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~AFTrackSelectorDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AFConvolverDlg
///////////////////////////////////////////////////////////////////////////////
class AFConvolverDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_LOGO_PANEL = 1000,
			ID_PLOT,
			ID_FULL_AUTORANGE_CHECK,
			ID_FB_AUTORANGE,
			ID_GAIN_LABEL_ST,
			ID_GAIN_TEXT,
			ID_TREV_IR_CHECK,
			ID_CROSSTALK_CHECK,
			ID_PRES_LENGTH_CHECK,
			ID_AUDIO_DATA_STEXT,
			ID_IR_DATA_STEXT,
			ID_FFT_SIZE_STEXT,
			ID_MODE_STEXT,
		};
		
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline6;
		wxPanel* m_panel8;
		wxStaticText* m_staticText11;
		wxStaticLine* m_staticline3;
		wxPanel* m_panel1;
		ConvPlot *mPlot;
		wxPanel* m_panel2;
		wxCheckBox* mFullAutorangeCheck;
		wxCheckBox* mFBAutorangeCheck;
		
		wxStaticText* mGainStext;
		wxTextCtrl* mGainText;
		wxStaticText* mdBStext;
		wxCheckBox* mTimeReversedCheck;
		wxCheckBox* mCrossTalkCheck;
		wxCheckBox* mPreserveLengthCheck;
		wxPanel* m_panel3;
		wxStaticText* m_staticText2;
		wxStaticText* mAudioDataStext;
		wxStaticText* m_staticText4;
		wxStaticText* mFilterStext;
		wxStaticText* m_staticText6;
		wxStaticText* mFftSizeStext;
		wxStaticText* m_staticText14;
		wxStaticText* mModeStext;
		wxStaticLine* m_staticline2;
		wxPanel* m_panel7;
		wxButton* mHelpBtn;
		
		wxButton* mCancelBtn;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnFullAutorangeCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFirstBlockAutorangeCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnGainText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnTimeReverseIrCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCrosstalkCancelCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPreserveLengthCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		AFConvolverDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aurora Convolver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~AFConvolverDlg();
	
};

#endif //__dialogs__
