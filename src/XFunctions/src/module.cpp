/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  module.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class EffectXFunctions
\brief The Audacity module front-end for Aurora Convolver class.

  This class is an Audacity module (plug-in) that loads on run time.
  Its core is the instantiation of an XFunctions singleton that 
  does all calculations.

*//*******************************************************************/


#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>

#include <afart.h>
#include "gui.h"
#include "module.h"

//----------------------------------------------------------------------------
// EffectXFunctions implementation
//----------------------------------------------------------------------------

bool EffectXFunctions::Init()
{
   printf("This is INIT\n"); fflush(stdout); // *** DEBUG
    
   // The very first thing to do!
   m_pXf = new XFunctions(&m_Cfg);
    
   m_pXf->SetSamplerate(mProjectRate);
   
   int nTracks = GetNumWaveTracks();
   if(nTracks != 2)
   {
      //For what reason one should analyze more than 8 tracks...    
      ::wxMessageBox(wxT("XFunctions works with two (2) tracks.\nNo less, no more."),
                   wxT("Error"), wxOK | wxICON_ERROR);
      delete m_pXf;
      return false;
   }

   this->CopyInputTracks(); // Set up mOutputTracks.
   //bool bGoodResult = true;

   sampleCount start,
               end;
   int     curTrackNum;
   double  curT0,
           curT1;
   //int     curChannel;

   TrackListIterator *iter = new TrackListIterator(mOutputTracks);

   WaveTrack * waveTrack = (WaveTrack*)(iter->First()); 
   curTrackNum = 0;
   while (waveTrack != NULL)
   { 
      //Get start and end times from track
      double trackStart = waveTrack->GetStartTime();
      double trackEnd   = waveTrack->GetEndTime();

      //Set the current bounds to whichever left marker is
      //greater and whichever right marker is less:
      curT0 = mT0 < trackStart? trackStart: mT0;
      curT1 = mT1 > trackEnd? trackEnd: mT1;


      // Process only if the right marker is to the right of the left marker
      if (curT1 > curT0) 
      {
          //Get current channel
          //curChannel = waveTrack->GetChannel();
          
         //Transform the marker timepoints to samples
         start = waveTrack->TimeToLongSamples(curT0);
         end   = waveTrack->TimeToLongSamples(curT1);
         m_pXf->SetInputVectorLength(end - start, curTrackNum);

         //m_pXf->AddTrackName(waveTrack->GetName());
         waveTrack->Get( (samplePtr) m_pXf->GetInputVector(curTrackNum), floatSample,
                         start, m_pXf->GetInputVectorsLength() );
      }

      //Iterate to the next track
      waveTrack = (WaveTrack*)(iter->Next());
      curTrackNum++;
   }

#ifdef __AUDEBUG__
   printf("exiting INIT\n"); fflush(stdout);
#endif
   return true;
}

bool EffectXFunctions::PromptUser()
{
#ifdef __AUDEBUG__
   printf("This is PROMPTUSER\n"); fflush(stdout); // *** DEBUG
#endif
   InitArtProvider();

   XFunctionsDialog dlog(mParent, m_pXf);
   dlog.CenterOnParent();

   if( !dlog.ShowModal() ) 
   {
      delete m_pXf;
      return false;
   }
   return true;
}

//------------------------- Processing methods -------------------------
bool EffectXFunctions::Process()
{
#ifdef __AUDEBUG__
   printf("This is PROCESS\n"); fflush(stdout); // *** DEBUG
#endif

   // Get it big!
   if(!m_pXf->Process())
   {   
      delete m_pXf;
      return false;
   }
   //If everything goes right, store gain and whatever...
   m_pXf->StoreConfigurationValues();
   
   XFunctionsShowDialog dlog(mParent, m_pXf, &m_Cfg);
   dlog.CenterOnParent();
   if(dlog.ShowModal()) 
   {
      // Make room for calculated vectors
      DeselectAllTracks();

      int ch = 0;  
      wxString name;
      while(ch < m_pXf->GetChannelsToExport())
      {      
          WaveTrack *t = mFactory->NewWaveTrack(floatSample, mProjectRate);
          t->Append((samplePtr)m_pXf->GetResultsVector(ch), floatSample,
                                m_pXf->GetResultsVectorLength() );
          t->Flush();
           
          t->SetName(m_pXf->GetResultVectorLabel(ch));
            
          mTracks->Add(t);
          t->SetSelected(true);
          ch++;
      }   
   }
   //delete m_pXf;
   
   return true;
}

void EffectXFunctions::SelectTracks(bool status)
{
   TrackListIterator iter(mTracks);
   for (Track *t = iter.First(); t; t = iter.Next()) 
   {
      t->SetSelected(status);
   }
}

void EffectXFunctions::SelectAllTracks()
{
   SelectTracks(true);
}

void EffectXFunctions::DeselectAllTracks()
{
   SelectTracks(false);
}

// ------ Ctors
EffectXFunctions::EffectXFunctions()
 : m_pXf(0)
{ }


EffectXFunctions::~EffectXFunctions()
{
//   if(m_pXf) delete m_pXf; // not sure if needed
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
         em.RegisterEffect(new EffectXFunctions(), BUILTIN_EFFECT | ANALYZE_EFFECT );
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

