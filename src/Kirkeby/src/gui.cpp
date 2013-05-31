/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Invert Kirkeby

  gui.cpp

  Simone Campanini

*******************************************************************//**

\class KirkebyDialog 
\brief Dialog used with EffectKirkeby.

*//*******************************************************************/

#include <wx/filename.h>

#include <afart.h>
#include <gpfuncts.h>
#include "gui.h"
#include "version.h"

//----------------------------------------------------------------------------
// KirkebyDialog implementation
//----------------------------------------------------------------------------

/*void KirkebyDialog::BuildFilterLengthList()
{
    wxString wxszValue;
    int nLength = int(m_pKirk->GetInverseFilterLength());
    int nExp = ::AuroraNearTwoPowerExp(double(nLength));
    m_pwxcmbFilterLength->Clear();
    while( nExp < 20)
    {
        wxszValue.Printf(wxT("%d"), int(pow(2.0, double(nExp))));
//        printf("%s\n", (const char*)wxszValue.ToAscii()); // DEBUG
        m_pwxcmbFilterLength->Append(wxszValue);
        nExp++;
    }
    m_pwxcmbFilterLength->SetSelection(0); //The best should be the first...
}
*/
// -------- Events manager
void KirkebyDialog::OnMonoFilteringRadio( wxCommandEvent& event )
{
    m_pKirk->SetFilterType(Kirkeby::IK_MONO);
    mCrossTalkCheck->Disable();
    mMultiIRsCheck->Enable();
    int nCols = 1;
    if(mMultiIRsCheck->IsChecked())
    {
      if(!(nCols = ::TextPtrToInt(mMultiIRText))) nCols = 1;
      
    }
    m_pKirk->SetCols(nCols);    
    
    m_pwxtcFilterLength->SetValue(wxString::Format(wxT("%d"), m_pKirk->GetColumnLength()));    
//    BuildFilterLengthList();
}

void KirkebyDialog::OnStereoFilteringRadio( wxCommandEvent& event )
{
    m_pKirk->SetFilterType(Kirkeby::IK_STEREO);
    mCrossTalkCheck->Enable();
    mMultiIRsCheck->Disable();
    m_pKirk->SetCols(2);        // TODO: check if it is the desired behaviour

    m_pwxtcFilterLength->SetValue(wxString::Format(wxT("%d"), m_pKirk->GetColumnLength()));
//    BuildFilterLengthList();
}

void KirkebyDialog::OnDipoleFilteringRadio( wxCommandEvent& event )
{
    m_pKirk->SetFilterType(Kirkeby::IK_DIPOLE);
    mCrossTalkCheck->Enable();
    mMultiIRsCheck->Disable();
    m_pKirk->SetCols(2);

    m_pwxtcFilterLength->SetValue(wxString::Format(wxT("%d"), m_pKirk->GetColumnLength()));    
//    BuildFilterLengthList();
}

void KirkebyDialog::OnCrossTalkCheck( wxCommandEvent& event )
{
   m_pKirk->SetCancelCrosstalk(event.IsChecked());
}

void KirkebyDialog::OnMultiIRCheck( wxCommandEvent& event )
{
   int nCols;
   if(event.IsChecked())
   {
      mMultiIRNumberLabelStext->Enable();
      mMultiIRText->Enable();
      if(!(nCols = ::TextPtrToInt(mMultiIRText))) nCols = 1;
      m_pKirk->SetCols(nCols);
   }
   else
   {
      mMultiIRNumberLabelStext->Disable();
      mMultiIRText->Disable();
   }
}

void KirkebyDialog::OnMultiIrText( wxCommandEvent& event )
{
   int nCols = ::TextPtrToInt(mMultiIRText);
   if(nCols <= 0)
   {
       nCols = 1;
       mMultiIRText->SetValue(wxString::Format(wxT("1")));
   }
   m_pKirk->SetCols(nCols);

   m_pwxtcFilterLength->SetValue(wxString::Format(wxT("%d"), m_pKirk->GetColumnLength()));    
   //   BuildFilterLengthList();
}

/*
void KirkebyDialog::OnFilterLengthCombo( wxCommandEvent& event )
{
    long lLength;
    event.GetString().ToLong(&lLength);
    if(lLength < m_pKirk->GetInverseFilterLength())
        lLength = m_pKirk->GetInverseFilterLength();
        
    m_pKirk->SetInverseFilterLength(AFSampleCount(lLength));
}

void KirkebyDialog::OnFilterLengthText( wxCommandEvent& event )
{
    AFSampleCount smpcLength = 0;
    //smpcLength = AFSampleCount(TextPtrToInt(mFilterLengthText)); //TODO Get text from combo line !!!!!!!!!!!!!!!!!!
    if(smpcLength < m_pKirk->GetInverseFilterLength())
    {
        wxString wxszValue;
        smpcLength = m_pKirk->GetInverseFilterLength();
        wxszValue.Printf(wxT("%d"), int(smpcLength));
        m_pwxcmbFilterLength->SetValue(wxszValue);
    }
    
    m_pKirk->SetInverseFilterLength(smpcLength);
}
*/
void KirkebyDialog::OnIRPText( wxCommandEvent& event )
{
   m_pKirk->SetInBandRegularisationParameter(::TextPtrToDouble(mIRPText));
}

void KirkebyDialog::OnORPText( wxCommandEvent& event )
{
   m_pKirk->SetOutBandRegularisationParameter(::TextPtrToDouble(mORPText));
}

void KirkebyDialog::OnLowerCutFrqText( wxCommandEvent& event )
{
   m_pKirk->SetLowerCutFrequency(::TextPtrToDouble(mLowerCutFrqText));
}

void KirkebyDialog::OnHigherCutFrqText( wxCommandEvent& event )
{
   m_pKirk->SetHigherCutFrequency(::TextPtrToDouble(mHigherCutFrqText));
}

void KirkebyDialog::OnTransitionWidthText( wxCommandEvent& event )
{
   m_pKirk->SetTransitionWidth(::TextPtrToDouble(mTransWidthText));
}

void KirkebyDialog::OnFadeInText( wxCommandEvent& event )
{
   m_pKirk->SetFadeInLength(AFSampleCount(::TextPtrToInt(mFadeInText)));
}

void KirkebyDialog::OnFadeOutText( wxCommandEvent& event )
{
   m_pKirk->SetFadeOutLength(AFSampleCount(::TextPtrToInt(mFadeOutText)));
}

void KirkebyDialog::OnAverageModeChoice( wxCommandEvent& event )
{
   int sel = event.GetSelection();
   if(sel > 0)
   {
       mAverageTypeLabelStext->Enable();
       mAverageTypeChoice->Enable();
       mAverageWidthLabelStext->Enable();
       mAverageWidthText->Enable();
       mAvgWidthMUStext->Enable();
   }
   else
   {
       mAverageTypeLabelStext->Disable();
       mAverageTypeChoice->Disable();
       mAverageWidthLabelStext->Disable();
       mAverageWidthText->Disable();
       mAvgWidthMUStext->Disable();
   }
   m_pKirk->SetAverageMode(sel);
}

void KirkebyDialog::OnAverageTypeChoice( wxCommandEvent& event )
{
   int sel = event.GetSelection();
   switch(sel)
   {
       case 0: mAvgWidthMUStext->SetLabel(wxT("Spectral points")); break;
       case 1: mAvgWidthMUStext->SetLabel(wxT("Octaves")); break;
   }
   m_pKirk->SetAverageType(sel);
}

void KirkebyDialog::OnAverageWidthText( wxCommandEvent& event )
{
   // TODO Has to be converted to spectral point if necessary
   double w = ::TextPtrToDouble(mAverageWidthText);
   m_pKirk->SetAverageWidth(w);
}

void KirkebyDialog::OnAutorangeCheck( wxCommandEvent& event )
{
   if(event.IsChecked())
   {
       mGainLabelStext->Disable();
       mGainText->Disable();
       mGainMUStext->Disable();
       m_pKirk->SetAutorange(true);
   }
   else
   {
       mGainLabelStext->Enable();
       mGainText->Enable();
       mGainMUStext->Enable();
       m_pKirk->SetAutorange(false);
   }
}

void KirkebyDialog::OnGainText( wxCommandEvent& event )
{
   m_pKirk->SetGaindB(::TextPtrToDouble(mGainText));
}

void KirkebyDialog::OnHelp( wxCommandEvent& event )
{
    wxString path = wxT("");
    path << wxT("Docs") << TRAILING_SLASH << wxT("kirk_filt.html");
    wxFileName help_path(path);
    help_path.MakeAbsolute();

    ::wxLaunchDefaultBrowser(help_path.GetFullPath());
}

void KirkebyDialog::OnCancel( wxCommandEvent& event )
{
   EndModal(false);
}

void KirkebyDialog::OnOk( wxCommandEvent& event )
{
    int nFilterLength = ::TextPtrToInt(m_pwxtcFilterLength);
    if(nFilterLength <= 0 ||
       nFilterLength > int(m_pKirk->GetInverseFilterLength()))
    {
        ::wxMessageBox(wxT("Wrong filter length: must be > 0 and not longer than the source track."), 
                       wxT("Error"), wxOK | wxICON_ERROR);
        return;
    }
   EndModal(true);
}

// ---- 'ctors
KirkebyDialog::KirkebyDialog(wxWindow* pParent, Kirkeby* pKirk, const bool bIsStereo)
  : KirkebyDlg( pParent ), 
    m_pKirk(pKirk)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - Kirkeby Filter Inversion Tool - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(IK_VERSION_TYPE, IK_RELEASE_CANDIDATE) << wxT(")");
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
			                           AFArtProvider::GetBitmap( wxT("kirk_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();

	// Init widgets
    m_pwxrbMonoFiltering->SetValue(true);
    
    wxString wxszValue;
    wxszValue.Printf( wxT("%.1f"), m_pKirk->GetSamplerate());
    m_pwxstRate->SetLabel(wxszValue);

    wxszValue.Printf( wxT("%d"), m_pKirk->GetRows());
    m_pwxstChnls->SetLabel(wxszValue);

    wxszValue.Printf( wxT("%d"), int(m_pKirk->GetRowLength()));
    m_pwxstLength->SetLabel(wxszValue);

   if(m_pKirk->GetChannels() == 2)
   {
        m_pwxrbStereoFiltering->Enable();
        m_pwxrbDipoleFiltering->Enable();
   }

   // Setup filter length combo box
   //BuildFilterLengthList();    
    wxszValue.Printf(wxT("%d"), int(m_pKirk->GetInverseFilterLength()));
    m_pwxtcFilterLength->SetValue(wxszValue);
    
    if(!bIsStereo) 
        m_pwxrbMonoFiltering->SetLabel(wxT("Mono (no CrossTalk cancellation)"));
    
   wxszValue.Printf(wxT("%.3f"), m_pKirk->GetInBandRegularisationParameter());
   mIRPText->SetValue(wxszValue);
   wxszValue.Printf(wxT("%.3f"), m_pKirk->GetOutBandRegularisationParameter());
   mORPText->SetValue(wxszValue);
   
   wxszValue.Printf(wxT("%.1f"), m_pKirk->GetLowerCutFrequency());
   mLowerCutFrqText->SetValue(wxszValue);
   wxszValue.Printf(wxT("%.1f"), m_pKirk->GetHigherCutFrequency());
   mHigherCutFrqText->SetValue(wxszValue);
   
   wxszValue.Printf(wxT("%.3f"), m_pKirk->GetTransitionWidth());
   mTransWidthText->SetValue(wxszValue);
   
   wxszValue.Printf(wxT("%d"), int(m_pKirk->GetFadeInLength()));
   mFadeInText->SetValue(wxszValue);
   wxszValue.Printf(wxT("%d"), int(m_pKirk->GetFadeOutLength()));
   mFadeOutText->SetValue(wxszValue);
   
   int sel = m_pKirk->GetAverageMode();
   mAverageModeChoice->SetSelection(sel);
   
   if(sel > Kirkeby::AM_NONE)
   {
      mAverageTypeLabelStext->Enable();
      mAverageTypeChoice->Enable();
      mAverageWidthLabelStext->Enable();
      mAverageWidthText->Enable();
      mAvgWidthMUStext->Enable();
   }
   mAverageTypeChoice->SetSelection(m_pKirk->GetAverageType());
   wxszValue.Printf(wxT("%.3f"), m_pKirk->GetAverageWidth());
   mAverageWidthText->SetValue(wxszValue);

   bool check = m_pKirk->IsAutorangeSet();
   mAutorangeCheck->SetValue(check);
   if(!check)
   {
      mGainLabelStext->Enable();
      mGainText->Enable();
      mGainMUStext->Enable();
   }
   wxszValue.Printf(wxT("%.1f"), m_pKirk->GetGaindB());
   mGainText->SetValue(wxszValue);

   
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
