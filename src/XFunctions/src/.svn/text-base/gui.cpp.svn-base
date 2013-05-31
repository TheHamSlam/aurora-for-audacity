/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  gui.cpp

  Simone Campanini

*******************************************************************//**

\class XFunctionsDialog 
\brief Dialog used with EffectXFunctions.

*//****************************************************************//**

\class XFunctionsShowDialog
\brief Window that shows xfunctions results.

*//*******************************************************************/

#include <wx/filename.h>

#include <afart.h>
#include <gpfuncts.h>

#include "gui.h"
#include "art.h"
#include "version.h"

//----------------------------------------------------------------------------
// XFunctionsDialog implementation
//----------------------------------------------------------------------------


void XFunctionsDialog::BuildFftChoice(const int nDefaultSel)
{
   //first clear control...
   mFftSizeChoice->Clear();
       
   // ...then fill it...
   wxString wxszValue;
   long   lDataSize = long(m_pXf->GetInputVectorsLength());
   double dbExp     = 9.0; // 2^9 = 512
   long   lSize     = long(pow(2.0, dbExp));
   while(lSize < lDataSize)
   {
       wxszValue.Printf(wxT("%d"), lSize);
       mFftSizeChoice->Append(wxszValue);
       lSize = long(pow(2.0, ++dbExp));
   }
   
   // ...and set default sel.
   if(nDefaultSel < (int(dbExp) - 9))
      mFftSizeChoice->SetSelection(nDefaultSel);
   else 
      mFftSizeChoice->SetSelection(0);
}

void XFunctionsDialog::UpdateLag() 
{
   wxString wxszValue(wxT("- s"));
   
   if(mLagStext->IsEnabled())
   {
      double dbExp = 9.0 + mFftSizeChoice->GetSelection();
      wxszValue.Printf(wxT("%.3f s"), pow(2.0, dbExp)/(2.0*m_pXf->GetSamplerate()));
   }   
   mLagStext->SetLabel(wxszValue);
}

void XFunctionsDialog::OnCloseEvent( wxCloseEvent& event)
{
	EndModal(false);
}

void XFunctionsDialog::OnFftSizeChoice( wxCommandEvent& event )
{
    wxString wxszValue = event.GetString();
    m_pXf->SetFFTLength(AFSampleCount(::StringToLong(wxszValue)));
    UpdateLag();
}

void XFunctionsDialog::OnWindowChoice( wxCommandEvent& event )
{
    m_pXf->SetWindowType(event.GetSelection());
}

void XFunctionsDialog::OnXFunctionChoice( wxCommandEvent& event)
{
   int nSel = event.GetSelection();
   m_pXf->SetXFunctionType(nSel);
   
   if(nSel == XFunctions::XFT_CROSS_CORRELATION)
   {
      mLagLabelStext->Enable();
      mLagStext->Enable();
   }
   else
   {
      mLagLabelStext->Disable();
      mLagStext->Disable();
   }
   UpdateLag();
      
   if(nSel == XFunctions::XFT_ALPHA)
   {
      if(m_pXf->IsProbeRigidTerminated()) nSel += 1;
      if(m_pXf->IsProbeFreeField())       nSel += 2;
   }
   //SetOutputLabels(sel);
   mEquationBmp->SetBitmap(wxArtProvider::GetBitmap(mEquationBitmapPtr[nSel]));
}

void XFunctionsDialog::OnSWTubeCheck( wxCommandEvent& event )
{
    if(mSWTubeCheck->IsChecked())
    {
       m_pXf->SetProbeRigidTerminated(true);
       mFreeFieldCheck->SetValue(false);
       
       if(m_pXf->GetXFunctionType() == XFunctions::XFT_ALPHA) {
           
          //SetOutputLabels(sel);
          mEquationBmp->SetBitmap(wxArtProvider::GetBitmap(mEquationBitmapPtr[XFunctions::XFT_ALPHA + 1]));
       }
    }
    else
    {
        m_pXf->SetProbeRigidTerminated(false);
        if(m_pXf->GetXFunctionType() == XFunctions::XFT_ALPHA)
        {
          //SetOutputLabels(sel);
          mEquationBmp->SetBitmap(wxArtProvider::GetBitmap(mEquationBitmapPtr[XFunctions::XFT_ALPHA]));
       }

    }
}

void XFunctionsDialog::OnFreeFieldCheck( wxCommandEvent& event )
{
    if(mFreeFieldCheck->IsChecked())
    {
       m_pXf->SetProbeFreeField(true);
       mSWTubeCheck->SetValue(false);       
       
       if(m_pXf->GetXFunctionType() == XFunctions::XFT_ALPHA)
       {
          //SetOutputLabels(sel);
          mEquationBmp->SetBitmap(wxArtProvider::GetBitmap(mEquationBitmapPtr[XFunctions::XFT_ALPHA + 2]));
       }
    }
    else
    {
       m_pXf->SetProbeFreeField(false);
       if(m_pXf->GetXFunctionType() == XFunctions::XFT_ALPHA)
       {
          //SetOutputLabels(sel);
          mEquationBmp->SetBitmap(wxArtProvider::GetBitmap(mEquationBitmapPtr[XFunctions::XFT_ALPHA]));
       }
    }
}

void XFunctionsDialog::OnSoundSpeedText( wxCommandEvent& event )
{
    m_pXf->SetSoundSpeed(::TextPtrToDouble(mSoundSpeedText));
}

void XFunctionsDialog::OnProbeDistanceText( wxCommandEvent& event )
{
    m_pXf->SetProbeDistance(::TextPtrToDouble(mProbeDistText));
}

void XFunctionsDialog::OnFmaxText( wxCommandEvent& event )
{
    m_pXf->SetProbeMaxFreq(::TextPtrToDouble(mFmaxText));
}

void XFunctionsDialog::OnEnableFollowingFilterCheck( wxCommandEvent& event )
{
    if(event.IsChecked())
    {
       mFollowLeftRadio->Enable();
       mFollowRightRadio->Enable();
       mBandwidthText->Enable();
    }
    else
    {
       mFollowLeftRadio->Disable();
       mFollowRightRadio->Disable();
       mBandwidthText->Disable();
    }
}

void XFunctionsDialog::OnFollowLeftRadio( wxCommandEvent& event )
{
    m_pXf->SetFollowingChannel(CH_LEFT);
}

void XFunctionsDialog::OnFollowRightRadio( wxCommandEvent& event )
{
    m_pXf->SetFollowingChannel(CH_RIGHT);
}

void XFunctionsDialog::OnBandwidthText( wxCommandEvent& event )
{
    m_pXf->SetFollowingBandwidth(::TextPtrToDouble(mBandwidthText));
}

void XFunctionsDialog::OnNormalizeLeftChannelCheck( wxCommandEvent& event )
{
    m_pXf->SetNormalize(event.IsChecked());
}

void XFunctionsDialog::OnHilbertCheck( wxCommandEvent& event )
{
    m_pXf->SetHilbertTransform(event.IsChecked());
}

void XFunctionsDialog::OnShiftToHalfWindowCheck( wxCommandEvent& event )
{
    m_pXf->SetShiftToHalfWindow(event.IsChecked());
}

void XFunctionsDialog::OnTimeReversalCheck( wxCommandEvent& event )
{
    m_pXf->SetTimeReversal(event.IsChecked());
}

void XFunctionsDialog::OnCoherenceCheck( wxCommandEvent& event )
{
    m_pXf->SetCoherenceWeighting(event.IsChecked());
}

void XFunctionsDialog::OnSaveMultispectrumCheck( wxCommandEvent& event )
{
    m_pXf->SetSaveMultispectrum(event.IsChecked());
}

void XFunctionsDialog::OnTriggerLevelText( wxCommandEvent& event )
{
    m_pXf->SetTriggerLevel(::TextPtrToDouble(mTriggerText));
}

void XFunctionsDialog::OnDiracPulseCheck( wxCommandEvent& event )
{
    m_pXf->SetDiracPulse(event.IsChecked());
}

void XFunctionsDialog::OnHelp( wxCommandEvent& event )
{
    wxString path = wxT("");
    path << wxT("Docs") << TRAILING_SLASH << wxT("x_funct.html");
    wxFileName help_path(path);
    help_path.MakeAbsolute();

    ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void XFunctionsDialog::OnOk( wxCommandEvent& event )
{
    EndModal(true);
}

void XFunctionsDialog::OnCancel( wxCommandEvent& event )
{
    EndModal(false);
}

XFunctionsDialog::XFunctionsDialog(wxWindow* pParent, XFunctions* pXf)
  : XFunctionsDlg(pParent),
    m_pXf(pXf)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Cross Functions Calculation Module - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(XF_VERSION_TYPE, XF_RELEASE_CANDIDATE) << wxT(")");
    SetTitle(wxszTitle);

	// Draw logo
	wxBoxSizer* pLogoSizer;
	pLogoSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pwxbmpAuroraLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                                 AFArtProvider::GetBitmap(wxT("Aurora_logo")),
			                                 wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpAuroraLogo, 0, wxALL, 5 );

	pLogoSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_pwxbmpLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                           AFArtProvider::GetBitmap( wxT("xfn_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();
    

   InitXFunctionsArtProvider();
   
   // equations bitmaps
   mEquationBitmapPtr.Add(wxT("eq_autocorr"));     // XFT_AUTO_CORRELATION,
   mEquationBitmapPtr.Add(wxT("eq_crosscorr"));    // XFT_CROSS_CORRELATION,
   mEquationBitmapPtr.Add(wxT("eq_whitened_csp")); // XFT_WHITE_CORRELATION,
   mEquationBitmapPtr.Add(wxT("eq_crosspower"));   // XFT_CROSS_POWER,
   mEquationBitmapPtr.Add(wxT("eq_h1"));           // XFT_TF_H1,
   mEquationBitmapPtr.Add(wxT("eq_h2"));           // XFT_TF_H2,
   mEquationBitmapPtr.Add(wxT("eq_h3"));           // XFT_TF_H3,
   mEquationBitmapPtr.Add(wxT("eq_alpha"));        // XFT_ALPHA, 
   mEquationBitmapPtr.Add(wxT("eq_pu_swtube"));    //  PU SW
   mEquationBitmapPtr.Add(wxT("eq_pu_freefield")); //  PU FF

   wxString wxszValue;
   
   int nSel = iround(log(double(m_pXf->GetFFTLength())) / log(2.0));
#ifdef __AUDEBUG__   
   printf("nSel: %f -> %d (%d)\n", double(m_pXf->GetFFTLength()), nSel, nSel-9);
#endif
   BuildFftChoice(nSel - 9); // starts from 2^9 = 512
   mWindowChoice->SetSelection(m_pXf->GetWindowType());

   //XFunction type
   nSel = m_pXf->GetXFunctionType();
   mXFunctionChoice->SetSelection(nSel);
   //SetOutputLabels(nSel);
   mEquationBmp->SetBitmap(wxArtProvider::GetBitmap(mEquationBitmapPtr[nSel]));
   
   // Eventually update lag text
   if(nSel == XFunctions::XFT_CROSS_CORRELATION) {
       
      mLagLabelStext->Enable();
      mLagStext->Enable();
      
   } else {
        
      mLagLabelStext->Disable();
      mLagStext->Disable();
   }
   UpdateLag();
   
   // PU Probe stuffs
   mSWTubeCheck->SetValue(m_pXf->IsProbeRigidTerminated());
   mFreeFieldCheck->SetValue(m_pXf->IsProbeFreeField());
   wxszValue.Printf(wxT("%.f"), m_pXf->GetSoundSpeed());
   mSoundSpeedText->SetValue(wxszValue);
   wxszValue.Printf(wxT("%.1f"), m_pXf->GetProbeDistance());
   mProbeDistText->SetValue(wxszValue);
   wxszValue.Printf(wxT("%.1f"), m_pXf->GetProbeMaxFreq());
   mFmaxText->SetValue(wxszValue);

   //Following filter stuffs
   mEnableFFilterCheck->SetValue(m_pXf->IsFollowingFilterEnabled());
   wxszValue.Printf(wxT("%.3f"), m_pXf->GetFollowingBandwidth());
   mBandwidthText->SetValue(wxszValue);
   
   // Checkers init
   mNormalizeLeftCheck->SetValue(m_pXf->IsNormalizeSet());
   mHilbertCheck->SetValue(m_pXf->IsHilbertTransformSet());
   mShiftToHalfCheck->SetValue(m_pXf->IsShiftToHalfWindowSet());
   mTimeReversalCheck->SetValue(m_pXf->IsTimeReversalSet());
   mCoherenceCheck->SetValue(m_pXf->IsCoherenceWeightingSet());
   mSaveMultispectrumCheck->SetValue(m_pXf->IsSaveMultispectrumSet());
   mDiracCheck->SetValue(m_pXf->IsDiracPulseSet());
   
   wxszValue.Printf(wxT("%.1f"), m_pXf->GetTriggerLevel());
   mTriggerText->SetValue(wxszValue);
}

//----------------------------------------------------------------------------
// XFunctionsShowDialog implementation
//----------------------------------------------------------------------------
void XFunctionsShowDialog::AddPlotDataSeries(XFPlot* pPlot, const wxColour& wxcolLine)
{
	XFSpectrumDataSerie *pBaseDataSerie, *pDataSerie;
	pBaseDataSerie = new XFSpectrumDataSerie(m_pXf->GetFunctionSpectrum(),
			                                 m_pXf->GetSpectrumLength(),
	                                         double(m_pXf->GetSamplerate()));

	pBaseDataSerie->SetAutocorrelationLeft(m_pXf->GetAutocorrelationSpectrum(CH_LEFT));
	pBaseDataSerie->SetAutocorrelationRight(m_pXf->GetAutocorrelationSpectrum(CH_RIGHT));
	pBaseDataSerie->SetCrosscorrelation(m_pXf->GetCrosscorrelationSpectrum());
	pBaseDataSerie->SetCoherence(m_pXf->GetCoherenceSpectrum());
	pBaseDataSerie->SetLineColour(wxcolLine);
    pBaseDataSerie->Show(false);
	pPlot->AddSerie(pBaseDataSerie); //with default handler: HT_AUTOCORR_L

	pDataSerie = pBaseDataSerie->Clone();
	pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_AUTOCORR_R);
	pPlot->AddSerie(pDataSerie);

	int nXFnType = m_pXf->GetXFunctionType();

	if(nXFnType != XFunctions::XFT_AUTO_CORRELATION)
    {
		// Add magnitude, phase, real, imag. series
		pDataSerie = pBaseDataSerie->Clone();
		pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_MAGNITUDE);
		pPlot->AddSerie(pDataSerie);

		pDataSerie = pBaseDataSerie->Clone();
		pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_PHASE);
		pPlot->AddSerie(pDataSerie);

		pDataSerie = pBaseDataSerie->Clone();
		pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_REAL);
		pPlot->AddSerie(pDataSerie);

		pDataSerie = pBaseDataSerie->Clone();
		pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_IMAGINARY);
		pPlot->AddSerie(pDataSerie);
    }

	if(nXFnType != XFunctions::XFT_ALPHA)
	{
		// Add alpha, coherence plot
		pDataSerie = pBaseDataSerie->Clone();
		pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_ALPHA);
		pPlot->AddSerie(pDataSerie);

		pDataSerie = pBaseDataSerie->Clone();
		pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_COHERENCE);
		pPlot->AddSerie(pDataSerie);
	}
	else if(!m_pXf->IsProbeFreeField() && !m_pXf->IsProbeRigidTerminated())
	{
		pDataSerie = pBaseDataSerie->Clone();
		pDataSerie->SetHandlerId(XFSpectrumDataSerie::HT_COHERENCE);
		pPlot->AddSerie(pDataSerie);
	}
}

void XFunctionsShowDialog::UpdatePlotData(XFPlot* pPlot, wxString& wxszPlotName)
{
	int nPlotType;
    if(!pPlot->SetPlotTypeByString(wxszPlotName, nPlotType))
    {
    	printf("Plot not found!\n");
    	return;
    }
    bool bIsLog = !mLinearScaleCheck->IsChecked();

	pPlot->GetFreqAxis()->SetTitle(wxT("Frequency [Hz]"));
	pPlot->GetFreqAxis()->SetFormat(AFAxisBase::RF_REAL);
	pPlot->GetFreqAxis()->SetLog(bIsLog);
	SetFrequencyRange(pPlot, mFrequencyRangeChoice->GetSelection(), bIsLog);

	switch(nPlotType)
	{
		case XFPlot::XPT_AUTOCORR_L:
		case XFPlot::XPT_AUTOCORR_R:
		case XFPlot::XPT_MAGNITUDE:
		case XFPlot::XPT_REAL:
		case XFPlot::XPT_IMAGINARY:
			pPlot->GetLevelAxis()->SetTitle(wxT("Level [dB]"));
			pPlot->GetLevelAxis()->SetRange(-80.0, 80.0, AFAxisBase::RF_LINEARdB);
			break;

		case XFPlot::XPT_COHERENCE:
			pPlot->GetLevelAxis()->SetTitle(wxT("Coherence"));
	        pPlot->GetLevelAxis()->SetRange(0, 1, AFAxisBase::RF_REAL);
			break;

		case XFPlot::XPT_PHASE:
			pPlot->GetLevelAxis()->SetTitle(wxT("Degrees [°]"));
	        pPlot->GetLevelAxis()->SetRange(-180, 180, AFAxisBase::RF_REAL);
			break;

		case XFPlot::XPT_ALPHA:
			pPlot->GetLevelAxis()->SetTitle(wxT("Alpha"));
	        pPlot->GetLevelAxis()->SetRange(0.0, 1.2, AFAxisBase::RF_REAL);
			break;
	}
    pPlot->SetHorzAxisAutorange(false);
    pPlot->SetVertAxisAutorange(false);
}

void XFunctionsShowDialog::GetChoiceItems(wxArrayString& awxszList)
{
   awxszList.Clear();
   wxString wxszFnName = wxT("Autocorrelation");
   awxszList.Add(wxszFnName + wxT(" Left"));
   awxszList.Add(wxszFnName + wxT(" Right"));

   int nXFnType = m_pXf->GetXFunctionType();
   switch(nXFnType)
   {
      case XFunctions::XFT_AUTO_CORRELATION:
         break;

      case XFunctions::XFT_CROSS_CORRELATION:
         wxszFnName = wxT("Crosscorrelation");
         break;

      case XFunctions::XFT_WHITE_CORRELATION:
         wxszFnName = wxT("White Crosscorr.");
         break;

      case XFunctions::XFT_CROSS_POWER:
         wxszFnName = wxT("Cross-Power Spect.");
         break;

      case XFunctions::XFT_TF_H1:
         wxszFnName = wxT("H1");
         break;

      case XFunctions::XFT_TF_H2:
         wxszFnName = wxT("H2");
         break;

      case XFunctions::XFT_TF_H3:
         wxszFnName = wxT("H3");
         break;

      case XFunctions::XFT_ALPHA:

         if(m_pXf->IsProbeFreeField())
         {
            awxszList.Add(wxT("PU FF Calibration"));
            wxszFnName = wxT("Dirac delta");
//          awxszList.Add(wxT("Alpha"));
         }
         else if(m_pXf->IsProbeRigidTerminated())
         {
            awxszList.Add(wxT("PU SW Calibration"));
            wxszFnName = wxT("Dirac delta");
//          awxszList.Add(wxT("Alpha"));
         }
         else // alpha
         {
            wxszFnName = wxT("Alpha");
            awxszList.Add(wxT("Coherence"));
//          awxszList.Add(wxT("Alpha"));
         }
         break;
   }

   if(nXFnType != XFunctions::XFT_AUTO_CORRELATION)
   {
	   awxszList.Add(wxszFnName + wxT(" Magn."));
	   awxszList.Add(wxszFnName + wxT(" Phase"));
	   awxszList.Add(wxszFnName + wxT(" Real"));
	   awxszList.Add(wxszFnName + wxT(" Imag."));
   }

   if(nXFnType != XFunctions::XFT_ALPHA)
   {
	   awxszList.Add(wxT("Coherence"));
	   awxszList.Add(wxT("Alpha"));
   }
   else if(!m_pXf->IsProbeFreeField() && !m_pXf->IsProbeRigidTerminated())
   {
	   awxszList.Add(wxT("Coherence"));
   }
}


void XFunctionsShowDialog::BuildPlotChoice(wxChoice* pwxchoiceItem, const int nDefaultSel)
{
   //first clear control...
	pwxchoiceItem->Clear();
       
   // ...then fill it...
   wxArrayString awxszList;
   GetChoiceItems(awxszList);
   for(unsigned int i = 0; i < awxszList.GetCount(); i++)
	   pwxchoiceItem->Append(awxszList[i]);
   
   // ...and set default selection
   pwxchoiceItem->SetSelection(nDefaultSel);
}

void XFunctionsShowDialog::SetPlotLagAxis(XFPlot* pPlot)
{
	// TODO: deprecated???
   double dbLag = double( m_pXf->GetSpectrumLength()/(2.0*m_pXf->GetSamplerate()) );
   pPlot->GetFreqAxis()->SetTitle(wxT("Lag [s]"));
   pPlot->GetFreqAxis()->SetLog(false);
   pPlot->GetFreqAxis()->SetRange(-dbLag, dbLag);
}

void XFunctionsShowDialog::SetFrequencyRange(XFPlot* pPlot, const int nChoice, const bool bIsLog)
{
	switch(nChoice)
	{
		case 0 : pPlot->GetFreqAxis()->SetRange( (bIsLog) ? 1.0 : 0.0,
				                                  2000.0 );                    break; // 0 -> 2kHz
		case 1 : pPlot->GetFreqAxis()->SetRange( (bIsLog) ? 1.0 : 0.0,
				                                 m_pXf->GetSamplerate()/2.0 ); break; // 0 -> Fny
	}
}


void XFunctionsShowDialog::OnCloseEvent( wxCloseEvent& event)
{
	StoreGeometry();
	EndModal(false);

}
void XFunctionsShowDialog::OnFrequencyRangeChoice( wxCommandEvent& event )
{
   int nChoice = event.GetSelection();
   SetFrequencyRange(mUpperPlot, nChoice, !mLinearScaleCheck->IsChecked());
   SetFrequencyRange(mLowerPlot, nChoice, !mLinearScaleCheck->IsChecked());
   mUpperPlot->Refresh();
   mLowerPlot->Refresh();
}

void XFunctionsShowDialog::OnLinearScaleCheck( wxCommandEvent& event )
{
   if(event.IsChecked())
   {
	   printf("[gui] Got check event. Setting to REAL\n");
       mUpperPlot->GetFreqAxis()->SetLog(false);
       mLowerPlot->GetFreqAxis()->SetLog(false);
   }
   else
   {
	   printf("[gui] Got check event. Setting to REALLOG\n");
       mUpperPlot->GetFreqAxis()->SetLog(true);
       mLowerPlot->GetFreqAxis()->SetLog(true);
   }
   mUpperPlot->Refresh();
   mLowerPlot->Refresh();
}

void XFunctionsShowDialog::OnSaveToTimeDelayCheck( wxCommandEvent& event )
{
	// eventually TODO but in fact not needed. See OnClose
}

void XFunctionsShowDialog::OnExportAllSpectrumsCheck( wxCommandEvent& event )
{
	mExportData.SetExportAll(event.IsChecked());
}

void XFunctionsShowDialog::OnSaveSpectrumBtn( wxCommandEvent& event )
{
	double dbMin, dbMax;
	mUpperPlot->GetFreqAxis()->GetRange(dbMin, dbMax); // These should be the same for both.
	mExportData.SetFrequencyBounds(dbMin, dbMax);

	mExportData.SaveToFile();
}

void XFunctionsShowDialog::OnCopySpectrumBtn( wxCommandEvent& event )
{
	double dbMin, dbMax;
	mUpperPlot->GetFreqAxis()->GetRange(dbMin, dbMax); // These should be the same for both.
	mExportData.SetFrequencyBounds(dbMin, dbMax);

	mExportData.CopyEntireTableToClipboard();
}

void XFunctionsShowDialog::OnExportWaveformsCheck( wxCommandEvent& event )
{
    // eventually TODO but in fact not needed. See OnClose
}

void XFunctionsShowDialog::OnFirstPlotChoice( wxCommandEvent& event )
{
    wxString wxszLabel = mFirstPlotChoice->GetString(event.GetSelection());
//    mUpperPlot->SetPlotTypeByString(wxszLabel);
    UpdatePlotData(mUpperPlot, wxszLabel);

    mUpperPlot->Refresh();
}

void XFunctionsShowDialog::OnSecondPlotChoice( wxCommandEvent& event )
{
    wxString wxszLabel = mSecondPlotChoice->GetString(event.GetSelection());
//    mLowerPlot->SetPlotTypeByString(wxszLabel);
    UpdatePlotData(mLowerPlot, wxszLabel);

    mLowerPlot->Refresh();
}

void XFunctionsShowDialog::OnHelp( wxCommandEvent& event )
{
    wxString path = wxT("");
    path << wxT("Docs") << TRAILING_SLASH << wxT("x_funct.html");
    wxFileName help_path(path);
    help_path.MakeAbsolute();

    ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void XFunctionsShowDialog::OnClose( wxCommandEvent& event )
{
   if(mSaveToTimeDelayCheck->IsEnabled())
      if(mSaveToTimeDelayCheck->IsChecked())
         mExportData.AppendTimeDelay( m_pXf->GetTriggerTime(),
        		                      m_pXf->GetXCorrelationMaxDelay() );
      
   StoreGeometry();
   EndModal(mExportWaveformsCheck->IsChecked());
}

void XFunctionsShowDialog::StoreGeometry()
{
	int nWidth, nHeight;
	this->GetSize(&nWidth, &nHeight);

//	int nHorzSplitPos = m_pHorzSplitter->GetSashPosition();

	m_pCfg->Write(wxT("/Aurora/XFunctions/ShowDialogWidth"), nWidth);
	m_pCfg->Write(wxT("/Aurora/XFunctions/ShowDialogHeight"), nHeight);
//	m_pCfg->Write(wxT("/Aurora/XFunctions/HorzSplitterPosition"), nHorzSplitPos);
}

void XFunctionsShowDialog::RestoreGeometry()
{
//	int nPos;
//	if(m_pCfg->Read(wxT("/Aurora/XFunctions/HorzSplitterPosition"), &nPos))
//	    m_pHorzSplitter->SetSashPosition(nPos);

	int nWidth, nHeight;
    if(m_pCfg->Read(wxT("/Aurora/XFunctions/ShowDialogWidth"), &nWidth) &&
       m_pCfg->Read(wxT("/Aurora/XFunctions/ShowDialogHeight"), &nHeight))
    {
        this->SetSize(nWidth, nHeight);
    }
}


XFunctionsShowDialog::XFunctionsShowDialog(wxWindow* pParent, XFunctions *pXf, AFConfig* pCfg)
  : XFunctionsShowDlg(pParent),
    m_pXf(pXf),
    mExportData(pParent),
    m_pCfg(pCfg)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Cross Functions Calculation Module - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(XF_VERSION_TYPE, XF_RELEASE_CANDIDATE) << wxT(")");
    SetTitle(wxszTitle);

	// Draw logo
	wxBoxSizer* pLogoSizer;
	pLogoSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pwxbmpAuroraLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                                 AFArtProvider::GetBitmap(wxT("Aurora_logo")),
			                                 wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpAuroraLogo, 0, wxALL, 5 );

	pLogoSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_pwxbmpLogo = new wxStaticBitmap( m_pwxpnlLogo, wxID_ANY,
			                           AFArtProvider::GetBitmap( wxT("xfn_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();


   wxString wxszValue;
   // ------- Fill Result boxes
   // Input waveform
   wxszValue.Printf(wxT("%d"), int(m_pXf->GetFFTLength()));
   mFftSizeStext->SetLabel(wxszValue);
   wxszValue.Printf(wxT("%d"), int(m_pXf->GetSamplerate()));
   mRateStext->SetLabel(wxszValue);
   wxszValue.Printf(wxT("%d"), int(m_pXf->GetBlocksNumber()));
   mNblocksStext->SetLabel(wxszValue);
    
   // Statistics
   mTransformTypeStext->SetLabel(m_pXf->GetCurrentXFunctionLabel());
   wxszValue.Printf(wxT("%.2f"), m_pXf->GetRMS(CH_LEFT));
   mRmsLeftStext->SetLabel(wxszValue);
   wxszValue.Printf(wxT("%.2f"), m_pXf->GetRMS(CH_RIGHT));
   mRmsRightStext->SetLabel(wxszValue);
   wxszValue.Printf(wxT("%.2f"), m_pXf->GetRMS(XFunctions::CH_CROSS));
   mRmsCrossStext->SetLabel(wxszValue);
    
   // Time of flight (only for Cross-Correlation)
   if(m_pXf->GetXFunctionType() == XFunctions::XFT_CROSS_CORRELATION)
   {
      mTimeOfFlightStext->Enable();
      mTriggerTimeLabelStext->Enable();
      mTriggerTimeStext->Enable();
      mTriggerTimeAtStext->Enable();
      mTriggerDelayStext->Enable();
       
      mNccMaxLabelStext->Enable();
      mNccMaxStext->Enable();
      mNccMaxAtStext->Enable();
      mNccMaxDelayStext->Enable();
       
      mSaveToTimeDelayCheck->Enable();
       
      wxszValue.Printf(wxT("%.1f%%"), m_pXf->GetTriggerLevel());
      mTriggerTimeStext->SetLabel(wxszValue);
      wxszValue.Printf(wxT("%.3f s"), m_pXf->GetTriggerTime());
      mTriggerDelayStext->SetLabel(wxszValue);
 
      wxszValue.Printf(wxT("%.4f"), m_pXf->GetXCorrelationMax());
      mNccMaxStext->SetLabel(wxszValue);
      wxszValue.Printf(wxT("%.3f s"), m_pXf->GetXCorrelationMaxDelay());
      mNccMaxDelayStext->SetLabel(wxszValue);
   }
   else
   {
      wxszValue.Printf(wxT("- %%"));
      mTriggerTimeStext->SetLabel(wxszValue);
      wxszValue.Printf(wxT("- s"));
      mTriggerDelayStext->SetLabel(wxszValue);
 
      wxszValue.Printf(wxT("- %%"));
      mNccMaxStext->SetLabel(wxszValue);
      wxszValue.Printf(wxT("- s"));
      mNccMaxDelayStext->SetLabel(wxszValue);
   }
   BuildPlotChoice(mFirstPlotChoice, 0);
   BuildPlotChoice(mSecondPlotChoice, 1);

   // By default horizontal axis is linear
   mLinearScaleCheck->SetValue(true);

   AddPlotDataSeries(mUpperPlot, *wxBLUE);
   AddPlotDataSeries(mLowerPlot, *wxRED);

   wxszValue = mFirstPlotChoice->GetStringSelection();
   UpdatePlotData(mUpperPlot, wxszValue);
   wxszValue = mSecondPlotChoice->GetStringSelection();
   UpdatePlotData(mLowerPlot, wxszValue);

   mUpperPlot->GetFreqAxis()->ShowGrid(true);
   mUpperPlot->GetFreqAxis()->ShowTitle(true);
   mUpperPlot->GetLevelAxis()->ShowGrid(true);
   mUpperPlot->GetLevelAxis()->ShowTitle(true);
   mUpperPlot->SetTopBorder(false);

   mLowerPlot->GetFreqAxis()->ShowGrid(true);
   mLowerPlot->GetFreqAxis()->ShowTitle(true);
   mLowerPlot->GetLevelAxis()->ShowGrid(true);
   mLowerPlot->GetLevelAxis()->ShowTitle(true);
   mLowerPlot->SetTopBorder(false);

   mUpperPlot->Refresh();
   mLowerPlot->Refresh();
   
//   mExportData.SetDataPlot(mUpperPlot, mLowerPlot);
   wxszValue = m_pXf->GetCurrentXFunctionLabel();
   mExportData.SetFunctionLabel(wxszValue);
   mExportData.SetDataSeriesArray(mUpperPlot->GetDataSeriesArray(), 0);
   mExportData.SetDataSeriesArray(mLowerPlot->GetDataSeriesArray(), 1);

   RestoreGeometry();
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
