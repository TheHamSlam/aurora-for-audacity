///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dialogs__
#define __dialogs__

class AFNotebook;

#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include "plot.h"
#include <wx/scrolwin.h>
#include <wx/splitter.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class THADlg
///////////////////////////////////////////////////////////////////////////////
class THADlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_SETUP_PAGE = 1000,
			ID_FULLSCALE_GRID,
			ID_RDC_CHECK,
			ID_CALIBRATION_PAGE,
			ID_CALIBRATION_GRID,
			ID_CALIB_APPLY_TO_ALL,
			ID_CALIBRATE_BTN,
		};
		
		wxNotebook* m_pNotebook;
		wxPanel* m_pwxpnlSetup;
		wxGrid* m_pwxgrdFullscales;
		wxCheckBox* m_pwxcbRemoveDC;
		wxPanel* m_pwxpnlCalibration;
		wxGrid* m_pwxgrdCalibration;
		wxCheckBox* m_pwxcbCh1ForAll;
		wxButton* m_pwxbtnCalibrate;
		wxStaticLine* m_staticline2;
		wxPanel* m_panel4;
		wxButton* m_pwxbtnHelp;
		
		wxButton* m_pwxbtnCancel;
		wxButton* m_pwxbtnAnalyze;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnFullscaleGridContentChanged( wxGridEvent& event ){ event.Skip(); }
		virtual void OnRemoveDCCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCalibrationGridContentChanged( wxGridEvent& event ){ event.Skip(); }
		virtual void OnApplyToAllCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCalibrate( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		THADlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Time History Analysis"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~THADlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class THAShowDlg
///////////////////////////////////////////////////////////////////////////////
class THAShowDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_DISPLAY_CHOICE = 1000,
			ID_PLOT,
			ID_GRID_PANEL,
			ID_PARAM_GRID,
			ID_ADD_TRACKS_BTN,
		};
		
		wxSplitterWindow* mSplitter;
		wxPanel* mLeftPanel;
		wxStaticText* m_pwxstPlotType;
		wxChoice* m_choice1;
		wxPanel* m_pwxpnlPlot;
		wxScrolledWindow* mPlotScroller;
		THAPlot *m_pPlot;
		wxPanel* mRightPanel;
		wxPanel* mGridPanel;
		wxGrid* m_pwxgrdResults;
		wxStaticLine* m_staticline1;
		wxPanel* mBottomPanel;
		wxButton* m_button8;
		
		wxButton* m_pwxbtnAddTracks;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDlg( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnSelectDisplay( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnGridCellRightClick( wxGridEvent& event ){ event.Skip(); }
		virtual void OnTogglePlot( wxGridEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAddTracksBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		THAShowDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Time History Analyzer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxFULL_REPAINT_ON_RESIZE );
		~THAShowDlg();
		void mSplitterOnIdle( wxIdleEvent& )
		{
		mSplitter->SetSashPosition( 0 );
		mSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( THAShowDlg::mSplitterOnIdle ), NULL, this );
		}
		
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class THADialog
///////////////////////////////////////////////////////////////////////////////
class THADialog : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_LOGO_PANEL = 1000,
			ID_HORZ_SPLITTER,
			ID_SETUP_NOTEBOOK,
			ID_SETUP_PAGE,
			ID_FULLSCALE_GRID,
			ID_ANALYZE_BTN,
			ID_RDC_CHECK,
			ID_CALIBRATION_PAGE,
			ID_CALIBRATION_GRID,
			ID_CALIBRATE_BTN,
			ID_CALIB_APPLY_TO_ALL,
			ID_DISPLAY_CHOICE,
			ID_PLOT,
			ID_GRID_PANEL,
			ID_PARAM_GRID,
			ID_ADD_TRACKS_BTN,
		};
		
		wxPanel* m_pwxpnlLogo;
		wxStaticLine* m_staticline4;
		wxSplitterWindow* m_pHorzSplitter;
		wxPanel* m_pwxpnlUpper;
		AFNotebook* m_pNotebook;
		wxPanel* m_pwxpnlSetup;
		wxGrid* m_pwxgrdFullscales;
		wxButton* m_pwxbtnAnalyze;
		
		wxCheckBox* m_pwxcbRemoveDC;
		wxPanel* m_pwxpnlCalibration;
		wxGrid* m_pwxgrdCalibration;
		wxButton* m_pwxbtnCalibrate;
		
		wxCheckBox* m_pwxcbCh1ForAll;
		wxPanel* m_pwxpnlLower;
		wxSplitterWindow* m_pVertSplitter;
		wxPanel* m_pwxpnlLeft;
		wxScrolledWindow* m_pwxplotScroller;
		wxStaticText* m_pwxstPlotType;
		wxChoice* m_pwxchoicePlotType;
		wxPanel* m_pwxpnlPlot;
		THAPlot *m_pPlot;
		wxPanel* m_pwxpnlRight;
		wxPanel* mGridPanel;
		wxGrid* m_pwxgrdResults;
		wxStaticLine* m_staticline3;
		wxPanel* mBottomPanel;
		wxButton* m_button8;
		
		wxButton* m_pwxbtnAddTracks;
		wxButton* mOkBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnFullscaleGridContentChanged( wxGridEvent& event ){ event.Skip(); }
		virtual void OnAnalyze( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRemoveDCCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCalibrationGridContentChanged( wxGridEvent& event ){ event.Skip(); }
		virtual void OnCalibrate( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnApplyToAllCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelectDisplay( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnGridCellRightClick( wxGridEvent& event ){ event.Skip(); }
		virtual void OnTogglePlot( wxGridEvent& event ){ event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAddTracksBtn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		THADialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Time History Analyzer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~THADialog();
		void m_pHorzSplitterOnIdle( wxIdleEvent& )
		{
		m_pHorzSplitter->SetSashPosition( 200 );
		m_pHorzSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( THADialog::m_pHorzSplitterOnIdle ), NULL, this );
		}
		
		void m_pVertSplitterOnIdle( wxIdleEvent& )
		{
		m_pVertSplitter->SetSashPosition( 0 );
		m_pVertSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( THADialog::m_pVertSplitterOnIdle ), NULL, this );
		}
		
	
};

#endif //__dialogs__
