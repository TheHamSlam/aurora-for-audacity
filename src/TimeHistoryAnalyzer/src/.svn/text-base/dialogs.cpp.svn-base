///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "nbook.h"

#include "dialogs.h"

///////////////////////////////////////////////////////////////////////////

THADlg::THADlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxSize( -1,-1 ) );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxpnlSetup = new wxPanel( m_pNotebook, ID_SETUP_PAGE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbGridSizer;
	sbGridSizer = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlSetup, wxID_ANY, wxT("Track(s) to analyze:") ), wxVERTICAL );
	
	m_pwxgrdFullscales = new wxGrid( m_pwxpnlSetup, ID_FULLSCALE_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgrdFullscales->CreateGrid( 3, 4 );
	m_pwxgrdFullscales->EnableEditing( true );
	m_pwxgrdFullscales->EnableGridLines( true );
	m_pwxgrdFullscales->EnableDragGridSize( false );
	m_pwxgrdFullscales->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgrdFullscales->SetColSize( 0, 90 );
	m_pwxgrdFullscales->SetColSize( 1, 90 );
	m_pwxgrdFullscales->SetColSize( 2, 90 );
	m_pwxgrdFullscales->SetColSize( 3, 90 );
	m_pwxgrdFullscales->AutoSizeColumns();
	m_pwxgrdFullscales->EnableDragColMove( false );
	m_pwxgrdFullscales->EnableDragColSize( true );
	m_pwxgrdFullscales->SetColLabelSize( 30 );
	m_pwxgrdFullscales->SetColLabelValue( 0, wxT("Ch 1") );
	m_pwxgrdFullscales->SetColLabelValue( 1, wxT("Ch 2") );
	m_pwxgrdFullscales->SetColLabelValue( 2, wxT("Ch 3") );
	m_pwxgrdFullscales->SetColLabelValue( 3, wxT("Ch 4") );
	m_pwxgrdFullscales->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgrdFullscales->EnableDragRowSize( true );
	m_pwxgrdFullscales->SetRowLabelSize( 140 );
	m_pwxgrdFullscales->SetRowLabelValue( 0, wxT("Select track:") );
	m_pwxgrdFullscales->SetRowLabelValue( 1, wxT("Select filter:") );
	m_pwxgrdFullscales->SetRowLabelValue( 2, wxT("Fullscale level [dB]") );
	m_pwxgrdFullscales->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgrdFullscales->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_TOP );
	m_pwxgrdFullscales->SetMinSize( wxSize( 400,110 ) );
	
	sbGridSizer->Add( m_pwxgrdFullscales, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer161->Add( sbGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_pwxcbRemoveDC = new wxCheckBox( m_pwxpnlSetup, ID_RDC_CHECK, wxT("Remove DC component"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxcbRemoveDC->SetValue(true);
	
	bSizer161->Add( m_pwxcbRemoveDC, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pwxpnlSetup->SetSizer( bSizer161 );
	m_pwxpnlSetup->Layout();
	bSizer161->Fit( m_pwxpnlSetup );
	m_pNotebook->AddPage( m_pwxpnlSetup, wxT("Setup"), true );
	m_pwxpnlCalibration = new wxPanel( m_pNotebook, ID_CALIBRATION_PAGE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer162;
	bSizer162 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlCalibration, wxID_ANY, wxT("Select track(s) containing calibration signal:") ), wxVERTICAL );
	
	m_pwxgrdCalibration = new wxGrid( m_pwxpnlCalibration, ID_CALIBRATION_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgrdCalibration->CreateGrid( 2, 4 );
	m_pwxgrdCalibration->EnableEditing( true );
	m_pwxgrdCalibration->EnableGridLines( true );
	m_pwxgrdCalibration->EnableDragGridSize( false );
	m_pwxgrdCalibration->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgrdCalibration->SetColSize( 0, 90 );
	m_pwxgrdCalibration->SetColSize( 1, 90 );
	m_pwxgrdCalibration->SetColSize( 2, 90 );
	m_pwxgrdCalibration->SetColSize( 3, 90 );
	m_pwxgrdCalibration->AutoSizeColumns();
	m_pwxgrdCalibration->EnableDragColMove( true );
	m_pwxgrdCalibration->EnableDragColSize( true );
	m_pwxgrdCalibration->SetColLabelSize( 30 );
	m_pwxgrdCalibration->SetColLabelValue( 0, wxT("Ch 1") );
	m_pwxgrdCalibration->SetColLabelValue( 1, wxT("Ch 2") );
	m_pwxgrdCalibration->SetColLabelValue( 2, wxT("Ch 3") );
	m_pwxgrdCalibration->SetColLabelValue( 3, wxT("Ch 4") );
	m_pwxgrdCalibration->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgrdCalibration->EnableDragRowSize( true );
	m_pwxgrdCalibration->SetRowLabelSize( 160 );
	m_pwxgrdCalibration->SetRowLabelValue( 0, wxT("Calibration signal:") );
	m_pwxgrdCalibration->SetRowLabelValue( 1, wxT("Reference level [dB]") );
	m_pwxgrdCalibration->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgrdCalibration->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_TOP );
	m_pwxgrdCalibration->SetMinSize( wxSize( 400,-1 ) );
	
	sbSizer5->Add( m_pwxgrdCalibration, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_pwxcbCh1ForAll = new wxCheckBox( m_pwxpnlCalibration, ID_CALIB_APPLY_TO_ALL, wxT("Apply Ch 1 calibration to all channels"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer5->Add( m_pwxcbCh1ForAll, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer162->Add( sbSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_pwxbtnCalibrate = new wxButton( m_pwxpnlCalibration, ID_CALIBRATE_BTN, wxT("Calibrate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer162->Add( m_pwxbtnCalibrate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_pwxpnlCalibration->SetSizer( bSizer162 );
	m_pwxpnlCalibration->Layout();
	bSizer162->Fit( m_pwxpnlCalibration );
	m_pNotebook->AddPage( m_pwxpnlCalibration, wxT("Calibration"), false );
	
	bSizer1->Add( m_pNotebook, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnHelp = new wxButton( m_panel4, wxID_HELP, wxT("Help"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer5->Add( m_pwxbtnHelp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxbtnCancel = new wxButton( m_panel4, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer5->Add( m_pwxbtnCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxbtnAnalyze = new wxButton( m_panel4, wxID_OK, wxT("Analyze"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_pwxbtnAnalyze->SetDefault(); 
	bSizer5->Add( m_pwxbtnAnalyze, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_panel4->SetSizer( bSizer5 );
	m_panel4->Layout();
	bSizer5->Fit( m_panel4 );
	bSizer1->Add( m_panel4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_pwxgrdFullscales->Connect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADlg::OnFullscaleGridContentChanged ), NULL, this );
	m_pwxcbRemoveDC->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADlg::OnRemoveDCCheck ), NULL, this );
	m_pwxgrdCalibration->Connect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADlg::OnCalibrationGridContentChanged ), NULL, this );
	m_pwxcbCh1ForAll->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADlg::OnApplyToAllCheck ), NULL, this );
	m_pwxbtnCalibrate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnCalibrate ), NULL, this );
	m_pwxbtnHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnCancel ), NULL, this );
	m_pwxbtnAnalyze->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnOk ), NULL, this );
}

THADlg::~THADlg()
{
	// Disconnect Events
	m_pwxgrdFullscales->Disconnect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADlg::OnFullscaleGridContentChanged ), NULL, this );
	m_pwxcbRemoveDC->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADlg::OnRemoveDCCheck ), NULL, this );
	m_pwxgrdCalibration->Disconnect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADlg::OnCalibrationGridContentChanged ), NULL, this );
	m_pwxcbCh1ForAll->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADlg::OnApplyToAllCheck ), NULL, this );
	m_pwxbtnCalibrate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnCalibrate ), NULL, this );
	m_pwxbtnHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnCancel ), NULL, this );
	m_pwxbtnAnalyze->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADlg::OnOk ), NULL, this );
}

THAShowDlg::THAShowDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bMainSizer;
	bMainSizer = new wxBoxSizer( wxVERTICAL );
	
	mSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_BORDER|wxSP_NO_XP_THEME );
	mSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( THAShowDlg::mSplitterOnIdle ), NULL, this );
	mLeftPanel = new wxPanel( mSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( mLeftPanel, wxID_ANY, wxT("Input data graph") ), wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxstPlotType = new wxStaticText( mLeftPanel, wxID_ANY, wxT("What's plotting:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstPlotType->Wrap( -1 );
	bSizer14->Add( m_pwxstPlotType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choice1Choices[] = { wxT("Peak (1 sample)"), wxT("RMS (1 ms)"), wxT("ITU (30 ms)"), wxT("Impulse (35 ms up, 1.5 s down)"), wxT("Fast (125 ms)"), wxT("Slow (1 s)") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( mLeftPanel, ID_DISPLAY_CHOICE, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 1 );
	bSizer14->Add( m_choice1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer3->Add( bSizer14, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pwxpnlPlot = new wxPanel( mLeftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	mPlotScroller = new wxScrolledWindow( m_pwxpnlPlot, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mPlotScroller->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	m_pPlot = new THAPlot(m_pwxpnlPlot, ID_PLOT);
	m_pPlot->SetMinSize( wxSize( 200,50 ) );
	
	bSizer19->Add( m_pPlot, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mPlotScroller->SetSizer( bSizer19 );
	mPlotScroller->Layout();
	bSizer19->Fit( mPlotScroller );
	bSizer17->Add( mPlotScroller, 1, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlPlot->SetSizer( bSizer17 );
	m_pwxpnlPlot->Layout();
	bSizer17->Fit( m_pwxpnlPlot );
	sbSizer3->Add( m_pwxpnlPlot, 1, wxEXPAND | wxALL, 5 );
	
	bSizer141->Add( sbSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mLeftPanel->SetSizer( bSizer141 );
	mLeftPanel->Layout();
	bSizer141->Fit( mLeftPanel );
	mRightPanel = new wxPanel( mSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( mRightPanel, wxID_ANY, wxT("Calculated parameters table") ), wxVERTICAL );
	
	mGridPanel = new wxPanel( mRightPanel, ID_GRID_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxgrdResults = new wxGrid( mGridPanel, ID_PARAM_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgrdResults->CreateGrid( 15, 1 );
	m_pwxgrdResults->EnableEditing( false );
	m_pwxgrdResults->EnableGridLines( true );
	m_pwxgrdResults->EnableDragGridSize( false );
	m_pwxgrdResults->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgrdResults->EnableDragColMove( false );
	m_pwxgrdResults->EnableDragColSize( true );
	m_pwxgrdResults->SetColLabelSize( 30 );
	m_pwxgrdResults->SetColLabelValue( 0, wxT("Left") );
	m_pwxgrdResults->SetColLabelValue( 1, wxT("Right") );
	m_pwxgrdResults->SetColLabelValue( 2, wxT("Avg") );
	m_pwxgrdResults->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgrdResults->AutoSizeRows();
	m_pwxgrdResults->EnableDragRowSize( true );
	m_pwxgrdResults->SetRowLabelSize( 220 );
	m_pwxgrdResults->SetRowLabelValue( 0, wxT("Plot Color") );
	m_pwxgrdResults->SetRowLabelValue( 1, wxT("Filter Type") );
	m_pwxgrdResults->SetRowLabelValue( 2, wxT("Full Scale Level [dB Peak]") );
	m_pwxgrdResults->SetRowLabelValue( 3, wxT("Average Level [Leq - dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 4, wxT("Single Event Level [SEL - dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 5, wxT("Total Duration [s]") );
	m_pwxgrdResults->SetRowLabelValue( 6, wxT("Active Speech Level [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 7, wxT("Threshold Level [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 8, wxT("Activity Factor [%]") );
	m_pwxgrdResults->SetRowLabelValue( 9, wxT("Max Peak Level [dB Peak]") );
	m_pwxgrdResults->SetRowLabelValue( 10, wxT("Max SPL Impulse [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 11, wxT("Max SPL Fast [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 12, wxT("Max SPL Slow [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 13, wxT("Duration of the impulsive event [s]") );
	m_pwxgrdResults->SetRowLabelValue( 14, wxT("Impulsive Event?") );
	m_pwxgrdResults->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	m_pwxgrdResults->SetLabelFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	// Cell Defaults
	m_pwxgrdResults->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	m_pwxgrdResults->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizer12->Add( m_pwxgrdResults, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	mGridPanel->SetSizer( bSizer12 );
	mGridPanel->Layout();
	bSizer12->Fit( mGridPanel );
	sbSizer4->Add( mGridPanel, 1, wxEXPAND | wxALL, 5 );
	
	bSizer7->Add( sbSizer4, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mRightPanel->SetSizer( bSizer7 );
	mRightPanel->Layout();
	bSizer7->Fit( mRightPanel );
	mSplitter->SplitVertically( mLeftPanel, mRightPanel, 0 );
	bMainSizer->Add( mSplitter, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bMainSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	mBottomPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1411;
	bSizer1411 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button8 = new wxButton( mBottomPanel, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer151->Add( m_button8, 0, wxALL, 5 );
	
	
	bSizer151->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxbtnAddTracks = new wxButton( mBottomPanel, ID_ADD_TRACKS_BTN, wxT("Close && Add tracks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnAddTracks->SetToolTip( wxT("Close dialog then add filtered tracks to Audacity workspace") );
	
	bSizer151->Add( m_pwxbtnAddTracks, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mOkBtn = new wxButton( mBottomPanel, wxID_OK, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	mOkBtn->SetDefault(); 
	mOkBtn->SetToolTip( wxT("Close dialog") );
	
	bSizer151->Add( mOkBtn, 0, wxALL, 5 );
	
	bSizer1411->Add( bSizer151, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mBottomPanel->SetSizer( bSizer1411 );
	mBottomPanel->Layout();
	bSizer1411->Fit( mBottomPanel );
	bMainSizer->Add( mBottomPanel, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, 5 );
	
	this->SetSizer( bMainSizer );
	this->Layout();
	bMainSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( THAShowDlg::OnCloseDlg ) );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( THAShowDlg::OnSelectDisplay ), NULL, this );
	m_pwxgrdResults->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( THAShowDlg::OnGridCellRightClick ), NULL, this );
	m_pwxgrdResults->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( THAShowDlg::OnTogglePlot ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THAShowDlg::OnHelp ), NULL, this );
	m_pwxbtnAddTracks->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THAShowDlg::OnAddTracksBtn ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THAShowDlg::OnOk ), NULL, this );
}

THAShowDlg::~THAShowDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( THAShowDlg::OnCloseDlg ) );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( THAShowDlg::OnSelectDisplay ), NULL, this );
	m_pwxgrdResults->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( THAShowDlg::OnGridCellRightClick ), NULL, this );
	m_pwxgrdResults->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( THAShowDlg::OnTogglePlot ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THAShowDlg::OnHelp ), NULL, this );
	m_pwxbtnAddTracks->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THAShowDlg::OnAddTracksBtn ), NULL, this );
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THAShowDlg::OnOk ), NULL, this );
}

THADialog::THADialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer15->Add( m_pwxpnlLogo, 0, wxRIGHT|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer15->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	m_pHorzSplitter = new wxSplitterWindow( this, ID_HORZ_SPLITTER, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_pHorzSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( THADialog::m_pHorzSplitterOnIdle ), NULL, this );
	m_pwxpnlUpper = new wxPanel( m_pHorzSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_pNotebook = new AFNotebook( m_pwxpnlUpper, ID_SETUP_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxpnlSetup = new wxPanel( m_pNotebook, ID_SETUP_PAGE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbGridSizer;
	sbGridSizer = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlSetup, wxID_ANY, wxT("Track(s) to analyze:") ), wxVERTICAL );
	
	m_pwxgrdFullscales = new wxGrid( m_pwxpnlSetup, ID_FULLSCALE_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgrdFullscales->CreateGrid( 3, 8 );
	m_pwxgrdFullscales->EnableEditing( true );
	m_pwxgrdFullscales->EnableGridLines( true );
	m_pwxgrdFullscales->EnableDragGridSize( false );
	m_pwxgrdFullscales->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgrdFullscales->SetColSize( 0, 90 );
	m_pwxgrdFullscales->SetColSize( 1, 90 );
	m_pwxgrdFullscales->SetColSize( 2, 90 );
	m_pwxgrdFullscales->SetColSize( 3, 90 );
	m_pwxgrdFullscales->SetColSize( 4, 90 );
	m_pwxgrdFullscales->SetColSize( 5, 90 );
	m_pwxgrdFullscales->SetColSize( 6, 90 );
	m_pwxgrdFullscales->SetColSize( 7, 90 );
	m_pwxgrdFullscales->AutoSizeColumns();
	m_pwxgrdFullscales->EnableDragColMove( false );
	m_pwxgrdFullscales->EnableDragColSize( true );
	m_pwxgrdFullscales->SetColLabelSize( 30 );
	m_pwxgrdFullscales->SetColLabelValue( 0, wxT("Ch 1") );
	m_pwxgrdFullscales->SetColLabelValue( 1, wxT("Ch 2") );
	m_pwxgrdFullscales->SetColLabelValue( 2, wxT("Ch 3") );
	m_pwxgrdFullscales->SetColLabelValue( 3, wxT("Ch 4") );
	m_pwxgrdFullscales->SetColLabelValue( 4, wxT("Ch 5") );
	m_pwxgrdFullscales->SetColLabelValue( 5, wxT("Ch 6") );
	m_pwxgrdFullscales->SetColLabelValue( 6, wxT("Ch 7") );
	m_pwxgrdFullscales->SetColLabelValue( 7, wxT("Ch 8") );
	m_pwxgrdFullscales->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgrdFullscales->EnableDragRowSize( true );
	m_pwxgrdFullscales->SetRowLabelSize( 140 );
	m_pwxgrdFullscales->SetRowLabelValue( 0, wxT("Select track:") );
	m_pwxgrdFullscales->SetRowLabelValue( 1, wxT("Select filter:") );
	m_pwxgrdFullscales->SetRowLabelValue( 2, wxT("Fullscale level [dB]") );
	m_pwxgrdFullscales->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgrdFullscales->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_TOP );
	m_pwxgrdFullscales->SetMinSize( wxSize( 400,-1 ) );
	
	sbGridSizer->Add( m_pwxgrdFullscales, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer161->Add( sbGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnAnalyze = new wxButton( m_pwxpnlSetup, ID_ANALYZE_BTN, wxT("Analyze"), wxDefaultPosition, wxSize( 150,-1 ), 0 );
	bSizer25->Add( m_pwxbtnAnalyze, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer25->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxcbRemoveDC = new wxCheckBox( m_pwxpnlSetup, ID_RDC_CHECK, wxT("Remove DC component"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxcbRemoveDC->SetValue(true);
	
	bSizer25->Add( m_pwxcbRemoveDC, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer161->Add( bSizer25, 0, wxEXPAND, 5 );
	
	m_pwxpnlSetup->SetSizer( bSizer161 );
	m_pwxpnlSetup->Layout();
	bSizer161->Fit( m_pwxpnlSetup );
	m_pNotebook->AddPage( m_pwxpnlSetup, wxT("Setup"), true );
	m_pwxpnlCalibration = new wxPanel( m_pNotebook, ID_CALIBRATION_PAGE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer162;
	bSizer162 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlCalibration, wxID_ANY, wxT("Select track(s) containing calibration signal:") ), wxVERTICAL );
	
	m_pwxgrdCalibration = new wxGrid( m_pwxpnlCalibration, ID_CALIBRATION_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgrdCalibration->CreateGrid( 2, 8 );
	m_pwxgrdCalibration->EnableEditing( true );
	m_pwxgrdCalibration->EnableGridLines( true );
	m_pwxgrdCalibration->EnableDragGridSize( false );
	m_pwxgrdCalibration->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgrdCalibration->SetColSize( 0, 90 );
	m_pwxgrdCalibration->SetColSize( 1, 90 );
	m_pwxgrdCalibration->SetColSize( 2, 90 );
	m_pwxgrdCalibration->SetColSize( 3, 90 );
	m_pwxgrdCalibration->SetColSize( 4, 90 );
	m_pwxgrdCalibration->SetColSize( 5, 90 );
	m_pwxgrdCalibration->SetColSize( 6, 90 );
	m_pwxgrdCalibration->SetColSize( 7, 90 );
	m_pwxgrdCalibration->AutoSizeColumns();
	m_pwxgrdCalibration->EnableDragColMove( true );
	m_pwxgrdCalibration->EnableDragColSize( true );
	m_pwxgrdCalibration->SetColLabelSize( 30 );
	m_pwxgrdCalibration->SetColLabelValue( 0, wxT("Ch 1") );
	m_pwxgrdCalibration->SetColLabelValue( 1, wxT("Ch 2") );
	m_pwxgrdCalibration->SetColLabelValue( 2, wxT("Ch 3") );
	m_pwxgrdCalibration->SetColLabelValue( 3, wxT("Ch 4") );
	m_pwxgrdCalibration->SetColLabelValue( 4, wxT("Ch 5") );
	m_pwxgrdCalibration->SetColLabelValue( 5, wxT("Ch 6") );
	m_pwxgrdCalibration->SetColLabelValue( 6, wxT("Ch 7") );
	m_pwxgrdCalibration->SetColLabelValue( 7, wxT("Ch 8") );
	m_pwxgrdCalibration->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgrdCalibration->EnableDragRowSize( true );
	m_pwxgrdCalibration->SetRowLabelSize( 160 );
	m_pwxgrdCalibration->SetRowLabelValue( 0, wxT("Calibration signal:") );
	m_pwxgrdCalibration->SetRowLabelValue( 1, wxT("Reference level [dB]") );
	m_pwxgrdCalibration->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgrdCalibration->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_TOP );
	m_pwxgrdCalibration->SetMinSize( wxSize( 400,-1 ) );
	
	sbSizer5->Add( m_pwxgrdCalibration, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer162->Add( sbSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnCalibrate = new wxButton( m_pwxpnlCalibration, ID_CALIBRATE_BTN, wxT("Calibrate"), wxDefaultPosition, wxSize( 150,-1 ), 0 );
	bSizer26->Add( m_pwxbtnCalibrate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer26->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxcbCh1ForAll = new wxCheckBox( m_pwxpnlCalibration, ID_CALIB_APPLY_TO_ALL, wxT("Apply Ch 1 calibration to all channels"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer26->Add( m_pwxcbCh1ForAll, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer162->Add( bSizer26, 0, wxEXPAND, 5 );
	
	m_pwxpnlCalibration->SetSizer( bSizer162 );
	m_pwxpnlCalibration->Layout();
	bSizer162->Fit( m_pwxpnlCalibration );
	m_pNotebook->AddPage( m_pwxpnlCalibration, wxT("Calibration"), false );
	
	bSizer21->Add( m_pNotebook, 1, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlUpper->SetSizer( bSizer21 );
	m_pwxpnlUpper->Layout();
	bSizer21->Fit( m_pwxpnlUpper );
	m_pwxpnlLower = new wxPanel( m_pHorzSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	m_pVertSplitter = new wxSplitterWindow( m_pwxpnlLower, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_BORDER|wxSP_NO_XP_THEME );
	m_pVertSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( THADialog::m_pVertSplitterOnIdle ), NULL, this );
	m_pwxpnlLeft = new wxPanel( m_pVertSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlLeft, wxID_ANY, wxT("Input data graph") ), wxVERTICAL );
	
	m_pwxplotScroller = new wxScrolledWindow( m_pwxpnlLeft, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_pwxplotScroller->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxstPlotType = new wxStaticText( m_pwxplotScroller, wxID_ANY, wxT("What's plotted:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstPlotType->Wrap( -1 );
	bSizer14->Add( m_pwxstPlotType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchoicePlotTypeChoices[] = { wxT("Peak (1 sample)"), wxT("RMS (1 ms)"), wxT("ITU (30 ms)"), wxT("Impulse (35 ms up, 1.5 s down)"), wxT("Fast (125 ms)"), wxT("Slow (1 s)") };
	int m_pwxchoicePlotTypeNChoices = sizeof( m_pwxchoicePlotTypeChoices ) / sizeof( wxString );
	m_pwxchoicePlotType = new wxChoice( m_pwxplotScroller, ID_DISPLAY_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchoicePlotTypeNChoices, m_pwxchoicePlotTypeChoices, 0 );
	m_pwxchoicePlotType->SetSelection( 1 );
	m_pwxchoicePlotType->Enable( false );
	
	bSizer14->Add( m_pwxchoicePlotType, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer29->Add( bSizer14, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pwxpnlPlot = new wxPanel( m_pwxplotScroller, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	m_pPlot = new THAPlot(m_pwxpnlPlot, ID_PLOT, wxDefaultPosition, wxSize(400,300));
	m_pPlot->SetMinSize( wxSize( 200,50 ) );
	
	bSizer19->Add( m_pPlot, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pwxpnlPlot->SetSizer( bSizer19 );
	m_pwxpnlPlot->Layout();
	bSizer19->Fit( m_pwxpnlPlot );
	bSizer29->Add( m_pwxpnlPlot, 1, wxEXPAND | wxALL, 5 );
	
	m_pwxplotScroller->SetSizer( bSizer29 );
	m_pwxplotScroller->Layout();
	bSizer29->Fit( m_pwxplotScroller );
	sbSizer3->Add( m_pwxplotScroller, 1, wxEXPAND | wxALL, 5 );
	
	bSizer141->Add( sbSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_pwxpnlLeft->SetSizer( bSizer141 );
	m_pwxpnlLeft->Layout();
	bSizer141->Fit( m_pwxpnlLeft );
	m_pwxpnlRight = new wxPanel( m_pVertSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_pwxpnlRight, wxID_ANY, wxT("Calculated parameters table") ), wxVERTICAL );
	
	mGridPanel = new wxPanel( m_pwxpnlRight, ID_GRID_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxgrdResults = new wxGrid( mGridPanel, ID_PARAM_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgrdResults->CreateGrid( 15, 1 );
	m_pwxgrdResults->EnableEditing( false );
	m_pwxgrdResults->EnableGridLines( true );
	m_pwxgrdResults->EnableDragGridSize( false );
	m_pwxgrdResults->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgrdResults->EnableDragColMove( false );
	m_pwxgrdResults->EnableDragColSize( true );
	m_pwxgrdResults->SetColLabelSize( 30 );
	m_pwxgrdResults->SetColLabelValue( 0, wxT("Left") );
	m_pwxgrdResults->SetColLabelValue( 1, wxT("Right") );
	m_pwxgrdResults->SetColLabelValue( 2, wxT("Avg") );
	m_pwxgrdResults->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgrdResults->AutoSizeRows();
	m_pwxgrdResults->EnableDragRowSize( true );
	m_pwxgrdResults->SetRowLabelSize( 220 );
	m_pwxgrdResults->SetRowLabelValue( 0, wxT("Plot Color") );
	m_pwxgrdResults->SetRowLabelValue( 1, wxT("Filter Type") );
	m_pwxgrdResults->SetRowLabelValue( 2, wxT("Full Scale Level [dB Peak]") );
	m_pwxgrdResults->SetRowLabelValue( 3, wxT("Average Level [Leq - dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 4, wxT("Single Event Level [SEL - dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 5, wxT("Total Duration [s]") );
	m_pwxgrdResults->SetRowLabelValue( 6, wxT("Active Speech Level [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 7, wxT("Threshold Level [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 8, wxT("Activity Factor [%]") );
	m_pwxgrdResults->SetRowLabelValue( 9, wxT("Max Peak Level [dB Peak]") );
	m_pwxgrdResults->SetRowLabelValue( 10, wxT("Max SPL Impulse [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 11, wxT("Max SPL Fast [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 12, wxT("Max SPL Slow [dB RMS]") );
	m_pwxgrdResults->SetRowLabelValue( 13, wxT("Duration of the impulsive event [s]") );
	m_pwxgrdResults->SetRowLabelValue( 14, wxT("Impulsive Event?") );
	m_pwxgrdResults->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	m_pwxgrdResults->SetLabelFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	// Cell Defaults
	m_pwxgrdResults->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	m_pwxgrdResults->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizer12->Add( m_pwxgrdResults, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	mGridPanel->SetSizer( bSizer12 );
	mGridPanel->Layout();
	bSizer12->Fit( mGridPanel );
	sbSizer4->Add( mGridPanel, 1, wxEXPAND | wxALL, 5 );
	
	bSizer7->Add( sbSizer4, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pwxpnlRight->SetSizer( bSizer7 );
	m_pwxpnlRight->Layout();
	bSizer7->Fit( m_pwxpnlRight );
	m_pVertSplitter->SplitVertically( m_pwxpnlLeft, m_pwxpnlRight, 0 );
	bSizer34->Add( m_pVertSplitter, 1, wxEXPAND, 5 );
	
	m_pwxpnlLower->SetSizer( bSizer34 );
	m_pwxpnlLower->Layout();
	bSizer34->Fit( m_pwxpnlLower );
	m_pHorzSplitter->SplitHorizontally( m_pwxpnlUpper, m_pwxpnlLower, 200 );
	bSizer15->Add( m_pHorzSplitter, 1, wxEXPAND, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer15->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	mBottomPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1411;
	bSizer1411 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button8 = new wxButton( mBottomPanel, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer151->Add( m_button8, 0, wxALL, 5 );
	
	
	bSizer151->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxbtnAddTracks = new wxButton( mBottomPanel, ID_ADD_TRACKS_BTN, wxT("Close && Add tracks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnAddTracks->SetToolTip( wxT("Close dialog then add filtered tracks to Audacity workspace") );
	
	bSizer151->Add( m_pwxbtnAddTracks, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mOkBtn = new wxButton( mBottomPanel, wxID_OK, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	mOkBtn->SetDefault(); 
	mOkBtn->SetToolTip( wxT("Close dialog") );
	
	bSizer151->Add( mOkBtn, 0, wxALL, 5 );
	
	bSizer1411->Add( bSizer151, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mBottomPanel->SetSizer( bSizer1411 );
	mBottomPanel->Layout();
	bSizer1411->Fit( mBottomPanel );
	bSizer15->Add( mBottomPanel, 0, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer15 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( THADialog::OnCloseDialog ) );
	m_pwxgrdFullscales->Connect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADialog::OnFullscaleGridContentChanged ), NULL, this );
	m_pwxbtnAnalyze->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnAnalyze ), NULL, this );
	m_pwxcbRemoveDC->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADialog::OnRemoveDCCheck ), NULL, this );
	m_pwxgrdCalibration->Connect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADialog::OnCalibrationGridContentChanged ), NULL, this );
	m_pwxbtnCalibrate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnCalibrate ), NULL, this );
	m_pwxcbCh1ForAll->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADialog::OnApplyToAllCheck ), NULL, this );
	m_pwxchoicePlotType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( THADialog::OnSelectDisplay ), NULL, this );
	m_pwxgrdResults->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( THADialog::OnGridCellRightClick ), NULL, this );
	m_pwxgrdResults->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( THADialog::OnTogglePlot ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnHelp ), NULL, this );
	m_pwxbtnAddTracks->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnAddTracksBtn ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnOk ), NULL, this );
}

THADialog::~THADialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( THADialog::OnCloseDialog ) );
	m_pwxgrdFullscales->Disconnect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADialog::OnFullscaleGridContentChanged ), NULL, this );
	m_pwxbtnAnalyze->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnAnalyze ), NULL, this );
	m_pwxcbRemoveDC->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADialog::OnRemoveDCCheck ), NULL, this );
	m_pwxgrdCalibration->Disconnect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( THADialog::OnCalibrationGridContentChanged ), NULL, this );
	m_pwxbtnCalibrate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnCalibrate ), NULL, this );
	m_pwxcbCh1ForAll->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( THADialog::OnApplyToAllCheck ), NULL, this );
	m_pwxchoicePlotType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( THADialog::OnSelectDisplay ), NULL, this );
	m_pwxgrdResults->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( THADialog::OnGridCellRightClick ), NULL, this );
	m_pwxgrdResults->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( THADialog::OnTogglePlot ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnHelp ), NULL, this );
	m_pwxbtnAddTracks->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnAddTracksBtn ), NULL, this );
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( THADialog::OnOk ), NULL, this );
}
