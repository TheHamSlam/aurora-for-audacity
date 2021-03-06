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
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include "plot.h"
#include <wx/listbox.h>
#include <wx/scrolwin.h>
#include <wx/grid.h>
#include <wx/splitter.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class AcParDlg
///////////////////////////////////////////////////////////////////////////////
class AcParDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_LOGO_PANEL = 1000,
			ID_OCTAVE_RADIO,
			ID_ONE_THIRD_OCTAVE_RADIO,
			ID_RTE_1_TEXT,
			ID_RTE_2_TEXT,
			ID_ENC_CHECKBOX,
			ID_EDT_CHECKBOX,
			ID_ST_CHECKBOX,
			ID_AVG_CHECKBOX,
			ID_DST_TEXT,
			ID_PEAK_SPL_TEXT,
			ID_2CH_MODE_OMNI_RADIO,
			ID_2CH_MODE_SOUNDFIELD_RADIO,
			ID_2CH_MODE_PU_PROBE_RADIO,
			ID_2CH_MODE_INTENSITY_PROBE_RADIO,
			ID_PROBE_MICS_DIST_STEXT,
			ID_PP_DIST_TEXT,
			ID_SOUND_SPEED_STEXT,
			ID_C_TEXT,
			ID_2CH_MODE_BINAURAL_RADIO,
			ID_IACC_STEXT,
			ID_IACC_CHOICE,
			ID_4CH_MODE_OMNI_RADIO,
			ID_4CH_SOUNDFIELD_STEXT,
			ID_4CH_MODE_SOUNDFIELD_XWYZ_RADIO,
			ID_4CH_MODE_SOUNDFIELD_WYXZ_RADIO,
			ID_APP_RES_CHECKBOX,
			ID_FILE_NAME_TEXT,
			ID_OPEN_FILE_BTN,
		};
		
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline2;
		wxPanel* m_pAnalysisPanel;
		wxRadioButton* m_pwxradioOctave;
		wxRadioButton* m_pwxradioThirdOctave;
		wxPanel* m_pExtrPanel;
		wxStaticText* m_staticText1;
		wxTextCtrl* mUserMinLevelText;
		wxStaticText* m_staticText2;
		wxTextCtrl* mUserMaxLevelText;
		wxStaticText* m_staticText3;
		wxPanel* m_pChecksPanel;
		wxCheckBox* mNoiseCorrectionCheck;
		wxCheckBox* mEDTCheck;
		wxCheckBox* mStageCheck;
		wxCheckBox* mAvgModeCheck;
		wxPanel* m_pLimitsPanel;
		wxStaticText* m_pwxstDST;
		wxTextCtrl* m_pwxtcDST;
		wxStaticText* m_pwxstDSTMu;
		wxStaticText* m_pwxstFS;
		wxTextCtrl* m_pwxtcFullScale;
		wxStaticText* m_pwxstFullScaleMu;
		wxPanel* m_pwxpnlTwoChnls;
		wxRadioButton* mTwoOmniRadio;
		wxRadioButton* mSoundfieldWYRadio;
		wxRadioButton* mPUProbeRadio;
		wxRadioButton* mIntensityProbeRadio;
		wxStaticText* m_pwxstProbeMicsDist;
		wxTextCtrl* m_pwxtcProbeMicsDist;
		wxStaticText* m_pwxstMm;
		wxStaticText* m_pwxstSoundSpeed;
		wxTextCtrl* m_pwxtcSoundSpeed;
		wxStaticText* m_pwxstMs;
		wxRadioButton* mBinauralRadio;
		wxStaticText* mIACCStext;
		wxChoice* mIACCChoice;
		wxPanel* m_pwxpnlFourChnls;
		wxRadioButton* mFourOmniRadio;
		wxStaticText* mFourSoundfieldStext;
		wxRadioButton* mSoundfieldWXYZRadio;
		wxRadioButton* mSoundfieldWYXZRadio;
		wxPanel* m_pAppendPanel;
		wxCheckBox* mAppendResultsCheck;
		wxTextCtrl* mFileNameText;
		wxButton* mOpenFileBtn;
		wxStaticLine* m_pStaticline;
		wxPanel* m_panel6;
		wxButton* m_pwxbtnHelp;
		
		wxButton* mCancelBtn;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnOctaveBandsRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnThirdOctaveBandsRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditRevTimeMinExtreme( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditRevTimeMaxExtreme( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNoiseCorrCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEDTCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnComputeStageParamCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAvgModeCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditDirSoundTrigValue( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditPeakSPLValue( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOmniMicClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSoundfieldClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPUProbeClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnIntensityProbeClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditProbeMicDist( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditCValue( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBinauralClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnIACCChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void On4ChModeOmniRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void On4ChModeSoundfieldWXYZRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void On4ChModeSoundfieldWYXZRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAppendResultsToFile( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditAppendFileName( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOpenFile( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		AcParDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Acoustical Parameters"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~AcParDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GStoreDlg
///////////////////////////////////////////////////////////////////////////////
class GStoreDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_G_DIST_TEXT = 1000,
			ID_RESTORE_BTN,
		};
		
		wxPanel* m_panel7;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxPanel* m_panel8;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrl8;
		wxStaticLine* m_staticline5;
		wxPanel* m_panel9;
		wxButton* m_pwxbtnRestore;
		
		wxButton* m_pwxbtnCancel;
		wxButton* m_pwxbtnStore;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnEditDistanceField( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRestoreDefaultValues( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOK( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GStoreDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Store new G reference value"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~GStoreDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AcParShowDlg
///////////////////////////////////////////////////////////////////////////////
class AcParShowDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_LOGO_PANEL = 1000,
			ID_PLOT_SBOX,
			ID_PLOT_PANEL,
			ID_PLOT,
			ID_BUTTONS_PANEL,
			ID_SETUP_BTN,
			ID_STORE_G_BTN,
			ID_MIC_TYPE_ST,
			ID_CHANNELS_LIST,
			ID_UP_TUSER_LIMIT_STEXT,
			ID_LOW_TUSER_LIMIT_STEXT,
			ID_PARAM_GRID,
		};
		
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline3;
		wxSplitterWindow* m_pHorzSplitter;
		wxScrolledWindow* m_pwxpnlUpper;
		wxPanel* m_pwxpnlPlotDesk;
		AFPlotBase *m_pPlot;
		wxPanel* m_panel15;
		wxButton* m_pwxbtnSetup;
		wxButton* m_pwxbtnSave;
		wxButton* m_pwxbtnCopy;
		wxButton* m_pwxbtnStoreG;
		wxStaticText* m_pwxstSelectedMic;
		wxListBox* mTracksList;
		wxStaticText* m_staticText12;
		wxStaticText* mMaxUserStext;
		wxStaticText* m_staticText14;
		wxStaticText* mMinUserStext;
		wxStaticText* m_staticText16;
		wxPanel* m_pwxpnlLower;
		wxGrid* mGrid;
		wxStaticLine* m_staticline4;
		wxPanel* m_pwxpnlButtons;
		wxButton* mHelpBtn;
		
		wxButton* mCloseBtn;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnSetupButton( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveResults( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCopyResults( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnStoreGRefSig( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnChannelListSelect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnGridCellRightClick( wxGridEvent& event ){ event.Skip(); }
		virtual void OnGraphChange( wxGridEvent& event ){ event.Skip(); }
		virtual void OnGridLabelDoubleClick( wxGridEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		AcParShowDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Acoustical Parameters according to ISO 3382"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~AcParShowDlg();
		void m_pHorzSplitterOnIdle( wxIdleEvent& )
		{
		m_pHorzSplitter->SetSashPosition( 0 );
		m_pHorzSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( AcParShowDlg::m_pHorzSplitterOnIdle ), NULL, this );
		}
		
	
};

#endif //__dialogs__
