/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  gui.cpp

  Simone Campanini

*******************************************************************//**

\class TimeHistoryAnalyzerDialog 
\brief Dialog used with EffectTimeHistoryAnalyzer.

*//****************************************************************//**

\class TimeHistoryAnalyzerShow
\brief Window that shows the time history analysis.

*//*******************************************************************/

#include "gui.h"

#include <commdefs.h>
#include <wx/filename.h>

#include <afart.h>
#include "version.h"

//----------------------------------------------------------------------------
// THAGridCellColoredRectRenderer implementation
//----------------------------------------------------------------------------
void THAGridCellColoredRectRenderer::Draw(wxGrid &grid, wxGridCellAttr& attr, wxDC &dc,
                                          const wxRect& rect, int nRow, int nCol, bool bIsSelected)
{
   wxGridCellStringRenderer::Draw(grid, attr, dc, rect, nRow, nCol, bIsSelected);

   wxColour wxcolFill;
   ::AuroraChooseColour(wxcolFill, nCol);

   wxRect r = rect;
   r.SetWidth(r.width/2);
   r.SetHeight(r.height/2);
   r.x += (rect.width - r.width)/2;
   r.y += (rect.height - r.height)/2; 

   dc.SetPen(*wxBLACK);
   dc.SetBrush(wxBrush(wxcolFill));
   dc.DrawRectangle(r);
}


//----------------------------------------------------------------------------
// TimeHistoryAnalyzerFrame implementation
//----------------------------------------------------------------------------
void TimeHistoryAnalyzerFrame::UpdateResults()
{
   //Setup grid
    int nCh,
	    nChnlsCount = m_paSignalTracks->GetCount(),
        nColsCount  = m_pwxgrdResults->GetNumberCols(),
        nNeededCols = (nChnlsCount+1) - nColsCount; //there is also the Avg column

    if(nNeededCols > 0)
    {
        m_pwxgrdResults->AppendCols(nNeededCols);
        InitColumns(nColsCount, nChnlsCount);
    }
    else if(nNeededCols < 0)
    {
	    m_pwxgrdResults->DeleteCols(nChnlsCount+1, -nNeededCols);
    }

    wxString wxszLabel;
    for(nCh = 0; nCh < nChnlsCount; nCh++)
    {
       wxszLabel =  m_paSignalTracks->Item(nCh).GetName();
 	   FillColumn(nCh, nChnlsCount, wxszLabel);
       m_pwxgrdResults->AutoSizeColumn(nCh);
    }
    // Avg channel
    wxszLabel = wxT("Avg");
    FillColumn(nChnlsCount, nChnlsCount, wxszLabel);


   //::AuroraUpdateGridBackgroundColor(m_pwxgrdResults);

   m_nCurrentChannel = 0;

   // ----------------- Plot update -----------------
   m_pPlot->GetTimeAxis()->SetFormat(AFAxis::RF_REAL);

   m_pPlot->GetLevelAxis()->SetRange(0.0, m_paSignalTracks->Item(m_nCurrentChannel).GetFullScale(), AFAxis::RF_LINEARdB);

   m_pPlot->SetHorzAxisAutorange(true);
   m_pPlot->SetVertAxisAutorange(false);

   m_pPlot->ClearSerie();

   AFTimeDataSerie *pDataSerie;

   wxColour wxcolLine;
   ::AuroraChooseColour(wxcolLine, m_nCurrentChannel);
   for(int nPlotType = 0; nPlotType < AFTimeHistoryAnalyzer::N_TIME_CONST; nPlotType++)
   {
	   pDataSerie = new AFTimeDataSerie(m_pResults[m_nCurrentChannel].GetBufferLength(),
										m_pResults[m_nCurrentChannel].GetBuffer(nPlotType),
										1000.0,         // Samplerate: there is a sample every 1 ms.
										m_paSignalTracks->Item(m_nCurrentChannel).GetFullScale());
	   pDataSerie->SetLineColour(wxcolLine);
	   m_pPlot->AddSerie(pDataSerie);
	   pDataSerie = 0;
   }
   m_pPlot->ShowSerie(size_t(m_nCurrentPlotType));

   m_pPlot->Refresh();

   if(!m_pwxchoicePlotType->IsEnabled())
	   m_pwxchoicePlotType->Enable();
}

void TimeHistoryAnalyzerFrame::InitColumns(const int nStartCol, const int nEndCol)
{
	int nRow;
    for(int nCol = nStartCol;
    		nCol < ((nEndCol < 0) ? m_pwxgrdResults->GetNumberCols() : nEndCol);
    		nCol ++)
    {
    	for(nRow = 0; nRow < (TimeHistoryAnalyzer::N_PARAMETERS + 2); nRow++)
    	    m_pwxgrdResults->SetCellBackgroundColour(nRow, nCol, *wxWHITE);

    	m_pwxgrdResults->SetCellRenderer(0, nCol, new THAGridCellColoredRectRenderer);
    }

}

void TimeHistoryAnalyzerFrame::FillColumn(const int nCh, const int nChnlsCount, wxString& wxszLabel)
{
    m_pwxgrdResults->SetColLabelValue(nCh, wxszLabel);

	wxString wxszValue;

	if(nCh < nChnlsCount)
	{
		switch(m_paSignalTracks->Item(nCh).GetSelectedFilter())
		{
		 case AFAudioTrack::FLT_LIN: wxszValue = wxT("Wide Band");       break;
		 case AFAudioTrack::FLT_ITU: wxszValue = wxT("ITU BandPass");    break;
		 case AFAudioTrack::FLT_IEC: wxszValue = wxT("IEC A-weighting"); break;
		 case AFAudioTrack::FLT_ISO: wxszValue = wxT("ISO whole body");  break;
		 case AFAudioTrack::FLT_UNI: wxszValue = wxT("UNI LP 250 Hz");   break;
		}
	}
	else
	{
		wxszValue = wxT("-");
	}
	m_pwxgrdResults->SetCellValue(1, nCh, wxszValue);

    int nParId = TimeHistoryAnalyzer::THA_FSL;
    if(nCh == nChnlsCount) nParId++;

    while(nParId < TimeHistoryAnalyzer::THA_DUR)
    {
	   wxszValue.Printf(wxT("%.2f"), m_pResults[nCh].GetParameter(nParId));
	   m_pwxgrdResults->SetCellValue(nParId+2, nCh, wxszValue);
	   nParId++;
    }

    wxszValue.Printf(wxT("%.3f"), m_pResults[nCh].GetParameter(nParId));
    m_pwxgrdResults->SetCellValue(nParId+2, nCh, wxszValue);
    nParId++;

    if(m_pResults[nCh].IsImpulsive())
	    wxszValue = wxT("yes");
    else
	    wxszValue = wxT("no");

    m_pwxgrdResults->SetCellValue(nParId+2, nCh, wxszValue);
}

void TimeHistoryAnalyzerFrame::StoreGeometry()
{
	int nWidth, nHeight;
	this->GetSize(&nWidth, &nHeight);

	int nHorzSplitPos = m_pHorzSplitter->GetSashPosition(),
	    nVertSplitPos = m_pVertSplitter->GetSashPosition();

	m_Cfg.Write(wxT("/Aurora/TimeHistoryAnalyzer/DialogWidth"), nWidth);
	m_Cfg.Write(wxT("/Aurora/TimeHistoryAnalyzer/DialogHeight"), nHeight);
	m_Cfg.Write(wxT("/Aurora/TimeHistoryAnalyzer/HorzSplitterPosition"), nHorzSplitPos);
	m_Cfg.Write(wxT("/Aurora/TimeHistoryAnalyzer/VertSplitterPosition"), nVertSplitPos);
}

void TimeHistoryAnalyzerFrame::RestoreGeometry()
{
	int nWidth, nHeight;
    if(m_Cfg.Read(wxT("/Aurora/TimeHistoryAnalyzer/DialogWidth"), &nWidth) &&
       m_Cfg.Read(wxT("/Aurora/TimeHistoryAnalyzer/DialogHeight"), &nHeight))
    {
        this->SetSize(nWidth, nHeight);
    }

	int nPos;

	if(m_Cfg.Read(wxT("/Aurora/TimeHistoryAnalyzer/HorzSplitterPosition"), &nPos))
	    m_pHorzSplitter->SetSashPosition(nPos);

	if(m_Cfg.Read(wxT("/Aurora/TimeHistoryAnalyzer/VertSplitterPosition"), &nPos))
	    m_pVertSplitter->SetSashPosition(nPos);

}

// ---- events handlers
void TimeHistoryAnalyzerFrame::OnCloseDialog( wxCloseEvent& event )
{
	StoreGeometry();
    EndModal(false);
}

void TimeHistoryAnalyzerFrame::OnFullscaleGridContentChanged( wxGridEvent& event )
{
	int nRow = event.GetRow(),
		nCol = event.GetCol();

	printf("[gui]: Fullscale grid changed in %d %d!!!\n", nRow, nCol); fflush(stdout); //DEBUG***

	wxASSERT_MSG(nCol < int(m_pEThan->GetTracksCount()),
			      wxT("THADlg: The requested column is out of range!!!"));

	switch(nRow)
	{
		case 0: // track name row
		{
	        wxString wxszName = m_pwxgrdFullscales->GetCellValue(nRow, nCol),
			         wxszLabel;
            wxszLabel << wxT("Ch ") << nCol+1 << wxT("/") <<  wxszName;
	        m_pwxgrdCalibration->SetColLabelValue(nCol, wxszLabel);
            m_pwxgrdCalibration->AutoSizeColumn(nCol); 
	        m_awxszCalibrationColsLabels[nCol] = wxszLabel;

	        //printf("[gui]: Track name %s\n", (const char*)wxszLabel.ToAscii()); fflush(stdout); //DEBUG***
		}
	    break;

		case 2: // fullscales row
		{
	    	for(int nCh = 0; nCh < int(m_pEThan->GetTracksCount()); nCh++)
	    	{
	    	    m_pwxgrdFullscales->SetCellBackgroundColour(2, nCh, *wxWHITE);
	    	}

		}
		break;
	}
}

void TimeHistoryAnalyzerFrame::OnAnalyze( wxCommandEvent& event )
{
   int nCh = 0;
   double dbFsValue, dbRefValue;
   wxString wxszTrackName, wxszFilterName, wxszValue, wxszPath;

   m_pEThan->ClearSignalTrackList();

   for(int nCol = 0; nCol < int(m_pEThan->GetTracksCount()); nCol++)
   {
	   wxszTrackName = m_pwxgrdFullscales->GetCellValue(0, nCol);
	   if(wxszTrackName != wxT("None"))
	   {
		   wxszFilterName = m_pwxgrdFullscales->GetCellValue(1, nCol);

		   wxszValue = m_pwxgrdFullscales->GetCellValue(2, nCol);
		   dbFsValue = ::StringToDouble(wxszValue);
		   printf("[gui] calibration for channel %d: %.2f\n", nCh, dbFsValue); // DEBUG***

		   // store fullscale value to configuration file
		   wxszPath.Printf(wxT("/Aurora/TimeHistoryAnalyzer/FullScale_Ch_%d"), nCh + 1);
		   m_Cfg.Write(wxszPath, dbFsValue);

		   wxszValue = m_pwxgrdCalibration->GetCellValue(1, nCol);
		   dbRefValue = ::StringToDouble(wxszValue);

		   // store reference value to configuration file
		   wxszPath.Printf(wxT("/Aurora/TimeHistoryAnalyzer/Calibration_Ch_%d"), nCh + 1);
		   m_Cfg.Write(wxszPath, dbRefValue);

		   m_Cfg.Flush();

		   m_pEThan->AddSignalTrackListItem(nCh, wxszTrackName, wxszFilterName, dbFsValue);

           nCh++;
	   }
   }

	if(nCh == 0)
	{
		::wxMessageBox(wxT("No tracks selected. Please choose almost one..."),
					   wxT("Error"),
					   wxOK | wxICON_ERROR);
		return;
	}

	m_pResults = m_pEThan->DoAnalysis();

	if(!m_pResults)
	{
		::wxMessageBox(wxT("An error has been occourred during analysis process."),
					   wxT("Error"),
					   wxOK | wxICON_ERROR);
		return;
	}

	UpdateResults();
}

void TimeHistoryAnalyzerFrame::OnRemoveDCCheck( wxCommandEvent& event )
{
	m_pThan->SetRemoveDC(event.IsChecked());
}

void TimeHistoryAnalyzerFrame::OnCalibrationGridContentChanged( wxGridEvent& event )
{}

void TimeHistoryAnalyzerFrame::OnCalibrate( wxCommandEvent& event )
{
	int nCh = 0;
	double dbRefValue;

	wxString wxszTrackName, wxszValue;

    if(m_pwxcbCh1ForAll->IsChecked())
    {
    	// get Ch 1 track name
    	wxszValue = m_pwxgrdCalibration->GetCellValue(0, 0);
    	if(wxszValue == wxT("None"))
    	{
    		::wxMessageBox(wxT("No calibration track selected."),
    				       wxT("Error"),
    				       wxOK | wxICON_ERROR);
    		return;
    	}

    	wxszTrackName = m_pwxgrdCalibration->GetCellValue(0, 0);

    	wxszValue  = m_pwxgrdCalibration->GetCellValue(1, 0);
    	dbRefValue = ::StringToDouble(wxszValue);

    	m_pEThan->AddCalibrationTrackListItem(0, wxszTrackName, dbRefValue);

    	double dbFullscale;
    	if(!m_pEThan->DoFullscaleCalibration(&dbFullscale))
        {
            m_pEThan->ClearCalibrationTrackList();

            ::wxMessageBox(wxT("Calibration failed!"), 
                           wxT("Error"), 
                           wxOK | wxICON_ERROR);
            return;
        }

    	// Update Fullscale grid
    	wxszValue.Printf(wxT("%.2f"), dbFullscale);
    	for(nCh = 0; nCh < int(m_pEThan->GetTracksCount()); nCh++)
    	{
    	    m_pwxgrdFullscales->SetCellValue(2, nCh, wxszValue);
	        m_pwxgrdFullscales->SetCellBackgroundColour(2, nCh, *wxGREEN);
    	}
    }
    else
    {
        for(nCh = 0; nCh < int(m_pEThan->GetTracksCount()); nCh++)
        {
        	wxszTrackName = m_pwxgrdCalibration->GetCellValue(0, nCh);
        	if(wxszTrackName != wxT("None"))
        	{
        	    wxszValue  = m_pwxgrdCalibration->GetCellValue(1, nCh);
        	    dbRefValue = ::StringToDouble(wxszValue);

      		    m_pEThan->AddCalibrationTrackListItem(nCh, wxszTrackName, dbRefValue);
            }
        }

    	double* adbFullscale = new double [m_pEThan->GetTracksCount()];
        if(!m_pEThan->DoFullscaleCalibration(adbFullscale))
        {
            delete [] adbFullscale;
            m_pEThan->ClearCalibrationTrackList();

            ::wxMessageBox(wxT("Calibration failed!"), 
                           wxT("Error"), 
                           wxOK | wxICON_ERROR);
            return;
        }

    	// Update Fullscale grid
    	for(nCh = 0; nCh < int(m_pEThan->GetTracksCount()); nCh++)
    	{
        	wxszValue.Printf(wxT("%.2f"), adbFullscale[nCh]);
    	    m_pwxgrdFullscales->SetCellValue(2, nCh, wxszValue);
    	    m_pwxgrdFullscales->SetCellBackgroundColour(2, nCh, *wxGREEN);
    	}
        delete [] adbFullscale;
    }
    m_pEThan->ClearCalibrationTrackList();
           
    ::wxMessageBox(wxT("Calibration done successifully!"), 
                   wxT("Info"), 
                   wxOK | wxICON_INFORMATION);
}

void TimeHistoryAnalyzerFrame::OnApplyToAllCheck( wxCommandEvent& event )
{
   int nCol;
   if(event.IsChecked())
   {
	   wxString wxszValue = wxT("All channels ");
	   m_pwxgrdCalibration->SetColLabelValue(0, wxszValue);

	   wxszValue = wxT(" ");
	   for(nCol = 1; nCol < int(m_pEThan->GetTracksCount()); nCol++ )
	   {
		   m_pwxgrdCalibration->SetColLabelValue(nCol, wxszValue);
		   m_pwxgrdCalibration->SetCellBackgroundColour(0, nCol, ::AuroraGetCanvasColour());
		   m_pwxgrdCalibration->SetCellBackgroundColour(1, nCol, ::AuroraGetCanvasColour());
	   }
   }
   else
   {
	   m_pwxgrdCalibration->SetColLabelValue(0, m_awxszCalibrationColsLabels[0]);
	   for(nCol = 1; nCol < int(m_pEThan->GetTracksCount()); nCol++ )
	   {
		   m_pwxgrdCalibration->SetColLabelValue(nCol, m_awxszCalibrationColsLabels[nCol]);
		   m_pwxgrdCalibration->SetCellBackgroundColour(0, nCol, *wxWHITE);
		   m_pwxgrdCalibration->SetCellBackgroundColour(1, nCol, *wxWHITE);
	   }
   }
}

void TimeHistoryAnalyzerFrame::OnSelectDisplay( wxCommandEvent& event )
{
	m_nCurrentPlotType = event.GetSelection();
	m_pPlot->ShowSerie(m_nCurrentPlotType);
	m_pPlot->Refresh();
}

void TimeHistoryAnalyzerFrame::OnGridCellRightClick( wxGridEvent& event )
{
	PopupMenu(m_pContextMenu);
}

void TimeHistoryAnalyzerFrame::OnTogglePlot( wxGridEvent& event )
{
   int nCh = event.GetCol();
   if(nCh < int(m_paSignalTracks->GetCount()))
   {
		m_nCurrentChannel = nCh;
		wxColour wxcolLine;
		::AuroraChooseColour(wxcolLine, m_nCurrentChannel);

		for(int nPlotType = 0; nPlotType < AFTimeHistoryAnalyzer::N_TIME_CONST; nPlotType++)
		{
		   m_pPlot->ReplaceTimeSerie(nPlotType,
									 m_pResults[m_nCurrentChannel].GetBuffer(nPlotType),
									 m_pResults[m_nCurrentChannel].GetBufferLength(),
									 m_paSignalTracks->Item(m_nCurrentChannel).GetFullScale(),
									 wxcolLine);
		}
		m_pPlot->ShowSerie(size_t(m_nCurrentPlotType));
		m_pPlot->Refresh();
   }
}

void TimeHistoryAnalyzerFrame::OnExport( wxCommandEvent& event )
{
	if(m_pExportData)
	{
        m_pExportData->SetCurrentPlotType(m_nCurrentPlotType);
        m_pExportData->SaveToFile();
	}
}

void TimeHistoryAnalyzerFrame::OnHelp( wxCommandEvent& event )
{
    wxString wxszPath = wxT("");
    wxszPath << wxT("Docs") << TRAILING_SLASH << wxT("itup56.html");
    wxFileName help_path(wxszPath);
    help_path.MakeAbsolute();

    ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void TimeHistoryAnalyzerFrame::OnAddTracksBtn( wxCommandEvent& event )
{
	StoreGeometry();
    EndModal(true);
}

void TimeHistoryAnalyzerFrame::OnOk( wxCommandEvent& event )
{
	StoreGeometry();
	EndModal(false);
}

void TimeHistoryAnalyzerFrame::OnCopyTableToClipboard( wxCommandEvent& event )
{
	if(m_pExportData)
        m_pExportData->CopyEntireTableToClipboard();
}

void TimeHistoryAnalyzerFrame::OnCopySelection( wxCommandEvent& event )
{
	if(m_pExportData)
        m_pExportData->CopyGridSelectionToClipboard(m_pwxgrdResults);
}

/** 'ctors */
TimeHistoryAnalyzerFrame::TimeHistoryAnalyzerFrame(wxWindow* pParent,
                                                   TimeHistoryAnalyzer* pThan,
                                                   EffectTimeHistoryAnalyzer* pEThan)
  : THADialog(pParent),
    m_pThan(pThan),
    m_pEThan(pEThan),
    m_paSignalTracks(0),
    m_pResults(0),
    m_pExportData(0),
    m_nCurrentPlotType(0),
    m_nCurrentChannel(0),
    m_pContextMenu(0)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Time History Analyzer - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(THA_VERSION_TYPE, THA_RELEASE_CANDIDATE) << wxT(")");
    SetTitle(wxszTitle);

	// Setup graphics.
	InitArtProvider();

	//Setup logo
	wxBoxSizer* pLogoSizer;
	pLogoSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pwxbmpAuroraLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                                 AFArtProvider::GetBitmap(wxT("Aurora_logo")),
			                                 wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpAuroraLogo, 0, wxALL, 5 );

	pLogoSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_pwxbmpTHALogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                              AFArtProvider::GetBitmap( wxT("tha_logo")),
			                              wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpTHALogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();

   // Get signals track list
	m_paSignalTracks = m_pEThan->GetSignalTrackList();

   // Setup track names list
   m_pEThan->SetTracksNamesArray(m_awxszTrackNames);
   m_awxszTrackNames.Insert(wxString(wxT("None")), 0);

   int nTracksCount = m_pEThan->GetTracksCount(),
	   nColsCount   = m_pwxgrdFullscales->GetNumberCols(),
	   nNeededCols  = (nTracksCount - nColsCount),
	   nCol         = 0;

   if(nNeededCols > 0)
   {
	   m_pwxgrdFullscales->AppendCols(nNeededCols);
	   m_pwxgrdCalibration->AppendCols(nNeededCols);
   }

   // grid on setup page.
   //m_wxcolPanelsBckgnd = m_pwxpnlUpper->GetBackgroundColour();

    m_pwxgrdFullscales->SetDefaultCellBackgroundColour(::AuroraGetCanvasColour());
    m_pwxgrdCalibration->SetDefaultCellBackgroundColour(::AuroraGetCanvasColour());

   const wxString apwxchFilterLabels[] = { wxT("None"),
										   wxT("ITU Band-Pass filter (160-5500 Hz)"),
										   wxT("IEC \"A\" weighting filter"),
										   wxT("ISO 2631 whole body combined"),
										   wxT("UNI 9916 Low Pass 250 Hz") };
   double   dbValue;
   wxString wxszValue, wxszPath;

   for(nCol = 0; nCol < nTracksCount; nCol++)
   {
	   wxszValue.Printf(wxT("Ch %d"), nCol+1);
	   m_pwxgrdFullscales->SetColLabelValue(nCol, wxszValue);

	   m_pwxgrdFullscales->SetCellEditor(0, nCol, new wxGridCellChoiceEditor(m_awxszTrackNames));
	   m_pwxgrdFullscales->SetCellEditor(1, nCol, new wxGridCellChoiceEditor(5, apwxchFilterLabels));
	   m_pwxgrdFullscales->SetCellEditor(2, nCol, new wxGridCellFloatEditor(4,2)); // width 4, precision 2 (0.00)

	   m_pwxgrdFullscales->SetCellValue(0, nCol, m_awxszTrackNames[nCol+1]);
	   m_pwxgrdFullscales->SetCellValue(1, nCol, m_awxszTrackNames[0]); // Not the same meaning, but the same string...

	   // Get stored data from configuration file
	   wxszPath.Printf(wxT("/Aurora/TimeHistoryAnalyzer/FullScale_Ch_%d"), nCol + 1);
	   if(!m_Cfg.Read(wxszPath, &dbValue))
		   dbValue = 120.0; // default fullscale value

	   wxszValue.Printf(wxT("%.2f"), dbValue);
	   m_pwxgrdFullscales->SetCellValue(2, nCol, wxszValue);

       m_pwxgrdFullscales->SetCellBackgroundColour(0, nCol, *wxWHITE);
       m_pwxgrdFullscales->SetCellBackgroundColour(1, nCol, *wxWHITE);
       m_pwxgrdFullscales->SetCellBackgroundColour(2, nCol, *wxWHITE);
   }

   // grid on calibration page
   for(nCol = 0; nCol < nTracksCount; nCol++)
   {
	   wxszValue.Printf(wxT("Ch %d"), nCol+1);
	   m_awxszCalibrationColsLabels.Add(wxszValue); // Backup...

	   wxszValue << wxT("/") << m_awxszTrackNames[nCol+1];
	   m_pwxgrdCalibration->SetColLabelValue(nCol, wxszValue);

	   m_pwxgrdCalibration->SetCellEditor(0, nCol, new wxGridCellChoiceEditor(m_awxszTrackNames));
	   m_pwxgrdCalibration->SetCellEditor(1, nCol, new wxGridCellFloatEditor(4,2)); // width 4, precision 2 (0.00)

	   m_pwxgrdCalibration->SetCellValue(0, nCol, m_awxszTrackNames[0]);

	   // Get stored data from configuration file
	   wxszPath.Printf(wxT("/Aurora/TimeHistoryAnalyzer/Calibration_Ch_%d"), nCol + 1);
	   if(!m_Cfg.Read(wxszPath, &dbValue))
		   dbValue = 94.0; // default reference value

	   wxszValue.Printf(wxT("%.2f"), dbValue);
	   m_pwxgrdCalibration->SetCellValue(1, nCol, wxszValue);

       m_pwxgrdCalibration->SetCellBackgroundColour(0, nCol, *wxWHITE);
       m_pwxgrdCalibration->SetCellBackgroundColour(1, nCol, *wxWHITE);
   }

   //Sizing..try to get text width
   wxFont font = m_pwxgrdFullscales->GetDefaultCellFont();
   size_t unTextWidth = 34; // The size of the longer filter label.
   for(int n = 0; n < nTracksCount; n++)
   {
       if(m_awxszTrackNames[n].Length() > unTextWidth) 
           unTextWidth = m_awxszTrackNames[n].Length(); 
   }

   int nFsColSize  = iround(unTextWidth * font.GetPointSize() * 0.6), // avg. font width.
       nCalColSize = iround((unTextWidth + 5) * font.GetPointSize() * 0.6); 
   for(nCol = 0; nCol < nColsCount; nCol++) // ???
   {
	   m_pwxgrdFullscales->SetColSize(nCol, nFsColSize);
	   m_pwxgrdCalibration->SetColSize(nCol, nCalColSize);
   }

   // Columns that don't contain data should be grayed
   wxszValue = wxT(" ");
   for(nCol = nTracksCount; nCol < nColsCount; nCol++ )
   {
	   m_pwxgrdFullscales->SetColLabelValue(nCol, wxszValue);
	   m_pwxgrdCalibration->SetColLabelValue(nCol, wxszValue);
   }

   // ------- init results table ------
   m_pwxgrdResults->AppendCols(nTracksCount);

   //m_pwxgrdResults->SetDefaultCellBackgroundColour(m_wxcolPanelsBckgnd); 
   m_pwxgrdResults->SetDefaultCellBackgroundColour(*wxWHITE);
   //m_pwxgrdResults->SetDefaultCellBackgroundColour(::AuroraGetCanvasColour());

   int nParId;
   for(nCol = 0; nCol < nTracksCount; nCol++)
   {
       wxszValue.Printf(wxT("Ch %d"), nCol+1);
	   m_pwxgrdResults->SetColLabelValue(nCol, wxszValue);

       m_pwxgrdResults->SetCellRenderer(0, nCol, new THAGridCellColoredRectRenderer);
       m_pwxgrdResults->SetCellValue(1, nCol, wxT("Wide Band"));
       m_pwxgrdResults->SetCellBackgroundColour(1, nCol, *wxWHITE);
       
       for(nParId  = 2; nParId <= TimeHistoryAnalyzer::N_PARAMETERS; nParId++)
       {
          m_pwxgrdResults->SetCellValue(nParId, nCol, wxT("-"));
          m_pwxgrdResults->SetCellBackgroundColour(nParId, nCol, *wxWHITE);
       }
   }
   wxszValue = wxT("Avg");
   m_pwxgrdResults->SetColLabelValue(nCol, wxszValue);
   for(nParId  = 1; nParId <= TimeHistoryAnalyzer::N_PARAMETERS; nParId++)
   {
      m_pwxgrdResults->SetCellValue(nParId, nCol, wxT("-"));
      m_pwxgrdResults->SetCellBackgroundColour(nParId, nCol, *wxWHITE);
   }

   m_pwxgrdResults->SetCellValue(1, nCol, wxT("-"));

//   ::AuroraUpdateGridBackgroundColor(m_pwxgrdResults);

   // ----------------- Plot Initialization -----------------
   m_pwxchoicePlotType->SetSelection(m_nCurrentPlotType);
    
   m_pPlot->GetTimeAxis()->SetTitle(wxT("Time [s]"));
   m_pPlot->GetTimeAxis()->ShowTitle(true);
   m_pPlot->GetTimeAxis()->ShowGrid(true);
   m_pPlot->GetTimeAxis()->SetRange(0.0, 10.0, AFAxis::RF_REAL);

   m_pPlot->GetLevelAxis()->SetTitle(wxT("Level [dB]"));
   m_pPlot->GetLevelAxis()->ShowTitle(true);
   m_pPlot->GetLevelAxis()->ShowGrid(true);
   m_pPlot->GetLevelAxis()->SetRange(0.0, 120.0, AFAxis::RF_LINEARdB);

   m_pPlot->SetTopBorder(false);

   RestoreGeometry();

   // init contextual menu event
   m_pContextMenu = new wxMenu;
   m_pContextMenu->Append(ID_COPY_SELECTION_MENU, wxT("&Copy selection\tCtrl+C"));
   m_pContextMenu->Append(ID_COPY_TABLE_MENU, wxT("&Copy entire table"));
   m_pContextMenu->Append(ID_EXPORT_TABLE_MENU, wxT("&Export to file..."));
   m_pContextMenu->Connect(ID_COPY_SELECTION_MENU, wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(TimeHistoryAnalyzerFrame::OnCopySelection), NULL, this );
   m_pContextMenu->Connect(ID_COPY_TABLE_MENU, wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(TimeHistoryAnalyzerFrame::OnCopyTableToClipboard), NULL, this );
   m_pContextMenu->Connect(ID_EXPORT_TABLE_MENU, wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(TimeHistoryAnalyzerFrame::OnExport), NULL, this );

}

TimeHistoryAnalyzerFrame::~TimeHistoryAnalyzerFrame()
{
	m_pContextMenu->Disconnect(ID_COPY_SELECTION_MENU, wxEVT_COMMAND_MENU_SELECTED,
	                           wxCommandEventHandler(TimeHistoryAnalyzerFrame::OnCopySelection), NULL, this );
	m_pContextMenu->Disconnect(ID_COPY_TABLE_MENU, wxEVT_COMMAND_MENU_SELECTED,
	                           wxCommandEventHandler(TimeHistoryAnalyzerFrame::OnCopyTableToClipboard), NULL, this );
	m_pContextMenu->Disconnect(ID_EXPORT_TABLE_MENU, wxEVT_COMMAND_MENU_SELECTED,
	                           wxCommandEventHandler(TimeHistoryAnalyzerFrame::OnExport), NULL, this );
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

