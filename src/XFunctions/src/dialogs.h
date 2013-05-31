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
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include "plot.h"
#include <wx/scrolwin.h>
#include <wx/splitter.h>

///////////////////////////////////////////////////////////////////////////

#define ID_LOGO_PANEL 1000
#define ID_FFT_SIZE_CHOICE 1001
#define ID_WINDOW_CHOICE 1002
#define ID_XFUNCTION_CHOICE 1003
#define ID_EQUATION_SBMP 1004
#define ID_LAG_LABEL_STEXT 1005
#define ID_LAG_STEXT 1006
#define ID_SW_TUBE_CHECK 1007
#define ID_FREE_FIELD_CHECK 1008
#define ID_SOUNDSPEED_TEXT 1009
#define ID_PROBE_DIST_TEXT 1010
#define ID_FMAX_TEXT 1011
#define ID_ENABLE_FFILTER_CHECK 1012
#define ID_FOLLOW_LEFT_RADIO 1013
#define ID_FOLLOW_RIGHT_RADIO 1014
#define ID_BANDWIDTH_TEXT 1015
#define ID_NORMALIZE_LEFT_CHECK 1016
#define ID_HILBERT_CHECK 1017
#define ID_SHIFT_TO_HALF_CHECK 1018
#define ID_TIME_REV_CHECK 1019
#define ID_COHERENCE_CHECK 1020
#define ID_SAVE_MULTISPECTRUM_CHECK 1021
#define ID_TRIGGER_TEXT 1022
#define ID_DIRAC_CHECK 1023
#define ID_FFT_SIZE_STEXT 1024
#define ID_CHANNELS_STEXT 1025
#define ID_RATE_STEXT 1026
#define ID_NBLOCKS_STEXT 1027
#define ID_TRANSFORM_TYPE_STEXT 1028
#define ID_RMS_LEFT_LABEL_STEXT 1029
#define ID_RMS_LEFT_STEXT 1030
#define ID_RMS_LEFT_dB_STEXT 1031
#define ID_RMS_RIGHT_LABEL_STEXT 1032
#define ID_RMS_RIGHT_STEXT 1033
#define ID_RMS_RIGHT_dB_STEXT 1034
#define ID_RMS_CROSS_LABEL_STEXT 1035
#define ID_RMS_CROSS_STEXT 1036
#define ID_RMS_CROSS_dB_STEXT 1037
#define ID_TIME_OF_FLIGHT_STEXT 1038
#define ID_TRIGGER_TIME_LABEL_STEXT 1039
#define ID_TRIGGER_TIME_STEXT 1040
#define ID_TRIGGER_TIME_AT_STEXT 1041
#define ID_TRIGGER_DELAY_STEXT 1042
#define ID_NCC_MAX_LABEL_STEXT 1043
#define ID_NCC_MAX_STEXT 1044
#define ID_NCC_MAX_AT_STEXT 1045
#define ID_NCC_MAX_DELAY_STEXT 1046
#define ID_SAVE_TO_TIMEDELAY_CHECK 1047
#define ID_FREQUENCY_RANGE_CHOICE 1048
#define ID_LINEAR_SCALE_CHECK 1049
#define ID_EXPORT_ALL_CHECK 1050
#define ID_SAVE_SPECTRUM_BTN 1051
#define ID_COPY_SPECTRUM_BTN 1052
#define ID_EXPORT_WAVEFORMS_CHECK 1053
#define ID_RSIDE_SPLITTER 1054
#define ID_PLOT_SPLITTER 1055
#define ID_FIRST_PLOT_CHOICE 1056
#define ID_UPPER_PLOT 1057
#define ID_SECOND_PLOT_CHOICE 1058
#define ID_LOWER_PLOT 1059

///////////////////////////////////////////////////////////////////////////////
/// Class XFunctionsDlg
///////////////////////////////////////////////////////////////////////////////
class XFunctionsDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline4;
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxChoice* mFftSizeChoice;
		
		wxStaticText* m_staticText2;
		wxChoice* mWindowChoice;
		wxPanel* m_panel2;
		wxChoice* mXFunctionChoice;
		wxPanel* mEquationPanel;
		wxStaticBitmap* mEquationBmp;
		wxStaticText* mLagLabelStext;
		wxStaticText* mLagStext;
		wxPanel* m_panel3;
		wxCheckBox* mSWTubeCheck;
		
		wxCheckBox* mFreeFieldCheck;
		wxStaticText* m_staticText22;
		wxTextCtrl* mSoundSpeedText;
		wxStaticText* m_staticText23;
		wxTextCtrl* mProbeDistText;
		wxStaticText* m_staticText24;
		wxTextCtrl* mFmaxText;
		wxPanel* m_panel4;
		wxCheckBox* mEnableFFilterCheck;
		wxStaticText* m_staticText26;
		wxStaticText* m_staticText27;
		wxRadioButton* mFollowLeftRadio;
		wxRadioButton* mFollowRightRadio;
		wxTextCtrl* mBandwidthText;
		wxPanel* m_panel5;
		wxCheckBox* mNormalizeLeftCheck;
		wxCheckBox* mHilbertCheck;
		wxCheckBox* mShiftToHalfCheck;
		wxCheckBox* mTimeReversalCheck;
		wxCheckBox* mCoherenceCheck;
		wxCheckBox* mSaveMultispectrumCheck;
		wxStaticText* m_staticText28;
		wxTextCtrl* mTriggerText;
		wxCheckBox* mDiracCheck;
		wxStaticLine* m_staticline2;
		wxPanel* m_panel6;
		wxButton* mHelpBtn;
		
		wxButton* mCancelBtn;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnFftSizeChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnWindowChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnXFunctionChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSWTubeCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFreeFieldCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSoundSpeedText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnProbeDistanceText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFmaxText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEnableFollowingFilterCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFollowLeftRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFollowRightRadio( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBandwidthText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNormalizeLeftChannelCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHilbertCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnShiftToHalfWindowCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnTimeReversalCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCoherenceCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveMultispectrumCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnTriggerLevelText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnDiracPulseCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		XFunctionsDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Cross Functions"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~XFunctionsDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class XFunctionsShowDlg
///////////////////////////////////////////////////////////////////////////////
class XFunctionsShowDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline5;
		wxPanel* m_panel7;
		wxPanel* m_panel9;
		wxStaticText* m_staticText29;
		wxStaticText* mFftSizeStext;
		wxStaticText* m_staticText31;
		wxStaticText* m_staticText32;
		wxStaticText* mChannelsStext;
		wxStaticText* m_staticText34;
		wxStaticText* m_staticText35;
		wxStaticText* mRateStext;
		wxStaticText* m_staticText37;
		wxStaticText* m_staticText38;
		wxStaticText* mNblocksStext;
		wxStaticText* m_staticText40;
		wxStaticText* mTransformTypeStext;
		wxStaticText* mRmsLeftLabelStext;
		wxStaticText* mRmsLeftStext;
		wxStaticText* mRmsLeftdBStext;
		wxStaticText* mRmsRightLabelStext;
		wxStaticText* mRmsRightStext;
		wxStaticText* mRmsRightdBStext;
		wxStaticText* mRmsCrossLabelStext;
		wxStaticText* mRmsCrossStext;
		wxStaticText* mRmsCrossdBStext;
		wxStaticLine* m_staticline4;
		wxStaticText* mTimeOfFlightStext;
		wxStaticText* mTriggerTimeLabelStext;
		wxStaticText* mTriggerTimeStext;
		wxStaticText* mTriggerTimeAtStext;
		wxStaticText* mTriggerDelayStext;
		wxStaticText* mNccMaxLabelStext;
		wxStaticText* mNccMaxStext;
		wxStaticText* mNccMaxAtStext;
		wxStaticText* mNccMaxDelayStext;
		wxCheckBox* mSaveToTimeDelayCheck;
		wxStaticText* m_staticText65;
		wxChoice* mFrequencyRangeChoice;
		wxCheckBox* mLinearScaleCheck;
		wxCheckBox* mExportAllCheck;
		wxButton* mSaveBtn;
		wxButton* mCopyBtn;
		wxCheckBox* mExportWaveformsCheck;
		wxSplitterWindow* mRightSideSplitter;
		wxPanel* mRUpperPanel;
		wxSplitterWindow* mPlotSplitter;
		wxPanel* mUpperSplitterPanel;
		wxChoice* mFirstPlotChoice;
		wxScrolledWindow* mUpperPlotScroller;
		XFPlot *mUpperPlot;
		wxPanel* mLowerSplitterPanel;
		wxChoice* mSecondPlotChoice;
		wxScrolledWindow* mLowerPlotScroller;
		XFPlot *mLowerPlot;
		wxStaticLine* m_staticline3;
		wxPanel* m_panel8;
		wxButton* mHelpBtn;
		
		wxButton* mCloseBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnSaveToTimeDelayCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFrequencyRangeChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLinearScaleCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnExportAllSpectrumsCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveSpectrumBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCopySpectrumBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnExportWaveformsCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFirstPlotChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSecondPlotChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		XFunctionsShowDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Cross Functions"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER );
		~XFunctionsShowDlg();
		void mRightSideSplitterOnIdle( wxIdleEvent& )
		{
		mRightSideSplitter->SetSashPosition( 420 );
		mRightSideSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( XFunctionsShowDlg::mRightSideSplitterOnIdle ), NULL, this );
		}
		
		void mPlotSplitterOnIdle( wxIdleEvent& )
		{
		mPlotSplitter->SetSashPosition( 0 );
		mPlotSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( XFunctionsShowDlg::mPlotSplitterOnIdle ), NULL, this );
		}
		
	
};

#endif //__dialogs__
