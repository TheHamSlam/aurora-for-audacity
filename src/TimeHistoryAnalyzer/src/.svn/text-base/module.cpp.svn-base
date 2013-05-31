/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  module.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class EffectTimeHistoryAnalyzer
\brief The Audacity module front-end for Aurora's TimeHistoryAnalyzer class.

  This class is an Audacity module (plug-in) that loads on run time.
  Its core is the instantiation of a TimeHistoryAnalyzer singleton that 
  does all calculations.

*//*******************************************************************/

#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>

#include <afart.h>
#include <afconfig.h>
#include "than.h"
#include "gui.h"
#include "module.h"

//----------------------------------------------------------------------------
// EffectTimeHistoryAnalyzer implementation
//----------------------------------------------------------------------------
#define THA_RESULTS_DLG_WIDTH   700 // TODO remove it
#define THA_RESULTS_DLG_HEIGTH  800 // TODO remove it

int  EffectTimeHistoryAnalyzer::GetFilterIdFromName(wxString& wxszName)
{
    if(wxszName.Find(wxT("ITU"))      != wxNOT_FOUND)  { return AFAudioTrack::FLT_ITU; }
    else if(wxszName.Find(wxT("IEC")) != wxNOT_FOUND)  { return AFAudioTrack::FLT_IEC; }
    else if(wxszName.Find(wxT("ISO")) != wxNOT_FOUND)  { return AFAudioTrack::FLT_ISO; }
    else if(wxszName.Find(wxT("UNI")) != wxNOT_FOUND)  { return AFAudioTrack::FLT_UNI; }

    return AFAudioTrack::FLT_LIN;
}

int EffectTimeHistoryAnalyzer::GetTrackIndexFromName(wxString& wxszName)
{
	int nChnl = 2; // This is the Audacity 'mono' case
    wxString wxszTrackName = wxszName;
    if(wxszTrackName.Find(wxT("[left]")) != wxNOT_FOUND)
    {
    	nChnl = 0;
    }
    else if(wxszTrackName.Find(wxT("[right]")) != wxNOT_FOUND)
    {
    	nChnl = 1;
    }

   	wxszTrackName = wxszTrackName.BeforeLast(wxT(' '));
   	if(wxszTrackName.IsEmpty())
   		wxszTrackName = wxszName;

    TrackListIterator iter(mOutputTracks);
    WaveTrack* pWt = (WaveTrack*)(iter.First());

    int  nCnt   = 0;
    while (pWt != NULL && nCnt < int(m_unTracksCount))
    {
        if(pWt->GetName() == wxszTrackName && pWt->GetChannel() == nChnl)
        {
        	return nCnt;
        }
        pWt = (WaveTrack*)(iter.Next());
        nCnt++;
    }
    return -1; // not found
}

bool EffectTimeHistoryAnalyzer::SetTrackListItem(int* anTrackList, const int nIdx, wxString& wxszName)
{
	wxASSERT_MSG(nIdx < int(m_unTracksCount),
			     wxT("SetTrackListItem: out of range."));

	wxASSERT_MSG(!wxszName.IsEmpty(),
			     wxT("SetTrackListItem: empty track name."));

	int nChnl = 2; // This is the Audacity 'mono' case
    wxString wxszTrackName = wxszName;
    if(wxszTrackName.Find(wxT("[left]")) != wxNOT_FOUND)
    {
    	nChnl = 0;

    }
    else if(wxszTrackName.Find(wxT("[right]")) != wxNOT_FOUND)
    {
    	nChnl = 1;
    }

   	wxszTrackName = wxszTrackName.BeforeLast(wxT(' '));
   	if(wxszTrackName.IsEmpty())
   		wxszTrackName = wxszName;

    TrackListIterator iter(mOutputTracks);
    WaveTrack* pWt = (WaveTrack*)(iter.First());

    int  nCnt   = 0;
    bool bFound = false;
    while (pWt != NULL && !bFound)
    {
        if(pWt->GetName() == wxszTrackName && pWt->GetChannel() == nChnl)
        {
        	bFound = true;
        	anTrackList[nIdx] = nCnt;
        }
        pWt = (WaveTrack*)(iter.Next());
        nCnt++;
    }

    return bFound;
}

void EffectTimeHistoryAnalyzer::SetTracksNamesArray(wxArrayString& awxszTrackNames)
{
    wxString wxszTrackName,
             wxszChnlName;

    TrackListIterator iter(mOutputTracks);
    WaveTrack* pWt = (WaveTrack*)(iter.First());

    while (pWt != NULL)
    {
        wxszTrackName = pWt->GetName();
        ::AuroraGetAudacityChannelName(wxszChnlName, pWt->GetChannel()); // TODO check if fits THA needs
        wxszTrackName << wxT(" [") << wxszChnlName << wxT("]");
        awxszTrackNames.Add(wxszTrackName);
        pWt = (WaveTrack*)(iter.Next());
    }
}

void EffectTimeHistoryAnalyzer::AddCalibrationTrackListItem(const int nChnl, wxString& wxszName, const double dbRefValue)
{
	int nIdx = GetTrackIndexFromName(wxszName);
	m_aCalibrationTrackList.Add(new THACalibrationAudioTrack(mProjectRate, dbRefValue, nIdx));
}

void EffectTimeHistoryAnalyzer::AddSignalTrackListItem(const int nChnl, wxString& wxszName, wxString& wxszFilter, const double dbFullscale)
{
	int nIdx      = GetTrackIndexFromName(wxszName),
	    nFilterId = GetFilterIdFromName(wxszFilter);

	THASignalAudioTrack* pTrack = new THASignalAudioTrack(mProjectRate);
	pTrack->SetIndex(nIdx);
	pTrack->SetFullScale(dbFullscale);
	pTrack->SetFilter(nFilterId);
	pTrack->SetName(wxszName);
    fflush(stdout);

	m_aSignalTrackList.Add(pTrack);
}

bool EffectTimeHistoryAnalyzer::LoadTrackData(AFAudioTrackBase* pTrack, const int nTrackIdx)
{
   TrackListIterator iter(mOutputTracks);
   WaveTrack* pWt = (WaveTrack*)(iter.First());

   //Checks the track rate, samples, minimum, maximum and name
   if(pTrack->GetSamplerate() != pWt->GetRate())
   {
       ::wxMessageBox(wxT("Sample rate mismatch.\nCheck tracks and project rates."),
                      wxT("Error"),
                      wxOK | wxICON_ERROR);
       return false;
   }

   //Get start and end times from track
   double dbTrackStart = pWt->GetStartTime();
   double dbTrackEnd   = pWt->GetEndTime();

   //Set the current bounds to whichever left marker is
   //greater and whichever right marker is less:
   double dbCurT0 = mT0 < dbTrackStart? dbTrackStart: mT0;
   double dbCurT1 = mT1 > dbTrackEnd  ? dbTrackEnd  : mT1;

   sampleCount smpcStart = 0,
		       smpcEnd   = 0;

   WaveClipList::compatibility_iterator it;
   int nClips = 0;
   WaveClip* pClip;
   sampleCount smpcClipEnd;

   // Process only if the right marker is to the right of the left marker
   if (dbCurT1 > dbCurT0)
   {
       int nCurrTrack = 0;
       while(nCurrTrack < nTrackIdx)
       {
           nCurrTrack++;
           pWt = (WaveTrack*)(iter.Next());
       }

       // clip experiments...
       for (it=pWt->GetClipIterator(); it; it=it->GetNext(), nClips++)
       {
    	   pClip = it->GetData();
       }

      //Transform the marker timepoints to samples
      smpcStart = pWt->TimeToLongSamples(dbCurT0);
      smpcEnd   = pWt->TimeToLongSamples(dbCurT1);

      if(nClips == 1)
      {
    	  // If there is only one clip, we can trim it, instead
    	  // of using the entire selection length...
          it    = pWt->GetClipIterator();
          pClip = it->GetData();
          smpcClipEnd = pClip->GetEndSample();
          smpcEnd     = ((smpcEnd > smpcClipEnd) && (smpcStart < smpcClipEnd)) ? smpcClipEnd : smpcEnd;
      }
      pTrack->SetTrackLength(smpcEnd-smpcStart, true);
      pWt->Get( (samplePtr) pTrack->GetData(), floatSample, smpcStart, smpcEnd-smpcStart );
   }

   return true;
}

void EffectTimeHistoryAnalyzer::AppendTracksToWorkspace()
{
    wxString wxszName;

    if(m_aSignalTrackList[0].GetSelectedFilter() != AFAudioTrack::FLT_NONE)  // TODO what's mean this????
    {
	   // If prompt user return true, add to workspace filtered tracks.
	   for(int nCh = 0; nCh < int(m_aSignalTrackList.GetCount()); nCh++)
	   {
		 wxszName = m_aSignalTrackList[nCh].GetName();
//		 wxszName.Printf(wxT("Ch %d"), nCh);

		 switch(m_aSignalTrackList[nCh].GetSelectedFilter())
		 {
			case AFAudioTrack::FLT_ITU: wxszName << wxT(" ITU filtered"); break;
			case AFAudioTrack::FLT_IEC: wxszName << wxT(" IEC filtered"); break;
			case AFAudioTrack::FLT_ISO: wxszName << wxT(" ISO filtered"); break;
			case AFAudioTrack::FLT_UNI: wxszName << wxT(" UNI filtered"); break;
			default: // shouldn't arrive here...
				wxszName << wxT(" not really filtered");
				break;
		 }
		 wxszName << wxT(" [") << int(nCh+1) << wxT("]");

		 WaveTrack* pWt = mFactory->NewWaveTrack(floatSample, mProjectRate);
		 pWt->Append((samplePtr)m_aSignalTrackList[nCh].GetFilteredTrack(),
				     floatSample,
				     m_aSignalTrackList[nCh].GetTrackLength() );
		 pWt->Flush();
		 pWt->SetName(wxszName);

		 mTracks->Add(pWt);
	  }
   }
}


bool EffectTimeHistoryAnalyzer::DoFullscaleCalibration(double* pdbFullscale)
{
    AFAudioTrackBase* pCalibrationSignal;

    int nCh = 0;
    while(nCh < int(m_aCalibrationTrackList.GetCount()))
    {
    	pCalibrationSignal = dynamic_cast<AFAudioTrackBase*>(&m_aCalibrationTrackList[nCh]);
        if(!LoadTrackData(pCalibrationSignal, m_aCalibrationTrackList[nCh].GetIndex()))
            return false;

        pdbFullscale[nCh] = m_aCalibrationTrackList[nCh].GetReferenceLevel() - 
                            m_aCalibrationTrackList[nCh].Leq();

        nCh++;
    }
    return true;
}


// -------------------------------- Effect virtual methods --------------------------------


TimeHistoryAnalyzer::TResults* EffectTimeHistoryAnalyzer::DoAnalysis()
{
    AFAudioTrackBase* pSignal;

    for(int nCh = 0; nCh < int(m_aSignalTrackList.GetCount()); nCh++)
    {
    	pSignal = dynamic_cast<AFAudioTrackBase*>(&m_aSignalTrackList[nCh]);
        if(!LoadTrackData(pSignal, m_aSignalTrackList[nCh].GetIndex()))
            return 0;
    }

#if !defined __WXGTK__
    m_pThan->SetProgressDialog(mProgress);
#endif

    m_pThan->SetTracksArray(&m_aSignalTrackList);

    if(!m_pThan->Analyze())
    {
        ::wxMessageBox(wxT("Something strange happened.\nCannot calculate Time History parameters."),
                       wxT("Error"),
                       wxOK | wxICON_ERROR);
        return 0;
    }

    return m_pThan->GetResults();
}

bool EffectTimeHistoryAnalyzer::Init()
{
#ifdef __AUDEBUG__
         printf("[TimeHistoryAnalyzer] INIT\n"); fflush(stdout);
#endif

    m_unTracksCount = size_t(GetNumWaveTracks());

    // The very first thing to do!
    m_pThan = new TimeHistoryAnalyzer(m_unTracksCount);

    this->CopyInputTracks(); // Set up mOutputTracks.

    return true;
}

bool EffectTimeHistoryAnalyzer::PromptUser()
{
#ifdef __AUDEBUG__
         printf("[TimeHistoryAnalyzer] PROMPT-USER\n"); fflush(stdout);
#endif
   // Setup graphics.
   InitArtProvider();

   TimeHistoryAnalyzerFrame*  pDlg;
   pDlg = new TimeHistoryAnalyzerFrame(mParent, m_pThan, this);

   pDlg->CenterOnParent();
   if(!pDlg->ShowModal())
   {
	   pDlg->Destroy();
	   return false;
   }

   pDlg->Destroy();
   return true;
}

bool EffectTimeHistoryAnalyzer::Process()
{
	AppendTracksToWorkspace();
    return true;
}

void EffectTimeHistoryAnalyzer::End()
{
    delete m_pThan;
}


// ------ Ctors
EffectTimeHistoryAnalyzer::EffectTimeHistoryAnalyzer()
 : m_pThan(0),
   m_unTracksCount(0)
{
#ifdef __AUDEBUG__
         printf("[TimeHistoryAnalyzer] Constructor.\n"); fflush(stdout);
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
#ifdef __AUDEBUG__
       printf("[TimeHistoryAnalyzer] Dispatch %d received.\n", type); fflush(stdout);
#endif
       
      if (type == ModuleInitialize)
      {
         EffectManager & em = EffectManager::Get();
         em.RegisterEffect(new EffectTimeHistoryAnalyzer(), BUILTIN_EFFECT | ANALYZE_EFFECT );

#ifdef __AUDEBUG__
         printf("[TimeHistoryAnalyzer] Module registered.\n"); fflush(stdout);
#endif
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

