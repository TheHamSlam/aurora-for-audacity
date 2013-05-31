/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  Time History Analyzer

  track.h

  Angelo Farina - Simone Campanini

**********************************************************************/

#ifndef __AURORA_ITUP56_TRACK_H__
#define __AURORA_ITUP56_TRACK_H__

#include <afaudio.h>

//----------------------------------------------------------------------------
// THASignalAudioTrack
//----------------------------------------------------------------------------
class THASignalAudioTrack : public AFAudioTrack
{
  private:
    int m_nIdx;

    wxString m_wxszName;

  public:
    void Filter(const int nCh = 0);

    int GetIndex() const { return m_nIdx; }
    void SetIndex(const int nIdx) { m_nIdx = nIdx; }

    wxString& GetName() { return m_wxszName; }
    void SetName(const wxChar* pwxchName) { m_wxszName = pwxchName; }
    void SetName(wxString& wxszName)      { m_wxszName = wxszName; }

    THASignalAudioTrack(const double dbRate,
    		            const int    nIdx        = 0,
    		            const double dbFullscale = 120.0,
    		            const int    nFilterId   = FLT_LIN,
    		            const int    nCh         = 1)
    : AFAudioTrack(dbRate, nCh), m_nIdx(nIdx), m_wxszName(wxT("TrackName"))
    { SetFullScale(dbFullscale);
      SetFilter(nFilterId);      }
};
WX_DECLARE_OBJARRAY(THASignalAudioTrack, TArrayOfTHASignalAudioTrack);

//----------------------------------------------------------------------------
// THACalibrationAudioTrack
//----------------------------------------------------------------------------
class THACalibrationAudioTrack : public AFAudioTrackBase
{
  private:
    int    m_nIdx;
    double m_dbReference;

  public:
    int GetIndex() const { return m_nIdx; }
    void SetIndex(const int nIdx) { m_nIdx = nIdx; }

    double GetReferenceLevel() const { return m_dbReference; }
    void SetReferenceLevel(const double dbValue) { m_dbReference = dbValue; }

    THACalibrationAudioTrack(const double dbRate, const double dbReference = 94.0, const int nIdx = 0, const int nCh = 1)
    : AFAudioTrackBase(dbRate, nCh), m_nIdx(nIdx), m_dbReference(dbReference) {}
};
WX_DECLARE_OBJARRAY(THACalibrationAudioTrack, TArrayOfTHACalibrationAudioTrack);


#endif //__AURORA_ITUP56_TRACK_H__

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
