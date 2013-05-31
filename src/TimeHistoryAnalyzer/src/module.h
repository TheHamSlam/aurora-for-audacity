/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  module.h

  Angelo Farina - Simone Campanini

**********************************************************************/

#ifndef __AURORA_ITUP56_MODULE_H__
#define __AURORA_ITUP56_MODULE_H__

// from Audacity
#include <Audacity.h>
#include <effects/Effect.h>
#include <WaveTrack.h>

#include "track.h"
#include "than.h"


//----------------------------------------------------------------------------
// EffectTimeHistoryAnalyzer
//----------------------------------------------------------------------------
class WaveTrack;

class EffectTimeHistoryAnalyzer: public Effect
{
 private:
   TimeHistoryAnalyzer *m_pThan;

   size_t  m_unTracksCount;

   TArrayOfTHASignalAudioTrack      m_aSignalTrackList;
   TArrayOfTHACalibrationAudioTrack m_aCalibrationTrackList;


   int  GetFilterIdFromName(wxString& wxszName);
   int  GetTrackIndexFromName(wxString& wxszName);
   bool SetTrackListItem(int* anTrackList, const int nIdx, wxString& wxszName);

 public:
   size_t GetTracksCount() const { return m_unTracksCount; }
   void   SetTracksNamesArray(wxArrayString& awxszTrackNames);

   TArrayOfTHACalibrationAudioTrack* GetCalibrationTrackList() { return  &m_aCalibrationTrackList; }
   void ClearCalibrationTrackList() { if(m_aCalibrationTrackList.GetCount() > 0)
	                                      m_aCalibrationTrackList.Clear(); }
   void AddCalibrationTrackListItem(const int nChnl, wxString& wxszName, const double dbRefValue);

   TArrayOfTHASignalAudioTrack* GetSignalTrackList() { return  &m_aSignalTrackList; }
   void ClearSignalTrackList() { if(m_aSignalTrackList.GetCount() > 0)
	                                m_aSignalTrackList.Clear(); }
   void AddSignalTrackListItem(const int nChnl, wxString& wxszName, wxString& wxszFilter, const double dbFullscale);

 private:
   bool LoadTrackData(AFAudioTrackBase* pTrack, const int nTrackIdx);
   void AppendTracksToWorkspace();

 public:
    bool DoFullscaleCalibration(double* pdbFullscale);

    TimeHistoryAnalyzer::TResults* DoAnalysis();

   // ---------------- Standard Audacity Effects' methods ----------------
   
   virtual wxString GetEffectName() {
#ifdef __WXDEBUG__
      return wxString(wxT("Aurora Time History Analyzer (debug)..."));
#else      
      return wxString(wxT("Aurora Time History Analyzer..."));
#endif      
   }

   virtual wxString GetEffectIdentifier() {
      return wxString(wxT("ITUP56"));
   }

   virtual wxString GetEffectAction() {
      return wxString(wxT("TimeHistoryAnalyzer"));
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

 protected:
   virtual bool Process();
   virtual void End();
 
 public:
    EffectTimeHistoryAnalyzer();

};


#endif // __AURORA_ITUP56_MODULE_H__

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



