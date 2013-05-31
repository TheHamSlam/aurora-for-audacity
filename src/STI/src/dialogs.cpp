///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

///////////////////////////////////////////////////////////////////////////

STISetupDlg::STISetupDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_pwxpnlLogo, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxRIGHT|wxLEFT, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxNbStartPnl = new wxPanel( m_notebook1, ID_START_PNL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer3->Add( 0, 30, 0, wxEXPAND, 5 );
	
	m_wxstWelcomeMsg = new wxStaticText( m_wxNbStartPnl, wxID_ANY, wxT("Welcome to Aurora's Speech Transmission Index Evaluator\n\nIn order to proceed, you have to provide the following recordings:\n\n  1) the calibration signal (94 dB)\n  2) the room's background noise\n  3) the test signal (pink noise, 62 dB @ 1m)\n  4) the room's Impulse Response.\n\nIf you have already calibrated the fullscale, the\nlast value should be saved and loaded as\ndefault; same thing for the S/N calculation:\nif you have previously saved a set of values,\nyou can restore them. \n\nOtherwise, all the signals 1-4 must be present\nin the workspace!\n\nThe recordings can be mono or stereo, but...be coherent!"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstWelcomeMsg->Wrap( -1 );
	bSizer3->Add( m_wxstWelcomeMsg, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_wxNbStartPnl->SetSizer( bSizer3 );
	m_wxNbStartPnl->Layout();
	bSizer3->Fit( m_wxNbStartPnl );
	m_notebook1->AddPage( m_wxNbStartPnl, wxT("Start"), true );
	m_wxNbFSCalibrationPnl = new wxPanel( m_notebook1, ID_FS_CALIBRATION_PNL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer5->Add( 0, 60, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("Current Fullscale") ), wxHORIZONTAL );
	
	m_wxstFsLeftLbl = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("Left:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstFsLeftLbl->Wrap( -1 );
	sbSizer1->Add( m_wxstFsLeftLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcLeftFs = new wxTextCtrl( m_wxNbFSCalibrationPnl, ID_LEFT_FS_TC, wxT("100.0"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	sbSizer1->Add( m_pwxtcLeftFs, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstFsRightLbl = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("dB        Right:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstFsRightLbl->Wrap( -1 );
	sbSizer1->Add( m_wxstFsRightLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcRightFs = new wxTextCtrl( m_wxNbFSCalibrationPnl, ID_RIGHT_FS_TC, wxT("100.0"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_RIGHT );
	sbSizer1->Add( m_pwxtcRightFs, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstFsRightdB = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstFsRightdB->Wrap( -1 );
	sbSizer1->Add( m_wxstFsRightdB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer5->Add( sbSizer1, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer5->Add( 0, 35, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("Choose calibration tracks from lists:") ), wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 5, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_wxtcLeftCalLbl = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("Left:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxtcLeftCalLbl->Wrap( -1 );
	fgSizer1->Add( m_wxtcLeftCalLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchLeftCalChoices[] = { wxT("None") };
	int m_pwxchLeftCalNChoices = sizeof( m_pwxchLeftCalChoices ) / sizeof( wxString );
	m_pwxchLeftCal = new wxChoice( m_wxNbFSCalibrationPnl, ID_LEFT_CAL_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchLeftCalNChoices, m_pwxchLeftCalChoices, 0 );
	m_pwxchLeftCal->SetSelection( 0 );
	m_pwxchLeftCal->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer1->Add( m_pwxchLeftCal, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstLeftLevelLbl = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstLeftLevelLbl->Wrap( -1 );
	fgSizer1->Add( m_wxstLeftLevelLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcLeftLevel = new wxTextCtrl( m_wxNbFSCalibrationPnl, ID_LEFT_CAL_TC, wxT("94.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	m_pwxtcLeftLevel->SetMinSize( wxSize( 60,-1 ) );
	
	fgSizer1->Add( m_pwxtcLeftLevel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstLeftLvldB = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstLeftLvldB->Wrap( -1 );
	fgSizer1->Add( m_wxstLeftLvldB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxtcRightCalLbl = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("Right:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxtcRightCalLbl->Wrap( -1 );
	fgSizer1->Add( m_wxtcRightCalLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchRightCalChoices[] = { wxT("None") };
	int m_pwxchRightCalNChoices = sizeof( m_pwxchRightCalChoices ) / sizeof( wxString );
	m_pwxchRightCal = new wxChoice( m_wxNbFSCalibrationPnl, ID_RIGHT_CAL_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchRightCalNChoices, m_pwxchRightCalChoices, 0 );
	m_pwxchRightCal->SetSelection( 0 );
	m_pwxchRightCal->Enable( false );
	m_pwxchRightCal->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer1->Add( m_pwxchRightCal, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstRightLevelLbl = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstRightLevelLbl->Wrap( -1 );
	fgSizer1->Add( m_wxstRightLevelLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcRightLevel = new wxTextCtrl( m_wxNbFSCalibrationPnl, ID_RIGHT_CAL_TC, wxT("94.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	m_pwxtcRightLevel->Enable( false );
	m_pwxtcRightLevel->SetMinSize( wxSize( 60,-1 ) );
	
	fgSizer1->Add( m_pwxtcRightLevel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstRightLvldB = new wxStaticText( m_wxNbFSCalibrationPnl, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstRightLvldB->Wrap( -1 );
	fgSizer1->Add( m_wxstRightLvldB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer6->Add( fgSizer1, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_pwxbtnCalibrate = new wxButton( m_wxNbFSCalibrationPnl, ID_CALIBRATE_BTN, wxT("Calibrate!"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnCalibrate->Enable( false );
	
	bSizer6->Add( m_pwxbtnCalibrate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	sbSizer2->Add( bSizer6, 0, wxEXPAND, 5 );
	
	bSizer5->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	m_wxNbFSCalibrationPnl->SetSizer( bSizer5 );
	m_wxNbFSCalibrationPnl->Layout();
	bSizer5->Fit( m_wxNbFSCalibrationPnl );
	m_notebook1->AddPage( m_wxNbFSCalibrationPnl, wxT("Fullscale Calibration"), false );
	m_wxNbSigNoisePnl = new wxPanel( m_notebook1, ID_SN_PNL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_wxNbSigNoisePnl, wxID_ANY, wxT("Choose background noise tracks from lists:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_wxstLeftBckNoiseLbl = new wxStaticText( m_wxNbSigNoisePnl, wxID_ANY, wxT("Left:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstLeftBckNoiseLbl->Wrap( -1 );
	fgSizer2->Add( m_wxstLeftBckNoiseLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchLeftBckNoiseChoices[] = { wxT("None") };
	int m_pwxchLeftBckNoiseNChoices = sizeof( m_pwxchLeftBckNoiseChoices ) / sizeof( wxString );
	m_pwxchLeftBckNoise = new wxChoice( m_wxNbSigNoisePnl, ID_LEFT_BCK_NOISE_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchLeftBckNoiseNChoices, m_pwxchLeftBckNoiseChoices, 0 );
	m_pwxchLeftBckNoise->SetSelection( 0 );
	m_pwxchLeftBckNoise->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer2->Add( m_pwxchLeftBckNoise, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstRightBckNoiseLbl = new wxStaticText( m_wxNbSigNoisePnl, wxID_ANY, wxT("Right:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstRightBckNoiseLbl->Wrap( -1 );
	fgSizer2->Add( m_wxstRightBckNoiseLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchRightBckNoiseChoices[] = { wxT("None") };
	int m_pwxchRightBckNoiseNChoices = sizeof( m_pwxchRightBckNoiseChoices ) / sizeof( wxString );
	m_pwxchRightBckNoise = new wxChoice( m_wxNbSigNoisePnl, ID_RIGHT_BCK_NOISE_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchRightBckNoiseNChoices, m_pwxchRightBckNoiseChoices, 0 );
	m_pwxchRightBckNoise->SetSelection( 0 );
	m_pwxchRightBckNoise->Enable( false );
	m_pwxchRightBckNoise->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer2->Add( m_pwxchRightBckNoise, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer3->Add( fgSizer2, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer7->Add( sbSizer3, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( m_wxNbSigNoisePnl, wxID_ANY, wxT("Choose test signal tracks from lists:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_wxstLeftSignalLbl = new wxStaticText( m_wxNbSigNoisePnl, wxID_ANY, wxT("Left:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstLeftSignalLbl->Wrap( -1 );
	fgSizer21->Add( m_wxstLeftSignalLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchLeftSignalChoices[] = { wxT("None") };
	int m_pwxchLeftSignalNChoices = sizeof( m_pwxchLeftSignalChoices ) / sizeof( wxString );
	m_pwxchLeftSignal = new wxChoice( m_wxNbSigNoisePnl, ID_LEFT_SIGNAL_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchLeftSignalNChoices, m_pwxchLeftSignalChoices, 0 );
	m_pwxchLeftSignal->SetSelection( 0 );
	m_pwxchLeftSignal->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer21->Add( m_pwxchLeftSignal, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstRightSignalLbl = new wxStaticText( m_wxNbSigNoisePnl, wxID_ANY, wxT("Right:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstRightSignalLbl->Wrap( -1 );
	fgSizer21->Add( m_wxstRightSignalLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchRightSignalChoices[] = { wxT("None") };
	int m_pwxchRightSignalNChoices = sizeof( m_pwxchRightSignalChoices ) / sizeof( wxString );
	m_pwxchRightSignal = new wxChoice( m_wxNbSigNoisePnl, ID_RIGHT_SIGNAL_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchRightSignalNChoices, m_pwxchRightSignalChoices, 0 );
	m_pwxchRightSignal->SetSelection( 0 );
	m_pwxchRightSignal->Enable( false );
	m_pwxchRightSignal->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer21->Add( m_pwxchRightSignal, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer31->Add( fgSizer21, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxrbSignal = new wxRadioButton( m_wxNbSigNoisePnl, ID_SIGNAL_RB, wxT("Signal"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	bSizer8->Add( m_wxrbSignal, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxrbSigNoise = new wxRadioButton( m_wxNbSigNoisePnl, ID_SIGNOISE_RB, wxT("Signal + Noise"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxrbSigNoise->SetValue( true ); 
	bSizer8->Add( m_wxrbSigNoise, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer31->Add( bSizer8, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer7->Add( sbSizer31, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_wxNbSigNoisePnl, wxID_ANY, wxT("Levels:") ), wxVERTICAL );
	
	m_pwxgridSplTable = new wxGrid( m_wxNbSigNoisePnl, ID_SPL_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgridSplTable->CreateGrid( 7, 6 );
	m_pwxgridSplTable->EnableEditing( false );
	m_pwxgridSplTable->EnableGridLines( true );
	m_pwxgridSplTable->EnableDragGridSize( false );
	m_pwxgridSplTable->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgridSplTable->EnableDragColMove( false );
	m_pwxgridSplTable->EnableDragColSize( true );
	m_pwxgridSplTable->SetColLabelSize( 30 );
	m_pwxgridSplTable->SetColLabelValue( 0, wxT("BckN Left") );
	m_pwxgridSplTable->SetColLabelValue( 1, wxT("BckN Right") );
	m_pwxgridSplTable->SetColLabelValue( 2, wxT("Sig Left") );
	m_pwxgridSplTable->SetColLabelValue( 3, wxT("Sig Right") );
	m_pwxgridSplTable->SetColLabelValue( 4, wxT("S+N Left") );
	m_pwxgridSplTable->SetColLabelValue( 5, wxT("S+N Right") );
	m_pwxgridSplTable->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgridSplTable->SetRowSize( 0, 23 );
	m_pwxgridSplTable->SetRowSize( 1, 23 );
	m_pwxgridSplTable->SetRowSize( 2, 23 );
	m_pwxgridSplTable->SetRowSize( 3, 23 );
	m_pwxgridSplTable->SetRowSize( 4, 23 );
	m_pwxgridSplTable->SetRowSize( 5, 23 );
	m_pwxgridSplTable->SetRowSize( 6, 23 );
	m_pwxgridSplTable->EnableDragRowSize( true );
	m_pwxgridSplTable->SetRowLabelSize( 60 );
	m_pwxgridSplTable->SetRowLabelValue( 0, wxT("125") );
	m_pwxgridSplTable->SetRowLabelValue( 1, wxT("250") );
	m_pwxgridSplTable->SetRowLabelValue( 2, wxT("500") );
	m_pwxgridSplTable->SetRowLabelValue( 3, wxT("1k") );
	m_pwxgridSplTable->SetRowLabelValue( 4, wxT("2k") );
	m_pwxgridSplTable->SetRowLabelValue( 5, wxT("4k") );
	m_pwxgridSplTable->SetRowLabelValue( 6, wxT("8k") );
	m_pwxgridSplTable->SetRowLabelAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgridSplTable->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	m_pwxgridSplTable->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	sbSizer7->Add( m_pwxgridSplTable, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	bSizer7->Add( sbSizer7, 1, wxEXPAND, 5 );
	
	m_panel6 = new wxPanel( m_wxNbSigNoisePnl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnLoadSplValues = new wxButton( m_panel6, ID_LOAD_SPL_VALUES_BTN, wxT("Load SPL Values"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_pwxbtnLoadSplValues, 0, wxALL, 5 );
	
	m_pwxbtnSaveSplValues = new wxButton( m_panel6, ID_SAVE_SPL_VALUES_BTN, wxT("Save SPL Values"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_pwxbtnSaveSplValues, 0, wxALL, 5 );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxbtnCalculateSPL = new wxButton( m_panel6, wxID_ANY, wxT("Compute Levels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnCalculateSPL->Enable( false );
	
	bSizer9->Add( m_pwxbtnCalculateSPL, 0, wxALL, 5 );
	
	m_panel6->SetSizer( bSizer9 );
	m_panel6->Layout();
	bSizer9->Fit( m_panel6 );
	bSizer7->Add( m_panel6, 0, wxALL|wxEXPAND, 5 );
	
	m_wxNbSigNoisePnl->SetSizer( bSizer7 );
	m_wxNbSigNoisePnl->Layout();
	bSizer7->Fit( m_wxNbSigNoisePnl );
	m_notebook1->AddPage( m_wxNbSigNoisePnl, wxT("SNR Calculation"), false );
	m_wxNbIRChoosePnl = new wxPanel( m_notebook1, ID_IR_PNL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer10->Add( 0, 80, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer32;
	sbSizer32 = new wxStaticBoxSizer( new wxStaticBox( m_wxNbIRChoosePnl, wxID_ANY, wxT("Choose Impulse Responses from track lists:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_wxstLeftIrLbl = new wxStaticText( m_wxNbIRChoosePnl, wxID_ANY, wxT("Left:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstLeftIrLbl->Wrap( -1 );
	fgSizer22->Add( m_wxstLeftIrLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchLeftIrChoices[] = { wxT("None") };
	int m_pwxchLeftIrNChoices = sizeof( m_pwxchLeftIrChoices ) / sizeof( wxString );
	m_pwxchLeftIr = new wxChoice( m_wxNbIRChoosePnl, ID_LEFT_IR_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchLeftIrNChoices, m_pwxchLeftIrChoices, 0 );
	m_pwxchLeftIr->SetSelection( 0 );
	m_pwxchLeftIr->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer22->Add( m_pwxchLeftIr, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstRightIrLbl = new wxStaticText( m_wxNbIRChoosePnl, wxID_ANY, wxT("Right:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstRightIrLbl->Wrap( -1 );
	fgSizer22->Add( m_wxstRightIrLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_pwxchRightIrChoices[] = { wxT("None") };
	int m_pwxchRightIrNChoices = sizeof( m_pwxchRightIrChoices ) / sizeof( wxString );
	m_pwxchRightIr = new wxChoice( m_wxNbIRChoosePnl, ID_RIGHT_IR_CHOICE, wxDefaultPosition, wxDefaultSize, m_pwxchRightIrNChoices, m_pwxchRightIrChoices, 0 );
	m_pwxchRightIr->SetSelection( 0 );
	m_pwxchRightIr->Enable( false );
	m_pwxchRightIr->SetMinSize( wxSize( 250,-1 ) );
	
	fgSizer22->Add( m_pwxchRightIr, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer32->Add( fgSizer22, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer10->Add( sbSizer32, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxstFatLbl = new wxStaticText( m_wxNbIRChoosePnl, wxID_ANY, wxT("First Arrival Threshold:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstFatLbl->Wrap( -1 );
	bSizer11->Add( m_wxstFatLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcFat = new wxTextCtrl( m_wxNbIRChoosePnl, ID_FAT_TC, wxT("20.0"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	m_pwxtcFat->SetMinSize( wxSize( 60,-1 ) );
	
	bSizer11->Add( m_pwxtcFat, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstFatBackLbl = new wxStaticText( m_wxNbIRChoosePnl, wxID_ANY, wxT("% of fullscale"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstFatBackLbl->Wrap( -1 );
	bSizer11->Add( m_wxstFatBackLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer10->Add( bSizer11, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_wxNbIRChoosePnl->SetSizer( bSizer10 );
	m_wxNbIRChoosePnl->Layout();
	bSizer10->Fit( m_wxNbIRChoosePnl );
	m_notebook1->AddPage( m_wxNbIRChoosePnl, wxT("Room Impulse Response"), false );
	
	bSizer1->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_wxButtonsPnl = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnHelp = new wxButton( m_wxButtonsPnl, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_pwxbtnHelp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxbtnCancel = new wxButton( m_wxButtonsPnl, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnCancel->SetDefault(); 
	bSizer2->Add( m_pwxbtnCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxbtnOk = new wxButton( m_wxButtonsPnl, wxID_OK, wxT("Compute STI"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnOk->Enable( false );
	
	bSizer2->Add( m_pwxbtnOk, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxButtonsPnl->SetSizer( bSizer2 );
	m_wxButtonsPnl->Layout();
	bSizer2->Fit( m_wxButtonsPnl );
	bSizer1->Add( m_wxButtonsPnl, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( STISetupDlg::OnCloseDialog ) );
	m_pwxtcLeftFs->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnLeftFullscaleText ), NULL, this );
	m_pwxtcRightFs->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnRightFullscaleText ), NULL, this );
	m_pwxchLeftCal->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnCalibLeftChoice ), NULL, this );
	m_pwxtcLeftLevel->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnCalibRefLeftText ), NULL, this );
	m_pwxchRightCal->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnCalibRightChoice ), NULL, this );
	m_pwxtcRightLevel->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnCalibRefRightText ), NULL, this );
	m_pwxbtnCalibrate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnDoFullscaleCalibration ), NULL, this );
	m_pwxchLeftBckNoise->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnNoiseLeftChoice ), NULL, this );
	m_pwxchRightBckNoise->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnNoiseRightChoice ), NULL, this );
	m_pwxchLeftSignal->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalLeftChoice ), NULL, this );
	m_pwxchRightSignal->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalRightChoice ), NULL, this );
	m_wxrbSignal->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalRadio ), NULL, this );
	m_wxrbSigNoise->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalPlusNoiseRadio ), NULL, this );
	m_pwxbtnLoadSplValues->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnLoadSplValues ), NULL, this );
	m_pwxbtnSaveSplValues->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnSaveSplValues ), NULL, this );
	m_pwxbtnCalculateSPL->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnComputeSNRatio ), NULL, this );
	m_pwxchLeftIr->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnLeftIRChoice ), NULL, this );
	m_pwxchRightIr->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnRightIRChoice ), NULL, this );
	m_pwxtcFat->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnFatText ), NULL, this );
	m_pwxbtnHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnCancel ), NULL, this );
	m_pwxbtnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnComputeSTI ), NULL, this );
}

STISetupDlg::~STISetupDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( STISetupDlg::OnCloseDialog ) );
	m_pwxtcLeftFs->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnLeftFullscaleText ), NULL, this );
	m_pwxtcRightFs->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnRightFullscaleText ), NULL, this );
	m_pwxchLeftCal->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnCalibLeftChoice ), NULL, this );
	m_pwxtcLeftLevel->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnCalibRefLeftText ), NULL, this );
	m_pwxchRightCal->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnCalibRightChoice ), NULL, this );
	m_pwxtcRightLevel->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnCalibRefRightText ), NULL, this );
	m_pwxbtnCalibrate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnDoFullscaleCalibration ), NULL, this );
	m_pwxchLeftBckNoise->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnNoiseLeftChoice ), NULL, this );
	m_pwxchRightBckNoise->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnNoiseRightChoice ), NULL, this );
	m_pwxchLeftSignal->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalLeftChoice ), NULL, this );
	m_pwxchRightSignal->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalRightChoice ), NULL, this );
	m_wxrbSignal->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalRadio ), NULL, this );
	m_wxrbSigNoise->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STISetupDlg::OnSignalPlusNoiseRadio ), NULL, this );
	m_pwxbtnLoadSplValues->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnLoadSplValues ), NULL, this );
	m_pwxbtnSaveSplValues->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnSaveSplValues ), NULL, this );
	m_pwxbtnCalculateSPL->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnComputeSNRatio ), NULL, this );
	m_pwxchLeftIr->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnLeftIRChoice ), NULL, this );
	m_pwxchRightIr->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( STISetupDlg::OnRightIRChoice ), NULL, this );
	m_pwxtcFat->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( STISetupDlg::OnFatText ), NULL, this );
	m_pwxbtnHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnHelp ), NULL, this );
	m_pwxbtnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnCancel ), NULL, this );
	m_pwxbtnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STISetupDlg::OnComputeSTI ), NULL, this );
}

STIShowDlg::STIShowDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlLogo = new wxPanel( this, ID_LOGO_PANEL, wxDefaultPosition, wxSize( -1,54 ), wxTAB_TRAVERSAL );
	bSizer11->Add( m_pwxpnlLogo, 0, wxEXPAND|wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline4, 0, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel10 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook2 = new wxNotebook( m_panel10, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxpnlGridPage = new wxPanel( m_notebook2, ID_GRID_PNL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxgridMtfTable = new wxGrid( m_pwxpnlGridPage, ID_MTF_VALUES_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgridMtfTable->CreateGrid( 14, 7 );
	m_pwxgridMtfTable->EnableEditing( false );
	m_pwxgridMtfTable->EnableGridLines( true );
	m_pwxgridMtfTable->EnableDragGridSize( false );
	m_pwxgridMtfTable->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgridMtfTable->EnableDragColMove( false );
	m_pwxgridMtfTable->EnableDragColSize( true );
	m_pwxgridMtfTable->SetColLabelSize( 30 );
	m_pwxgridMtfTable->SetColLabelValue( 0, wxT("125 Hz") );
	m_pwxgridMtfTable->SetColLabelValue( 1, wxT("250 Hz") );
	m_pwxgridMtfTable->SetColLabelValue( 2, wxT("500 Hz") );
	m_pwxgridMtfTable->SetColLabelValue( 3, wxT("1 kHz") );
	m_pwxgridMtfTable->SetColLabelValue( 4, wxT("2 kHz") );
	m_pwxgridMtfTable->SetColLabelValue( 5, wxT("4 kHz") );
	m_pwxgridMtfTable->SetColLabelValue( 6, wxT("8 kHz") );
	m_pwxgridMtfTable->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgridMtfTable->EnableDragRowSize( true );
	m_pwxgridMtfTable->SetRowLabelSize( 60 );
	m_pwxgridMtfTable->SetRowLabelValue( 0, wxT("0.63") );
	m_pwxgridMtfTable->SetRowLabelValue( 1, wxT("0.8") );
	m_pwxgridMtfTable->SetRowLabelValue( 2, wxT("1") );
	m_pwxgridMtfTable->SetRowLabelValue( 3, wxT("1.25") );
	m_pwxgridMtfTable->SetRowLabelValue( 4, wxT("1.6") );
	m_pwxgridMtfTable->SetRowLabelValue( 5, wxT("2") );
	m_pwxgridMtfTable->SetRowLabelValue( 6, wxT("2.5") );
	m_pwxgridMtfTable->SetRowLabelValue( 7, wxT("3.15") );
	m_pwxgridMtfTable->SetRowLabelValue( 8, wxT("4") );
	m_pwxgridMtfTable->SetRowLabelValue( 9, wxT("5") );
	m_pwxgridMtfTable->SetRowLabelValue( 10, wxT("6.3") );
	m_pwxgridMtfTable->SetRowLabelValue( 11, wxT("8") );
	m_pwxgridMtfTable->SetRowLabelValue( 12, wxT("10") );
	m_pwxgridMtfTable->SetRowLabelValue( 13, wxT("12.5") );
	m_pwxgridMtfTable->SetRowLabelAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgridMtfTable->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	m_pwxgridMtfTable->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_TOP );
	bSizer15->Add( m_pwxgridMtfTable, 0, wxALL, 5 );
	
	m_pwxpnlGridPage->SetSizer( bSizer15 );
	m_pwxpnlGridPage->Layout();
	bSizer15->Fit( m_pwxpnlGridPage );
	m_notebook2->AddPage( m_pwxpnlGridPage, wxT("MTF Values table"), false );
	
	bSizer17->Add( m_notebook2, 1, wxEXPAND | wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_panel10, wxID_ANY, wxT("Band STI values") ), wxVERTICAL );
	
	m_pwxgridSTITable = new wxGrid( m_panel10, ID_BAND_STI_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pwxgridSTITable->CreateGrid( 1, 7 );
	m_pwxgridSTITable->EnableEditing( false );
	m_pwxgridSTITable->EnableGridLines( true );
	m_pwxgridSTITable->EnableDragGridSize( false );
	m_pwxgridSTITable->SetMargins( 0, 0 );
	
	// Columns
	m_pwxgridSTITable->EnableDragColMove( false );
	m_pwxgridSTITable->EnableDragColSize( true );
	m_pwxgridSTITable->SetColLabelSize( 30 );
	m_pwxgridSTITable->SetColLabelValue( 0, wxT("125 Hz") );
	m_pwxgridSTITable->SetColLabelValue( 1, wxT("250 Hz") );
	m_pwxgridSTITable->SetColLabelValue( 2, wxT("500 Hz") );
	m_pwxgridSTITable->SetColLabelValue( 3, wxT("1 kHz") );
	m_pwxgridSTITable->SetColLabelValue( 4, wxT("2 kHz") );
	m_pwxgridSTITable->SetColLabelValue( 5, wxT("4 kHz") );
	m_pwxgridSTITable->SetColLabelValue( 6, wxT("8 kHz") );
	m_pwxgridSTITable->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pwxgridSTITable->EnableDragRowSize( true );
	m_pwxgridSTITable->SetRowLabelSize( 80 );
	m_pwxgridSTITable->SetRowLabelValue( 0, wxT("Band STI") );
	m_pwxgridSTITable->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pwxgridSTITable->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	m_pwxgridSTITable->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_TOP );
	sbSizer10->Add( m_pwxgridSTITable, 0, wxALL, 5 );
	
	bSizer17->Add( sbSizer10, 0, wxEXPAND, 5 );
	
	bSizer13->Add( bSizer17, 1, wxEXPAND, 5 );
	
	m_panel11 = new wxPanel( m_panel10, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer16->Add( 0, 25, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_panel11, wxID_ANY, wxT("Channel Selection") ), wxHORIZONTAL );
	
	m_pwxrbLeft = new wxRadioButton( m_panel11, ID_LEFT_RB, wxT("Left"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	m_pwxrbLeft->SetValue( true ); 
	sbSizer7->Add( m_pwxrbLeft, 0, wxALL, 5 );
	
	
	sbSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_pwxrbRight = new wxRadioButton( m_panel11, ID_RIGHT_RB, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer7->Add( m_pwxrbRight, 0, wxALL, 5 );
	
	bSizer16->Add( sbSizer7, 0, wxEXPAND, 5 );
	
	
	bSizer16->Add( 0, 25, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panel11, wxID_ANY, wxT("MTF Settings") ), wxVERTICAL );
	
	m_pwxcbSNCorr = new wxCheckBox( m_panel11, ID_SNCORR_CB, wxT("S/N Correction"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxcbSNCorr->SetValue(true);
	
	sbSizer8->Add( m_pwxcbSNCorr, 0, wxALL, 5 );
	
	m_pwxcbMaskCorr = new wxCheckBox( m_panel11, ID_MASK_CB, wxT("Masking Correction"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxcbMaskCorr->SetValue(true);
	
	sbSizer8->Add( m_pwxcbMaskCorr, 0, wxALL, 5 );
	
	bSizer16->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	
	bSizer16->Add( 0, 25, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panel11, wxID_ANY, wxT("Weighted STI") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 5, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_pwxstSTIMaleLbl = new wxStaticText( m_panel11, wxID_ANY, wxT("STI male:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSTIMaleLbl->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTIMaleLbl, 0, wxALL, 5 );
	
	m_pwxstSTIMale = new wxStaticText( m_panel11, ID_STI_MALE_ST, wxT("0.000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_pwxstSTIMale->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTIMale, 0, wxALL, 5 );
	
	m_pwxstSTIFemaleLbl = new wxStaticText( m_panel11, wxID_ANY, wxT("STI female:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSTIFemaleLbl->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTIFemaleLbl, 0, wxALL, 5 );
	
	m_pwxstSTIFemale = new wxStaticText( m_panel11, ID_STI_FEMALE_ST, wxT("0.000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_pwxstSTIFemale->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTIFemale, 1, wxALL, 5 );
	
	m_pwxstRaSTILbl = new wxStaticText( m_panel11, wxID_ANY, wxT("RaSTI:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstRaSTILbl->Wrap( -1 );
	fgSizer5->Add( m_pwxstRaSTILbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstRaSTI = new wxStaticText( m_panel11, ID_RASTI_ST, wxT("0.000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_pwxstRaSTI->Wrap( -1 );
	fgSizer5->Add( m_pwxstRaSTI, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstSTItelLbl = new wxStaticText( m_panel11, wxID_ANY, wxT("STItel:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSTItelLbl->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTItelLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstSTItel = new wxStaticText( m_panel11, wxID_ANY, wxT("0.000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_pwxstSTItel->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTItel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstSTIpaLbl = new wxStaticText( m_panel11, wxID_ANY, wxT("STIpa:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstSTIpaLbl->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTIpaLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstSTIpa = new wxStaticText( m_panel11, wxID_ANY, wxT("0.000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_pwxstSTIpa->Wrap( -1 );
	fgSizer5->Add( m_pwxstSTIpa, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer9->Add( fgSizer5, 1, wxEXPAND, 5 );
	
	bSizer16->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	
	bSizer16->Add( 0, 25, 0, wxEXPAND, 5 );
	
	m_pwxbtnSave = new wxButton( m_panel11, ID_SAVE_BTN, wxT("Save to File..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_pwxbtnSave, 0, wxALL|wxEXPAND, 5 );
	
	m_panel11->SetSizer( bSizer16 );
	m_panel11->Layout();
	bSizer16->Fit( m_panel11 );
	bSizer13->Add( m_panel11, 0, wxEXPAND | wxALL, 5 );
	
	m_panel10->SetSizer( bSizer13 );
	m_panel10->Layout();
	bSizer13->Fit( m_panel10 );
	bSizer11->Add( m_panel10, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxbtnHelp = new wxButton( m_panel7, wxID_HELP, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_wxbtnHelp, 0, wxALL, 5 );
	
	m_wxbtnOk = new wxButton( m_panel7, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_wxbtnOk, 0, wxALL, 5 );
	
	m_panel7->SetSizer( bSizer12 );
	m_panel7->Layout();
	bSizer12->Fit( m_panel7 );
	bSizer11->Add( m_panel7, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer11 );
	this->Layout();
	bSizer11->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( STIShowDlg::OnCloseDialog ) );
	m_pwxrbLeft->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STIShowDlg::OnLeftRadio ), NULL, this );
	m_pwxrbRight->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STIShowDlg::OnRightRadio ), NULL, this );
	m_pwxcbSNCorr->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( STIShowDlg::OnSnCorrectionCheck ), NULL, this );
	m_pwxcbMaskCorr->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( STIShowDlg::OnMaskCorrectionCheck ), NULL, this );
	m_pwxbtnSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STIShowDlg::OnSave ), NULL, this );
	m_wxbtnHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STIShowDlg::OnHelp ), NULL, this );
	m_wxbtnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STIShowDlg::OnOk ), NULL, this );
}

STIShowDlg::~STIShowDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( STIShowDlg::OnCloseDialog ) );
	m_pwxrbLeft->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STIShowDlg::OnLeftRadio ), NULL, this );
	m_pwxrbRight->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( STIShowDlg::OnRightRadio ), NULL, this );
	m_pwxcbSNCorr->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( STIShowDlg::OnSnCorrectionCheck ), NULL, this );
	m_pwxcbMaskCorr->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( STIShowDlg::OnMaskCorrectionCheck ), NULL, this );
	m_pwxbtnSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STIShowDlg::OnSave ), NULL, this );
	m_wxbtnHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STIShowDlg::OnHelp ), NULL, this );
	m_wxbtnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( STIShowDlg::OnOk ), NULL, this );
}
