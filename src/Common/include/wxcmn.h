/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  wxcmn.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_WXCMN_H__
#define __AURORA_WXCMN_H__

#include <wx/wx.h>   // since 15/11/11 vc++ don't like it anymore...

#include <gpfuncts.h>

#define wxAURORA_NAME wxT("Aurora")
#define wxAURORA_VERSION wxT("4.3")

#ifdef __WXWIN__
    // Windows use the backslash in path expressions...
    #define TRAILING_SLASH wxT("\\")
    #define TRAILING_SLASH_CH '\\'
#else
    // ...while Unixes system use the slash.
    #define TRAILING_SLASH wxT("/")
    #define TRAILING_SLASH_CH '/'
#endif

#ifdef __WXMSW__
   #define LINE_BREAK         _("\r\n")
   #define FILES_LINE_BREAK wxT("\r\n")
#else
   #define LINE_BREAK         _("\n")
   #define FILES_LINE_BREAK wxT("\n")
#endif


#endif //__AURORA_WXCMN_H__
