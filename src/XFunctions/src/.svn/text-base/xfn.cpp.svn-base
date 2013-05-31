/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  xfn.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class XFunctions
\brief The Aurora's powerful cross-functions calculator module

  blabla
*//*******************************************************************/


#include "xfn.h"
#include "plot.h"

void XFunctions::ShowErrorMessage(const char* pchMsg, const char* pchCaption)
{
   wxString wxszMsg(pchMsg, *wxConvCurrent);
   wxString wxszTitle(pchCaption, *wxConvCurrent);
   ::wxMessageBox(wxszMsg, wxszTitle, wxOK | wxICON_ERROR);
}

void XFunctions::InitProgressMeter(const wxString& msg) 
{
   m_pProgressDlg = new ProgressDialog(wxT("Aurora Cross Functions"),
                                     msg);
}

bool XFunctions::UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total) 
{
   return (m_pProgressDlg->Update(int(step), int(total)) > 0) ? true : false;
}

void XFunctions::DestroyProgressMeter() 
{
   m_pProgressDlg->Destroy();
   m_pProgressDlg = 0;
}

void XFunctions::ReadConfigurationValues() 
{
// Read parameter from stored configuration
   bool   bValue;
   double dValue;
   AFSampleCount lValue;
   
   wxString path;
   path.Printf(wxT("/Aurora/XFunctions/FftSize"));
   if(m_pAuroraCfg->Read(path, &lValue))  SetFFTLength(lValue);
   path.Printf(wxT("/Aurora/XFunctions/WindowType"));
   if(m_pAuroraCfg->Read(path, &lValue))  SetWindowType(int(lValue));
   
   path.Printf(wxT("/Aurora/XFunctions/XFunctionType"));
   if(m_pAuroraCfg->Read(path, &lValue))  SetXFunctionType(int(lValue));
   
   path.Printf(wxT("/Aurora/XFunctions/ProbeFreeField"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetProbeFreeField(bValue);
   path.Printf(wxT("/Aurora/XFunctions/ProbeRigidTerminated"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetProbeRigidTerminated(bValue);
   path.Printf(wxT("/Aurora/XFunctions/SoundSpeed"));
   if(m_pAuroraCfg->Read(path, &dValue))  SetSoundSpeed(dValue);
   path.Printf(wxT("/Aurora/XFunctions/ProbeMicDistance"));
   if(m_pAuroraCfg->Read(path, &dValue))  SetProbeDistance(dValue);
   path.Printf(wxT("/Aurora/XFunctions/ProbeMaxFreq"));
   if(m_pAuroraCfg->Read(path, &dValue))  SetProbeMaxFreq(dValue);

   path.Printf(wxT("/Aurora/XFunctions/FollowingFilter"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetFollowingFilter(bValue);
   path.Printf(wxT("/Aurora/XFunctions/FollowingBandwidth"));
   if(m_pAuroraCfg->Read(path, &dValue))  SetFollowingBandwidth(dValue);
   
   path.Printf(wxT("/Aurora/XFunctions/Normalize"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetNormalize(bValue);
   path.Printf(wxT("/Aurora/XFunctions/ShiftToHalfWindow"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetShiftToHalfWindow(bValue);
   path.Printf(wxT("/Aurora/XFunctions/CoherenceWeighting"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetCoherenceWeighting(bValue);
   path.Printf(wxT("/Aurora/XFunctions/HilbertTransform"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetHilbertTransform(bValue);
   path.Printf(wxT("/Aurora/XFunctions/TimeReversal"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetTimeReversal(bValue);
   path.Printf(wxT("/Aurora/XFunctions/SaveMultispectrum"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetSaveMultispectrum(bValue);
   path.Printf(wxT("/Aurora/XFunctions/DiracPulse"));
   if(m_pAuroraCfg->Read(path, &bValue))  SetDiracPulse(bValue);
   
   path.Printf(wxT("/Aurora/XFunctions/TriggerLevel"));
   if(m_pAuroraCfg->Read(path, &dValue))  SetTriggerLevel(dValue);
}

void XFunctions::StoreConfigurationValues() 
{
   wxString path;
   path.Printf(wxT("/Aurora/XFunctions/FftSize"));
   m_pAuroraCfg->Write(path, GetFFTLength());
   path.Printf(wxT("/Aurora/XFunctions/WindowType"));
   m_pAuroraCfg->Write(path, AFSampleCount(GetWindowType()));
   
   path.Printf(wxT("/Aurora/XFunctions/XFunctionType"));
   m_pAuroraCfg->Write(path, AFSampleCount(GetXFunctionType()));

   path.Printf(wxT("/Aurora/XFunctions/ProbeFreeField"));
   m_pAuroraCfg->Write(path, IsProbeFreeField());
   path.Printf(wxT("/Aurora/XFunctions/ProbeRigidTerminated"));
   m_pAuroraCfg->Write(path, IsProbeRigidTerminated());
   path.Printf(wxT("/Aurora/XFunctions/SoundSpeed"));
   m_pAuroraCfg->Write(path, GetSoundSpeed());
   path.Printf(wxT("/Aurora/XFunctions/ProbeMicDistance"));
   m_pAuroraCfg->Write(path, GetProbeDistance());
   path.Printf(wxT("/Aurora/XFunctions/ProbeMaxFreq"));
   m_pAuroraCfg->Write(path, GetProbeMaxFreq());
   
   path.Printf(wxT("/Aurora/XFunctions/FollowingFilter"));
   m_pAuroraCfg->Write(path, IsFollowingFilterEnabled());
   path.Printf(wxT("/Aurora/XFunctions/FollowingBandwidth"));
   m_pAuroraCfg->Write(path, GetFollowingBandwidth());
   
   path.Printf(wxT("/Aurora/XFunctions/Normalize"));
   m_pAuroraCfg->Write(path, IsNormalizeSet());
   path.Printf(wxT("/Aurora/XFunctions/ShiftToHalfWindow"));
   m_pAuroraCfg->Write(path, IsShiftToHalfWindowSet());
   path.Printf(wxT("/Aurora/XFunctions/CoherenceWeighting"));
   m_pAuroraCfg->Write(path, IsCoherenceWeightingSet());
   path.Printf(wxT("/Aurora/XFunctions/HilbertTransform"));
   m_pAuroraCfg->Write(path, IsHilbertTransformSet());
   path.Printf(wxT("/Aurora/XFunctions/TimeReversal"));
   m_pAuroraCfg->Write(path, IsTimeReversalSet());
   path.Printf(wxT("/Aurora/XFunctions/SaveMultispectrum"));
   m_pAuroraCfg->Write(path, IsSaveMultispectrumSet());
   path.Printf(wxT("/Aurora/XFunctions/DiracPulse"));
   m_pAuroraCfg->Write(path, IsDiracPulseSet());
   
   path.Printf(wxT("/Aurora/XFunctions/TriggerLevel"));
   m_pAuroraCfg->Write(path, GetTriggerLevel());
   
   // Writes immediately changes
   m_pAuroraCfg->Flush();
}

int XFunctions::GetXFunctionTypeByString(wxString& wxszXFnType)
{
	if(wxszXFnType.Find(wxT("Autocorrelation")) != wxNOT_FOUND)
	   return XFT_AUTO_CORRELATION;
	else if(wxszXFnType.Find(wxT("Crosscorrelation")) != wxNOT_FOUND)
	   return XFT_CROSS_CORRELATION;
	else if(wxszXFnType.Find(wxT("White Crosscorr.")) != wxNOT_FOUND)
	   return XFT_WHITE_CORRELATION;
	else if(wxszXFnType.Find(wxT("Cross-Power Spect.")) != wxNOT_FOUND)
	   return XFT_CROSS_POWER;
	else if(wxszXFnType.Find(wxT("H1")) != wxNOT_FOUND)
	   return XFT_TF_H1;
	else if(wxszXFnType.Find(wxT("H2")) != wxNOT_FOUND)
	   return XFT_TF_H2;
	else if(wxszXFnType.Find(wxT("H3")) != wxNOT_FOUND)
	   return XFT_TF_H3;
	else if(wxszXFnType.Find(wxT("Alpha")) != wxNOT_FOUND)
	   return XFT_ALPHA;
	else if(wxszXFnType.Find(wxT("Coherence")) != wxNOT_FOUND)
	   return XFT_COHERENCE;
	else if(wxszXFnType.Find(wxT("PU FF Calibration")) != wxNOT_FOUND)
	   return XFT_PU_CALIBRATION_FREE_FIELD;
	else if(wxszXFnType.Find(wxT("PU SW Calibration")) != wxNOT_FOUND)
	   return XFT_PU_CALIBRATION_SW_TUBE;
	else if(wxszXFnType.Find(wxT("Dirac delta")) != wxNOT_FOUND)
	   return XFT_DIRAC_DELTA;

	return -1;
}

int XFunctions::GetPlotType(wxString& label, int* type, int* ch)
{
    // Search for function type
    int fnType = 0;
    if(label.Find(wxT("Autocorrelation")) != wxNOT_FOUND)
       fnType = XFT_AUTO_CORRELATION;
    else if(label.Find(wxT("Crosscorrelation")) != wxNOT_FOUND)
       fnType = XFT_CROSS_CORRELATION;
    else if(label.Find(wxT("White Crosscorr.")) != wxNOT_FOUND)
       fnType = XFT_WHITE_CORRELATION;
    else if(label.Find(wxT("Cross-Power Spect.")) != wxNOT_FOUND)
       fnType = XFT_CROSS_POWER;
    else if(label.Find(wxT("H1")) != wxNOT_FOUND)
       fnType = XFT_TF_H1;
    else if(label.Find(wxT("H2")) != wxNOT_FOUND)
       fnType = XFT_TF_H2;
    else if(label.Find(wxT("H3")) != wxNOT_FOUND)
       fnType = XFT_TF_H3;
    else if(label.Find(wxT("Alpha")) != wxNOT_FOUND)
       fnType = XFT_ALPHA;
    else if(label.Find(wxT("Coherence")) != wxNOT_FOUND)
       fnType = XFT_COHERENCE;
    else if(label.Find(wxT("PU FF Calibration")) != wxNOT_FOUND)
       fnType = XFT_PU_CALIBRATION_FREE_FIELD;
    else if(label.Find(wxT("PU SW Calibration")) != wxNOT_FOUND)
       fnType = XFT_PU_CALIBRATION_SW_TUBE;
    else if(label.Find(wxT("Dirac delta")) != wxNOT_FOUND)
       fnType = XFT_DIRAC_DELTA;
    
    //Search for plot type
    if(label.Find(wxT("Magn.")) != wxNOT_FOUND)
       *type = XFPlot::XPT_MAGNITUDE;
    else if(label.Find(wxT("Phase")) != wxNOT_FOUND)
       *type = XFPlot::XPT_PHASE;
    else if(label.Find(wxT("Real")) != wxNOT_FOUND)
       *type = XFPlot::XPT_REAL;
    else if(label.Find(wxT("Imag.")) != wxNOT_FOUND)
       *type = XFPlot::XPT_IMAGINARY;
    else
       *type = XFPlot::XPT_ADHOC;
    
    //Search for channel
    if(label.Find(wxT("Left")) != wxNOT_FOUND)
       *ch = 0;
    else if(label.Find(wxT("Right")) != wxNOT_FOUND)
       *ch = 1;
    
#ifdef __AUDEBUG__        
    printf("Found %d function, %d plot type and chnl %d\n", fnType, *type, *ch);
#endif

    return fnType;
}


// --- ctors
XFunctions::XFunctions(AFConfig* pCfg)
   : Correlator(),
     m_pProgressDlg(0),
     m_pAuroraCfg(pCfg)
{
   m_awxszXFnNames.Add(wxT("Auto-Correlation"));
   m_awxszXFnNames.Add(wxT("Cross-Correlation"));
   m_awxszXFnNames.Add(wxT("White Cross Correlation"));
   m_awxszXFnNames.Add(wxT("Cross Power Spectrum Ph."));
   m_awxszXFnNames.Add(wxT("Transfer Function H1"));
   m_awxszXFnNames.Add(wxT("Transfer Function H2"));
   m_awxszXFnNames.Add(wxT("Transfer Function H3"));
   m_awxszXFnNames.Add(wxT("Absorp.Coefficient"));

   m_awxszOutputTrackLabels.Add(wxT(" "));                           // NONE = 0,
   m_awxszOutputTrackLabels.Add(wxT("Autocorrelation Left"));        // AUTO_CORRELATION_L,
   m_awxszOutputTrackLabels.Add(wxT("Autocorrelation Right"));       // AUTO_CORRELATION_R ,
   m_awxszOutputTrackLabels.Add(wxT("Crosscorrelation"));            // CROSS_CORRELATION,
   m_awxszOutputTrackLabels.Add(wxT("White correlation"));           // WHITE_CORRELATION,
   m_awxszOutputTrackLabels.Add(wxT("Cross power"));                 // CROSS_POWER,
   m_awxszOutputTrackLabels.Add(wxT("Transfer function H1"));        // TF_H1,
   m_awxszOutputTrackLabels.Add(wxT("Transfer function H2"));        // TF_H2,
   m_awxszOutputTrackLabels.Add(wxT("Transfer function H3"));        // TF_H3,
   m_awxszOutputTrackLabels.Add(wxT("Alpha"));                       // ALPHA,
   m_awxszOutputTrackLabels.Add(wxT("Coherence function"));          // COHERENCE,
   m_awxszOutputTrackLabels.Add(wxT("Dirac delta"));                 // DIRAC_DELTA,
   m_awxszOutputTrackLabels.Add(wxT("PU Probe Calib. SW tube "));    // PU_CAL_SW_TUBE,
   m_awxszOutputTrackLabels.Add(wxT("Pu Probe Calib. Free Field ")); // PU_CAL_FREE_FIELD
   
   // Read parameters value from stored configuration
   ReadConfigurationValues();
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
