/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  Acoustical Parameters

  track.h
 
  Angelo Farina - Simone Campanini
 
 **********************************************************************/
#ifndef __AURORA_ACPAR_TRACK_H__
#define __AURORA_ACPAR_TRACK_H__

#include <afaudio.h>

//-------------------------------------------------------------------------------------
// APAudioTrack
//
/// \brief Audio data holder.
/// Holds audio datas - got from Audacity track(s) in some way - 
/// and do some time domain operations on them. This class is designed
/// for Acoustical Parameters modules, so the data stored hopefully has
/// to be Room Impulse Responses.
//-------------------------------------------------------------------------------------
class APAudioTrack : public AFAudioTrack
{
  private:
	wxString m_wxszName; ///< Audio data label

    /// Impulse response's First Arrival Time, IOW direct wave arrival time.
	double m_dbFAT;
    
  public:
	wxString& GetName() { return m_wxszName; }
	void SetName(const wxChar* pwxchName)  { m_wxszName = pwxchName; }
	void SetName(const wxString& wxszName) { m_wxszName = wxszName; }

    /// Tries to find the First Arrival Time of the stored Impulse Response
    /// \param dbDirectSoundTrigdB - the direct wave trigger level in deciBel
    /// \return true on success, false othervise (try with lower trigger level)
	bool FindFirstArrivalTime(const double dbDirectSoundTrigdB);
    
    /// Returns the audio data length - in samples - starting from First Arrival Time
	AFSampleCount GetLengthFromFAT()    { return m_smpcLen -
			                                     AFSampleCount(m_dbFAT*m_dbRate); }
	/// \sa GetLengthFromFAT()
	AFSampleCount GetSamplesFromFAT()   { return m_smpcLen -
			                                     AFSampleCount(m_dbFAT*m_dbRate); }
    
    /// It returns the delay of the First Arrival Time in samples.
	double GetFirstArrivalTime() { return m_dbFAT; }

    /// Applies the selected filter to an octave band
    /// \param nBandId - the octave band identifier
	void ApplyFilter(const int nBandId);

    /// The constructor
    /// \param dbRate - sampling rate of the audio data
    /// \param bCh - number f channels of the audio data structure (deprecated)
	APAudioTrack(const double dbRate = 48000.0,
			     const int nCh = 1)
	: AFAudioTrack(dbRate, nCh),
	  m_wxszName(wxT("Trackname")),
	  m_dbFAT(0.0)
	{ }

    /// The constructor
    /// \param dbRate - sampling rate of the audio data
    /// \param smpcLength - audio data length in samples
    /// \param bCh - number f channels of the audio data structure    
	APAudioTrack(const double dbRate,
			     const AFSampleCount smpcLength,
			     const int nCh = 1)
	: AFAudioTrack(dbRate, nCh),
	  m_wxszName(wxT("Trackname")),
	  m_dbFAT(0.0)
	{ SetLength(smpcLength, true);
	  m_smpcFilteredTrackLength = smpcLength; }

};
WX_DECLARE_OBJARRAY(APAudioTrack, TArrayOfAPAudioTracks);


#endif // __AURORA_ACPAR_TRACK_H__

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

