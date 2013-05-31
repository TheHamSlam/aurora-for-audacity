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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>

///////////////////////////////////////////////////////////////////////////

#define ID_LOGO_PANEL 1000
#define ID_START_PNL 1001
#define ID_FS_CALIBRATION_PNL 1002
#define ID_LEFT_FS_TC 1003
#define ID_RIGHT_FS_TC 1004
#define ID_LEFT_CAL_CHOICE 1005
#define ID_LEFT_CAL_TC 1006
#define ID_RIGHT_CAL_CHOICE 1007
#define ID_RIGHT_CAL_TC 1008
#define ID_CALIBRATE_BTN 1009
#define ID_SN_PNL 1010
#define ID_LEFT_BCK_NOISE_CHOICE 1011
#define ID_RIGHT_BCK_NOISE_CHOICE 1012
#define ID_LEFT_SIGNAL_CHOICE 1013
#define ID_RIGHT_SIGNAL_CHOICE 1014
#define ID_SIGNAL_RB 1015
#define ID_SIGNOISE_RB 1016
#define ID_SPL_GRID 1017
#define ID_LOAD_SPL_VALUES_BTN 1018
#define ID_SAVE_SPL_VALUES_BTN 1019
#define ID_IR_PNL 1020
#define ID_LEFT_IR_CHOICE 1021
#define ID_RIGHT_IR_CHOICE 1022
#define ID_FAT_TC 1023
#define ID_GRID_PNL 1024
#define ID_MTF_VALUES_GRID 1025
#define ID_BAND_STI_GRID 1026
#define ID_LEFT_RB 1027
#define ID_RIGHT_RB 1028
#define ID_SNCORR_CB 1029
#define ID_MASK_CB 1030
#define ID_STI_MALE_ST 1031
#define ID_STI_FEMALE_ST 1032
#define ID_RASTI_ST 1033
#define ID_SAVE_BTN 1034

///////////////////////////////////////////////////////////////////////////////
/// Class STISetupDlg
///////////////////////////////////////////////////////////////////////////////
class STISetupDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline3;
		wxNotebook* m_notebook1;
		wxPanel* m_wxNbStartPnl;
		
		wxStaticText* m_wxstWelcomeMsg;
		wxPanel* m_wxNbFSCalibrationPnl;
		
		wxStaticText* m_wxstFsLeftLbl;
		wxTextCtrl* m_pwxtcLeftFs;
		wxStaticText* m_wxstFsRightLbl;
		wxTextCtrl* m_pwxtcRightFs;
		wxStaticText* m_wxstFsRightdB;
		
		wxStaticText* m_wxtcLeftCalLbl;
		wxChoice* m_pwxchLeftCal;
		wxStaticText* m_wxstLeftLevelLbl;
		wxTextCtrl* m_pwxtcLeftLevel;
		wxStaticText* m_wxstLeftLvldB;
		wxStaticText* m_wxtcRightCalLbl;
		wxChoice* m_pwxchRightCal;
		wxStaticText* m_wxstRightLevelLbl;
		wxTextCtrl* m_pwxtcRightLevel;
		wxStaticText* m_wxstRightLvldB;
		wxButton* m_pwxbtnCalibrate;
		wxPanel* m_wxNbSigNoisePnl;
		wxStaticText* m_wxstLeftBckNoiseLbl;
		wxChoice* m_pwxchLeftBckNoise;
		wxStaticText* m_wxstRightBckNoiseLbl;
		wxChoice* m_pwxchRightBckNoise;
		wxStaticText* m_wxstLeftSignalLbl;
		wxChoice* m_pwxchLeftSignal;
		wxStaticText* m_wxstRightSignalLbl;
		wxChoice* m_pwxchRightSignal;
		wxRadioButton* m_wxrbSignal;
		wxRadioButton* m_wxrbSigNoise;
		wxGrid* m_pwxgridSplTable;
		wxPanel* m_panel6;
		wxButton* m_pwxbtnLoadSplValues;
		wxButton* m_pwxbtnSaveSplValues;
		
		wxButton* m_pwxbtnCalculateSPL;
		wxPanel* m_wxNbIRChoosePnl;
		
		wxStaticText* m_wxstLeftIrLbl;
		wxChoice* m_pwxchLeftIr;
		wxStaticText* m_wxstRightIrLbl;
		wxChoice* m_pwxchRightIr;
		wxStaticText* m_wxstFatLbl;
		wxTextCtrl* m_pwxtcFat;
		wxStaticText* m_wxstFatBackLbl;
		wxStaticLine* m_staticline1;
		wxPanel* m_wxButtonsPnl;
		wxButton* m_pwxbtnHelp;
		
		wxButton* m_pwxbtnCancel;
		wxButton* m_pwxbtnOk;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnLeftFullscaleText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRightFullscaleText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCalibLeftChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCalibRefLeftText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCalibRightChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCalibRefRightText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnDoFullscaleCalibration( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNoiseLeftChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNoiseRightChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSignalLeftChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSignalRightChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSignalRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSignalPlusNoiseRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLoadSplValues( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveSplValues( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnComputeSNRatio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLeftIRChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRightIRChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFatText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnComputeSTI( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		STISetupDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aurora STI & Octave Band Analysis"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~STISetupDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class STIShowDlg
///////////////////////////////////////////////////////////////////////////////
class STIShowDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline4;
		wxPanel* m_panel10;
		wxNotebook* m_notebook2;
		wxPanel* m_pwxpnlGridPage;
		wxGrid* m_pwxgridMtfTable;
		wxGrid* m_pwxgridSTITable;
		wxPanel* m_panel11;
		
		wxRadioButton* m_pwxrbLeft;
		
		wxRadioButton* m_pwxrbRight;
		
		wxCheckBox* m_pwxcbSNCorr;
		wxCheckBox* m_pwxcbMaskCorr;
		
		wxStaticText* m_pwxstSTIMaleLbl;
		wxStaticText* m_pwxstSTIMale;
		wxStaticText* m_pwxstSTIFemaleLbl;
		wxStaticText* m_pwxstSTIFemale;
		wxStaticText* m_pwxstRaSTILbl;
		wxStaticText* m_pwxstRaSTI;
		wxStaticText* m_pwxstSTItelLbl;
		wxStaticText* m_pwxstSTItel;
		wxStaticText* m_pwxstSTIpaLbl;
		wxStaticText* m_pwxstSTIpa;
		
		wxButton* m_pwxbtnSave;
		wxStaticLine* m_staticline2;
		wxPanel* m_panel7;
		wxButton* m_wxbtnHelp;
		wxButton* m_wxbtnOk;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnLeftRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRightRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSnCorrectionCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMaskCorrectionCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSave( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		STIShowDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("STI (according to IEC-EN 60268-16:2003)"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~STIShowDlg();
	
};

#endif //__dialogs__
