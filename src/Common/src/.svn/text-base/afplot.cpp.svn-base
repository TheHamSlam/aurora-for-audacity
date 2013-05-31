/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common Libraries

  afplot.cpp

  Simone Campanini

*******************************************************************//**

\class AFPlot
\brief Plot parent class (MUST be derived!)

*//*******************************************************************/

#include "gpfuncts.h"
#include "afplot.h"

#if wxUSE_METAFILE
   #include <wx/metafile.h>
#endif

#include <wx/clipbrd.h>
#include <wx/menu.h>

//----------------------------------------------------------------------------
// AFLegendEntry implementation
//----------------------------------------------------------------------------

#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfAFLegendEntry);

//----------------------------------------------------------------------------
// AFLegend implementation
//----------------------------------------------------------------------------
void AFLegend::FindMaxLabelsDims(wxDC& dc)
{
	wxSize sz;
	for(size_t un = 0; un < m_aEntries.GetCount(); un++)
	{
	    sz = dc.GetTextExtent(m_aEntries[un].GetLabel());

		if(sz.GetWidth() > m_wxsizeMaxLabelsDims.GetWidth())
			m_wxsizeMaxLabelsDims.SetWidth(sz.GetWidth());

		if(sz.GetHeight() > m_wxsizeMaxLabelsDims.GetHeight())
			m_wxsizeMaxLabelsDims.SetHeight(sz.GetHeight());
	}
}

void AFLegend::AddLabel(wxString& wxszLabel, const wxColour& wxcolColour)
{
	wxColour col = wxcolColour;
	if(col == wxNullColour)
		::AuroraChooseColour(col, int(m_aEntries.GetCount()));

    m_aEntries.Add(new AFLegendEntry(wxszLabel, col));
}

void AFLegend::AddLabel(const wxChar* pwxchLabel, const wxColour& wxcolColour)
{
	wxColour col = wxcolColour;
	if(col == wxNullColour)
		::AuroraChooseColour(col, int( m_aEntries.GetCount()));

	m_aEntries.Add(new AFLegendEntry(pwxchLabel, col));
}

void AFLegend::RemoveLabel(const int nIdx)
{
    m_aEntries.RemoveAt(size_t(nIdx));
}

void AFLegend::Draw(wxDC& dc, wxRect& wxrectClientArea)
{
   int nLabelsCount = m_aEntries.GetCount();
   if(m_bShow && (nLabelsCount > 0))
   {
	   dc.SetFont(m_wxfntFont);
	   if(m_wxsizeMaxLabelsDims == wxSize(0,0))
		   FindMaxLabelsDims(dc);

	   // Evaluate legend box sizes (5 is the Legend border, 10 is the sample coloured line size)
	   m_wxrectBox.width  = LGD_MARGIN + LGD_LINE_WIDTH + LGD_MARGIN + m_wxsizeMaxLabelsDims.GetWidth() + LGD_MARGIN;
	   m_wxrectBox.height = LGD_MARGIN + nLabelsCount*(m_wxsizeMaxLabelsDims.GetHeight() + LGD_MARGIN);

	   switch(m_nPosition)
	   {
		   case TOP_LEFT:
			   m_wxrectBox.x = wxrectClientArea.GetLeft() + LGD_BORDER;
			   m_wxrectBox.y = wxrectClientArea.GetTop()  + LGD_BORDER;
			   break;

		   case TOP_RIGHT:
			   m_wxrectBox.x = wxrectClientArea.GetRight() - (m_wxrectBox.width + LGD_BORDER);
			   m_wxrectBox.y = wxrectClientArea.GetTop()   + LGD_BORDER;
			   break;

		   case BOTTOM_RIGHT:
			   m_wxrectBox.x = wxrectClientArea.GetRight()  - (m_wxrectBox.width  + LGD_BORDER);
			   m_wxrectBox.y = wxrectClientArea.GetBottom() - (m_wxrectBox.height + LGD_BORDER);
			   break;

		   case BOTTOM_LEFT:
			   m_wxrectBox.x = wxrectClientArea.GetLeft()   + LGD_BORDER;
			   m_wxrectBox.y = wxrectClientArea.GetBottom() - (m_wxrectBox.height + LGD_BORDER);
			   break;
	   }
	   dc.SetBrush(*wxWHITE_BRUSH);
	   dc.SetPen(*wxBLACK_PEN);
	   dc.DrawRectangle(m_wxrectBox);
/*
	   printf("[canvas] l r t b %d %d %d %d\n", wxrectClientArea.GetLeft(), wxrectClientArea.GetRight(),
			                                    wxrectClientArea.GetTop(), wxrectClientArea.GetBottom());
	   printf("[canvas] x y w h %d %d %d %d\n", wxrectClientArea.x, wxrectClientArea.y,
			                                    wxrectClientArea.width, wxrectClientArea.height);

	   printf("[legend] x y w h : %d %d %d %d\n", m_wxrectBox.x, m_wxrectBox.y, m_wxrectBox.width, m_wxrectBox.height);
       fflush(stdout);
*/
	   wxPen pen;
	   for(int n = 0; n < nLabelsCount; n++)
	   {
		   pen.SetColour(m_aEntries[n].GetColour());
		   dc.SetPen(pen);
		   dc.DrawLine(m_wxrectBox.x + LGD_MARGIN,
					   m_wxrectBox.y + LGD_MARGIN + m_wxsizeMaxLabelsDims.GetHeight()/2 + n*(m_wxsizeMaxLabelsDims.GetHeight() + LGD_MARGIN),
					   m_wxrectBox.x + LGD_MARGIN + LGD_LINE_WIDTH,
					   m_wxrectBox.y + LGD_MARGIN + m_wxsizeMaxLabelsDims.GetHeight()/2 + n*(m_wxsizeMaxLabelsDims.GetHeight() + LGD_MARGIN));

		   dc.SetPen(*wxBLACK_PEN);
		   dc.DrawText(m_aEntries[n].GetLabel(),
					   m_wxrectBox.x + LGD_MARGIN + LGD_LINE_WIDTH + LGD_MARGIN,
					   m_wxrectBox.y + LGD_MARGIN + n*(m_wxsizeMaxLabelsDims.GetHeight() + LGD_MARGIN));
	   }
   }
}

AFLegend::AFLegend(const int nPosition)
  : m_nPosition(nPosition),
    m_wxrectBox(0,0,0,0),
    m_wxsizeMaxLabelsDims(0,0),
    m_wxfntFont(LEGEND_FONT_SIZE, wxSWISS, wxNORMAL, wxNORMAL),
	m_bShow(false)
{}


//----------------------------------------------------------------------------
// AFPlotBase implementation
//----------------------------------------------------------------------------

void AFPlotBase::Autorange(const double* pdbSerie, const size_t unLength, double& dbMin, double& dbMax, const bool bIsLog)
{
    // TODO Missing Log case!!!!
   if(bIsLog) return; // to be removed....
   
   dbMax = -1.0e-12, dbMin = 1.0e+12;
   for(size_t un = 0; un < unLength; un++)
   {
	   dbMax = (pdbSerie[un] < dbMax) ? dbMax : pdbSerie[un];
	   dbMin = (pdbSerie[un] > dbMin) ? dbMin : pdbSerie[un];
   }

   double dbRange = dbMax - dbMin;
   double dbDiv   = 0.000001;

   while(dbRange * dbDiv < 1) dbDiv *= 10;

   double dbStep  = 0.5 / dbDiv;
   dbMax = dbStep * ceil( dbMax/ dbStep );

   if(dbMin < 0)
       dbMin = dbStep * floor( dbMin/ dbStep );
}


void AFPlotBase::UpdatePlot(wxDC& dc, const wxSize& sz)
{
   // Cannot draw anything without axis (maybe an Assert fit better)!
   if(!m_pHorzAxis || !m_pVertAxis) return;

   // Set up grid, background & rulers
   m_nWidth  = sz.x;
   m_nHeight = sz.y;

   //Borders calculation
   m_nBBorder = m_pHorzAxis->GetHeight(dc);
   m_nTBorder = (m_bIsTBorderOn) ? m_nBBorder : ((m_Title.bShow) ? m_nBBorder : 0);
   m_nLBorder = m_pVertAxis->GetWidth(dc);
   m_nRBorder = (m_bIsRBorderOn) ?  m_nLBorder : 0;

#ifndef __WXOSX__
    m_wxcolCanvas = GetBackgroundColour();
#endif
    wxBrush brush(m_wxcolCanvas);
    wxPen   pen(m_wxcolBorders); 
   
   dc.SetBrush(brush);
   dc.SetPen(*wxTRANSPARENT_PEN);

   // Canvas plot background
   wxRect wxrectCanvas(0, 0, m_nWidth, m_nHeight);
   dc.DrawRectangle(wxrectCanvas);

   // Client area border
   m_wxrectClientArea.x      = m_nLBorder;
   m_wxrectClientArea.y      = m_nTBorder;
   m_wxrectClientArea.width  = m_nWidth  - (m_nLBorder + m_nRBorder);
   m_wxrectClientArea.height = m_nHeight - (m_nTBorder + m_nBBorder) + 1;

   brush.SetColour(m_wxcolBackground);
   dc.SetBrush(brush);
   dc.SetPen(pen);
   dc.DrawRectangle(m_wxrectClientArea);

   // Draw plot title
   if(m_Title.bShow)
   {
       dc.SetFont(m_Title.wxfntFont);
       dc.DrawText( m_Title.wxszLabel,
                    (m_nWidth - dc.GetTextExtent(m_Title.wxszLabel).GetWidth())/2,
                    m_nTBorder/2 - PLOT_TITLE_FONT_SIZE );
   }

   // Axis update, sizing and drawing
   UpdateHorizontalAxis();
   UpdateVerticalAxis();

   // Draw rulers
   m_pHorzAxis->SetBounds( dc,
		                   m_nLBorder,                // l
		                   m_nHeight - m_nBBorder,    // r
		                   m_nWidth - m_nRBorder,     // t
		                   m_nHeight,                 // b
		                   m_nHeight - (m_nTBorder + m_nBBorder) ); // gridlength

   m_pVertAxis->SetBounds( dc,
		                   0,                        // l
		                   m_nTBorder,               // r
		                   m_nLBorder,               // t
		                   m_nHeight - m_nBBorder,   // b
		                   m_nWidth - (m_nLBorder + m_nRBorder) ); // gridlength

   m_pHorzAxis->Draw(dc);
   m_pVertAxis->Draw(dc);

   // Finally it draws the plot!
   Draw(dc);

   // Draw Legend
   if(m_pLegend)
	   m_pLegend->Draw(dc, m_wxrectClientArea);

   if(m_bIsSelectionOn)
	   DrawSelectionRegion(dc);

   // Paint border again
   dc.SetBrush(*wxTRANSPARENT_BRUSH);
   dc.SetPen(pen);
   dc.DrawRectangle(m_wxrectClientArea);
}

void AFPlotBase::DrawSelectionRegion(wxDC& dc)
{
    if(m_wxrectSelection.width != 0 && m_wxrectSelection.height != 0)
    {
        dc.SetBrush(wxColour(255,255,0));
        dc.SetPen(*wxTRANSPARENT_PEN);
//       dc.SetLogicalFunction(wxEQUIV); // or wxOR_REVERSE [on mac these don't work]
        dc.SetLogicalFunction(wxXOR);
        dc.DrawRectangle(m_wxrectSelection);
        dc.SetLogicalFunction(wxCOPY); // restore default function.
    }
}

// --- handlers

void AFPlotBase::OnPaint(wxPaintEvent& evt)
{
   const wxSize sz = GetClientSize();
   wxAutoBufferedPaintDC adc(this);
   UpdatePlot(adc, sz);
}

void AFPlotBase::OnRightButtonClick(wxMouseEvent& evt)
{
   int nX = evt.GetX(), nY = evt.GetY();
   wxString wxszLabel(wxT("Set "));
   
   wxMenu menu;
    
   if(m_wxrectClientArea.Contains(nX, nY))
   {
       menu.Append(ID_COPY_BITMAP, wxT("&Copy\tCtrl+C"));
#if wxUSE_METAFILE
       menu.Append(ID_COPY_VECTORIAL, wxT("Copy as vectorial"));
#endif
       menu.AppendCheckItem(ID_SHOW_LEGEND_MCHK, wxT("Show legend"));
       menu.Check(ID_SHOW_LEGEND_MCHK, GetLegend()->IsShown());
       PopupMenu(&menu);
   }
   else if(m_pHorzAxis->GetRulerBounds().Contains(nX, nY) && m_bIsHorzRangeMutable)
   {
       wxszLabel << m_pHorzAxis->GetName() << wxT(" axis range");
	   menu.Append(ID_SET_X_AXIS_RANGE, wxszLabel);
	   menu.AppendCheckItem(ID_X_AUTORANGE_MCHK, wxT("Autorange"));
       menu.Check(ID_X_AUTORANGE_MCHK, m_bIsHorzAutorangeOn);
       PopupMenu(&menu);
   }
   else if(m_pVertAxis->GetRulerBounds().Contains(nX, nY) && m_bIsVertRangeMutable)
   {
	   wxszLabel << m_pVertAxis->GetName() << wxT(" axis range");
	   menu.Append(ID_SET_Y_AXIS_RANGE, wxszLabel);
	   menu.AppendCheckItem(ID_Y_AUTORANGE_MCHK, wxT("Autorange"));
	   menu.Check(ID_Y_AUTORANGE_MCHK, m_bIsVertAutorangeOn);
	   PopupMenu(&menu);
   }
}

#if wxUSE_METAFILE
void AFPlotBase::OnCopyVectorial(wxCommandEvent& evt)
{
    const wxString caption(_("wxPlot"));
    wxSize sz = GetClientSize();
    sz *= 2;

    wxMetafileDC dc(wxEmptyString, sz.x, sz.y, caption);
    if(dc.IsOk()) {

        UpdatePlot(dc, sz);
        wxMetafile *mf = dc.Close();
        if(!mf) {
            wxClipboardLocker locker;
            if(!locker)
                ::wxMessageBox(_("Cannot open the clipboard"), _("Error"), wxOK | wxICON_ERROR);
            else
                mf->SetClipboard();
            delete mf;
        }
    }
}
#endif

void AFPlotBase::OnCopyBitmap(wxCommandEvent& evt)
{
#ifdef __AUDEBUG__
   printf("Copy bitmap selected..."); fflush(stdout);
#endif
   wxSize sz = GetClientSize();
   sz *= 2;

   wxBitmap bmp(m_nWidth, m_nHeight);
   wxMemoryDC dc(bmp);

   if(dc.IsOk())
   {
       UpdatePlot(dc, sz);
       wxClipboardLocker locker;
       if(!locker)
       {
          ::wxMessageBox(wxT("Cannot open the clipboard"),
                         wxT("Error"),
                         wxOK | wxICON_ERROR);
       }
       else
       {
           if ( !wxTheClipboard->AddData(new wxBitmapDataObject(bmp)) )
              ::wxMessageBox(wxT("Can't copy data to the clipboard!"),
                             wxT("Error"),
                             wxOK | wxICON_ERROR);
       }
   }
}

void AFPlotBase::OnShowSetXAxisRange(wxCommandEvent& evt)
{
	SetAxisRangeDialog* pDlg;
	pDlg = new SetAxisRangeDialog(m_pwxwndParent, ID_SET_X_AXIS_DLG, m_pHorzAxis);
	if(pDlg->ShowModal())
	{
		SetHorzAxisAutorange(false);
		Refresh();
	}
	pDlg->Destroy();
}

void AFPlotBase::OnShowSetYAxisRange(wxCommandEvent& evt)
{
	SetAxisRangeDialog* pDlg;
	pDlg = new SetAxisRangeDialog(m_pwxwndParent, ID_SET_Y_AXIS_DLG, m_pVertAxis);
	if(pDlg->ShowModal())
	{
		SetVertAxisAutorange(false);
		Refresh();
	}
	pDlg->Destroy();
}

void AFPlotBase::OnXAutorangeMenuCheck(wxCommandEvent& evt)
{
    m_bIsHorzAutorangeOn = evt.IsChecked();
    Refresh();
}

void AFPlotBase::OnYAutorangeMenuCheck(wxCommandEvent& evt)
{
	m_bIsVertAutorangeOn = evt.IsChecked();
	Refresh();
}

void AFPlotBase::OnShowLegendMenuCheck(wxCommandEvent& evt)
{
    GetLegend()->Show(evt.IsChecked());
    Refresh();
}


void AFPlotBase::OnChar(wxKeyEvent &evt)
{
#if defined __WXOSX__    
    if((evt.GetKeyCode() == 99) && (evt.GetModifiers() == wxMOD_CMD))   // Command+C
#else        
    if(evt.GetKeyCode() == 3)   // Ctrl+C
#endif
    {
      wxCommandEvent cmd(wxEVT_COMMAND_MENU_SELECTED, ID_COPY_BITMAP);
	  OnCopyBitmap(cmd);
	}
}

// ----------------- Selection management handlers ------------------------
void AFPlotBase::OnMouseStartSelection(wxMouseEvent& evt)
{
    int nX = evt.GetX(), nY = evt.GetY();
    if(m_bIsHorzRangeMutable && m_pHorzAxis->GetRulerBounds().Contains(nX, nY))
    {
        m_bIsSelectionOn     = true;
        m_bIsHorzAutorangeOn = false;
        m_wxrectSelection.x  = nX;        
        m_wxrectSelection.y  = m_pHorzAxis->GetRulerBounds().y;        
        m_wxrectSelection.width  = 0;
        m_wxrectSelection.height = m_pHorzAxis->GetRulerBounds().height;

    }
    else if(m_bIsVertRangeMutable && m_pVertAxis->GetRulerBounds().Contains(nX, nY))
    {    
        m_bIsSelectionOn     = true;
        m_bIsVertAutorangeOn = false;
        m_wxrectSelection.x  = m_pVertAxis->GetRulerBounds().x;                
        m_wxrectSelection.y  = nY;
        m_wxrectSelection.width  = m_pVertAxis->GetRulerBounds().width;
        m_wxrectSelection.height = 0;
    }    
}

void AFPlotBase::OnMouseSelection(wxMouseEvent& evt)
{
    int nX = evt.GetX(), nY = evt.GetY();
    if(m_bIsSelectionOn && evt.LeftIsDown())
    {
        if(m_pHorzAxis->GetRulerBounds().Contains(nX, nY))
        {
    	    m_wxrectSelection.width = nX - m_wxrectSelection.x;
    	    Refresh();
        }
        else if(m_pVertAxis->GetRulerBounds().Contains(nX, nY))
        {
            m_wxrectSelection.height = nY - m_wxrectSelection.y;
    	    Refresh();

        }
    }
}

void AFPlotBase::OnMouseEndSelection(wxMouseEvent& evt)
{
    int nX = evt.GetX(), nY = evt.GetY();
    int nMin = 0, nMax = 0;
    if(m_bIsSelectionOn)
    {
        if(m_pHorzAxis->GetRulerBounds().Contains(nX, nY))
        {
            nMin = m_wxrectSelection.x - m_pHorzAxis->GetBounds().x;
            nMax = nMin + m_wxrectSelection.width;
            if(nMax < nMin)
            {
                int nTmp = nMin;
                nMin = nMax;
                nMax = nTmp;
            }
            m_pHorzAxis->SetPixelRange(nMin, nMax);
        }
        else if(m_pVertAxis->GetRulerBounds().Contains(nX, nY))
        {
            nMax = m_wxrectSelection.y - m_pVertAxis->GetBounds().y;
            nMin = nMax + m_wxrectSelection.height;
            
            nMax = m_pVertAxis->GetBounds().height - nMax; // values flipping
            nMin = m_pVertAxis->GetBounds().height - nMin;
            
            if(nMax < nMin)
            {
                int nTmp = nMin;
                nMin = nMax;
                nMax = nTmp;
            }
            m_pVertAxis->SetPixelRange(nMin, nMax);
        }
 
        m_bIsSelectionOn = false;
        Refresh();
    }
}

AFLegend* AFPlotBase::GetLegend ()
{
	if(!m_pLegend)
    {
	    m_pLegend = new AFLegend();
	}
	return m_pLegend;
}

void AFPlotBase::ShowLegend(const bool bValue)
{
	if(!m_pLegend && !bValue) return;

	if(!m_pLegend)
	{
		m_pLegend = new AFLegend();
	}
	m_pLegend->Show(bValue);
}

// --- ctors
AFPlotBase::AFPlotBase( wxWindow *parent,   wxWindowID id,
                        const wxPoint& pos, const wxSize& size,
                        const long style )
  : wxControl(parent, id, pos, size, style),
    m_pwxwndParent(parent),

    //m_wxcolCanvas(wxT("#EDEDED")),     // default canvas colour...on Mac!
    m_wxcolCanvas(::AuroraGetCanvasColour()),
    m_wxcolBackground(wxT("#FFFFFF")), // default plot background is white
    m_wxcolBorders(wxT("#000000")),    // default borders are black

    m_pHorzAxis(0), m_pVertAxis(0),

    m_pLegend(0),

    m_nTBorder(0), m_nBBorder(0),
    m_nLBorder(0), m_nRBorder(0),
    m_bIsTBorderOn(true), m_bIsRBorderOn(true),

    m_bIsHorzAutorangeOn(true),    m_bIsVertAutorangeOn(true),
    m_bIsHorzRangeMutable(true),   m_bIsVertRangeMutable(true),
                             
    m_bIsSelectionOn(false)

{
   SetBackgroundStyle(wxBG_STYLE_CUSTOM);
   SetInitialSize(size);

   m_nWidth  = size.x;
   m_nHeight = size.y;

   m_Title.bShow     = false;
   m_Title.wxszLabel = wxT("Plot Title");
   m_Title.wxfntFont.SetPointSize(PLOT_TITLE_FONT_SIZE);
   m_Title.wxfntFont.SetFamily(wxSWISS);
   m_Title.wxfntFont.SetStyle(wxNORMAL);
   m_Title.wxfntFont.SetWeight(wxNORMAL);

   Connect(wxEVT_PAINT,      wxPaintEventHandler(AFPlotBase::OnPaint),               NULL, this);
   Connect(wxEVT_CHAR,       wxCharEventHandler(AFPlotBase::OnChar),                 NULL, this);
   Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(AFPlotBase::OnRightButtonClick),    NULL, this);
   Connect(wxEVT_LEFT_DOWN,  wxMouseEventHandler(AFPlotBase::OnMouseStartSelection), NULL, this);
   Connect(wxEVT_MOTION,     wxMouseEventHandler(AFPlotBase::OnMouseSelection),      NULL, this);
   Connect(wxEVT_LEFT_UP,    wxMouseEventHandler(AFPlotBase::OnMouseEndSelection),   NULL, this);

   Connect(ID_COPY_BITMAP,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnCopyBitmap), NULL, this );
 #if wxUSE_METAFILE
   Connect(ID_COPY_VECTORIAL,   wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnCopyVectorial), NULL, this );
 #endif

   Connect(ID_SET_X_AXIS_RANGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnShowSetXAxisRange), NULL, this );
   Connect(ID_SET_Y_AXIS_RANGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnShowSetYAxisRange), NULL, this );
   Connect(ID_X_AUTORANGE_MCHK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnXAutorangeMenuCheck), NULL, this );
   Connect(ID_Y_AUTORANGE_MCHK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnYAutorangeMenuCheck), NULL, this );
   Connect(ID_SHOW_LEGEND_MCHK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnShowLegendMenuCheck), NULL, this );
}

AFPlotBase::~AFPlotBase()
{
   if(m_pHorzAxis) delete m_pHorzAxis;
   if(m_pVertAxis) delete m_pVertAxis;
   if(m_pLegend)   delete m_pLegend;

   Disconnect(wxEVT_PAINT,      wxPaintEventHandler(AFPlotBase::OnPaint),               NULL, this);
   Disconnect(wxEVT_CHAR,       wxCharEventHandler(AFPlotBase::OnChar),                 NULL, this);
   Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(AFPlotBase::OnRightButtonClick),    NULL, this);
   Disconnect(wxEVT_LEFT_DOWN,  wxMouseEventHandler(AFPlotBase::OnMouseStartSelection), NULL, this);
   Disconnect(wxEVT_MOTION,     wxMouseEventHandler(AFPlotBase::OnMouseSelection),      NULL, this);
   Disconnect(wxEVT_LEFT_UP,    wxMouseEventHandler(AFPlotBase::OnMouseEndSelection),   NULL, this);

   Disconnect(ID_COPY_BITMAP,      wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnCopyBitmap), NULL, this );
#if wxUSE_METAFILE
   Disconnect(ID_COPY_VECTORIAL,   wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnCopyVectorial), NULL, this );
#endif
   Disconnect(ID_SET_X_AXIS_RANGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnShowSetXAxisRange), NULL, this );
   Disconnect(ID_SET_Y_AXIS_RANGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnShowSetYAxisRange), NULL, this );
   Disconnect(ID_X_AUTORANGE_MCHK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnXAutorangeMenuCheck), NULL, this );
   Disconnect(ID_Y_AUTORANGE_MCHK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnYAutorangeMenuCheck), NULL, this );
   Disconnect(ID_SHOW_LEGEND_MCHK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AFPlotBase::OnShowLegendMenuCheck), NULL, this );
}


//----------------------------------------------------------------------------
// SetAxisRangeDialog implementation
//----------------------------------------------------------------------------
void SetAxisRangeDialog::OnCancel( wxCommandEvent& event )
{
	EndModal(false);
}

void SetAxisRangeDialog::OnOk( wxCommandEvent& event )
{
    m_dbMin = ::TextPtrToDouble(m_pwxtcMin);
    m_dbMax = ::TextPtrToDouble(m_pwxtcMax);

	if(m_dbMax <= m_dbMin)
	{
	    ::wxMessageBox(wxT("Invalid bounds."), wxT("Error"), wxOK | wxICON_ERROR);
	    EndModal(false);
	}
	else
	{
        m_pAxis->SetRange(m_dbMin, m_dbMax);
		EndModal(true);
	}
}

SetAxisRangeDialog::SetAxisRangeDialog(wxWindow* pParent, wxWindowID id, AFAxisBase* pAxis,
                                       const wxString& title, 
                                       const wxPoint& pos, 
                                       const wxSize& size, 
                                       long style)
  : wxDialog( pParent, id, title, pos, size, style ),
    m_pAxis(pAxis),
    m_nId(id)
{
    	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_pwxpnlUpper = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_pwxstMinLbl = new wxStaticText( m_pwxpnlUpper, wxID_ANY, wxT("Min:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstMinLbl->Wrap( -1 );
	fgSizer1->Add( m_pwxstMinLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcMin = new wxTextCtrl( m_pwxpnlUpper, ID_MIN_TC, wxT("-100.000000"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	m_pwxtcMin->SetMinSize( wxSize( 100,-1 ) );
	
	fgSizer1->Add( m_pwxtcMin, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstMinMu = new wxStaticText( m_pwxpnlUpper, ID_MIN_MU_ST, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstMinMu->Wrap( -1 );
	m_pwxstMinMu->SetMinSize( wxSize( 30,-1 ) );
	
	fgSizer1->Add( m_pwxstMinMu, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstMaxLbl = new wxStaticText( m_pwxpnlUpper, wxID_ANY, wxT("Max:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstMaxLbl->Wrap( -1 );
	fgSizer1->Add( m_pwxstMaxLbl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxtcMax = new wxTextCtrl( m_pwxpnlUpper, wxID_ANY, wxT("100.000000"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	m_pwxtcMax->SetMinSize( wxSize( 100,-1 ) );
	
	fgSizer1->Add( m_pwxtcMax, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxstMaxMu = new wxStaticText( m_pwxpnlUpper, ID_MAX_MU_ST, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxstMaxMu->Wrap( -1 );
	fgSizer1->Add( m_pwxstMaxMu, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxpnlUpper->SetSizer( fgSizer1 );
	m_pwxpnlUpper->Layout();
	fgSizer1->Fit( m_pwxpnlUpper );
	bSizer13->Add( m_pwxpnlUpper, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer13->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_pwxpnlLower = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pwxbtnCancel = new wxButton( m_pwxpnlLower, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_pwxbtnCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxbtnOk = new wxButton( m_pwxpnlLower, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pwxbtnOk->SetDefault(); 
	bSizer14->Add( m_pwxbtnOk, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pwxpnlLower->SetSizer( bSizer14 );
	m_pwxpnlLower->Layout();
	bSizer14->Fit( m_pwxpnlLower );
	bSizer13->Add( m_pwxpnlLower, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer13 );
	this->Layout();
	bSizer13->Fit( this );
	
   	// Connect Events
	m_pwxbtnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetAxisRangeDialog::OnCancel ), NULL, this );
	m_pwxbtnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetAxisRangeDialog::OnOk ), NULL, this );

    // My own setup
    wxString wxszTitle = wxT("Set ");    
    wxszTitle << m_pAxis->GetName() << wxT(" axis range");
    SetTitle(wxszTitle);

	m_pAxis->GetRange(m_dbMin, m_dbMax);

    m_pwxtcMin->SetValue(wxString::Format(wxT("%f"), m_dbMin));
    m_pwxtcMax->SetValue(wxString::Format(wxT("%f"), m_dbMax));

    m_pwxstMinMu->SetLabel(m_pAxis->GetMeasureUnit());
    m_pwxstMaxMu->SetLabel(m_pAxis->GetMeasureUnit());
    
    CentreOnParent();
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
