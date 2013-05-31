/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common Libraries

  afexports.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AFExports
\brief Data exports manager parent class

  This class manages exports to/from files and clipboard.

*//*******************************************************************/

#include "afexports.h"

#include <wx/clipbrd.h>

const wxChar* const  AFExports::m_awxchExtension [] = { wxT("txt"), wxT("csv"), wxT("prn")};
const wxChar  AFExports::m_awxchSeparator [] = { wxT('\t'), wxT(',')};

bool AFExports::IsExtensionPresent(wxString& wxszFn)
{
    wxString wxszExt = wxszFn.AfterLast(wxT('.'));
    if(wxszExt.IsSameAs(wxszFn))
        return false;

    return true;
}

void AFExports::CopyEntireTableToClipboard()
{
   wxClipboardLocker locker;
   if( !locker ) 
   {
      ::wxMessageBox(wxT("Cannot open clipboard!"),
    		         wxT("Error"),
    		         wxOK | wxICON_ERROR);
      return;
   }
   wxTheClipboard->Clear();

   //Copy results to clipboard
   wxString wxszData;
   if(!BuildParametersTable(wxszData, DD_CLIPBOARD)) 
   {
       ::wxMessageBox(wxT("Error building table or table is too big (> 65535 rows)"),
    		          wxT("Error"),
    		          wxOK | wxICON_ERROR);
       return;
   }
   if ( !wxTheClipboard->AddData(new wxTextDataObject(wxszData)) ) 
      ::wxMessageBox(wxT("Can't copy data to the clipboard!"),
    		         wxT("Error"),
    		         wxOK | wxICON_ERROR);
//   else
//      wxMessageBox( wxT("Data successifully copied to the clipboard!"), wxT("Data copied"), wxOK | wxICON_INFORMATION);
}

void AFExports::CopyGridSelectionToClipboard(wxGrid *pGrid)
{
   wxClipboardLocker locker;
   if( !locker ) 
   {
      ::wxMessageBox(wxT("Cannot open clipboard!"),
    		         wxT("Error"),
    		         wxOK | wxICON_ERROR);
      return;
   }

   wxTheClipboard->Clear();

   //Copy results to clipboard  
   size_t i;
   int nRow, nCol;
   wxString wxszData;
   int nRows = pGrid->GetNumberRows();
   int nCols = pGrid->GetNumberCols();
   
   const wxGridCellCoordsArray awxTopLeftGrd  = pGrid->GetSelectionBlockTopLeft();
   const wxGridCellCoordsArray awxBtmRightGrd = pGrid->GetSelectionBlockBottomRight();
   const wxGridCellCoordsArray awxSparseCellsGrd = pGrid->GetSelectedCells();
   const wxArrayInt awxnRows = pGrid->GetSelectedRows();
   const wxArrayInt awxnCols = pGrid->GetSelectedCols();

   bool bThereAreBoxes  = false;
   bool bThereAreRows   = false;
   bool bThereAreCols   = false;
   bool bThereAreSparse = false;
   
   int nMinRow = nRows -1; 
   int nMaxRow = 0;
   int nMinCol = nCols - 1; 
   int nMaxCol =0; 
   
   //find minimum grid subset containing all selections
   if((awxTopLeftGrd.GetCount() > 0) && (awxBtmRightGrd.GetCount() > 0)) 
   {   
      bThereAreBoxes = true;
      for(i = 0; i < awxTopLeftGrd.GetCount(); i++) 
      {
          nMinRow = (awxTopLeftGrd[i].GetRow() < nMinRow)  ? awxTopLeftGrd[i].GetRow()  : nMinRow;
          nMinCol = (awxTopLeftGrd[i].GetCol() < nMinCol)  ? awxTopLeftGrd[i].GetCol()  : nMinCol;
          nMaxRow = (awxBtmRightGrd[i].GetRow() > nMaxRow) ? awxBtmRightGrd[i].GetRow() : nMaxRow;
          nMaxCol = (awxBtmRightGrd[i].GetCol() > nMaxCol) ? awxBtmRightGrd[i].GetCol() : nMaxCol;
      }
   }
   if(awxnRows.GetCount() > 0) 
   {
       bThereAreRows = true;
       for(i = 0; i < awxnRows.GetCount(); i++) 
       {
           nMinRow = (awxnRows[i] < nMinRow) ? awxnRows[i] : nMinRow;
           nMaxRow = (awxnRows[i] > nMaxRow) ? awxnRows[i] : nMaxRow;
       }
       nMinCol = 0;
       nMaxCol = nCols -1;
   }
   if(awxnCols.GetCount() > 0) 
   {
       bThereAreCols = true;
       for(i = 0; i < awxnCols.GetCount(); i++) 
       {
           nMinCol = (awxnCols[i] < nMinCol) ? awxnCols[i] : nMinCol;
           nMaxCol = (awxnCols[i] > nMaxCol) ? awxnCols[i] : nMaxCol;
       }
       nMinRow = 0;
       nMaxRow = nRows - 1;
   }
   if(awxSparseCellsGrd.GetCount() > 0) 
   {
       bThereAreSparse = true;
       for(i = 0; i < awxSparseCellsGrd.GetCount(); i++) 
       {
          nMinRow = (awxSparseCellsGrd[i].GetRow() < nMinRow) ? awxSparseCellsGrd[i].GetRow() : nMinRow;
          nMinCol = (awxSparseCellsGrd[i].GetCol() < nMinCol) ? awxSparseCellsGrd[i].GetCol() : nMinCol;
          nMaxRow = (awxSparseCellsGrd[i].GetRow() > nMaxRow) ? awxSparseCellsGrd[i].GetRow() : nMaxRow;
          nMaxCol = (awxSparseCellsGrd[i].GetCol() > nMaxCol) ? awxSparseCellsGrd[i].GetCol() : nMaxCol;
           
       }
   }
   // Now the matrix size is (nMaxRow - nMinRow + 1) x (nMaxCol - nMinCol + 1) 
   bool bFound = false;
   for(nRow = nMinRow; nRow < (nMaxRow+1); nRow++) 
   {
       for(nCol = nMinCol; nCol < (nMaxCol+1); nCol++) 
       {
          if(bThereAreBoxes) 
          {
             for(i = 0; (i < awxTopLeftGrd.GetCount()) &&  (!bFound); i++) 
                if( (nCol >= awxTopLeftGrd[i].GetCol()) && (nCol <= awxBtmRightGrd[i].GetCol()) &&
                    (nRow >= awxTopLeftGrd[i].GetRow()) && (nRow <= awxBtmRightGrd[i].GetRow()) )   bFound = true; 
          }
          if(bThereAreCols) 
          {
             for(i = 0; (i < awxnCols.GetCount()) && (!bFound); i++) 
                if( nCol == awxnCols[i] ) bFound = true; 
          }
          if(bThereAreRows) 
          {
              for(i = 0; (i < awxnRows.GetCount()) && (!bFound); i++)
                if( nRow == awxnRows[i] ) bFound = true; 
          }
          if(bThereAreSparse) 
          {
              for(i = 0; (i < awxSparseCellsGrd.GetCount()) && (!bFound); i++)
                if( (nCol == awxSparseCellsGrd[i].GetCol()) && 
                    (nRow == awxSparseCellsGrd[i].GetRow()) ) bFound = true; 
          }
          
          if(bFound) wxszData << pGrid->GetCellValue(nRow, nCol);
          wxszData << wxT("\t");
          bFound = false;
       }
       wxszData << LINE_BREAK;
   }
   
  if ( !wxTheClipboard->AddData(new wxTextDataObject(wxszData)) )  
      ::wxMessageBox(wxT("Can't copy wxszData to the clipboard!"),
    		         wxT("Error"),
    		         wxOK | wxICON_ERROR);
//   else
//      wxMessageBox( wxT("Data successifully copied to the clipboard!"), wxT("Data copied"), wxOK | wxICON_INFORMATION);
}

AFExports::AFExports(wxWindow *pParent)
  : m_pParent(pParent),
    m_nSeparatorType(FS_TAB)
{
   // under X we usually want to use the primary selection by default (which
   // is shared with other apps)
   wxTheClipboard->UsePrimarySelection();
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

