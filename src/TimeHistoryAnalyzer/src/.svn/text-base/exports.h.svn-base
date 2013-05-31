/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  exports.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_ITUP56_EXPORTS_H__
#define __AURORA_ITUP56_EXPORTS_H__

#include <afexports.h>

#include <wx/textfile.h>

#include "than.h"

class THAExports : public AFExports
{
    public:
       enum FileType { FT_PARAMETER_TXT, 
                       FT_PARAMETER_CSV, 
                       FT_TIME_HISTORY_TXT, 
                       FT_TIME_HISTORY_CSV };

    private:
       TArrayOfTHASignalAudioTrack*   m_paSignalTracks;
       TimeHistoryAnalyzer::TResults* m_pResults;

       int m_nCurrentPlotType;

       void StoreParametersTable(wxTextFile *fo, int file_type = FF_TXT);
       void StoreTimeHistory(wxTextFile *fo, int file_type = FF_TXT);

    protected:
       bool BuildParametersTable(wxString &data_buffer,
    		                     const int nDest = DD_FILE,
    		                     const int file_type = FF_TXT);
       
    public:
      bool SaveToFile(); 
      
      void SetCurrentPlotType(const int nType) { m_nCurrentPlotType = nType; }

      THAExports(wxWindow *parent,
                 TArrayOfTHASignalAudioTrack*   paSignalTracks,
                 TimeHistoryAnalyzer::TResults* pResults);
};

#endif // __AURORA_ITUP56_EXPORTS_H__

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
