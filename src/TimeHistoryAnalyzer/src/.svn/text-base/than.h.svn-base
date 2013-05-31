/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  than.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_ITUP56_THAN_H__
#define __AURORA_ITUP56_THAN_H__

#include "afthan.h"

#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include <afconfig.h>

class TimeHistoryAnalyzer : public AFTimeHistoryAnalyzer
{
   private:
     ProgressDialog* m_pProgressDlg;
     
   protected:
     void InitProgressMeter();
     void SetProgressMeterMessage(const wxString& wxszMsg);
     bool UpdateProgressMeter(const int nStep, const int nTotal);
     void DestroyProgressMeter();

  public:
    void SetProgressDialog(ProgressDialog* pProgDlg) { m_pProgressDlg = pProgDlg; }
	
    // --- ctors
    TimeHistoryAnalyzer(const int channels = 1);
};

#endif // __AURORA_ITUP56_THAN_H__
