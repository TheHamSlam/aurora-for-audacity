/****************************************************************
 *                                                              *
 *                       Convolver class                        *
 *                                                              *
 * This class is a partitioned convolution engine: it simply    *
 * takes as input a vector and a filter, then evaluates the     *
 * convolution product between them.                            *
 * It is not very optimized, but it's simple and works quite    *
 * well.                                                        *
 *                                                              *
 * ------------------------------------------------------------ *
 * Usage:                                                       *
 *                                                              *
 * 1) Instantiate the class using one of the constructors       *
 *    provided;                                                 *
 * 2) if not done by the constructor, set the filter and the    *
 *    vector using 'SetFilter' and 'SetVector' methods;         *
 * 3) call the 'Process' method to start calculations;          *
 * 4) get results using 'GetResultSize' and 'GetResultVector'   *
 *    methods.                                                  *
 * 5) At this point you can load another filter or another      *
 *    vector using 'SetFilter' and/or 'SetVector' and recall    *
 *    'Process'.                                                *
 *                                                              *
 * ------------------------------------------------------------ *
 *                                                              *
 * by Simone Campanini 2009                                     *
 *                                                              *
 * ------------------------------------------------------------ *
 *                                                              *
 * convolver.h                                                  *
 *                                                              *
 ***************************************************************/

/*
  This file contains the convolution class.

 */
#ifndef __AURORA_CONVOLVER_H__
#define __AURORA_CONVOLVER_H__

#include <commdefs.h>

#include <fftw3.h>
#include <string.h>

/*
  PRESERVE LENGTH
  ---------------
  Si identifica il "Picco centrale" della rfisposta all'impulso. Esso
  deve corrispondere allo "zero time" della convoluzione. Quindi, se la
  IR era lunga N campioni, essa tendenzialmente "ritarda" di N-1
  campioni il segnale con essa convoluto. Ma, se devo rispettare lo
  "zero time" al campione P, vuol dire che, una volta fatta la
  convoluzione, buttero' via i primi P-1 campioni all'inizio del segnale
  convoluto, e gli ultimi N-P campini alla fine. In questo modo, il
  segnale convoluto, anziche' esere lungo M+N-1 campioni, sara' lungo M
  campioni, come il segnale originale.
  
*/

class AFConvolver
{
 public:
    enum PreProcessTags{ AFC_PRE_REVERSE_FILTER = 0 }; 
    enum PostProcessTags{ AFC_POST_AUTORANGE = 1, AFC_POST_FB_AUTORANGE, AFC_POST_REMOVE_DC, AFC_POST_GAIN, AFC_N_OPTS }; 
     
  private:
    AFSampleCount m_smpcFftLength;
    AFSampleCount m_smpcBlockLength;
    AFSample      m_smpInvBlockLength;

    AFSample* m_psmpX; //vectors to be convolved
    AFSample* m_psmpH; //filter
    AFSample* m_psmpY; //results vector

    AFSample* m_psmpXt;
    AFSample* m_psmpHt;
    AFSample* m_psmpYt;

    AFSampleCount m_smpcXLength;
    AFSampleCount m_smpcHLength;
    AFSampleCount m_smpcYLength;
    
    // fftw3 stuffs
    fftwf_complex* m_pcpxXf;
    fftwf_complex* m_pcpxHf;
    fftwf_complex* m_pcpxYf;

    fftwf_plan m_fftwForwardPlan;
    fftwf_plan m_fftwBackwardPlan;
    
    //Flag useful when reload vectors
    bool m_bFilterSet;
    bool m_bVectorSet;
    
    // pre-post process options
    bool m_abOpts[AFC_N_OPTS];
    
  protected:
    AFSample m_smpGain;
    AFSample m_smpFbMax;
    AFSampleCount m_smpcPeakPosition;
 
    AFSampleCount BlockSize() const;
    AFSample      FindMax(AFSample *v, AFSampleCount len) const;
    void AdjustVectorHead(const AFSampleCount smpcOldHLength, const AFSampleCount smpcNewHLength);

    void LoadFilter();
    void LoadBlock(const AFSampleCount from, const AFSampleCount to);
    void StoreResultBlock(const AFSampleCount from);

    void BlockConvolve();
    void FFT(fftwf_complex *Vf, AFSample *vt);
    void IFFT(AFSample *vt, fftwf_complex *Vf);
 
    // ***** Set Input data
  public:
    void SetFilter(AFSample *f, AFSampleCount flen);
    void SetVector(AFSample *v, AFSampleCount vlen);

    // ***** Pre-processing methods
    virtual void PreProcess();
    
  protected:    
    virtual void ReverseFilter();
    virtual void FindFilterPeakPosition(); 
    virtual void PreserveOutputLength();
    
  public:
    AFSampleCount FindPeakPosition(AFSample* psmpH, const AFSampleCount smpcHLength);
    void PreserveLength(AFSample* psmpV, const AFSampleCount smpcVLength, const AFSampleCount smpcHLength, const AFSampleCount smpcPeakPostion = 0);
    
  public:
    // *** THIS should be called for calculations...
    virtual bool Process(); 
    
    // ***** This methods does the convolution calculations
    bool Convolve();

    // ***** Post-processing methods
    virtual void PostProcess();
    
  protected:
    virtual void Gain();
    virtual void Autorange(); // these operate on output vector.
    virtual void RemoveDC();
    
  public:
    void Gain(AFSample *v, AFSampleCount len);
    void Autorange(AFSample *v, AFSampleCount len, const bool bFirstBlockAR = false);
    void RemoveDC(AFSample *v, AFSampleCount len);
  
    // ***** Methods to get results
    AFSampleCount   GetResultSize()  const { return m_smpcXLength; }
    AFSampleCount   GetResultVector(AFSample *p) const { memcpy(p, m_psmpY, m_smpcXLength * sizeof(AFSample));
                                                          return m_smpcXLength; }
    const AFSample *GetResultVector() const { return m_psmpY; }

    // ***** General purpose get/setters, boolcheck
    bool IsTimeReversedFilter()  const { return m_abOpts[AFC_PRE_REVERSE_FILTER]; }
    bool IsAutorange()           const { return m_abOpts[AFC_POST_AUTORANGE]; }
    bool IsFirstBlockAutorange() const { return m_abOpts[AFC_POST_FB_AUTORANGE]; }
    bool IsRemoveDC()            const { return m_abOpts[AFC_POST_REMOVE_DC]; }
    bool IsGain()                const { return m_abOpts[AFC_POST_GAIN]; }
    
    AFSample GetGainValue()     const { return m_smpGain; }  // dB
    AFSampleCount GetFFTSize()  const { return m_smpcFftLength; }  // samples
    AFSample GetFirstBlockMax() const { return m_smpFbMax; }
    
    void SetGainValue(AFSample value)       { m_smpGain  = value; } // dB
    void SetTimeReversedFilter(bool value)  { m_abOpts[AFC_PRE_REVERSE_FILTER] = value; }
    void SetAutorange(bool value)           { m_abOpts[AFC_POST_AUTORANGE] = value; }
    void SetFirstBlockAutorange(bool value) { m_abOpts[AFC_POST_FB_AUTORANGE] = value; }
    void SetRemoveDC(bool value)            { m_abOpts[AFC_POST_REMOVE_DC] = value;}
    void SetGain(bool value)                { m_abOpts[AFC_POST_GAIN] = value; }

 protected:   
	virtual void InitProgressMeter() = 0;
	virtual bool UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total) = 0;
	virtual void DestroyProgressMeter() = 0;
 
 public:
    // ***** ctors    
    AFConvolver();
    AFConvolver(AFSample *vector, AFSample *filter, 
                const AFSampleCount vlen, const AFSampleCount flen, const int opts = 0);

    ~AFConvolver();

}; 

#endif // __AURORA_CONVOLVER_H__