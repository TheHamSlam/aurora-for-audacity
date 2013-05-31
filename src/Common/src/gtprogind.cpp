// Progress Indicator (code by Guido Truffelli)

//#include <wxcmn.h>
//#include <wx/sizer.h>
//#include <wx/gauge.h>

#include "gtprogind.h"

///////////////////////////////////////////////////////////
// GTProgressIndicator
///////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(GTProgressIndicator, wxDialog)
//  EVT_MENU(wxID_CANCEL, GTProgressIndicator::OnCancel)
END_EVENT_TABLE()

wxString GTProgressIndicator::msec2str(long ms) const
{
  int s = ms/1000;
  const int h = s / 3600;
  s -= h*3600;
  const int m = s / 60;
  s -= m*60;
  return wxString::Format(wxT("%02d:%02d:%02d"), h, m, s);
}

void GTProgressIndicator::SetRange(int nRange, int nGauge)
{
  wxASSERT(nRange >= 0 && nGauge >= 0 && nGauge < MAX_GAUGES);
  m_pGauge[nGauge]->SetRange(nRange);
}

bool GTProgressIndicator::SetProgress(int nPos, int nGauge)
{
  if (!IsShown())
    return false;

  wxASSERT(nPos >= 0 && nGauge >= 0 && nGauge < MAX_GAUGES);
  m_pGauge[nGauge]->SetValue(nPos);

  const long elap = Elapsed();
  if (elap > m_nNextUpdate)
  {
    m_nNextUpdate = elap+CLOCKS_PER_SEC;
    m_pPassed->SetLabel(msec2str(elap));

    wxLongLong_t nTotValue = 0, nTotRange = 0;
    for (int i = 0; i < MAX_GAUGES && m_pGauge[i]; i++)
    {
      const int nValue = m_pGauge[i]->GetValue();
      const int nRange = m_pGauge[i]->GetRange();
      if (nValue < nRange) // Escludi dal calcolo i processi gi� terminati
      {
        nTotValue += nValue;
        nTotRange += nRange;
      }
    }
    if (nTotValue > 0)
    {
      const long est = long(elap * nTotRange / nTotValue);
      m_pEstimated->SetLabel(msec2str(est));
      m_pResidual->SetLabel(msec2str(est-elap));
    }

    wxYield();
  }

  return true;
}

void GTProgressIndicator::SetMessage(wxString msg)
{
  SetLabel(msg);
}

void GTProgressIndicator::Init(wxString msg, int nGauges, bool bCancellable)
{
  const int nGap = 4;
  wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(pTopSizer);

  memset(m_pGauge, 0, sizeof(m_pGauge));
  for (int i = 0; i < nGauges; i++)
  {
    m_pGauge[i] = new wxGauge(this, 1001+i, 100, wxDefaultPosition, wxSize(400, -1));
    pTopSizer->Add(m_pGauge[i], 0, wxALL, nGap);
  }

  wxGridSizer* pTimersSizer = new wxGridSizer(1, 3, nGap, nGap);
  pTopSizer->Add(pTimersSizer, 0, wxEXPAND);

  wxStaticBoxSizer* pPassed = new wxStaticBoxSizer(wxVERTICAL, this, _("Elapsed Time"));
  pTimersSizer->Add(pPassed, 0, wxEXPAND);
  m_pPassed = new wxStaticText(this, 1101, wxT("00:00:00"));
  pPassed->Add(m_pPassed, 0, wxALL|wxALIGN_CENTER, 0);

  wxStaticBoxSizer* pResidual = new wxStaticBoxSizer(wxVERTICAL, this, _("Residual Time"));
  pTimersSizer->Add(pResidual, 0, wxEXPAND);
  m_pResidual = new wxStaticText(this, 1102, wxT("00:00:00"));
  pResidual->Add(m_pResidual, 0, wxALL|wxALIGN_CENTER, 0);

  wxStaticBoxSizer* pEstimated = new wxStaticBoxSizer(wxVERTICAL, this, _("Estimated Time"));
  pTimersSizer->Add(pEstimated, 0, wxEXPAND);
  m_pEstimated = new wxStaticText(this, 1103, wxT("00:00:00"));
  pEstimated->Add(m_pEstimated, 0, wxALL|wxALIGN_CENTER, 0);

  wxButton* pCancel = NULL;
  if (bCancellable)
  {
    pCancel = new wxButton(this, wxID_CANCEL, _("Cancel"));
    pTopSizer->Add(pCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, nGap);
  }

  pTopSizer->SetSizeHints(this);

  SetMessage(msg);

  Show();
  Enable();
  Update();

  m_nNextUpdate = 0;
  m_chrono.Start();
}

GTProgressIndicator::GTProgressIndicator(size_t nRange, wxString msg, bool bCancellable)
                   : wxDialog(NULL, wxID_ANY, msg)  
{
  Init(msg, 1, bCancellable);
  SetRange(nRange, 0);
}

GTProgressIndicator::GTProgressIndicator(wxString msg, bool bCancellable, int nGauges)
                   : wxDialog(NULL, wxID_ANY, msg)
{
  Init(msg, nGauges, bCancellable);
}

GTProgressIndicator::~GTProgressIndicator()
{ }

