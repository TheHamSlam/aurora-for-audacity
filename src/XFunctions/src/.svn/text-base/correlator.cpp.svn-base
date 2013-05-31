/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions
  
  correlator.cpp

  Simone Campanini

**********************************************************************/

#include <string.h>

#include "correlator.h"

///////////////////////////////////////////////////
// Correlator class implementation
///////////////////////////////////////////////////

/*
   IPP Perm format of FFT Transform result:
   
   Idx:  0    1      2    3    ... N-2      N-1      [N]
   Perm: R(0) R(N/2) R(1) I(1) ... R(N/2-1) I(N/2-1)
   
   where: R(0) is the DC component (no imag. part)
          R(N/2) is the Nyquist freq. component (no imag. part)
   
*/

#define DC   0
#define fNyq (m_smpcSpectrumLength - 1)

// ------------------------------------------------------------------- Initialization & setup methods ---

void Correlator::InitWindow(const AFSampleCount smpcLength)
{
    m_asmpWindow = new AFSample [m_smpcBlockLength];
    memset(m_asmpWindow, 0, m_smpcBlockLength*sizeof(AFSample));
    
    // Analysis window generation
    AFSampleCount k;
    
    switch(m_nWindowType)
    {

       case  WT_RECTANGULAR:
          for(k = 0; k < smpcLength; k++) m_asmpWindow[k] = 1.0;
          break;
          
       case WT_HANNING:
          for(k = 0; k < smpcLength; k++) m_asmpWindow[k] = ( 0.5 - 0.5 * cos((2.0*M_PI*k)/smpcLength) );
          break;
          
       case WT_BLACKMANN_HARRIS:
          for(k = 0; k < smpcLength; k++) m_asmpWindow[k] = ( (0.35875 - 0.48829 * cos(2.0*M_PI*k/smpcLength)
                                                              + 0.14128 * cos(4.0*M_PI*k/smpcLength)
                                                              - 0.01168 * cos(6.0*M_PI*k/smpcLength)) / 0.35875 );
          break;
          
       case WT_FLAT_TOP:
          for(k = 0;               k < 0.25*smpcLength; k++) m_asmpWindow[k] = sin(2.0*M_PI*k/smpcLength);
          for(k = 0.25*smpcLength; k < 0.75*smpcLength; k++) m_asmpWindow[k] = 1.0;
          for(k = 0.75*smpcLength; k < smpcLength;      k++) m_asmpWindow[k] = m_asmpWindow[smpcLength - k - 1];
          break;
          
       case WT_TRIANGULAR:
          for(k = 0;              k < 0.5*smpcLength; k++) m_asmpWindow[k] = 2.0 * AFSample(k) / AFSample(smpcLength);
          for(k = 0.5*smpcLength; k < smpcLength;     k++) m_asmpWindow[k] = m_asmpWindow[smpcLength - k - 1];
          break;
          
       case WT_HALF_SINE:
          for(k = 0; k < smpcLength; k++) m_asmpWindow[k] = sin(2.0*M_PI*k/smpcLength);
          break;
    }
    //for(k = 0; k < smpcLength; k += 1024) printf("%f ", m_asmpWindow[k]);
    //printf("\n");
    //fflush(stdout);
}

void Correlator::InitInputVector(const int nCh)
{
   DeleteInputVector(nCh);
   m_aasmpIn[nCh] = new AFSample [m_smpcVectorLength];
   memset(m_aasmpIn[nCh], 0, m_smpcVectorLength * sizeof(AFSample));
}

void Correlator::InitInputVectors() 
{
   for(int i = 0; i < CHANNELS_COUNT; i++)
      InitInputVector(i);
}

void Correlator::DeleteInputVector(const int ch) 
{
   if(m_aasmpIn[ch]) delete [] m_aasmpIn[ch];
    m_aasmpIn[ch] = 0;
}

void Correlator::DeleteInputVectors() 
{
   for(int i = 0; i < CHANNELS_COUNT; i++)
      DeleteInputVector(i);
}

void Correlator::InitVectors() 
{
    // Make room for vectors
    m_asmpLeft  = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_asmpRight = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_asmpGll   = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_asmpGrr   = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_asmpGlr   = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_asmpC     = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    m_asmpHx    = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
    
     memset((AFSample *)m_asmpLeft, 0, m_smpcBlockLength * sizeof(AFSample));
     memset((AFSample *)m_asmpRight, 0, m_smpcBlockLength * sizeof(AFSample));
           
    m_acpxLeft  = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    m_acpxRight = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    m_acpxGll   = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    m_acpxGrr   = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    m_acpxGlr   = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    m_acpxC     = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);

    memset((fftwf_complex *)m_acpxLeft,   0, m_smpcFftLength * sizeof(fftwf_complex));
    memset((fftwf_complex *)m_acpxRight,   0, m_smpcFftLength * sizeof(fftwf_complex));
    memset((fftwf_complex *)m_acpxGll, 0, m_smpcFftLength * sizeof(fftwf_complex));
    memset((fftwf_complex *)m_acpxGrr, 0, m_smpcFftLength * sizeof(fftwf_complex));
    memset((fftwf_complex *)m_acpxGlr, 0, m_smpcFftLength * sizeof(fftwf_complex));
    memset((fftwf_complex *)m_acpxC,   0, m_smpcFftLength * sizeof(fftwf_complex));

    if(m_nXFnTypeId == XFT_CROSS_POWER)
    {
       m_asmpWlr = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
       m_acpxWlr = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
       memset((fftwf_complex *)m_acpxWlr, 0, m_smpcFftLength * sizeof(fftwf_complex));

    }

    if(m_abOptions[X_SQUARED_HILBERT_TRANSFORM])
    {
       //  printf("Hilbert on (%x)\n", options);
       m_aasmpHilbert[CH_LEFT] = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
       m_aacpxHilbert[CH_LEFT] = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    
       if(m_nXFnTypeId == XFT_AUTO_CORRELATION)
       {
           m_aasmpHilbert[CH_RIGHT] = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
           m_aacpxHilbert[CH_RIGHT] = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
       }
    }
    
    if(m_nXFnTypeId == XFT_ALPHA)
    {
       m_asmpAlpha   = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
       m_acpxAlpha   = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
    }
    
    if(m_abOptions[X_DIRAC_PULSE] || (m_nXFnTypeId == XFT_ALPHA))
    {
      m_asmpDelta   = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
      m_acpxDelta   = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
      
      memset((AFSample *)m_asmpDelta, 0, m_smpcBlockLength * sizeof(AFSample));
      m_asmpDelta[0] = 1.0; // Dirac pulse at time 0.
    }

   if( (m_nXFnTypeId ==  XFT_TF_H1) ||
       (m_nXFnTypeId ==  XFT_TF_H2) ||
       (m_nXFnTypeId ==  XFT_TF_H3) )
   {
           m_asmpHx = (AFSample *) fftwf_malloc(sizeof(AFSample) * m_smpcBlockLength);
           m_acpxHx = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * m_smpcFftLength);
   }
   
   // Init fftw plans
    m_fftplanForward  = fftwf_plan_dft_r2c_1d(m_smpcFftLength, m_asmpLeft, m_acpxLeft, FFTW_ESTIMATE);
    m_fftplanBackward = fftwf_plan_dft_c2r_1d(m_smpcFftLength, m_acpxRight, m_asmpRight, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
}

void Correlator::DeleteVectors() 
{
    if(m_asmpLeft)  fftwf_free(m_asmpLeft);
    if(m_asmpRight) fftwf_free(m_asmpRight);
    if(m_asmpGll)   fftwf_free(m_asmpGll);
    if(m_asmpGrr)   fftwf_free(m_asmpGrr);
    if(m_asmpGlr)   fftwf_free(m_asmpGlr);
    if(m_asmpC)     fftwf_free(m_asmpC);
    if(m_asmpHx)    fftwf_free(m_asmpHx);
    if(m_asmpDelta) fftwf_free(m_asmpDelta);
    if(m_asmpAlpha) fftwf_free(m_asmpAlpha);
    
    
    if(m_acpxLeft)  fftwf_free(m_acpxLeft);
    if(m_acpxRight) fftwf_free(m_acpxRight);
    if(m_acpxGll)   fftwf_free(m_acpxGll);
    if(m_acpxGrr)   fftwf_free(m_acpxGrr);
    if(m_acpxGlr)   fftwf_free(m_acpxGlr);
    if(m_acpxC)     fftwf_free(m_acpxC);
    if(m_acpxHx)    fftwf_free(m_acpxHx);
    if(m_acpxDelta) fftwf_free(m_acpxDelta);
    if(m_acpxAlpha) fftwf_free(m_acpxAlpha);

    
    if(m_nXFnTypeId == XFT_CROSS_POWER)
    {
       if(m_asmpWlr) fftwf_free(m_asmpWlr);
       if(m_acpxWlr) fftwf_free(m_acpxWlr);
    }
    
    if(m_abOptions[X_SQUARED_HILBERT_TRANSFORM])
    {
        if(m_aasmpHilbert[CH_LEFT]) fftwf_free(m_aasmpHilbert[CH_LEFT]);
        if(m_aacpxHilbert[CH_LEFT]) fftwf_free(m_aacpxHilbert[CH_LEFT]);
    
       if(m_nXFnTypeId == XFT_AUTO_CORRELATION)
       {
           fftwf_free(m_aasmpHilbert[CH_RIGHT]);
           fftwf_free(m_aacpxHilbert[CH_RIGHT]);
       }
    }
}


// ---------------------------------------------------------------------- Math methods ---
    
void Correlator::ComplexRatio(fftwf_complex& fcpxQ, fftwf_complex& fcpxN, fftwf_complex& fcpxD)
{
    AFSample smpDen = SqrMod(fcpxD) + 1.0E-12;

    Re(fcpxQ) = (Re(fcpxN)*Re(fcpxD) + Im(fcpxN)*Im(fcpxD)) / smpDen;
    Im(fcpxQ) = (Im(fcpxN)*Re(fcpxD) - Re(fcpxN)*Im(fcpxD)) / smpDen;
}

// ---------------------------------------------------------------------- fft methods --

void Correlator::FFT(fftwf_complex* pfcpxOut, AFSample* psmpIn)
{
    fftwf_execute_dft_r2c(m_fftplanForward, psmpIn, pfcpxOut);
}

void Correlator::IFFT(AFSample* psmpOut, fftwf_complex* pfcpxIn)
{
    fftwf_execute_dft_c2r(m_fftplanBackward, pfcpxIn, psmpOut);
    for(AFSampleCount un = 0; un < m_smpcFftLength; un++)
    	psmpOut[un] /= m_smpcFftLength;
}


// ---------------------------------------------------------------------- Vector ops methods --

AFSample Correlator::FindModMax(fftwf_complex* pfcpxIn)
{
    AFSample smpMod = 0.0;
    AFSample smpMax = 0.0;
    for(AFSampleCount i = 0; i < m_smpcFftLength; i++)
    {
    	smpMod = Mod(pfcpxIn[i]);
    	smpMax = smpMod > smpMax ? smpMod : smpMax;
    }
    return smpMax;
}

AFSample Correlator::SquareRms(AFSample* psmpU, AFSample* psmpW, AFSampleCount smpcLength)
{
    // Calculates RMS or "cross" RMS value,
    AFSample smpRms = 0.0;
    for(AFSampleCount i = 0; i < smpcLength; i++)
    	smpRms += psmpU[i]*psmpW[i];

    return smpRms / AFSample(smpcLength);
}

AFSampleCount Correlator::FindImax(const fftwf_complex* pfcpxX)
{
   AFSampleCount smpcMaxIdx = 0;
   AFSample smpSqMod = 0.0, smpMax = 0.0;
    
   for(AFSampleCount i = 0; i < m_smpcFftLength; i++)
   {
	   smpSqMod = SqrMod(pfcpxX[i]);
      if(smpSqMod > smpMax) { smpMax = smpSqMod; smpcMaxIdx = i; }
   }
   return smpcMaxIdx;
}
    

void Correlator::FindMax(const AFSample* psmpIn, const AFSampleCount smpcLength, AFSample* psmpMax, AFSampleCount* psmpcMaxIdx)
{
    AFSample      smpTmpMax = 0.0;
    AFSampleCount smpcTmpMaxIdx = 0;
        
    for(AFSampleCount i = 0; i < smpcLength; i++)
    {
        if( fabs(psmpIn[i]) > smpTmpMax)
        {
        	smpTmpMax     = fabs(psmpIn[i]);
            smpcTmpMaxIdx = i;
        }
    }    
    // il valore di Xmax viene cambiato solo se XM ne è maggiore
    // mentre quello di MaxPos viene cambiato in ogni caso
    if( smpTmpMax > *psmpMax)
    	*psmpMax = smpTmpMax;

    if(psmpcMaxIdx)
    	*psmpcMaxIdx = smpcTmpMaxIdx;
}

void Correlator::RemoveDC(AFSample* psmpIn, AFSampleCount smpcLength)
{
    AFSampleCount i;
    AFSample smpDC = 0.0;

    for(i = 0; i < smpcLength; i++)
    	smpDC += psmpIn[i];

    smpDC /= AFSample(smpcLength);

    // Remove DC
    for(i = 0; i < smpcLength; i++)
    	psmpIn[i] -= smpDC;
}

void Correlator::Normalize(AFSample* psmpIn, AFSample smpMax, AFSampleCount smpcLength)
{
    for(AFSampleCount k = 0; k < smpcLength; k++)
    	psmpIn[k] /= smpMax;
}

void Correlator::CircularShift(AFSample* psmpIn, AFSampleCount smpcHalfLength)
{
    //It swaps the two halfs of a vector
    AFSample smpTmp;

    for(AFSampleCount i = 0; i < smpcHalfLength; i++)
    {
       smpTmp = psmpIn[i];
       psmpIn[i] = psmpIn[smpcHalfLength + i];
       psmpIn[smpcHalfLength + i] = smpTmp;
    }
} 
       
double Correlator::Delay(const AFSampleCount smpcMaxIdx)
{
    // Delay from the origin calculation
    AFSampleCount smpcTimeSpan;

    if( !m_abOptions[X_SHIFT_TO_HALF_WINDOW] )
    	smpcTimeSpan = m_smpcBlockLength/2;
    else if( smpcMaxIdx < (m_smpcBlockLength/2) )
    	smpcTimeSpan = 0;
    else
    	smpcTimeSpan = m_smpcBlockLength;

    double dbDelay = double(smpcMaxIdx - smpcTimeSpan) /  m_smpRate; // in s

    return ( m_abOptions[X_TIME_REVERSAL]) ? -dbDelay : dbDelay;
}

double Correlator::Trigger(const AFSample* psmpIn)
{
    // Search for trigger value
    AFSample smpTriggerValue = AFSample(0.01 * m_dbTriggerLevel); // maximum is 1.0
    AFSampleCount smpcTriggerPos = 0;

    AFSampleCount i = 0;
    while( (i < m_smpcBlockLength) && ( smpcTriggerPos == 0) )
    {
       if( fabs(psmpIn[i]) > smpTriggerValue )  smpcTriggerPos = i;
       i++;
    }
    //if( m_abOptions[X_SHIFT_TO_HALF_WINDOW]) trigger_pos -= m_smpcBlockLength;
    //m_dbTriggerTime = double(trigger_pos) / m_smpRate; // in s
    return Delay(smpcTriggerPos);
}

// -------------------------------------------------------------- Transformation & filtering methods --


void Correlator::HilbertTransform(fftwf_complex* pfcpxIn, fftwf_complex* pfcpxOut)
{
    // Hilbert transform: H{w} = Im(w) + j*(-Re(w))
    Re(pfcpxOut[DC])   = 0.0;
    Re(pfcpxOut[fNyq]) = 0.0;

    for(AFSampleCount i = 1; i < fNyq; i++) 
    {
       Re(pfcpxOut[i]) =  Im(pfcpxIn[i]);
       Im(pfcpxOut[i]) = -Re(pfcpxIn[i]);
    }
}


void Correlator::HFilter(fftwf_complex* pfcpxN, fftwf_complex* pfcpxD)
{
    // Mette in pfcpxH il rapporto complesso fra gli spettri di pfcpxU ed pfcpxW
    Re(m_acpxHx[DC]) = Re(pfcpxN[DC]) /
                       (Re(pfcpxD[DC]) + AFSample(1.0E-12)); //DC
                 
    Re(m_acpxHx[fNyq]) = Re(pfcpxN[fNyq]) /
                         (Re(pfcpxD[fNyq]) + AFSample(1.0E-12)); //Nyquist

    for(AFSampleCount i = 1; i < fNyq; i++) 
       ComplexRatio(m_acpxHx[i], pfcpxN[i], pfcpxD[i]);
}

void Correlator::H3Filter(fftwf_complex* pfcpxN, fftwf_complex* pfcpxD)
{
    // Mette in pfcpxH la radice quadrata del rapporto complesso fra gli spettri di pfcpxX ed pfcpxY
    Re(m_acpxHx[DC]) = AFSample( sqrt( Re(pfcpxN[DC]) /
                                  (Re(pfcpxD[DC]) + 1.0E-12) ) ); //DC

    Re(m_acpxHx[fNyq]) = AFSample( sqrt( Re(pfcpxN[fNyq]) /
                                    (Re(pfcpxD[fNyq]) + 1.0E-12) ) ); //Nyquist

    for(AFSampleCount i = 1; i < fNyq; i++)
    {   
       Re(m_acpxHx[i]) = AFSample( sqrt(Re(pfcpxN[i])/(Re(pfcpxD[i]) + 1.0E-12)) );
       Im(m_acpxHx[i]) = 0.0;  // imaginary part, always 0!
    }
}

// ---------------------------------------------------------------------- Signal generation methods --

void Correlator::Dirac()
{
   // Mette in Out una delta di Dirac finestrata
   double f = 0;

   Re(m_acpxDelta[DC])   = 1.0; // DC
   Re(m_acpxDelta[fNyq]) = 1.0;// Fnyq

   for(AFSampleCount i = 1; i < fNyq; i++) 
   {   
      f = m_smpRate*double(i)/m_smpcFftLength;
      
      if( (f < 24.0) || (f > m_dbFmax) )
      {
         Re(m_acpxDelta[i]) = 0.0;
         Im(m_acpxDelta[i]) = 0.0;
      } 
      else 
      {
         Re(m_acpxDelta[i]) = 1.0;
         Im(m_acpxDelta[i]) = 0.0;
      }
   }
}

// ------------------------------------------------------------ Alpha & PU Probe calibration methods --

void Correlator::Alpha()  
{
   // Calcolo Alpha (normalizzata fra zero e 1)

   AFSample f = 0, k = 0;
   AFSample d = AFSample(m_dbMicsDistance/1000.0); // d è in mm, x è in metri
   AFSample Zr = 0, Zi = 0;
   AFSample Rr = 0, Ri = 0;

   Re(m_acpxAlpha[DC])   = 0.0;// DC
   Re(m_acpxAlpha[fNyq]) = 0.0;// Fnyq

   for(AFSampleCount i = 1; i < fNyq; i++)
   {   
      f = m_smpRate*i/AFSample(m_smpcFftLength);
      k = 2.0*M_PI*f/m_dbSoundSpeed;

      Zr = -Re(m_acpxGlr[i])/(Re(m_acpxGrr[i]) + 1E-12);  // pv/vv = p/v
      Zi = -Im(m_acpxGlr[i])/(Re(m_acpxGrr[i]) + 1E-12);

      Rr = ( cos(2.0*k*d) * (Zr*Zr + Zi*Zi - 1) - 2.0*sin(2*k*d)*Zi ) / (Zr*Zr + Zi*Zi + 1 + 2*Zr);
      Ri = ( sin(2.0*k*d) * (Zr*Zr + Zi*Zi - 1) + 2.0*cos(2*k*d)*Zi ) / (Zr*Zr + Zi*Zi + 1 + 2*Zr);

      Re(m_acpxAlpha[i]) = AFSample( (1 - Rr*Rr - Ri*Ri) / (1 + Rr*Rr + Ri*Ri - 2*Rr) );
      Im(m_acpxAlpha[i]) = AFSample( 2.0*Ri / (1 + Rr*Rr + Ri*Ri - 2*Rr) );
   }
}

void Correlator::PUCalibrationSWTube() 
{
   // Mette in Out il rapporto complesso fra gli spettri di Glr e Grr, e moltiplica per [0,tan(2*pi*f*d/c)]
   AFSample f= 0.0, k = 0.0;
   AFSample d = AFSample(m_dbMicsDistance/1000.0); // d in metri
   
   Re(m_acpxAlpha[DC])   = 0.0;// DC
   Re(m_acpxAlpha[fNyq]) = 0.0;// Fnyq
   
   for(AFSampleCount i = 1; i < fNyq; i++)
   {
      f = m_smpRate * i/AFSample(m_smpcFftLength);

      if( (f < 24.0) || (f > m_dbFmax) )
      {
         Re(m_acpxAlpha[i]) = 0.0;
         Im(m_acpxAlpha[i]) = 0.0;
      } 
      else 
      {
         k = AFSample( tan( 2.0*M_PI*m_smpRate*d/m_dbSoundSpeed * i/(1.0*m_smpcFftLength) ) );
         Re(m_acpxAlpha[i]) = AFSample( Im(m_acpxGlr[i])/(Re(m_acpxGrr[i]) + 1.0E-12) * k);
         Im(m_acpxAlpha[i]) = AFSample( Re(m_acpxGlr[i])/(Re(m_acpxGrr[i]) + 1.0E-12) * k);
      }
   }
}

void Correlator::PUCalibrationFreeField() 
{
   // Mette in Out il rapporto complesso fra gli spettri di Glr e Grr, e divide per [1+1/jkd]
   AFSample f= 0.0, k = 0.0;
   AFSample d = AFSample(m_dbMicsDistance/1000.0); // d in metri
   
   Re(m_acpxAlpha[DC])   = 0.0;// DC
   Re(m_acpxAlpha[fNyq]) = 0.0;// Fnyq
   
   for(AFSampleCount i = 1; i < fNyq; i++)
   {
      f = AFSample(m_smpRate * i/AFSample(m_smpcFftLength));

      if( (f < 24.0) || (f > m_dbFmax) )
      {
         Re(m_acpxAlpha[i]) = 0.0;
         Im(m_acpxAlpha[i]) = 0.0;
      } 
      else 
      {
         k = AFSample( 2.0*M_PI*m_smpRate* d/m_dbSoundSpeed * i/AFSample(m_smpcFftLength) );
         Re(m_acpxAlpha[i]) = AFSample( Re(m_acpxGlr[i])/Re(m_acpxGrr[i]) + Im(m_acpxGlr[i])/Re(m_acpxGrr[i]) / k);
         Im(m_acpxAlpha[i]) = AFSample( Im(m_acpxGlr[i])/Re(m_acpxGrr[i]) - Re(m_acpxGlr[i])/Re(m_acpxGrr[i]) / k);
      }
   }
}

// ---------------------------------------------------------------------- Correlation methods ---

void Correlator::AutoSpectrum(fftwf_complex* pcpxOut, fftwf_complex* pfcpxIn, AFSampleCount smpcCurrentBlock)
{
    // It applies Welch's method
    //  https://ccrma.stanford.edu/~jos/sasp/Welch_s_Method.html#sec:pwelch
    AFSampleCount i;
    AFSample smpNorm  = AFSample(smpcCurrentBlock);
    AFSample smpDNorm = AFSample(smpcCurrentBlock + 1);
    
    if (m_smpcLowerBound == 0)
    {
       Re(pcpxOut[DC])   = ( Re(pcpxOut[DC]) * smpNorm +
                             Re(pfcpxIn[DC]) * Re(pfcpxIn[DC]) ) / smpDNorm;

       Re(pcpxOut[fNyq]) = ( Re(pcpxOut[fNyq]) * smpNorm +
                            Re(pfcpxIn[fNyq]) * Re(pfcpxIn[fNyq]) ) / smpDNorm;
    }
    for(i = 1; i < (m_smpcLowerBound + 1); i++)
    {   
       Re(pcpxOut[i]) = (Re(pcpxOut[i]) * smpNorm) / smpDNorm;    //Real
       Im(pcpxOut[i]) = 0.0;  //Imag. always 0 in the auto-spectrum
    }
    for(i = (m_smpcLowerBound + 1); i < m_smpcHigherBound; i++)
    {   
       // pcpxOut = pfcpxIn * conj(pfcpxIn)
       Re(pcpxOut[i]) = (Re(pcpxOut[i]) * smpNorm +  Re(pfcpxIn[i])*Re(pfcpxIn[i]) + Im(pfcpxIn[i])*Im(pfcpxIn[i])) / smpDNorm; //Real
       Im(pcpxOut[i])  = 0.0;  //Imag. always 0 in the auto-spectrum
    }

    for(i = m_smpcHigherBound; i < fNyq; i++)
    {  
       Re(pcpxOut[i]) = (Re(pcpxOut[i]) * smpNorm) / smpDNorm;    //Real
       Im(pcpxOut[i]) = 0.0;  //Imag. always 0 in the auto-spectrum
    }
}

void Correlator::CrossSpectrum(AFSampleCount smpcCurrentBlock)
{
    // It applies Welch's method
    //  https://ccrma.stanford.edu/~jos/sasp/Welch_s_Method.html#sec:pwelch
    AFSampleCount i;
    AFSample smpNorm  = AFSample(smpcCurrentBlock);
    AFSample smpDNorm = AFSample(smpcCurrentBlock + 1);
    
    if(m_smpcLowerBound == 0)
    {
       Re(m_acpxGlr[DC]) = ( Re(m_acpxGlr[DC]) * smpNorm +
                             Re(m_acpxLeft[DC]) * Re(m_acpxRight[DC]) ) / smpDNorm;

       Re(m_acpxGlr[fNyq]) = ( Re(m_acpxGlr[fNyq]) * smpNorm +
                               Re(m_acpxLeft[fNyq]) * Re(m_acpxRight[fNyq]) ) / smpDNorm;
    }
    for(i = 1; i < (m_smpcLowerBound + 1); i++)
    { 
       Re(m_acpxGlr[i]) = (Re(m_acpxGlr[i]) * smpNorm) / smpDNorm;    //Real
       Im(m_acpxGlr[i]) = (Im(m_acpxGlr[i]) * smpNorm) / smpDNorm;    //Imag.
    }
    for(i = (m_smpcLowerBound + 1); i < m_smpcHigherBound; i++)
    {   
       // m_acpxGlr = L * conj(R);
       Re(m_acpxGlr[i])  = (Re(m_acpxGlr[i]) * smpNorm + Re(m_acpxLeft[i])*Re(m_acpxRight[i]) + Im(m_acpxLeft[i])*Im(m_acpxRight[i])) / smpDNorm; //Real
       Im(m_acpxGlr[i])  = (Im(m_acpxGlr[i]) * smpNorm + Im(m_acpxLeft[i])*Re(m_acpxRight[i]) - Re(m_acpxLeft[i])*Im(m_acpxRight[i])) / smpDNorm; //Imag.
    }
    for(i = m_smpcHigherBound; i < fNyq; i++)
    { 
       Re(m_acpxGlr[i]) = (Re(m_acpxGlr[i]) * smpNorm) / smpDNorm;    //Real
       Im(m_acpxGlr[i]) = (Im(m_acpxGlr[i]) * smpNorm) / smpDNorm;    //Imag.
    } 
}
	    
void Correlator::Coherence()
{
    // Calcolo funzione di coerenza (normalizzata fra zero e 1)
    //
    // C_xy = |G_xy|^2 / (G_xx * G_yy)
    // 
    // where G_zz are the cross and auto spectral density
    
    Re(m_acpxC[DC])   = sqrt( SqrMod(m_acpxGlr[DC]) /
                              ( Re(m_acpxGll[DC])*Re(m_acpxGrr[DC]) + 1.0E-12f)  );

    Re(m_acpxC[fNyq]) = sqrt( SqrMod(m_acpxGlr[fNyq]) /
                              ( Re(m_acpxGll[fNyq])*Re(m_acpxGrr[fNyq]) + 1.0E-12f)  );
    
    for(AFSampleCount i = 1; i < fNyq; i++)
    {
       Re(m_acpxC[i]) = sqrt( SqrMod(m_acpxGlr[i]) / (Re(m_acpxGll[i])*Re(m_acpxGrr[i]) + 1.0E-12f) ); // Real
       Im(m_acpxC[i]) = 0.0; // Imag
    }
}

void Correlator::WhitenedCrossSpectrumPhase()
{
    // Calcolo del Whitened cross-spectrum phase (CSP) - Farina/Zanetta

    AFSample smpMod = 0.0;
    AFSample smpModMax = FindModMax(m_acpxGlr);

    for(AFSampleCount i = 1; i < m_smpcSpectrumLength; i++)
    {
    	smpMod = Mod(m_acpxGlr[i]);         // Calculate complex number module

       if( smpMod > (0.01*smpModMax) )   // Tengo solo i 40 dB superiori.....
       {
          Re(m_acpxGlr[i]) /= smpMod;
          Im(m_acpxGlr[i]) /= smpMod;
       }
       else 
       {
          Re(m_acpxGlr[i]) = 0.0;
          Im(m_acpxGlr[i]) = 0.0;
       }
    }
}

void Correlator::CoherenceWeighting(fftwf_complex* pfcpxOut, fftwf_complex* pfcpxIn)
{
    // It weights first spectrum with the second one
    AFSample smpSqCoherence = 0.0;

    for(AFSampleCount i = 0; i < m_smpcSpectrumLength; i++)
    {
    	smpSqCoherence = Re(pfcpxIn[i]) * Re(pfcpxIn[i]);
        Re(pfcpxOut[i]) *= smpSqCoherence;
        Im(pfcpxOut[i]) *= smpSqCoherence;
    }
}

void Correlator::CrossPowerSpectrumPhase(AFSampleCount smpcCurrentBlock)
{
    AFSampleCount i;

    AFSample smpDen, smpRe, smpIm;
    AFSample smpNorm  = AFSample(smpcCurrentBlock);
    AFSample smpDNorm = AFSample(smpcCurrentBlock + 1);

    if (m_smpcLowerBound == 0)
    {
       Re(m_acpxWlr[DC])   = Re(m_acpxWlr[DC]) * smpNorm + Re(m_acpxLeft[DC])*Re(m_acpxRight[DC]) / smpDNorm; //DC
       Re(m_acpxWlr[fNyq]) = Re(m_acpxWlr[fNyq]) * smpNorm + (Re(m_acpxLeft[fNyq])*Re(m_acpxRight[fNyq])) / smpDNorm; // Fnyq
    }

    for(i=1; i < (m_smpcLowerBound + 1); i++)
    { 
       Re(m_acpxWlr[i]) = (Re(m_acpxWlr[i])*smpNorm) / smpDNorm;    //Real
       Im(m_acpxWlr[i]) = (Im(m_acpxWlr[i])*smpNorm) / smpDNorm;    //Imag.
    }

    for(i=(m_smpcLowerBound+1); i < m_smpcHigherBound; i++)
    {   
       // re + j*im = Lf * conj(Rf)
       smpRe = Re(m_acpxLeft[i])*Re(m_acpxRight[i]) + Im(m_acpxLeft[i])*Im(m_acpxRight[i]);
       smpIm = Im(m_acpxLeft[i])*Re(m_acpxRight[i]) - Re(m_acpxLeft[i])*Im(m_acpxRight[i]);
       //d  = sqrt(Re(m_acpxLeft[i])*Re(m_acpxLeft[i]) + Im(m_acpxLeft[i])*Im(m_acpxLeft[i])) + sqrt(Re(m_acpxRight[i])*Re(m_acpxRight[i]) - Im(m_acpxRight[i])*Im(m_acpxRight[i]));  // Omologo
       smpDen  = sqrt( smpRe*smpRe + smpIm*smpIm );  // Farina

       Re(m_acpxWlr[i]) = (Re(m_acpxWlr[i])*smpNorm + (smpRe / smpDen)) / smpDNorm; //Real
       Im(m_acpxWlr[i]) = (Im(m_acpxWlr[i])*smpNorm + (smpIm / smpDen)) / smpDNorm; //Imag.
    }

    for(i=m_smpcHigherBound; i < fNyq; i++)
    {
       Re(m_acpxWlr[i]) = (Re(m_acpxWlr[i])*smpNorm) / smpDNorm;    //Real
       Im(m_acpxWlr[i]) = (Im(m_acpxWlr[i])*smpNorm) / smpDNorm;    //Imag.
    }
}

// ---------------------------------------------------------------------- Processing methods ---

bool Correlator::DoCrossCorrelation() 
{
    // Block size:                 m_smpcBlockLength
    // Input vector pointer step:  m_smpcBlockLength / 4;

    // m_smpcBlocksCount = (AFSampleCount)( (vector_length - m_smpcBlockLength) / (m_smpcBlockLength/4) + 1 );
    if( (m_smpcBlocksCount = (m_smpcVectorLength - m_smpcBlockLength) / (m_smpcBlockLength/4) + 1) == 0 )
       return false;
    
#ifdef __WXWINDOWS__
    InitProgressMeter(wxT("Calculating..."));
#else
    InitProgressMeter("Calculating...");
#endif
    
    AFSampleCount i = 0;
    AFSampleCount j = 0;

    // Analysis window calculation. TODO: what happens if m_smpcBlockLength = 1 ???
    InitWindow(m_smpcBlockLength);
    
    for(AFSampleCount smpcBlock = 0; smpcBlock <= m_smpcBlocksCount; smpcBlock++)
    {
        // Check input vectors offset: if the last part is too short...
        if( ((j = smpcBlock * (m_smpcBlockLength/4)) + m_smpcBlockLength) >= m_smpcVectorLength)
        {    
           // ...rebuild a shorter window!
           InitWindow(m_smpcVectorLength - j);
        }
        memset(m_asmpLeft, 0, m_smpcBlockLength * sizeof(AFSample));
        memset(m_asmpRight, 0, m_smpcBlockLength * sizeof(AFSample));
        
        // li estraggo in lt e rt, applicando la finestra
        for (i = 0; (i < m_smpcBlockLength) && (j < m_smpcVectorLength); i++)
        {
           m_asmpLeft[i] = m_aasmpIn[CH_LEFT][j]  * m_asmpWindow[i];
           m_asmpRight[i] = m_aasmpIn[CH_RIGHT][j] * m_asmpWindow[i];
           j++;
        } 
       
        // Ora calcolo le FFT dirette dei dati
        FFT(m_acpxLeft, m_asmpLeft);
        FFT(m_acpxRight, m_asmpRight);
        
        // Set correlation bounds, if the case
        SetBounds();
    
        // Infine calcolo i valori spettrali medi
        AutoSpectrum(m_acpxGll, m_acpxLeft, smpcBlock);
        AutoSpectrum(m_acpxGrr, m_acpxRight, smpcBlock);
        CrossSpectrum(smpcBlock);

        if(m_nXFnTypeId == XFT_CROSS_POWER) // Calcolo Cross-power Spectrum Phase secondo Omologo
           CrossPowerSpectrumPhase(smpcBlock);
    
        // aggiorno il progress meter
        if(!UpdateProgressMeter(smpcBlock + 1, m_smpcBlocksCount + 1))
        {
           DestroyProgressMeter();
           return false;
        }
   }    
    // Calcolo i valori complessivi RMS normalizzati sulla lunghezza totale effettiva
    // e corretti per il tipo di finestra impiegata

    m_adbRMS[CH_LEFT]  = sqrt(SquareRms(m_aasmpIn[CH_LEFT],  m_aasmpIn[CH_LEFT],  m_smpcVectorLength));
    m_adbRMS[CH_RIGHT] = sqrt(SquareRms(m_aasmpIn[CH_RIGHT], m_aasmpIn[CH_RIGHT], m_smpcVectorLength));
    m_adbRMS[CH_CROSS] = SquareRms(m_aasmpIn[CH_LEFT],  m_aasmpIn[CH_RIGHT], m_smpcVectorLength);

    //Now we have: in m_acpxGll and m_acpxGrr the autospectrums of left and right channels,
    //             in m_acpxGlr the cross-spectrum of left and right channels,
    //             in m_adbRMS  the rms values of the input vectors,
    //             in m_acpxWlr the cross-power spectrum phase (if option selected)
                
    DestroyProgressMeter();
    
    return true;
}

void Correlator::PostProcessAutocorrelation()
{
#ifdef __WXWINDOWS__
    InitProgressMeter(wxT("Post-processing Autocorrelation..."));
#else
    InitProgressMeter("Post-processing Autocorrelation...");
#endif

    IFFT(m_asmpGll, m_acpxGll);
    IFFT(m_asmpGll, m_acpxGrr);
    
    // --------------------------------------- Shift to half option
    if(m_abOptions[X_SHIFT_TO_HALF_WINDOW])
    {
        CircularShift(m_asmpGll, m_smpcBlockLength/2);
        CircularShift(m_asmpGrr, m_smpcBlockLength/2);
    }
    // ---------------------------------------- Get Mean Square Power
    // At lag 0, autocorrelation reduces to average power
    //    r_x[0] = 1/N sum_{m=0}^{N-1} |x(m)|^2
    // cfr: https://ccrma.stanford.edu/~jos/mdft/Autocorrelation.html#21254
    AFSample smpGlr_0 = m_asmpGlr[0];  // this should be related with cross (R)MS...
    UpdateProgressMeter(30, 100);

    // --------------------------------------- Hilbert transform option
    if(m_abOptions[X_SQUARED_HILBERT_TRANSFORM])
    {
        HilbertTransform(m_acpxGll, m_aacpxHilbert[CH_LEFT]);
        HilbertTransform(m_acpxGrr, m_aacpxHilbert[CH_RIGHT]);
        
        IFFT(m_aasmpHilbert[CH_LEFT],  m_aacpxHilbert[CH_LEFT]);
        IFFT(m_aasmpHilbert[CH_RIGHT], m_aacpxHilbert[CH_RIGHT]);
    
        if(m_abOptions[X_SHIFT_TO_HALF_WINDOW])
        {
           CircularShift(m_aasmpHilbert[CH_LEFT],  m_smpcBlockLength/2);
           CircularShift(m_aasmpHilbert[CH_RIGHT], m_smpcBlockLength/2);
        }
        
        for(AFSampleCount i = 0; i < m_smpcBlockLength; i++)
        {
           m_asmpGll[i] = m_asmpGll[i]*m_asmpGll[i] + m_aasmpHilbert[CH_LEFT][i]*m_aasmpHilbert[CH_LEFT][i];
           m_asmpGrr[i] = m_asmpGrr[i]*m_asmpGrr[i] + m_aasmpHilbert[CH_RIGHT][i]*m_aasmpHilbert[CH_RIGHT][i];
        }
    }  
    else 
    {    
        RemoveDC(m_asmpGll, m_smpcBlockLength);
        RemoveDC(m_asmpGrr, m_smpcBlockLength);
    }
    UpdateProgressMeter(60, 100);
    
    //---------------------------------------- Searching for maximum values...
    FindMax(m_asmpGll, m_smpcBlockLength, &m_asmpGMax[CH_LEFT],  0);
    FindMax(m_asmpGrr, m_smpcBlockLength, &m_asmpGMax[CH_RIGHT], 0);
    UpdateProgressMeter(80, 100);
    
    // --------------------------------------- Crosscorrelation Max scaling factor
    m_smpGlrMax = (m_adbRMS[CH_CROSS] / m_adbRMS[CH_LEFT] / m_adbRMS[CH_RIGHT]) / smpGlr_0;

    //--------------------------------------------------- ....and finally normalize to calculated values
    Normalize(m_asmpGll, (m_asmpGMax[CH_LEFT] > 0)  ? m_asmpGMax[CH_LEFT] : 1.0,  m_smpcBlockLength);
    Normalize(m_asmpGrr, (m_asmpGMax[CH_RIGHT] > 0) ? m_asmpGMax[CH_RIGHT] : 1.0, m_smpcBlockLength);
    UpdateProgressMeter(100, 100);
    
    DestroyProgressMeter();
}

void Correlator::PostProcessCrossFunction(AFSample* psmpOut, fftwf_complex* pfcpxIn)
{
#ifdef __WXWINDOWS__
    InitProgressMeter(wxT("Post-processing Cross Function..."));
#else
    InitProgressMeter("Post-processing Cross Function...");
#endif

    // --------------------------------------- Coherence calculation
    Coherence();
/*
    printf("Cf:\n");
    for(AFSampleCount k = 0; k < m_smpcSpectrumLength; k += 1000) printf("%f ", Re(m_acpxC[k]));
	printf("\n");
*/
    UpdateProgressMeter(10, 100);
    
    // --------------------------------------- Coherence weighting option
    if(m_abOptions[X_COHERENCE_WEIGHTING])
        CoherenceWeighting(pfcpxIn, m_acpxC);
    
    IFFT(psmpOut, pfcpxIn);   // cross-correlation
    IFFT(m_asmpC, m_acpxC); // coherence
/*
    printf("psmpOut:\n");
    for(AFSampleCount k = 0; k < m_smpcBlockLength; k += 1000) printf("%f ", psmpOut[k]);
	printf("\n");
*/
	UpdateProgressMeter(20, 100);
    
    // --------------------------------------- Shift to half option
    if(m_abOptions[X_SHIFT_TO_HALF_WINDOW])
    {
        CircularShift(psmpOut,  m_smpcBlockLength/2);
        CircularShift(m_asmpC, m_smpcBlockLength/2);
    }
    UpdateProgressMeter(40, 100);
    
    // ---------------------------------------- Get Mean Square Power
    // At lag 0, autocorrelation reduces to average power
    //    r_x[0] = 1/N sum_{m=0}^{N-1} |x(m)|^2
    // cfr: https://ccrma.stanford.edu/~jos/mdft/Autocorrelation.html#21254
    AFSample smpGlr_0 = m_asmpGlr[0];  // this should be related with cross (R)MS...
    
    
    // --------------------------------------- Hilbert transform option
    if(m_abOptions[X_SQUARED_HILBERT_TRANSFORM])
    {
        HilbertTransform(pfcpxIn, m_aacpxHilbert[CH_LEFT]);
        IFFT(m_aasmpHilbert[CH_LEFT], m_aacpxHilbert[CH_LEFT]);

        if(m_abOptions[X_SHIFT_TO_HALF_WINDOW])
           CircularShift(m_aasmpHilbert[CH_LEFT], m_smpcBlockLength/2);

        for(AFSampleCount i = 0; i < m_smpcBlockLength; i++)
           psmpOut[i] = psmpOut[i]*psmpOut[i] + m_aasmpHilbert[CH_LEFT][i]*m_aasmpHilbert[CH_LEFT][i]; // sq. mod.
    } 
    else 
    {    
        RemoveDC(psmpOut, m_smpcBlockLength);
    }
    UpdateProgressMeter(60, 100);
    
    //---------------------------------------- Searching for maximum values...          
    FindMax(psmpOut, m_smpcBlockLength, &m_asmpGMax[CH_CROSSCORRELATION], &m_smpcGMaxIdx);
    FindMax(m_asmpC, m_smpcBlockLength, &m_asmpGMax[CH_COHERENCE], 0);
    
    // --------------------------------------- Crosscorrelation Max scaling factor
    m_smpGlrMax = (m_adbRMS[CH_CROSS] / m_adbRMS[CH_LEFT] / m_adbRMS[CH_RIGHT]) / smpGlr_0;
    UpdateProgressMeter(80, 100);
    
    // --------------------------------------- Cross correlation stuffs...
    if(m_nXFnTypeId == XFT_CROSS_CORRELATION)
    {
        // Delay calculation
        m_dbDelay = Delay(m_smpcGMaxIdx);
    
        // Fly time calculation
        m_dbTriggerTime = Trigger(m_asmpGlr);

        if(m_abOptions[X_NORMALIZE])
        {
           // Normalized correlation:
           //NC = Sumi( A(i)*B(i) ) / Sqrt( Sumi( A(i)*A(i) ) * Sumi( B(i)*B(i) )
           //MaxCC = (Xmax/CC0) * (RMSlr/RMSl/RMSr));
           //Xmax=CC0/RMSlr*RMSl*RMSr;             // visualizzo il valore vero della CC normalizzata [???]
           m_asmpGMax[CH_CROSSCORRELATION] /= m_smpGlrMax;
        }
    }
    UpdateProgressMeter(90, 100);
    
    //---------------------------------------------- ....and finally normalize to calculated values    
    Normalize(psmpOut,  (m_asmpGMax[CH_CROSSCORRELATION] > 0) ? m_asmpGMax[CH_CROSSCORRELATION] : 1.0, m_smpcBlockLength);
    //Normalize(m_asmpC, (m_asmpGMax[CH_COHERENCE] > 0) ? m_asmpGMax[CH_COHERENCE] : 1.0, m_smpcBlockLength);
    UpdateProgressMeter(100, 100);
    
    DestroyProgressMeter();
}


bool Correlator::Process()
{
    // Init vectors
    InitVectors();
    
    // Call to pre-process method
    DoCrossCorrelation();

    //Now we have: in m_acpxGll and m_acpxGrr the autospectrums of left and right channels,
    //             in m_acpxGlr the cross-spectrum of left and right channels,
    //             in m_adbRMS  the rms values of the input vectors,
    //             in m_acpxWlr the cross-power spectrum phase (if option selected)

    printf("lb: %ld, hb: %ld\n", long(m_smpcLowerBound), long(m_smpcHigherBound));

    //  AFSample smpGlr_0 =0.0;  // CC0
    
    switch(m_nXFnTypeId)
    {    
       case XFT_AUTO_CORRELATION:
          PostProcessAutocorrelation();
          m_aotOut[0].SetTrack(m_asmpGll);
          m_aotOut[0].SetType(OutputTrack::AUTO_CORRELATION_L);
          m_aotOut[1].SetTrack(m_asmpGrr);
          m_aotOut[1].SetType(OutputTrack::AUTO_CORRELATION_R);
          mChannelsToExport = 2;
          break;
          
       case XFT_CROSS_CORRELATION:
          PostProcessCrossFunction(m_asmpGlr, m_acpxGlr);
          m_aotOut[0].SetTrack(m_asmpGlr);
          m_aotOut[0].SetType(OutputTrack::CROSS_CORRELATION);
          //m_aotOut[1].SetTrack(m_asmpC);
          //m_aotOut[1].SetType(OutputTrack::COHERENCE);
          break;

       case XFT_WHITE_CORRELATION:
          WhitenedCrossSpectrumPhase();
          PostProcessCrossFunction(m_asmpGlr, m_acpxGlr);
          m_aotOut[0].SetTrack(m_asmpGlr);
          m_aotOut[0].SetType(OutputTrack::WHITE_CORRELATION);
          //m_aotOut[1].SetTrack(m_asmpC);
          //m_aotOut[1].SetType(OutputTrack::COHERENCE);

          break;
          
       case XFT_CROSS_POWER:
          PostProcessCrossFunction(m_asmpWlr, m_acpxWlr);
          m_aotOut[0].SetTrack(m_asmpWlr);
          m_aotOut[0].SetType(OutputTrack::CROSS_POWER);
          //m_aotOut[1].SetTrack(m_asmpC);
          //m_aotOut[1].SetType(OutputTrack::COHERENCE);
          break;
          
       case XFT_TF_H1:
          HFilter(m_acpxGlr, m_acpxGll);                 // now m_acpxHx is filled
          PostProcessCrossFunction(m_asmpHx, m_acpxHx);
          m_aotOut[0].SetTrack(m_asmpHx);
          m_aotOut[0].SetType(OutputTrack::TF_H1);
          //m_aotOut[1].SetTrack(m_asmpC);
          //m_aotOut[1].SetType(OutputTrack::COHERENCE);
          break;

       case XFT_TF_H2:
          HFilter(m_acpxGrr, m_acpxGlr);                 // now m_acpxHx is filled
          PostProcessCrossFunction(m_asmpHx, m_acpxHx);
          m_aotOut[0].SetTrack(m_asmpHx);
          m_aotOut[0].SetType(OutputTrack::TF_H2);
          //m_aotOut[1].SetTrack(m_asmpC);
          //m_aotOut[1].SetType(OutputTrack::COHERENCE);
          break;
          
       case XFT_TF_H3:
          H3Filter(m_acpxGll,m_acpxGrr);                // H3, rapporto fra i moduli degli autospettri
          PostProcessCrossFunction(m_asmpHx, m_acpxHx);
          m_aotOut[0].SetTrack(m_asmpHx);
          m_aotOut[0].SetType(OutputTrack::TF_H3);
          //m_aotOut[1].SetTrack(m_asmpC);
          //m_aotOut[1].SetType(OutputTrack::COHERENCE);
          break;

       case XFT_ALPHA: 
          Coherence();      // Coerenza
          IFFT(m_asmpC,  m_acpxC);
          if(m_bIsFreeField)
          {
             Dirac(); 
             PUCalibrationFreeField(); // 1/H2/(1+1/jkd)
             IFFT(m_asmpDelta, m_acpxDelta);
             IFFT(m_asmpAlpha, m_acpxAlpha);
             RemoveDC(m_asmpDelta, m_smpcBlockLength);
             FindMax(m_asmpDelta, m_smpcBlockLength, &m_asmpGMax[CH_LEFT], 0);
             //m_aotOut[0].SetTrack(m_asmpAlpha);
             //m_aotOut[0].SetType(OutputTrack::PU_CAL_FREE_FIELD);
             m_aotOut[0].SetTrack(m_asmpDelta);
             m_aotOut[0].SetType(OutputTrack::DIRAC_DELTA);
          } 
          else if(m_bIsSwTube)
          {
             Dirac();               // Delta di Dirac canale Left
             PUCalibrationSWTube(); // 1/H2 *tan(kd)
             IFFT(m_asmpDelta, m_acpxDelta);
             IFFT(m_asmpAlpha, m_acpxAlpha);
             RemoveDC(m_asmpDelta, m_smpcBlockLength);
             FindMax(m_asmpDelta, m_smpcBlockLength, &m_asmpGMax[CH_LEFT], 0);
             //m_aotOut[0].SetTrack(m_asmpAlpha);
             //m_aotOut[0].SetType(OutputTrack::PU_CAL_SW_TUBE);
             m_aotOut[0].SetTrack(m_asmpDelta);
             m_aotOut[0].SetType(OutputTrack::DIRAC_DELTA);
          } 
          else 
          {
            Alpha();      // Absorption Coefficient canale left
            IFFT(m_asmpAlpha, m_acpxAlpha);
            RemoveDC(m_asmpAlpha, m_smpcBlockLength);
            FindMax(m_asmpAlpha, m_smpcBlockLength, &m_asmpGMax[CH_LEFT], 0);
            //m_aotOut[0].SetTrack(m_asmpAlpha);
            //m_aotOut[0].SetType(OutputTrack::ALPHA);
            m_aotOut[0].SetTrack(m_asmpDelta);
            m_aotOut[0].SetType(OutputTrack::DIRAC_DELTA);
          }

          // --------------------------------------- Crosscorrelation Max scaling factor
          m_smpGlrMax = m_adbRMS[CH_CROSS] / m_adbRMS[CH_LEFT] / m_adbRMS[CH_RIGHT]; // FIXIT
          
          //m_asmpGMax[CH_CROSSCORRELATION] = 1.0;
          break;
    }    

#ifdef __AUDEBUG__   
    printf("{%f %f %.12f %.12f %f %f }\n", m_smpGlrMax, m_asmpGMax[CH_CROSSCORRELATION], m_asmpGlr[0], m_adbRMS[CH_CROSS], m_adbRMS[CH_LEFT], m_adbRMS[CH_RIGHT]);
#endif
    
    // Convert RMS values in deciBels
    m_adbRMS[CH_LEFT]  = dB20(m_adbRMS[CH_LEFT]);
    m_adbRMS[CH_RIGHT] = dB20(m_adbRMS[CH_RIGHT]);
    m_adbRMS[CH_CROSS] = dB(fabs(m_adbRMS[CH_CROSS]));

    return (m_bIsProcessed = true);
}

// ---------------------------------------------------------------------- set & get methods ---
fftwf_complex* Correlator::GetFunctionSpectrum(const int nXfn, const int nCh)
{
   switch(nXfn)
   {    
      case XFT_AUTO_CORRELATION:          return (nCh == 0) ? m_acpxGll : m_acpxGrr;
      case XFT_CROSS_CORRELATION:         return m_acpxGlr;
      case XFT_WHITE_CORRELATION:         return m_acpxGlr;
      case XFT_CROSS_POWER:               return m_acpxWlr;
      case XFT_TF_H1:
      case XFT_TF_H2:
      case XFT_TF_H3:                     return m_acpxHx;
      case XFT_COHERENCE:                 return m_acpxC;
      case XFT_ALPHA:
      case XFT_PU_CALIBRATION_SW_TUBE:
      case XFT_PU_CALIBRATION_FREE_FIELD: return m_acpxAlpha;
      case XFT_DIRAC_DELTA:               return m_acpxDelta;
   }
   return 0;
}

void Correlator::SetBounds()
{
   if(m_bIsFollowingFilterOn)
   {    
      fftwf_complex *pfcpxX = (m_nFollowChn == CH_LEFT) ? m_acpxLeft : m_acpxRight;
      AFSampleCount iMax = FindImax(pfcpxX);
      double bandFactor = pow(2, m_dbFollowBW/2);

      if( (m_smpcHigherBound = AFSampleCount(iMax*bandFactor)) > m_smpcSpectrumLength)
         m_smpcHigherBound = m_smpcSpectrumLength - 1;
   
      if( (m_smpcLowerBound = AFSampleCount(iMax/bandFactor)) > m_smpcSpectrumLength)
         m_smpcLowerBound = 0;
   } 
   else 
   {
       m_smpcLowerBound  = 0;
       m_smpcHigherBound = m_smpcSpectrumLength - 1;
   }
}

void Correlator::SetInputVectorLength(const AFSampleCount len, const int ch, const bool init)
{
    if(len >m_smpcVectorLength)
        m_smpcVectorLength = len;
    
    if(init) InitInputVector(ch);
}

void Correlator::SetInputVectorsLength(const AFSampleCount len, const bool init)
{
    if(len >m_smpcVectorLength)
        m_smpcVectorLength = len;
    
    if(init) InitInputVectors();
}


void Correlator::GetResultsVector(AFSample* v, const int chn)
{
    //    printf("getting results for channel %d...", chn);
    if(m_bIsProcessed)
      memcpy(v, m_aotOut[chn].GetTrack(), m_smpcBlockLength*sizeof(AFSample));
    //printf(".done.\n");
}

// ---------------------------------------------------------------------------- 'ctors ---

Correlator::Correlator()
  : m_nXFnTypeId(XFT_CROSS_CORRELATION),
    m_smpRate(44100),  mChannelsToExport(1),
    m_abOptions(0),
    m_smpcVectorLength(0),  m_smpcBlockLength(0),
    m_smpcFftLength(16384), m_smpcSpectrumLength(0),
    m_smpcBlocksCount(0),
    m_smpcLowerBound(0),    m_smpcHigherBound(0),
    m_smpcGMaxIdx(0),       m_smpGlrMax(0.0),
    m_dbDelay(0.0),         m_dbTriggerLevel(50.0),
    m_dbTriggerTime(0.0),   m_asmpWindow(0),
    m_asmpLeft(0),  m_asmpRight(0),
    m_asmpGll(0),   m_asmpGrr(0),   m_asmpGlr(0),
    m_acpxLeft(0),  m_acpxRight(0),
    m_acpxGll(0),   m_acpxGrr(0),   m_acpxGlr(0),
    m_asmpC(0),     m_acpxC(0),
    m_asmpHx(0),    m_acpxHx(0),
    m_asmpDelta(0), m_acpxDelta(0),
    m_asmpAlpha(0), m_acpxAlpha(0),
    m_acpxWlr(0),
    m_nWindowType(WT_HANNING),
    m_bIsFollowingFilterOn(false),
    m_nFollowChn(0),       m_dbFollowBW(0.333333),
    m_dbSoundSpeed(343.0), m_dbMicsDistance(40.0), m_dbFmax(1900.0),
    m_bIsFreeField(true),  m_bIsSwTube(false),
    m_bIsProcessed(false)

{
    m_asmpGMax[0] = 0.0; m_asmpGMax[1] = 0.0;
    
    m_abOptions = new bool [OPTIONS_COUNT];
    for(int i = 0; i < OPTIONS_COUNT; i++)
       m_abOptions[i] = false;
           
    m_abOptions[X_NORMALIZE] = true;
    m_abOptions[X_SHIFT_TO_HALF_WINDOW] = true;
    m_abOptions[X_SQUARED_HILBERT_TRANSFORM] = true;
        
    
    // init vectors.
    for(int i = 0; i < CHANNELS_COUNT; i++)
    {    
       m_aasmpIn[i] = 0;
       m_aasmpHilbert[i] = 0;   m_aacpxHilbert[i] = 0;
    }
    
    //Useful for calculations
    m_adbRMS[CH_LEFT]  = 0.0;
    m_adbRMS[CH_RIGHT] = 0.0;
    m_adbRMS[CH_CROSS] = 0.0;

    m_smpcBlockLength = m_smpcFftLength;          // Fft logical size
    m_smpcSpectrumLength = 1 + m_smpcFftLength/2;  //thanks to hermitian simmetry of a real data DFT
    //m_smpcFftLength = (m_smpcBlockLength >> 1) + 1; //???
    
    //Used when following filter is enabled
    m_smpcLowerBound  = 0;
    m_smpcHigherBound = m_smpcSpectrumLength;
    
}

Correlator::~Correlator()
{
    DeleteVectors();    
    DeleteInputVectors();
    
    delete [] m_asmpWindow;
    delete [] m_abOptions;
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


