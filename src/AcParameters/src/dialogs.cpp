///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

///////////////////////////////////////////////////////////////////////////

AcParDlg::AcParDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 300,500 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Common options") ), wxVERTICAL );
	
	m_pAnalysisPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_pAnalysisPanel, wxID_ANY, wxT("Analysis") ), wxHORIZONTAL );
	
	m_pwxradioOctave = new wxRadioButton( m_pAnalysisPanel, ID_OCTAVE_RADIO, wxT("Octave Bands"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	m_pwxradioOctave->SetValue( true ); 
	sbSizer9->Add( m_pwxradioOctave, 0, wxALL, 5 );
	
	m_pwxradioThirdOctave = new wxRadioButton( m_pAnalysisPanel, ID_ONE_THIRD_OCTAVE_RADIO, wxT("One-Third Octave Bands"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer9->Add( m_pwxradioThirdOctave, 0, wxALL, 5 );
	
	m_pAnalysisPanel->SetSizer( sbSizer9 );
	m_pAnalysisPanel->Layout();
	sbSizer9->Fit( m_pAnalysisPanel );
	sbSizer7->Add( m_pAnalysisPanel, 0, wxALL|wxEXPAND, 5 );
	
	m_pExtrPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_pExtrPanel, wxID_ANY, wxT("User Defined Reverberation Time Extremes") ), wxVERTICAL );
	
	sbSizer1->SetMinSize( wxSize( 290,-1 ) ); 
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_pExtrPanel, wxID_ANY, wxT("("), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer10->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mUserMinLevelText = new wxTextCtrl( m_pExtrPanel, ID_RTE_1_TEXT, wxT("-5.0"), wxDefaultPosition, wxSize( 60,-1 ), wxTE_RIGHT );
	bSizer10->Add( mUserMinLevelText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( m_pExtrPanel, wxID_ANY, wxT("dB, "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer10->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mUserMaxLevelText = new wxTextCtrl( m_pExtrPanel, ID_RTE_2_TEXT, wxT("-15.0"), wxDefaultPosition, wxSize( 60,-1 ), wxTE_RIGHT );
	bSizer10->Add( mUserMaxLevelText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( m_pExtrPanel, wxID_ANY, wxT("dB )"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer10->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer10, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pExtrPanel->SetSizer( sbSizer1 );
	m_pExtrPanel->Layout();
	sbSizer1->Fit( m_pExtrPanel );
	sbSizer7->Add( m_pExtrPanel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_pChecksPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	mNoiseCorrectionCheck = new wxCheckBox( m_pChecksPanel, ID_ENC_CHECKBOX, wxT("Enable Noise Correction"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	
	bSizer2->Add( mNoiseCorrectionCheck, 0, wxALL, 5 );
	
	mEDTCheck = new wxCheckBox( m_pChecksPanel, ID_EDT_CHECKBOX, wxT("EDT without linear regression"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	
	bSizer2->Add( mEDTCheck, 0, wxALL, 5 );
	
	mStageCheck = new wxCheckBox( m_pChecksPanel, ID_ST_CHECKBOX, wxT("Compute Stage Parameters (ST)"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	
	bSizer2->Add( mStageCheck, 0, wxALL, 5 );
	
	mAvgModeCheck = new wxCheckBox( m_pChecksPanel, ID_AVG_CHECKBOX, wxT("Average Mode instead of A-weight"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	
	bSizer2->Add( mAvgModeCheck, 0, wxALL, 5 );
	
	m_pChecksPanel->SetSizer( bSizer2 );
	m_pChecksPanel->Layout();
	bSizer2->Fit( m_pChecksPanel );
	sbSizer7->Add( m_pChecksPanel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pLimitsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_pwxstDST = new wxStaticText( m_pLimitsPanel, wxID_ANY, wxT("Direct Sound Trigger (below FS):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstDST->Wrap( -1 );
	fgSizer1->Add( m_pwxstDST, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcDST = new wxTextCtrl( m_pLimitsPanel, ID_DST_TEXT, wxT("20.0"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	fgSizer1->Add( m_pwxtcDST, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstDSTMu = new wxStaticText( m_pLimitsPanel, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstDSTMu->Wrap( -1 );
	fgSizer1->Add( m_pwxstDSTMu, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstFS = new wxStaticText( m_pLimitsPanel, wxID_ANY, wxT("Peak SPL value (FullScale):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstFS->Wrap( -1 );
	fgSizer1->Add( m_pwxstFS, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcFullScale = new wxTextCtrl( m_pLimitsPanel, ID_PEAK_SPL_TEXT, wxT("120.0"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	fgSizer1->Add( m_pwxtcFullScale, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstFullScaleMu = new wxStaticText( m_pLimitsPanel, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstFullScaleMu->Wrap( -1 );
	fgSizer1->Add( m_pwxstFullScaleMu, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pLimitsPanel->SetSizer( fgSizer1 );
	m_pLimitsPanel->Layout();
	fgSizer1->Fit( m_pLimitsPanel );
	sbSizer7->Add( m_pLimitsPanel, 1, wxEXPAND | wxALL, 5 );
	
	bSizer22->Add( sbSizer7, 1, wxEXPAND|wxALL, 5 );
	
	bSizer21->Add( bSizer22, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlTwoChnls = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlTwoChnls, wxID_ANY, wxT("Two Channels Mode") ), wxVERTICAL );
	
	mTwoOmniRadio = new wxRadioButton( m_pwxpnlTwoChnls, ID_2CH_MODE_OMNI_RADIO, wxT("2 Omidirectional Microphones"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	mTwoOmniRadio->SetValue( true ); 
	mTwoOmniRadio->Enable( false );
	
	sbSizer2->Add( mTwoOmniRadio, 0, wxALL, 5 );
	
	mSoundfieldWYRadio = new wxRadioButton( m_pwxpnlTwoChnls, ID_2CH_MODE_SOUNDFIELD_RADIO, wxT("Soundfield(R) Microphone (WY)"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	mSoundfieldWYRadio->Enable( false );
	
	sbSizer2->Add( mSoundfieldWYRadio, 0, wxALL, 5 );
	
	mPUProbeRadio = new wxRadioButton( m_pwxpnlTwoChnls, ID_2CH_MODE_PU_PROBE_RADIO, wxT("Omni/Eight microphone - PU probe"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	mPUProbeRadio->Enable( false );
	
	sbSizer2->Add( mPUProbeRadio, 0, wxALL, 5 );
	
	mIntensityProbeRadio = new wxRadioButton( m_pwxpnlTwoChnls, ID_2CH_MODE_INTENSITY_PROBE_RADIO, wxT("P-P Sound Intensity Probe"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	mIntensityProbeRadio->Enable( false );
	
	sbSizer2->Add( mIntensityProbeRadio, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxstProbeMicsDist = new wxStaticText( m_pwxpnlTwoChnls, ID_PROBE_MICS_DIST_STEXT, wxT("d:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_pwxstProbeMicsDist->Wrap( -1 );
	m_pwxstProbeMicsDist->Enable( false );
	
	bSizer5->Add( m_pwxstProbeMicsDist, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcProbeMicsDist = new wxTextCtrl( m_pwxpnlTwoChnls, ID_PP_DIST_TEXT, wxT("12.0"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	m_pwxtcProbeMicsDist->Enable( false );
	m_pwxtcProbeMicsDist->SetToolTip( wxT("Distance in millimetres between Sound Intensity Probe microphones.") );
	
	bSizer5->Add( m_pwxtcProbeMicsDist, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstMm = new wxStaticText( m_pwxpnlTwoChnls, wxID_ANY, wxT("mm,"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstMm->Wrap( -1 );
	m_pwxstMm->Enable( false );
	
	bSizer5->Add( m_pwxstMm, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstSoundSpeed = new wxStaticText( m_pwxpnlTwoChnls, ID_SOUND_SPEED_STEXT, wxT("c:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSoundSpeed->Wrap( -1 );
	m_pwxstSoundSpeed->Enable( false );
	
	bSizer5->Add( m_pwxstSoundSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcSoundSpeed = new wxTextCtrl( m_pwxpnlTwoChnls, ID_C_TEXT, wxT("340.0"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	m_pwxtcSoundSpeed->Enable( false );
	m_pwxtcSoundSpeed->SetToolTip( wxT("Sound speed in m/s.") );
	
	bSizer5->Add( m_pwxtcSoundSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstMs = new wxStaticText( m_pwxpnlTwoChnls, wxID_ANY, wxT("m/s."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstMs->Wrap( -1 );
	m_pwxstMs->Enable( false );
	
	bSizer5->Add( m_pwxstMs, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer5, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mBinauralRadio = new wxRadioButton( m_pwxpnlTwoChnls, ID_2CH_MODE_BINAURAL_RADIO, wxT("Binaural Dummy Head"), wxDefaultPosition, wxDefaultSize, 0 );
	mBinauralRadio->Enable( false );
	
	sbSizer2->Add( mBinauralRadio, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	mIACCStext = new wxStaticText( m_pwxpnlTwoChnls, ID_IACC_STEXT, wxT("IACC integration"), wxDefaultPosition, wxDefaultSize, 0 );
	mIACCStext->Wrap( -1 );
	mIACCStext->Enable( false );
	
	bSizer6->Add( mIACCStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mIACCChoiceChoices[] = { wxT("0-80 ms (Early)"), wxT("80-\u221E ms (Late)"), wxT("0-\u221E ms (All)") };
	int mIACCChoiceNChoices = sizeof( mIACCChoiceChoices ) / sizeof( wxString );
	mIACCChoice = new wxChoice( m_pwxpnlTwoChnls, ID_IACC_CHOICE, wxDefaultPosition, wxDefaultSize, mIACCChoiceNChoices, mIACCChoiceChoices, 0 );
	mIACCChoice->SetSelection( 2 );
	mIACCChoice->Enable( false );
	
	bSizer6->Add( mIACCChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer6, 0, 0, 5 );
	
	m_pwxpnlTwoChnls->SetSizer( sbSizer2 );
	m_pwxpnlTwoChnls->Layout();
	sbSizer2->Fit( m_pwxpnlTwoChnls );
	bSizer23->Add( m_pwxpnlTwoChnls, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_pwxpnlFourChnls = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlFourChnls, wxID_ANY, wxT("Four Channels Mode") ), wxVERTICAL );
	
	mFourOmniRadio = new wxRadioButton( m_pwxpnlFourChnls, ID_4CH_MODE_OMNI_RADIO, wxT("4 Omnidirectional Microphones"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	mFourOmniRadio->SetValue( true ); 
	mFourOmniRadio->Enable( false );
	
	sbSizer6->Add( mFourOmniRadio, 0, wxALL, 5 );
	
	mFourSoundfieldStext = new wxStaticText( m_pwxpnlFourChnls, ID_4CH_SOUNDFIELD_STEXT, wxT("Soundfield(R) Microphone:"), wxDefaultPosition, wxDefaultSize, 0 );
	mFourSoundfieldStext->Wrap( -1 );
	mFourSoundfieldStext->Enable( false );
	
	sbSizer6->Add( mFourSoundfieldStext, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	mSoundfieldWXYZRadio = new wxRadioButton( m_pwxpnlFourChnls, ID_4CH_MODE_SOUNDFIELD_XWYZ_RADIO, wxT("WX YZ"), wxDefaultPosition, wxDefaultSize, 0 );
	mSoundfieldWXYZRadio->Enable( false );
	
	bSizer19->Add( mSoundfieldWXYZRadio, 0, wxALL, 5 );
	
	mSoundfieldWYXZRadio = new wxRadioButton( m_pwxpnlFourChnls, ID_4CH_MODE_SOUNDFIELD_WYXZ_RADIO, wxT("WY XZ"), wxDefaultPosition, wxDefaultSize, 0 );
	mSoundfieldWYXZRadio->Enable( false );
	
	bSizer19->Add( mSoundfieldWYXZRadio, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer6->Add( bSizer19, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pwxpnlFourChnls->SetSizer( sbSizer6 );
	m_pwxpnlFourChnls->Layout();
	sbSizer6->Fit( m_pwxpnlFourChnls );
	bSizer23->Add( m_pwxpnlFourChnls, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer21->Add( bSizer23, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer21, 1, wxEXPAND, 5 );
	
	m_pAppendPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	mAppendResultsCheck = new wxCheckBox( m_pAppendPanel, ID_APP_RES_CHECKBOX, wxT("Append Results to File:"), wxDefaultPosition, wxSize( -1,20 ), 0 );
	
	bSizer7->Add( mAppendResultsCheck, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	mFileNameText = new wxTextCtrl( m_pAppendPanel, ID_FILE_NAME_TEXT, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	mFileNameText->Enable( false );
	
	bSizer8->Add( mFileNameText, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mOpenFileBtn = new wxButton( m_pAppendPanel, ID_OPEN_FILE_BTN, wxT("..."), wxDefaultPosition, wxSize( 30,25 ), 0 );
	mOpenFileBtn->Enable( false );
	
	bSizer8->Add( mOpenFileBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( bSizer8, 1, wxEXPAND, 5 );
	
	m_pAppendPanel->SetSizer( bSizer7 );
	m_pAppendPanel->Layout();
	bSizer7->Fit( m_pAppendPanel );
	bSizer1->Add( m_pAppendPanel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_pStaticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_pStaticline, 0, wxEXPAND | wxALL, 5 );
	
	m_panel6 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnHelp = new wxButton( m_panel6, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_pwxbtnHelp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCancelBtn = new wxButton( m_panel6, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer9->Add( mCancelBtn, 0, wxALL, 5 );
	
	mOkBtn = new wxButton( m_panel6, wxID_OK, wxT("Calculate!"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	mOkBtn->SetDefault(); 
	bSizer9->Add( mOkBtn, 0, wxALL, 5 );
	
	m_panel6->SetSizer( bSizer9 );
	m_panel6->Layout();
	bSizer9->Fit( m_panel6 );
	bSizer1->Add( m_panel6, 0, wxALL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AcParDlg::OnCloseDialog ) );
	m_pwxradioOctave->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnOctaveBandsRadio ), NULL, this );
	m_pwxradioThirdOctave->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnThirdOctaveBandsRadio ), NULL, this );
	mUserMinLevelText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditRevTimeMinExtreme ), NULL, this );
	mUserMaxLevelText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditRevTimeMaxExtreme ), NULL, this );
	mNoiseCorrectionCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnNoiseCorrCheck ), NULL, this );
	mEDTCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnEDTCheck ), NULL, this );
	mStageCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnComputeStageParamCheck ), NULL, this );
	mAvgModeCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnAvgModeCheck ), NULL, this );
	m_pwxtcDST->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditDirSoundTrigValue ), NULL, this );
	m_pwxtcFullScale->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditPeakSPLValue ), NULL, this );
	mTwoOmniRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnOmniMicClick ), NULL, this );
	mSoundfieldWYRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnSoundfieldClick ), NULL, this );
	mPUProbeRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnPUProbeClick ), NULL, this );
	mIntensityProbeRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnIntensityProbeClick ), NULL, this );
	m_pwxtcProbeMicsDist->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditProbeMicDist ), NULL, this );
	m_pwxtcSoundSpeed->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditCValue ), NULL, this );
	mBinauralRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnBinauralClick ), NULL, this );
	mIACCChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AcParDlg::OnIACCChoice ), NULL, this );
	mFourOmniRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::On4ChModeOmniRadio ), NULL, this );
	mSoundfieldWXYZRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::On4ChModeSoundfieldWXYZRadio ), NULL, this );
	mSoundfieldWYXZRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::On4ChModeSoundfieldWYXZRadio ), NULL, this );
	mAppendResultsCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnAppendResultsToFile ), NULL, this );
	mFileNameText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditAppendFileName ), NULL, this );
	mOpenFileBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnOpenFile ), NULL, this );
	m_pwxbtnHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnHelp ), NULL, this );
	mCancelBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnCancel ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnOk ), NULL, this );
}

AcParDlg::~AcParDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AcParDlg::OnCloseDialog ) );
	m_pwxradioOctave->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnOctaveBandsRadio ), NULL, this );
	m_pwxradioThirdOctave->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnThirdOctaveBandsRadio ), NULL, this );
	mUserMinLevelText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditRevTimeMinExtreme ), NULL, this );
	mUserMaxLevelText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditRevTimeMaxExtreme ), NULL, this );
	mNoiseCorrectionCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnNoiseCorrCheck ), NULL, this );
	mEDTCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnEDTCheck ), NULL, this );
	mStageCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnComputeStageParamCheck ), NULL, this );
	mAvgModeCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnAvgModeCheck ), NULL, this );
	m_pwxtcDST->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditDirSoundTrigValue ), NULL, this );
	m_pwxtcFullScale->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditPeakSPLValue ), NULL, this );
	mTwoOmniRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnOmniMicClick ), NULL, this );
	mSoundfieldWYRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnSoundfieldClick ), NULL, this );
	mPUProbeRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnPUProbeClick ), NULL, this );
	mIntensityProbeRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnIntensityProbeClick ), NULL, this );
	m_pwxtcProbeMicsDist->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditProbeMicDist ), NULL, this );
	m_pwxtcSoundSpeed->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditCValue ), NULL, this );
	mBinauralRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::OnBinauralClick ), NULL, this );
	mIACCChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AcParDlg::OnIACCChoice ), NULL, this );
	mFourOmniRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::On4ChModeOmniRadio ), NULL, this );
	mSoundfieldWXYZRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::On4ChModeSoundfieldWXYZRadio ), NULL, this );
	mSoundfieldWYXZRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AcParDlg::On4ChModeSoundfieldWYXZRadio ), NULL, this );
	mAppendResultsCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AcParDlg::OnAppendResultsToFile ), NULL, this );
	mFileNameText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AcParDlg::OnEditAppendFileName ), NULL, this );
	mOpenFileBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnOpenFile ), NULL, this );
	m_pwxbtnHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnHelp ), NULL, this );
	mCancelBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnCancel ), NULL, this );
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParDlg::OnOk ), NULL, this );
}

GStoreDlg::GStoreDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( m_panel7, wxID_ANY, wxT("You have requested to store the actual Signal values as reference for the strenGth computation. This means that this impulse response is perfectly anechoic, and it was measured at a known distance from the sound source (assumed omnidirectional)"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
	m_staticText9->Wrap( 400 );
	bSizer10->Add( m_staticText9, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( m_panel7, wxID_ANY, wxT("If you want to proceed, please insert the exact distance (in m) and press Store. If you press Cancel, the previous reference values will be left unchanged."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( 400 );
	bSizer10->Add( m_staticText10, 0, wxALL, 5 );
	
	m_panel7->SetSizer( bSizer10 );
	m_panel7->Layout();
	bSizer10->Fit( m_panel7 );
	bSizer9->Add( m_panel7, 0, wxALL, 5 );
	
	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( m_panel8, wxID_ANY, wxT("Distance from the sound source (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer11->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl8 = new wxTextCtrl( m_panel8, ID_G_DIST_TEXT, wxEmptyString, wxDefaultPosition, wxSize( -1,20 ), 0 );
	bSizer11->Add( m_textCtrl8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_panel8->SetSizer( bSizer11 );
	m_panel8->Layout();
	bSizer11->Fit( m_panel8 );
	bSizer9->Add( m_panel8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer9->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	m_panel9 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnRestore = new wxButton( m_panel9, ID_RESTORE_BTN, wxT("Restore defaults"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_pwxbtnRestore, 0, wxALL, 5 );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxbtnCancel = new wxButton( m_panel9, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_pwxbtnCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxbtnStore = new wxButton( m_panel9, wxID_OK, wxT("Store"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnStore->SetDefault(); 
	bSizer12->Add( m_pwxbtnStore, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_panel9->SetSizer( bSizer12 );
	m_panel9->Layout();
	bSizer12->Fit( m_panel9 );
	bSizer9->Add( m_panel9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GStoreDlg::OnCloseDialog ) );
	m_textCtrl8->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GStoreDlg::OnEditDistanceField ), NULL, this );
	m_pwxbtnRestore->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GStoreDlg::OnRestoreDefaultValues ), NULL, this );
	m_pwxbtnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GStoreDlg::OnCancel ), NULL, this );
	m_pwxbtnStore->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GStoreDlg::OnOK ), NULL, this );
}

GStoreDlg::~GStoreDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GStoreDlg::OnCloseDialog ) );
	m_textCtrl8->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GStoreDlg::OnEditDistanceField ), NULL, this );
	m_pwxbtnRestore->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GStoreDlg::OnRestoreDefaultValues ), NULL, this );
	m_pwxbtnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GStoreDlg::OnCancel ), NULL, this );
	m_pwxbtnStore->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GStoreDlg::OnOK ), NULL, this );
}

AcParShowDlg::AcParShowDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer13->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer13->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_pHorzSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_pHorzSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( AcParShowDlg::m_pHorzSplitterOnIdle ), NULL, this );
	m_pwxpnlUpper = new wxScrolledWindow( m_pHorzSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_pwxpnlUpper->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlUpper, ID_PLOT_SBOX, wxT("Unfiltered Impulse Response") ), wxVERTICAL );
	
	m_pwxpnlPlotDesk = new wxPanel( m_pwxpnlUpper, ID_PLOT_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bPlotSizer;
	bPlotSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pPlot = new APDecayPlot(m_pwxpnlPlotDesk, ID_PLOT, wxDefaultPosition, wxDefaultSize);
	m_pPlot->SetMinSize( wxSize( -1,250 ) );
	
	bPlotSizer->Add( m_pPlot, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pwxpnlPlotDesk->SetSizer( bPlotSizer );
	m_pwxpnlPlotDesk->Layout();
	bPlotSizer->Fit( m_pwxpnlPlotDesk );
	sbSizer6->Add( m_pwxpnlPlotDesk, 1, wxEXPAND | wxALL, 5 );
	
	bSizer14->Add( sbSizer6, 1, wxEXPAND|wxALL, 5 );
	
	m_panel15 = new wxPanel( m_pwxpnlUpper, ID_BUTTONS_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxbtnSetup = new wxButton( m_panel15, ID_SETUP_BTN, wxT("Setup"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnSetup->SetDefault(); 
	bSizer15->Add( m_pwxbtnSetup, 0, wxALL|wxEXPAND, 5 );
	
	m_pwxbtnSave = new wxButton( m_panel15, wxID_SAVE, wxT("Save Results to File..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_pwxbtnSave, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_pwxbtnCopy = new wxButton( m_panel15, wxID_COPY, wxT("Copy Results to Clipboard"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_pwxbtnCopy, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_pwxbtnStoreG = new wxButton( m_panel15, ID_STORE_G_BTN, wxT("Store G Reference Signal"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_pwxbtnStoreG, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panel15, wxID_ANY, wxT("Mic/probe type:") ), wxVERTICAL );
	
	m_pwxstSelectedMic = new wxStaticText( m_panel15, ID_MIC_TYPE_ST, wxT("Omnidirectional mic(s) "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_pwxstSelectedMic->Wrap( -1 );
	sbSizer8->Add( m_pwxstSelectedMic, 0, wxALL, 5 );
	
	bSizer15->Add( sbSizer8, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel15, wxID_ANY, wxT("Channels:") ), wxVERTICAL );
	
	mTracksList = new wxListBox( m_panel15, ID_CHANNELS_LIST, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	mTracksList->SetMinSize( wxSize( -1,90 ) );
	
	sbSizer3->Add( mTracksList, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer15->Add( sbSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel15, wxID_ANY, wxT("Tuser limits:") ), wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( m_panel15, wxID_ANY, wxT("("), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer18->Add( m_staticText12, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5 );
	
	mMaxUserStext = new wxStaticText( m_panel15, ID_UP_TUSER_LIMIT_STEXT, wxT("-10.0"), wxDefaultPosition, wxDefaultSize, 0 );
	mMaxUserStext->Wrap( -1 );
	bSizer18->Add( mMaxUserStext, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText14 = new wxStaticText( m_panel15, wxID_ANY, wxT(" dB, "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer18->Add( m_staticText14, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5 );
	
	mMinUserStext = new wxStaticText( m_panel15, ID_LOW_TUSER_LIMIT_STEXT, wxT("-20.0"), wxDefaultPosition, wxDefaultSize, 0 );
	mMinUserStext->Wrap( -1 );
	bSizer18->Add( mMinUserStext, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText16 = new wxStaticText( m_panel15, wxID_ANY, wxT(" dB)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer18->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	sbSizer4->Add( bSizer18, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer15->Add( sbSizer4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_panel15->SetSizer( bSizer15 );
	m_panel15->Layout();
	bSizer15->Fit( m_panel15 );
	bSizer14->Add( m_panel15, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_pwxpnlUpper->SetSizer( bSizer14 );
	m_pwxpnlUpper->Layout();
	bSizer14->Fit( m_pwxpnlUpper );
	m_pwxpnlLower = new wxPanel( m_pHorzSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxVERTICAL );
	
	mGrid = new wxGrid( m_pwxpnlLower, ID_PARAM_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	mGrid->CreateGrid( 14, 12 );
	mGrid->EnableEditing( false );
	mGrid->EnableGridLines( true );
	mGrid->EnableDragGridSize( false );
	mGrid->SetMargins( 0, 0 );
	
	// Columns
	mGrid->SetColSize( 0, 80 );
	mGrid->EnableDragColMove( false );
	mGrid->EnableDragColSize( true );
	mGrid->SetColLabelSize( 25 );
	mGrid->SetColLabelValue( 0, wxT("31.5") );
	mGrid->SetColLabelValue( 1, wxT("63") );
	mGrid->SetColLabelValue( 2, wxT("125") );
	mGrid->SetColLabelValue( 3, wxT("250") );
	mGrid->SetColLabelValue( 4, wxT("500") );
	mGrid->SetColLabelValue( 5, wxT("1k") );
	mGrid->SetColLabelValue( 6, wxT("2k") );
	mGrid->SetColLabelValue( 7, wxT("4k") );
	mGrid->SetColLabelValue( 8, wxT("8k") );
	mGrid->SetColLabelValue( 9, wxT("16k") );
	mGrid->SetColLabelValue( 10, wxT("A") );
	mGrid->SetColLabelValue( 11, wxT("Lin") );
	mGrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	mGrid->AutoSizeRows();
	mGrid->EnableDragRowSize( true );
	mGrid->SetRowLabelSize( 120 );
	mGrid->SetRowLabelValue( 0, wxT("Signal [dB]") );
	mGrid->SetRowLabelValue( 1, wxT("Noise [dB]") );
	mGrid->SetRowLabelValue( 2, wxT("strenGth [dB]") );
	mGrid->SetRowLabelValue( 3, wxT("C50 [dB]") );
	mGrid->SetRowLabelValue( 4, wxT("C80 [dB]") );
	mGrid->SetRowLabelValue( 5, wxT("D50 [%]") );
	mGrid->SetRowLabelValue( 6, wxT("Ts [ms]") );
	mGrid->SetRowLabelValue( 7, wxT("EDT [s]") );
	mGrid->SetRowLabelValue( 8, wxT("Tuser [s]") );
	mGrid->SetRowLabelValue( 9, wxT("T20 [s]") );
	mGrid->SetRowLabelValue( 10, wxT("T30 [s]") );
	mGrid->SetRowLabelValue( 11, wxT("Peakiness [dB]") );
	mGrid->SetRowLabelValue( 12, wxT("Millisecs [dB]") );
	mGrid->SetRowLabelValue( 13, wxT("Impulsivs [dB]") );
	mGrid->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	mGrid->SetLabelFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	// Cell Defaults
	mGrid->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizer201->Add( mGrid, 1, wxALL|wxEXPAND, 5 );
	
	m_pwxpnlLower->SetSizer( bSizer201 );
	m_pwxpnlLower->Layout();
	bSizer201->Fit( m_pwxpnlLower );
	m_pHorzSplitter->SplitHorizontally( m_pwxpnlUpper, m_pwxpnlLower, 0 );
	bSizer13->Add( m_pHorzSplitter, 1, wxEXPAND, 5 );
	
	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer13->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlButtons = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	mHelpBtn = new wxButton( m_pwxpnlButtons, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( mHelpBtn, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer19->Add( 0, 0, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	mCloseBtn = new wxButton( m_pwxpnlButtons, wxID_CLOSE, wxT("Close"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer19->Add( mCloseBtn, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	mOkBtn = new wxButton( m_pwxpnlButtons, wxID_OK, wxT("Filter"), wxDefaultPosition, wxDefaultSize, 0 );
	mOkBtn->SetDefault(); 
	mOkBtn->SetToolTip( wxT("Add to workspace filtered track(s).") );
	
	bSizer19->Add( mOkBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxpnlButtons->SetSizer( bSizer19 );
	m_pwxpnlButtons->Layout();
	bSizer19->Fit( m_pwxpnlButtons );
	bSizer13->Add( m_pwxpnlButtons, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer13 );
	this->Layout();
	bSizer13->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AcParShowDlg::OnCloseDialog ) );
	m_pwxbtnSetup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnSetupButton ), NULL, this );
	m_pwxbtnSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnSaveResults ), NULL, this );
	m_pwxbtnCopy->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnCopyResults ), NULL, this );
	m_pwxbtnStoreG->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnStoreGRefSig ), NULL, this );
	mTracksList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AcParShowDlg::OnChannelListSelect ), NULL, this );
	mGrid->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( AcParShowDlg::OnGridCellRightClick ), NULL, this );
	mGrid->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( AcParShowDlg::OnGraphChange ), NULL, this );
	mGrid->Connect( wxEVT_GRID_LABEL_LEFT_DCLICK, wxGridEventHandler( AcParShowDlg::OnGridLabelDoubleClick ), NULL, this );
	mHelpBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnHelp ), NULL, this );
	mCloseBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnClose ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnOk ), NULL, this );
}

AcParShowDlg::~AcParShowDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( AcParShowDlg::OnCloseDialog ) );
	m_pwxbtnSetup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnSetupButton ), NULL, this );
	m_pwxbtnSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnSaveResults ), NULL, this );
	m_pwxbtnCopy->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnCopyResults ), NULL, this );
	m_pwxbtnStoreG->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnStoreGRefSig ), NULL, this );
	mTracksList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AcParShowDlg::OnChannelListSelect ), NULL, this );
	mGrid->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( AcParShowDlg::OnGridCellRightClick ), NULL, this );
	mGrid->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( AcParShowDlg::OnGraphChange ), NULL, this );
	mGrid->Disconnect( wxEVT_GRID_LABEL_LEFT_DCLICK, wxGridEventHandler( AcParShowDlg::OnGridLabelDoubleClick ), NULL, this );
	mHelpBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnHelp ), NULL, this );
	mCloseBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnClose ), NULL, this );
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AcParShowDlg::OnOk ), NULL, this );
}
