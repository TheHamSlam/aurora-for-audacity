/****************************************************************
 *                                                              *
 *                       AFConvolver class                        *
 *                                                              *
 * This class is a partitioned convolution engine: it simply    *
 * takes as input a vector and a filter, then evaluates the     *
 * convolution product between them.                            *
 * It is not very optimized, but it's simply and works quite    *
 * fine.                                                        *
 * ------------------------------------------------------------ *
 *                                                              *
 * by Simone Campanini 2009                                     *
 *                                                              *
 * ------------------------------------------------------------ *
 *                                                              *
 * convolver.cpp                                                *
 *                                                              *
 ***************************************************************/

/*
  This file contains the convolution class code.

 */
#include "convolver.h"


void AFConvolver::SetFilter(AFSample *f, AFSampleCount len)
{
    // Save old m_smpcHLength value
    AFSampleCount smpcOldHLength = m_smpcHLength;

    m_psmpH = f;
    m_smpcHLength = len;
    //printf("len: %ld\n", len);
    
    if( m_bFilterSet )
    {
        fftwf_free(m_psmpXt); m_psmpXt = 0;
        fftwf_free(m_psmpHt); m_psmpHt = 0;
        fftwf_free(m_psmpYt); m_psmpYt = 0;
        fftwf_free(m_pcpxXf); m_pcpxXf = 0;
        fftwf_free(m_pcpxHf); m_pcpxHf = 0;
        fftwf_free(m_pcpxYf); m_pcpxYf = 0;

        fftwf_destroy_plan(m_fftwForwardPlan);
        fftwf_destroy_plan(m_fftwBackwardPlan);
    }        
    
    //Search for the optimal size.
    m_smpcBlockLength = BlockSize();
    m_smpcFftLength = (m_smpcBlockLength / 2) + 1;

   //Useful for calculations
    m_smpInvBlockLength = AFSample(1.0/m_smpcBlockLength);

    m_psmpXt = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_psmpHt = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_psmpYt = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
        
    m_pcpxXf = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    m_pcpxHf = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    m_pcpxYf = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    
    m_fftwForwardPlan  = fftwf_plan_dft_r2c_1d(m_smpcBlockLength, m_psmpXt, m_pcpxXf, FFTW_ESTIMATE);
    m_fftwBackwardPlan = fftwf_plan_dft_c2r_1d(m_smpcBlockLength, m_pcpxYf, m_psmpYt, FFTW_ESTIMATE);

    //Adjust vector head if necessary
    
    if( m_bVectorSet && (smpcOldHLength != m_smpcHLength) )
        AdjustVectorHead(smpcOldHLength, m_smpcHLength);
    

    //initialize filter vector
    LoadFilter();

    m_bFilterSet = true;

}

void AFConvolver::SetVector(AFSample *v, AFSampleCount len)
{
    m_smpcXLength = m_smpcHLength + len;
    m_smpcYLength = m_smpcXLength;

    if(m_bVectorSet)
    {
        delete [] m_psmpX;
        delete [] m_psmpY;
    }
    m_psmpX = new AFSample[m_smpcXLength];
    m_psmpY = new AFSample[m_smpcYLength];

    memset(m_psmpX, 0, m_smpcHLength * sizeof(AFSample));
    memcpy(m_psmpX + m_smpcHLength, v, len * sizeof(AFSample));

    m_bVectorSet = true;

}

void AFConvolver::AdjustVectorHead(const AFSampleCount smpcOldHLength, const AFSampleCount smpcNewHLength)
{
    AFSample *p;
    AFSampleCount smpcSize = m_smpcHLength + m_smpcXLength - smpcOldHLength;

    // Add 'm_smpcHLength' zeros in the vector head
    p = new AFSample[smpcSize];
    
    memset(p, 0, m_smpcHLength * sizeof(AFSample));
    memcpy(p + m_smpcHLength, m_psmpX + smpcOldHLength, (m_smpcXLength - smpcOldHLength) * sizeof(AFSample));
    
    delete [] m_psmpX;

    m_psmpX = p;
    m_smpcXLength += m_smpcHLength - smpcOldHLength;

    // Resizing x mean resizing y too
    m_smpcYLength = m_smpcXLength;
    delete [] m_psmpY;
    m_psmpY = new AFSample[m_smpcYLength];
}

AFSampleCount AFConvolver::BlockSize() const
{
    // Block size must be a power of 2
    AFSampleCount l = 2;
    while( (l *= 2) < m_smpcHLength );
    return l *= 2;
}

AFSample AFConvolver::FindMax(AFSample * v, AFSampleCount len) const
{
    AFSampleCount i = 0;
    AFSample smpMax = 0;
    for(i=0; i < len; i++)
        smpMax = (fabs(v[i]) > smpMax) ? fabs(v[i]) : smpMax;

    return smpMax;
}

void AFConvolver::LoadFilter()
{
    memcpy(m_psmpHt, m_psmpH, m_smpcHLength * sizeof(AFSample));

    //Zeropad if the case...    
    if( m_smpcHLength < m_smpcBlockLength)
	memset(m_psmpHt + m_smpcHLength, 0, (m_smpcBlockLength - m_smpcHLength) * sizeof(AFSample));
}

void AFConvolver::ReverseFilter()
{
   if(!m_psmpH) return;
   AFSample* smpTmp = new AFSample [m_smpcHLength];
   
   for(AFSampleCount i = 0; i < m_smpcHLength; i++)
       smpTmp[i] = m_psmpH[(m_smpcHLength-1) - i];
   
   memcpy(m_psmpH, smpTmp, m_smpcHLength*sizeof(AFSample));
   delete [] smpTmp;
}

AFSampleCount AFConvolver::FindPeakPosition(AFSample* psmpH, const AFSampleCount smpcHLength)
{
    // Finds the main peak position of the IR (filter),
    // needed by the preserve length function.
    m_smpcPeakPosition = 0;
    AFSample smpTmp = 0.0;
#ifdef __AUDEBUG__
    printf("convolver: finding peak...");
#endif
    for(AFSampleCount i = 0; i < smpcHLength; i++)
    {
        if(fabs(psmpH[i]) > smpTmp)
        {
            smpTmp = fabs(psmpH[i]);
            m_smpcPeakPosition = i;
        }
    }
#ifdef __AUDEBUG__
    printf("%ld\n", long(m_smpcPeakPosition));
#endif
    return m_smpcPeakPosition;
}

void AFConvolver::FindFilterPeakPosition()
{
    FindPeakPosition(m_psmpH, m_smpcHLength);
}

void AFConvolver::LoadBlock(const AFSampleCount from, const AFSampleCount to)
{
    AFSampleCount smpcChunkSize = to - from;
    memcpy(m_psmpXt, m_psmpX + from, smpcChunkSize * sizeof(AFSample));
    
    //Zeropad if the case...
    if(smpcChunkSize < m_smpcBlockLength)
        memset(m_psmpXt + smpcChunkSize, 0, (m_smpcBlockLength - smpcChunkSize) * sizeof(AFSample));
}

void AFConvolver::StoreResultBlock(const AFSampleCount from)
{
    AFSampleCount to;

    //Prevents overflow...
    if( (from + m_smpcBlockLength - m_smpcHLength) > m_smpcYLength ) to = m_smpcYLength;
    else to = from + m_smpcBlockLength - m_smpcHLength;

    memcpy(m_psmpY + from, m_psmpYt + m_smpcHLength, (to - from) * sizeof(AFSample));
    
    // First block autorange: finds max on first block (from = 0)
    if(!from) m_smpFbMax = FindMax(m_psmpY, to);
}

void AFConvolver::PreProcess()
{
   if(m_abOpts[AFC_PRE_REVERSE_FILTER])
       ReverseFilter();
}

void AFConvolver::PostProcess()
{
   if( m_abOpts[AFC_POST_AUTORANGE] ||
       m_abOpts[AFC_POST_FB_AUTORANGE] )
       Autorange();
   
   if(m_abOpts[AFC_POST_REMOVE_DC])
       RemoveDC();
   
   if(m_abOpts[AFC_POST_GAIN])
       Gain();
}

bool AFConvolver::Process()
{
   PreProcess();
   if(!Convolve()) return false;
   PostProcess();
   return true;
}

bool AFConvolver::Convolve()
{
	InitProgressMeter();

    // Convolution engine following the overlap & save scheme

    AFSampleCount i  = 0;
    AFSampleCount il = 0;
    AFSampleCount L  = m_smpcBlockLength - m_smpcHLength;

    FFT(m_pcpxHf, m_psmpHt);

    while( i < m_smpcXLength)
    {
        // Overlap & Save loop
        il = ( (i + m_smpcBlockLength) < m_smpcXLength ) ? i + m_smpcBlockLength : m_smpcXLength;

        LoadBlock(i, il); 

        FFT(m_pcpxXf, m_psmpXt);

        BlockConvolve();

        IFFT(m_psmpYt, m_pcpxYf);

        StoreResultBlock(i); // the last 'm_smpcHLength' samples are good!
            
        i += L;

		if(!UpdateProgressMeter(il, m_smpcXLength))
        {
           DestroyProgressMeter();
           return false;
        }
    }
    DestroyProgressMeter();
    
	return true;
}

void AFConvolver::BlockConvolve()
{
    // Convolve a partition of input vectors
    for(AFSampleCount i=0; i < m_smpcFftLength; i++)
    {
        m_pcpxYf[i][0] = (m_pcpxXf[i][0] * m_pcpxHf[i][0] - m_pcpxXf[i][1] * m_pcpxHf[i][1]) * m_smpInvBlockLength;;; //  real part
        m_pcpxYf[i][1] = (m_pcpxXf[i][0] * m_pcpxHf[i][1] + m_pcpxXf[i][1] * m_pcpxHf[i][0]) * m_smpInvBlockLength;;; //  imaginary part
    }
}

void AFConvolver::FFT(fftwf_complex * Vf, AFSample *vt)
{
    fftwf_execute_dft_r2c(m_fftwForwardPlan, vt, Vf);
}

void AFConvolver::IFFT(AFSample * vt, fftwf_complex * Vf)
{
    fftwf_execute_dft_c2r(m_fftwBackwardPlan, Vf, vt);
}

void AFConvolver::Gain(AFSample *v, AFSampleCount len)
{
    AFSample g = pow(10.0, m_smpGain/20.0);
    for(AFSampleCount i=0; i < len; i++) v[i] *= g;
}


void AFConvolver::Autorange(AFSample *v, AFSampleCount len, const bool bFirstBlockAR)
{
#ifdef __AUDEBUG__
    printf("Doing simple autorange\n"); fflush(stdout);
#endif    
    // Normalize (deafult -6 dB FS) 
    AFSample smpInvMax = (bFirstBlockAR) ? 1/(2.0*m_smpFbMax)
                                         : 1/(2.0*FindMax(v, len));

    for(AFSampleCount i=0; i < len; i++) v[i] *= smpInvMax;
    m_smpGain = dB20(smpInvMax);
#ifdef __AUDEBUG__
    printf("Applied gain of: %f dB\n", m_smpGain); fflush(stdout);
#endif
}

void AFConvolver::RemoveDC(AFSample *v, AFSampleCount len)
{
    AFSampleCount i;
    AFSample dc = 0.0;

    // First step: find DC component (vector average)
    for(i=0; i < len; i++) dc += v[i];
    //printf("DC comp: %3.4f ->", dc); //****DEBUG
    dc /= len;
    //printf(" %3.4f\n", dc);
    // Second step: remove effectively DC component
    for(i=0; i < len; i++) v[i] -= dc;
}

void AFConvolver::PreserveLength(AFSample* psmpV, const AFSampleCount smpcVLength, const AFSampleCount smpcHLength, const AFSampleCount smpcPeakPosition)
{
    // Basically, we can translate back the
    // result vector of the same retard
    // introduced by the filtering operation.
    // The position of the IR main peak gives
    // the retard length. We can also discard
    // the last (m_smpcHLength - m_smpcPeakPosition)
    // samples.
#ifdef __AUDEBUG__
    printf("convolver: preserving length...");
#endif
    if(smpcPeakPosition == 0) return;
    for(AFSampleCount i=0; i < (smpcVLength - smpcHLength); i++)
        psmpV[i] = psmpV[i + smpcPeakPosition];
    
    memset(psmpV + (smpcVLength - smpcHLength), 0, smpcHLength * sizeof(AFSample));
#ifdef __AUDEBUG__
    printf("done\n");
#endif
}


void AFConvolver::PreserveOutputLength()
{
    PreserveLength(m_psmpY, m_smpcYLength, m_smpcHLength, m_smpcPeakPosition);
}

void AFConvolver::Gain()
{
    Gain(m_psmpY, m_smpcXLength);
}

void AFConvolver::Autorange()
{
    Autorange(m_psmpY, m_smpcXLength, m_abOpts[AFC_POST_FB_AUTORANGE]);
}

void AFConvolver::RemoveDC()
{
    RemoveDC(m_psmpY, m_smpcXLength);
}


AFConvolver::AFConvolver()
  : m_smpcBlockLength(0),
    m_smpcXLength(0.0),
    m_smpcHLength(0.0),
    m_smpcYLength(0.0),
    m_bFilterSet(false),
    m_bVectorSet(false),
    m_smpGain(-6.0),      // dB
    m_smpFbMax(0.0),
    m_smpcPeakPosition(0)
{
   memset(m_abOpts, 0, AFC_N_OPTS * sizeof(bool));
}


AFConvolver::AFConvolver(AFSample *vector, AFSample *filter, 
                         const AFSampleCount vlen, const AFSampleCount flen, const int opts)
  : m_smpcBlockLength(0),
    m_smpcXLength(0.0),
    m_smpcHLength(0.0),
    m_smpcYLength(0.0),
    m_bFilterSet(false),
    m_bVectorSet(false),
    m_smpGain(-6.0),      // dB
    m_smpFbMax(0.0),
    m_smpcPeakPosition(0)
{ 
    memset(m_abOpts, 0, AFC_N_OPTS * sizeof(bool));
   
    SetVector(vector, vlen);
    SetFilter(filter, flen);
}

AFConvolver::~AFConvolver()
{
    //If some data was istantiated
    // m_smpcBlockLength should be set
    if( m_bVectorSet )
    {
        delete [] m_psmpY;
    }

    if( m_bFilterSet )
    {
        fftwf_free(m_psmpXt);
        fftwf_free(m_psmpHt);
        fftwf_free(m_psmpYt);
        fftwf_free(m_pcpxXf);
        fftwf_free(m_pcpxHf);
        fftwf_free(m_pcpxYf);
    
        fftwf_destroy_plan(m_fftwForwardPlan);
        fftwf_destroy_plan(m_fftwBackwardPlan);
    }
}
