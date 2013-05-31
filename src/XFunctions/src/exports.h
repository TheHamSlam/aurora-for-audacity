/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  exports.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_XFUNCTIONS_EXPORTS_H__
#define __AURORA_XFUNCTIONS_EXPORTS_H__

#include <afexports.h>

#include <wx/textfile.h>
#include <wx/txtstrm.h>

#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include "data.h"

class XFunctionsExports : public AFExports
{
    public:
       enum FileType { FT_SPECTRUM_TXT = FF_TXT,
                       FT_SPECTRUM_CSV = FF_CSV,
                       FT_CLIPBOARD };

    private:
       wxString m_wxszXFnLabel;

       bool   m_bExportAll;

       double m_dbFLo,  // Lower  frequency bound
              m_dbFHi;  // Higher frequency bound
       
       TArrayOfXFSpectrumDataSerie *m_paDataSeries [2]; // 0: upper plot
                                                        // 1: lower plot
       wxTextOutputStream* m_pOutputStream;
       
       ProgressDialog*     m_pProgressDlg;

       int GetShownPlotType(const int nPlot);
       wxString GetDataLabel(const int type);
       double   GetDataValue(XFSpectrumDataSerie& ds, const int unIdx, const double dbFrq, const double dbRate);
       
    protected:
     bool BuildParametersTable(wxString &data_buffer,
                               const int nDest = DD_FILE,
                               const int file_type = FF_TXT);
       
    public:
      bool SaveToFile();
      bool AppendTimeDelay(const double dbTriggerTime, const double dbMaxDelay);
      
      bool IsExportAllSet() const { return m_bExportAll; }
      
      void SetExportAll(const bool bValue) { m_bExportAll = bValue; }

      void SetDataSeriesArray(TArrayOfXFSpectrumDataSerie* paDataSerie, const int nPlot) { m_paDataSeries[nPlot] = paDataSerie; }

      void SetFrequencyBounds(const double dbFLo, const double dbFHi)  { m_dbFLo = dbFLo,
                                                                         m_dbFHi = dbFHi; }

      void SetFunctionLabel(wxString& wxszLabel)  { m_wxszXFnLabel = wxszLabel;
                                                    m_wxszFileName = wxT("XFN_") + m_wxszXFnLabel;}
      
      void InitProgressMeter();
      bool UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total);
      void DestroyProgressMeter();
      
      XFunctionsExports(wxWindow* pParent, const wxString& wxszXFnLabel = wxEmptyString);
};

#endif // __AURORA_FUNCTIONS_EXPORTS_H__

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
