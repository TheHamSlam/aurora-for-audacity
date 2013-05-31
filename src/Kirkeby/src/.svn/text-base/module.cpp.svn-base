/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Invert Kirkeby

  module.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class EffectKirkeby
\brief The Audacity module front-end for Aurora's Kirkeby class.

  This class is an Audacity module (plug-in) that loads on run time.
  Its core is the instantiation of a Kirkeby singleton that does
  all calculations.

*//*******************************************************************/


#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>

#include <afart.h>
#include <afconfig.h>
#include "kirk.h"
#include "gui.h"
#include "module.h"

//----------------------------------------------------------------------------
// EffectKirkeby implementation
//----------------------------------------------------------------------------


bool EffectKirkeby::LoadTracks()
{

    int  nCurChannel; // quite unuseful...
    
    m_pKirk->SetInputTrackLength(m_smpcEnd - m_smpcStart); // Set tracks length

    int nRow = 0;
    int nCol = 0;
    int nColsNo = m_pKirk->GetCols();
    int nColumnWidth = int(m_smpcEnd - m_smpcStart) / nColsNo;
    
    WaveTrack* pWaveTrack = (WaveTrack*)(m_pIter->First());

    //Get the track rate
    m_pKirk->SetSamplerate(pWaveTrack->GetRate());

    samplePtr pInput;
    
    while (pWaveTrack != NULL)
    {
        //Get current channel (unuseful..)
        nCurChannel = pWaveTrack->GetChannel();

        //m_pKirk->AddTrackName(waveTrack->GetName());
        nCol = 0;
        while(nCol < nColsNo)
        {
            if((pInput = (samplePtr) m_pKirk->GetInputTrackItem(nRow, nCol)) == 0)
            {
                printf("Error in memory allocation\n");
                return false;
            }
            pWaveTrack->Get( pInput, floatSample, m_smpcStart + nCol*nColumnWidth,
                             nColumnWidth);
            nCol++;
        }

        //Iterate to the next track
        pWaveTrack = (WaveTrack*)(m_pIter->Next());
        nRow++;
    }

    
    return true;
}

bool EffectKirkeby::Init()
{   
    // The very first thing to do!
    m_smpcTracksNo = GetNumWaveTracks();
    m_pKirk = new Kirkeby(m_smpcTracksNo);
    
    m_pKirk->SetSamplerate(mProjectRate);
    
    this->CopyInputTracks(); // Set up mOutputTracks.
    
    m_pIter = new TrackListIterator(mOutputTracks);
    WaveTrack* pWaveTrack = (WaveTrack*)(m_pIter->First());
    
    //Get start and end times from track
    double dbTrackStart = pWaveTrack->GetStartTime();
    double dbTrackEnd   = pWaveTrack->GetEndTime();
    
    //Set the current bounds to whichever left marker is
    //greater and whichever right marker is less:
    double dbCurT0 = mT0 < dbTrackStart ? dbTrackStart : mT0;
    double dbCurT1 = mT1 > dbTrackEnd   ? dbTrackEnd   : mT1;
    
    // Process only if the right marker is to the right of the left marker
    if (dbCurT1 <= dbCurT0) return false;
    
    //Transform the marker timepoints to samples
    m_smpcStart = pWaveTrack->TimeToLongSamples(dbCurT0);
    m_smpcEnd   = pWaveTrack->TimeToLongSamples(dbCurT1);

    m_pKirk->SetInputTrackLength(m_smpcEnd - m_smpcStart);
    
    //Check if it's a single stereo track
    if(m_smpcTracksNo == 2 && pWaveTrack->GetChannel() == 0)
        m_bIsStereo = true;
    
    return true;
}

bool EffectKirkeby::PromptUser()
{
    // Gui stuffs
    InitArtProvider();

   KirkebyDialog dlog(mParent, m_pKirk, m_bIsStereo);
   dlog.CenterOnParent();

   if(!dlog.ShowModal())
   {
       delete m_pKirk; m_pKirk = 0;
       return false;
   }
   
#ifdef __AUDEBUG__   
   printf("kirk: PromptUser terminated\n");
#endif
   m_bProcess = true;
   return true;
}

//------------------------- Processing methods -------------------------
bool EffectKirkeby::Process()
{

#ifdef __AUDEBUG__
   printf("kirk: entering in Process()\n"); fflush(stdout);
#endif

    if(!m_pKirk || !m_bProcess)
    {
        printf("Calculation aborted!\n");
        return false;
    }
    
    if(!m_pKirk->Init())
    {
        wxMessageBox(wxT("Kirkeby module initialization failed."),
                        wxT("Error"), wxOK | wxICON_ERROR);
        delete m_pKirk; m_pKirk = 0;
        return false;
    }

    if(!LoadTracks())
    {
        ::wxMessageBox(wxT("Something strange occourred.\nCannot load tracks in memory."),
                       wxT("Error"), wxOK | wxICON_ERROR);
        delete m_pKirk; m_pKirk = 0;
        return false;
    }

    //WaveTrack *waveTrack = (WaveTrack*)(mIter->First());

    int nRow = 0, nCol = 0;
    wxString wxszName;
    if(!m_pKirk->Process())
    {
        ::wxMessageBox(wxT("Something strange occourred.\nCannot calculate Kirkeby Inverse filter."),
                       wxT("Error"), wxOK | wxICON_ERROR);
        delete m_pKirk; m_pKirk = 0;
        return false;
    }
    printf("Processing terminated successifully.\n"); fflush(stdout);   // DEBUG
    // If we arrived here, it should be not more than two tracks
    // selected!
    //while((ch < m_pKirk->GetChannelsNumber()) && (waveTrack != NULL)) {

    
    // TODO: if(m_bIsStereo) Generate stereo output track.
    while(nRow < m_pKirk->GetRows())
    {
        wxszName.Printf(wxT("Inverse Filter %d"), nRow + 1);

        WaveTrack *t = mFactory->NewWaveTrack(floatSample, mProjectRate);

        nCol = 0;
        while(nCol < m_pKirk->GetCols())
        {
            t->Append((samplePtr)m_pKirk->GetOutputTrackItem(nRow, nCol), floatSample,
                        m_pKirk->GetInverseFilterLength() );
            nCol++;
        }
        t->Flush();
        t->SetName(wxszName);

        mTracks->Add(t);
        nRow++;
    }
    // From Effect class: replaces current tracks
    // with mOutputTracks
    //ReplaceProcessedTracks(true);

   
#ifdef __AUDEBUG__
   printf("kirk: done.\n"); fflush(stdout); 
#endif   
   delete m_pKirk; m_pKirk = 0;
   return true;
}

// ------ Ctors
EffectKirkeby::EffectKirkeby()
  : m_pIter(0),
    m_smpcTracksNo(0),
    m_smpcStart(0),
    m_smpcEnd(0),
    m_pKirk(0),
    m_bProcess(false),
    m_bIsStereo(false)
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
      if (type == ModuleInitialize) {
         EffectManager & em = EffectManager::Get();
         em.RegisterEffect(new EffectKirkeby(), BUILTIN_EFFECT | PROCESS_EFFECT );
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

