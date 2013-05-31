/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  audtypes.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_AUDTYPES_H__
#define __AURORA_AUDTYPES_H__

// This files works as wrap between Audacity types definitions
// and Aurora classes

#define _AF_USE_FLOAT_

#ifndef __STAND_ALONE__

   // from Audacity
   #include <Audacity.h>
   #include <SampleFormat.h>
   #include <Sequence.h>
 
   typedef  float         AFSample;     
   typedef  sampleFormat  AFSampleFormat;
   typedef  samplePtr     AFSamplePtr;   
   typedef  sampleCount   AFSampleCount;

#else

   typedef  float         AFSample;
   typedef  float*        AFSamplePtr;
   typedef  unsigned long AFSampleCount;
   
#endif

#include <fftw3.h>

#ifdef _AF_USE_FLOAT_
   typedef fftwf_complex Complex_t;
   typedef fftwf_plan    FftPlan_t;
   #define PLAN_DFT_R2C     fftwf_plan_dft_r2c_1d
   #define PLAN_DFT_C2R     fftwf_plan_dft_c2r_1d
   #define EXEC_DFT_R2C     fftwf_execute_dft_r2c
   #define EXEC_DFT_C2R     fftwf_execute_dft_c2r
   #define DESTROY_DFT_PLAN fftwf_destroy_plan
#else
   typedef  fftw_complex  Complex_t;
   typedef  fftw_plan     FftPlan_t;
   #define PLAN_DFT_R2C     fftw_plan_dft_r2c_1d
   #define PLAN_DFT_C2R     fftw_plan_dft_c2r_1d
   #define EXEC_DFT_R2C     fftw_execute_dft_r2c
   #define EXEC_DFT_C2R     fftw_execute_dft_c2r
   #define DESTROY_DFT_PLAN fftw_destroy_plan
#endif
   
   
#endif // __AURORA_AUDTYPES_H__
