/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  module.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class EffectAuroraSTI
\brief The Audacity module front-end for Aurora STI class.

  This class is an Audacity module (plug-in) that loads on run time.
  Its core is the instantiation of an AuroraSTI singleton that 
  does all calculations.

*//*******************************************************************/


#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>
#include <WaveClip.h>

#include <afart.h>
#include <afconfig.h>
#include <gpfuncts.h>
#include "gui.h"
#include "module.h"
#include "track.h"

//----------------------------------------------------------------------------
// EffectAuroraSTI implementation
//----------------------------------------------------------------------------

bool EffectAuroraSTI::LoadTrackData(STIAudioTrack* pTrack, const int nCh, const int nTrackIdx)
{
   
   TrackListIterator iter(mOutputTracks);
   WaveTrack* pWt = (WaveTrack*)(iter.First()); 

   //Checks the track rate, samples, minimum, maximum and name
   if(m_pAuSti->GetSamplerate() != pWt->GetRate())
   {
       ::wxMessageBox(wxT("Sample rate mismatch."),
                      wxT("Error"),
                      wxOK | wxICON_ERROR);
       return false;
   }

   //Get start and end times from track
   double trackStart = pWt->GetStartTime();
   double trackEnd   = pWt->GetEndTime();

   //Set the current bounds to whichever left marker is
   //greater and whichever right marker is less:
   double curT0 = mT0 < trackStart? trackStart: mT0;
   double curT1 = mT1 > trackEnd? trackEnd: mT1;

   printf("[Track %d] -> trackStart: %d, trackEnd: %d, mT0; %d, mT1: %d\n", nTrackIdx, (int)trackStart, (int)trackEnd, (int)mT0, (int)mT1);
   fflush(stdout);

   sampleCount start = 0,
		       end   = 0;

   WaveClipList::compatibility_iterator it;
   int nClips = 0;
   WaveClip* pClip;
   sampleCount smpcClipEnd;
   
   // Process only if the right marker is to the right of the left marker
   if (curT1 > curT0) 
   {
       int currTrack = 0;
       while(currTrack < nTrackIdx)
       {
           currTrack++;
           pWt = (WaveTrack*)(iter.Next());       
       }

       // clip experiments...
       for (it=pWt->GetClipIterator(); it; it=it->GetNext(), nClips++)
       {
    	   pClip = it->GetData();
       }

      AFSample min, max;
      pWt->GetMinMax(&min, &max, curT0, curT1);
      
      //Transform the marker timepoints to samples
      start = pWt->TimeToLongSamples(curT0);
      end   = pWt->TimeToLongSamples(curT1);

      if(nClips == 1)
      {
    	  // If there is only one clip, we can trim it, instead
    	  // of using the entire selection length...
          it = pWt->GetClipIterator();
          pClip = it->GetData();
          smpcClipEnd = pClip->GetEndSample();
          end = ((end > smpcClipEnd) && (start < smpcClipEnd)) ? smpcClipEnd : end;
      }
      pTrack->SetTrackLength(end-start, true, nCh);
      pWt->Get( (samplePtr) pTrack->GetTrack(nCh), floatSample, start, end-start );
   }
   
   return true;
}

bool EffectAuroraSTI::DoFullscaleCalibration(const bool bIsStereo)
{
    int nChnls = bIsStereo ? 2 : 1;
    STIAudioTrack* pCalibrationSignal = new STIAudioTrack(nChnls, mProjectRate);
    
    for(int nCh = 0; nCh < nChnls; nCh++)
    {
        if(!LoadTrackData(pCalibrationSignal, nCh, m_anCalibrationTracksIdx[nCh]-1))
        {
            delete pCalibrationSignal;
            return false;
        }
        m_pAuSti->CalibrateFullscale(pCalibrationSignal, nCh);
    }
    delete pCalibrationSignal;
    return true;
}

bool EffectAuroraSTI::DoSNRatioCalculation(const bool bIsStereo)
{
    int nChnls = bIsStereo ? 2 : 1;
    STIAudioTrack* pNoise  = new STIAudioTrack(nChnls, mProjectRate);
    STIAudioTrack* pSignal = new STIAudioTrack(nChnls, mProjectRate);
/*
    mProgress = new ProgressDialog(wxString(wxT("Octave Spectrum Calculation")),
                                   wxEmptyString,
                                   pdlgHideStopButton);
    m_pAuSti->SetProgressDlg(mProgress);
*/
    m_pAuSti->InitProgressMeter(nChnls, 12, wxString(wxT("Octave Spectrum Calculation")));
    
    for(int nCh = 0; nCh < nChnls; nCh++)
    {
        if( !LoadTrackData(pSignal, nCh, m_anSignalTracksIdx[nCh]-1) ||
            !LoadTrackData(pNoise, nCh, m_anNoiseTracksIdx[nCh]-1)   ||
            !m_pAuSti->StoreSpectrums(pSignal, pNoise, nCh) )
        {
            delete pNoise; delete pSignal;
            m_pAuSti->DestroyProgressMeter();
//            delete mProgress; mProgress = 0;
            return false;
        }
        m_pAuSti->UpdateOverallProgressMeter(nCh);
    }
    delete pNoise; delete pSignal;
    m_pAuSti->DestroyProgressMeter();
//    delete mProgress; mProgress = 0;
    return true;
}

bool EffectAuroraSTI::DoSTICalculation()
{
    int nChnls = m_bIsStereo ? 2 : 1;
    STIAudioTrack* pIR = new STIAudioTrack(nChnls, mProjectRate);
    
    m_pAuSti->InitProgressMeter(nChnls, 7, wxString(wxT("Aurora - Speech Transmission Index")));

    for(int nCh = 0; nCh < nChnls; nCh++)
    {    
        if(!LoadTrackData(pIR, nCh, m_anIrTracksIdx[nCh]-1))
        {
            delete pIR;
            m_pAuSti->DestroyProgressMeter();
            return false;
        }
        m_pAuSti->CalculateMatrix(pIR, nCh);    
        m_pAuSti->UpdateOverallProgressMeter(nCh);
    }
    delete pIR;
    m_pAuSti->DestroyProgressMeter();

    return true;
}
   
bool EffectAuroraSTI::Init()
{
    if(!m_awxszTrackNames.IsEmpty())
        m_awxszTrackNames.Clear();

    // The very first thing to do!
    m_pAuSti = new AuroraSTI(&m_Cfg);
    
    m_pAuSti->ReadConfigurationValues();

    m_pAuSti->SetSamplerate(mProjectRate);

    this->CopyInputTracks(); // Set up mOutputTracks.       

   return true;
}

bool EffectAuroraSTI::PromptUser()
{
    // ------------------ Prepare track info list ---------------
    wxString wxszTrackName;
    wxString wxszChnlName;
    
    TrackListIterator iter(mOutputTracks);
    WaveTrack* pWt = (WaveTrack*)(iter.First()); 
    
    while (pWt != NULL) 
    {  
        wxszTrackName = pWt->GetName();
        ::AuroraGetAudacityChannelName(wxszChnlName, pWt->GetChannel());
        wxszTrackName << wxT(" [") << wxszChnlName << wxT("]");
        m_awxszTrackNames.Add(wxszTrackName);
        pWt = (WaveTrack*)(iter.Next());
    }   
    // ------------------ end of Prepare track info list ---------------

    // Gui stuffs
    InitArtProvider();
    
    // Show Track Selector dialog
    STISetupDialog* pDlg = new STISetupDialog(mParent, m_pAuSti, this, &m_Cfg);
    pDlg->CenterOnParent();   
    if(!pDlg->ShowModal())
    {
        delete m_pAuSti; m_pAuSti = 0;
        pDlg->Destroy();
        return false;
    }
    pDlg->Destroy();

    m_pAuSti->StoreConfigurationValues(); // Save STI environment

    // I would do all these calculation in Process() but on GTK
    // the ProgressMeter always crashes!

    if( !IsIrTrackSet(CH_LEFT) ) // At least left channel must be set
         return false;

     m_bIsStereo = false;
     if( AreIrTracksSet() )
         m_bIsStereo = true;

     DoSTICalculation();

    return true;
}

//------------------------- Processing methods -------------------------
bool EffectAuroraSTI::Process()
{
/*
    if( !IsIrTrackSet(CH_LEFT) ) // At least left channel must be set
        return false;

    m_pAuSti->SetProgressDlg(mProgress);
    
    m_bIsStereo = false;
    if( AreIrTracksSet() )
        m_bIsStereo = true;

    DoSTICalculation();
*/
    return false; // no modification on waveform in the
                  // workspace, so in fact no Process()
                  // has been done.
}

void EffectAuroraSTI::End()
{
    //TODO: In this window there is a problem that hangs Audacity
    STIShowDialog* pDlg = new STIShowDialog(mParent, m_pAuSti, m_bIsStereo);
    pDlg->CenterOnParent();
    pDlg->ShowModal();

    pDlg->Destroy();
    delete m_pAuSti; m_pAuSti = 0;
}

void EffectAuroraSTI::SelectTracks(bool status)
{
   TrackListIterator iter(mTracks);
   for (Track *t = iter.First(); t; t = iter.Next())
   {
      t->SetSelected(status);
   }
}


void EffectAuroraSTI::SelectAllTracks()
{
   SelectTracks(true);
}

void EffectAuroraSTI::DeselectAllTracks()
{
   SelectTracks(false);
}

// ------ Ctors
EffectAuroraSTI::EffectAuroraSTI()
 : m_pAuSti(0),
   m_bIsStereo(false)
{ 
    m_anCalibrationTracksIdx [0] = 0;
    m_anNoiseTracksIdx       [0] = 0;
    m_anSignalTracksIdx      [0] = 0;
    m_anIrTracksIdx          [0] = 0;
    m_anCalibrationTracksIdx [1] = 0;
    m_anNoiseTracksIdx       [1] = 0;
    m_anSignalTracksIdx      [1] = 0;
    m_anIrTracksIdx          [1] = 0;    
}

//----------------------------------------------------------------------------
// Module callback
//----------------------------------------------------------------------------
extern "C"
{
   #ifdef _MSC_VER
      #define DLL_API _declspec(dllexport)
   #else
      #define DLL_API __attribute__ ((visibility("default")))
   #endif

// The current (5/12/2011) Audacity binary release
// doesn't include the string version test

    wxString g_wxszVersion;

	extern DLL_API const wxChar* GetVersionString();	

	const wxChar* GetVersionString()
	{
       if(gPrefs != 0)
           gPrefs->Read(wxT("/Version"), &g_wxszVersion);

       return g_wxszVersion.c_str();
    }

   extern DLL_API int ModuleDispatch(ModuleDispatchTypes type);

   int ModuleDispatch(ModuleDispatchTypes type)
   {
      if (type == ModuleInitialize)
      {
         EffectManager & em = EffectManager::Get();
         em.RegisterEffect(new EffectAuroraSTI(), BUILTIN_EFFECT | ANALYZE_EFFECT );
      }

      return 1;
   }
};



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

