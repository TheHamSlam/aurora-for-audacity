/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters

  acpar.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AcParameters
\brief A powerful analizing tool for room acoustics

  This class derived from AFAcousticalParameters.

*//*******************************************************************/

#include <wx/textfile.h>
#include <wx/progdlg.h>

#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include <vector>

#include <commdefs.h>
#include <afconfig.h>

#include "afacpar.h"
#include "acpar.h"


const wxChar* const AcParameters::m_awxpchParamLabels[] = {

    wxT("Signal"),    wxT("Noise"),      wxT("Strength"),  wxT("C50"),   wxT("C80"),
    wxT("D50"),       wxT("Ts"),         wxT("EDT"),       wxT("Tuser"), wxT("T20"),
    wxT("T30"),

    wxT("Peakiness"), wxT("Millisecs"),  wxT("Impulsivs"),

    wxT("St1"),       wxT("St2"),        wxT("StLate"),
    wxT("IACC"),      wxT("IACC delay"), wxT("IACC width"),
    wxT("JLF"),       wxT("JLFC"),       wxT("LJ")
};


void AcParameters::ReadConfigurationValues()
{
    if(!m_pCfg)
    {
    	ShowErrorMessage(ERR_NO_CONFIG_SOURCE);
    	return;
    }

   // Read parameter from stored configuration
   double dbValue;
   if(m_pCfg->Read(wxT("/Aurora/AcParameters/UserMinLevel"), &dbValue))
     SetUserMinLevel(dbValue);
   if(m_pCfg->Read(wxT("/Aurora/AcParameters/UserMaxLevel"), &dbValue))
     SetUserMaxLevel(dbValue);
   if(m_pCfg->Read(wxT("/Aurora/AcParameters/DirectSoundTrigger"), &dbValue))
     SetDirectSoundTrigValue(dbValue);
   if(m_pCfg->Read(wxT("/Aurora/AcParameters/FullScale"), &dbValue))
     SetFullScale(dbValue);
   if(m_pCfg->Read(wxT("/Aurora/AcParameters/ProbeMicsDistance"), &dbValue))
     SetProbeMicsDistance(dbValue);
   if(m_pCfg->Read(wxT("/Aurora/AcParameters/SoundSpeed"), &dbValue))
     SetSoundSpeedValue(dbValue);
   
   ReadConfigurationGReferenceLevels();
}

void AcParameters::StoreConfigurationValues()
{
    if(!m_pCfg)
    {
    	ShowErrorMessage(ERR_NO_CONFIG_SOURCE);
    	return;
    }

   m_pCfg->Write(wxT("/Aurora/AcParameters/UserMinLevel"), GetUserMinLevel());
   m_pCfg->Write(wxT("/Aurora/AcParameters/UserMaxLevel"), GetUserMaxLevel());
   m_pCfg->Write(wxT("/Aurora/AcParameters/DirectSoundTrigger"), GetDirectSoundTrigValue());
   m_pCfg->Write(wxT("/Aurora/AcParameters/FullScale"), GetFullScale());
   m_pCfg->Write(wxT("/Aurora/AcParameters/ProbeMicsDistance"), GetProbeMicsDistance());
   m_pCfg->Write(wxT("/Aurora/AcParameters/SoundSpeed"), GetSoundSpeedValue());
}

void AcParameters::ReadConfigurationGReferenceLevels()
{
    if(!m_pCfg)
    {
    	ShowErrorMessage(ERR_NO_CONFIG_SOURCE);
    	return;
    }

   double dbValue;
   if(m_pCfg->Read(wxT("/Aurora/AcParameters/ReferenceLevel_31_5"), &dbValue))
      SetGReferenceLevel(dbValue, BD_31_5);
   
   wxString wxszPath;
   for(int bd = BD_63; bd < N_BANDS; bd++)
   {
      wxszPath =  wxT("/Aurora/AcParameters/ReferenceLevel_");
      wxszPath += g_awxpchBandLabels[bd];
      if(m_pCfg->Read(wxszPath, &dbValue))
         SetGReferenceLevel(dbValue, bd);
   }
}

void AcParameters::StoreConfigurationGReferenceLevels()
{
    if(!m_pCfg)
    {
    	ShowErrorMessage(ERR_NO_CONFIG_SOURCE);
    	return;
    }

   m_pCfg->Write(wxT("/Aurora/AcParameters/ReferenceLevel_31_5"),
              GetGReferenceLevel(BD_31_5));
   
   wxString wxszPath;
   for(int bd = BD_63; bd < N_BANDS; bd++)
   {
      wxszPath =  wxT("/Aurora/AcParameters/ReferenceLevel_");
      wxszPath += g_awxpchBandLabels[bd];
      m_pCfg->Write(wxszPath, GetGReferenceLevel(bd));
   }
}


void AcParameters::ShowErrorMessage(const int nErrNo)
{
	wxString wxszMsg;
	switch(nErrNo)
	{
	    case ERR_NO_FAT:
	    	wxszMsg = wxT("Cannot locate First Arrival Time.\nThreshold is too high.\n\nTry again with a lower Threshold.");
	    	break;
	    case ERR_SPATIAL_IR_TOO_SHORT:
	    	wxszMsg = wxT("The Impulse Response is too short (< 80 ms) for spatial parameters calculations.");
	    	break;
	    case ERR_NO_CONFIG_SOURCE:
	    	wxszMsg = wxT("No configuration file found.");
	    	break;
	    default:
	    	wxszMsg = wxT("Error unknown.");
	    	break;
	}
   ::wxMessageBox(wxszMsg, wxT("Error"), wxOK | wxICON_ERROR);
}

void AcParameters::InitProgressMeter(const int nTotal)
{
#ifdef __WX_NATIVE_PROG_DLG__
	m_pProgressDlg = new wxProgressDialog(wxT("Aurora - ISO 3382 Acoustic Parameters"),
                                          wxT("Calculating..."),
                                          nTotal,
                                          NULL,
                                          wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);
	wxSize sz = m_pProgressDlg->GetSize();
	sz.x += 100;
	m_pProgressDlg->SetSize(sz);

#else
   m_nProgMax = nTotal;
   m_pProgressDlg->SetMessage(wxT("Calculating..."));
#endif
}

bool AcParameters::UpdateProgressMeter(const int nStep)
{
#ifdef __WX_NATIVE_PROG_DLG__
	return m_pProgressDlg->Update(nStep);
#else
   return m_pProgressDlg->Update(nStep, m_nProgMax);
#endif
}

void AcParameters::DestroyProgressMeter() 
{
#ifdef __WX_NATIVE_PROG_DLG__
   m_pProgressDlg->Destroy();
   m_pProgressDlg = 0;
#endif
}

void AcParameters::PostProcess()
{
/*
   if(IsAppendDataToFile()) 
   {
       AppendResultsToFile(CH_LEFT);
       if(GetChannelsNumber() > 1)
    	   AppendResultsToFile(CH_RIGHT);
   }
   */
}

int AcParameters::GetParameterFromString(wxString& wxszLabel)
{
     if(wxszLabel.Find(wxT("Signal"))   != wxNOT_FOUND) return AP_SIGNAL; else
     if(wxszLabel.Find(wxT("Noise"))    != wxNOT_FOUND) return AP_NOISE;  else
     if(wxszLabel.Find(wxT("strenGth")) != wxNOT_FOUND) return AP_G;      else
     if(wxszLabel.Find(wxT("C50"))      != wxNOT_FOUND) return AP_C50;    else
     if(wxszLabel.Find(wxT("C80"))      != wxNOT_FOUND) return AP_C80;    else
     if(wxszLabel.Find(wxT("D50"))      != wxNOT_FOUND) return AP_D50;    else
     if(wxszLabel.Find(wxT("Ts"))       != wxNOT_FOUND) return AP_Ts;     else
     if(wxszLabel.Find(wxT("EDT"))      != wxNOT_FOUND) return AP_EDT;    else
     if(wxszLabel.Find(wxT("Tuser"))    != wxNOT_FOUND) return AP_Tuser;  else
     if(wxszLabel.Find(wxT("T20"))      != wxNOT_FOUND) return AP_T20;    else
     if(wxszLabel.Find(wxT("T30"))      != wxNOT_FOUND) return AP_T30;    else
     if(wxszLabel.Find(wxT("Peak"))     != wxNOT_FOUND) return AP_PEAKINESS; else
     if(wxszLabel.Find(wxT("Millis"))   != wxNOT_FOUND) return AP_MILLISECS; else
     if(wxszLabel.Find(wxT("Impuls"))   != wxNOT_FOUND) return AP_IMPULSIVS; else
     if(wxszLabel.Find(wxT("St1"))      != wxNOT_FOUND) return AP_ST1;    else
     if(wxszLabel.Find(wxT("St2"))      != wxNOT_FOUND) return AP_ST2;    else
     if(wxszLabel.Find(wxT("StL"))      != wxNOT_FOUND) return AP_STL;    else
     if(wxszLabel.Find(wxT("t IACC"))   != wxNOT_FOUND) return AP_T_IACC; else
     if(wxszLabel.Find(wxT("W IACC"))   != wxNOT_FOUND) return AP_W_IACC; else
     if(wxszLabel.Find(wxT("IACC"))     != wxNOT_FOUND) return AP_IACC;   else
     if(wxszLabel.Find(wxT("JLFC"))     != wxNOT_FOUND) return AP_JLFC;   else
     if(wxszLabel.Find(wxT("JLF"))      != wxNOT_FOUND) return AP_JLF;    else
     if(wxszLabel.Find(wxT("LJ"))       != wxNOT_FOUND) return AP_LJ;

     return -1; // unknown
}


//AcParameters::AcParameters()
//{}

AcParameters::AcParameters(TArrayOfAPAudioTracks* paAudioTracks, AFConfig* pCfg)
  : AFAcousticalParameters(paAudioTracks),
    m_bAppendDataToFile(false),
    m_pCfg(pCfg),
#ifndef __WX_NATIVE_PROG_DLG__
    m_nProgMax(100),
#endif
    m_pProgressDlg(0)
{ }

AcParameters::~AcParameters()
{
   if(m_pProgressDlg) DestroyProgressMeter();
}

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

