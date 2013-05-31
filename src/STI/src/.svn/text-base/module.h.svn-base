/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  module.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_STI_MODULE_H__
#define __AURORA_STI_MODULE_H__

// from Audacity
#include <Audacity.h>
#include <effects/Effect.h>
#include <WaveTrack.h>

#include <wxcmn.h>
#include <wx/dynarray.h>
#include <afconfig.h>

#include "sti.h"
#include "track.h"

class WaveTrack;

class EffectAuroraSTI: public Effect 
{
 private:
    AuroraSTI*   m_pAuSti;
    bool         m_bIsStereo;

    wxArrayString  m_awxszTrackNames;

    int  m_anCalibrationTracksIdx [2],
         m_anSignalTracksIdx [2],
         m_anNoiseTracksIdx [2],
         m_anIrTracksIdx    [2];
    
    AFConfig m_Cfg;

  public:
    wxString& GetTrackName(const int nIdx) const { return m_awxszTrackNames.Item(nIdx); }
    wxArrayString* GetTrackNamesArray() { return &m_awxszTrackNames; }

    bool IsCalibrationTrackSet(const int nChnl) const { return (m_anCalibrationTracksIdx [nChnl] != 0); }
    bool IsSignalTrackSet(const int nChnl)      const { return (m_anSignalTracksIdx [nChnl] != 0); }
    bool IsNoiseTrackSet(const int nChnl)       const { return (m_anNoiseTracksIdx [nChnl] != 0); }
    bool IsIrTrackSet(const int nChnl)          const { return (m_anIrTracksIdx [nChnl] != 0); }
    
    bool AreCalibrationTracksSet() const { return (m_anCalibrationTracksIdx[CH_LEFT] != 0) && 
                                                  (m_anCalibrationTracksIdx[CH_RIGHT] != 0); }
    bool AreIrTracksSet()          const { return (m_anIrTracksIdx[CH_LEFT] != 0) && 
                                                  (m_anIrTracksIdx[CH_RIGHT] != 0); }
    bool AreSignalAndNoiseSet(const int nChnl) const { return (m_anSignalTracksIdx[nChnl] != 0) && 
                                                              (m_anNoiseTracksIdx[nChnl] != 0); }
    
    int GetCalibrationTrackIdx(const int nChnl) const { return m_anCalibrationTracksIdx [nChnl]; }
    int GetSignalTrackIdx     (const int nChnl)      const { return m_anSignalTracksIdx [nChnl]; }
    int GetNoiseTrackIdx      (const int nChnl)       const { return m_anNoiseTracksIdx [nChnl]; }
    int GetIrTrackIdx         (const int nChnl)          const { return m_anIrTracksIdx [nChnl]; }
    
    void SetCalibrationTrackIdx(const int nChnl, const int nValue) { m_anCalibrationTracksIdx [nChnl] = nValue; }
    void SetSignalTrackIdx     (const int nChnl, const int nValue)      { m_anSignalTracksIdx [nChnl] = nValue; }
    void SetNoiseTrackIdx      (const int nChnl, const int nValue)       { m_anNoiseTracksIdx [nChnl] = nValue; }
    void SetIrTrackIdx         (const int nChnl, const int nValue)          { m_anIrTracksIdx [nChnl] = nValue; }
    
  public:
    void SetProgressMeterMessage(const wxString& wxszMsg);
    bool UpdateProgressMeter(const int nStep, const int nTotal);

  private:
    bool LoadTrackData(STIAudioTrack* pTrack, const int nCh, const int nTrackIdx);
   
    void SelectTracks(bool status);
    void SelectAllTracks();
    void DeselectAllTracks();
   
 public:
    bool DoFullscaleCalibration(const bool bIsStereo = false);    
    bool DoSNRatioCalculation(const bool bIsStereo = false);
    bool DoSTICalculation();
   
   // ---------------- Standard Audacity Effects' methods ----------------
   
   virtual wxString GetEffectName() 
   {
#ifdef __WXDEBUG__
      return wxString(wxT("Aurora STI (debug)..."));
#else
      return wxString(wxT("Aurora STI..."));
#endif
   }

   virtual wxString GetEffectIdentifier() 
   {
      return wxString(_("STI"));
   }

   virtual wxString GetEffectAction() 
   {
      return wxString(_("Calcuating Speech Transmission Index..."));
   }

   virtual std::set<wxString> GetEffectCategories() 
   {
      std::set<wxString> result;
      result.insert(wxT("http://lv2plug.in/ns/lv2core#AnalyserPlugin"));
      return result;
   }

   virtual int GetEffectFlags() 
   {
      return BUILTIN_EFFECT | ANALYZE_EFFECT;
   }   

   // Useful only after PromptUser values have been set. --------------
   //   virtual wxString GetEffectDescription(); 
    
   virtual bool Init();
   virtual bool PromptUser();
//   virtual bool TransferParameters( Shuttle & shuttle );

 protected:
    //In this module, process doesn't do anything, so it can be
    //skipped with this trick:
    //virtual bool CheckWhetherSkipEffect() { return true; }

   virtual bool Process();
   virtual void End();
    
 public:     
    EffectAuroraSTI();
    //~EffectAuroraSTI();

};


#endif // __AURORA_STI_MODULE_H__

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

