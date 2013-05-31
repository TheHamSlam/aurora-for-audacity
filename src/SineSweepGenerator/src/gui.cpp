/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Sine Sweep Signal Generator

  gui.cpp

  Simone Campanini

*******************************************************************//**

\class SineSweepGeneratorDialog 
\brief Dialog used with EffectSineSweepGenerator.

*//*******************************************************************/

#include <commdefs.h>
#include "gui.h"

#include <afart.h>
#include <gpfuncts.h>
#include "version.h"

//----------------------------------------------------------------------------
// SineSweepGeneratorDialog
//----------------------------------------------------------------------------

void SineSweepGeneratorDialog::OnStartFrequencyText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnEndFrequencyText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnSweepDurationText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnAmplitudeText( wxCommandEvent& event )
{
}
void SineSweepGeneratorDialog::OnSweepChannelsChoice( wxCommandEvent& event )
{
   m_pSsg->SetSweepChnlsNumber(event.GetSelection()+1);
}

void SineSweepGeneratorDialog::OnLinearSweepRadio( wxCommandEvent& event )
{
   m_pSsg->SetSweepType(SineSweepGenerator::ST_LINEAR);
}

void SineSweepGeneratorDialog::OnLogSweepRadio( wxCommandEvent& event )
{
   m_pSsg->SetSweepType(SineSweepGenerator::ST_LOG);
}

void SineSweepGeneratorDialog::OnPinkSweepRadio( wxCommandEvent& event )
{
   m_pSsg->SetSweepType(SineSweepGenerator::ST_PINK);
}

void SineSweepGeneratorDialog::OnFadeInText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnFadeInChoice( wxCommandEvent& event )
{
    m_pSsg->SetFadeInType(event.GetSelection());
}

void SineSweepGeneratorDialog::OnFadeOutText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnFadeOutChoice( wxCommandEvent& event )
{
   m_pSsg->SetFadeOutType(event.GetSelection());
}

void SineSweepGeneratorDialog::OnSilenceDurationText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnRepetitionsText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnDeltaLText( wxCommandEvent& event )
{
}

void SineSweepGeneratorDialog::OnControlPulsesCheck( wxCommandEvent& event )
{

}


void SineSweepGeneratorDialog::OnOk( wxCommandEvent& event )
{
	wxWindow*  pWnd = FindWindowById(ID_START_FREQ_TEXT, this);
	wxTextCtrl* pTc = wxDynamicCast(pWnd, wxTextCtrl);
	double  dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetStartFrequency(dbValue);

	pWnd = FindWindowById(ID_END_FREQ_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetEndFrequency(dbValue);

	pWnd = FindWindowById(ID_DURATION_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetSweepDuration(dbValue);

	pWnd = FindWindowById(ID_AMPLITUDE_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetAmplitude(dbValue);

	pWnd = FindWindowById(ID_CHANNELS_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	long lValue = ::TextPtrToLong(pTc);
	m_pSsg->SetSweepChnlsNumber(lValue);

	pWnd = FindWindowById(ID_FADE_IN_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetFadeInDuration(dbValue);

	pWnd = FindWindowById(ID_FADE_OUT_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetFadeOutDuration(dbValue);

	pWnd = FindWindowById(ID_SILENCE_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetSilenceDuration(dbValue);

	pWnd = FindWindowById(ID_REPETITIONS_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	lValue = ::TextPtrToLong(pTc);
	m_pSsg->SetRepetitionsNumber(lValue);

	pWnd = FindWindowById(ID_DELTA_L_TEXT, this);
	pTc  = wxDynamicCast(pWnd, wxTextCtrl);
	dbValue = ::TextPtrToDouble(pTc);
	m_pSsg->SetDeltaL(dbValue);

	m_pSsg->SetControlPulses(m_pwxchkPulses->IsChecked());

    if( m_pSsg->ErrorCheck() != SineSweepGenerator::ERR_OK)
    {
    	wxString wxszMsg;
    	m_pSsg->GetErrorMessage(wxszMsg);
    	::wxMessageBox(wxszMsg, wxT("Error"), wxOK | wxICON_ERROR);
		return;
	}

    EndModal(true);
}

void SineSweepGeneratorDialog::OnCancel( wxCommandEvent& event )
{
    EndModal(false);
}

void SineSweepGeneratorDialog::OnHelp( wxCommandEvent& event )
{
    // TODO: Implement OnHelp
}

SineSweepGeneratorDialog::SineSweepGeneratorDialog(SineSweepGenerator* pSsg, wxWindow* pParent)
  : SsgDlg( pParent ),
    m_pSsg(pSsg)
{    
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Sine Sweep Gen. - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(SSG_VERSION_TYPE, SSG_RELEASE_CANDIDATE) << wxT(")");
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
			                           AFArtProvider::GetBitmap( wxT("ssg_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();
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

