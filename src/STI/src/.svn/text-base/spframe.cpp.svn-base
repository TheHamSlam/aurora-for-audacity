///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "spframe.h"

///////////////////////////////////////////////////////////////////////////

STISpectrumDlg::STISpectrumDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800,500 ), wxDefaultSize );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_SPECTRUM_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer17->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer17->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlTop = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxstChnlSel = new wxStaticText( m_pwxpnlTop, wxID_ANY, wxT("Select channel:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstChnlSel->Wrap( -1 );
	bSizer6->Add( m_pwxstChnlSel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchoiceChannelChoices[] = { wxT("Left"), wxT("Right") };
	int m_pwxchoiceChannelNChoices = sizeof( m_pwxchoiceChannelChoices ) / sizeof( wxString );
	m_pwxchoiceChannel = new wxChoice( m_pwxpnlTop, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_pwxchoiceChannelNChoices, m_pwxchoiceChannelChoices, 0 );
	m_pwxchoiceChannel->SetSelection( 0 );
	bSizer6->Add( m_pwxchoiceChannel, 0, wxALL, 5 );
	
	m_pwxpnlTop->SetSizer( bSizer6 );
	m_pwxpnlTop->Layout();
	bSizer6->Fit( m_pwxpnlTop );
	bSizer17->Add( m_pwxpnlTop, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pSplitter = new wxSplitterWindow( this, ID_MAIN_SPLITTER, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_pSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( STISpectrumDlg::m_pSplitterOnIdle ), NULL, this );
	m_pwxpnlUpper = new wxPanel( m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bPlotSizer;
	bPlotSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pSpectrumPlot = new OctaveBandsPlot(m_pwxpnlUpper, ID_LEFT_PLOT);
	bPlotSizer->Add( m_pSpectrumPlot, 1, wxALL|wxEXPAND, 5 );
	
	m_pwxpnlUpper->SetSizer( bPlotSizer );
	m_pwxpnlUpper->Layout();
	bPlotSizer->Fit( m_pwxpnlUpper );
	m_pwxpnlLower = new wxPanel( m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );
	
	m_panel4 = new wxPanel( m_pwxpnlLower, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxgridSpectrumTable = new wxGrid( m_panel4, ID_SPECTRUM_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgridSpectrumTable->CreateGrid( 3, 13 );
	m_pwxgridSpectrumTable->EnableEditing( true );
	m_pwxgridSpectrumTable->EnableGridLines( true );
	m_pwxgridSpectrumTable->EnableDragGridSize( false );
	m_pwxgridSpectrumTable->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgridSpectrumTable->SetColSize( 0, 50 );
	m_pwxgridSpectrumTable->SetColSize( 1, 50 );
	m_pwxgridSpectrumTable->SetColSize( 2, 50 );
	m_pwxgridSpectrumTable->SetColSize( 3, 50 );
	m_pwxgridSpectrumTable->SetColSize( 4, 50 );
	m_pwxgridSpectrumTable->SetColSize( 5, 50 );
	m_pwxgridSpectrumTable->SetColSize( 6, 50 );
	m_pwxgridSpectrumTable->SetColSize( 7, 50 );
	m_pwxgridSpectrumTable->SetColSize( 8, 50 );
	m_pwxgridSpectrumTable->SetColSize( 9, 50 );
	m_pwxgridSpectrumTable->SetColSize( 10, 50 );
	m_pwxgridSpectrumTable->SetColSize( 11, 50 );
	m_pwxgridSpectrumTable->SetColSize( 12, 50 );
	m_pwxgridSpectrumTable->EnableDragColMove( false );
	m_pwxgridSpectrumTable->EnableDragColSize( true );
	m_pwxgridSpectrumTable->SetColLabelSize( 30 );
	m_pwxgridSpectrumTable->SetColLabelValue( 0, wxT(" ") );
	m_pwxgridSpectrumTable->SetColLabelValue( 1, wxT("31.5") );
	m_pwxgridSpectrumTable->SetColLabelValue( 2, wxT("63") );
	m_pwxgridSpectrumTable->SetColLabelValue( 3, wxT("125") );
	m_pwxgridSpectrumTable->SetColLabelValue( 4, wxT("250") );
	m_pwxgridSpectrumTable->SetColLabelValue( 5, wxT("500") );
	m_pwxgridSpectrumTable->SetColLabelValue( 6, wxT("1k") );
	m_pwxgridSpectrumTable->SetColLabelValue( 7, wxT("2k") );
	m_pwxgridSpectrumTable->SetColLabelValue( 8, wxT("4k") );
	m_pwxgridSpectrumTable->SetColLabelValue( 9, wxT("8k") );
	m_pwxgridSpectrumTable->SetColLabelValue( 10, wxT("16k") );
	m_pwxgridSpectrumTable->SetColLabelValue( 11, wxT("A") );
	m_pwxgridSpectrumTable->SetColLabelValue( 12, wxT("Lin") );
	m_pwxgridSpectrumTable->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgridSpectrumTable->EnableDragRowSize( true );
	m_pwxgridSpectrumTable->SetRowLabelSize( 120 );
	m_pwxgridSpectrumTable->SetRowLabelValue( 0, wxT("Background Noise") );
	m_pwxgridSpectrumTable->SetRowLabelValue( 1, wxT("Signal") );
	m_pwxgridSpectrumTable->SetRowLabelValue( 2, wxT("Signal + Noise") );
	m_pwxgridSpectrumTable->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgridSpectrumTable->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	m_pwxgridSpectrumTable->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_TOP );
	bSizer5->Add( m_pwxgridSpectrumTable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel4->SetSizer( bSizer5 );
	m_panel4->Layout();
	bSizer5->Fit( m_panel4 );
	bSizer41->Add( m_panel4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pwxpnlLower->SetSizer( bSizer41 );
	m_pwxpnlLower->Layout();
	bSizer41->Fit( m_pwxpnlLower );
	m_pSplitter->SplitHorizontally( m_pwxpnlUpper, m_pwxpnlLower, 560 );
	bSizer17->Add( m_pSplitter, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer17 );
	this->Layout();
	
	// Connect Events
	m_pwxchoiceChannel->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISpectrumDlg::OnChannelSelect ), NULL, this );
	m_pwxgridSpectrumTable->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( STISpectrumDlg::OnLevelTableLabelClick ), NULL, this );
}

STISpectrumDlg::~STISpectrumDlg()
{
	// Disconnect Events
	m_pwxchoiceChannel->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISpectrumDlg::OnChannelSelect ), NULL, this );
	m_pwxgridSpectrumTable->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( STISpectrumDlg::OnLevelTableLabelClick ), NULL, this );
}
