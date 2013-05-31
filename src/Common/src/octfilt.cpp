/******************************
 *
 *  Third Octave Band Filter
 *
 ******************************/

#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <cstring>
#include <vector>

#include <audtypes.h>
#include <commdefs.h>

#include "sigwin.h"
#include "firwin.h"
#include "octfir.h"
#include "octfilt.h"

#include "fir-taps.cpp"
#include "iir-taps.cpp"

#define SCIPY_FILTER
//#define GP_IIR 

#ifdef DUMP_TAPS
void SCFilter::Dump(const int id, const char* tag)
{
    FILE* f;
    int k;
    
    char str[32];
    if(m_adbB != 0)
    {
        sprintf(str, "/tmp/%s_%d", tag, id);
        std::cout << "Dumping FIR taps " << id << " to " << str << std::endl;
        if((f = fopen(str, "w")) != 0)
        {
            k = 0;
            
            while(k < m_nOrder)
            {
                fprintf(f, "%.18e\n", m_adbB[k++]);
            }
            fclose(f);
        }
    }
}
#endif

#ifdef GP_IIR

void SCFilter::IIR(AFSample* yt, AFSample* xt, const AFSampleCount length)
{    
    AFSample* y = yt;
    AFSample* x = xt;
    AFSample* x_ptr;
    AFSample* y_ptr;
    
    int i ,k;
    
    for(i = 0; i < m_nOrder; i++)
    {
        x_ptr = x;
        y_ptr = y;
        
        *y = m_adbB[0] * *x;
        
        for(k = 1; k <= i; k++)
        {
            x_ptr--, y_ptr--;
            *y += m_adbB[k] * *x_ptr - m_adbA[k] * *y_ptr;
        }
        x++;
        y++;
    }
    
    for(i = 0; i < int(length - m_nOrder); i++)
    {
        x_ptr = x;
        y_ptr = y;
        
        *y = m_adbB[0] * *x;
   
        for(k = 1; k < m_nOrder; k++)
        {
            x_ptr--; y_ptr--;
            *y += m_adbB[k] * *x_ptr - m_adbA[k] * *y_ptr;     // x[i-k]
        }
        x++;
        y++;
    } 
}

#elif defined SCIPY_FILTER
void SCFilter::IIR(AFSample* yt, AFSample* xt, const AFSampleCount length)
{   
    // Direct Form II
    AFSample *ptr_x = xt, *ptr_y = yt;
    AFSample *ptr_Z, *ptr_b;
    AFSample *ptr_a;
    AFSample *xn, *yn;
    const AFSample a0 = m_adbA[0];
    int n;
    AFSampleCount k;

    AFSample* Z = new AFSample [m_nOrder];
    memset(Z, 0, sizeof(AFSample)*m_nOrder);
    
    for (k = 0; k < length; k++) 
    {
        ptr_b = m_adbB;   /* Reset a and b pointers */
        ptr_a = m_adbA;
        xn = ptr_x;
        yn = ptr_y;
        if (m_nOrder > 1) 
        {
            ptr_Z = Z;
            *yn = *ptr_Z + *ptr_b / a0 * *xn;   /* Calculate first delay (output) */
            ptr_b++;
            ptr_a++;
            /* Fill in middle delays */
            for (n = 0; n < m_nOrder - 2; n++) 
            {
                *ptr_Z =
                    ptr_Z[1] + *xn * (*ptr_b / a0) - *yn * (*ptr_a / a0);
                ptr_b++;
                ptr_a++;
                ptr_Z++;
            }
            /* Calculate last delay */
            *ptr_Z = *xn * (*ptr_b / a0) - *yn * (*ptr_a / a0);
        } 
        else 
        {
            *yn = *xn * (*ptr_b / a0);
        }

        ptr_y += 1;      /* Move to next input/output point */
        ptr_x += 1;
    }    
    delete [] Z;
}

#endif

#if defined SCIPY_FILTER
void SCFilter::FIR(AFSample* yt, AFSample* xt, const AFSampleCount length)
{    
    // Direct Form II
    AFSample *ptr_x = xt, *ptr_y = yt;
    AFSample *ptr_Z, *ptr_b;
    AFSample *xn, *yn;
    int n;
    AFSampleCount k;

    AFSample* Z = new AFSample [m_nOrder];
    memset(Z, 0, sizeof(AFSample)*m_nOrder);
    
    for (k = 0; k < length; k++) 
    {
        ptr_b = m_adbB;   /* Reset a and b pointers */
        xn = ptr_x;
        yn = ptr_y;
        if (m_nOrder > 1) 
        {
            ptr_Z = Z;
            *yn = *ptr_Z + *ptr_b * *xn;   /* Calculate first delay (output) */
            ptr_b++;
            /* Fill in middle delays */
            for (n = 0; n < m_nOrder - 2; n++) 
            {
                *ptr_Z = ptr_Z[1] + *xn * (*ptr_b);
                ptr_b++;
                ptr_Z++;
            }
            /* Calculate last delay */
            *ptr_Z = *xn * (*ptr_b);
        } 
        else 
        {
            *yn = *xn * (*ptr_b);
        }

        ptr_y += 1;      /* Move to next input/output point */
        ptr_x += 1;
    }    
    delete [] Z;
}

#else

void SCFilter::FIR(AFSample* yt, AFSample* xt, const AFSampleCount length)
{    
    // Generic fir calculation routine...not really optimized yet.
    
    AFSample* y = yt;
    AFSample* x = xt;
    AFSample* x_ptr;

    int i,k;    
    
    for(i = 0; i < m_nOrder; i++)
    {
        x_ptr = x;
        *y    = 0.0;
        
        for(k = 0; k <= i; k++, x_ptr--)
        {
            *y += m_adbB[k] * *x_ptr;
        }
        x++;
        y++;
    }
    
    for(i = 0; i < int(length - m_nOrder); i++)
    {
        x_ptr = x;
        *y    = 0.0;
           
        for(k = 0; k < m_nOrder; k++, x_ptr--)
        {
            *y += m_adbB[k] * *x_ptr;     // x[i-k]
        }
        x++;
        y++;
    } 
}
#endif

bool SCFilter::Apply(AFSample* yt, AFSample* xt, const AFSampleCount length)
{
    if(int(length) < m_nOrder)
        return false;
        
    if(m_adbA == 0)
    {
        FIR(yt, xt, length);    
    }
    else
    {
        IIR(yt, xt, length);        
    }
  
    return true;    
}  

void SCFilter::init(const AFSample* b, const AFSample* a)
{
    if(b != 0)
    {
        m_adbB = new AFSample [m_nOrder];
        memcpy(m_adbB, b, m_nOrder*sizeof(AFSample));
        
        if(a != 0)
        {
            m_adbA = new AFSample [m_nOrder];
            memcpy(m_adbA, a, m_nOrder*sizeof(AFSample));
        }
    }   
    
}

SCFilter::SCFilter(const int    N,
                   double       cutoff,
                   const int    window,
                   const double width,
                   const bool   passZero,
                   const bool   scale,
                   const double fnyq)
: m_nErr(NO_ERR),
  m_dbRate(2.0 * fnyq),
  m_dbFnyq(fnyq),
  m_nOrder(N),
  m_adbB(0),
  m_adbA(0),
  m_bIsFir(true)
{
    SCFirWin fw(N, cutoff, window, width, passZero, scale, fnyq);
    init(fw.Get());
}

SCFilter::SCFilter(const int N,
                   AFSample* b,
                   AFSample* a,
                   const bool   isFir,
                   const double rate)
  : m_nErr(NO_ERR),
    m_dbRate(rate),
    m_dbFnyq(rate/2.0),
    m_nOrder(N),               
    m_adbB(0),
    m_adbA(0),
    m_bIsFir(isFir)
{
    init(b, a);
}

SCFilter::~SCFilter()
{
    if(m_adbB)
    {
        delete [] m_adbB;
        if(m_adbA)
            delete [] m_adbA;
    }

}

// ------------------------------------------------------------------
SCOctaveBandFilterBase::SCOctaveBandFilterBase()
: SCFilter((int)0,(AFSample*)0, (AFSample*)0, true, 0.0),
  m_dbFmExp(0.0)
{}

SCOctaveBandFilterBase::SCOctaveBandFilterBase(const double rate,
                                               const double fmExp,
                                               const bool   isFir)
  : SCFilter((int)0,(AFSample*)0, (AFSample*)0, (bool)isFir, (double)rate),
    m_dbFmExp(fmExp)
{
   Create(rate, fmExp, isFir);
}

// ------------------------------------------------------------------
void SCOctaveBandFilter::Create(const double rate,
                                const double fmExp,
                                const bool   isFir)
{
	m_dbRate  = rate;
	m_dbFmExp = fmExp;
	m_bIsFir  = isFir;

    SCOctaveBandFirPreset param(m_dbFmExp, m_dbRate, 0, 0);

    if(m_bIsFir)
    {
        if(m_dbRate == 96000.0)
        {
            if(m_dbFmExp == 12.0)
            {
                param.LpN =  65;    param.LpDelta =  0.01;
                param.HpN = 161;    param.HpDelta = 0.005;
            }
            else if (m_dbFmExp == 9.0)
            {
                param.LpN = 115;    param.LpDelta = 0.005;
                param.HpN = 161;    param.HpDelta = 0.005;
            }
            else
            {
                m_nErr = ERR_FM;
                return;
            }
        }
        else if(m_dbRate == 48000.0)
        {
            if(m_dbFmExp == 12.0)
            {
                param.LpN = 69;    param.LpDelta = 0.01;
                param.HpN = 89;    param.HpDelta = 0.01;
            }
            else if (m_dbFmExp == 9.0)
            {
                param.LpN = 69;    param.LpDelta = 0.01;
                param.HpN = 89;    param.HpDelta = 0.01;
            }
            else
            {
                m_nErr = ERR_FM;
                return;
            }
        }
        else if(m_dbRate == 44100.0)
        {
            if(m_dbFmExp == 12.0)
            {
                param.LpN = 55;    param.LpDelta = -0.03;
                param.HpN = 89;    param.HpDelta =  0.01;
            }
            else if (m_dbFmExp == 9.0)
            {
                param.LpN = 55;    param.LpDelta = 0.01;
                param.HpN = 89;    param.HpDelta = 0.01;
            }
            else
            {
                m_nErr = ERR_FM;
                return;
            }
        }
        else
        {
            m_nErr = ERR_RATE;
            return;
        }
    }
    else
    {
		m_nErr = ERR_NOT_IMPL;
		return;

	    const AFSample* a_ptr = 0;
	    const AFSample* b_ptr = 0;
	    AFSampleCount L = 0;

	    m_nOrder = int(L) / sizeof(AFSample);
	    SCFilter::init(b_ptr, a_ptr);
    }

    SCOctaveBandFir obf(param);
    if(!obf.IsOk())
    {
        m_nErr = ERR_CREATING_FILTER;
        return;
    }
    m_nOrder = obf.GetOrder();
    SCFilter::init(obf.Get());
}

SCOctaveBandFilter::SCOctaveBandFilter()
: SCOctaveBandFilterBase()
{}

SCOctaveBandFilter::SCOctaveBandFilter(const double rate,
                                       const double fmExp,
                                       const bool   isFir)
: SCOctaveBandFilterBase(rate, fmExp, isFir)
{}

// ------------------------------------------------------------------
void SCThirdOctaveBandFilter::Create(const double rate,
                                     const double fmExp,
                                     const bool   isFir)
{
	m_dbRate  = rate;
	m_dbFmExp = fmExp;
	m_bIsFir  = isFir;

    SCOctaveBandFirPreset param(m_dbFmExp, m_dbRate, 0, 0);
    param.OctaveFraction = 3.0;

    if(m_bIsFir)
    {
        if(m_dbRate == 96000.0)
        {
            if(m_dbFmExp == 13.0)
            {
                param.LpN = 111;    param.LpDelta = 0.01;
                param.HpN = 131;    param.HpDelta = 0.007;
            }
            else // 12.0, 11.0, 10.0
            {
                param.LpN = 171;    param.LpDelta = 0.006;
                param.HpN = 201;    param.HpDelta = 0.005;
            }
        }
        else if(m_dbRate == 48000.0)
        {
            if(m_dbFmExp == 13.0)
            {
                param.LpN =  71;    param.LpDelta = 0.01;
                param.HpN = 111;    param.HpDelta = 0.01;
            }
            else // 12.0, 11.0, 10.0
            {
                param.LpN = 121;    param.LpDelta = 0.005;
                param.HpN = 177;    param.HpDelta = 0.005;
            }
        }
        else if(m_dbRate == 44100.0)
        {
            if(m_dbFmExp == 13.0)
            {
                param.LpN =  81;    param.LpDelta = -0.02;
                param.HpN = 121;    param.HpDelta =  0.005;
            }
            else // 12.0, 11.0, 10.0
            {
                param.LpN = 105;    param.LpDelta = 0.01;
                param.HpN = 167;    param.HpDelta = 0.005;
            }
        }
        else
        {
            m_nErr = ERR_RATE;
            return;
        }
    }
    else
    {
        m_nErr = ERR_NOT_IMPL;
        return;

        const AFSample* a_ptr = 0;
        const AFSample* b_ptr = 0;
        AFSampleCount L = 0;

        m_nOrder = int(L) / sizeof(AFSample);
        SCFilter::init(b_ptr, a_ptr);
    }

    SCOctaveBandFir obf(param);
    if(!obf.IsOk())
    {
        m_nErr = ERR_CREATING_FILTER;
        return;
    }
    m_nOrder = obf.GetOrder();
    SCFilter::init(obf.Get());
}

SCThirdOctaveBandFilter::SCThirdOctaveBandFilter()
: SCOctaveBandFilterBase()
{}

SCThirdOctaveBandFilter::SCThirdOctaveBandFilter(const double rate, 
                                                 const double fmExp,
                                                 const bool   isFir)
  : SCOctaveBandFilterBase(rate, fmExp, isFir)
{}

