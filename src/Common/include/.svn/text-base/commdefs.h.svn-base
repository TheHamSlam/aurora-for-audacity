/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  commdefs.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_COMMDEFS_H__
#define __AURORA_COMMDEFS_H__


#include "audtypes.h"
#include "version.h"

#define   AURORA_NAME   "Aurora"

#include <assert.h>
#include <math.h>

// ----- from unixsh math.h
#ifndef M_PI
    #define M_PI        3.1415926535897932384626433
#endif
#ifndef M_SQRT2
    #define M_SQRT2     1.41421356237309504880  /* sqrt(2) */
#endif
#ifndef M_SQRT1_2
    #define M_SQRT1_2   0.70710678118654752440  /* 1/sqrt(2) */
#endif
#ifndef M_E
    #define M_E         2.7182818284590452354   /* e */
#endif

// #ifndef TWO_PI
//     #define TWO_PI      6.2831853   /* 2*pi */
// #endif

// ----- custom
#define dB(x)     ((x > 0) ? 10.0*log10(x) : -200.0)
#define dB20(x)   ((x > 0) ? 20.0*log10(x) : -200.0)
#define undB(x)   (pow(10.0, x/10.0))
#define undB20(x) (pow(10.0, x/20.0))
#define dBsum(x,y) (10.0*log10(pow(10.0, x/10.0) + pow(10.0, y/10.0)))

// channels macro
#ifndef CH_LEFT
    #define CH_LEFT 0
#endif

#ifndef CH_RIGHT
    #define CH_RIGHT 1
#endif

// Octave bands enum
enum OctaveBand {  BD_31_5, BD_63, BD_125, BD_250, BD_500,
                   BD_1k,   BD_2k, BD_4k,  BD_8k,  BD_16k,
                   BD_A,    BD_Lin, N_BANDS  };


// these are for fftw_complex vectors
#ifndef __FFTW_REIM__
#define __FFTW_REIM__
    #define Re(c) c[0]         // real part of c fftw[f]_complex
    #define Im(c) c[1]         // imag part of c fftw[f]_complex
    #define Mod(c)    sqrt(c[0]*c[0] + c[1]*c[1]) // Module, where 'c' is a fftw[f]_complex
    #define SqrMod(c)     (c[0]*c[0] + c[1]*c[1])  // Square module, where 'c' is a fftw[f]_complex
    #define Magnitude(c)    sqrt(c[0]*c[0] + c[1]*c[1])  // Magnitude and Mod should be alias.
    #define SqrMagnitude(c)      (c[0]*c[0] + c[1]*c[1])
    #define Phase(c)        (-atan2(c[1], c[0])) 
    #define DegPhase(c)     (-(atan2(c[1], c[0]) * 180) / M_PI)
    #define Mag(c) c[0]
    #define Ph(c)  c[1]
#endif

// useful for rounding to nearest integer
#define iround(d)  ( int((d >= 0) ? floor(d + 0.5) : ceil(d - 0.5)) )
#define afround(d) (AFSampleCount(d + 0.5))
#define unRound(d) (size_t(d + 0.5))


#define __WX_NATIVE_PROG_DLG__ 1

#endif // __AURORA_COMMDEFS_H__
