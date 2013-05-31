/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  spectrum.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_STI_SPECTRUM_H__
#define __AURORA_STI_SPECTRUM_H__

#include <afconfig.h>

#include "exports.h"
#include "sti.h"
#include "spframe.h"

#define ID_RIGHT_PLOT  10002
#define ID_LEVEL_COPY_SELECTION_MENU 10022

//----------------------------------------------------------------------------
// STISpectrumGridCellColoredRectRenderer
//----------------------------------------------------------------------------
class STISpectrumGridCellColoredRectRenderer : public wxGridCellStringRenderer
{
  public:
   virtual void Draw(wxGrid &grid, wxGridCellAttr& attr, wxDC &dc,
                     const wxRect& rect, int nRow, int nCol, bool bIsSelected);
};

///////////////////////////////////////////////////////////////////////////////
/// Class STISpectrumDialog
///////////////////////////////////////////////////////////////////////////////
class STISpectrumDialog : public STISpectrumDlg
{
  private:
    AuroraSTI*  m_pAs;
    bool        m_bIsStereo;
    int         m_nCurrentChnl;

    wxPanel* m_pwxpnlRightPage;
    wxMenu*  m_pwxLevelContextMenu;

    wxStaticBitmap *m_pwxbmpAuroraLogo,
                   *m_pwxbmpLogo;

    STISpectrumExports  m_ExportsMgr;

    wxArrayString m_awxszBandLabels;

    AFConfig* m_pCfg;
        
// private methods
    void FillTable();
        
    void OnCloseDialog( wxCloseEvent& event );
    void OnChannelSelect( wxCommandEvent& event );
//    void OnPageChange( wxNotebookEvent& event );
    void OnLevelTableLabelClick( wxGridEvent& event );
    void OnLevelTableRightClick( wxGridEvent& event );

    void OnLevelTableKeyPress( wxKeyEvent& event );
    void OnLevelTableCopySelection(wxCommandEvent & event);

    void StoreGeometry();
    void RestoreGeometry();

  public:
        
    STISpectrumDialog( wxWindow* parent,
                      AuroraSTI* pAs,
                      AFConfig* pCfg,
                      const bool bIsStereo = false);
    ~STISpectrumDialog();
};

#endif //__AURORA_STI_SPECTRUM_H__
