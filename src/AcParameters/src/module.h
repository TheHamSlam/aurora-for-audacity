/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters

  module.h

  Angelo Farina - Simone Campanini

**********************************************************************/

#ifndef __AURORA_ACPARAM_MODULE_H__
#define __AURORA_ACPARAM_MODULE_H__

class WaveTrack;

//-----------------------------------------------------------------------------
// EffectAcParameters
//
/// \brief The Acoustical Parameters module main class.
//
/// This class is the interface with Audacity, so it is
/// derived from Effect and implements all its methods.
/// Its core is the instantiation of a AcParameter object that does
/// all the calculations.
/// See \sa AFAcousticalParameters to know what exactly
/// it computes.
//-----------------------------------------------------------------------------
class EffectAcParameters: public Effect 
{

 private:
	/// Pointer to Acoustical Parameter calculation class
   AcParameters*        m_pAp;

   /// Pointer to Aurora configuration file manager
   AFConfig*            m_pCfg;

   /// Pointer to Acoustical Parameters data export manager
   AcParametersExports* m_pDataExport;

   /// Process function return value
   bool                 m_bProcess;
   bool                 m_bAppendDataToFile;

   /// The array of audio datas: every item should be a Room
   /// Impulse Response.
   TArrayOfAPAudioTracks m_aAudioData;

   /// Append filtered/processed audio data to Audacity workspace
   /// as new track(s).
   void AddProcessedTracks();

   /// Load audio data from Audacity workspace.
   void LoadTracks();

 public:
   /// Returns a pointer to the audio data array.
   TArrayOfAPAudioTracks* GetTracksArray() { return &m_aAudioData; }

   /// Set to true if the parameters table has to be appended to a
   /// results file.
   void SetAppendDataToFile(const bool bValue) { m_bAppendDataToFile = bValue; }

   // ---------------- Standard Audacity Effects' methods ----------------
   
   virtual wxString GetEffectName() {
#ifdef __WXDEBUG__
      return wxString(wxT("Aurora Acoustical Parameters (debug)..."));
#else
      return wxString(_("Aurora Acoustical Parameters..."));
#endif
   }

   virtual wxString GetEffectIdentifier() {
      return wxString(_("AuroraAcParam"));
   }

   virtual wxString GetEffectAction() {
      return wxString(_("Aurora Acoustical Parameters Evaluation"));
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
    EffectAcParameters();
//   ~EffectAcParameters();

};


#endif // __AURORA_ACPARAM_MODULE_H__

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

