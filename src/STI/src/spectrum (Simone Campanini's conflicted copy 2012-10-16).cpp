/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  spectrum.cpp

  Simone Campanini

**********************************************************************/

#include <gpfuncts.h>
#include <afart.h>

#include "spectrum.h"
#include "version.h"

//----------------------------------------------------------------------------
// STISpectrumGridCellColoredRectRenderer implementation
//----------------------------------------------------------------------------
void STISpectrumGridCellColoredRectRenderer::Draw(wxGrid &grid, wxGridCellAttr& attr, wxDC &dc,
                                                  const wxRect& rect, int nRow, int nCol, bool bIsSelected)
{
   wxGridCellStringRenderer::Draw(grid, attr, dc, rect, nRow, nCol, bIsSelected);

   wxColour col;
   ::AuroraChooseColour(col, nRow);

   wxRect r = rect;
   r.SetWidth(r.width/2);
   r.SetHeight(r.height/2);
   r.x += (rect.width - r.width)/2;
   r.y += (rect.height - r.height)/2; 

   dc.SetPen(*wxBLACK);
   dc.SetBrush(wxBrush(col));
   dc.DrawRectangle(r);
}

//----------------------------------------------------------------------------
// STISpectrumDialog implementation
//----------------------------------------------------------------------------

void STISpectrumDialog::FillTable()
{
    wxString wxszValue;
    for(int nBand = 0; nBand < 12; nBand++)
    {
        wxszValue.Printf(wxT("%.1f"), m_pAs->GetNoiseLevel(nBand, m_nCurrentChnl)); 
        m_pwxgridSpectrumTable->SetCellValue(0, nBand+1, wxszValue);
        wxszValue.Printf(wxT("%.1f"), m_pAs->GetSignalLevel(nBand, m_nCurrentChnl));
        m_pwxgridSpectrumTable->SetCellValue(1, nBand+1, wxszValue);
        wxszValue.Printf(wxT("%.1f"), m_pAs->GetSigNoiseLevel(nBand, m_nCurrentChnl));
        m_pwxgridSpectrumTable->SetCellValue(2, nBand+1, wxszValue);
    }
}

void STISpectrumDialog::OnCloseDialog( wxCloseEvent& event )
{ 
	StoreGeometry();
    EndModal(true);     
}

void STISpectrumDialog::OnChannelSelect( wxCommandEvent& event )
{
    if(event.GetSelection() == m_nCurrentChnl) return;
    
    m_nCurrentChnl = event.GetSelection();
    
    m_pSpectrumPlot->ReplaceSerie(0, (const double*)m_pAs->GetNoiseSpectrumVector(m_nCurrentChnl), 12);
    m_pSpectrumPlot->ReplaceSerie(1, (const double*)m_pAs->GetSignalSpectrumVector(m_nCurrentChnl), 12);
    m_pSpectrumPlot->ReplaceSerie(2, (const double*)m_pAs->GetSigNoiseSpectrumVector(m_nCurrentChnl), 12);
    
    FillTable();    
    m_pSpectrumPlot->Refresh();
}

void STISpectrumDialog::OnLevelTableLabelClick( wxGridEvent& event )
{
    m_pSpectrumPlot->ToggleSerieVisibility(event.GetRow());
    m_pSpectrumPlot->Refresh();
}

void STISpectrumDialog::OnLevelTableRightClick( wxGridEvent& event )
{
    PopupMenu(m_pwxLevelContextMenu);
}

void STISpectrumDialog::OnLevelTableKeyPress( wxKeyEvent& event )
{
#ifndef __WXMAC__
    if( (event.GetModifiers() == 3) )              // Ctrl+C  ascii translated code.
#else
    if( (event.GetModifiers() == wxMOD_CMD) &&    // Command+C  on Apple machines
    	 event.GetKeyCode() == 99 )
#endif
    {   
	    wxCommandEvent cmd(wxEVT_COMMAND_MENU_SELECTED, ID_LEVEL_COPY_SELECTION_MENU);
        OnLevelTableCopySelection(cmd);
    }
}

void STISpectrumDialog::OnLevelTableCopySelection(wxCommandEvent & event)
{
    m_ExportsMgr.CopyGridSelectionToClipboard(m_pwxgridSpectrumTable);
}

void STISpectrumDialog::StoreGeometry()
{
	int nWidth, nHeight;
	this->GetSize(&nWidth, &nHeight);

	int nHorzSplitPos = m_pSplitter->GetSashPosition();

	m_pCfg->Write(wxT("/Aurora/STI/SpectrumDialogWidth"), nWidth);
	m_pCfg->Write(wxT("/Aurora/STI/SpectrumDialogHeight"), nHeight);
	m_pCfg->Write(wxT("/Aurora/STI/SpectrumDialogSplitterPosition"), nHorzSplitPos);
}

void STISpectrumDialog::RestoreGeometry()
{
	int nPos;
	if(m_pCfg->Read(wxT("/Aurora/STI/SpectrumDialogSplitterPosition"), &nPos))
	    m_pSplitter->SetSashPosition(nPos);

	int nWidth, nHeight;
    if(m_pCfg->Read(wxT("/Aurora/STI/SpectrumDialogWidth"), &nWidth) &&
       m_pCfg->Read(wxT("/Aurora/STI/SpectrumDialogHeight"), &nHeight))
    {
        this->SetSize(nWidth, nHeight);
    }
}

STISpectrumDialog::STISpectrumDialog( wxWindow* pParent,
                                      AuroraSTI* pAs,
                                      AFConfig* pCfg,
                                      const bool bIsStereo)
  : STISpectrumDlg(pParent),
    m_pAs(pAs),
    m_bIsStereo(bIsStereo),
    m_nCurrentChnl(CH_LEFT),
    m_ExportsMgr(pParent, pAs, bIsStereo),
    m_pCfg(pCfg)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Octave Bands Analisys - (v."));
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

    // Set data
    m_pSpectrumPlot->GetBandsAxis()->SetTitle(wxT("Octave Bands [Hz]"));
    m_pSpectrumPlot->GetBandsAxis()->ShowTitle(true);
    m_pSpectrumPlot->GetBandsAxis()->AddCategories(g_awxpchBandLabels, 12);

    m_pSpectrumPlot->GetLevelAxis()->SetTitle(wxT("Level [dB]"));
    m_pSpectrumPlot->GetLevelAxis()->ShowTitle(true);
    m_pSpectrumPlot->GetLevelAxis()->ShowGrid(true);
    m_pSpectrumPlot->GetLevelAxis()->SetRange(30.0, 130.0, AFAxisBase::RF_REAL);

    m_pSpectrumPlot->AddSerie((const double*)m_pAs->GetNoiseSpectrumVector(CH_LEFT), 12);
    m_pSpectrumPlot->AddSerie((const double*)m_pAs->GetSignalSpectrumVector(CH_LEFT), 12);
    m_pSpectrumPlot->AddSerie((const double*)m_pAs->GetSigNoiseSpectrumVector(CH_LEFT), 12);

    if(!m_bIsStereo) 
    {
        m_pwxstChnlSel->Disable();
        m_pwxchoiceChannel->Disable();
    }

    ::AuroraUpdateGridBackgroundColor(m_pwxgridSpectrumTable);

    wxGridCellAttr*  pCellAttr = new wxGridCellAttr();
    pCellAttr->SetReadOnly();
    for(int nRow = 0; nRow < 3; nRow++)
    {
        m_pwxgridSpectrumTable->SetCellRenderer(nRow, 0, new STISpectrumGridCellColoredRectRenderer);
        m_pwxgridSpectrumTable->SetRowAttr(nRow, pCellAttr->Clone());
    }
#ifdef __WXGTK__
    m_pwxgridSpectrumTable->SetRowLabelSize(140);
#endif
    FillTable();
    
    RestoreGeometry();

    m_pSpectrumPlot->Refresh();

    // init table context menu
    m_pwxLevelContextMenu = new wxMenu;   
    m_pwxLevelContextMenu->Append(ID_LEVEL_COPY_SELECTION_MENU, wxT("&Copy\tCtrl+C"));
    m_pwxLevelContextMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STISpectrumDialog::OnLevelTableCopySelection), NULL, this );
    m_pwxgridSpectrumTable->Connect(wxEVT_CHAR, wxCharEventHandler(STISpectrumDialog::OnLevelTableKeyPress), NULL, this);
}

STISpectrumDialog::~STISpectrumDialog()
{
   m_pwxLevelContextMenu->Disconnect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(STISpectrumDialog::OnLevelTableCopySelection), NULL, this );
   m_pwxgridSpectrumTable->Disconnect(wxEVT_CHAR, wxCharEventHandler(STISpectrumDialog::OnLevelTableKeyPress), NULL, this);
}
