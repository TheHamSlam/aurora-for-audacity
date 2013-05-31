/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  than.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class TimeHistoryAnalyzer
\brief The Aurora's powerful analyzer of time history data

  blabla
*//*******************************************************************/

#include "than.h"

void TimeHistoryAnalyzer::InitProgressMeter() 
{
   m_pProgressDlg = new ProgressDialog(wxT("Time History Analyzer"),
                                       wxT("Calculating..."));
}

bool TimeHistoryAnalyzer::UpdateProgressMeter(const int nStep, const int nTotal)
{
	if(m_pProgressDlg)
    	return (m_pProgressDlg->Update(nStep, nTotal) == eProgressSuccess) ? true : false;

	return false;
}

void TimeHistoryAnalyzer::SetProgressMeterMessage(const wxString& wxszMsg)
{
	if(m_pProgressDlg) m_pProgressDlg->SetMessage(wxszMsg);
}

void TimeHistoryAnalyzer::DestroyProgressMeter() 
{
   m_pProgressDlg->Destroy();
   m_pProgressDlg = 0;
}

// --- ctors
TimeHistoryAnalyzer::TimeHistoryAnalyzer(const int channels)
   : AFTimeHistoryAnalyzer(channels),
     m_pProgressDlg(0)
{ }


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
