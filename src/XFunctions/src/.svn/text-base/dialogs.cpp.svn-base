///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

#include "../res/equations/null.xpm"

///////////////////////////////////////////////////////////////////////////

XFunctionsDlg::XFunctionsDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_pwxpnlLogo, 0, wxEXPAND | wxALL, 5 );
	
	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("FFT Setup") ), wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("Length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mFftSizeChoiceChoices[] = { wxT("512"), wxT("1024"), wxT("2048"), wxT("4096"), wxT("8192"), wxT("16384"), wxT("32768"), wxT("65536"), wxT("131072"), wxT("262144"), wxT("524288"), wxT("1048576") };
	int mFftSizeChoiceNChoices = sizeof( mFftSizeChoiceChoices ) / sizeof( wxString );
	mFftSizeChoice = new wxChoice( m_panel1, ID_FFT_SIZE_CHOICE, wxDefaultPosition, wxDefaultSize, mFftSizeChoiceNChoices, mFftSizeChoiceChoices, 0 );
	mFftSizeChoice->SetSelection( 5 );
	bSizer2->Add( mFftSizeChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, wxT("Window:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer2->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mWindowChoiceChoices[] = { wxT("Rectangular"), wxT("Hanning"), wxT("Blackman-Harris"), wxT("Flat-Top"), wxT("Triangular"), wxT("Half-Sine") };
	int mWindowChoiceNChoices = sizeof( mWindowChoiceChoices ) / sizeof( wxString );
	mWindowChoice = new wxChoice( m_panel1, ID_WINDOW_CHOICE, wxDefaultPosition, wxDefaultSize, mWindowChoiceNChoices, mWindowChoiceChoices, 0 );
	mWindowChoice->SetSelection( 1 );
	bSizer2->Add( mWindowChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer10->Add( bSizer2, 1, wxEXPAND, 5 );
	
	m_panel1->SetSizer( sbSizer10 );
	m_panel1->Layout();
	sbSizer10->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 0, wxALL|wxEXPAND, 5 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Processing Function:") ), wxVERTICAL );
	
	wxString mXFunctionChoiceChoices[] = { wxT("Auto-Correlation"), wxT("Cross-Correlation"), wxT("White Cross-Correlation"), wxT("Cross-Power Spectrum Phase"), wxT("Transfer Function H1"), wxT("Transfer Function H2"), wxT("Transfer Function H3"), wxT("Absorption Coefficient Alpha (PU probe)") };
	int mXFunctionChoiceNChoices = sizeof( mXFunctionChoiceChoices ) / sizeof( wxString );
	mXFunctionChoice = new wxChoice( m_panel2, ID_XFUNCTION_CHOICE, wxDefaultPosition, wxDefaultSize, mXFunctionChoiceNChoices, mXFunctionChoiceChoices, 0 );
	mXFunctionChoice->SetSelection( 1 );
	sbSizer1->Add( mXFunctionChoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mEquationPanel = new wxPanel( m_panel2, wxID_ANY, wxDefaultPosition, wxSize( 310,60 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	mEquationBmp = new wxStaticBitmap( mEquationPanel, ID_EQUATION_SBMP, wxBitmap( null_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( mEquationBmp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mEquationPanel->SetSizer( bSizer19 );
	mEquationPanel->Layout();
	sbSizer1->Add( mEquationPanel, 1, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	mLagLabelStext = new wxStaticText( m_panel2, ID_LAG_LABEL_STEXT, wxT("Lag:"), wxDefaultPosition, wxDefaultSize, 0 );
	mLagLabelStext->Wrap( -1 );
	mLagLabelStext->Enable( false );
	
	bSizer25->Add( mLagLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLagStext = new wxStaticText( m_panel2, ID_LAG_STEXT, wxT("9.9 s"), wxDefaultPosition, wxDefaultSize, 0 );
	mLagStext->Wrap( -1 );
	mLagStext->Enable( false );
	
	bSizer25->Add( mLagStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer25, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel2->SetSizer( sbSizer1 );
	m_panel2->Layout();
	sbSizer1->Fit( m_panel2 );
	bSizer1->Add( m_panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Computation of FIR filters for PU Probe calibration") ), wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	mSWTubeCheck = new wxCheckBox( m_panel3, ID_SW_TUBE_CHECK, wxT("Rigid termination in a SW tube"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer3->Add( mSWTubeCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	mFreeFieldCheck = new wxCheckBox( m_panel3, ID_FREE_FIELD_CHECK, wxT("Free Field"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer3->Add( mFreeFieldCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText22 = new wxStaticText( m_panel3, wxID_ANY, wxT("c [m/s]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer4->Add( m_staticText22, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	mSoundSpeedText = new wxTextCtrl( m_panel3, ID_SOUNDSPEED_TEXT, wxT("343.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	mSoundSpeedText->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer4->Add( mSoundSpeedText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText23 = new wxStaticText( m_panel3, wxID_ANY, wxT("d [mm]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer4->Add( m_staticText23, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	mProbeDistText = new wxTextCtrl( m_panel3, ID_PROBE_DIST_TEXT, wxT("40.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	mProbeDistText->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer4->Add( mProbeDistText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText24 = new wxStaticText( m_panel3, wxID_ANY, wxT("fmax [Hz]:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	bSizer4->Add( m_staticText24, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	mFmaxText = new wxTextCtrl( m_panel3, ID_FMAX_TEXT, wxT("1900.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	mFmaxText->SetMinSize( wxSize( 65,-1 ) );
	
	bSizer4->Add( mFmaxText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer4, 1, wxEXPAND, 5 );
	
	m_panel3->SetSizer( sbSizer2 );
	m_panel3->Layout();
	sbSizer2->Fit( m_panel3 );
	bSizer1->Add( m_panel3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel4, wxID_ANY, wxT("Following Filter (sine sweep measurements)") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mEnableFFilterCheck = new wxCheckBox( m_panel4, ID_ENABLE_FFILTER_CHECK, wxT("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer2->Add( mEnableFFilterCheck, 0, wxALL, 5 );
	
	m_staticText26 = new wxStaticText( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer2->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText27 = new wxStaticText( m_panel4, wxID_ANY, wxT("Bandwidth (Octave)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer2->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mFollowLeftRadio = new wxRadioButton( m_panel4, ID_FOLLOW_LEFT_RADIO, wxT("Follow Left"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	mFollowLeftRadio->SetValue( true ); 
	mFollowLeftRadio->Enable( false );
	
	fgSizer2->Add( mFollowLeftRadio, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mFollowRightRadio = new wxRadioButton( m_panel4, ID_FOLLOW_RIGHT_RADIO, wxT("Follow Right"), wxDefaultPosition, wxDefaultSize, 0 );
	mFollowRightRadio->Enable( false );
	
	fgSizer2->Add( mFollowRightRadio, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mBandwidthText = new wxTextCtrl( m_panel4, ID_BANDWIDTH_TEXT, wxT("0.33"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	mBandwidthText->Enable( false );
	mBandwidthText->SetMinSize( wxSize( 120,-1 ) );
	
	fgSizer2->Add( mBandwidthText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	sbSizer3->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	m_panel4->SetSizer( sbSizer3 );
	m_panel4->Layout();
	sbSizer3->Fit( m_panel4 );
	bSizer1->Add( m_panel4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel5, wxID_ANY, wxT("Output Results") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 4, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mNormalizeLeftCheck = new wxCheckBox( m_panel5, ID_NORMALIZE_LEFT_CHECK, wxT("Normalize"), wxDefaultPosition, wxDefaultSize, 0 );
	mNormalizeLeftCheck->SetValue(true);
	
	fgSizer3->Add( mNormalizeLeftCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mHilbertCheck = new wxCheckBox( m_panel5, ID_HILBERT_CHECK, wxT("Squared Hilbert Transform"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer3->Add( mHilbertCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mShiftToHalfCheck = new wxCheckBox( m_panel5, ID_SHIFT_TO_HALF_CHECK, wxT("Shift to half window"), wxDefaultPosition, wxDefaultSize, 0 );
	mShiftToHalfCheck->SetValue(true);
	
	fgSizer3->Add( mShiftToHalfCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mTimeReversalCheck = new wxCheckBox( m_panel5, ID_TIME_REV_CHECK, wxT("Time reversal"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer3->Add( mTimeReversalCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mCoherenceCheck = new wxCheckBox( m_panel5, ID_COHERENCE_CHECK, wxT("Coherence weighting"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer3->Add( mCoherenceCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mSaveMultispectrumCheck = new wxCheckBox( m_panel5, ID_SAVE_MULTISPECTRUM_CHECK, wxT("Save Multispectrum"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer3->Add( mSaveMultispectrumCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText28 = new wxStaticText( m_panel5, wxID_ANY, wxT("Trigger Level [%]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	bSizer5->Add( m_staticText28, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mTriggerText = new wxTextCtrl( m_panel5, ID_TRIGGER_TEXT, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	mTriggerText->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer5->Add( mTriggerText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer3->Add( bSizer5, 1, wxEXPAND, 5 );
	
	mDiracCheck = new wxCheckBox( m_panel5, ID_DIRAC_CHECK, wxT("Dirac Pulse"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer3->Add( mDiracCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer4->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	m_panel5->SetSizer( sbSizer4 );
	m_panel5->Layout();
	sbSizer4->Fit( m_panel5 );
	bSizer1->Add( m_panel5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_panel6 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	mHelpBtn = new wxButton( m_panel6, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( mHelpBtn, 0, wxALL, 5 );
	
	
	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCancelBtn = new wxButton( m_panel6, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( mCancelBtn, 0, wxALL, 5 );
	
	mOkBtn = new wxButton( m_panel6, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	mOkBtn->SetDefault(); 
	bSizer6->Add( mOkBtn, 0, wxALL, 5 );
	
	m_panel6->SetSizer( bSizer6 );
	m_panel6->Layout();
	bSizer6->Fit( m_panel6 );
	bSizer1->Add( m_panel6, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( XFunctionsDlg::OnCloseDialog ) );
	mFftSizeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnFftSizeChoice ), NULL, this );
	mWindowChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnWindowChoice ), NULL, this );
	mXFunctionChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnXFunctionChoice ), NULL, this );
	mSWTubeCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnSWTubeCheck ), NULL, this );
	mFreeFieldCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnFreeFieldCheck ), NULL, this );
	mSoundSpeedText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnSoundSpeedText ), NULL, this );
	mProbeDistText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnProbeDistanceText ), NULL, this );
	mFmaxText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnFmaxText ), NULL, this );
	mEnableFFilterCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnEnableFollowingFilterCheck ), NULL, this );
	mFollowLeftRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnFollowLeftRadio ), NULL, this );
	mFollowRightRadio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnFollowRightRadio ), NULL, this );
	mBandwidthText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnBandwidthText ), NULL, this );
	mNormalizeLeftCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnNormalizeLeftChannelCheck ), NULL, this );
	mHilbertCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnHilbertCheck ), NULL, this );
	mShiftToHalfCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnShiftToHalfWindowCheck ), NULL, this );
	mTimeReversalCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnTimeReversalCheck ), NULL, this );
	mCoherenceCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnCoherenceCheck ), NULL, this );
	mSaveMultispectrumCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnSaveMultispectrumCheck ), NULL, this );
	mTriggerText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnTriggerLevelText ), NULL, this );
	mDiracCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnDiracPulseCheck ), NULL, this );
	mHelpBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnHelp ), NULL, this );
	mCancelBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnCancel ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnOk ), NULL, this );
}

XFunctionsDlg::~XFunctionsDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( XFunctionsDlg::OnCloseDialog ) );
	mFftSizeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnFftSizeChoice ), NULL, this );
	mWindowChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnWindowChoice ), NULL, this );
	mXFunctionChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnXFunctionChoice ), NULL, this );
	mSWTubeCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnSWTubeCheck ), NULL, this );
	mFreeFieldCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnFreeFieldCheck ), NULL, this );
	mSoundSpeedText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnSoundSpeedText ), NULL, this );
	mProbeDistText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnProbeDistanceText ), NULL, this );
	mFmaxText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnFmaxText ), NULL, this );
	mEnableFFilterCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnEnableFollowingFilterCheck ), NULL, this );
	mFollowLeftRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnFollowLeftRadio ), NULL, this );
	mFollowRightRadio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( XFunctionsDlg::OnFollowRightRadio ), NULL, this );
	mBandwidthText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnBandwidthText ), NULL, this );
	mNormalizeLeftCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnNormalizeLeftChannelCheck ), NULL, this );
	mHilbertCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnHilbertCheck ), NULL, this );
	mShiftToHalfCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnShiftToHalfWindowCheck ), NULL, this );
	mTimeReversalCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnTimeReversalCheck ), NULL, this );
	mCoherenceCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnCoherenceCheck ), NULL, this );
	mSaveMultispectrumCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnSaveMultispectrumCheck ), NULL, this );
	mTriggerText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( XFunctionsDlg::OnTriggerLevelText ), NULL, this );
	mDiracCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnDiracPulseCheck ), NULL, this );
	mHelpBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnHelp ), NULL, this );
	mCancelBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnCancel ), NULL, this );
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsDlg::OnOk ), NULL, this );
}

XFunctionsShowDlg::XFunctionsShowDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer7->Add( m_pwxpnlLogo, 0, wxALL|wxEXPAND, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_panel9 = new wxPanel( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer221;
	bSizer221 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panel9, wxID_ANY, wxT("Input Waveform Info") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 4, 3, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText29 = new wxStaticText( m_panel9, wxID_ANY, wxT("FFT Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer4->Add( m_staticText29, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mFftSizeStext = new wxStaticText( m_panel9, ID_FFT_SIZE_STEXT, wxT("1048576"), wxDefaultPosition, wxDefaultSize, 0 );
	mFftSizeStext->Wrap( -1 );
	fgSizer4->Add( mFftSizeStext, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText31 = new wxStaticText( m_panel9, wxID_ANY, wxT("Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer4->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText32 = new wxStaticText( m_panel9, wxID_ANY, wxT("Channels:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer4->Add( m_staticText32, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mChannelsStext = new wxStaticText( m_panel9, ID_CHANNELS_STEXT, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	mChannelsStext->Wrap( -1 );
	fgSizer4->Add( mChannelsStext, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText34 = new wxStaticText( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer4->Add( m_staticText34, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText35 = new wxStaticText( m_panel9, wxID_ANY, wxT("Sample Rate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer4->Add( m_staticText35, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRateStext = new wxStaticText( m_panel9, ID_RATE_STEXT, wxT("44100"), wxDefaultPosition, wxDefaultSize, 0 );
	mRateStext->Wrap( -1 );
	fgSizer4->Add( mRateStext, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText37 = new wxStaticText( m_panel9, wxID_ANY, wxT("Hz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	fgSizer4->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText38 = new wxStaticText( m_panel9, wxID_ANY, wxT("N. of blocks:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	fgSizer4->Add( m_staticText38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mNblocksStext = new wxStaticText( m_panel9, ID_NBLOCKS_STEXT, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	mNblocksStext->Wrap( -1 );
	fgSizer4->Add( mNblocksStext, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText40 = new wxStaticText( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	fgSizer4->Add( m_staticText40, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer5->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	bSizer221->Add( sbSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_panel9, wxID_ANY, wxT("Transform type") ), wxVERTICAL );
	
	mTransformTypeStext = new wxStaticText( m_panel9, ID_TRANSFORM_TYPE_STEXT, wxT("Very long transform type name"), wxDefaultPosition, wxDefaultSize, 0 );
	mTransformTypeStext->Wrap( -1 );
	sbSizer10->Add( mTransformTypeStext, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer221->Add( sbSizer10, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_panel9, wxID_ANY, wxT("Statistics") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mRmsLeftLabelStext = new wxStaticText( m_panel9, ID_RMS_LEFT_LABEL_STEXT, wxT("RMS left:"), wxDefaultPosition, wxDefaultSize, 0 );
	mRmsLeftLabelStext->Wrap( -1 );
	fgSizer5->Add( mRmsLeftLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRmsLeftStext = new wxStaticText( m_panel9, ID_RMS_LEFT_STEXT, wxT("-120.00"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	mRmsLeftStext->Wrap( -1 );
	fgSizer5->Add( mRmsLeftStext, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	mRmsLeftdBStext = new wxStaticText( m_panel9, ID_RMS_LEFT_dB_STEXT, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	mRmsLeftdBStext->Wrap( -1 );
	fgSizer5->Add( mRmsLeftdBStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRmsRightLabelStext = new wxStaticText( m_panel9, ID_RMS_RIGHT_LABEL_STEXT, wxT("RMS right:"), wxDefaultPosition, wxDefaultSize, 0 );
	mRmsRightLabelStext->Wrap( -1 );
	fgSizer5->Add( mRmsRightLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRmsRightStext = new wxStaticText( m_panel9, ID_RMS_RIGHT_STEXT, wxT("-120.00"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	mRmsRightStext->Wrap( -1 );
	fgSizer5->Add( mRmsRightStext, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRmsRightdBStext = new wxStaticText( m_panel9, ID_RMS_RIGHT_dB_STEXT, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	mRmsRightdBStext->Wrap( -1 );
	fgSizer5->Add( mRmsRightdBStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRmsCrossLabelStext = new wxStaticText( m_panel9, ID_RMS_CROSS_LABEL_STEXT, wxT("RMS cross:"), wxDefaultPosition, wxDefaultSize, 0 );
	mRmsCrossLabelStext->Wrap( -1 );
	fgSizer5->Add( mRmsCrossLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRmsCrossStext = new wxStaticText( m_panel9, ID_RMS_CROSS_STEXT, wxT("-120.00"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	mRmsCrossStext->Wrap( -1 );
	fgSizer5->Add( mRmsCrossStext, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	mRmsCrossdBStext = new wxStaticText( m_panel9, ID_RMS_CROSS_dB_STEXT, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	mRmsCrossdBStext->Wrap( -1 );
	fgSizer5->Add( mRmsCrossdBStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer6->Add( fgSizer5, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline4 = new wxStaticLine( m_panel9, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sbSizer6->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	mTimeOfFlightStext = new wxStaticText( m_panel9, ID_TIME_OF_FLIGHT_STEXT, wxT("Time of flight:"), wxDefaultPosition, wxDefaultSize, 0 );
	mTimeOfFlightStext->Wrap( -1 );
	mTimeOfFlightStext->Enable( false );
	
	sbSizer6->Add( mTimeOfFlightStext, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mTriggerTimeLabelStext = new wxStaticText( m_panel9, ID_TRIGGER_TIME_LABEL_STEXT, wxT("Trigger Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	mTriggerTimeLabelStext->Wrap( -1 );
	mTriggerTimeLabelStext->Enable( false );
	
	fgSizer6->Add( mTriggerTimeLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mTriggerTimeStext = new wxStaticText( m_panel9, ID_TRIGGER_TIME_STEXT, wxT("50.0%"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	mTriggerTimeStext->Wrap( -1 );
	mTriggerTimeStext->Enable( false );
	
	fgSizer6->Add( mTriggerTimeStext, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mTriggerTimeAtStext = new wxStaticText( m_panel9, ID_TRIGGER_TIME_AT_STEXT, wxT("at"), wxDefaultPosition, wxDefaultSize, 0 );
	mTriggerTimeAtStext->Wrap( -1 );
	mTriggerTimeAtStext->Enable( false );
	
	fgSizer6->Add( mTriggerTimeAtStext, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mTriggerDelayStext = new wxStaticText( m_panel9, ID_TRIGGER_DELAY_STEXT, wxT(" 0.000 s"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	mTriggerDelayStext->Wrap( -1 );
	mTriggerDelayStext->Enable( false );
	
	fgSizer6->Add( mTriggerDelayStext, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mNccMaxLabelStext = new wxStaticText( m_panel9, ID_NCC_MAX_LABEL_STEXT, wxT("NCC Max.:"), wxDefaultPosition, wxDefaultSize, 0 );
	mNccMaxLabelStext->Wrap( -1 );
	mNccMaxLabelStext->Enable( false );
	
	fgSizer6->Add( mNccMaxLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mNccMaxStext = new wxStaticText( m_panel9, ID_NCC_MAX_STEXT, wxT("0.9999"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	mNccMaxStext->Wrap( -1 );
	mNccMaxStext->Enable( false );
	
	fgSizer6->Add( mNccMaxStext, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mNccMaxAtStext = new wxStaticText( m_panel9, ID_NCC_MAX_AT_STEXT, wxT("at"), wxDefaultPosition, wxDefaultSize, 0 );
	mNccMaxAtStext->Wrap( -1 );
	mNccMaxAtStext->Enable( false );
	
	fgSizer6->Add( mNccMaxAtStext, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	mNccMaxDelayStext = new wxStaticText( m_panel9, ID_NCC_MAX_DELAY_STEXT, wxT("0.000 s"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	mNccMaxDelayStext->Wrap( -1 );
	mNccMaxDelayStext->Enable( false );
	
	fgSizer6->Add( mNccMaxDelayStext, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	sbSizer6->Add( fgSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mSaveToTimeDelayCheck = new wxCheckBox( m_panel9, ID_SAVE_TO_TIMEDELAY_CHECK, wxT("Save to timedelay.txt"), wxDefaultPosition, wxDefaultSize, 0 );
	mSaveToTimeDelayCheck->SetValue(true);
	
	mSaveToTimeDelayCheck->Enable( false );
	
	sbSizer6->Add( mSaveToTimeDelayCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer221->Add( sbSizer6, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panel9, wxID_ANY, wxT("Horizontal axis settings:") ), wxVERTICAL );
	
	m_staticText65 = new wxStaticText( m_panel9, wxID_ANY, wxT("Frequency range:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	sbSizer9->Add( m_staticText65, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mFrequencyRangeChoiceChoices[] = { wxT("0 Hz -> 2 kHZ"), wxT("0 Hz -> Nyquist Frequency") };
	int mFrequencyRangeChoiceNChoices = sizeof( mFrequencyRangeChoiceChoices ) / sizeof( wxString );
	mFrequencyRangeChoice = new wxChoice( m_panel9, ID_FREQUENCY_RANGE_CHOICE, wxDefaultPosition, wxDefaultSize, mFrequencyRangeChoiceNChoices, mFrequencyRangeChoiceChoices, 0 );
	mFrequencyRangeChoice->SetSelection( 1 );
	sbSizer9->Add( mFrequencyRangeChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	mLinearScaleCheck = new wxCheckBox( m_panel9, ID_LINEAR_SCALE_CHECK, wxT("Linear Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer9->Add( mLinearScaleCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer221->Add( sbSizer9, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_panel9, wxID_ANY, wxT("Export spectral data") ), wxVERTICAL );
	
	mExportAllCheck = new wxCheckBox( m_panel9, ID_EXPORT_ALL_CHECK, wxT("Dump all spectrums"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer11->Add( mExportAllCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	mSaveBtn = new wxButton( m_panel9, ID_SAVE_SPECTRUM_BTN, wxT("Save as..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( mSaveBtn, 0, wxALL, 5 );
	
	mCopyBtn = new wxButton( m_panel9, ID_COPY_SPECTRUM_BTN, wxT("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( mCopyBtn, 0, wxALL, 5 );
	
	sbSizer11->Add( bSizer20, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer211->Add( sbSizer11, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	mExportWaveformsCheck = new wxCheckBox( m_panel9, ID_EXPORT_WAVEFORMS_CHECK, wxT("Export waveforms to workspace"), wxDefaultPosition, wxDefaultSize, 0 );
	mExportWaveformsCheck->SetValue(true);
	
	bSizer211->Add( mExportWaveformsCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer221->Add( bSizer211, 0, wxEXPAND, 5 );
	
	m_panel9->SetSizer( bSizer221 );
	m_panel9->Layout();
	bSizer221->Fit( m_panel9 );
	bSizer9->Add( m_panel9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer8->Add( bSizer9, 0, 0, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	mRightSideSplitter = new wxSplitterWindow( m_panel7, ID_RSIDE_SPLITTER, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME );
	mRightSideSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( XFunctionsShowDlg::mRightSideSplitterOnIdle ), NULL, this );
	mRUpperPanel = new wxPanel( mRightSideSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	mPlotSplitter = new wxSplitterWindow( mRUpperPanel, ID_PLOT_SPLITTER, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME );
	mPlotSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( XFunctionsShowDlg::mPlotSplitterOnIdle ), NULL, this );
	mPlotSplitter->SetMinSize( wxSize( 400,-1 ) );
	
	mUpperSplitterPanel = new wxPanel( mPlotSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxVERTICAL );
	
	wxString mFirstPlotChoiceChoices[] = { wxT("Autocorrelation Left"), wxT("Autocorrelation Right"), wxT("Cross-Power Spect. Magn."), wxT("Cross-Power Spect. Phase") };
	int mFirstPlotChoiceNChoices = sizeof( mFirstPlotChoiceChoices ) / sizeof( wxString );
	mFirstPlotChoice = new wxChoice( mUpperSplitterPanel, ID_FIRST_PLOT_CHOICE, wxDefaultPosition, wxDefaultSize, mFirstPlotChoiceNChoices, mFirstPlotChoiceChoices, 0 );
	mFirstPlotChoice->SetSelection( 0 );
	bSizer141->Add( mFirstPlotChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mUpperPlotScroller = new wxScrolledWindow( mUpperSplitterPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mUpperPlotScroller->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	mUpperPlot = new XFPlot(mUpperPlotScroller, ID_UPPER_PLOT);
	bSizer15->Add( mUpperPlot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	mUpperPlotScroller->SetSizer( bSizer15 );
	mUpperPlotScroller->Layout();
	bSizer15->Fit( mUpperPlotScroller );
	bSizer141->Add( mUpperPlotScroller, 1, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mUpperSplitterPanel->SetSizer( bSizer141 );
	mUpperSplitterPanel->Layout();
	bSizer141->Fit( mUpperSplitterPanel );
	mLowerSplitterPanel = new wxPanel( mPlotSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1411;
	bSizer1411 = new wxBoxSizer( wxVERTICAL );
	
	wxString mSecondPlotChoiceChoices[] = { wxT("Autocorrelation Left"), wxT("Autocorrelation Right"), wxT("Cross-Power Spect. Magn."), wxT("Cross-Power Spect. Phase") };
	int mSecondPlotChoiceNChoices = sizeof( mSecondPlotChoiceChoices ) / sizeof( wxString );
	mSecondPlotChoice = new wxChoice( mLowerSplitterPanel, ID_SECOND_PLOT_CHOICE, wxDefaultPosition, wxDefaultSize, mSecondPlotChoiceNChoices, mSecondPlotChoiceChoices, 0 );
	mSecondPlotChoice->SetSelection( 1 );
	bSizer1411->Add( mSecondPlotChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mLowerPlotScroller = new wxScrolledWindow( mLowerSplitterPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mLowerPlotScroller->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxVERTICAL );
	
	mLowerPlot = new XFPlot(mLowerPlotScroller,  ID_LOWER_PLOT);
	bSizer151->Add( mLowerPlot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	mLowerPlotScroller->SetSizer( bSizer151 );
	mLowerPlotScroller->Layout();
	bSizer151->Fit( mLowerPlotScroller );
	bSizer1411->Add( mLowerPlotScroller, 1, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mLowerSplitterPanel->SetSizer( bSizer1411 );
	mLowerSplitterPanel->Layout();
	bSizer1411->Fit( mLowerSplitterPanel );
	mPlotSplitter->SplitHorizontally( mUpperSplitterPanel, mLowerSplitterPanel, 0 );
	bSizer21->Add( mPlotSplitter, 1, wxEXPAND, 5 );
	
	mRUpperPanel->SetSizer( bSizer21 );
	mRUpperPanel->Layout();
	bSizer21->Fit( mRUpperPanel );
	mRightSideSplitter->Initialize( mRUpperPanel );
	bSizer13->Add( mRightSideSplitter, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer8->Add( bSizer13, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_panel7->SetSizer( bSizer8 );
	m_panel7->Layout();
	bSizer8->Fit( m_panel7 );
	bSizer7->Add( m_panel7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline3, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	mHelpBtn = new wxButton( m_panel8, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( mHelpBtn, 0, wxALL, 5 );
	
	
	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCloseBtn = new wxButton( m_panel8, wxID_CLOSE, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	mCloseBtn->SetDefault(); 
	bSizer14->Add( mCloseBtn, 0, wxALL, 5 );
	
	m_panel8->SetSizer( bSizer14 );
	m_panel8->Layout();
	bSizer14->Fit( m_panel8 );
	bSizer7->Add( m_panel8, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( XFunctionsShowDlg::OnCloseDialog ) );
	mSaveToTimeDelayCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnSaveToTimeDelayCheck ), NULL, this );
	mFrequencyRangeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsShowDlg::OnFrequencyRangeChoice ), NULL, this );
	mLinearScaleCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnLinearScaleCheck ), NULL, this );
	mExportAllCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnExportAllSpectrumsCheck ), NULL, this );
	mSaveBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnSaveSpectrumBtn ), NULL, this );
	mCopyBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnCopySpectrumBtn ), NULL, this );
	mExportWaveformsCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnExportWaveformsCheck ), NULL, this );
	mFirstPlotChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsShowDlg::OnFirstPlotChoice ), NULL, this );
	mSecondPlotChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsShowDlg::OnSecondPlotChoice ), NULL, this );
	mHelpBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnHelp ), NULL, this );
	mCloseBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnClose ), NULL, this );
}

XFunctionsShowDlg::~XFunctionsShowDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( XFunctionsShowDlg::OnCloseDialog ) );
	mSaveToTimeDelayCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnSaveToTimeDelayCheck ), NULL, this );
	mFrequencyRangeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsShowDlg::OnFrequencyRangeChoice ), NULL, this );
	mLinearScaleCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnLinearScaleCheck ), NULL, this );
	mExportAllCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnExportAllSpectrumsCheck ), NULL, this );
	mSaveBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnSaveSpectrumBtn ), NULL, this );
	mCopyBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnCopySpectrumBtn ), NULL, this );
	mExportWaveformsCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnExportWaveformsCheck ), NULL, this );
	mFirstPlotChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsShowDlg::OnFirstPlotChoice ), NULL, this );
	mSecondPlotChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( XFunctionsShowDlg::OnSecondPlotChoice ), NULL, this );
	mHelpBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnHelp ), NULL, this );
	mCloseBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( XFunctionsShowDlg::OnClose ), NULL, this );
}
