/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Aurora Convolver

  auconv.h

  Simone Campanini

**********************************************************************/
#ifndef __AURORA_CONVOLVER_AUCONV_H__
#define __AURORA_CONVOLVER_AUCONV_H__

#include <commdefs.h>
#include <afconfig.h>

#include "multivolver.h"

class AuroraConvolver {


private:
   double mRate;
   int    mIrRows;
   int    mIrCols;
   bool   mMatrixMode;
   bool   mCancelCrossTalk;
   bool   mFullAutorange;
   bool   mFirstBlockAutorange;
   bool   mTimeReversedIr;
   bool   mPreserveLength;
   bool   mOneForAll;
   double mGain;           // dB
   
   AFSample **mIr;    
   AFSample **mAudioData;
   AFSample **mOutputData;
   
   AFSampleCount mIrLength;
   AFSampleCount mAudioDataLength;
   AFSampleCount mOutputDataLength;
   
   AFSample *mMin;
   AFSample *mMax;
   
   AFMatrixvolver *mAfm;
   
   AFConfig mCfg;
   
public:
   //void ResetData();
   bool InitIrTrack(const int idx);
   bool InitAudioDataTrack(const int idx);
   void DeleteIrTrack(const int idx);
   void DeleteAudioDataTrack(const int idx);
   bool CheckSamplerate(const double value);
   
   
   // *** Get/setters
   bool IsMatrixMode()          const { return mMatrixMode; }
   bool IsCancelCrossTalk()     const { return mCancelCrossTalk; }
   bool IsFullAutorange()       const { return mFullAutorange; }
   bool IsFirstBlockAutorange() const { return mFirstBlockAutorange; }
   bool IsTimeReversedIr()      const { return mTimeReversedIr; }
   bool IsPreserveLength()      const { return mPreserveLength; }
   bool IsOneForAll()           const { return mOneForAll; }
   double GetGain()             const { return mGain; }
   double GetSamplerate()       const { return mRate; }
   int  GetAudioDataRows()      const { return mIrCols; }
   int  GetIrRows()             const { return mIrRows; }
   int  GetIrCols()             const { return mIrCols; }
   
   AFSample *GetIrTrack(int idx)                 { return mIr[idx]; }
   AFSampleCount GetIrTrackLength()        const { return mIrLength; }
   AFSample *GetAudioDataTrack(int idx)          { return mAudioData[idx]; }
   AFSampleCount GetAudioDataTrackLength() const { return mAudioDataLength; }
   AFSample *GetOutputDataTrack(int idx)         { return mOutputData[idx]; }
   AFSampleCount GetOutputTrackLength()    const { return (mOutputDataLength - ((mPreserveLength) ? mIrLength : 0)); }
   AFSample GetIrMin(int idx)              const { return mMin[idx]; }
   AFSample GetIrMax(int idx)              const { return mMax[idx]; }
   AFSample GetAbsIrMin();
   AFSample GetAbsIrMax();
   AFSampleCount GetFFTLength();
   
   void SetSamplerate(double value)     { mRate = value; }
   void SetIrMatrixDimensions(const int rows = 1, const int cols = 1);
   
   void SetMatrixMode(const bool value)       { if((mMatrixMode = value))
                                                   mOneForAll = false; } 
   void SetCancelCrossTalk(const bool value)  { mCancelCrossTalk = value; }
   void SetFullAutorange(const bool value)    { if((mFullAutorange = value)) 
                                                   mFirstBlockAutorange = false; }
   void SetFirstBlockAutorange(const bool value) { if((mFirstBlockAutorange = value)) 
                                                      mFullAutorange = false; }
   void SetTimeReversedIr(const bool value)      { mTimeReversedIr = value; }
   void SetPreserveLength(const bool value)      { mPreserveLength = value; }
   void SetOneForAll(const bool value)           { if((mOneForAll = value)) 
                                                      mMatrixMode = false; }
   void SetGain(const double value)              { mGain = value; }
   
   bool SetIrTrackLength(AFSampleCount value);
   bool SetAudioDataTrackLength(AFSampleCount value);
   void SetIrMin(int idx, AFSample value)  { mMin[idx] = value; }
   void SetIrMax(int idx, AFSample value)  { mMax[idx] = value; }
   

   
   // *** processing
  private:
   void MatrixConvolution();
   void StereoConvolution();   // only if Cancel Crosstalk is set
   void CancelCrossTalkConvolution();
   void MultitrackConvolution();
   void MultitrackMonoConvolution();
  public: 
   bool Calculate();
   
   void ReadConfigurationValues();
   void StoreConfigurationValues();
   
   // *** Ctors
   AuroraConvolver();
   ~AuroraConvolver();

};

#endif // __AURORA_CONVOLVER_AUCONV_H__

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

