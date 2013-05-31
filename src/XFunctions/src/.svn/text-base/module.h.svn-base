/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  module.h

  Angelo Farina - Simone Campanini

**********************************************************************/

#ifndef __AURORA_XFUNCTIONS_MODULE_H__
#define __AURORA_XFUNCTIONS_MODULE_H__

// from Audacity
#include <Audacity.h>
#include <effects/Effect.h>
#include <WaveTrack.h>

#include <commdefs.h>
#include <afconfig.h>
#include "xfn.h"

class WaveTrack;

class EffectXFunctions: public Effect
{

 private:
   XFunctions *m_pXf;

   AFConfig m_Cfg;

   void SelectTracks(bool status);
   void SelectAllTracks();
   void DeselectAllTracks();
   
 public:

   // ---------------- Standard Audacity Effects' methods ----------------
   
   virtual wxString GetEffectName() {
#ifdef __WXDEBUG__       
      return wxString(_("Aurora XFunctions (debug)..."));
#else
      return wxString(_("Aurora XFunctions..."));      
#endif
   }

   virtual wxString GetEffectIdentifier() {
      return wxString(_("XFunctions"));
   }

   virtual wxString GetEffectAction() {
      return wxString(_("Cross Functions"));
   }

   virtual std::set<wxString> GetEffectCategories() {
      std::set<wxString> result;
      result.insert(wxT("http://lv2plug.in/ns/lv2core#AnalyserPlugin"));
      return result;
   }

   virtual int GetEffectFlags() {
      return BUILTIN_EFFECT | ANALYZE_EFFECT;
   }   

   // Useful only after PromptUser values have been set. --------------
   //   virtual wxString GetEffectDescription(); 

   virtual bool Init();
   virtual bool PromptUser();
//   virtual bool TransferParameters( Shuttle & shuttle );

 protected:
   virtual bool Process();

 
 public:     
    EffectXFunctions();
    ~EffectXFunctions();

};


#endif // __AURORA_XFUNCTIONS_MODULE_H__

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

