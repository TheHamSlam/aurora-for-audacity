/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Aurora Convolver

  module.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class EffectAuroraConvolver
\brief The Audacity module front-end for Aurora Convolver class.

  This class is an Audacity module (plug-in) that loads on run time.
  Its core is the instantiation of an AuroraConvolver singleton that 
  does all calculations.

*//*******************************************************************/


#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>

#include <afart.h>
#include <afconfig.h>

#include "gui.h"
#include "module.h"
#include "trprop.h"

//----------------------------------------------------------------------------
// EffectAuroraConvolver implementation
//----------------------------------------------------------------------------

bool EffectAuroraConvolver::LoadTrackData(WaveTrack *wt, int idx, bool is_ir)
{
   sampleCount start;
   sampleCount end;
   
   //Get start and end times from track
   double trackStart = wt->GetStartTime();
   double trackEnd   = wt->GetEndTime();

   //Set the current bounds to whichever left marker is
   //greater and whichever right marker is less:
   double curT0 = mT0 < trackStart? trackStart: mT0;
   double curT1 = mT1 > trackEnd? trackEnd: mT1;

   // Process only if the right marker is to the right of the left marker
   if (curT1 > curT0) {

      //Checks the track rate, samples, minimum, maximum and name
      if(!mAc->CheckSamplerate(wt->GetRate())) return false;
      
      AFSample min, max;
      wt->GetMinMax(&min, &max, curT0, curT1);
      
      //Transform the marker timepoints to samples
      start = wt->TimeToLongSamples(curT0);
      end   = wt->TimeToLongSamples(curT1);

      if(is_ir) {
             
          mAc->SetIrMin(idx, min);
          mAc->SetIrMax(idx, max);
          
          if(mAc->SetIrTrackLength(end - start))
             mAc->InitIrTrack(idx); // curChannel causes errors!
         
          wt->Get( (samplePtr) mAc->GetIrTrack(idx), floatSample, start, mAc->GetIrTrackLength() );
      
      } else {

          if(mAc->SetAudioDataTrackLength(end - start))
             mAc->InitAudioDataTrack(idx); // curChannel causes errors!
             
          wt->Get( (samplePtr) mAc->GetAudioDataTrack(idx), floatSample, start, mAc->GetAudioDataTrackLength() );
      }
   }
   return true;
}

bool EffectAuroraConvolver::Init()
{
#ifdef __AUDEBUG__
    printf("This is INIT\n"); fflush(stdout); // *** DEBUG
#endif

    // The very first thing to do!
    mAc = new AuroraConvolver();
    
    mAc->SetSamplerate(mProjectRate);
    
    // ------------- Select tracks to process
    int nTracks = GetNumWaveTracks();
    if(nTracks < 2)
    {
      wxMessageBox(_("Too few tracks for convolution process (at least two needed)!"), 
                   _("Error"), wxOK | wxICON_ERROR);
      delete mAc; mAc = 0;
      return false;
   }
   
   // ------------------ Prepare track info list ---------------
   AFTrackProperties atp(nTracks);
   AFTrackInfoItem trinfo;
   
   this->CopyInputTracks(); // Set up mOutputTracks.
   
   TrackListIterator iter(mOutputTracks);
   WaveTrack *waveTrack = (WaveTrack*)(iter.First()); 
   
   int curTrackNum = 0;
   while (waveTrack != NULL) { 
      
      trinfo.SetIndex(curTrackNum);
      trinfo.SetName(waveTrack->GetName());
      trinfo.SetChannel(waveTrack->GetChannel());
      atp.AddTrackInfoItem(trinfo);
#ifdef __AUDEBUG__
      printf("Added: %s, idx:    %d chnl: %d\n", (const char *)trinfo.GetName().ToAscii(), 
                trinfo.GetIndex(), trinfo.GetChannel()); fflush(stdout); // *** DEBUG
#endif            
      waveTrack = (WaveTrack*)(iter.Next());
      curTrackNum++;
   }   
   // ------------------ end of Prepare track info list ---------------

   // Gui stuffs
   InitArtProvider();
   
   // Show Track Selector dialog
   AuroraTrackSelectorDialog dlg(mParent, mAc, &atp);
   
   dlg.CenterOnParent();   
   if(!dlg.ShowModal())
   {
       delete mAc; mAc = 0;
       return false;
   }
   
   mAc->SetIrMatrixDimensions(atp.GetFilterRowsCount(), atp.GetAudioDataRowsCount());
   
   AFTrackInfoItem *tinfo;
   
   // ---------- get filters --------------
   int idx = 0;
   while(idx <  atp.GetFilterRowsCount())
   {
#ifdef __AUDEBUG__
      printf("module: outerloop %d)....\n", idx); fflush(stdout); // **** DEBUG
#endif
      waveTrack = (WaveTrack*)(iter.First()); 
      curTrackNum = 0;
      while (waveTrack != NULL) { 

#ifdef __AUDEBUG__
         printf("module: innerloop %d)....\n", curTrackNum); fflush(stdout); // **** DEBUG
#endif
         tinfo = atp.GetTrackInfoItem(curTrackNum);
         if(tinfo->IsIr() && (tinfo->GetRow() == idx))
         {
            if(!LoadTrackData(waveTrack, idx, true))
            {     
               wxMessageBox(_("Sample rate mismatch or error copying data from workspace!!"), 
                            _("Error"), wxOK | wxICON_ERROR);
               delete mAc; mAc = 0;
               return false;
            }
         }
         //Iterate to the next track
         waveTrack = (WaveTrack*)(iter.Next());
         curTrackNum++;
      }
      idx++;
   }
   
   // ---------- get audiodata --------------
   idx = 0;
   while(idx < atp.GetAudioDataRowsCount())
   {
#ifdef __AUDEBUG__   
      printf("module: outerloop %d)....\n", idx); fflush(stdout); // **** DEBUG
#endif
      waveTrack = (WaveTrack*)(iter.First()); 
      curTrackNum = 0;
      while (waveTrack != NULL)
      {
#ifdef __AUDEBUG__
         printf("module: innerloop %d)....\n", curTrackNum); fflush(stdout); // **** DEBUG
#endif
         tinfo = atp.GetTrackInfoItem(curTrackNum);
         
         if(tinfo->IsAudioData() && (tinfo->GetRow() == idx))
         {
            if(!LoadTrackData(waveTrack, idx, false))
            {     
               wxMessageBox(_("Sample rate mismatch or error copying data from workspace!!"), 
                            _("Error"), wxOK | wxICON_ERROR);
               delete mAc; mAc = 0;
               return false;
            }
         }
         
         //Iterate to the next track
         waveTrack = (WaveTrack*)(iter.Next());
         curTrackNum++;
      }
      idx++;
   }

   // if ir length is bigger than audiodata length, there should be some problems...
//    if(mAc->GetIrTrackLength() > mAc->GetAudioDataTrackLength()) {     
//       wxMessageBox(_("IR is longer than audio data vector!!\nCannot proceed."), 
//                    _("Error"), wxOK | wxICON_ERROR);
//       delete mAc;
//       return false;
//    }
#ifdef __AUDEBUG__
   printf("exiting INIT\n"); fflush(stdout);
#endif
   return true;
}

bool EffectAuroraConvolver::PromptUser()
{
#ifdef __AUDEBUG__
   printf("This is PROMPTUSER\n"); fflush(stdout); // *** DEBUG
#endif
   AuroraConvolverDialog dlog(mParent, mAc);
   dlog.CenterOnParent();

   if( !dlog.ShowModal() )
   {
      ::wxMessageBox(wxT("Convolution calculation aborted."),
                     wxT("Aurora Convolver"),
                     wxOK | wxICON_INFORMATION);
      delete mAc; mAc = 0;
      return false;
   }
   return true;
}

//------------------------- Processing methods -------------------------
bool EffectAuroraConvolver::Process()
{
#ifdef __AUDEBUG__
   printf("This is PROCESS\n"); fflush(stdout); // *** DEBUG
#endif

   // Get it big!
   if(!mAc->Calculate())
   {
      delete mAc; mAc = 0;
      return false;
   }
   //If everything goes right, store gain and whatever...
   mAc->StoreConfigurationValues();
   
   // Make room for calculated vectors
   DeselectAllTracks();
   
   int ch = 0;  
   wxString name;
   while(ch < mAc->GetIrRows())
   {
      WaveTrack *t = mFactory->NewWaveTrack(floatSample, mProjectRate);
      t->Append((samplePtr)mAc->GetOutputDataTrack(ch), floatSample, 
                           mAc->GetOutputTrackLength() );
      t->Flush();
      
      name.Printf(_("Convolved %d"), ch+1);
      t->SetName(name);
      
      mTracks->Add(t);
      t->SetSelected(true);
      ch++;
   }   
   delete mAc; mAc = 0;
   
   return true;
}

void EffectAuroraConvolver::SelectTracks(bool status)
{
   TrackListIterator iter(mTracks);
   for (Track *t = iter.First(); t; t = iter.Next())
   {
      t->SetSelected(status);
   }
}

void EffectAuroraConvolver::SelectAllTracks()
{
   SelectTracks(true);
}

void EffectAuroraConvolver::DeselectAllTracks()
{
   SelectTracks(false);
}

// ------ Ctors
EffectAuroraConvolver::EffectAuroraConvolver()
 : mAc(0)
{ }


EffectAuroraConvolver::~EffectAuroraConvolver()
{
   if(mAc != 0) delete mAc; // not sure if needed
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
	extern DLL_API int ModuleDispatch(ModuleDispatchTypes type);
	
	const wxChar* GetVersionString()
	{
       if(gPrefs != 0)
           gPrefs->Read(wxT("/Version"), &g_wxszVersion);

       return g_wxszVersion.c_str();
	}
	

   int ModuleDispatch(ModuleDispatchTypes type)
   {
      if (type == ModuleInitialize)
      {
         EffectManager & em = EffectManager::Get();
         em.RegisterEffect(new EffectAuroraConvolver(), BUILTIN_EFFECT | PROCESS_EFFECT );
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

