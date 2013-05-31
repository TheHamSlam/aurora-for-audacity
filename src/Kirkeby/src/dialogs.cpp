///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../src/dialogs.h"

///////////////////////////////////////////////////////////////////////////

KirkebyDlg::KirkebyDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Impulse Response info") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_pwxstRateLbl = new wxStaticText( m_panel1, wxID_ANY, wxT("Sampling freqency:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstRateLbl->Wrap( -1 );
	fgSizer3->Add( m_pwxstRateLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstRate = new wxStaticText( m_panel1, ID_RATE_ST, wxT("192000.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstRate->Wrap( -1 );
	fgSizer3->Add( m_pwxstRate, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_pwxstHz = new wxStaticText( m_panel1, wxID_ANY, wxT("Hz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstHz->Wrap( -1 );
	fgSizer3->Add( m_pwxstHz, 0, wxALL, 5 );
	
	m_pwxstChnlsLbl = new wxStaticText( m_panel1, ID_CHNLS_LBL_ST, wxT("Channel(s):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstChnlsLbl->Wrap( -1 );
	fgSizer3->Add( m_pwxstChnlsLbl, 0, wxALL, 5 );
	
	m_pwxstChnls = new wxStaticText( m_panel1, ID_CHNLS_LBL, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstChnls->Wrap( -1 );
	fgSizer3->Add( m_pwxstChnls, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_pwxstSpc = new wxStaticText( m_panel1, wxID_ANY, wxT(" "), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSpc->Wrap( -1 );
	fgSizer3->Add( m_pwxstSpc, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstLengthLbl = new wxStaticText( m_panel1, wxID_ANY, wxT("Length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstLengthLbl->Wrap( -1 );
	fgSizer3->Add( m_pwxstLengthLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstLength = new wxStaticText( m_panel1, ID_LENGTH_ST, wxT("1000000000"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstLength->Wrap( -1 );
	fgSizer3->Add( m_pwxstLength, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstSamples = new wxStaticText( m_panel1, wxID_ANY, wxT("samples"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSamples->Wrap( -1 );
	fgSizer3->Add( m_pwxstSamples, 0, wxALL, 5 );
	
	sbSizer1->Add( fgSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxrbMonoFiltering = new wxRadioButton( m_panel1, ID_MONO_FILTERING_RADIO, wxT("Dual Mono (no CrossTalk cancellation)"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	m_pwxrbMonoFiltering->SetValue( true ); 
	bSizer6->Add( m_pwxrbMonoFiltering, 0, wxALL, 5 );
	
	m_pwxrbStereoFiltering = new wxRadioButton( m_panel1, ID_STEREO_FILTERING_RADIO, wxT("Stereo (with CrossTalk cancellation)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxrbStereoFiltering->Enable( false );
	
	bSizer6->Add( m_pwxrbStereoFiltering, 0, wxALL, 5 );
	
	m_pwxrbDipoleFiltering = new wxRadioButton( m_panel1, ID_DIPOLE_FILTERING_RADIO, wxT("Dipole (2x2, with CrossTalk cancellation)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxrbDipoleFiltering->Enable( false );
	
	bSizer6->Add( m_pwxrbDipoleFiltering, 0, wxALL, 5 );
	
	sbSizer1->Add( bSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mCrossTalkCheck = new wxCheckBox( m_panel1, ID_CROSSTALK_CHECK, wxT("CrossTalk cancel only"), wxDefaultPosition, wxDefaultSize, 0 );
	
	mCrossTalkCheck->Enable( false );
	
	sbSizer1->Add( mCrossTalkCheck, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	mMultiIRsCheck = new wxCheckBox( m_panel1, ID_MULTI_IR_CHECK, wxT("Multiple IRs"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer3->Add( mMultiIRsCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer3->Add( 25, 0, 0, 0, 5 );
	
	mMultiIRNumberLabelStext = new wxStaticText( m_panel1, ID_IR_NUMBER_LABEL_STEXT, wxT("Number of IRs to invert:"), wxDefaultPosition, wxDefaultSize, 0 );
	mMultiIRNumberLabelStext->Wrap( -1 );
	mMultiIRNumberLabelStext->Enable( false );
	
	bSizer3->Add( mMultiIRNumberLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mMultiIRText = new wxTextCtrl( m_panel1, ID_MULTI_IR_TEXT, wxT("1"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	mMultiIRText->Enable( false );
	
	bSizer3->Add( mMultiIRText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer3, 1, wxEXPAND, 5 );
	
	bSizer10->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_panel1->SetSizer( bSizer10 );
	m_panel1->Layout();
	bSizer10->Fit( m_panel1 );
	bSizer7->Add( m_panel1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Filter Calculation Parameters") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 8, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText7 = new wxStaticText( m_panel2, wxID_ANY, wxT("Inverse filter length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer1->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcFilterLength = new wxTextCtrl( m_panel2, ID_FILTER_LENGTH_TEXT, wxT("100000000"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( m_pwxtcFilterLength, 0, wxALL, 5 );
	
	m_staticText18 = new wxStaticText( m_panel2, wxID_ANY, wxT("Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer1->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText9 = new wxStaticText( m_panel2, wxID_ANY, wxT("IN-band Regularisation Parameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer1->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mIRPText = new wxTextCtrl( m_panel2, ID_IRP_TEXT, wxT("0.001"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( mIRPText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText19 = new wxStaticText( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer1->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText10 = new wxStaticText( m_panel2, wxID_ANY, wxT("OUT-band Regularisation Parameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mORPText = new wxTextCtrl( m_panel2, ID_ORP_TEXT, wxT("1.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( mORPText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText20 = new wxStaticText( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer1->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText11 = new wxStaticText( m_panel2, wxID_ANY, wxT("Lower cut frequency:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLowerCutFrqText = new wxTextCtrl( m_panel2, ID_LOWER_CUT_FRQ_TEXT, wxT("80"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( mLowerCutFrqText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText21 = new wxStaticText( m_panel2, wxID_ANY, wxT("Hz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer1->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText12 = new wxStaticText( m_panel2, wxID_ANY, wxT("Higher cut frequency:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer1->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mHigherCutFrqText = new wxTextCtrl( m_panel2, ID_HIGHER_CUT_FRQ_TEXT, wxT("16000"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( mHigherCutFrqText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( m_panel2, wxID_ANY, wxT("Hz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer1->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText13 = new wxStaticText( m_panel2, wxID_ANY, wxT("Transition width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer1->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mTransWidthText = new wxTextCtrl( m_panel2, ID_TRANSITION_WIDTH_TEXT, wxT("0.333"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( mTransWidthText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText23 = new wxStaticText( m_panel2, wxID_ANY, wxT("Octaves"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer1->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText14 = new wxStaticText( m_panel2, wxID_ANY, wxT("Fade-in:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer1->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mFadeInText = new wxTextCtrl( m_panel2, ID_FADE_IN_TEXT, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( mFadeInText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText24 = new wxStaticText( m_panel2, wxID_ANY, wxT("Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer1->Add( m_staticText24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText15 = new wxStaticText( m_panel2, wxID_ANY, wxT("Fade-out:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer1->Add( m_staticText15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mFadeOutText = new wxTextCtrl( m_panel2, ID_FADE_OUT_TEXT, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( mFadeOutText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText25 = new wxStaticText( m_panel2, wxID_ANY, wxT("Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer1->Add( m_staticText25, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer4->Add( fgSizer1, 1, wxEXPAND|wxALL, 5 );
	
	m_panel2->SetSizer( sbSizer4 );
	m_panel2->Layout();
	sbSizer4->Fit( m_panel2 );
	bSizer7->Add( m_panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Averaging Mode") ), wxVERTICAL );
	
	wxString mAverageModeChoiceChoices[] = { wxT("No Average"), wxT("Real, Imaginary"), wxT("Magnitude, Phase"), wxT("Cepstrum") };
	int mAverageModeChoiceNChoices = sizeof( mAverageModeChoiceChoices ) / sizeof( wxString );
	mAverageModeChoice = new wxChoice( m_panel3, ID_AVERAGE_MODE_CHOICE, wxDefaultPosition, wxDefaultSize, mAverageModeChoiceNChoices, mAverageModeChoiceChoices, 0 );
	mAverageModeChoice->SetSelection( 0 );
	sbSizer2->Add( mAverageModeChoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mAverageTypeLabelStext = new wxStaticText( m_panel3, ID_AVERAGE_TYPE_LABEL_STEXT, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	mAverageTypeLabelStext->Wrap( -1 );
	mAverageTypeLabelStext->Enable( false );
	
	fgSizer4->Add( mAverageTypeLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mAverageTypeChoiceChoices[] = { wxT("Linear"), wxT("Octaves") };
	int mAverageTypeChoiceNChoices = sizeof( mAverageTypeChoiceChoices ) / sizeof( wxString );
	mAverageTypeChoice = new wxChoice( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, mAverageTypeChoiceNChoices, mAverageTypeChoiceChoices, 0 );
	mAverageTypeChoice->SetSelection( 0 );
	mAverageTypeChoice->Enable( false );
	
	fgSizer4->Add( mAverageTypeChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText26 = new wxStaticText( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer4->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mAverageWidthLabelStext = new wxStaticText( m_panel3, ID_AVERAGE_WIDTH_LABEL_STEXT, wxT("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	mAverageWidthLabelStext->Wrap( -1 );
	mAverageWidthLabelStext->Enable( false );
	
	fgSizer4->Add( mAverageWidthLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mAverageWidthText = new wxTextCtrl( m_panel3, ID_AVERAGE_WIDTH_TEXT, wxT("5.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	mAverageWidthText->Enable( false );
	
	fgSizer4->Add( mAverageWidthText, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mAvgWidthMUStext = new wxStaticText( m_panel3, ID_AVG_WIDTH_MU_STEXT, wxT("Spectral Points"), wxDefaultPosition, wxDefaultSize, 0 );
	mAvgWidthMUStext->Wrap( -1 );
	mAvgWidthMUStext->Enable( false );
	
	fgSizer4->Add( mAvgWidthMUStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( fgSizer4, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer8->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Gain Settings") ), wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	mAutorangeCheck = new wxCheckBox( m_panel3, ID_AUTORANGE_CHECK, wxT("Autorange"), wxDefaultPosition, wxDefaultSize, 0 );
	mAutorangeCheck->SetValue(true);
	
	bSizer18->Add( mAutorangeCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer18->Add( 25, 0, 0, 0, 5 );
	
	mGainLabelStext = new wxStaticText( m_panel3, ID_GAIN_LABEL_STEXT, wxT("Manual Gain:"), wxDefaultPosition, wxDefaultSize, 0 );
	mGainLabelStext->Wrap( -1 );
	mGainLabelStext->Enable( false );
	
	bSizer18->Add( mGainLabelStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mGainText = new wxTextCtrl( m_panel3, wxID_ANY, wxT("100.0"), wxDefaultPosition, wxSize( 60,-1 ), wxTE_RIGHT );
	mGainText->Enable( false );
	
	bSizer18->Add( mGainText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mGainMUStext = new wxStaticText( m_panel3, ID_GAIN_MU_STEXT, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	mGainMUStext->Wrap( -1 );
	mGainMUStext->Enable( false );
	
	bSizer18->Add( mGainMUStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer3->Add( bSizer18, 1, wxEXPAND, 5 );
	
	bSizer8->Add( sbSizer3, 0, wxEXPAND, 5 );
	
	m_panel3->SetSizer( bSizer8 );
	m_panel3->Layout();
	bSizer8->Fit( m_panel3 );
	bSizer7->Add( m_panel3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer7, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	mHelpBtn = new wxButton( m_panel5, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( mHelpBtn, 0, wxALL, 5 );
	
	
	bSizer19->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCancelBtn = new wxButton( m_panel5, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( mCancelBtn, 0, wxALL, 5 );
	
	mOkBtn = new wxButton( m_panel5, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	mOkBtn->SetDefault(); 
	bSizer19->Add( mOkBtn, 0, wxALL, 5 );
	
	m_panel5->SetSizer( bSizer19 );
	m_panel5->Layout();
	bSizer19->Fit( m_panel5 );
	bSizer1->Add( m_panel5, 0, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_pwxrbMonoFiltering->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( KirkebyDlg::OnMonoFilteringRadio ), NULL, this );
	m_pwxrbStereoFiltering->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( KirkebyDlg::OnStereoFilteringRadio ), NULL, this );
	m_pwxrbDipoleFiltering->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( KirkebyDlg::OnDipoleFilteringRadio ), NULL, this );
	mCrossTalkCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( KirkebyDlg::OnCrossTalkCheck ), NULL, this );
	mMultiIRsCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( KirkebyDlg::OnMultiIRCheck ), NULL, this );
	mMultiIRText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnMultiIrText ), NULL, this );
	mIRPText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnIRPText ), NULL, this );
	mORPText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnORPText ), NULL, this );
	mLowerCutFrqText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnLowerCutFrqText ), NULL, this );
	mHigherCutFrqText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnHigherCutFrqText ), NULL, this );
	mTransWidthText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnTransitionWidthText ), NULL, this );
	mFadeInText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnFadeInText ), NULL, this );
	mFadeOutText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnFadeOutText ), NULL, this );
	mAverageModeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( KirkebyDlg::OnAverageModeChoice ), NULL, this );
	mAverageTypeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( KirkebyDlg::OnAverageTypeChoice ), NULL, this );
	mAverageWidthText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnAverageWidthText ), NULL, this );
	mAutorangeCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( KirkebyDlg::OnAutorangeCheck ), NULL, this );
	mGainText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnGainText ), NULL, this );
	mHelpBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KirkebyDlg::OnHelp ), NULL, this );
	mCancelBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KirkebyDlg::OnCancel ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KirkebyDlg::OnOk ), NULL, this );
}

KirkebyDlg::~KirkebyDlg()
{
	// Disconnect Events
	m_pwxrbMonoFiltering->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( KirkebyDlg::OnMonoFilteringRadio ), NULL, this );
	m_pwxrbStereoFiltering->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( KirkebyDlg::OnStereoFilteringRadio ), NULL, this );
	m_pwxrbDipoleFiltering->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( KirkebyDlg::OnDipoleFilteringRadio ), NULL, this );
	mCrossTalkCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( KirkebyDlg::OnCrossTalkCheck ), NULL, this );
	mMultiIRsCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( KirkebyDlg::OnMultiIRCheck ), NULL, this );
	mMultiIRText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnMultiIrText ), NULL, this );
	mIRPText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnIRPText ), NULL, this );
	mORPText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnORPText ), NULL, this );
	mLowerCutFrqText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnLowerCutFrqText ), NULL, this );
	mHigherCutFrqText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnHigherCutFrqText ), NULL, this );
	mTransWidthText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnTransitionWidthText ), NULL, this );
	mFadeInText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnFadeInText ), NULL, this );
	mFadeOutText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnFadeOutText ), NULL, this );
	mAverageModeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( KirkebyDlg::OnAverageModeChoice ), NULL, this );
	mAverageTypeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( KirkebyDlg::OnAverageTypeChoice ), NULL, this );
	mAverageWidthText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnAverageWidthText ), NULL, this );
	mAutorangeCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( KirkebyDlg::OnAutorangeCheck ), NULL, this );
	mGainText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KirkebyDlg::OnGainText ), NULL, this );
	mHelpBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KirkebyDlg::OnHelp ), NULL, this );
	mCancelBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KirkebyDlg::OnCancel ), NULL, this );
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KirkebyDlg::OnOk ), NULL, this );
}
