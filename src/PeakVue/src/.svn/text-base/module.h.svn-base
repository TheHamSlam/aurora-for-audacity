/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  PeakVue

  module.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_PEAKVUE_MODULE_H__
#define __AURORA_PEAKVUE_MODULE_H__

// from Audacity
#include <Audacity.h>
#include <effects/Effect.h>
#include <WaveTrack.h>

#include <commdefs.h>
#include <afconfig.h>

#include "gui.h"
#include "data.h"
#include "peakvue.h"


class WaveTrack;

class EffectPeakVue: public Effect
{

 private:
   AFConfig* m_pCfg;
   bool      m_bProcess;

   PVDataShuttle*  m_pDataShuttle;

   void AddProcessedTracks();
   void LoadAudioData(const int selectedIdx);
   void GetTrackLabels();

 public:

   bool DoAnalysis(const int selectedIdx);

   // ---------------- Standard Audacity Effects' methods ----------------
   
   virtual wxString GetEffectName() {
#ifdef __WXDEBUG__
      return wxString(wxT("Aurora Peak Analysis (debug)..."));
#else
      return wxString(_("Aurora Peak Analysis..."));
#endif
   }

   virtual wxString GetEffectIdentifier() {
      return wxString(_("AuroraPeakAnalysis"));
   }

   virtual wxString GetEffectAction() {
      return wxString(_("Aurora Peak Analysis"));
   }

   virtual std::set<wxString> GetEffectCategories() {
      std::set<wxString> result;
      result.insert(wxT("http://lv2plug.in/ns/lv2core#AnalyserPlugin"));
      //      result.insert(wxT("http://audacityteam.org/namespace#AnalyzerPlugin"));
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
   virtual void End();
 
 public:
    EffectPeakVue();

};


#endif // __AURORA_PEAKVUE_MODULE_H__

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

