///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

///////////////////////////////////////////////////////////////////////////

PeakVueSetupDlg::PeakVueSetupDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_pwxpnlLogo, 0, wxLEFT|wxRIGHT|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlMain = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlMain, wxID_ANY, wxT("Input") ), wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxstInSelect = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("Select track:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstInSelect->Wrap( -1 );
	bSizer5->Add( m_pwxstInSelect, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_pwxchTrackChoices;
	m_pwxchTrack = new wxChoice( m_pwxpnlMain, ID_TRACK_SELECT_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchTrackChoices, 0 );
	m_pwxchTrack->SetSelection( 0 );
	m_pwxchTrack->SetMinSize( wxSize( 150,-1 ) );
	
	bSizer5->Add( m_pwxchTrack, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_pwxstRateLabel = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("Sample Rate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstRateLabel->Wrap( -1 );
	fgSizer1->Add( m_pwxstRateLabel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstRate = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("48000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_pwxstRate->Wrap( -1 );
	fgSizer1->Add( m_pwxstRate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstRateHz = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("Hz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstRateHz->Wrap( -1 );
	fgSizer1->Add( m_pwxstRateHz, 0, wxALL, 5 );
	
	m_pwxstLengthLabel = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("Length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstLengthLabel->Wrap( -1 );
	fgSizer1->Add( m_pwxstLengthLabel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstLength = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("600.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstLength->Wrap( -1 );
	fgSizer1->Add( m_pwxstLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstLengthSec = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("s"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstLengthSec->Wrap( -1 );
	fgSizer1->Add( m_pwxstLengthSec, 0, wxALL, 5 );
	
	sbSizer1->Add( fgSizer1, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer4->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlMain, wxID_ANY, wxT("Setup") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 4, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_pwxstPeakBlLabel = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("Peak block size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstPeakBlLabel->Wrap( -1 );
	fgSizer2->Add( m_pwxstPeakBlLabel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcPeakBlockSize = new wxTextCtrl( m_pwxpnlMain, ID_PEAK_BLOCK_SIZE_TC, wxT("5.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer2->Add( m_pwxtcPeakBlockSize, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_pwxstPeakBlMs = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstPeakBlMs->Wrap( -1 );
	fgSizer2->Add( m_pwxstPeakBlMs, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstPeakTypeLabel = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("Peak type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstPeakTypeLabel->Wrap( -1 );
	fgSizer2->Add( m_pwxstPeakTypeLabel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchPeakTypeChoices[] = { wxT("In signo"), wxT("Absolute"), wxT("Square") };
	int m_pwxchPeakTypeNChoices = sizeof( m_pwxchPeakTypeChoices ) / sizeof( wxString );
	m_pwxchPeakType = new wxChoice( m_pwxpnlMain, ID_PEAK_BLOCK_TYPE_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchPeakTypeNChoices, m_pwxchPeakTypeChoices, 0 );
	m_pwxchPeakType->SetSelection( 0 );
	fgSizer2->Add( m_pwxchPeakType, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_pwxstSpace1 = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSpace1->Wrap( -1 );
	fgSizer2->Add( m_pwxstSpace1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstFftSizeLabel = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("FFT size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstFftSizeLabel->Wrap( -1 );
	fgSizer2->Add( m_pwxstFftSizeLabel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcFftSize = new wxTextCtrl( m_pwxpnlMain, wxID_ANY, wxT("1024"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer2->Add( m_pwxtcFftSize, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_pwxstSmpl = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("smpls"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSmpl->Wrap( -1 );
	fgSizer2->Add( m_pwxstSmpl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstWinLabel = new wxStaticText( m_pwxpnlMain, wxID_ANY, wxT("Window type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstWinLabel->Wrap( -1 );
	fgSizer2->Add( m_pwxstWinLabel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchWinTypeChoices[] = { wxT("Rectangular"), wxT("Hanning"), wxT("Blackman-Harris"), wxT("Flat top"), wxT("Triangular"), wxT("Half-sine") };
	int m_pwxchWinTypeNChoices = sizeof( m_pwxchWinTypeChoices ) / sizeof( wxString );
	m_pwxchWinType = new wxChoice( m_pwxpnlMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_pwxchWinTypeNChoices, m_pwxchWinTypeChoices, 0 );
	m_pwxchWinType->SetSelection( 0 );
	fgSizer2->Add( m_pwxchWinType, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	sbSizer2->Add( fgSizer2, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer4->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	m_pwxbtnAnalyze = new wxButton( m_pwxpnlMain, ID_ANALYZE_BTN, wxT("Analyze"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_pwxbtnAnalyze, 0, wxALL|wxEXPAND, 5 );
	
	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxUpperSplitter = new wxSplitterWindow( m_pwxpnlMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_pwxUpperSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( PeakVueSetupDlg::m_pwxUpperSplitterOnIdle ), NULL, this );
	m_pwxUpperPlotPanel = new wxPanel( m_pwxUpperSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_pUpperPlotScroller = new wxScrolledWindow( m_pwxUpperPlotPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_pUpperPlotScroller->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_pTimePlot = new PVRealDataPlot(m_pUpperPlotScroller, ID_TIME_PLOT);
	bSizer11->Add( m_pTimePlot, 1, wxALL|wxEXPAND, 5 );
	
	m_pUpperPlotScroller->SetSizer( bSizer11 );
	m_pUpperPlotScroller->Layout();
	bSizer11->Fit( m_pUpperPlotScroller );
	bSizer8->Add( m_pUpperPlotScroller, 1, wxEXPAND | wxALL, 5 );
	
	m_pwxUpperPlotPanel->SetSizer( bSizer8 );
	m_pwxUpperPlotPanel->Layout();
	bSizer8->Fit( m_pwxUpperPlotPanel );
	m_panel5 = new wxPanel( m_pwxUpperSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxLowerSplitter = new wxSplitterWindow( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_pwxLowerSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( PeakVueSetupDlg::m_pwxLowerSplitterOnIdle ), NULL, this );
	m_pwxMiddlePlotPanel = new wxPanel( m_pwxLowerSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_pMiddlePlotScroller = new wxScrolledWindow( m_pwxMiddlePlotPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_pMiddlePlotScroller->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_pSpectrumPlot = new PVSpectrumMagnitudePlot(m_pMiddlePlotScroller, ID_SPECTRUM_PLOT);
	bSizer12->Add( m_pSpectrumPlot, 1, wxALL|wxEXPAND, 5 );
	
	m_pMiddlePlotScroller->SetSizer( bSizer12 );
	m_pMiddlePlotScroller->Layout();
	bSizer12->Fit( m_pMiddlePlotScroller );
	bSizer9->Add( m_pMiddlePlotScroller, 1, wxEXPAND | wxALL, 5 );
	
	m_pwxMiddlePlotPanel->SetSizer( bSizer9 );
	m_pwxMiddlePlotPanel->Layout();
	bSizer9->Fit( m_pwxMiddlePlotPanel );
	m_pwxLowerPlotPanel = new wxPanel( m_pwxLowerSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_pLowerPlotScroller = new wxScrolledWindow( m_pwxLowerPlotPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_pLowerPlotScroller->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_pAcorrPlot = new PVRealDataPlot(m_pLowerPlotScroller, ID_ACORR_PLOT);
	bSizer13->Add( m_pAcorrPlot, 1, wxALL|wxEXPAND, 5 );
	
	m_pLowerPlotScroller->SetSizer( bSizer13 );
	m_pLowerPlotScroller->Layout();
	bSizer13->Fit( m_pLowerPlotScroller );
	bSizer10->Add( m_pLowerPlotScroller, 1, wxEXPAND | wxALL, 5 );
	
	m_pwxLowerPlotPanel->SetSizer( bSizer10 );
	m_pwxLowerPlotPanel->Layout();
	bSizer10->Fit( m_pwxLowerPlotPanel );
	m_pwxLowerSplitter->SplitHorizontally( m_pwxMiddlePlotPanel, m_pwxLowerPlotPanel, 0 );
	bSizer7->Add( m_pwxLowerSplitter, 1, wxEXPAND, 5 );
	
	m_panel5->SetSizer( bSizer7 );
	m_panel5->Layout();
	bSizer7->Fit( m_panel5 );
	m_pwxUpperSplitter->SplitHorizontally( m_pwxUpperPlotPanel, m_panel5, 0 );
	bSizer6->Add( m_pwxUpperSplitter, 1, wxEXPAND, 5 );
	
	bSizer3->Add( bSizer6, 1, wxEXPAND, 5 );
	
	m_pwxpnlMain->SetSizer( bSizer3 );
	m_pwxpnlMain->Layout();
	bSizer3->Fit( m_pwxpnlMain );
	bSizer1->Add( m_pwxpnlMain, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlButtons = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnHelp = new wxButton( m_pwxpnlButtons, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_pwxbtnHelp, 0, wxALL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxbtnCancel = new wxButton( m_pwxpnlButtons, wxID_CLOSE, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_pwxbtnCancel, 0, wxALL, 5 );
	
	m_pwxpnlButtons->SetSizer( bSizer2 );
	m_pwxpnlButtons->Layout();
	bSizer2->Fit( m_pwxpnlButtons );
	bSizer1->Add( m_pwxpnlButtons, 0, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( PeakVueSetupDlg::OnCloseDialog ) );
	m_pwxbtnAnalyze->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PeakVueSetupDlg::OnAnalyze ), NULL, this );
	m_pwxbtnHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PeakVueSetupDlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PeakVueSetupDlg::OnCloseBtn ), NULL, this );
}

PeakVueSetupDlg::~PeakVueSetupDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( PeakVueSetupDlg::OnCloseDialog ) );
	m_pwxbtnAnalyze->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PeakVueSetupDlg::OnAnalyze ), NULL, this );
	m_pwxbtnHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PeakVueSetupDlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PeakVueSetupDlg::OnCloseBtn ), NULL, this );
}
