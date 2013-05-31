/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  gui.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_STI_GUI_H__
#define __AURORA_STI_GUI_H__

#include <commdefs.h>
#include <afconfig.h>

#include "dialogs.h"
#include "exports.h"
#include "module.h"
#include "plot.h"
#include "spectrum.h"
#include "sti.h"

//----------------------------------------------------------------------------
// STISetupDialog
//----------------------------------------------------------------------------
#define ID_SPL_COPY_SELECTION_MENU 10020

class STISetupDialog : public STISetupDlg
{
private:
    AuroraSTI*        m_pAs;
    EffectAuroraSTI*  m_pEas;   

    STISpectrumDialog* m_pSpectrumDlg;
    
    /*wxArrayString     m_wxastrTrackNames;
    
    int   m_anCalibrationTracksIdx [2],
          m_anNoiseTracksIdx       [2],
          m_anSignalTracksIdx      [2],
          m_anIrTracksIdx          [2];*/

    wxMenu*            m_pwxSPLTableContextMenu;
    STISpectrumExports m_ExportsMgr;
    
    wxStaticBitmap *m_pwxbmpAuroraLogo,
                   *m_pwxbmpLogo;

    AFConfig* m_pCfg;

    void InitTrackChoice(wxChoice* pwxChoice);
    void FillSigNoiseGrid();
    
protected:    
    // Handlers for STISetupDlg events.
    void OnCloseDialog( wxCloseEvent& event ) { EndModal(false); }
    void OnLeftFullscaleText( wxCommandEvent& event );
    void OnRightFullscaleText( wxCommandEvent& event );
    void OnCalibLeftChoice( wxCommandEvent& event );
    void OnCalibRefLeftText( wxCommandEvent& event );
    void OnCalibRightChoice( wxCommandEvent& event );
    void OnCalibRefRightText( wxCommandEvent& event );
    void OnDoFullscaleCalibration( wxCommandEvent& event );
    void OnNoiseLeftChoice( wxCommandEvent& event );
    void OnNoiseRightChoice( wxCommandEvent& event );
    void OnSignalLeftChoice( wxCommandEvent& event );
    void OnSignalRightChoice( wxCommandEvent& event );
    void OnSignalRadio( wxCommandEvent& event );
    void OnSignalPlusNoiseRadio( wxCommandEvent& event );
    void OnSplTableRightClick( wxGridEvent& event ); //***
    void OnLoadSplValues( wxCommandEvent& event );
    void OnSaveSplValues( wxCommandEvent& event );
    void OnComputeSNRatio( wxCommandEvent& event );
    void OnLeftIRChoice( wxCommandEvent& event );
    void OnRightIRChoice( wxCommandEvent& event );
    void OnFatText( wxCommandEvent& event );
    void OnHelp( wxCommandEvent& event );
    void OnCancel( wxCommandEvent& event )  { EndModal(false); }
    void OnComputeSTI( wxCommandEvent& event )  { EndModal(true); }
    
    void OnSplTableKeyPress( wxKeyEvent& event );
    void OnSplTableCopySelection(wxCommandEvent & event);

public:
    /** Constructor */
    STISetupDialog( wxWindow* parent, 
                    AuroraSTI* pAs,
                    EffectAuroraSTI* pEas,
                    AFConfig* pCfg);
    ~STISetupDialog();
};

//----------------------------------------------------------------------------
// STIShowDialog
//----------------------------------------------------------------------------
#define ID_PLOT   10010
#define ID_MTF_COPY_SELECTION_MENU 10020
#define ID_STI_COPY_SELECTION_MENU 10021

class STIShowDialog : public STIShowDlg
{
private:
    wxPanel*    m_pwxpnlPlotPage;
    STIPlot*    m_pPlot;
    
    AuroraSTI*  m_pAs;
    bool        m_bIsStereo;
    
    int m_nCurrentChannel;

    wxMenu*         m_pwxMtfTableContextMenu;
    wxMenu*         m_pwxSTITableContextMenu;    
    STIShowExports  m_ExportsMgr;

    wxStaticBitmap *m_pwxbmpAuroraLogo,
                   *m_pwxbmpLogo;

    void UpdateTables();
    void UpdatePlot();
    
protected:
    // Handlers for STIShowDlg events.
    void OnCloseDialog( wxCloseEvent& event ) { EndModal(false); }
    void OnMtfTableRigtClick( wxGridEvent& event );
    void OnMtfTableKeyPress( wxKeyEvent& event );
    void OnSTITableRightClick( wxGridEvent& event );
    void OnSTITableKeyPress( wxKeyEvent& event );
    void OnLeftRadio( wxCommandEvent& event );
    void OnRightRadio( wxCommandEvent& event );
    void OnSnCorrectionCheck( wxCommandEvent& event );
    void OnMaskCorrectionCheck( wxCommandEvent& event );
    void OnSave( wxCommandEvent& event );
    void OnHelp( wxCommandEvent& event );
    void OnOk( wxCommandEvent& event );

    // Context menu handlers
    void OnMtfTableCopySelection(wxCommandEvent & event);
    void OnSTITableCopySelection(wxCommandEvent & event);   
    
public:
    /** Constructor */
    STIShowDialog( wxWindow* parent, AuroraSTI* pAs, const bool bIsStereo = false);
    ~STIShowDialog();
};

#endif // __AURORA_STI_GUI__

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
