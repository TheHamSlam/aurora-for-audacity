/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  gui.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_XFUNCTIONS_GUI_H__
#define __AURORA_XFUNCTIONS_GUI_H__

#include <commdefs.h>

#include "xfn.h"
#include "dialogs.h"
#include "exports.h"
#include "module.h"
#include "plot.h"

//----------------------------------------------------------------------------
// XFunctionsDialog
//----------------------------------------------------------------------------
class XFunctionsDialog : public XFunctionsDlg
{
  private:
    XFunctions *m_pXf;
    
    wxArrayString mEquationBitmapPtr;

    wxStaticBitmap *m_pwxbmpAuroraLogo,
                   *m_pwxbmpLogo;

    //void   SetOutputLabels(const int sel)
    
    void BuildFftChoice(const int nDefaultSel = 0);
    void UpdateLag();
    
  protected:
    // Handlers for XFunctionsDlg events.
    void OnCloseEvent( wxCloseEvent& event);
    void OnFftSizeChoice( wxCommandEvent& event );
    void OnWindowChoice( wxCommandEvent& event );
    void OnXFunctionChoice( wxCommandEvent& event);
    void OnSWTubeCheck( wxCommandEvent& event );
    void OnFreeFieldCheck( wxCommandEvent& event );
    void OnSoundSpeedText( wxCommandEvent& event );
    void OnProbeDistanceText( wxCommandEvent& event );
    void OnFmaxText( wxCommandEvent& event );
    void OnEnableFollowingFilterCheck( wxCommandEvent& event );
    void OnFollowLeftRadio( wxCommandEvent& event );
    void OnFollowRightRadio( wxCommandEvent& event );
    void OnBandwidthText( wxCommandEvent& event );
    void OnNormalizeLeftChannelCheck( wxCommandEvent& event );
    void OnHilbertCheck( wxCommandEvent& event );
    void OnShiftToHalfWindowCheck( wxCommandEvent& event );
    void OnTimeReversalCheck( wxCommandEvent& event );
    void OnCoherenceCheck( wxCommandEvent& event );
    void OnSaveMultispectrumCheck( wxCommandEvent& event );
    void OnTriggerLevelText( wxCommandEvent& event );
    void OnDiracPulseCheck( wxCommandEvent& event );
    void OnHelp( wxCommandEvent& event );
    void OnOk( wxCommandEvent& event );
    void OnCancel( wxCommandEvent& event );
    
public:
    /** Constructor */
    XFunctionsDialog(wxWindow* pParent, XFunctions* pXf);
};

//----------------------------------------------------------------------------
// XFunctionsShowDialog
//----------------------------------------------------------------------------
/** Implementing XFunctionsShowDlg */
class XFunctionsShowDialog : public XFunctionsShowDlg
{
  private:
    XFunctions* m_pXf;
    XFunctionsExports mExportData;
    
    wxStaticBitmap *m_pwxbmpAuroraLogo,
                   *m_pwxbmpLogo;

    TArrayOfXFSpectrumDataSerie m_aDataSeries;

    AFConfig* m_pCfg;

   void AddPlotDataSeries(XFPlot* pPlot, const wxColour& wxcolLine);
   void UpdatePlotData(XFPlot* pPlot, wxString& wxszPlotName);
   void GetChoiceItems(wxArrayString& awxszList);
   void BuildPlotChoice(wxChoice* pwxchoiceItem, const int nDefaultSel = 0);
   void SetPlotLagAxis(XFPlot* pPlot);
   void SetFrequencyRange(XFPlot* pPlot, const int nChoice, const bool bIsLog);
   
protected:
   // Handlers for XFunctionsShowDlg events.
   void OnCloseEvent( wxCloseEvent& event);
   void OnFrequencyRangeChoice( wxCommandEvent& event );
   void OnLinearScaleCheck( wxCommandEvent& event );
   void OnSaveToTimeDelayCheck( wxCommandEvent& event );
   void OnExportAllSpectrumsCheck( wxCommandEvent& event );
   void OnSaveSpectrumBtn( wxCommandEvent& event );
   void OnCopySpectrumBtn( wxCommandEvent& event );
   void OnExportWaveformsCheck( wxCommandEvent& event );
   void OnFirstPlotChoice( wxCommandEvent& event );
   void OnSecondPlotChoice( wxCommandEvent& event );
   void OnHelp( wxCommandEvent& event );
   void OnClose( wxCommandEvent& event );

   void StoreGeometry();
   void RestoreGeometry();

public:
   /** Constructor */
   XFunctionsShowDialog(wxWindow* pParent, XFunctions* pXf, AFConfig* pCfg);
};

#endif // __AURORA_XFUNCTIONS_GUI_H__

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
