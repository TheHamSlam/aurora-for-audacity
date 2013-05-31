/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  exports.h

  Angelo Farina - Simone Campanini

************************************************************************/
#ifndef __AURORA_STI_EXPORTS_H__
#define __AURORA_STI_EXPORTS_H__

#include <afexports.h>

#include <wx/textfile.h>

#include "sti.h"

// ----------------------------------------------------------------------------
// STISpectrumExport declaration
// ----------------------------------------------------------------------------
class STISpectrumExports : public AFExports 
{ 
  public:
    enum { OPEN_PROMPT = 0, SAVE_PROMPT};

  private:
    wxWindow* m_pParent;

    AuroraSTI* m_pAs;
    bool       m_bIsStereo;
           
  protected:
    bool BuildParametersTable(wxString &wxszDataBuffer, 
                              const int nDest = DD_FILE,
                              const int nFileType = FF_TXT);
  
  private:
    bool LoadFromFile(wxTextFile& wxtfSplData);
    bool SaveToFile(wxTextFile& wxtfSplData);

  public:
     bool OpenSavePrompt(const int nType = OPEN_PROMPT); 

     bool IsStereo() const { return m_bIsStereo; }
     void SetStereo(const bool bValue) { m_bIsStereo = bValue; }

    STISpectrumExports(wxWindow* pParent, AuroraSTI* pAs, const bool bIsStereo = false);
};

// ----------------------------------------------------------------------------
// STIShowExport declaration
// ----------------------------------------------------------------------------
class STIShowExports : public AFExports 
{
  public:

  private:
    wxWindow *m_pParent;

    AuroraSTI* m_pAs;
    bool       m_bIsStereo;
       
    wxString m_wxszIrName;

  protected:
    bool BuildParametersTable(wxString &wxszDataBuffer, 
                              const int nDest = DD_FILE, 
                              const int nFileType = FF_TXT);

  public:
    bool SavePrompt();

    STIShowExports(wxWindow* pParent, AuroraSTI* pAs, const bool nIsStereo = false);
};


#endif // __AURORA_STI_EXPORTS_H__

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
