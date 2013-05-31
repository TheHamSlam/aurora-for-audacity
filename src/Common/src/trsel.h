/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Aurora Convolver

  gui.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_CONVOLVER_GUI_H__
#define __AURORA_CONVOLVER_GUI_H__

#include <commdefs.h>

#include <wx/dnd.h>

#include "auconv.h"
#include "dialogs.h"
#include "module.h"
#include "trprop.h"


//----------------------------------------------------------------------------
// AFTrackDropSource
//----------------------------------------------------------------------------
class AFTrackDropSource : public wxDropSource
{
   public:
      bool GiveFeedback(wxDragResult effect);

      AFTrackDropSource(wxTextDataObject& data, wxListCtrl *owner);
};

//----------------------------------------------------------------------------
// AFTrackDropTarget
//----------------------------------------------------------------------------
class AFTrackDropTarget : public wxTextDropTarget
{
   protected:   
      wxListCtrl* mOwner;
      
   public:

     virtual bool OnDropText(wxCoord x, wxCoord y, 
                             const wxString& data);

     AFTrackDropTarget(wxListCtrl *owner);
};
 
//----------------------------------------------------------------------------
// AuroraTrackSelectorDialog
//----------------------------------------------------------------------------

class AuroraTrackSelectorDialog : public AFTrackSelectorDlg
{
 private:
    enum Direction { D_UP, D_DOWN, D_LEFT, D_RIGHT };
    AuroraConvolver   *mAc;
    AFTrackProperties *mAtp;
    
 protected:
    // Handlers for AFTrackSelectorDlg events.
    void OnToIRsBtn( wxCommandEvent& event );
    void ToAudioDataBtn( wxCommandEvent& event );
    void OnMatrixModeCheck( wxCommandEvent& event );
    void OnOneForAllCheck( wxCommandEvent& event );
    void OnMoveUpBtn( wxCommandEvent& event );
    void OnMoveDownBtn( wxCommandEvent& event );
    void OnToRightBtn( wxCommandEvent& event );
    void OnToLeftBtn( wxCommandEvent& event );
    void OnRemoveBtn( wxCommandEvent& event );
    void OnHelp( wxCommandEvent& event );
    void OnOK( wxCommandEvent& event );
    void OnCancel( wxCommandEvent& event );
    
    void InitDrag(wxListCtrl* lst);
    void OnAvailableDragInit(wxListEvent& event);
    void OnAudioDataDragInit(wxListEvent& event);
    void OnFilterDragInit(wxListEvent& event);
    
    void PopulateAvailableTracksList();
    bool MoveItemsBetweenLists(wxListCtrl* src, wxListCtrl* dest);
    bool MoveUpListItem(wxListCtrl* lst);
    bool MoveDownListItem(wxListCtrl* lst);
    void ToggleMatrixModeCheck();
    void ToggleControls();
    
  public:    
    /** Constructor */
    AuroraTrackSelectorDialog( wxWindow* parent, AuroraConvolver *ac, AFTrackProperties *atp );
};

//----------------------------------------------------------------------------
// AuroraConvolverDialog
//----------------------------------------------------------------------------
class AuroraConvolverDialog : public AFConvolverDlg
{
   private:
    AuroraConvolver *mAc;
      
    double TextToDoublePtr(wxTextCtrl *txt);
    
  protected:
    // Handlers for AFConvolverDlg events.
    void OnOk( wxCommandEvent& event );
    void OnCancel( wxCommandEvent& event );
    void OnHelp( wxCommandEvent& event );
    void OnFullAutorangeCheck( wxCommandEvent& event );
    void OnFirstBlockAutorangeCheck( wxCommandEvent& event );
    void OnGainText( wxCommandEvent& event );
    void OnTimeReverseIrCheck( wxCommandEvent& event );
    void OnPreserveLengthCheck( wxCommandEvent& event );
    void OnCrosstalkCancelCheck( wxCommandEvent& event );
    
public:    
    /** Constructor */
    AuroraConvolverDialog( wxWindow* parent, AuroraConvolver *ac );
};

#endif // __AURORA_CONVOLVER_GUI__

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
