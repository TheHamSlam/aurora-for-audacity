///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dialogs__
#define __dialogs__

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
#include <wx/statbox.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include "plot.h"
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_LOGO_PANEL 1000
#define ID_TRACK_SELECT_CHOICE 1001
#define ID_PEAK_BLOCK_SIZE_TC 1002
#define ID_PEAK_BLOCK_TYPE_CHOICE 1003
#define ID_ANALYZE_BTN 1004
#define ID_TIME_PLOT 1005
#define ID_SPECTRUM_PLOT 1006
#define ID_ACORR_PLOT 1007

///////////////////////////////////////////////////////////////////////////////
/// Class PeakVueSetupDlg
///////////////////////////////////////////////////////////////////////////////
class PeakVueSetupDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline1;
		wxPanel* m_pwxpnlMain;
		wxStaticText* m_pwxstInSelect;
		wxChoice* m_pwxchTrack;
		wxStaticText* m_pwxstRateLabel;
		wxStaticText* m_pwxstRate;
		wxStaticText* m_pwxstRateHz;
		wxStaticText* m_pwxstLengthLabel;
		wxStaticText* m_pwxstLength;
		wxStaticText* m_pwxstLengthSec;
		wxStaticText* m_pwxstPeakBlLabel;
		wxTextCtrl* m_pwxtcPeakBlockSize;
		wxStaticText* m_pwxstPeakBlMs;
		wxStaticText* m_pwxstPeakTypeLabel;
		wxChoice* m_pwxchPeakType;
		wxStaticText* m_pwxstSpace1;
		wxStaticText* m_pwxstFftSizeLabel;
		wxTextCtrl* m_pwxtcFftSize;
		wxStaticText* m_pwxstSmpl;
		wxStaticText* m_pwxstWinLabel;
		wxChoice* m_pwxchWinType;
		wxButton* m_pwxbtnAnalyze;
		wxSplitterWindow* m_pwxUpperSplitter;
		wxPanel* m_pwxUpperPlotPanel;
		wxScrolledWindow* m_pUpperPlotScroller;
		PVRealDataPlot* m_pTimePlot;
		wxPanel* m_panel5;
		wxSplitterWindow* m_pwxLowerSplitter;
		wxPanel* m_pwxMiddlePlotPanel;
		wxScrolledWindow* m_pMiddlePlotScroller;
		PVSpectrumMagnitudePlot* m_pSpectrumPlot;
		wxPanel* m_pwxLowerPlotPanel;
		wxScrolledWindow* m_pLowerPlotScroller;
		PVRealDataPlot* m_pAcorrPlot;
		wxStaticLine* m_staticline2;
		wxPanel* m_pwxpnlButtons;
		wxButton* m_pwxbtnHelp;
		
		wxButton* m_pwxbtnCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnAnalyze( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCloseBtn( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		PeakVueSetupDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aurora PeakVue Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~PeakVueSetupDlg();
		void m_pwxUpperSplitterOnIdle( wxIdleEvent& )
		{
		m_pwxUpperSplitter->SetSashPosition( 0 );
		m_pwxUpperSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( PeakVueSetupDlg::m_pwxUpperSplitterOnIdle ), NULL, this );
		}
		
		void m_pwxLowerSplitterOnIdle( wxIdleEvent& )
		{
		m_pwxLowerSplitter->SetSashPosition( 0 );
		m_pwxLowerSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( PeakVueSetupDlg::m_pwxLowerSplitterOnIdle ), NULL, this );
		}
		
	
};

#endif //__dialogs__
