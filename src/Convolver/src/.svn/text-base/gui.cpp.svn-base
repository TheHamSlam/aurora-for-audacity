/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Aurora Convolver

  gui.cpp

  Simone Campanini

*******************************************************************//**

\class AuroraConvolverDialog 
\brief Dialog used with EffectAuroraConvolver.

*//*******************************************************************/


#include <commdefs.h>
#include <gpfuncts.h>
#include <afart.h>

#include <wx/filename.h>

#include "gui.h"
#include "version.h"

//----------------------------------------------------------------------------
// AFTrackDropSource implementation
//----------------------------------------------------------------------------
bool AFTrackDropSource::GiveFeedback(wxDragResult effect)
{
   //printf("I'm moving!\n");
   return true;
}

AFTrackDropSource::AFTrackDropSource(wxTextDataObject& data, wxListCtrl *owner)
   : wxDropSource(data, owner)
{}

//----------------------------------------------------------------------------
// AFTrackDropTarget implementation
//----------------------------------------------------------------------------
bool AFTrackDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
  // d'n'd appends data to the list
  // data contains a tab separated list of list labels
  wxString text = data;
  wxString textItem = text.BeforeFirst(TRAILING_SLASH_CH);
  
  //first field contains the number of items
  long count;
  textItem.ToLong(&count);
  while(count > 0)
  {
     text = text.AfterFirst(TRAILING_SLASH_CH);
     textItem = text.BeforeFirst(TRAILING_SLASH_CH);
#ifdef __AUDEBUG__
     printf("Dropping %s @ pos %d\n", (const char*)textItem.ToAscii(), mOwner->GetItemCount());
#endif
     mOwner->InsertItem(mOwner->GetItemCount(), textItem);
     
     count--;
  }
  
  return true;
}

AFTrackDropTarget::AFTrackDropTarget(wxListCtrl *owner)
   : mOwner(owner)
{}

//----------------------------------------------------------------------------
// AuroraTrackSelectorDialog implementation
//----------------------------------------------------------------------------
void AuroraTrackSelectorDialog::OnToIRsBtn( wxCommandEvent& event )
{
   MoveItemsBetweenLists(mAvailableList, mFilterList);
   ToggleControls();
}

void AuroraTrackSelectorDialog::ToAudioDataBtn( wxCommandEvent& event )
{
   MoveItemsBetweenLists(mAvailableList, mAudioDataList);
   ToggleControls();
}

void AuroraTrackSelectorDialog::OnMatrixModeCheck( wxCommandEvent& event )
{   
   if(event.IsChecked())
   {
      mAc->SetMatrixMode(true);
      mOneForAllCheck->SetValue(false);
      
   } else
       mAc->SetMatrixMode(false);
}

void AuroraTrackSelectorDialog::OnOneForAllCheck( wxCommandEvent& event )
{
   if(event.IsChecked())
   {
     mAc->SetOneForAll(true);
     mMatrixModeCheck->SetValue(false);
     
   } else
       mAc->SetOneForAll(false);
}

void AuroraTrackSelectorDialog::OnMoveUpBtn( wxCommandEvent& event )
{
  MoveUpListItem(mFilterList);
  MoveUpListItem(mAudioDataList);
  ToggleControls();
}

void AuroraTrackSelectorDialog::OnMoveDownBtn( wxCommandEvent& event )
{
   MoveDownListItem(mFilterList);
   MoveDownListItem(mAudioDataList);
   ToggleControls();
}

void AuroraTrackSelectorDialog::OnToRightBtn( wxCommandEvent& event )
{
   MoveItemsBetweenLists(mAudioDataList, mFilterList);
   ToggleControls();
}

void AuroraTrackSelectorDialog::OnToLeftBtn( wxCommandEvent& event )
{
   MoveItemsBetweenLists(mFilterList, mAudioDataList);
   ToggleControls();
}

void AuroraTrackSelectorDialog::OnRemoveBtn( wxCommandEvent& event )
{
   MoveItemsBetweenLists(mFilterList, mAvailableList);
   MoveItemsBetweenLists(mAudioDataList, mAvailableList);
   ToggleControls();
}

void AuroraTrackSelectorDialog::OnHelp( wxCommandEvent& event )
{
   wxString path = wxT("");
   path << wxT("Docs") << TRAILING_SLASH << wxT("lin_conv.html");
   wxFileName help_path(path);
   help_path.MakeAbsolute();

   ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void AuroraTrackSelectorDialog::OnOK( wxCommandEvent& event )
{
   int filterItemsCount = mFilterList->GetItemCount();  
   if(!filterItemsCount)
   {
      wxMessageBox(_("No filter(s) selected."),_("Error"), wxOK | wxICON_ERROR);
      EndModal(false);
      return;
   }
   // With this options it takes always the first filter of the list for
   // each audiodata track
   if(mAc->IsOneForAll()) filterItemsCount = 1;
   
   int  i,j;
   wxString text;
   AFTrackInfoItem *tinfo;
   
   for(i = 0; i < filterItemsCount; i++)
   {
      text = mFilterList->GetItemText(i);
      for(j = 0; j < mAtp->GetTrackInfoCount(); j++)
      {
         tinfo = mAtp->GetTrackInfoItem(j);
         if(text == tinfo->GetLabel())
         {
             tinfo->SetAsIr();
             tinfo->SetRow(i);
         }
      }
   }
   
   int adItemsCount = mAudioDataList->GetItemCount();  
   if(!adItemsCount)
   {
      wxMessageBox(_("No audio data(s) selected."),_("Error"), wxOK | wxICON_ERROR);
      EndModal(false);
      return;
   }
   
   for(i = 0; i < adItemsCount; i++)
   {
      text = mAudioDataList->GetItemText(i);
      for(j = 0; j < mAtp->GetTrackInfoCount(); j++)
      {
         tinfo = mAtp->GetTrackInfoItem(j);
         if(text == tinfo->GetLabel())
         {
             tinfo->SetAsAudioData();
             tinfo->SetRow(i);
         }
      }
   }
   mAtp->SetAudioDataRowsCount(adItemsCount);
   mAtp->SetFilterRowsCount(filterItemsCount);
   
   if(!mAc->IsOneForAll())
   {    
      if(adItemsCount != filterItemsCount)
      {
         // The number of filters row is different from
         // audio datas -> Force Matrix Mode
         mAc->SetMatrixMode(true);
      }
   }
   
   EndModal(true);
}

void AuroraTrackSelectorDialog::OnCancel( wxCommandEvent& event )
{
   EndModal(false);
}

void AuroraTrackSelectorDialog::InitDrag(wxListCtrl* list)
{
   wxString text;
     
   // 1: find selected items, return false is there isn't
   text.Clear();
   int selectedItemsCount = list->GetSelectedItemCount();
//    printf("Selected %d items\n", selectedItemsCount); fflush(stdout);
   text << selectedItemsCount << TRAILING_SLASH; 
   int idx = 0;
   long *itemsList = new long [selectedItemsCount];
   long item = -1;
   for( ;; )
   {
       item = list->GetNextItem(item, wxLIST_NEXT_ALL,  wxLIST_STATE_SELECTED);
       
       if( item > -1 )
       {
// 		  printf("appending %d item\n", item); fflush(stdout);
          text << list->GetItemText(item) << TRAILING_SLASH;
          itemsList[idx++] = item;

       } else break;
   }
   
   // 2: build DropSource ad do drag'n'drop
   wxTextDataObject tdo(text);
   AFTrackDropSource tds(tdo, list);
   tds.DoDragDrop(); 
//    printf("dragdrop done\n"); fflush(stdout);
   
   // 3: delete items from source
   for(idx = (selectedItemsCount-1); idx >= 0; idx--)
      list->DeleteItem(itemsList[idx]);
   
   delete [] itemsList;
   
   ToggleControls();
//    printf("exiting initdrag\n"); fflush(stdout);
}

void AuroraTrackSelectorDialog::OnAvailableDragInit(wxListEvent& event)
{
   InitDrag(mAvailableList);
}

void AuroraTrackSelectorDialog::OnAudioDataDragInit(wxListEvent& event)
{
    InitDrag(mAudioDataList);
}

void AuroraTrackSelectorDialog::OnFilterDragInit(wxListEvent& event)
{
    InitDrag(mFilterList);
}


void AuroraTrackSelectorDialog::PopulateAvailableTracksList()
{
   int i = 0;   
   //wxString label;
   AFTrackInfoItem *tinfo;
   while(i < mAtp->GetTrackInfoCount())
   {
      //label.Printf(_("Track %d"), i+1);
      if((tinfo = mAtp->GetTrackInfoItem(i))) 
         mAvailableList->InsertItem(i, tinfo->GetLabel());
      else
         printf("tinfo is NULL\n"); fflush(stdout); // *** DEBUG
      i++;
   }

}

bool AuroraTrackSelectorDialog::MoveItemsBetweenLists(wxListCtrl *l_src, wxListCtrl *l_dest)
{
   // 1: find selected items, return false is there isn't
   int selectedItemsCount = l_src->GetSelectedItemCount();
   if(selectedItemsCount <= 0) return false;
   
   int idx = 0;
   long *itemsList = new long [selectedItemsCount];
   long item = -1;
   for( ;; )
   {
       item = l_src->GetNextItem(item, wxLIST_NEXT_ALL,  wxLIST_STATE_SELECTED);
       
       if( item == -1 )  
          break;
       else 
          itemsList[idx++] = item;
       
       // this item is selected - do whatever is needed with it
    }
   
   // 2: copy items from source to dest
   wxString text;
   int destItemCount = l_dest->GetItemCount();
   for(idx = 0; idx < selectedItemsCount; idx++)
   {
      text = l_src->GetItemText(itemsList[idx]);
      l_dest->InsertItem(destItemCount+idx, text);
   }
   
   // 3: delete items from source
   for(idx = (selectedItemsCount-1); idx >= 0; idx--)
   {
       l_src->DeleteItem(itemsList[idx]);
   }
   
   delete [] itemsList;
   
   return true;
}

bool AuroraTrackSelectorDialog::MoveUpListItem(wxListCtrl *lst)
{
   // 1: find selected item, return false is there isn't or if there
   //    are more than 1!
   int selectedItemsCount = lst->GetSelectedItemCount();
   if(selectedItemsCount != 1) return false;
   
   // 2: find selected item (if it is at the position '0', it cannot 
   //    be moved up!)
   long item = lst->GetNextItem(-1, wxLIST_NEXT_ALL,  wxLIST_STATE_SELECTED);
   if(!item) return false;
   
   // 3: copy selected item in the new place
   wxString text;
   text = lst->GetItemText(item);
   lst->InsertItem(item-1, text);
   
   // 4: delete old item
   lst->DeleteItem(item+1);
   
   return true;
}

bool AuroraTrackSelectorDialog::MoveDownListItem(wxListCtrl *lst)
{
   // 1: find selected item, return false is there isn't or if there
   //    are more than 1!
   int selectedItemsCount = lst->GetSelectedItemCount();
   if(selectedItemsCount != 1) return false;
   
   // 2: find selected item (if it is at the last position, it cannot 
   //    be moved up!)
   long item = lst->GetNextItem(-1, wxLIST_NEXT_ALL,  wxLIST_STATE_SELECTED);
   if(item == (lst->GetItemCount()-1)) return false;
   
   // 3: copy selected item in the new place
   wxString text;
   text = lst->GetItemText(item);
   lst->InsertItem(item+2, text);
   
   // 4: delete old item
   lst->DeleteItem(item);

   return true;
}

void AuroraTrackSelectorDialog::ToggleMatrixModeCheck()
{
   int filterCount = mFilterList->GetItemCount();
   int adCount = mAudioDataList->GetItemCount();
   
   if(adCount != filterCount)
   {
       mAc->SetMatrixMode(false);
       mMatrixModeCheck->SetValue(false);
       mMatrixModeCheck->Disable();
       
   } else {
       
       mMatrixModeCheck->Enable();
   }
}

void AuroraTrackSelectorDialog::ToggleControls()
{
   int filterCount = mFilterList->GetItemCount();
   int adCount = mAudioDataList->GetItemCount();
   
   if((!filterCount) || (!adCount))
   {
      mMatrixModeCheck->Disable();
      mOkBtn->Disable();
      
   } else {
       
      mMatrixModeCheck->Enable();
      mOkBtn->Enable();
      
   }
}

/** Constructor */
AuroraTrackSelectorDialog::AuroraTrackSelectorDialog( wxWindow* parent, AuroraConvolver *ac, AFTrackProperties *atp )
  : AFTrackSelectorDlg(parent),
    mAc(ac), mAtp(atp)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Convolver - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(AC_VERSION_TYPE, AC_RELEASE_CANDIDATE) << wxT(")");
    SetTitle(wxszTitle);

	// Draw logo
	wxBoxSizer* pLogoSizer;
	pLogoSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pwxbmpAuroraLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                                 AFArtProvider::GetBitmap(wxT("Aurora_logo")),
			                                 wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpAuroraLogo, 0, wxALL, 5 );

	pLogoSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_pwxbmpLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                           AFArtProvider::GetBitmap( wxT("conv_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();

	// Init widgets
   PopulateAvailableTracksList();
   
   //setup drag'n'drop
   AFTrackDropTarget *availDataTarget = new AFTrackDropTarget(mAvailableList);
   mAvailableList->SetDropTarget(availDataTarget);
   
   AFTrackDropTarget *audioDataTarget = new AFTrackDropTarget(mAudioDataList);
   mAudioDataList->SetDropTarget(audioDataTarget);
   
   AFTrackDropTarget *filterTarget = new AFTrackDropTarget(mFilterList);
   mFilterList->SetDropTarget(filterTarget); 
}

//----------------------------------------------------------------------------
// AuroraConvolverDialog
//----------------------------------------------------------------------------

void AuroraConvolverDialog::OnOk( wxCommandEvent& event )
{
    EndModal(true);
}

void AuroraConvolverDialog::OnCancel( wxCommandEvent& event )
{
    EndModal(false);
}

void AuroraConvolverDialog::OnHelp( wxCommandEvent& event )
{
    wxString path = wxT("");
    path << wxT("Docs") << TRAILING_SLASH << wxT("lin_conv.html");
    wxFileName help_path(path);
    help_path.MakeAbsolute();

    ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void AuroraConvolverDialog::OnFullAutorangeCheck( wxCommandEvent& event )
{
   if(event.IsChecked())
   {
       mGainStext->Disable();
       mGainText->Disable();
       mdBStext->Disable();
       mAc->SetFullAutorange(true);
       if(mFBAutorangeCheck->IsChecked()) 
          mFBAutorangeCheck->SetValue(false);
       
   } else {
       
       mGainStext->Enable();
       mGainText->Enable();
       mdBStext->Enable();
       mAc->SetFullAutorange(false);
   }
}

void AuroraConvolverDialog::OnFirstBlockAutorangeCheck( wxCommandEvent& event )
{
   if(event.IsChecked())
   {
       mGainStext->Disable();
       mGainText->Disable();
       mdBStext->Disable();
       mAc->SetFirstBlockAutorange(true);
       if(mFullAutorangeCheck->IsChecked()) 
          mFullAutorangeCheck->SetValue(false);
       
   } else {
       
       mGainStext->Enable();
       mGainText->Enable();
       mdBStext->Enable();
       mAc->SetFirstBlockAutorange(false);
   }
}

void AuroraConvolverDialog::OnGainText( wxCommandEvent& event )
{
   double d = ::TextPtrToDouble(mGainText);
   mAc->SetGain(d);
}

void AuroraConvolverDialog::OnTimeReverseIrCheck( wxCommandEvent& event )
{
    mAc->SetTimeReversedIr(event.IsChecked());
    //mPlot->SetTimeReversed(event.IsChecked());  //TODO this call must be checked
    mPlot->Refresh();
}

void AuroraConvolverDialog::OnPreserveLengthCheck( wxCommandEvent& event )
{
    mAc->SetPreserveLength(event.IsChecked());
}

void AuroraConvolverDialog::OnCrosstalkCancelCheck( wxCommandEvent& event )
{
    mAc->SetCancelCrossTalk(event.IsChecked());
}

// *** Ctors
AuroraConvolverDialog::AuroraConvolverDialog(wxWindow* parent, AuroraConvolver *ac) 
 : AFConvolverDlg( parent ),
   mAc(ac)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Convolver - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(AC_VERSION_TYPE, AC_RELEASE_CANDIDATE) << wxT(")");
    SetTitle(wxszTitle);

	// Draw logo
	wxBoxSizer* pLogoSizer;
	pLogoSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pwxbmpAuroraLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                                 AFArtProvider::GetBitmap(wxT("Aurora_logo")),
			                                 wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpAuroraLogo, 0, wxALL, 5 );

	pLogoSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_pwxbmpLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                           AFArtProvider::GetBitmap( wxT("conv_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();

	// Init widgets
    wxString wxszValue;
    wxszValue.Printf(_("%.2f"), mAc->GetGain());
    mGainText->SetValue(wxszValue);

    if(((mAc->GetIrRows() != 2) && (mAc->GetIrCols() != 2)) || mAc->IsMatrixMode())
    {
        mCrossTalkCheck->Disable();
    }
    else
    {
        mCrossTalkCheck->SetValue(mAc->IsCancelCrossTalk());
    }

    //Set/unset checks
    mFullAutorangeCheck->SetValue(mAc->IsFullAutorange());
    mFBAutorangeCheck->SetValue(mAc->IsFirstBlockAutorange());
    mTimeReversedCheck->SetValue(mAc->IsTimeReversedIr());
    mPreserveLengthCheck->SetValue(mAc->IsPreserveLength());

    if(mFullAutorangeCheck->IsChecked() || mFBAutorangeCheck->IsChecked())
    {
        mGainText->Disable();
        mGainStext->Disable();
        mdBStext->Disable();
    }
   
    // Update info static text
    wxString wxszLabel;
    wxszLabel.Printf(_("%.0f Hz/"), mAc->GetSamplerate());
    wxszValue.Printf(_("%d Channel"), mAc->GetIrCols());
    wxszLabel << wxszValue;
    if(mAc->GetIrCols() > 1) 
        wxszLabel << _("s/");
    else                     
        wxszLabel << _("/");
    wxszValue.Printf(_("%ld Samples"), long(mAc->GetAudioDataTrackLength()));
    wxszLabel << wxszValue;
    mAudioDataStext->SetLabel(wxszLabel);

    wxszLabel.Printf(_("%.0f Hz/"), mAc->GetSamplerate());
    if(!mAc->IsMatrixMode())
    {
        wxszValue.Printf(_("%d Channel"), (!mAc->IsOneForAll()) ? mAc->GetIrRows() : 1);
        wxszLabel << wxszValue;
        if((mAc->GetIrRows() > 1) && (!mAc->IsOneForAll())) 
            wxszLabel << _("s/");
        else                     
            wxszLabel << _(" /");
    }
    else
    {
        wxszValue.Printf(_("%dx%d Matrix/"), mAc->GetIrRows(), mAc->GetIrCols());
        wxszLabel << wxszValue;
    }
    wxszValue.Printf(_("%ld Samples"),
                 long(mAc->GetIrTrackLength()/((!mAc->IsOneForAll()) ? mAc->GetIrCols() : 1)));
    wxszLabel << wxszValue;
    mFilterStext->SetLabel(wxszLabel);

    wxszLabel.Printf(_("%ld Samples (estimated)"), long(mAc->GetFFTLength()));
    mFftSizeStext->SetLabel(wxszLabel);

    if(mAc->IsMatrixMode())
        wxszLabel.Printf(_("Matrix Convolution Product (%d x %d)"), mAc->GetIrRows(), mAc->GetIrCols());
    else if(mAc->IsOneForAll())
        wxszLabel.Printf(_("Row to row Convolution Product - One for All (N = %d)"), mAc->GetIrRows());
    else
        wxszLabel.Printf(_("Row to row Convolution Product (N = %d)"), mAc->GetIrRows());

    mModeStext->SetLabel(wxszLabel);

    // Initialize plot
//    mPlot->SetTitle("RMS");
    mPlot->GetTimeAxis()->SetTitle(wxT("Time [s]"));
    mPlot->GetTimeAxis()->SetFormat(AFAxisBase::RF_REAL);
    mPlot->GetTimeAxis()->ShowTitle(true);
    mPlot->GetTimeAxis()->ShowGrid(true);

    mPlot->GetLevelAxis()->SetTitle(wxT("RMS Level [dB]"));
    mPlot->GetLevelAxis()->SetRange(-120, 0, AFAxisBase::RF_LINEARdB);
    mPlot->GetLevelAxis()->ShowTitle(true);
    mPlot->GetLevelAxis()->ShowGrid(true);

    wxColour col;
    AFTimeDataSerie* pTds;
    for(int nCh = 0; nCh < (mAc->IsOneForAll() ? 1 : mAc->GetIrRows()); nCh++)
    {
        pTds = new AFTimeDataSerie(mAc->GetIrTrackLength(),
                                   mAc->GetIrTrack(nCh),
                                   mAc->GetSamplerate());
        
        pTds->SetTimeReversed(mAc->IsTimeReversedIr());
        
        wxszLabel.Printf(wxT("Ch %d"), nCh+1);
        pTds->SetLabel(wxszLabel);
        
        ::AuroraChooseColour(col, nCh);
        pTds->SetLineColour(col);
        
        mPlot->AddSerie(pTds);
    }
    mPlot->SetTopBorder(false);
    mPlot->SetRightBorder(false);    
    mPlot->ShowLegend(true);
    
    mPlot->Refresh();
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

