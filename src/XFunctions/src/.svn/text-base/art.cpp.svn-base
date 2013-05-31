/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  art.cpp

  Simone Campanini

**********************************************************************/
#include <afart.h>

#include "art.h"
#include "equations.h"

//
// XFunctionsArtProvider implementation
//
wxBitmap XFunctionsArtProvider::CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
{
    if(id == wxT("eq_autocorr"))     return GetBitmapFromMemory(eq_autocorr);
    if(id == wxT("eq_crosscorr"))    return GetBitmapFromMemory(eq_crosscorr);
    if(id == wxT("eq_whitened_csp")) return GetBitmapFromMemory(eq_whitened_csp);
    if(id == wxT("eq_crosspower"))   return GetBitmapFromMemory(eq_crosspower);
    if(id == wxT("eq_h1"))           return GetBitmapFromMemory(eq_h1);
    if(id == wxT("eq_h2"))           return GetBitmapFromMemory(eq_h2);
    if(id == wxT("eq_h3"))           return GetBitmapFromMemory(eq_h3);
    if(id == wxT("eq_alpha"))        return GetBitmapFromMemory(eq_alpha);
    if(id == wxT("eq_pu_swtube"))    return GetBitmapFromMemory(eq_pu_swtube);
    if(id == wxT("eq_pu_freefield")) return GetBitmapFromMemory(eq_pu_freefield);

    return wxNullBitmap;
}


void InitXFunctionsArtProvider()
{
   wxArtProvider::Push(new XFunctionsArtProvider);
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
