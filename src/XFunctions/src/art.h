/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  art.h

  Simone Campanini

**********************************************************************/
#ifndef __AURORA_XFUNCTIONS_ART_H__
#define __AURORA_XFUNCTIONS_ART_H__

//
// XFunctionsArtProvider implementation
//
#include <commdefs.h>
#include <wx/artprov.h>
#include <wx/image.h>
#include <wx/mstream.h>

//
// XFunctionsArtProvider declaration 
//
class XFunctionsArtProvider : public wxArtProvider
{
  protected:
     virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size);
};


//
// XFunctionsArtProvider initializer
//
void InitXFunctionsArtProvider();


#endif // __AURORA_XFUNCTIONS_ART_H__

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
