#ifndef __PROGIND_H__
#define __PROGIND_H__

#include <wxcmn.h>
//#include <commdefs.h>

#include <wx/stattext.h>
#include <wx/stopwatch.h>

///////////////////////////////////////////////////////////
// GTProgressIndicator
///////////////////////////////////////////////////////////

class GTProgressIndicator : public wxDialog
{
  enum { MAX_GAUGES = 16 };
  wxGauge* m_pGauge[MAX_GAUGES];
  wxStaticText* m_pPassed;
  wxStaticText* m_pResidual;
  wxStaticText* m_pEstimated;
  wxStopWatch m_chrono;
  long m_nNextUpdate;

protected:
  DECLARE_EVENT_TABLE();

  void Init(wxString msg, int nGauges, bool bCancellable);
  wxString msec2str(long ms) const;
  long Elapsed() const { return m_chrono.Time(); }

public:
  void SetRange(int nRange, int nGauge = 0);
  bool SetProgress(int nPos, int nGauge = 0);
  void SetMessage(wxString msg);

  GTProgressIndicator(wxString msg, bool bCancellable, int nGauges);
  GTProgressIndicator(size_t nRange, wxString msg, bool bCancellable);
  virtual ~GTProgressIndicator();
};

#endif
