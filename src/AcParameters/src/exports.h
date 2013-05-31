/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters

  exports.h

  Angelo Farina - Simone Campanini

************************************************************************/
#ifndef __AURORA_ACPARAM_EXPORTS_H__
#define __AURORA_ACPARAM_EXPORTS_H__


class AcParametersExports : public AFExports 
{
    public:
       enum FileType { FT_PARAMETER_TXT,
                       FT_PARAMETER_CSV,
                       FT_RAMSETE_ECHOGRAM_PRN };

    private:
        wxWindow *mParent;

       AcParameters *m_pAp;
       
       TArrayOfAPAudioTracks*               m_paAudioData;
       std::vector<TSchroederDecay>&        m_paDecay;
       std::vector<AcParameters::TResults>& m_paResults;

       wxString m_wxszAppendToFileFn;

       static const wxChar* const m_awxpchParamLabels[];

       void StoreParametersTable(wxTextFile& fo, const int nFileType = FF_TXT);
       void StoreEchogram(wxTextFile& fo);
    
    protected:
       bool BuildParametersTable(wxString &wxszDataBuffer, 
                                 const int nDest = DD_FILE, 
                                 const int nFileType = FF_TXT);

    public:
      bool SaveToFile();
      void AppendResultsToFile();

      wxString& GetAppendToFileName() { return m_wxszAppendToFileFn; }
      void SetAppendToFileName(wxString& wxszName) { m_wxszAppendToFileFn = wxszName; }

      AcParametersExports(wxWindow* pParent, TArrayOfAPAudioTracks* paAudioData, AcParameters* pAp);
};
       
       

#endif // __AURORA_ACPARAM_EXPORTS_H__

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
