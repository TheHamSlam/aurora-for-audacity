/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  afaudio.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_AFAUDIO_H__
#define __AURORA_AFAUDIO_H__

#include <audtypes.h>
#include <commdefs.h>

//----------------------------------------------------------------------------
// AFAudioTrackBase
/// \brief The base class of audio data holder.
/// This class provides a container for audio data with some fundamental
/// operations/calculus on it.
//----------------------------------------------------------------------------

class AFAudioTrackBase
{
  public:
	/// Types of audio data (to be Deprecated)
    enum Mode { AFM_MONO = 1, AFM_STEREO = 2, AFM_TETRA = 4 };

  protected:
    int     m_nMode;           ///< What sort of data are stored (Deprecated)
    double  m_dbRate;          ///< Sampling rate in Hz.
    int     m_nChannels;       ///< Number of channels stored (Deprecated)
    double  m_dbFullScale;     ///< Fullscale level in dB.

    AFSample** m_apsmpTrack;   ///< The audio datas itselves

    AFSampleCount m_smpcLen;   ///< Audio data length.

    double *m_pdbMin,          ///< Audio data absolute maximum.
           *m_pdbMax;          ///< Audio data absolute minumum.

    AFSampleCount* m_psmpcFAT; ///< The First Arrival Time (direct wave arrival time) (Deprecated)

  protected:
    /// If data length is set, initialize nCh channel(s) track.
    virtual bool Init(const int nCh);
    /// Destroy existing audio data.
    virtual void Destroy(const int nCh);

    /// Copy data.
    /// \param src - Source data pointer
    /// \param dest - Destination data pointer
    /// \param len - How many sample has to be copied
    /// \param gain - Optional gain to apply to destination data.
    void Copy(AFSample *src, AFSample *dest, const AFSampleCount len, const double gain);

    /// Find audio data minimum absolute value
    /// \param nCh - The requested channel
    virtual double FindMin(const int nCh = 0);

    /// Find audio data maximum absolute value
    /// \param nCh - The requested channel
    virtual double FindMax(const int nCh = 0);

  public:   // TODO: Some reordering has to be done...
    /// Find direct wave arrival time. This method make sense only if an Impulse
    /// Response has been stored in the class (Deprecated).
    virtual bool FindFirstArrivalTime(const double dbThreshold, const int nCh);

  public:
    /// Dump track to txt file (useful for scipy)
    virtual void Dump(const int idx = -1);

    /// Get Root Mean Square of the audio datas. In reality it computes
    /// a value proportional to the signal energy, so the square root
    /// is not calculated.
    virtual double RMS(const int nCh = 0);
    /// Get Equivalent Level of the signal stored. Calculated starting
    /// from RMS().
    double Leq(const int nCh = 0) { return dB(RMS(nCh)); }

    // --- Checkers
    bool IsStereo() const { return (m_nMode == AFM_STEREO); }
    bool IsTetra()  const { return (m_nMode == AFM_TETRA); }

    //--- Get/Setters
    double  GetRate()           const { return m_dbRate; }
    double  GetSamplerate()     const { return m_dbRate; }
    int     GetChannelsNumber() const { return m_nChannels; }
    double  GetFullScale()      const { return m_dbFullScale; } // dB

    /// Get pointer to audio data vector. Can be useful for some fast processing that requires
    /// direct data access.
    /// \param nCh - The requested channel (Deprecated).
    /// \return Audio data vector pointer.
    AFSample* GetData  (const int nCh = 0) const { return m_apsmpTrack[nCh]; }
    /// \sa GetData()
    AFSample* GetTrack (const int nCh = 0) const { return m_apsmpTrack[nCh]; }

    /// Get a sample.
    /// \param nCh - The requested channel (Deprecated)
    /// \param smpl - The sample index
    /// \return The sample.
    AFSample  GetSample      (const AFSampleCount smpl, const int nCh = 0)  const { return m_apsmpTrack[nCh][smpl]; }
    /// \sa GetSample()
    AFSample  GetTrackSample (const int nCh, const AFSampleCount smpl)      const { return m_apsmpTrack[nCh][smpl]; }

    /// Get the square value of a sample.
    /// \param nCh - The requested channel (Deprecated)
    /// \param smpl - The sample index
    /// \return The square value of requested sample.
    AFSample  GetSquaredSample      (const AFSampleCount smpl, const int nCh = 0)  const { return m_apsmpTrack[nCh][smpl] * m_apsmpTrack[nCh][smpl]; }
    /// \sa GetSquaredSample()
    AFSample  GetTrackSquaredSample (const int nCh, const AFSampleCount smpl)      const { return m_apsmpTrack[nCh][smpl] * m_apsmpTrack[nCh][smpl]; }

    /// Get audio datas length.
    AFSampleCount GetLength()      const { return m_smpcLen; }
    /// \sa GetLength()
    AFSampleCount GetTrackLength() const { return m_smpcLen; }

    double  GetMin     (const int nCh = 0) const { return m_pdbMin[nCh]; }
    double  GetMax     (const int nCh = 0) const { return m_pdbMax[nCh]; }
    double  GetTrackMin(const int nCh = 0) const { return m_pdbMin[nCh]; }
    double  GetTrackMax(const int nCh = 0) const { return m_pdbMax[nCh]; }

    void SetMode(const int nChnls)           { m_nChannels   = (m_nMode = nChnls); }
    void SetSamplerate(const double dbValue) { m_dbRate      = dbValue; }
    void SetFullScale(const double dbValue)  { m_dbFullScale = dbValue; }

    /// Store audio data. Before using this method, a length has to be specified (if not yet)
    /// using, for example, SetLength().
    /// \param nCh - Channel to store in.
    /// \param src - Pointer to source data.
    /// \param bInitTrack - Initialize vector before data storing.
    virtual void SetTrack(const int nCh, AFSample *src, const bool bInitTrack = false);

    /// Store audio data. \sa SetTrack().
    virtual void SetTrack(const int nCh, double *pdbSrc, const bool bInitTrack = false);

    /// Store audio data.
    /// \param nCh - Channel to store in.
    /// \param psmpSrc - Pointer to source data.
    /// \param smpcLen - Source data length.
    /// \param bInitTrack - Initialize vector before data storing.
    virtual void SetTrack(const int nCh, AFSample *psmpSrc, const AFSampleCount smpcLen, const bool bInitTrack = false);

    /// Store audio data. \sa SetTrack().
    virtual void SetTrack(const int nCh, double *pdbSrc, const AFSampleCount smpcLen, const bool bInitTrack = false);

    /// Modify audio datas vector length and optionally initialize it.
    /// \param smpcLen - The new data length
    /// \param bInitTrack - Initialize (or reinitialize) data vector
    virtual void SetLength(const AFSampleCount smpcLen, const bool bInitTrack = false)
    { SetTrackLength(smpcLen, bInitTrack); }

    /// Modify audio datas vector length and optionally initialize it (Deprecated).
    /// \param smpcLen - The new data length
    /// \param bInitTrack - Initialize (or reinitialize) data vector
    /// \param nCh - The requested channel.
    virtual void SetTrackLength(const AFSampleCount smpcLen, const bool bInitTrack = false, int nCh = 0);

    void SetTrackMin(const int nCh, const double dbMin) { m_pdbMin[nCh] = dbMin; }
    void SetTrackMax(const int nCh, const double dbMax) { m_pdbMax[nCh] = dbMax; }
    void SetMin(const double dbMin, const int nCh = 0)  { m_pdbMin[nCh] = dbMin; }
    void SetMax(const double dbMax, const int nCh = 0)  { m_pdbMax[nCh] = dbMax; }

    void SetTrackSample(const int nCh, const AFSampleCount smpcPos, const AFSample smpValue)  { m_apsmpTrack[nCh][smpcPos] = smpValue; }

    /// The constructor.
    /// \param dbRate - the data sampling rate in Hz
    /// \param nChannels - the number of channel(s) to store (Deprecated)
    AFAudioTrackBase(const double dbRate = 48000.0, const int nChannels = 1);
    virtual ~AFAudioTrackBase();
};

//----------------------------------------------------------------------------
// AFAudioTrack
//
/// \brief Audio data container with time domain filtering tools.
/// This class can modify stored data with the following implemented
/// filters (code written by Angelo Farina):
/// - \b IEC \b 61260 Octave bands
/// - \b ITU \b P56 150-550 Hz band pass
/// - \b ISO \b 8041 Generic axis acceleration ponderation
/// - \b UNI \b 9916 250 Hz low pass
/// - \b A-weighting filter.
/// It can also remove the DC component and performs a noise correction.\n
/// Note that all the filters operation will have place on a copy of the
/// stored audio date, so before a filtering method call, a call to
/// ResetFilteredTrack() should be done, otherwise the result is not
/// guaranteed...
//
//----------------------------------------------------------------------------

class AFAudioTrack : public AFAudioTrackBase
{
   public:
	   /// Implemented filters tags.
       enum FilterType
       {
    	   BPF = 0, LPF, HPF, NotchF,

           FLT_LIN,     // not implemented??
           FLT_ITU,     // Band-pass (160-5500 Hz)
           FLT_IEC,     // A-weighting filter
           FLT_ISO,     // 2631 whole combined (???)
           FLT_UNI,
           FLT_NONE      // Useful for selections...
       };


   protected:
      AFSample** m_apsmpFilteredTrack;  ///< The filtered data vector.
      double     m_dbNoiseCorrFactor;   ///< Noise correction flag.
      int        m_nSelectedFilter;     ///< The filter selected by user.

      AFSampleCount m_smpcFilteredTrackLength; ///< The filtered data length
      double        m_dbFilteredTrackRate;     ///< The filtered data samplerate

      /// If a track length is set, initialize nCh channel datas.
      virtual bool Init(const int nCh);
      /// Destroy nCh channel datas.
      virtual void Destroy(const int nCh);
      
   public:   // TODO: Some reordering has to be done...
   
      // --- Utils
    
      /// Restore the filtered data vector. This method should be called
      /// every time a new filtering operation is needed.
      /// \param nCh - The requested channel (Deprecated)
      /// \param gain - gain to apply to data before filtering.
      void ResetFilteredTrack(const int nCh = 0, const double gain = 1.0);
      
      /// Set nCh audio data to filtered version (loosing backup).
      /// \param nCh - The requested channel (Deprecated)
      /// \param gain - gain to apply.
      void ReplaceTrackWithFiltered(const int nCh = 0, const double gain = 1.0);
    
    
    // --- Filtering
   private:
      /// Time domain IIR filter function, called by every filtering method.
      /// \f[ y[n] = 2 ( \alpha (x[n] + \mu x[n-1] + \sigma x[n-2]) + \gamma y[n-1] - \beta y[n-2] ) \f]
      /// \param nCh - The requested data channel (Deprecated)
      /// \param alpha, beta, gamma, mu, sigma - The filter parameters
       void IIR(const int nCh, 
                const double alpha, const double beta, const double gamma, 
                const double mu,    const double sigma);

   public:
      /// Apply gain to filtered data.
      /// \param nCh - The requested data channel (Deprecated)
      /// \param G - Gain level in dB
      void Gain(const int nCh, const double G); // G [dB]
      
      /// Filtering function wrapper for low-pass, band-pass, high-pass and notch
      /// \param type - Filter type, must be one of LPF, BPF, HPF, NotchF.
      /// \param nCh - The requested data channel (Deprecated)
      /// \param f0 - Cutoff frequency
      /// \param fQ - Q factor.
      void Filter           (const int type, const int nCh, const double f0, const double fQ);

      /// A-weigthed filter.
      /// \param nCh - The requested data channel (Deprecated)
      void AFilter          (const int nCh = 0); //... bool preserve = true);

      /// High-pass filter, cutoff 20 Hz.
      /// \param nCh - The requested data channel (Deprecated)
      void LFilter          (const int nCh = 0);

      /// ISO 8042 filter. Used in accelerometer measures for the generic axis
      /// ponderation.
      /// \param nCh - The requested data channel (Deprecated)
      void ISO_8041_Filter  (const int nCh = 0);

      /// ITU P56 filter. Pass band filter 160 - 5500 Hz
      /// \param nCh - The requested data channel (Deprecated)
      void ITU_P56_Filter   (const int nCh = 0);

      /// UNI 9916 filter. Low pass, cutoff 250 Hz. Used in vibration measures.
      /// \param nCh - The requested data channel (Deprecated)
      void UNI_9916_Filter  (const int nCh = 0);

      /// IEC 61260 Octave bands filter.
      /// \param nCh - The requested data channel (Deprecated)
      /// \param dbFc - Center band frequency in Hz, one of 31.5, 63, 125, 250, 500
      ///               1000, 2000, 4000, 8000, 16000.
      void OctaveFilter     (const int nCh, const double dbFc);

      /// DC component remover.
      /// \param nCh - The requested data channel (Deprecated)
      void RemoveMean       (const int nCh = 0);

      /// Noise correction function.
      /// \param nCh - The requested data channel (Deprecated)
      void NoiseCorrection  (const int nCh = 0);
      
      /// Root Mean Square of the filtered data. Like the base class method (that
      /// operates on backup audio data) the value calculated is proportional to
      /// energy, so no square root is performed.
      /// \param nCh - The requested data channel (Deprecated)
      virtual double RMS(const int nCh = 0);

      /// Get pointer to filtered data vector.
      /// \param nCh - The requested data channel (Deprecated)
      /// \return Filtered data vector.
      AFSample* GetFilteredData               (const int nCh = 0) const { return m_apsmpFilteredTrack[nCh]; }

      /// \sa GetFilteredData()
      AFSample* GetFilteredTrack              (const int nCh = 0) const { return m_apsmpFilteredTrack[nCh]; }

      AFSample  GetFilteredSample             (const AFSampleCount smpl, const int nCh = 0) const { return m_apsmpFilteredTrack[nCh][smpl]; }
      AFSample  GetFilteredTrackSample        (const int nCh, const AFSampleCount smpl) const { return m_apsmpFilteredTrack[nCh][smpl]; }

      AFSample  GetFilteredSquaredSample      (const AFSampleCount smpl, const int nCh = 0) const { return m_apsmpFilteredTrack[nCh][smpl] * m_apsmpFilteredTrack[nCh][smpl]; }
      AFSample  GetFilteredTrackSquaredSample (const int nCh, const AFSampleCount smpl) const { return m_apsmpFilteredTrack[nCh][smpl] * m_apsmpFilteredTrack[nCh][smpl]; }

      AFSampleCount GetFilteredDataLength     () const { return m_smpcFilteredTrackLength; }
      double        GetFilteredDataRate       () const { return m_dbFilteredTrackRate; }

      void SetFilteredDataLength(const AFSampleCount length) { m_smpcFilteredTrackLength = length; }
      void SetFilteredDataRate  (const double rate)          { m_dbFilteredTrackRate = rate; }

      /// Store audio data like AFAudioTrackBase method, but also optionally initialize filtered vector.
      /// \sa AFAudioTrackBase::SetTrack()
      virtual void SetTrack(const int nCh, AFSample *src,     const bool bInitTrack = false);

      /// \sa SetTrack()
      virtual void SetTrack(const int nCh, double   *pdbSrc,  const bool bInitTrack = false);

      /// Store audio data like AFAudioTrackBase method, but also optionally initialize filtered vector.
      /// \sa AFAudioTrackBase::SetTrack()
      virtual void SetTrack(const int nCh, AFSample *psmpSrc, const AFSampleCount smpcLen, const bool bInitTrack = false);

      /// \sa SetTrack()
      virtual void SetTrack(const int nCh, double   *pdbSrc,  const AFSampleCount smpcLen, const bool bInitTrack = false);
      
   
      int  GetSelectedFilter() const { return m_nSelectedFilter; }
      void SetFilter    (const int nType) { m_nSelectedFilter = nType; }
      void SetFilterType(const int nType) { m_nSelectedFilter = nType; }

      double& GetNoiseCorrFactor() { return m_dbNoiseCorrFactor; }

      /// The constructor.
      /// \param dbRate - the data sampling rate in Hz
      /// \param nChannels - the number of channel(s) to store (Deprecated)
      AFAudioTrack(const double dbRate = 48000.0, const int nChannels = 1);
      ~AFAudioTrack();
};

#endif // __AURORA_IR_H__
