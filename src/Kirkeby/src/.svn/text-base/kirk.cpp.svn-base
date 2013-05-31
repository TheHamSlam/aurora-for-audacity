/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Invert Kirkeby

  kirk.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class Kirkeby
\brief The derived Kirkeby class

  Bla bla bla

*//*******************************************************************/

#include "kirk.h"

void Kirkeby::ReadConfigurationValues()
{
   // Read parameter from stored configuration
   //double value;
   //if(mCfg.Read(_("/Aurora/AcParameters/UserMinLevel"), &value))
   //  SetUserMinLevel(value);
}

void Kirkeby::StoreConfigurationValues()
{
   //mCfg.Write(wxT("/Aurora/AcParameters/UserMinLevel"), GetUserMinLevel());
}

void Kirkeby::InitProgressMeter()
{
   mProgressDlg = new ProgressDialog(wxT("Aurora Invert Kirkeby"),
                                     _("Designing invers filter..."));
}
void Kirkeby::UpdateProgressMeter(int step, int total)
{
   mProgressDlg->Update(step, total);      
}

void Kirkeby::DestroyProgressMeter()
{
   mProgressDlg->Destroy();
   mProgressDlg = 0;
}

     

// --- 'ctors

Kirkeby::Kirkeby(const int nRows, const int nCols)
  : AFKirkeby(nRows, nCols),
    mProgressDlg(0)
{}

Kirkeby::~Kirkeby()
{
   if(mProgressDlg) DestroyProgressMeter();
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
