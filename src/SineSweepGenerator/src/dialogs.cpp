///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

///////////////////////////////////////////////////////////////////////////

SsgDlg::SsgDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( 380,54 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Sweep") ), wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxstFrom = new wxStaticText( m_panel1, wxID_ANY, wxT("From"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstFrom->Wrap( -1 );
	bSizer9->Add( m_pwxstFrom, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcFrom = new wxTextCtrl( m_panel1, ID_START_FREQ_TEXT, wxT("20.0"), wxDefaultPosition, wxSize( -1,25 ), wxTE_RIGHT );
	bSizer9->Add( m_pwxtcFrom, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstHzTo = new wxStaticText( m_panel1, wxID_ANY, wxT("Hz  to"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstHzTo->Wrap( -1 );
	bSizer9->Add( m_pwxstHzTo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcTo = new wxTextCtrl( m_panel1, ID_END_FREQ_TEXT, wxT("20000.0"), wxDefaultPosition, wxSize( -1,25 ), wxTE_RIGHT );
	bSizer9->Add( m_pwxtcTo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcHz = new wxStaticText( m_panel1, wxID_ANY, wxT("Hz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxtcHz->Wrap( -1 );
	bSizer9->Add( m_pwxtcHz, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer9, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( m_panel1, wxID_ANY, wxT("Duration"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer1->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pwxtcDuration = new wxTextCtrl( m_panel1, ID_DURATION_TEXT, wxT("10.0"), wxDefaultPosition, wxSize( -1,25 ), wxTE_RIGHT );
	m_pwxtcDuration->SetToolTip( wxT("Duration of the sweep; if the number is < 100 is taken as seconds, otherwise it's taken as samples count.") );
	
	fgSizer1->Add( m_pwxtcDuration, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( m_panel1, wxID_ANY, wxT("s or samples"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer1->Add( m_staticText9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText4 = new wxStaticText( m_panel1, wxID_ANY, wxT("Amplitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pwxtcAmplitude = new wxTextCtrl( m_panel1, ID_AMPLITUDE_TEXT, wxT("1.0"), wxDefaultPosition, wxSize( -1,25 ), wxTE_RIGHT );
	fgSizer1->Add( m_pwxtcAmplitude, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( m_panel1, wxID_ANY, wxT("(0 - 1.0)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText17 = new wxStaticText( m_panel1, wxID_ANY, wxT("Channels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer1->Add( m_staticText17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pwxtcChnlsCount = new wxTextCtrl( m_panel1, ID_CHANNELS_TEXT, wxT("1"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer1->Add( m_pwxtcChnlsCount, 0, wxALL, 5 );
	
	m_staticText18 = new wxStaticText( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer1->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( fgSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_radioBtn1 = new wxRadioButton( m_panel1, ID_LINEAR_SWEEP_RADIO, wxT("Linear Sweep"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_radioBtn1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_radioBtn2 = new wxRadioButton( m_panel1, ID_LOG_SWEEP_RADIO, wxT("Log Sweep"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtn2->SetValue( true ); 
	bSizer10->Add( m_radioBtn2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_radioBtn3 = new wxRadioButton( m_panel1, ID_PINK_SWEEP_RADIO, wxT("Pink Sweep"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_radioBtn3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sbSizer1->Add( bSizer10, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer2->Add( sbSizer1, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Fade-in and Fade-out duration") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText12 = new wxStaticText( m_panel1, wxID_ANY, wxT("Fade-in"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer2->Add( m_staticText12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText13 = new wxStaticText( m_panel1, wxID_ANY, wxT("(s or samples)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer2->Add( m_staticText13, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_pwxtcFadeIn = new wxTextCtrl( m_panel1, ID_FADE_IN_TEXT, wxT("0.1"), wxDefaultPosition, wxSize( 60,25 ), wxTE_RIGHT );
	fgSizer2->Add( m_pwxtcFadeIn, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxString m_pwxchoiceFadeInChoices[] = { wxT("Rectangular"), wxT("Hamming"), wxT("Hann"), wxT("1/4 Sine"), wxT("Linear"), wxT("Gaussian"), wxT("Blackmann"), wxT("Black/Harris"), wxT("Log") };
	int m_pwxchoiceFadeInNChoices = sizeof( m_pwxchoiceFadeInChoices ) / sizeof( wxString );
	m_pwxchoiceFadeIn = new wxChoice( m_panel1, ID_FADE_IN_CHOICE, wxDefaultPosition, wxSize( -1,25 ), m_pwxchoiceFadeInNChoices, m_pwxchoiceFadeInChoices, 0 );
	m_pwxchoiceFadeIn->SetSelection( 2 );
	fgSizer2->Add( m_pwxchoiceFadeIn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText14 = new wxStaticText( m_panel1, wxID_ANY, wxT("Fade-out"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer2->Add( m_staticText14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText15 = new wxStaticText( m_panel1, wxID_ANY, wxT("(s or samples)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer2->Add( m_staticText15, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pwxtcFadeOut = new wxTextCtrl( m_panel1, ID_FADE_OUT_TEXT, wxT("0.1"), wxDefaultPosition, wxSize( 60,25 ), wxTE_RIGHT );
	fgSizer2->Add( m_pwxtcFadeOut, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxString m_pwxchoiceFadeOutChoices[] = { wxT("Rectangular"), wxT("Hamming"), wxT("Hann"), wxT("1/4 Sine"), wxT("Linear"), wxT("Gaussian"), wxT("Blackmann"), wxT("Black/Harris"), wxT("Log") };
	int m_pwxchoiceFadeOutNChoices = sizeof( m_pwxchoiceFadeOutChoices ) / sizeof( wxString );
	m_pwxchoiceFadeOut = new wxChoice( m_panel1, ID_FADE_OUT_CHOICE, wxDefaultPosition, wxSize( -1,25 ), m_pwxchoiceFadeOutNChoices, m_pwxchoiceFadeOutChoices, 0 );
	m_pwxchoiceFadeOut->SetSelection( 2 );
	fgSizer2->Add( m_pwxchoiceFadeOut, 0, wxALL, 5 );
	
	sbSizer4->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer4, 1, wxEXPAND|wxALL, 5 );
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Silence") ), wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( m_panel3, wxID_ANY, wxT("Duration (s or samples)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	sbSizer2->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcSilenceDur = new wxTextCtrl( m_panel3, ID_SILENCE_TEXT, wxT("8.0"), wxDefaultPosition, wxSize( -1,25 ), wxTE_RIGHT );
	sbSizer2->Add( m_pwxtcSilenceDur, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( sbSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, wxT("Repetitions") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText6 = new wxStaticText( m_panel3, wxID_ANY, wxT("Number of cycles"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer3->Add( m_staticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pwxtcCyclesCount = new wxTextCtrl( m_panel3, ID_REPETITIONS_TEXT, wxT("1"), wxDefaultPosition, wxSize( -1,25 ), wxTE_RIGHT );
	fgSizer3->Add( m_pwxtcCyclesCount, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText16 = new wxStaticText( m_panel3, wxID_ANY, wxT("Level variation (dB/rep)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer3->Add( m_staticText16, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcDeltaL = new wxTextCtrl( m_panel3, ID_DELTA_L_TEXT, wxT("0.0"), wxDefaultPosition, wxSize( -1,25 ), wxTE_RIGHT );
	fgSizer3->Add( m_pwxtcDeltaL, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer3->Add( fgSizer3, 1, wxEXPAND|wxALL, 5 );
	
	bSizer7->Add( sbSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_panel3->SetSizer( bSizer7 );
	m_panel3->Layout();
	bSizer7->Fit( m_panel3 );
	bSizer1->Add( m_panel3, 1, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxchkPulses = new wxCheckBox( m_panel2, ID_CTRL_PULSES_CHECK, wxT("Add a control pulses track"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer6->Add( m_pwxchkPulses, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel2->SetSizer( bSizer6 );
	m_panel2->Layout();
	bSizer6->Fit( m_panel2 );
	bSizer1->Add( m_panel2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlBottom = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnHelp = new wxButton( m_pwxpnlBottom, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_pwxbtnHelp, 0, wxALL, 5 );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxbtnCancel = new wxButton( m_pwxpnlBottom, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_pwxbtnCancel, 0, wxALL, 5 );
	
	m_pwxbtnGenerate = new wxButton( m_pwxpnlBottom, wxID_OK, wxT("Generate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnGenerate->SetDefault(); 
	bSizer4->Add( m_pwxbtnGenerate, 0, wxALL, 5 );
	
	m_pwxpnlBottom->SetSizer( bSizer4 );
	m_pwxpnlBottom->Layout();
	bSizer4->Fit( m_pwxpnlBottom );
	bSizer1->Add( m_pwxpnlBottom, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_pwxtcFrom->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnStartFrequencyText ), NULL, this );
	m_pwxtcTo->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnEndFrequencyText ), NULL, this );
	m_pwxtcDuration->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnSweepDurationText ), NULL, this );
	m_pwxtcAmplitude->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnAmplitudeText ), NULL, this );
	m_radioBtn1->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( SsgDlg::OnLinearSweepRadio ), NULL, this );
	m_radioBtn2->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( SsgDlg::OnLogSweepRadio ), NULL, this );
	m_radioBtn3->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( SsgDlg::OnPinkSweepRadio ), NULL, this );
	m_pwxtcFadeIn->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnFadeInText ), NULL, this );
	m_pwxchoiceFadeIn->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SsgDlg::OnFadeInChoice ), NULL, this );
	m_pwxtcFadeOut->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnFadeOutText ), NULL, this );
	m_pwxchoiceFadeOut->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SsgDlg::OnFadeOutChoice ), NULL, this );
	m_pwxtcSilenceDur->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnSilenceDurationText ), NULL, this );
	m_pwxtcCyclesCount->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnRepetitionsText ), NULL, this );
	m_pwxtcDeltaL->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnDeltaLText ), NULL, this );
	m_pwxchkPulses->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SsgDlg::OnControlPulsesCheck ), NULL, this );
	m_pwxbtnHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SsgDlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SsgDlg::OnCancel ), NULL, this );
	m_pwxbtnGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SsgDlg::OnOk ), NULL, this );
}

SsgDlg::~SsgDlg()
{
	// Disconnect Events
	m_pwxtcFrom->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnStartFrequencyText ), NULL, this );
	m_pwxtcTo->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnEndFrequencyText ), NULL, this );
	m_pwxtcDuration->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnSweepDurationText ), NULL, this );
	m_pwxtcAmplitude->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnAmplitudeText ), NULL, this );
	m_radioBtn1->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( SsgDlg::OnLinearSweepRadio ), NULL, this );
	m_radioBtn2->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( SsgDlg::OnLogSweepRadio ), NULL, this );
	m_radioBtn3->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( SsgDlg::OnPinkSweepRadio ), NULL, this );
	m_pwxtcFadeIn->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnFadeInText ), NULL, this );
	m_pwxchoiceFadeIn->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SsgDlg::OnFadeInChoice ), NULL, this );
	m_pwxtcFadeOut->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnFadeOutText ), NULL, this );
	m_pwxchoiceFadeOut->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SsgDlg::OnFadeOutChoice ), NULL, this );
	m_pwxtcSilenceDur->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnSilenceDurationText ), NULL, this );
	m_pwxtcCyclesCount->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnRepetitionsText ), NULL, this );
	m_pwxtcDeltaL->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SsgDlg::OnDeltaLText ), NULL, this );
	m_pwxchkPulses->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SsgDlg::OnControlPulsesCheck ), NULL, this );
	m_pwxbtnHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SsgDlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SsgDlg::OnCancel ), NULL, this );
	m_pwxbtnGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SsgDlg::OnOk ), NULL, this );
}
