/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Aurora Convolver

  auconv.cpp

  Simone Campanini

**********************************************************************/

#include "auconv.h"

bool AuroraConvolver::InitIrTrack(const int idx)
{
   if( (!mIrRows) || (!mIrLength) ) return false;
   if(!mIr)
   { 
       mIr = new AFSample* [mIrRows];
       for(int i=0; i < mIrRows; i++) mIr[i] = 0;
   }
   mIr[idx] = new AFSample [mIrLength];
   return true;
}

bool AuroraConvolver::InitAudioDataTrack(const int idx)
{
   if( (!mIrCols) || (!mAudioDataLength) ) return false;
   if(!mAudioData)
   {
       mAudioData = new AFSample* [mIrCols];
       for(int i=0; i < mIrCols; i++) mAudioData[i] = 0;
   }
   mAudioData[idx] = new AFSample[mAudioDataLength];
   return true;
}

void AuroraConvolver::DeleteIrTrack(const int idx) 
{
   if(mIr && mIr[idx]) delete [] mIr[idx];
}

void AuroraConvolver::DeleteAudioDataTrack(const int idx) 
{
   if(mAudioData && mAudioData[idx]) delete [] mAudioData[idx];
}

bool AuroraConvolver::CheckSamplerate(const double value) 
{
   return (mRate != value) ? false : true;   // rate mismatch
}

AFSample AuroraConvolver::GetAbsIrMin()
{
    AFSample max = AFSample(-1.0e-12);
    if(mMax)
       for(int i = 0; i < mIrRows; i++)
          max = (mMax[i] > max) ? mMax[i] : max;
    return max;    
}

AFSample AuroraConvolver::GetAbsIrMax()    
{
    AFSample min = AFSample(1.0e+12);
    if(mMin)
       for(int i = 0; i < mIrRows; i++)
          min = (mMin[i] > min) ? mMin[i] : min;
    return min;    
}

AFSampleCount AuroraConvolver::GetFFTLength()
{
    AFSampleCount l = 2;
    while( (l *= 2) < mIrLength );
    return l+1;
}

void AuroraConvolver::SetIrMatrixDimensions(const int rows,const int cols)
{
    mIrRows = rows; mIrCols = cols;
    
    if(mOneForAll) 
       mIrRows = mIrCols;
    
    if(mIr) delete [] mIr;
    mIr = new AFSample* [mIrRows];
    
    if(mAudioData) delete [] mAudioData;
    mAudioData = new AFSample* [mIrCols];
    
    if(mMin) delete [] mMin;
    mMin = new AFSample [mIrRows];
    
    if(mMax) delete [] mMax;
    mMax = new AFSample [mIrRows];
    
    for(int i=0; i < mIrRows; i++) { 
        mIr[i] = 0;  
        mMin[i] = 0; mMax[i] = 0;
    }
    for(int i=0; i < mIrCols; i++) 
        mAudioData[i] = 0;
}


bool AuroraConvolver::SetIrTrackLength(AFSampleCount value) 
{
   if(!mIrLength) mIrLength = value;
   return (mIrLength != value) ? false : true; // length mismatch
}

bool AuroraConvolver::SetAudioDataTrackLength(AFSampleCount value) 
{
   if(!mAudioDataLength) mAudioDataLength = value;
   return (mAudioDataLength != value) ? false: true; // length mismatch
}
   
   
// *** processing

void AuroraConvolver::MatrixConvolution()
{
   mAfm = new AFMatrixvolver(mIrRows, mIrCols, mAudioDataLength, mIrLength/mIrCols);
    
   // Class setup
   mAfm->SetTimeReversedFilter(mTimeReversedIr);
   if(IsFullAutorange())
   {
      mAfm->SetMatrixAutorange(true);
      mAfm->SetRemoveDC(true);
      
   } else if(mGain != 0.0) {
   
      mAfm->SetApplyGain(true);
      mAfm->SetGainValue(mGain);
   }
   
   // Load vectors
   AFSample *p;
   int row, col;
   for(row = 0; row < mIrRows; row++)
   {
      mAfm->SetInputVectorItem(mAudioData[row], row);

      for(col = 0; col < mIrCols; col++)
      {
         p = mIr[row] + col*(mIrLength/mIrCols);
         mAfm->SetFilterMatrixItem(p, row, col);
      }
   }
   
   mAfm->Process();
   
   for(row = 0; row < mIrRows; row++)
   {
      mOutputDataLength = mAfm->GetOutputVectorItemLength();
      mOutputData[row]  = (AFSample *)mAfm->GetOutputVectorItem(row);
   }
   
   mGain = double(mAfm->GetGainValue()); // for storing purposes...
}

void AuroraConvolver::CancelCrossTalkConvolution()
{
   mAfm = new AFMatrixvolver(2, mAudioDataLength, mIrLength);
    
   // Class setup
   mAfm->SetTimeReversedFilter(mTimeReversedIr);
   mAfm->SetFirstBlockMatrixAutorange(mFirstBlockAutorange);
   if(mFullAutorange)
   {
      mAfm->SetMatrixAutorange(true);
      mAfm->SetRemoveDC(true);
      
   } else if(mGain != 0.0) {
   
      mAfm->SetApplyGain(true);
      mAfm->SetGainValue(mGain);
   }
   
   // Load vectors follows this layout:
   /*
      |hl hr|   |xl|
      |hr hl| * |xr| = |xlhl+xrhr xlhr+xrhl| = |yl yr|
   */
   
   mAfm->SetInputVectorItem(mAudioData[CH_LEFT], CH_LEFT);
   mAfm->SetInputVectorItem(mAudioData[CH_RIGHT], CH_RIGHT);

   mAfm->SetFilterMatrixItem(mIr[CH_LEFT], 0, 0);
   mAfm->SetFilterMatrixItem(mIr[CH_LEFT], 1, 1);
   mAfm->SetFilterMatrixItem(mIr[CH_RIGHT], 0, 1);
   mAfm->SetFilterMatrixItem(mIr[CH_RIGHT], 1, 0);

   mAfm->Process();
   
   for(int row = 0; row < 2; row++)
   {
      mOutputDataLength = mAfm->GetOutputVectorItemLength();
      mOutputData[row]  = (AFSample *)mAfm->GetOutputVectorItem(row);
   }
   
   mGain = double(mAfm->GetGainValue()); // for storing purposes...
}

void AuroraConvolver::MultitrackConvolution()
{
   mAfm = new AFMatrixvolver(mIrRows, mAudioDataLength, mIrLength);
    
   // Class setup
   mAfm->SetTimeReversedFilter(mTimeReversedIr);
   mAfm->SetFirstBlockAutorange(mFirstBlockAutorange);
   // This is the only case where preserve length has sense...
   mAfm->SetPreserveLength(mPreserveLength);
   
   if(mFullAutorange)
   {
      printf("This IS full autorange\n");
      mAfm->SetAutorange(true);
      mAfm->SetRemoveDC(true);
      
   } else { //if(mGain != 0.0) {
   
      printf("This is NOT full autorange\n");
      mAfm->SetApplyGain(true);
      mAfm->SetGainValue(mGain);
   }
   
   // It loads vectors following this layout:
   /*
      |h1  0  0 ...  0|   |x1|
      | 0 h2  0 ...  0|   |x2|
      | 0  0 h3 ...  0|   |x3| 
      | .  .  .  .   .| * | .|  = |y1 y2 y3 ... yn|
      | .  .  .  .   .|   | .|
      | .  .  .  .   .|   | .|
      | 0  0  0 ... hn|   |xn|
   
   */
   int row;
   for(row = 0; row < mIrRows; row++)
   {
      mAfm->SetInputVectorItem(mAudioData[row], row);      
      if(!mOneForAll)
         mAfm->SetFilterMatrixItem(mIr[row], row, row);
      else
         mAfm->SetFilterMatrixItem(mIr[0], row, row);
   }

   mAfm->Process();

   for(row = 0; row < mIrRows; row++)
   {
      mOutputDataLength = mAfm->GetOutputVectorItemLength();
      mOutputData[row]  = (AFSample *)mAfm->GetOutputVectorItem(row);
   }
   
   mGain = double(mAfm->GetGainValue()); // for storing purposes...
}

bool AuroraConvolver::Calculate()
{
   // prepare output array
   mOutputData = new AFSample* [mIrRows];
   
   if(mMatrixMode)
   {
      MatrixConvolution();

   } else {
   
      if(mCancelCrossTalk && (mIrRows == 2) && (mIrCols == 2))
         CancelCrossTalkConvolution();
      else
         MultitrackConvolution();
   }

   return true; 
}
 
void AuroraConvolver::ReadConfigurationValues()
{
   // Read parameter from stored configuration
   double dbValue;
   if(mCfg.Read(_("/Aurora/Convolver/Gain"), &dbValue))
      mGain =  dbValue;
   bool bValue;
   if(mCfg.Read(_("/Aurora/Convolver/FullAutorange"), &bValue))
      SetFullAutorange(bValue);
   if(mCfg.Read(_("/Aurora/Convolver/FirstBlockAutorange"), &bValue))
      SetFirstBlockAutorange(bValue);
   if(mCfg.Read(_("/Aurora/Convolver/CancelCrossTalk"), &bValue))
      SetCancelCrossTalk(bValue);
   if(mCfg.Read(_("/Aurora/Convolver/TimeReversedIr"), &bValue))
      SetTimeReversedIr(bValue);
   if(mCfg.Read(_("/Aurora/Convolver/PreserveLength"), &bValue))
      SetPreserveLength(bValue);
   
}

void AuroraConvolver::StoreConfigurationValues()
{
   mCfg.Write(_("/Aurora/Convolver/Gain"), mGain);
   mCfg.Write(_("/Aurora/Convolver/FullAutorange"), mFullAutorange);
   mCfg.Write(_("/Aurora/Convolver/FirstBlockAutorange"), mFirstBlockAutorange);
   mCfg.Write(_("/Aurora/Convolver/CancelCrossTalk"), mCancelCrossTalk);
   mCfg.Write(_("/Aurora/Convolver/TimeReversedIr"), mTimeReversedIr);
   mCfg.Write(_("/Aurora/Convolver/PreserveLength"), mPreserveLength);
}
   
 
// *** Ctors
AuroraConvolver::AuroraConvolver()
  : mRate(0),
    mIrRows(1), mIrCols(1),
    mMatrixMode(false),
    mCancelCrossTalk(false),
    mFullAutorange(true),
    mFirstBlockAutorange(false),
    mTimeReversedIr(false),
    mPreserveLength(false),
    mOneForAll(false),
    mGain(0.0),
    mIr(0),
    mAudioData(0),
    mOutputData(0),
    mIrLength(0),
    mAudioDataLength(0),
    mOutputDataLength(0),
    mMin(0), mMax(0), 
	mAfm(0)
{
   // read parameters values from stored configuration
   ReadConfigurationValues();
}

AuroraConvolver::~AuroraConvolver()
{
   for(int i = 0; i < mIrRows; i++) 
      DeleteIrTrack(i);
   for(int i = 0; i < mIrCols; i++) 
      DeleteAudioDataTrack(i);
   
   if(mIr)        delete [] mIr;
   if(mAudioData) delete [] mAudioData;
   if(mMin)       delete [] mMin;
   if(mMax)       delete [] mMax;
   
   if(mAfm) delete mAfm;
/*   
   if(mAfc) {
       
       delete mAfc;
       for(int i = 0; i < mChannels; i++) 
           if(mOutputData[i]) delete [] mOutputData[i];
   }
   */
   
   if(mOutputData) delete [] mOutputData;
}

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

