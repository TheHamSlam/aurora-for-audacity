/****************************************************************
 *                                                              *
 *                 Multiple Convolver class                     *
 *                                                              *
 * This class performs N by N matrix filtering using            *
 * partitioned convolution engine.                              *
 *                                                              *
 * ------------------------------------------------------------ *
 *                                                              *
 * by Simone Campanini 2009                                     *
 *                                                              *
 * ------------------------------------------------------------ *
 *                                                              *
 * multivolver.cpp                                              *
 *                                                              *
 ***************************************************************/

#include "multivolver.h"


// -------------------------------------------
// AFMultivolver implementation
// -------------------------------------------

void AFMultivolver::SetFilterLength(const AFSampleCount f_len)
{
    m_smpcFLength = f_len;

    // Check it: case simple constructor...
    if( m_smpcInLength )
    {
       m_smpcOutLength = m_smpcInLength + m_smpcFLength;
       if(m_psmpOut != 0) delete [] m_psmpOut;
       for(int nRow=0; nRow < m_nRows; nRow++)
       {
          m_psmpOut[nRow] = new AFSample[m_smpcOutLength];
          memset(m_psmpOut[nRow], 0, sizeof(AFSample)*m_smpcOutLength);
       }
    } 
}

void AFMultivolver::ReverseFilter()
{
   if( !m_smpcFLength ) return;

   int nRow, nCol;
   AFSampleCount i;
   AFSample *tmp = new AFSample [m_smpcFLength];
   
   for(nRow = 0; nRow < m_nRows; nRow++)
   {
      for(nCol = 0; nCol < m_nRows; nCol ++)
      {
         for(i = 0; i < m_smpcFLength; i++)
            tmp[i] = m_psmpFilterMatrix[nRow][nCol][(m_smpcFLength-1) - i];
          memcpy(m_psmpFilterMatrix[nRow][nCol], tmp, m_smpcFLength*sizeof(AFSample));
      }
   }
   delete [] tmp;
}

void AFMultivolver::FindFilterPeakPosition()
{
    // This makes really sense only for 1 column filter matrixes....
    for(int nRow = 0; nRow < m_nRows; nRow++)
        if(m_psmpFilterMatrix[nRow][0]) 
		    m_psmpcFilterPeakPosition[nRow] = FindPeakPosition(m_psmpFilterMatrix[nRow][0], m_smpcFLength);
}

void AFMultivolver::PreserveOutputLength()
{
    for(int nRow = 0; nRow < m_nRows; nRow++)
        PreserveLength(m_psmpOut[nRow], m_smpcOutLength, m_smpcFLength, m_psmpcFilterPeakPosition[nRow]);
}


void AFMultivolver::SetInputVectorLength(const AFSampleCount in_len)
{
    m_smpcInLength  = in_len;

    // Check it: case simple constructor...
    if( m_smpcFLength )
    {
       m_smpcOutLength = m_smpcInLength + m_smpcFLength;
       if(m_psmpOut != 0) delete [] m_psmpOut;
       for(int nRow=0; nRow < m_nRows; nRow++)
       {
          m_psmpOut[nRow] = new AFSample [m_smpcOutLength];
          memset(m_psmpOut[nRow], 0, sizeof(AFSample)*m_smpcOutLength);
       }
    }
}

bool AFMultivolver::SetInputVectorItem(AFSample *p, const int index)
{
    if( !m_smpcInLength ) return false;
    m_psmpIn[index] = p;
    return true;
}

bool AFMultivolver::SetFilterMatrixItem(AFSample *f, const int nRow, const int nCol)
{
    if( !m_smpcFLength ) return false;
    m_psmpFilterMatrix[nRow][nCol] = f;
    return true;
}

AFSampleCount AFMultivolver::GetOutputVectorItemLength() const
{
    return m_bDone ? m_smpcOutLength : 0;
}

bool AFMultivolver::GetOutputVectorItem(AFSample *p, const int index) const
{
   if(!m_bDone) return false;
   memcpy(p, m_psmpOut[index], m_smpcOutLength*sizeof(AFSample));
   return true;
}

const AFSample * AFMultivolver::GetOutputVectorItem(const int index) const
{
    return m_bDone ? m_psmpOut[index] : 0;
}   

void AFMultivolver::GetOutputVectorsInterlaced(AFSample *p) const
{
    for(int i=0; i<m_smpcOutLength; i++)
       for(int nRow=0; nRow<m_nRows; nRow++)
          p[m_nRows*i+nRow] = m_psmpOut[nRow][i];
}

void AFMultivolver::PreProcess()
{
    if(m_abOpts[AFM_PRE_REVERSE_FILTER])
       ReverseFilter();
    else if(m_abOpts[AFM_PRESERVE_LENGTH])
       FindFilterPeakPosition();
}


bool AFMultivolver::Process()
{
    PreProcess();
    
    int nRow = 0;
    int nCol = 0;
    //int progress = 0;
    //AFSample square = 1.0 * _n * _n;
    AFSample *p;

    // Check if the setup has been done...
    if( !m_smpcInLength  || !m_smpcFLength ) return (m_bDone = false);
    
    for(nCol=0; nCol < m_nCols; nCol++)
        if( !m_psmpIn[nCol] ) return (m_bDone = false);

    // init progress meter
    InitOverallProgressMeter(m_nRows*m_nCols, 0);

    // Start processing.
    for(nCol=0; nCol < m_nCols; nCol++)
    {
        SetVector(m_psmpIn[nCol], m_smpcInLength);
        
        for(nRow=0; nRow < m_nRows; nRow++)
        {
            // if a m_psmpFilterMatrix item is null, the convolution result
            // will be null, so it doesn't make sense to do any sort of
            // calculation...
            if(m_psmpFilterMatrix[nRow][nCol])
            {
               SetFilter(m_psmpFilterMatrix[nRow][nCol], m_smpcFLength);
               if(!Convolve()) return (m_bDone = false);
               p = (AFSample *)GetResultVector();
               AddVector(p, m_psmpOut[nRow], m_smpcOutLength);
            
               // Update first block Autorange.
               if(m_abOpts[AFM_POST_FB_AUTORANGE]) m_psmpFbsMax[nRow] = m_smpFbMax;
            }
            UpdateOverallProgressMeter(nCol*m_nRows + (nRow+1), 0);
        }
    }
    m_bDone = true;
    
    PostProcess();
    
    // delete progress meter
    DestroyOverallProgressMeter();

    return m_bDone;
}

void AFMultivolver::PostProcess()
{
   int nRow;
   if(m_abOpts[AFM_POST_FB_MATRIX_AUTORANGE])
   {
       VectorFBAutorange();
          
   } else if(m_abOpts[AFM_POST_FB_AUTORANGE]) {
   
        for(nRow=0; nRow < m_nRows; nRow++)
        {
            Autorange(m_psmpOut[nRow], m_smpcOutLength, true);
        }
          
   } else if(m_abOpts[AFM_POST_MATRIX_AUTORANGE]) {
       
        VectorAutorange();
            
   } else if(m_abOpts[AFM_POST_AUTORANGE]) {

        for(nRow=0; nRow < m_nRows; nRow++)
        {
            Autorange(m_psmpOut[nRow], m_smpcOutLength);
        }
           
   }
   if(m_abOpts[AFM_POST_REMOVE_DC])
      VectorRemoveDC();
   if(m_abOpts[AFM_POST_GAIN])
      VectorBoost();
   
   if(m_abOpts[AFM_PRESERVE_LENGTH])
       PreserveOutputLength();
}

void AFMultivolver::AddVector(AFSample * b, AFSample * a, const AFSampleCount len)
{
    // a += b
    for(AFSampleCount i = 0; i < len; i++) a[i] += b[i];
}

bool AFMultivolver::VectorRemoveDC()
{
    if(!m_bDone)  return false;
    for(int nRow = 0; nRow < m_nRows; nRow++)
       RemoveDC(m_psmpOut[nRow], m_smpcOutLength);
    return true;
}

bool AFMultivolver::VectorFBAutorange()
{
    if(!m_bDone)  return false;
    AFSample smpMax = 0.0;
    
    //Find smpMax for every result
    for(AFSampleCount row=0; row<m_nRows; row++)
        smpMax = (m_psmpFbsMax[row]  > smpMax) ? m_psmpFbsMax[row] : smpMax;

    // Normalize @ -6 dB FS 
    // m_smpGain = 0.5/smpMax; //printf("Gain: %2.4f\n", m_smpGain); // *** DEBUG
    VectorBoost(1.0/2.0*smpMax);
    m_smpGain = m_smpGain - dB20(smpMax);
    return true;
}

bool AFMultivolver::VectorAutorange()
{
    if(!m_bDone)  return false;
#ifdef __AUDEBUG__    
    printf("Doing matrix autorange\n"); // *** DEBUG
#endif
    AFSampleCount i;
    AFSample smpMax = 0.0;
    
    //Find smpMax for every result
    for(AFSampleCount row=0; row<m_nRows; row++)
    {
        for(i=0; i<m_smpcOutLength; i++)
        {
            smpMax = (AFSample(fabs(m_psmpOut[row][i])) > smpMax) ? AFSample(fabs(m_psmpOut[row][i]))
                                                                  : smpMax;
        }
    }

    // Normalize @ -6 dB FS
#ifdef __AUDEBUG__            
    printf("multivolver: smpMax =  %.4f\n", smpMax); 
#endif
    m_smpGain = dB20(0.5/smpMax);
    VectorBoost();
#ifdef __AUDEBUG__
    printf("multivolver: Gain =  %.4f\n", m_smpGain); 
#endif
    return true;
}

bool AFMultivolver::VectorBoost()
{
    if(!m_bDone)  return false;
    AFSampleCount i;
    AFSample smpG = pow(10.0, m_smpGain/20.0);
    
    //Find max for every result
    for(AFSampleCount row=0; row<m_nRows; row++)
        for(i=0; i<m_smpcOutLength; i++) m_psmpOut[row][i] *= smpG;

    return true;
}

    
bool AFMultivolver::VectorBoost(const AFSample g)
{
    AFSampleCount i;
    
    if(!m_bDone)  return false;
    //Find max for every result
    for(AFSampleCount row=0; row<m_nRows; row++)
       for(i=0; i<m_smpcOutLength; i++) m_psmpOut[row][i] *= g;

    return true;
}


void AFMultivolver::InitVectors() 
{
   m_psmpIn  = new AFSample* [m_nCols];
   m_psmpOut = new AFSample* [m_nRows];
   m_psmpFilterMatrix = new AFSample** [m_nRows];

   m_pbOutSet = new bool  [m_nRows];

   m_psmpFbsMax = new AFSample [m_nRows];
   m_psmpcFilterPeakPosition = new AFSampleCount [m_nRows];
    
   int nCol, nRow;
   for(nCol=0; nCol < m_nCols; nCol++)
   {
       m_psmpIn[nCol]  = 0;
   }
   
   for(nRow=0; nRow < m_nRows; nRow++)
   {
      m_psmpFilterMatrix[nRow] = new AFSample* [m_nCols];
      m_psmpFbsMax[nRow] = 0;
      m_psmpcFilterPeakPosition[nRow] = 0;
      m_pbOutSet[nRow] = false;
    
      for(nCol=0; nCol < m_nCols; nCol++)
      {
          m_psmpFilterMatrix[nRow][nCol] = 0;
      }
   }
    
   for(int i = 0; i < AFM_N_OPTS; i++) 
       m_abOpts[i] = false;
}

void AFMultivolver::DeleteVectors() 
{
   for(int nRow=0; nRow < m_nRows; nRow++)
   {
      if(m_psmpFilterMatrix[nRow])
         delete [] m_psmpFilterMatrix[nRow];
   }  

   if(m_psmpIn) 
      delete [] m_psmpIn;
   if(m_psmpOut) 
      delete [] m_psmpOut;
   if(m_psmpFilterMatrix)
      delete [] m_psmpFilterMatrix;
   
   if(m_pbOutSet)
      delete [] m_pbOutSet;
   
   if(m_psmpFbsMax)
      delete [] m_psmpFbsMax;
   
   if(m_psmpcFilterPeakPosition)
       delete [] m_psmpcFilterPeakPosition;
}

// ---- ctors

AFMultivolver::AFMultivolver(const int N) 
    : AFConvolver(), 
      m_nRows(N), m_nCols(N),
      m_smpcInLength(0), m_smpcOutLength(0), m_smpcFLength(0),
      m_psmpIn(0), m_psmpOut(0), m_psmpFilterMatrix(0),
      m_pbOutSet(0),
      m_bDone(false),  m_bAborted(false)
{
   InitVectors();
}


AFMultivolver::AFMultivolver(const int N, 
                             const AFSampleCount in_len, const AFSampleCount f_len) 
    : AFConvolver(), 
      m_nRows(N), m_nCols(N),
      m_smpcInLength(in_len), m_smpcFLength(f_len),
      m_bDone(false), m_bAborted(false)
{
   InitVectors();
   
   m_smpcOutLength = m_smpcInLength + m_smpcFLength;
   
   for(int nRow=0; nRow < m_nRows; nRow++) {
        
       m_psmpOut[nRow]  = new AFSample  [m_smpcOutLength];
       memset(m_psmpOut[nRow], 0, sizeof(AFSample)*m_smpcOutLength);
   }
}

AFMultivolver::AFMultivolver(const int nRows, const int nCols)
  : AFConvolver(), 
    m_nRows(nRows), m_nCols(nRows),
    m_smpcInLength(0), m_smpcOutLength(0), m_smpcFLength(0),
    m_psmpIn(0), m_psmpOut(0), m_psmpFilterMatrix(0),
    m_pbOutSet(0),
    m_bDone(false),  m_bAborted(false)
{
   InitVectors();
}

AFMultivolver::AFMultivolver(const int nRows, const int nCols,
                             const AFSampleCount in_len, const AFSampleCount f_len)
  : AFConvolver(), 
    m_nRows(nRows), m_nCols(nCols),
    m_smpcInLength(in_len), m_smpcFLength(f_len),
    m_bDone(false), m_bAborted(false)
{
   InitVectors();
   
   m_smpcOutLength = m_smpcInLength + m_smpcFLength;
   
   for(int nRow=0; nRow < m_nRows; nRow++)
   {
       m_psmpOut[nRow]  = new AFSample  [m_smpcOutLength];
       memset(m_psmpOut[nRow], 0, sizeof(AFSample)*m_smpcOutLength);
   }
}


AFMultivolver::~AFMultivolver() 
{
   DeleteVectors();
}



// -------------------------------------------
// AFMatrixvolver implementation
// -------------------------------------------
void AFMatrixvolver::InitOverallProgressMeter(const int overall_range, const AFSampleCount range)
{
   mProgressDlg = new GTProgressIndicator(_("Aurora Matrix Convolver"), true, 2);
   if(overall_range > 0) SetOverallRange(overall_range);
   if(range > 0) SetRange(range);
}

void AFMatrixvolver::SetOverallRange(const int value)
{
   mProgressDlg->SetRange(value, 0);
}
void AFMatrixvolver::SetRange(const AFSampleCount value)
{
   mProgressDlg->SetRange(int(value), 1);
}

bool AFMatrixvolver::UpdateOverallProgressMeter(const int step, const int total)
{
   if(total > 0) mProgressDlg->SetRange(total, 0);
   return mProgressDlg->SetProgress(step, 0);  
}

bool AFMatrixvolver::UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total)
{
   if(total > 0) mProgressDlg->SetRange(int(total), 1);
   return mProgressDlg->SetProgress(int(step), 1);  
}

void AFMatrixvolver::DestroyOverallProgressMeter()
{
   if(mProgressDlg) delete mProgressDlg;
   mProgressDlg = 0;
}

// --- 'ctors
AFMatrixvolver::AFMatrixvolver(const int N) 
  : AFMultivolver(N),
    mProgressDlg(0)
{}

AFMatrixvolver::AFMatrixvolver(const int N, const AFSampleCount in_len, const AFSampleCount f_len) 
  : AFMultivolver(N, in_len, f_len),
    mProgressDlg(0)
{}

AFMatrixvolver::AFMatrixvolver(const int nRows,
                               const int nCols)
  : AFMultivolver(nRows, nCols),
    mProgressDlg(0)
{}

AFMatrixvolver::AFMatrixvolver(const int nRows, const int nCols,
                               const AFSampleCount in_len, const AFSampleCount f_len) 
  : AFMultivolver(nRows, nCols, in_len, f_len),
    mProgressDlg(0)
{}


AFMatrixvolver::~AFMatrixvolver() 
{
   DestroyProgressMeter();
}
