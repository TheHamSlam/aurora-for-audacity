/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  spectfrm.h

  Simone Campanini

**********************************************************************/

#ifndef __spectrumfrm__
#define __spectrumfrm__

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/string.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/frame.h>

#include <wx/wxfreechartdefs.h>
#include <wx/chartpanel.h>
#include <wx/bars/barplot.h>

#include "sti.h"

///////////////////////////////////////////////////////////////////////////

#define ID_SPECTRUM_FRAME 10000
#define ID_SPECTRUM_GRID  10001
#define ID_PLOT_NB        10002
#define ID_SPECTRUM_PLOT_LEFT   10003
#define ID_SPECTRUM_PLOT_RIGHT  10004


//----------------------------------------------------------------------------
// STISpectrumGridCellColoredRectRenderer
//----------------------------------------------------------------------------
class STISpectrumGridCellColoredRectRenderer : public wxGridCellStringRenderer
{
private:
   void ChooseBrush(wxBrush &brush, const int nCh);

public:
   virtual void Draw(wxGrid &grid, wxGridCellAttr& attr, wxDC &dc,
	                 const wxRect& rect, int nRow, int nCol, bool bIsSelected);
};

///////////////////////////////////////////////////////////////////////////////
/// Class STISpectrumFrame
///////////////////////////////////////////////////////////////////////////////
class STISpectrumFrame : public wxFrame 
{
	private:
        AuroraSTI*  m_pAs;
        bool        m_bIsStereo;
        int         m_nCurrentChnl;

        wxChartPanel* m_pwxfcSpectrumPlot [2];
		wxGrid*       m_pwxgridSpectrumTable;
        Chart*        m_pwxChart [2];
        
        wxPanel*      m_pwxpnlMain;
        wxNotebook*   m_pwxnbSpectrumPlot;

// private methods
        void     FillTable();
        BarPlot* UpdatePlot(const int nChnl);
        
        void OnClose( wxCommandEvent& event );
        void OnPageChange( wxNotebookEvent& event );
		void OnLevelTableLabelClick( wxGridEvent& event );
		
	public:
        void UpdateChart();
        
		STISpectrumFrame( wxWindow* parent, 
                          AuroraSTI* pAs,
                          const bool bIsStereo = false,
                          wxWindowID id = ID_SPECTRUM_FRAME, 
                          const wxString& title = wxT("Octave Band Spectrum"), 
                          const wxPoint& pos = wxDefaultPosition,
                          const wxSize& size = wxSize( -1,-1 ),
                          long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxFRAME_FLOAT_ON_PARENT|wxTAB_TRAVERSAL );
   
		~STISpectrumFrame();
};

#endif //__spectrumfrm__
