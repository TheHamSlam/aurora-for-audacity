///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

#include "../res/down.xpm"
#include "../res/left.xpm"
#include "../res/right.xpm"
#include "../res/up.xpm"

///////////////////////////////////////////////////////////////////////////

AFTrackSelectorDlg::AFTrackSelectorDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer10->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer10->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	m_panel9 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( m_panel9, wxID_ANY, wxT("Step 1: Select Tracks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer22->Add( m_staticText12, 0, wxALL, 5 );
	
	m_panel9->SetSizer( bSizer22 );
	m_panel9->Layout();
	bSizer22->Fit( m_panel9 );
	bSizer10->Add( m_panel9, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer10->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	m_panel10 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText8 = new wxStaticText( m_panel10, wxID_ANY, wxT("Selected tracks:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer12->Add( m_staticText8, 0, wxALL, 5 );
	
	mAvailableList = new wxListCtrl( m_panel10, ID_AVAIL_TRACKS_LIST, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxRAISED_BORDER );
	mAvailableList->SetMinSize( wxSize( -1,150 ) );
	
	bSizer12->Add( mAvailableList, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button6 = new wxButton( m_panel10, ID_TO_AUDIO_DATA_BTN, wxT("To Audio Data"), wxDefaultPosition, wxSize( 130,-1 ), 0 );
	m_button6->SetToolTip( wxT("Move selected track(s) to Audio Data list.") );
	
	bSizer13->Add( m_button6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_button5 = new wxButton( m_panel10, ID_TO_IRs_BTN, wxT("To Filters"), wxDefaultPosition, wxSize( 130,-1 ), 0 );
	m_button5->SetToolTip( wxT("Move selected track(s) to Filters list.") );
	
	bSizer13->Add( m_button5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer12->Add( bSizer13, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel10->SetSizer( bSizer12 );
	m_panel10->Layout();
	bSizer12->Fit( m_panel10 );
	bSizer10->Add( m_panel10, 1, wxEXPAND | wxALL, 5 );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText11 = new wxStaticText( m_panel4, wxID_ANY, wxT("Audio Datas:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer16->Add( m_staticText11, 0, wxALL, 5 );
	
	mAudioDataList = new wxListCtrl( m_panel4, ID_AUDIO_DATA_LIST, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxRAISED_BORDER );
	mAudioDataList->SetMinSize( wxSize( 120,150 ) );
	
	bSizer16->Add( mAudioDataList, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer16, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_bpButton1 = new wxBitmapButton( m_panel4, ID_MOVE_UP_BTN, wxBitmap( up_xpm ), wxDefaultPosition, wxSize( 30,30 ), wxBU_AUTODRAW );
	m_bpButton1->SetToolTip( wxT("Move selected track up in the list.") );
	
	m_bpButton1->SetToolTip( wxT("Move selected track up in the list.") );
	
	bSizer15->Add( m_bpButton1, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bpButton2 = new wxBitmapButton( m_panel4, ID_TO_LEFT_BTN, wxBitmap( left_xpm ), wxDefaultPosition, wxSize( 30,30 ), wxBU_AUTODRAW );
	m_bpButton2->SetToolTip( wxT("Move selected track(s) from Filters to Audio Datas list.") );
	
	m_bpButton2->SetToolTip( wxT("Move selected track(s) from Filters to Audio Datas list.") );
	
	bSizer191->Add( m_bpButton2, 0, wxLEFT, 5 );
	
	
	bSizer191->Add( 30, 0, 0, 0, 5 );
	
	m_bpButton3 = new wxBitmapButton( m_panel4, ID_TO_RIGHT_BTN, wxBitmap( right_xpm ), wxDefaultPosition, wxSize( 30,30 ), wxBU_AUTODRAW );
	m_bpButton3->SetToolTip( wxT("Move selected track(s) from Audio Datas to Filters list.") );
	
	m_bpButton3->SetToolTip( wxT("Move selected track(s) from Audio Datas to Filters list.") );
	
	bSizer191->Add( m_bpButton3, 0, wxRIGHT, 5 );
	
	bSizer15->Add( bSizer191, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_bpButton4 = new wxBitmapButton( m_panel4, ID_MOVE_DOWN_BTN, wxBitmap( down_xpm ), wxDefaultPosition, wxSize( 30,30 ), wxBU_AUTODRAW );
	m_bpButton4->SetToolTip( wxT("Move selected track down in the list.") );
	
	m_bpButton4->SetToolTip( wxT("Move selected track down in the list.") );
	
	bSizer15->Add( m_bpButton4, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer15->Add( 0, 10, 0, 0, 5 );
	
	m_button9 = new wxButton( m_panel4, ID_REMOVE_BTN, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button9->SetToolTip( wxT("Remove selected track(s) from list.") );
	
	bSizer15->Add( m_button9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer11->Add( bSizer15, 0, wxALIGN_BOTTOM, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( m_panel4, wxID_ANY, wxT("Filters (IRs):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer14->Add( m_staticText9, 0, wxALL, 5 );
	
	mFilterList = new wxListCtrl( m_panel4, ID_IR_LIST, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxRAISED_BORDER );
	mFilterList->SetMinSize( wxSize( 120,150 ) );
	
	bSizer14->Add( mFilterList, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer14, 1, wxEXPAND, 5 );
	
	m_panel4->SetSizer( bSizer11 );
	m_panel4->Layout();
	bSizer11->Fit( m_panel4 );
	bSizer10->Add( m_panel4, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel11 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	mMatrixModeCheck = new wxCheckBox( m_panel11, ID_MATRIX_MODE_CHECK, wxT("Force Matrix Mode"), wxDefaultPosition, wxDefaultSize, 0 );
	
	mMatrixModeCheck->Enable( false );
	mMatrixModeCheck->SetToolTip( wxT("When there are M audio data vectors and N filters, with M != N, the matrix convolution product is automatically selected. \nOtherwise, when M = N, a \"row to row\" convolution product is performed, with N output tracks. If this control is checked, then the matrix convolution product is forced. Pay attention: filters tracks must be in \"matrix\" form, so they will be splitted in M \"columns\".") );
	
	bSizer19->Add( mMatrixModeCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer19->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mOneForAllCheck = new wxCheckBox( m_panel11, ID_ONE_FOR_ALL_CHECK, wxT("One for All"), wxDefaultPosition, wxDefaultSize, 0 );
	
	mOneForAllCheck->SetToolTip( wxT("It uses the first filter of the list for each audio data vector (only raw to raw mode).") );
	
	bSizer19->Add( mOneForAllCheck, 0, wxALL, 5 );
	
	m_panel11->SetSizer( bSizer19 );
	m_panel11->Layout();
	bSizer19->Fit( m_panel11 );
	bSizer10->Add( m_panel11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer10->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	m_panel6 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	mHelpBtn = new wxButton( m_panel6, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( mHelpBtn, 0, wxALL, 5 );
	
	
	bSizer17->Add( 0, 0, 1, 0, 5 );
	
	mCancelBtn = new wxButton( m_panel6, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( mCancelBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mOkBtn = new wxButton( m_panel6, wxID_OK, wxT("Continue"), wxDefaultPosition, wxDefaultSize, 0 );
	mOkBtn->SetDefault(); 
	mOkBtn->SetToolTip( wxT("Continue to convolution setup dialog.") );
	
	bSizer17->Add( mOkBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_panel6->SetSizer( bSizer17 );
	m_panel6->Layout();
	bSizer17->Fit( m_panel6 );
	bSizer18->Add( m_panel6, 0, wxALL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_panel5->SetSizer( bSizer18 );
	m_panel5->Layout();
	bSizer18->Fit( m_panel5 );
	bSizer10->Add( m_panel5, 0, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	this->SetSizer( bSizer10 );
	this->Layout();
	bSizer10->Fit( this );
	
	// Connect Events
	mAvailableList->Connect( wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler( AFTrackSelectorDlg::OnAvailableDragInit ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::ToAudioDataBtn ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnToIRsBtn ), NULL, this );
	mAudioDataList->Connect( wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler( AFTrackSelectorDlg::OnAudioDataDragInit ), NULL, this );
	m_bpButton1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnMoveUpBtn ), NULL, this );
	m_bpButton2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnToLeftBtn ), NULL, this );
	m_bpButton3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnToRightBtn ), NULL, this );
	m_bpButton4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnMoveDownBtn ), NULL, this );
	m_button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnRemoveBtn ), NULL, this );
	mFilterList->Connect( wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler( AFTrackSelectorDlg::OnFilterDragInit ), NULL, this );
	mMatrixModeCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnMatrixModeCheck ), NULL, this );
	mOneForAllCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnOneForAllCheck ), NULL, this );
	mHelpBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnHelp ), NULL, this );
	mCancelBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnCancel ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFTrackSelectorDlg::OnOK ), NULL, this );
}

AFTrackSelectorDlg::~AFTrackSelectorDlg()
{
}

AFConvolverDlg::AFConvolverDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline6, 0, wxEXPAND|wxALL, 5 );
	
	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( m_panel8, wxID_ANY, wxT("Step 2: setup convolution"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer21->Add( m_staticText11, 0, wxALL, 5 );
	
	m_panel8->SetSizer( bSizer21 );
	m_panel8->Layout();
	bSizer21->Fit( m_panel8 );
	bSizer1->Add( m_panel8, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer51;
	sbSizer51 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Impulse Response(s) RMS") ), wxVERTICAL );
	
	mPlot = new ConvPlot((wxWindow *)m_panel1, (wxWindowID)ID_PLOT);
	mPlot->SetMinSize( wxSize( 450,200 ) );
	
	sbSizer51->Add( mPlot, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer2->Add( sbSizer51, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Autorange") ), wxVERTICAL );
	
	mFullAutorangeCheck = new wxCheckBox( m_panel2, ID_FULL_AUTORANGE_CHECK, wxT("Full Autorange - Remove DC (2 passes)"), wxDefaultPosition, wxDefaultSize, 0 );
	mFullAutorangeCheck->SetValue(true);
	
	sbSizer1->Add( mFullAutorangeCheck, 0, wxALL, 5 );
	
	mFBAutorangeCheck = new wxCheckBox( m_panel2, ID_FB_AUTORANGE, wxT("First Block autorange"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer1->Add( mFBAutorangeCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer6->Add( 5, 0, 0, 0, 5 );
	
	mGainStext = new wxStaticText( m_panel2, ID_GAIN_LABEL_ST, wxT("Gain:"), wxDefaultPosition, wxDefaultSize, 0 );
	mGainStext->Wrap( -1 );
	bSizer6->Add( mGainStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mGainText = new wxTextCtrl( m_panel2, ID_GAIN_TEXT, wxT("0.00"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	mGainText->SetMinSize( wxSize( 80,25 ) );
	
	bSizer6->Add( mGainText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mdBStext = new wxStaticText( m_panel2, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	mdBStext->Wrap( -1 );
	bSizer6->Add( mdBStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer6, 1, wxEXPAND, 5 );
	
	bSizer4->Add( sbSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Advanced") ), wxVERTICAL );
	
	mTimeReversedCheck = new wxCheckBox( m_panel2, ID_TREV_IR_CHECK, wxT("TimeReversed Imp. Resp."), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer2->Add( mTimeReversedCheck, 0, wxALL, 5 );
	
	mCrossTalkCheck = new wxCheckBox( m_panel2, ID_CROSSTALK_CHECK, wxT("Crosstalk Cancel Mode"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer2->Add( mCrossTalkCheck, 0, wxALL, 5 );
	
	mPreserveLengthCheck = new wxCheckBox( m_panel2, ID_PRES_LENGTH_CHECK, wxT("Preserve Length"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer2->Add( mPreserveLengthCheck, 0, wxALL, 5 );
	
	bSizer4->Add( sbSizer2, 0, wxALL, 5 );
	
	m_panel2->SetSizer( bSizer4 );
	m_panel2->Layout();
	bSizer4->Fit( m_panel2 );
	bSizer1->Add( m_panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Info") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 4, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( m_panel3, wxID_ANY, wxT("Audio Data:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer1->Add( m_staticText2, 0, wxALL, 5 );
	
	mAudioDataStext = new wxStaticText( m_panel3, ID_AUDIO_DATA_STEXT, wxT("44100 Hz/16 bits/Mono/100000 Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	mAudioDataStext->Wrap( -1 );
	fgSizer1->Add( mAudioDataStext, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( m_panel3, wxID_ANY, wxT("Impulse Resp.:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALL, 5 );
	
	mFilterStext = new wxStaticText( m_panel3, ID_IR_DATA_STEXT, wxT("44100 Hz/16 bits/Mono/100000 Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	mFilterStext->Wrap( -1 );
	fgSizer1->Add( mFilterStext, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( m_panel3, wxID_ANY, wxT("FFT Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL, 5 );
	
	mFftSizeStext = new wxStaticText( m_panel3, ID_FFT_SIZE_STEXT, wxT("65535 Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	mFftSizeStext->Wrap( -1 );
	fgSizer1->Add( mFftSizeStext, 0, wxALL, 5 );
	
	m_staticText14 = new wxStaticText( m_panel3, wxID_ANY, wxT("Mode:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer1->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mModeStext = new wxStaticText( m_panel3, ID_MODE_STEXT, wxT("Matrix Convolution Product"), wxDefaultPosition, wxDefaultSize, 0 );
	mModeStext->Wrap( -1 );
	fgSizer1->Add( mModeStext, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer5->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	bSizer9->Add( sbSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_panel3->SetSizer( bSizer9 );
	m_panel3->Layout();
	bSizer9->Fit( m_panel3 );
	bSizer1->Add( m_panel3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	mHelpBtn = new wxButton( m_panel7, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( mHelpBtn, 0, wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCancelBtn = new wxButton( m_panel7, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( mCancelBtn, 0, wxALL, 5 );
	
	mOkBtn = new wxButton( m_panel7, wxID_OK, wxT("Calculate!"), wxDefaultPosition, wxDefaultSize, 0 );
	mOkBtn->SetDefault(); 
	bSizer3->Add( mOkBtn, 0, wxALL, 5 );
	
	m_panel7->SetSizer( bSizer3 );
	m_panel7->Layout();
	bSizer3->Fit( m_panel7 );
	bSizer1->Add( m_panel7, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	mFullAutorangeCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnFullAutorangeCheck ), NULL, this );
	mFBAutorangeCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnFirstBlockAutorangeCheck ), NULL, this );
	mGainText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AFConvolverDlg::OnGainText ), NULL, this );
	mTimeReversedCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnTimeReverseIrCheck ), NULL, this );
	mCrossTalkCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnCrosstalkCancelCheck ), NULL, this );
	mPreserveLengthCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnPreserveLengthCheck ), NULL, this );
	mHelpBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnHelp ), NULL, this );
	mCancelBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnCancel ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AFConvolverDlg::OnOk ), NULL, this );
}

AFConvolverDlg::~AFConvolverDlg()
{
}
