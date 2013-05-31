/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Invert Kirkeby

  afkirk.h

  Angelo Farina - Simone Campanini

***********************************************************************/
#ifndef __AURORA_KIRKEBY_AFKIRK_H__
#define __AURORA_KIRKEBY_AFKIRK_H__


#include <fftw3.h>
#include <commdefs.h>

// Vector related stuffs
#include "afcpxmatrix.h"
#include "afmatrix.h"
typedef AFVector<AFSample>                       TimeVector_t;
typedef AFComplexVector<fftwf_complex, AFSample> FreqVector_t;
typedef AFMatrix<AFSample>                       TimeMatrix_t;
typedef AFComplexMatrix<fftwf_complex, AFSample> FreqMatrix_t;

// Hazardous vector macros...
#define VectorItemPtr(ptr,r,c, lrow, lcol)   (ptr + r*lrow + c*lcol)
#define VectorRowPtr(ptr, r, lrow)           (ptr + r*lrow)

#define InItem(r,c)   VectorItemPtr(m_psmpIn,r,c,m_smpcInRowLength,m_smpcInColLength)
#define InRow(r)      VectorRowPtr(m_psmpIn,r,m_smpcInRowLength)
#define OutItem(r,c)  VectorItem(m_psmpOut,r,c,m_smpcOutRowLength,m_smpcOutColLength)
#define OutRow(r)     VectorRowPtr(m_psmpOut,r,m_smpcOutRowLength)

class AFKirkeby
{
      enum { CPX_REAL = 0, CPX_IMAG = 1, CPX_MAGN = 0, CPX_PHASE = 1 }; 
    
   public: 
      enum FilterType  { IK_MONO = 0, IK_STEREO, IK_DIPOLE, IK_MATRIX };
      enum AverageMode { AM_NONE = 0, AM_REIM, AM_MAGPH, AM_CEPSTRUM };
      enum AvgType     { AT_LINEAR = 0, AT_OCTAVE };
      
   private:
      double m_dbRate;
      int    m_nRows; //alias channels...
      int    m_nCols;
      
      TimeMatrix_t  m_aaHt;
      FreqMatrix_t  m_aaHf;

      FftPlan_t m_fftForwardPlan;
      FftPlan_t m_fftBackwardPlan;
      bool      m_bFftPlansExist;

      AFSampleCount m_smpcColLength;
      AFSampleCount m_smpcRowLength;
      
      int    m_nFilterType;
      bool   m_bCancelCrosstalk;
      double m_dbInRP;
      double m_dbOutRP;
      double m_dbLowCutFrq;
      double m_dbHighCutFrq;
      double m_dbTransWidth;
      AFSampleCount m_smpcFadeIn;
      AFSampleCount m_smpcFadeOut;
      
      int    m_nAvgMode;
      int    m_nAvgType;
      double m_dbAvgWidth;  // TODO Check it!! Maybe AFSampleCount...

      bool   m_bAutorange;
      double m_dbGain;
      
      bool   m_bActiveNoiseControl;
      
      // --- methods
      void InitVectors();
      void DeleteVectors();
      void InitFft();
      void DeleteFft();
      
      void FFT(FreqVector_t& Xf, TimeVector_t& Xt);
      void IFFT(TimeVector_t& Xt, FreqVector_t& Xf);
      
      void ApplyGain();
      
      //Farina's
      void MovingAverage(FreqVector_t& Hf);
      void MovingAverage(FreqVector_t& Hf, const int nCpxPart); // -> MediaLplus
      void OctaveSmoothing(FreqVector_t& Hf);
      void OctaveSmoothing(FreqVector_t& Hf, const int nCpxPart);
      
      void Average(FreqVector_t& Hf);
      void Cepstrum(FreqVector_t& Hf);
          
      void KirkebyModulusInversion(FreqVector_t& Hf);
      void KirkebyRatioModulusInversion(FreqVector_t& Uf, FreqVector_t& Wf);

      bool MonoInverseFilter(TimeVector_t& Ht);
      bool QuadInverseFilter(TimeMatrix_t& Ht);

    public:
      bool Init();
        
      bool PreProcess();
      bool Process();
      bool PostProcess();
      
      // -- checkers
      bool IsCancelCrosstalkSet()    const { return m_bCancelCrosstalk; }
      bool IsAverageSet()            const { return (m_nAvgMode > AM_NONE); }
      bool IsAutorangeSet()          const { return m_bAutorange; }
      bool IsActiveNoiseControlSet() const { return m_bActiveNoiseControl; }
      
      // -- set-getters
      double GetSamplerate() const { return m_dbRate; } 
      
      int GetRows()     const { return m_nRows; }
      int GetCols()     const { return m_nCols; } 
      int GetChannels() const { return m_nRows; }
      
      AFSample* GetInputTrackItem(const int nRow, const int nCol)  { return ((nCol < m_nCols) && (nRow < m_nRows)) ? m_aaHt.Item(nRow, nCol).GetData() : 0; }
      AFSample* GetOutputTrackItem(const int nRow, const int nCol) { return ((nCol < m_nCols) && (nRow < m_nRows)) ? m_aaHt.Item(nRow, nCol).GetData() : 0; }

      AFSampleCount GetRowLength()     const { return m_smpcRowLength; }
      AFSampleCount GetColumnLength() const { return m_smpcColLength; }
      AFSampleCount GetColumnWidth()   const { return m_smpcColLength; }
      AFSampleCount GetFftLength()     const { return m_smpcColLength; }
      AFSampleCount GetInverseFilterLength() const { return m_smpcColLength; }
      
      int    GetFilterType() const { return m_nFilterType; }
      double GetInBandRegularisationParameter()  const { return m_dbInRP; }
      double GetOutBandRegularisationParameter() const { return m_dbOutRP; }
      double GetLowerCutFrequency()   const { return m_dbLowCutFrq; }
      double GetHigherCutFrequency()  const { return m_dbHighCutFrq; }
      double GetTransitionWidth()     const { return m_dbTransWidth; }
      AFSampleCount GetFadeInLength()   const { return m_smpcFadeIn; }
      AFSampleCount GetFadeOutLength()  const { return m_smpcFadeOut; }
      
      int    GetAverageMode()  const { return m_nAvgMode; }
      int    GetAverageType()  const { return m_nAvgType; }
      double GetAverageWidth() const { return m_dbAvgWidth; } // TODO Check it!!

      double GetGaindB() const { return dB(m_dbGain); }
      double GetGain()   const { return m_dbGain; }

      void SetSamplerate(const double dbValue) { m_dbRate = dbValue; }

      void SetRows(const int nValue)     { m_nRows = nValue; }
      void SetCols(const int nValue)     { m_nCols = nValue;
                                           m_smpcColLength = m_smpcRowLength / 
                                           ((m_nFilterType == IK_STEREO) ? 1 : m_nCols); } 
      void SetChannels(const int nValue) { SetRows(nValue); }

      void SetCancelCrosstalk(const bool bValue)    { m_bCancelCrosstalk = bValue; }
      void SetAutorange(const bool bValue)          { m_bAutorange = bValue; }
      void SetActiveNoiseControl(const bool bValue) { m_bActiveNoiseControl = bValue; }

      void SetInputRowLength(const AFSampleCount smpcValue)   { m_smpcRowLength = smpcValue;
                                                                m_smpcColLength = smpcValue / 
                                                                                 ((m_nFilterType == IK_STEREO) ? 1 : m_nCols); }
      void SetInputTrackLength(const AFSampleCount smpcValue) { SetInputRowLength(smpcValue); }

      void SetFftLength(const AFSampleCount smpcValue)           { m_smpcColLength = smpcValue;
                                                                   m_smpcRowLength = smpcValue * m_nCols; }
      void SetInverseFilterLength(const AFSampleCount smpcValue) { m_smpcColLength = smpcValue;
                                                                   m_smpcRowLength = smpcValue * m_nCols;  }
      
      void SetFilterType(const int nValue) { m_nFilterType = nValue; }
      void SetInBandRegularisationParameter(const double dbValue)  { m_dbInRP  = dbValue; }
      void SetOutBandRegularisationParameter(const double dbValue) { m_dbOutRP = dbValue; }
      void SetLowerCutFrequency(const double dbValue)  { m_dbLowCutFrq  = dbValue; }
      void SetHigherCutFrequency(const double dbValue) { m_dbHighCutFrq = dbValue; }
      void SetTransitionWidth(const double dbValue)    { m_dbTransWidth = dbValue; }
      void SetFadeInLength(const  AFSampleCount smpcValue)  { m_smpcFadeIn = smpcValue; }
      void SetFadeOutLength(const  AFSampleCount smpcValue) { m_smpcFadeOut = smpcValue; }
      
      void SetAverageMode(const int nValue)      { m_nAvgMode = nValue; }
      void SetAverageType(const int nValue)      { m_nAvgType = nValue; }
      void SetAverageWidth(const double dbValue) { m_dbAvgWidth = dbValue; }  // TODO Check it!!

      void SetGaindB(const double dbValue) { m_dbGain = undB(dbValue); }
      void SetGain(const double dbValue)   { m_dbGain = dbValue; }
      
      // --- 'ctors
      AFKirkeby(const int nRows = 1, const int nCols = 1);
      ~AFKirkeby();
};

#endif // __AURORA_KIRKEBY_AFKIRK_H__

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



