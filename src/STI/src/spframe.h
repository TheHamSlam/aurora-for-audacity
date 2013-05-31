///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __spframe__
#define __spframe__

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include "plot.h"
#include <wx/grid.h>
#include <wx/splitter.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_SPECTRUM_DLG 1000
#define ID_SPECTRUM_LOGO_PANEL 1001
#define ID_MAIN_SPLITTER 1002
#define ID_LEFT_PLOT 1003
#define ID_SPECTRUM_GRID 1004

///////////////////////////////////////////////////////////////////////////////
/// Class STISpectrumDlg
///////////////////////////////////////////////////////////////////////////////
class STISpectrumDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline1;
		wxPanel* m_pwxpnlTop;
		wxStaticText* m_pwxstChnlSel;
		wxChoice* m_pwxchoiceChannel;
		wxSplitterWindow* m_pSplitter;
		wxPanel* m_pwxpnlUpper;
		OctaveBandsPlot* m_pSpectrumPlot;
		wxPanel* m_pwxpnlLower;
		wxPanel* m_panel4;
		wxGrid* m_pwxgridSpectrumTable;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChannelSelect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLevelTableLabelClick( wxGridEvent& event ){ event.Skip(); }
		
	
	public:
		STISpectrumDlg( wxWindow* parent, wxWindowID id = ID_SPECTRUM_DLG, const wxString& title = wxT("Octave Band Analysis"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 900,800 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~STISpectrumDlg();
		void m_pSplitterOnIdle( wxIdleEvent& )
		{
		m_pSplitter->SetSashPosition( 560 );
		m_pSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( STISpectrumDlg::m_pSplitterOnIdle ), NULL, this );
		}
		
	
};

#endif //__spframe__
