/****************************************************************
 *                                                              *
 *                 Multiple Convolver class                     *
 *                                                              *
 * This class performs N by N matrix filtering using            *
 * partitioned convolution engine.                              *
 *                                                              *
 * ------------------------------------------------------------ *
 * Usage:                                                       *
 *                                                              *
 * 1) Instantiate the class using one of the constructors       *
 *    provided;                                                 *
 * 2) if not done by the constructor, set the filter and the    *
 *    vector using 'SetFilter' and 'SetVector' methods;         *
 * 3) call the 'Convolve' method to start calculations;         *
 * 4) get results using 'GetResultSize' and 'GetResultVector'   *
 *    methods.                                                  *
 * 5) At this point you can load another filter or another      *
 *    vector using 'SetFilter' and/or 'SetVector' and recall    *
 *    'Convolve'.                                               *
 *                                                              *
 * ------------------------------------------------------------ *
 *                                                              *
 * by Simone Campanini 2009                                     *
 *                                                              *
 * ------------------------------------------------------------ *
 *                                                              *
 * multivolver.h                                                *
 *                                                              *
 ***************************************************************/
#ifndef __AURORA_MULTIVOLVER_H__
#define __AURORA_MULTIVOLVER_H__

#include "convolver.h"

//#define MV_AUTORANGE 0x01
//#define MV_REMOVEDC  0x02
//#define MV_BOOST     0x04

class AFMultivolver : public AFConvolver
{
 public:
    enum { AFM_PRE_REVERSE_FILTER = 0,
           AFM_POST_AUTORANGE = 1,    AFM_POST_FB_AUTORANGE,
           AFM_POST_MATRIX_AUTORANGE, AFM_POST_FB_MATRIX_AUTORANGE,
           AFM_POST_REMOVE_DC,        AFM_POST_GAIN,
           AFM_PRESERVE_LENGTH,
           AFM_N_OPTS };
      
  private:
    // ***************************** Attributes *******************************
    int m_nRows;
    int m_nCols;
    
    AFSampleCount m_smpcInLength;
    AFSampleCount m_smpcOutLength;
    AFSampleCount m_smpcFLength;

    AFSample**  m_psmpIn;
    AFSample**  m_psmpOut;
    AFSample*** m_psmpFilterMatrix;

    bool* m_pbOutSet;

    //AFSample  m_smpGain;
    AFSample* m_psmpFbsMax;
    AFSampleCount* m_psmpcFilterPeakPosition;
    
    bool m_bDone;
    bool m_bAborted;

    bool m_abOpts [AFM_N_OPTS];
    
  public:    
    // Setup methods
    void SetFilterLength(const AFSampleCount f_len);
    void SetInputVectorLength(const AFSampleCount in_len);
    bool SetInputVectorItem(AFSample *p, const int index);
    bool SetFilterMatrixItem(AFSample *f, const int row, const int col);

    AFSampleCount GetOutputVectorItemLength() const;
    bool GetOutputVectorItem(AFSample *p, const int index) const;
    const AFSample *GetOutputVectorItem(const int index) const;
    void GetOutputVectorsInterlaced(AFSample *p) const;   // NB: p must be a AFSample array of out_length*N size.

    virtual void PreProcess();
    virtual bool Process();
    virtual void PostProcess(); // as opts you can 'or' MV_AUTORANGE, MV_REMOVEDC and MV_BOOST
    
   void InitProgressMeter() {}
   virtual void InitOverallProgressMeter(const int overall_range, const AFSampleCount range) = 0;
   virtual bool UpdateOverallProgressMeter(const int step, const int total) = 0;
   virtual bool UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total) { return true; }
   virtual void DestroyOverallProgressMeter() = 0;
   void DestroyProgressMeter() {}
    //virtual bool UpdateMeter(const int value) const;

 private:
    void AddVector(AFSample *b, AFSample *a, const AFSampleCount len);
    void ReverseFilter();
    void FindFilterPeakPosition(); 
    void PreserveOutputLength();
    
    bool VectorBoost();                 // uses class gain (SetGain)
    bool VectorBoost(const AFSample g);
    bool VectorRemoveDC();
    bool VectorFBAutorange();
    bool VectorAutorange();

 public:
    // --- boolcheckers, get-setters     
    bool IsTimeReversedFilter()        const { return m_abOpts[AFM_PRE_REVERSE_FILTER]; }
    bool IsAutorange()                 const { return m_abOpts[AFM_POST_AUTORANGE]; }
    bool IsMatrixAutorange()           const { return m_abOpts[AFM_POST_MATRIX_AUTORANGE]; }
    bool IsFirstBlockAutorange()       const { return m_abOpts[AFM_POST_FB_AUTORANGE]; }
    bool IsFirstBlockMatrixAutorange() const { return m_abOpts[AFM_POST_FB_MATRIX_AUTORANGE]; }
    bool IsRemoveDC()                  const { return m_abOpts[AFM_POST_REMOVE_DC]; }
    bool IsApplyGain()                 const { return m_abOpts[AFM_POST_GAIN]; }
    bool IsPreserveLength()            const { return m_abOpts[AFM_PRESERVE_LENGTH]; }
    
    //AFSample GetGainValue()     const { return m_smpGain; }  // dB
    
    //void SetGainValue(const AFSample smpValue)     { m_smpGain  = smpValue; } // dB
    void SetTimeReversedFilter(const bool bValue)  { m_abOpts[AFM_PRE_REVERSE_FILTER] = bValue; }
    void SetAutorange(const bool bValue)          { if((m_abOpts[AFM_POST_AUTORANGE] = bValue) == true)
                                                        m_abOpts[AFM_POST_MATRIX_AUTORANGE] = false; }
    void SetMatrixAutorange(const bool bValue)    { if((m_abOpts[AFM_POST_MATRIX_AUTORANGE] = bValue) == true)
                                                        m_abOpts[AFM_POST_AUTORANGE] = false; }
    void SetFirstBlockAutorange(const bool bValue) { if((m_abOpts[AFM_POST_FB_AUTORANGE] = bValue) == true)
                                                         m_abOpts[AFM_POST_FB_MATRIX_AUTORANGE] = false; }
    void SetFirstBlockMatrixAutorange(const bool bValue) { if((m_abOpts[AFM_POST_FB_MATRIX_AUTORANGE] = bValue) == true)
                                                               m_abOpts[AFM_POST_FB_AUTORANGE] = false; }
    void SetRemoveDC(const bool bValue)       { m_abOpts[AFM_POST_REMOVE_DC] = bValue;}
    void SetApplyGain(const bool bValue)      { m_abOpts[AFM_POST_GAIN] = bValue; }
    void SetPreserveLength(const bool bValue) { m_abOpts[AFM_PRESERVE_LENGTH] = bValue; }

  private:
    void InitVectors();  
    void DeleteVectors();  
      
    // --- 'ctors
    // - N is the filter matrix order (if it is a square matrix);
    // - rows and cols are referred always to the
    //   filter matrix, so if you have a N x M input filter matrix,
    //   you need a M rows input data vector, and you'll obtain an
    //   M rows output data vector
  public:
	AFMultivolver(const int N);
    AFMultivolver(const int N, 
                  const AFSampleCount in_len, const AFSampleCount f_len); 
    AFMultivolver(const int rows, const int cols); 
    AFMultivolver(const int rows, const int cols, 
                  const AFSampleCount in_len, const AFSampleCount f_len); 
    ~AFMultivolver();

};


#include <gtprogind.h>

class AFMatrixvolver : public AFMultivolver
{
  private:
     GTProgressIndicator *mProgressDlg;

  protected:
     void InitOverallProgressMeter(const int overall_range, const AFSampleCount range);
     void SetOverallRange(const int value);
     void SetRange(const AFSampleCount value);
     bool UpdateOverallProgressMeter(const int step, const int total);
     bool UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total);
     void DestroyOverallProgressMeter();

  public:
     AFMatrixvolver(const int N);
     AFMatrixvolver(const int N, 
                    const AFSampleCount in_len, const AFSampleCount f_len);
     AFMatrixvolver(const int rows, const int cols);
     AFMatrixvolver(const int rows, const int cols, 
                    const AFSampleCount in_len, const AFSampleCount f_len);
     ~AFMatrixvolver();
};


#endif // __AURORA_MULTIVOLVER_H__