/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  PeakVue

  module.cpp

  Simone Campanini

*******************************************************************//**

\class EffectPeakVue
\brief The Audacity module front-end for Aurora's PeakVue class.

*//*******************************************************************/

// From Audacity source tree
#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>

#include <afart.h>

#include "peakvue.h"
#include "gui.h"
#include "module.h"

//----------------------------------------------------------------------------
// EffectPeakVue implementation
//----------------------------------------------------------------------------
void EffectPeakVue::AddProcessedTracks()
{
    // This code appends processed tracks to workspace.
    // I don't want to modify the existing ones.
	/*
    wxString wxszName;
    for(int nCh = 0; nCh < int(audioData.GetCount()); nCh++)
    {
    	wxszName = m_aAudioData[nCh].GetName();

        WaveTrack* pWt = mFactory->NewWaveTrack(floatSample, mProjectRate);
        pWt->Append( (samplePtr)m_aAudioData[nCh].GetFilteredData(),
                      floatSample,
                      m_aAudioData[nCh].GetLength() );
        pWt->Flush();
        
        pWt->SetName(wxszName);
        
        mTracks->Add(pWt);
    }
    */
}


void EffectPeakVue::LoadAudioData(const int selectedIdx)
{
	sampleCount smpcStart, smpcEnd;

	double  dbCurT0, dbCurT1;

	TrackListIterator* pIter = new TrackListIterator(mOutputTracks);
	WaveTrack*         pWt   = (WaveTrack*)(pIter->First());

	int currentIdx = 0;
	while (pWt != NULL)
	{
        //Get current channel (unuseful..)
        //nCurChannel = pWt->GetChannel();
		if(currentIdx == selectedIdx)
		{

		    //Get smpcStart and smpcEnd times from track
		    double dbTrackStart = pWt->GetStartTime();
		    double dbTrackEnd   = pWt->GetEndTime();

		    //Set the current bounds to whichever left marker is
		    //greater and whichever right marker is less:
		    dbCurT0 = mT0 < dbTrackStart ? dbTrackStart : mT0;
		    dbCurT1 = mT1 > dbTrackEnd   ? dbTrackEnd   : mT1;

            // Process only if the right marker is to the right of the left marker
		    if (dbCurT1 > dbCurT0)
		    {
			    //Transform the marker timepoints to samples
			    smpcStart = pWt->TimeToLongSamples(dbCurT0);
			    smpcEnd   = pWt->TimeToLongSamples(dbCurT1);

                AFSample*     audioData  = new AFSample [smpcEnd - smpcStart];
                AFSampleCount dataLength = smpcEnd - smpcStart;

                //printf("Loading track %s (%d samples)\n", (const char*)pTrack->GetName().ToAscii(), int(pTrack->GetLength())); fflush(stdout);
                pWt->Get( (samplePtr) audioData, floatSample, smpcStart,  dataLength );

                m_pDataShuttle->GetAudioData().SetDownsampledData(audioData, dataLength, double(pWt->GetRate()));

                delete [] audioData;
		    }
		}
		//Iterate to the next track
		pWt = (WaveTrack*)(pIter->Next());
	}
}

void EffectPeakVue::GetTrackLabels()
{
	TrackListIterator* pIter = new TrackListIterator(mOutputTracks);
	WaveTrack*         pWt   = (WaveTrack*)(pIter->First());

	while (pWt != NULL)
	{
	    m_pDataShuttle->GetLabels().Add(pWt->GetName());

		//Iterate to the next track
		pWt = (WaveTrack*)(pIter->Next());
	}
}


bool EffectPeakVue::DoAnalysis(const int selectedIdx)
{
    // 1. Get correct track
	LoadAudioData(selectedIdx);

	// 2. Setup analyzer
	PVSpectrum* pSpectralAnalyzer = new PVSpectrum(m_pDataShuttle);

	// 3. Analyze
	pSpectralAnalyzer->Compute();

	// 4. Get results

	delete pSpectralAnalyzer;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Effect derived methods
//
////////////////////////////////////////////////////////////////////////////////
bool EffectPeakVue::Init()
{
   this->CopyInputTracks(); // Set up mOutputTracks.

   m_pDataShuttle = new PVDataShuttle();
   GetTrackLabels();

   return true;
}

bool EffectPeakVue::PromptUser()
{
    // Gui stuffs
    InitArtProvider();

   PeakVueDialog* pDlg = new PeakVueDialog(mParent, wxID_ANY, this, *m_pDataShuttle); //, this, m_pAp, m_pDataExport);
   pDlg->CenterOnParent();

   if(!pDlg->ShowModal())
   {
       delete m_pCfg; m_pCfg = 0;
       pDlg->Destroy();

       return false;
   }
   
   //m_pAp->StoreConfigurationValues();

   pDlg->Destroy();

//   m_bProcess = m_pAp->CalculateAcousticParameters();  // Tries to skip the ProgressDialog curse...

   return true;
}

//------------------------- Processing methods -------------------------
bool EffectPeakVue::Process()
{
#ifndef __WXGTK__
    m_pAp->SetProgressDialog(mProgress);
#endif

//    return (m_bProcess = m_pAp->CalculateAcousticParameters());

      // From Effect class: replaces current tracks
      // with mOutputTracks
      //ReplaceProcessedTracks(true);
	return true;
}

void EffectPeakVue::End()
{
    delete m_pCfg; m_pCfg = 0;
    delete m_pDataShuttle;
}

// ------ Ctors
EffectPeakVue::EffectPeakVue()
: m_pCfg(0),
  m_bProcess(false)
{}


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
       switch(type)
       {
           case ModuleInitialize:
               {
#ifdef __AUDEBUG__
                   fprintf(stderr, "[PeakVue]: dispatch %d received.\n", int(type));
#endif
                   EffectManager & em = EffectManager::Get();
                   em.RegisterEffect(new EffectPeakVue(), BUILTIN_EFFECT | ANALYZE_EFFECT );
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
               fprintf(stderr, "[PeakVue]: dispatch %d received.\n", int(type));
#endif
               break;
                   
           default:
               //do something
#ifdef __AUDEBUG__
               fprintf(stderr, "[PeakVue]: unknown dispatch received.\n");
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

