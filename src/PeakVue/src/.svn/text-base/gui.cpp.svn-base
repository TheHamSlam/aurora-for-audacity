/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  PeakVue

  gui.cpp

  Simone Campanini

**********************************************************************/
#include <commdefs.h>
#include <afart.h>

#include "data.h"
#include "gui.h"
#include "version.h"

void PeakVueDialog::OnCloseDialog( wxCloseEvent& event )
{
    EndModal(false);
}

void PeakVueDialog::OnAnalyze( wxCommandEvent& event )
{
	m_DataShuttle.GetAudioData().SetPeakMethod(m_pwxchPeakType->GetSelection());
	m_DataShuttle.GetAudioData().SetBlockDuration(::TextPtrToDouble(m_pwxtcPeakBlockSize));
	m_DataShuttle.SetFftLength(::TextPtrToInt(m_pwxtcFftSize));

	if(!m_pEpv->DoAnalysis(m_pwxchTrack->GetSelection()))
	{
		::wxMessageBox(wxT("Analysis failed"),
				       wxT("Error"),
				       wxOK |wxICON_ERROR );
		return;
	}
	    // TODO: get results and display them
	PVRealDataSerie* pData = new PVRealDataSerie(m_DataShuttle.GetAudioData());
	m_pTimePlot->AddSerie(pData);
	m_pTimePlot->Refresh();

	PVSpectrumMagnitudeDataSerie* pMagn = new PVSpectrumMagnitudeDataSerie(m_DataShuttle.GetSpectralData(),
			                                                               m_DataShuttle.GetFftLength());
	m_pSpectrumPlot->AddSerie(pMagn);
	m_pSpectrumPlot->Refresh();

}

void PeakVueDialog::OnHelp( wxCommandEvent& event )
{
    // TODO
}

void PeakVueDialog::OnCloseBtn( wxCommandEvent& event )
{
    EndModal(true);
}


PeakVueDialog::PeakVueDialog( wxWindow* parent,
		                      wxWindowID id,
	                          EffectPeakVue* pEpv,
	                          PVDataShuttle& dataShuttle)
 : PeakVueSetupDlg(parent, id),
   m_pEpv(pEpv),
   m_DataShuttle(dataShuttle)
{
	// Set caption
	wxString wxszTitle(wxT("Aurora for Audacity - PeakVue Analysis - (v."));
	wxszTitle << ::AuroraModuleVersionNumber(PV_VERSION_TYPE, PV_RELEASE_CANDIDATE) << wxT(")");
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
			                           AFArtProvider::GetBitmap( wxT("peakvue_logo")),
			                           wxDefaultPosition, wxDefaultSize, 0 );
	pLogoSizer->Add( m_pwxbmpLogo, 0, wxALL, 5 );

	m_pwxpnlLogo->SetSizer( pLogoSizer );
	m_pwxpnlLogo->Layout();

	// Init other widgets
	m_pwxchTrack->Append(m_DataShuttle.GetLabels());
	m_pwxchTrack->SetSelection(0);
	m_pwxchPeakType->SetSelection(m_DataShuttle.GetAudioData().GetPeakMethod());

	m_pTimePlot->GetHorzAxis()->SetTitle(wxT("Time [s]"));
	m_pTimePlot->GetHorzAxis()->ShowTitle(true);
	m_pTimePlot->GetHorzAxis()->ShowGrid(true);
	m_pTimePlot->GetHorzAxis()->SetRange(0.0, 10.0, AFAxis::RF_REAL);

	m_pTimePlot->GetVertAxis()->SetTitle(wxT("Level [dB]"));
	m_pTimePlot->GetVertAxis()->ShowTitle(true);
	m_pTimePlot->GetVertAxis()->ShowGrid(true);
	m_pTimePlot->GetVertAxis()->SetRange(0.0, 120.0, AFAxis::RF_LINEARdB);

	m_pTimePlot->SetTopBorder(false);

	m_pSpectrumPlot->GetHorzAxis()->SetTitle(wxT("Frequency [Hz]"));
	m_pSpectrumPlot->GetHorzAxis()->ShowTitle(true);
	m_pSpectrumPlot->GetHorzAxis()->ShowGrid(true);
	m_pSpectrumPlot->GetHorzAxis()->SetLog(true);
	m_pSpectrumPlot->GetHorzAxis()->SetRange(20.0, 20000.0, AFAxis::RF_REAL);

	m_pSpectrumPlot->GetVertAxis()->SetTitle(wxT("Level [dB]"));
	m_pSpectrumPlot->GetVertAxis()->ShowTitle(true);
	m_pSpectrumPlot->GetVertAxis()->ShowGrid(true);
	m_pSpectrumPlot->GetVertAxis()->SetRange(0.0, 120.0, AFAxis::RF_LINEARdB);

	m_pSpectrumPlot->SetTopBorder(false);

	m_pAcorrPlot->GetHorzAxis()->SetTitle(wxT("Time [s]"));
	m_pAcorrPlot->GetHorzAxis()->ShowTitle(true);
	m_pAcorrPlot->GetHorzAxis()->ShowGrid(true);
	m_pAcorrPlot->GetHorzAxis()->SetRange(-1.0, 1.0, AFAxis::RF_REAL);

	m_pAcorrPlot->GetVertAxis()->SetTitle(wxT("Level [dB]"));
	m_pAcorrPlot->GetVertAxis()->ShowTitle(true);
	m_pAcorrPlot->GetVertAxis()->ShowGrid(true);
	m_pAcorrPlot->GetVertAxis()->SetRange(0.0, 120.0, AFAxis::RF_LINEARdB);

	m_pAcorrPlot->SetTopBorder(false);
}


PeakVueDialog::~PeakVueDialog()
{}

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
