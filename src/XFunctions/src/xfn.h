/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  xfn.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_XFUNCTIONS_XFN_H__
#define __AURORA_XFUNCTIONS_XFN_H__

#include "correlator.h"

#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include <afconfig.h>

class XFunctions : public Correlator
{
   private:

//      wxArrayString mTrackName;
     wxArrayString m_awxszXFnNames;
     wxArrayString m_awxszOutputTrackLabels;

     ProgressDialog* m_pProgressDlg;

     AFConfig* m_pAuroraCfg;
     
   protected:
     void ShowErrorMessage(const char* pchMsg, const char* pchCaption);
     
     void InitProgressMeter(const wxString& msg);
     bool UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total);
     void DestroyProgressMeter();

  public:
    
    wxString GetXFunctionLabel(const int type)   const { return m_awxszXFnNames[type]; }
    wxString GetCurrentXFunctionLabel()          const { return m_awxszXFnNames[m_nXFnTypeId]; }
    wxString GetResultVectorLabel(const int chn) const { return m_awxszOutputTrackLabels[m_aotOut[chn].GetType()]; }
    
    int GetXFunctionTypeByString(wxString& wxszXFnType);
    int GetPlotType(wxString& label, int* type, int* ch);
    
//     wxString GetTrackName(int ch)  { return mTrackName[ch]; }    
//     void AddTrackName(wxString tn) { mTrackName.Add(tn); }
    
    void ReadConfigurationValues();
    void StoreConfigurationValues();
    
    // --- ctors
    XFunctions(AFConfig* pCfg);

};

#endif // __AURORA_XFUNCTIONS_XFN_H__
