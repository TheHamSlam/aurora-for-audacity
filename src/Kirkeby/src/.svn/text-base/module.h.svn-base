/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Invert Kirkeby

  module.h

  Angelo Farina - Simone Campanini

**********************************************************************/

#ifndef __AURORA_KIRKEBY_MODULE_H__
#define __AURORA_KIRKEBY_MODULE_H__

// from Audacity
#include <Audacity.h>
#include <effects/Effect.h>
#include <WaveTrack.h>

#include <commdefs.h>
//#include "kirk.h"


class WaveTrack;

class EffectKirkeby: public Effect {

 private:
   TrackListIterator* m_pIter;
   sampleCount m_smpcTracksNo;
   sampleCount m_smpcStart;
   sampleCount m_smpcEnd;
   
   Kirkeby* m_pKirk;

   bool m_bProcess,
        m_bIsStereo;
   
   bool LoadTracks();
   
 public:

   // ---------------- Standard Audacity Effects' methods ----------------
   
   virtual wxString GetEffectName() {
#ifdef __WXDEBUG__       
       return wxString(_("Aurora Invert Kirkeby (debug)..."));
#else       
       return wxString(_("Aurora Invert Kirkeby..."));
#endif
   }

   virtual wxString GetEffectIdentifier() {
      return wxString(_("InvertKirkeby"));
   }

   virtual wxString GetEffectAction() {
      return wxString(_("Kirkeby Inversion"));
   }

   virtual std::set<wxString> GetEffectCategories() {
      std::set<wxString> result;
      result.insert(wxT("http://lv2plug.in/ns/lv2core#AnalyserPlugin"));
      //      result.insert(wxT("http://audacityteam.org/namespace#AnalyzerPlugin"));
      return result;
   }

   virtual int GetEffectFlags() {
      return BUILTIN_EFFECT | PROCESS_EFFECT;
   }   

   // Useful only after PromptUser values have been set. --------------
   //   virtual wxString GetEffectDescription(); 

   virtual bool Init();
   virtual bool PromptUser();
//   virtual bool TransferParameters( Shuttle & shuttle );

 protected:
   virtual bool Process();

 
 public:
    EffectKirkeby();
//   ~EffectKirkeby();

};


#endif // __AURORA_KIRKEBY_MODULE_H__

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

