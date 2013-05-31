/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Sine Sweep Signal Sweep Generator

  module.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_SSWGEN_MODULE_H__
#define __AURORA_SSWGEN_MODULE_H__

#include <Audacity.h>

#include <effects/Effect.h>
#include <WaveTrack.h>

#include <effects/TimeWarper.h>

#include "sswgen.h"


class WaveTrack;

// taken `as is` from TimeWarper.cpp
class AFStepTimeWarper : public TimeWarper
{
private:
   double mTStep;
   double mOffset;
public:
   AFStepTimeWarper(double tStep, double offset);
   virtual double Warp(double originalTime) const;
};

class EffectSineSweepGenerator: public Effect
{
 private:
   SineSweepGenerator* m_pSsg;
   TrackListIterator*  m_pIter; 

   double mDuration;  // taken `as is` from Generator.cpp

   void SelectTracks(bool bStatus);
   void SelectAllTracks();
   void DeselectAllTracks();
    
 public:

   // ---------------- Standard Audacity Effects' methods ----------------
   
   wxString GetEffectName() {
#ifdef __WXDEBUG__
      return wxString(_("Aurora Sine Sweep Generator (debug)..."));
#else      
      return wxString(_("Aurora Sine Sweep Generator..."));
#endif
   }

   wxString GetEffectIdentifier() {
      return wxString(_("AuroraSineSweepGenerator"));
   }

   wxString GetEffectAction() {
      return wxString(_("Aurora Sinusoidal Sweep Generator"));
   }

   std::set<wxString> GetEffectCategories() {
      std::set<wxString> result;
      result.insert(wxT("http://lv2plug.in/ns/lv2core#GeneratorPlugin"));
      return result;
   }

   int GetEffectFlags() {
      return BUILTIN_EFFECT | INSERT_EFFECT;
      //return PLUGIN_EFFECT | INSERT_EFFECT;
   }   

   // Useful only after PromptUser values have been set. --------------
   //   wxString GetEffectDescription(); 
protected:
   bool Init();
   bool PromptUser();
// bool TransferParameters( Shuttle & shuttle );
   void BeforeGenerate();
   bool GenerateTrack(WaveTrack *tmp, const WaveTrack &track, int ntrack);
   void Failure();
   void Success();
   bool Process(); // taken `as is` from Generator.cpp

 public:
    EffectSineSweepGenerator();
};


#endif // __AURORA_SSWGEN_MODULE_H__

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

