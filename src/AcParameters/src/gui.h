/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters

  gui.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_ACPARAM_GUI__
#define __AURORA_ACPARAM_GUI__

#include <wxcmn.h>

#include <wx/clipbrd.h>
#include <wx/statline.h>
#include <wx/textfile.h>

//----------------------------------------------------------------------------
// AcParametersDialog
//
/// \brief The Acoustical Parameters setup dialog.
//
/// From this dialog the user can set the module
/// parameters and options.
//----------------------------------------------------------------------------
class AcParametersDialog: public AcParDlg 
{ 
   private:
	  /// Pointer to Acoustical Parameter module class
	  EffectAcParameters* m_pEap;

      /// Pointer to Acoustical Parameter calculation class
      AcParameters* m_pAp;

      ///@{
      /// The module logos (Aurora and Acoustical Parameters)
      wxStaticBitmap *m_pwxbmpAuroraLogo,
                     *m_pwxbmpLogo;
      ///@}

      /// Pointer to Acoustical Parameters data export manager
      AcParametersExports*  m_pExportData;

   protected:
      ///@{
      /// Dialog events handlers
      void OnCloseDialog      (wxCloseEvent& event);

      // --- Checkbox events ---
      void OnNoiseCorrCheck(wxCommandEvent & event);
      void OnEDTCheck(wxCommandEvent & event);
      void OnComputeStageParamCheck(wxCommandEvent & event);
      void OnAvgModeCheck(wxCommandEvent & event);
      void OnAppendResultsToFile(wxCommandEvent & event);

      // --- TextCtl events ---
      void OnEditRevTimeMinExtreme(wxCommandEvent & event);
      void OnEditRevTimeMaxExtreme(wxCommandEvent & event);
      void OnEditDirSoundTrigValue(wxCommandEvent & event);
      void OnEditPeakSPLValue(wxCommandEvent & event);
      void OnEditProbeMicDist(wxCommandEvent & event);
      void OnEditCValue(wxCommandEvent & event);
      void OnEditAppendFileName(wxCommandEvent & event) ;

      // --- Radiobuttons event ---
      void OnOctaveBandsRadio( wxCommandEvent& event );
      void OnThirdOctaveBandsRadio( wxCommandEvent& event );
      void OnOmniMicClick(wxCommandEvent & event);
      void OnSoundfieldClick(wxCommandEvent & event);
      void OnPUProbeClick(wxCommandEvent & event);
      void OnIntensityProbeClick(wxCommandEvent & event);
      void OnBinauralClick(wxCommandEvent & event);
      void On4ChModeOmniRadio( wxCommandEvent& event );
      void On4ChModeSoundfieldWXYZRadio( wxCommandEvent& event );
      void On4ChModeSoundfieldWYXZRadio( wxCommandEvent& event );
        
      // --- Choice events ---
      void OnIACCChoice(wxCommandEvent & event);

      // --- Buttons events
      void OnOpenFile(wxCommandEvent & event);
      void OnOk(wxCommandEvent & event);
      void OnCancel(wxCommandEvent & event);
      ///@}

      // -- Utilities ---
      void StereoModeCtl(int mode);

public:
      /// The constructor
      /// \param pParent - Pointer to parent window
      /// \param pEap - Pointer to Acoustical Parameter module class
      /// \param pAp - Pointer to Acoustical Parameter calculation class
      /// \param pExportData - Pointer to Acoustical Parameters data export manager
      AcParametersDialog(wxWindow* pParent,
                         EffectAcParameters* pEap,
    		             AcParameters* pAp,
                         AcParametersExports* pExportData);
};




//----------------------------------------------------------------------------
// AcParametersShow
//
/// \brief The Acoustical Parameters result dialog.
//
/// From this dialog the user can see the calculation results
/// both in graphical and textual way.
//----------------------------------------------------------------------------
class AcParametersShowDialog : public AcParShowDlg
{
 
 protected:
    enum { 
        ID_COPY_SELECTION_MENU = 0x2000 
    };
   
 private:

   wxWindow  *mParent;
   wxMenu    *mContextMenu;
   APDecayPlot* m_pDecayPlot;
   APBarPlot*   m_pBarPlot;
   
   EffectAcParameters* m_pEap;
   AcParameters*       m_pAp; // To be removed
   
   // Data sources
   TArrayOfAPAudioTracks*               m_paAudioTracks;
   std::vector<TSchroederDecay>&        m_paDecay;
   std::vector<AcParameters::TResults>& m_paResults;

   AcParametersExports*  m_pExportData;
   AFConfig*             m_pCfg;

   wxStaticBitmap *m_pwxbmpAuroraLogo,
                  *m_pwxbmpLogo;

   int m_nCurrentChannel,
       m_nCurrentBand,
       m_nCurrentParameter;

   bool m_bIsScopeOn;

   void UpdateCellValue(const int nPar, const int nRow, const int nBand, const bool bInit = false);
   void UpdateParametersValues(const bool init = false);
   void UpdatePlot(const bool bReplaceData = true);
   
   void CreateDecayPlot();
   void CreateBarPlot();
   void SetupDecayPlot();
   void SetupBarPlot();

   // --- Events handlers
   void OnCloseDialog       (wxCloseEvent& event);
   void OnClose             (wxCommandEvent & event);
   void OnHelp              (wxCommandEvent & event);
   void OnOk                (wxCommandEvent & event);
   void OnSetupButton       (wxCommandEvent& event);
   void OnSaveResults       (wxCommandEvent & event);
   void OnCopyResults       (wxCommandEvent & event);
   void OnCopySelection     (wxCommandEvent & event);
   void OnStoreGRefSig      (wxCommandEvent & event);
   void OnChannelListSelect ( wxCommandEvent& event );
   void OnGridCellRightClick( wxGridEvent& event );
   void OnGraphChange       ( wxGridEvent& event );
   void OnGridLabelDoubleClick( wxGridEvent& event );
   void OnChar              (wxKeyEvent &event);

   void PromptSetupDialog();
   void StoreGeometry();
   void RestoreGeometry();
   void Init();

  public:
   // --- ctors    
   AcParametersShowDialog(wxWindow* pParent,
		                  EffectAcParameters* pEap,
		                  AcParameters* pAp,
		                  AcParametersExports* pExportData,
		                  AFConfig* pCfg);
   ~AcParametersShowDialog();
};

//----------------------------------------------------------------------------
// StoreGValueDialog
//----------------------------------------------------------------------------
class StoreGValueDialog : public GStoreDlg
{
private: 
   AcParameters* m_pAp;
   double mDist;
   
protected:
    // Handlers for GStoreDlg events.
    void OnCloseDialog      (wxCloseEvent& event);
    void OnEditDistanceField( wxCommandEvent& event );
    void OnRestoreDefaults  ( wxCommandEvent& event );
    void OnOK               ( wxCommandEvent& event );
    void OnCancel           ( wxCommandEvent& event );
    
public:
    /** Constructor */
    StoreGValueDialog( AcParameters *ap, 
                       wxWindow* parent );
};


#endif // __AURORA_ACPARAM_GUI__

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
