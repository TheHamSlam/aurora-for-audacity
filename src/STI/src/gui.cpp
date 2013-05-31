/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  gui.cpp

  Simone Campanini

*******************************************************************//**

\class STISetupDialog \
\brief Dialog used with EffectAuroraSTI.

*//*******************************************************************/

#include <commdefs.h>
#include <gpfuncts.h>
#include <afart.h>

#include <wx/filename.h>

#include "gui.h"
#include "version.h"

//----------------------------------------------------------------------------
// STISetupDialog implementation
//----------------------------------------------------------------------------

void STISetupDialog::InitTrackChoice(wxChoice* pwxChoice)
{
   if(!pwxChoice->IsEmpty()) 
   {    
       pwxChoice->Clear();
       pwxChoice->Append(wxT("None"));
   }
   pwxChoice->Append(*(m_pEas->GetTrackNamesArray()));
}

void STISetupDialog::FillSigNoiseGrid()
{
    int nCh, nBand;
    for(nCh = 0; nCh < 2; nCh++)
    {
        // These band went from 125 Hz to 8 kHz, so there is an offset of 2 from standard Octave bands
        for(nBand = 0; nBand < 7; nBand++)
            m_pwxgridSplTable->SetCellValue(nBand, 0 + nCh, 
                                            wxString::Format(wxT("%.1f"), m_pAs->GetNoiseLevel(nBand + 2, nCh)));
        for(nBand = 0; nBand < 7; nBand++)
            m_pwxgridSplTable->SetCellValue(nBand, 2 + nCh, 
                                            wxString::Format(wxT("%.1f"), m_pAs->GetSignalLevel(nBand + 2, nCh)));
        for(nBand = 0; nBand < 7; nBand++)
            m_pwxgridSplTable->SetCellValue(nBand, 4 + nCh, 
                                            wxString::Format(wxT("%.1f"), m_pAs->GetSigNoiseLevel(nBand + 2, nCh)));
    }
}

void STISetupDialog::OnLeftFullscaleText( wxCommandEvent& event )
{
   m_pAs->SetFullScaleLevel(::TextPtrToDouble(m_pwxtcLeftFs), CH_LEFT);
}
    
void STISetupDialog::OnRightFullscaleText( wxCommandEvent& event )
{
    m_pAs->SetFullScaleLevel(::TextPtrToDouble(m_pwxtcRightFs), CH_RIGHT);
}
    
void STISetupDialog::OnCalibLeftChoice( wxCommandEvent& event )
{
    m_pEas->SetCalibrationTrackIdx(CH_LEFT, event.GetSelection());
    if(m_pEas->IsCalibrationTrackSet(CH_LEFT) && !m_pwxchRightCal->IsEnabled())
    {
        m_pwxchRightCal->Enable();
        m_pwxtcRightLevel->Enable();
        m_pwxbtnCalibrate->Enable();
    }
    else if(!m_pEas->IsCalibrationTrackSet(CH_LEFT))
    {
        m_pwxchRightCal->Disable();
        m_pwxtcRightLevel->Disable();
        m_pwxbtnCalibrate->Disable();
        // TODO reset right index
    }
}

void STISetupDialog::OnCalibRefLeftText( wxCommandEvent& event )
{
    m_pAs->SetCalibrationLevel(::TextPtrToDouble(m_pwxtcLeftLevel), CH_LEFT);
}

void STISetupDialog::OnCalibRightChoice( wxCommandEvent& event )
{
    m_pEas->SetCalibrationTrackIdx(CH_RIGHT, event.GetSelection());
}

void STISetupDialog::OnCalibRefRightText( wxCommandEvent& event )
{
    m_pAs->SetCalibrationLevel(::TextPtrToDouble(m_pwxtcRightLevel), CH_RIGHT);
}

void STISetupDialog::OnDoFullscaleCalibration( wxCommandEvent& event )
{
   if(m_pEas->AreCalibrationTracksSet())
   {
        if( !m_pEas->DoFullscaleCalibration(true) )  // stereo
        {
            ::wxMessageBox(wxT("Calibration failed."), 
                           wxT("Error"), 
                           wxOK | wxICON_ERROR); 
            return;
        }

        m_pwxtcLeftFs->SetValue(wxString::Format( wxT("%.1f"), 
                                                  m_pAs->GetFullScaleLevel(CH_LEFT)) );
        m_pwxtcRightFs->SetValue(wxString::Format( wxT("%.1f"), 
                                                   m_pAs->GetFullScaleLevel(CH_RIGHT)) );
   }
   else if(m_pEas->IsCalibrationTrackSet(CH_LEFT))
   {
        if( !m_pEas->DoFullscaleCalibration() )  // mono 
        {
            ::wxMessageBox(wxT("Calibration failed."), 
                           wxT("Error"), 
                           wxOK | wxICON_ERROR);             
            return;
        }

        m_pwxtcLeftFs->SetValue(wxString::Format( wxT("%.1f"), 
                                                  m_pAs->GetFullScaleLevel(CH_LEFT)) );
   }
   else 
   {
       ::wxMessageBox(wxT("No track(s) selected."), 
                      wxT("Error"), 
                      wxOK | wxICON_ERROR); 
   }
   ::wxMessageBox(wxT("Calibration done successifully."), 
                  wxT("Info"), 
                  wxOK | wxICON_INFORMATION);
}

void STISetupDialog::OnNoiseLeftChoice( wxCommandEvent& event )
{
    m_pEas->SetNoiseTrackIdx(CH_LEFT, event.GetSelection());
    if(m_pEas->IsNoiseTrackSet(CH_LEFT) && !m_pwxchRightBckNoise->IsEnabled())
    {
        m_pwxchRightBckNoise->Enable();
        if(m_pEas->IsSignalTrackSet(CH_LEFT) && !m_pwxbtnCalculateSPL->IsEnabled())
        {
            m_pwxbtnCalculateSPL->Enable();
        }
    }
    else if(!m_pEas->IsNoiseTrackSet(CH_LEFT))
    {
        m_pwxchRightBckNoise->Disable();
        m_pwxbtnCalculateSPL->Disable();
        // TODO reset right index
    }
}

void STISetupDialog::OnNoiseRightChoice( wxCommandEvent& event )
{
    m_pEas->SetNoiseTrackIdx(CH_RIGHT, event.GetSelection());
}

void STISetupDialog::OnSignalLeftChoice( wxCommandEvent& event )
{
    m_pEas->SetSignalTrackIdx(CH_LEFT, event.GetSelection());
    if(m_pEas->IsSignalTrackSet(CH_LEFT) && !m_pwxchRightSignal->IsEnabled())
    {
        m_pwxchRightSignal->Enable();
        if(m_pEas->IsNoiseTrackSet(CH_LEFT) && !m_pwxbtnCalculateSPL->IsEnabled())
        {
            m_pwxbtnCalculateSPL->Enable();
        }
    }
    else if(!m_pEas->IsSignalTrackSet(CH_LEFT))
    {
        m_pwxchRightSignal->Disable();
        // TODO reset right index
        m_pwxbtnCalculateSPL->Disable();
    }
}

void STISetupDialog::OnSignalRightChoice( wxCommandEvent& event )
{
    m_pEas->SetSignalTrackIdx(CH_RIGHT, event.GetSelection());
}

void STISetupDialog::OnSignalRadio( wxCommandEvent& event )
{
    m_pAs->SetSignalPlusNoise(false);
}

void STISetupDialog::OnSignalPlusNoiseRadio( wxCommandEvent& event )
{
    m_pAs->SetSignalPlusNoise(true);
}

void STISetupDialog::OnSplTableRightClick( wxGridEvent& event )
{
   PopupMenu(m_pwxSPLTableContextMenu);
}
    
void STISetupDialog::OnLoadSplValues( wxCommandEvent& event )
{
   if(m_ExportsMgr.OpenSavePrompt(STISpectrumExports::OPEN_PROMPT))
       FillSigNoiseGrid();
}

void STISetupDialog::OnSaveSplValues( wxCommandEvent& event )
{
    // Always save stereo data
    m_ExportsMgr.OpenSavePrompt(STISpectrumExports::SAVE_PROMPT);
}

void STISetupDialog::OnComputeSNRatio( wxCommandEvent& event )
{
    bool bIsStereo = false;
   
    if( m_pEas->AreSignalAndNoiseSet(CH_LEFT) &&
        m_pEas->AreSignalAndNoiseSet(CH_RIGHT) )
    {
        bIsStereo = true;
    }
    else if( !m_pEas->AreSignalAndNoiseSet(CH_LEFT) )
    {
        // At least the left channel must be set
        return;
    }
    
    if(!m_pEas->DoSNRatioCalculation(bIsStereo))
    {
        ::wxMessageBox(wxT("Error calculating signal level.\nNoise level too high in some bands."), 
                       wxT("Error"),
                       wxOK | wxICON_ERROR);
    }
    
    FillSigNoiseGrid();

    m_pSpectrumDlg = new STISpectrumDialog(this, m_pAs, m_pCfg, bIsStereo);
    m_pSpectrumDlg->SetClientSize(900, 440);
    m_pSpectrumDlg->Centre();
    m_pSpectrumDlg->ShowModal();
}

void STISetupDialog::OnLeftIRChoice( wxCommandEvent& event )
{
    int nSel = event.GetSelection();
    m_pEas->SetIrTrackIdx(CH_LEFT, nSel);

    if(nSel && !m_pwxchRightIr->IsEnabled())
    {
        m_pwxchRightIr->Enable();
    }
    else if(!nSel)
    {
        m_pwxchRightIr->Disable();
        // TODO reset right index
    }
    
    if( (!m_pwxbtnOk->IsEnabled()) && (nSel) )
        m_pwxbtnOk->Enable();
    
    if(!nSel && !m_pEas->IsIrTrackSet(CH_RIGHT))
        m_pwxbtnOk->Disable();
}

void STISetupDialog::OnRightIRChoice( wxCommandEvent& event )
{
    int nSel = event.GetSelection();
    m_pEas->SetIrTrackIdx(CH_RIGHT, nSel);
    
    if( (!m_pwxbtnOk->IsEnabled()) && (nSel) )
        m_pwxbtnOk->Enable();
    
    if(!nSel && !m_pEas->IsIrTrackSet(CH_LEFT))
        m_pwxbtnOk->Disable();
}

void STISetupDialog::OnFatText( wxCommandEvent& event )
{
    m_pAs->SetFirstArriveThreshold(::TextPtrToDouble(m_pwxtcFat) / 100.0);
}

void STISetupDialog::OnHelp( wxCommandEvent& event )
{
   wxString path = wxT("Docs/sti.html");
   wxFileName help_path(path);
   help_path.MakeAbsolute();

   ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void STISetupDialog::OnSplTableKeyPress( wxKeyEvent& event )
{
#ifndef __WXMAC__
    if( (event.GetModifiers() == 3) )              // Ctrl+C  ascii translated code.
#else
    if( (event.GetModifiers() == wxMOD_CMD) &&    // Command+C  on Apple machines
    	 event.GetKeyCode() == 99 )
#endif
    {   
	    wxCommandEvent cmd(wxEVT_COMMAND_MENU_SELECTED, ID_SPL_COPY_SELECTION_MENU);
        OnSplTableCopySelection(cmd);
    }
    //printf("keycode = %d\n", int(event.GetKeyCode()));
}

void STISetupDialog::OnSplTableCopySelection(wxCommandEvent & event)
{
    m_ExportsMgr.CopyGridSelectionToClipboard(m_pwxgridSplTable);
}

// 'ctors
STISetupDialog::STISetupDialog( wxWindow* parent, 
                                AuroraSTI* pAs,
                                EffectAuroraSTI* pEas,
                                AFConfig* pCfg )
  : STISetupDlg( parent ),
    m_pAs(pAs),
    m_pEas(pEas),
    m_ExportsMgr(parent, pAs),
    m_pCfg(pCfg)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Speech Transmission Index Calculation Module - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(STI_VERSION_TYPE, STI_RELEASE_CANDIDATE) << wxT(")");
    SetTitle(wxszTitle);

	// Draw logo
	wxBoxSizer* pLogoSizer;
	pLogoSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pwxbmpAuroraLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                                 AFArtProvider::GetBitmap(wxT("Aurora_logo")),
			                                 wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpAuroraLogo, 0, wxALL, 5 );

	pLogoSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_pwxbmpLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                           AFArtProvider::GetBitmap( wxT("sti_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();

   // Fill choices with track names
   InitTrackChoice(m_pwxchLeftCal);
   InitTrackChoice(m_pwxchRightCal);
   InitTrackChoice(m_pwxchLeftBckNoise);
   InitTrackChoice(m_pwxchRightBckNoise);
   InitTrackChoice(m_pwxchLeftSignal);
   InitTrackChoice(m_pwxchRightSignal);
   InitTrackChoice(m_pwxchLeftIr);
   InitTrackChoice(m_pwxchRightIr);
   
    // Initialize choices
    m_pwxchLeftCal->SetSelection(0);
    m_pwxchRightCal->SetSelection(0);
    m_pwxchLeftBckNoise->SetSelection(0);
    m_pwxchRightBckNoise->SetSelection(0);
	m_pwxchLeftSignal->SetSelection(0);
	m_pwxchRightSignal->SetSelection(0);
	m_pwxchLeftIr->SetSelection(0);
	m_pwxchRightIr->SetSelection(0);    

   // Init default fullscale levels
   m_pwxtcLeftFs->SetValue(wxString::Format(wxT("%.1f"), m_pAs->GetFullScaleLevel(CH_LEFT)));
   m_pwxtcRightFs->SetValue(wxString::Format(wxT("%.1f"), m_pAs->GetFullScaleLevel(CH_RIGHT)));
   
   // Init default calibration level (should be 94.0 dB)
   m_pwxtcLeftLevel->SetValue(wxString::Format(wxT("%.1f"), m_pAs->GetCalibrationLevel(CH_LEFT)));
   m_pwxtcRightLevel->SetValue(wxString::Format(wxT("%.1f"), m_pAs->GetCalibrationLevel(CH_RIGHT)));
   
   // Init First Arrive Threshold Percentage (default 20 %)
   m_pwxtcFat->SetValue(wxString::Format(wxT("%.1f"), 100.0 * m_pAs->GetFirstArriveThreshold()));

   FillSigNoiseGrid();

   // Set grid colors
   ::AuroraUpdateGridBackgroundColor(m_pwxgridSplTable);

   // init grids contextual menu event
   m_pwxSPLTableContextMenu = new wxMenu;   
   m_pwxSPLTableContextMenu->Append(ID_SPL_COPY_SELECTION_MENU, wxT("&Copy\tCtrl+C"));
   m_pwxSPLTableContextMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STISetupDialog::OnSplTableCopySelection), NULL, this );
   m_pwxgridSplTable->Connect(wxEVT_CHAR, wxCharEventHandler(STISetupDialog::OnSplTableKeyPress), NULL, this);
}

STISetupDialog::~STISetupDialog()
{
   m_pwxSPLTableContextMenu->Disconnect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STISetupDialog::OnSplTableCopySelection), NULL, this );
   m_pwxgridSplTable->Disconnect(wxEVT_CHAR, wxCharEventHandler(STISetupDialog::OnSplTableKeyPress), NULL, this);
}


//----------------------------------------------------------------------------
// STIShowDialog
//----------------------------------------------------------------------------
void STIShowDialog::UpdateTables()
{
    wxString wxszValue;
    int nBand;
    for(int nParam = 0; nParam < 14; nParam++)
    {
        for(nBand = 0; nBand < 7; nBand++)
        {
            wxszValue.Printf(wxT("%.3f"), m_pAs->GetMtfTableValue(nParam, nBand, m_nCurrentChannel));
            m_pwxgridMtfTable->SetCellValue(nParam, nBand, wxszValue);
        }
    }
    for(nBand = 0; nBand < 7; nBand++)
    {
        wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIValue(nBand, m_nCurrentChannel));
        m_pwxgridSTITable->SetCellValue(0, nBand, wxszValue);
    }

    wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIMale(m_nCurrentChannel));
    m_pwxstSTIMale->SetLabel(wxszValue);

    wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIFemale(m_nCurrentChannel));
    m_pwxstSTIFemale->SetLabel(wxszValue);

    wxszValue.Printf(wxT("%.3f"), m_pAs->GetRaSTI(m_nCurrentChannel));
    m_pwxstRaSTI->SetLabel(wxszValue);   

    wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTItel(m_nCurrentChannel));
    m_pwxstSTItel->SetLabel(wxszValue);

    wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIpa(m_nCurrentChannel));
    m_pwxstSTIpa->SetLabel(wxszValue);
}


void STIShowDialog::UpdatePlot()
{
    double adbSerie[14];
    int    nParam, nBand;

    const wxChar* awxpchLabels[] = { wxT("125 Hz"), wxT("250 Hz"), wxT("500 Hz"), wxT("1 kHz"),
                                     wxT("2 kHz"),  wxT("4 kHz"),  wxT("8 kHz") };
    //Some cleaning...
    m_pPlot->ClearSerie();
    m_pPlot->GetLegend()->Clear();

    AFDataSerie* pDs;
    wxColour col;
    for(nBand = AuroraSTI::RBD_125; nBand <= AuroraSTI::RBD_8k; nBand++)
    {
        for(nParam = 0; nParam < 14; nParam++)
            adbSerie[nParam] = 100.0 * m_pAs->GetMtfTableValue(nParam, nBand, m_nCurrentChannel );
       
        ::AuroraChooseColour(col, nBand);

        pDs = new AFDataSerie(14, adbSerie);
        pDs->SetLabel(awxpchLabels[nBand]);
        pDs->SetLineColour(col);

        m_pPlot->AddSerie(pDs);
    }
    
    m_pPlot->Refresh();
}


void STIShowDialog::OnMtfTableRigtClick( wxGridEvent& event )
{
    PopupMenu(m_pwxMtfTableContextMenu);
}

void STIShowDialog::OnMtfTableKeyPress( wxKeyEvent& event) 
{
#ifndef __WXMAC__
    if( (event.GetModifiers() == 3) )              // Ctrl+C  ascii translated code.
#else
    if( (event.GetModifiers() == wxMOD_CMD) &&    // Command+C  on Apple machines
        (event.GetKeyCode() == 99) )
#endif
    {   
	    wxCommandEvent cmd(wxEVT_COMMAND_MENU_SELECTED, ID_MTF_COPY_SELECTION_MENU);
        OnMtfTableCopySelection(cmd);
    }
}

void STIShowDialog::OnSTITableRightClick( wxGridEvent& event )
{
    PopupMenu(m_pwxSTITableContextMenu);
}

void STIShowDialog::OnSTITableKeyPress( wxKeyEvent& event) 
{
#ifndef __WXMAC__
    if( (event.GetModifiers() == 3) )              // Ctrl+C  ascii translated code.
#else
    if( (event.GetModifiers() == wxMOD_CMD) &&    // Command+C  on Apple machines
    	 event.GetKeyCode() == 'c' )
#endif
    {   
	    wxCommandEvent cmd(wxEVT_COMMAND_MENU_SELECTED, ID_STI_COPY_SELECTION_MENU);
        OnSTITableCopySelection(cmd);
    }
}

void STIShowDialog::OnLeftRadio( wxCommandEvent& event )
{
    m_nCurrentChannel = CH_LEFT;
    UpdateTables();
    UpdatePlot();
    m_pPlot->Refresh();
}

void STIShowDialog::OnRightRadio( wxCommandEvent& event )
{
    m_nCurrentChannel = CH_RIGHT;
    UpdateTables();
    UpdatePlot();
    m_pPlot->Refresh();
}

void STIShowDialog::OnSnCorrectionCheck( wxCommandEvent& event )
{
    m_pAs->SetSNCorrection(event.IsChecked());
    m_pAs->CalculateSTI(CH_LEFT);
    if(m_bIsStereo) 
        m_pAs->CalculateSTI(CH_RIGHT);
    
    UpdateTables();
    UpdatePlot();
}

void STIShowDialog::OnMaskCorrectionCheck( wxCommandEvent& event )
{
    m_pAs->SetMaskingCorrection(event.IsChecked());
    m_pAs->CalculateSTI(CH_LEFT);
    if(m_bIsStereo) 
        m_pAs->CalculateSTI(CH_RIGHT);
    
    UpdateTables();
    UpdatePlot();
}

void STIShowDialog::OnSave( wxCommandEvent& event )
{
    m_ExportsMgr.SavePrompt();
}

void STIShowDialog::OnHelp( wxCommandEvent& event )
{
   wxString path = wxT("Docs/sti.html");
   wxFileName help_path(path);
   help_path.MakeAbsolute();

   ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void STIShowDialog::OnOk( wxCommandEvent& event )
{
    EndModal(true);
}

void STIShowDialog::OnMtfTableCopySelection(wxCommandEvent & event)
{
    m_ExportsMgr.CopyGridSelectionToClipboard(m_pwxgridMtfTable);
}

void STIShowDialog::OnSTITableCopySelection(wxCommandEvent & event)
{
    m_ExportsMgr.CopyGridSelectionToClipboard(m_pwxgridSTITable);   
}


// 'ctors
STIShowDialog::STIShowDialog( wxWindow* parent,
                              AuroraSTI* pAs, const bool bIsStereo )
 : STIShowDlg( parent ),
   m_pAs(pAs),
   m_bIsStereo(bIsStereo),
   m_nCurrentChannel(CH_LEFT),
   m_ExportsMgr(parent, pAs, bIsStereo)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Speech Transmission Index Calculation Module - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(STI_VERSION_TYPE, STI_RELEASE_CANDIDATE) << wxT(")");
    SetTitle(wxszTitle);

	// Draw logo
	wxBoxSizer* pLogoSizer;
	pLogoSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pwxbmpAuroraLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                                 AFArtProvider::GetBitmap(wxT("Aurora_logo")),
			                                 wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpAuroraLogo, 0, wxALL, 5 );

	pLogoSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_pwxbmpLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                           AFArtProvider::GetBitmap( wxT("sti_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();

    // Create plot & plot notebook page
    m_pwxpnlPlotPage = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
    wxBoxSizer* bPlotSizer;
    bPlotSizer = new wxBoxSizer( wxVERTICAL );
    
    m_pPlot = new STIPlot(m_pwxpnlPlotPage, ID_PLOT);
    bPlotSizer->Add( m_pPlot, 1, wxALL|wxEXPAND, 5 );
    
    m_pwxpnlPlotPage->SetSizer( bPlotSizer );
    m_pwxpnlPlotPage->Layout();
    bPlotSizer->Fit( m_pwxpnlPlotPage );
        
    m_notebook2->AddPage( m_pwxpnlPlotPage, wxT("MTF Values Graph"), true );

    // Initialize plot
	const wxChar* awxpchFrqLabels[] = { wxT("0.63"), wxT("0.8"), wxT("1.0"), wxT("1.25"),
	                                    wxT("1.6"),  wxT("2.0"), wxT("2.5"), wxT("3.15"),
	                                    wxT("4.0"),  wxT("5.0"), wxT("6.3"), wxT("8.0"),
	                                    wxT("10.0"), wxT("12.5") };

    m_pPlot->GetFrqAxis()->SetTitle(wxT("M"));
    m_pPlot->GetFrqAxis()->ShowTitle(true);
    m_pPlot->GetFrqAxis()->ShowGrid(true);
    m_pPlot->GetFrqAxis()->AddCategories(awxpchFrqLabels, 14);

    m_pPlot->GetSTIAxis()->SetTitle(wxT("%"));
    m_pPlot->GetSTIAxis()->ShowTitle(true);
    m_pPlot->GetSTIAxis()->ShowGrid(true);
    m_pPlot->GetSTIAxis()->SetRange(0.0, 100.0, AFAxisBase::RF_INT);

    m_pPlot->GetLegend()->Show(true);


   // Disable channels check buttons if mono analysis
    if(!m_bIsStereo)
    {
        m_pwxrbLeft->Disable();
        m_pwxrbRight->Disable();
    }
    
    ::AuroraUpdateGridBackgroundColor(m_pwxgridMtfTable);
    ::AuroraUpdateGridBackgroundColor(m_pwxgridSTITable);

    // init grids contextual menu event
    m_pwxMtfTableContextMenu = new wxMenu;   
    m_pwxMtfTableContextMenu->Append(ID_MTF_COPY_SELECTION_MENU, wxT("&Copy\tCtrl+C"));
    m_pwxMtfTableContextMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STIShowDialog::OnMtfTableCopySelection), NULL, this );
    m_pwxgridMtfTable->Connect(wxEVT_CHAR, wxCharEventHandler(STIShowDialog::OnMtfTableKeyPress), NULL, this);

    m_pwxSTITableContextMenu = new wxMenu;  
    m_pwxSTITableContextMenu->Append(ID_STI_COPY_SELECTION_MENU, wxT("&Copy\tCtrl+C"));
    m_pwxSTITableContextMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STIShowDialog::OnSTITableCopySelection), NULL, this );
    m_pwxgridSTITable->Connect(wxEVT_CHAR, wxCharEventHandler(STIShowDialog::OnSTITableKeyPress), NULL, this);

    // Initialize values
    m_pwxrbLeft->SetValue(true); // It always starts with left channel selected
    m_pwxcbSNCorr->SetValue(m_pAs->IsSNCorrection());
    m_pwxcbMaskCorr->SetValue(m_pAs->IsMaskingCorrection());
    
    m_pAs->CalculateSTI(CH_LEFT);
    if(m_bIsStereo) 
        m_pAs->CalculateSTI(CH_RIGHT);

    UpdateTables();
    UpdatePlot();
}

STIShowDialog::~STIShowDialog()
{
   m_pwxMtfTableContextMenu->Disconnect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STIShowDialog::OnMtfTableCopySelection), NULL, this );
   m_pwxgridMtfTable->Disconnect(wxEVT_CHAR, wxCharEventHandler(STIShowDialog::OnMtfTableKeyPress), NULL, this);
   m_pwxSTITableContextMenu->Disconnect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STIShowDialog::OnSTITableCopySelection), NULL, this );
   m_pwxgridSTITable->Disconnect(wxEVT_CHAR, wxCharEventHandler(STIShowDialog::OnSTITableKeyPress), NULL, this);

}

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: c05d7383-e7cd-410e-b7b8-f45f47c9e283

