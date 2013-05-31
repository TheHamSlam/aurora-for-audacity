/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Sine Sweep Signal Generator

  module.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class EffectSineSweepGenerator
\brief The Audacity module front-end for Aurora's SineSweepGenerator class.

  This class is an Audacity module (plug-in) that loads on run time.
  Its core is the instantiation of a TimeHistoryAnalyzer singleton that 
  does all calculations.

*//*******************************************************************/


#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>

#include <afart.h>
#include <afconfig.h>
#include "sswgen.h"
#include "gui.h"
#include "module.h"

//----------------------------------------------------------------------------
// AFStepTimeWarper implementation `as is` from TimeWarper.cpp
//----------------------------------------------------------------------------
double AFStepTimeWarper::Warp(double originalTime) const
{
   return originalTime + ((originalTime > mTStep) ? mOffset : 0.0);
}

AFStepTimeWarper::AFStepTimeWarper(double tStep, double offset)
: mTStep(tStep), mOffset(offset)
{ }

//----------------------------------------------------------------------------
// EffectSineSweepGenerator implementation
//----------------------------------------------------------------------------
void EffectSineSweepGenerator::SelectTracks(bool bStatus)
{
#ifdef __AUDEBUG__
    int n = 0;
#endif
   TrackListIterator iter(mTracks);
   for (Track *t = iter.First(); t; t = iter.Next())
   {
      t->SetSelected(bStatus);
#ifdef __AUDEBUG__
      printf("elsg: toggling track %d (%d)\n", n++, int(bStatus)); fflush(stdout); // ************DEBUG
#endif
   }
}

void EffectSineSweepGenerator::SelectAllTracks()
{
   SelectTracks(true);
}

void EffectSineSweepGenerator::DeselectAllTracks()
{
   SelectTracks(false);
}


bool EffectSineSweepGenerator::Init()
{
#ifdef __AUDEBUG__
    printf("elsg: INIT\n"); fflush(stdout); // ************DEBUG
#endif
    // The very first thing to do!
    m_pSsg = new SineSweepGenerator();
    
    m_pSsg->SetSamplerate(mProjectRate);

    // useful to save presets
    //gPrefs->Read(wxT("/CsPresets/NoiseGen_Duration"), &mDuration, 1L);
    
    return true;
    
}

bool EffectSineSweepGenerator::PromptUser()
{
#ifdef __AUDEBUG__
   printf("elsg: PROMPTUSER\n"); fflush(stdout); 
#endif
   InitArtProvider();

   SineSweepGeneratorDialog dlog(m_pSsg, mParent);
   dlog.CenterOnParent();

   if( !dlog.ShowModal() )  return false;
   
   if(!m_pSsg->Generate()) 
   {
      wxMessageBox(wxT("Something strange occourred.\nCannot generate Sine Sweep Signal."),
                   wxT("Error"),
                   wxOK | wxICON_ERROR);
      delete m_pSsg;
      return false;
   }
   // This should be set to the correct value.
   mDuration = m_pSsg->GetTotalDuration();
   return true;
}

void EffectSineSweepGenerator::BeforeGenerate()
{
#ifdef __AUDEBUG__
   printf("elsg: BEFOREGENERATE\n"); fflush(stdout); 
   printf("elsg: detected %d tracks\n", int(GetNumWaveTracks())); fflush(stdout);
#endif
   // These lines add new tracks if needed
   int existingTracks = GetNumWaveTracks();
   int neededTracks   = m_pSsg->GetNeededTracks();
   
   //If there are selected tracks it's a mess, better deselect all first...
   int i = 1;
   if(existingTracks > 1) 
   {
       DeselectAllTracks();
       i = 0;
   }
   while(i < neededTracks) 
   {  
      WaveTrack *t = mFactory->NewWaveTrack(floatSample, mProjectRate);
      mTracks->Add(t);
      t->SetSelected(true);
      i++;
   }
   // Select all tracks
   i = 1;
   wxString name;
   TrackListIterator iter(mTracks);
   for (Track *t = iter.First(); t; t = iter.Next()) 
   {    
      name.Printf(_("Sweep Channel %d"), i);
      if(m_pSsg->IsControlPulsesSet()) {
          
         if(i == (neededTracks-1)) name = _("Inverse Filter");
         if(i == neededTracks)     name = _("Pulses Channel");     
      } 
      else 
      {    
         if(i == neededTracks) name = _("Inverse Filter");
      }
      t->SetName(name);
      i++;
   }
   
}


//------------------------- Processing methods -------------------------
bool EffectSineSweepGenerator::Process()
{
   // taken `as is` from Audacity`s Generator.cpp to resolve
   // a vc++ linking problem...
   
   if (mDuration < 0.0)
      return false;

   BeforeGenerate();

   // Set up mOutputTracks. This effect needs Track::All for grouping
   this->CopyInputTracks(Track::All);

   // Iterate over the tracks
   bool bGoodResult = true;
   int ntrack = 0;
   TrackListIterator iter(mOutputTracks);
   Track* t = iter.First();

   while (t != NULL)
   {
      if (t->GetKind() == Track::Wave && t->GetSelected()) 
      {
         WaveTrack* track = (WaveTrack*)t;
         
         bool editClipCanMove = true;
         //gPrefs->Read(wxT("/GUI/EditClipCanMove"), &editClipCanMove, true);

         //if we can't move clips, and we're generating into an empty space,
         //make sure there's room.
         if (!editClipCanMove &&
             track->IsEmpty(mT0, mT1+1.0/track->GetRate()) &&
             !track->IsEmpty(mT0, mT0+mDuration-(mT1-mT0)-1.0/track->GetRate()))
         {
             wxMessageBox(_("There is not enough room available to generate the audio"),
                          _("Error"), wxICON_STOP);   
            Failure();
            return false;
         }

         if (mDuration > 0.0)
         {
            // Create a temporary track
            WaveTrack *tmp = mFactory->NewWaveTrack(track->GetSampleFormat(),
                                                    track->GetRate());
            //BeforeTrack(*track);

            // Fill it with data
            if (!GenerateTrack(tmp, *track, ntrack))
               bGoodResult = false;
            else 
            {
               // Transfer the data from the temporary track to the actual one
               tmp->Flush();
               SetTimeWarper(new AFStepTimeWarper(mT0+mDuration, mDuration-(mT1-mT0)));
               bGoodResult = track->ClearAndPaste(mT0, mT1, tmp, true,
                     false, GetTimeWarper());
               delete tmp;
            }

            if (!bGoodResult) 
            {
               Failure();
               return false;
            }
         }
         else
         {
            // If the duration is zero, there's no need to actually
            // generate anything
            track->Clear(mT0, mT1);
         }

         ntrack++;
      }
      else if (t->IsSyncLockSelected()) 
      {
         t->SyncLockAdjust(mT1, mT0 + mDuration);
      }
      // Move on to the next track
      t = iter.Next();
   }

   Success();

   this->ReplaceProcessedTracks(bGoodResult);

   mT1 = mT0 + mDuration; // Update selection.

   return true;
}

bool EffectSineSweepGenerator::GenerateTrack(WaveTrack *tmp, const WaveTrack &track, int ntrack)
{
#ifdef __AUDEBUG__
   printf("elsg: GENERATETRACK\n"); fflush(stdout); // ************DEBUG
#endif
   bool bGoodResult = true;
   //numSamples = track.TimeToLongSamples(mDuration);
   sampleCount numSamples;
   //Filter has different length
   if(ntrack == m_pSsg->GetFilterChannel())       
      numSamples = sampleCount(m_pSsg->GetFilterLength());
   else
      numSamples = sampleCount(m_pSsg->GetBuffersLength());
   
   sampleCount i = 0;
   AFSample *data = new AFSample[tmp->GetMaxBlockSize()];
   sampleCount block = 0;

   while ((i < numSamples) && bGoodResult) 
   {
      block = tmp->GetBestBlockSize(i);
      if (block > (numSamples - i))
         block = numSamples - i;

//       GenerateBlock(data, track, block);
      m_pSsg->FillBlock(data, AFSampleCount(block), AFSampleCount(i), ntrack);

      // Add the generated data to the temporary track
      tmp->Append((samplePtr)data, floatSample, block);
      i += block;

      // Update the progress meter
      if (TrackProgress(ntrack, (double)i / numSamples))
         bGoodResult = false;
      
   }
   tmp->Flush();

   delete[] data;
   return bGoodResult;   
}


void EffectSineSweepGenerator::Failure()
{
   delete m_pSsg;
   wxMessageBox(_("Cannot create signal tracks."), _("Error"), wxOK | wxICON_ERROR);
}

void EffectSineSweepGenerator::Success()
{
   delete m_pSsg;
#ifdef __AUDEBUG__
   printf("elsg: SUCCESS\n"); fflush(stdout); // ************DEBUG
#endif
   /* save last used values
      save duration unless value was got from selection, so we save only
      when user explicitely setup a value
      */
   /*
   if (mT1 == mT0)
      gPrefs->Write(wxT("/CsPresets/NoiseGen_Duration"), mDuration);

   gPrefs->Write(wxT("/CsPresets/NoiseGen_Type"), noiseType);
   gPrefs->Write(wxT("/CsPresets/NoiseGen_Amp"), noiseAmplitude);
   */
}


// ------ Ctors
EffectSineSweepGenerator::EffectSineSweepGenerator()
 : m_pSsg(0), m_pIter(0)
{
#if defined __WXMSW__ || defined __WXGTK__
   mDuration = sDefaultGenerateLen; // taken `as is` from Generator.cpp
#endif
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
		switch(type)
        {
            case ModuleInitialize:
            {
 #ifdef __AUDEBUG__
                fprintf(stderr, "[SineSweepGenerator]: dispatch %d received.\n", int(type));
 #endif
                EffectManager & em = EffectManager::Get();
                em.RegisterEffect(new EffectSineSweepGenerator(), PLUGIN_EFFECT | INSERT_EFFECT );
			}
			break;

		   case ModuleTerminate:
		   case AppInitialized:
		   case AppQuiting:
		   case ProjectInitialized:
		   case ProjectClosing:
		   case MenusRebuilt:
			   //do something
#ifdef __AUDEBUG__
			   fprintf(stderr, "[SineSweepGenerator]: dispatch %d received.\n", int(type));
#endif
			   break;

		   default:
			   //do something
#ifdef __AUDEBUG__
			   fprintf(stderr, "[SineSweepGenerator]: unknown dispatch received.\n");
#endif
			   break;
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

