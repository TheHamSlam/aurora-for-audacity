/*************s*********************************************************
 *
 *  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 *                       plugin collection
 *
 *  Common libraries
 *
 *  afcomplex.cpp
 *
 *  Simone Campanini 2011
 *
 **********************************************************************/
#include "afcomplex.h"

// Specialized methods

template<>
AFComplexVector<fftwf_complex, float>& AFComplexVector<fftwf_complex, float>::ToPolar()
{
    assert(!m_bIsPolar);
    /*
     * It overwrites the input vector U with its own polar
     * complex coordinates.
     * Here the fftwf_complex type is reinterpretated from Re,Im, to Mag,Phase
     */
    fftwf_complex cpxTmp;
    
    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)
    {
        Mag(cpxTmp) = Magnitude(m_pcpxUf[i]);
        Ph(cpxTmp)  = -Phase(m_pcpxUf[i]);
        Mag(m_pcpxUf[i]) = Mag(cpxTmp);
        Ph(m_pcpxUf[i])  = Ph(cpxTmp);
    }
    m_bIsPolar = true;
    return *this;
}

template<>
AFComplexVector<fftwf_complex, float>& AFComplexVector<fftwf_complex, float>::ToRectangular()
{
    assert(m_bIsPolar);
    /*
     * It overwrites the complex 'polar' input vector U with its own rectangular
     * complex coordinates.
     * Here the fftwf_complex type is reinterpretated from Re,Im, to Mag,Phase
     */
    
    // Devo verificare se la fase della componente DC o Fnyq è pi greca,
    // o multiplo intero se la fase non è un multiplo intero di 2pi allora
    // la assumo negativa.
    
    //a freq. zero ho solo componente reale
    Im(m_pcpxUf[0]) = 0.0;
    if( (fmodf(Ph(m_pcpxUf[0]), M_PI) > 1.0) && (fmodf(Ph(m_pcpxUf[0]), M_PI) < 3.0) )
        Re(m_pcpxUf[0]) = -Mag(m_pcpxUf[0]); //cioe' se il resto e' non zero,
    else
        Re(m_pcpxUf[0]) = Mag(m_pcpxUf[0]);
    
    //alla freq. di Nyquist, ho solo valore reale, la Fnyq e' il secondo elemento di h e l'ultimo di hpm
    Im(m_pcpxUf[m_smpcLength-1]) = 0.0;
    if( (fmodf(Ph(m_pcpxUf[m_smpcLength-1]), M_PI) > 1.0) && (fmodf(Ph(m_pcpxUf[m_smpcLength-1]), M_PI) < 3.0) )
        Re(m_pcpxUf[m_smpcLength-1]) = -Mag(m_pcpxUf[m_smpcLength-1]); //cioe' se il resto non e' zero,
    else
        Re(m_pcpxUf[m_smpcLength-1]) = Mag(m_pcpxUf[m_smpcLength-1]);
                                      
    fftwf_complex cpxTmp;
                  
    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)   // altre frequenze, conto fino ad L2
    {
        Re(cpxTmp) = Mag(m_pcpxUf[i]) * cosf(Ph(m_pcpxUf[i]));
        Im(cpxTmp) = Mag(m_pcpxUf[i]) * sinf(Ph(m_pcpxUf[i]));
        Re(m_pcpxUf[i]) = Re(cpxTmp);
        Im(m_pcpxUf[i]) = Im(cpxTmp);
    }
    m_bIsPolar = false;
    return *this;
}

template<>
AFComplexVector<fftw_complex, double>& AFComplexVector<fftw_complex, double>::ToPolar()
{
    assert(!m_bIsPolar);
    /*
     * It overwrites the input vector U with its own polar
     * complex coordinates.
     * Here the fftwf_complex type is reinterpretated from Re,Im, to Mag,Phase
     */
    fftw_complex cpxTmp;
    
    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)
    {
        Mag(cpxTmp) = Magnitude(m_pcpxUf[i]);
        Ph(cpxTmp)  = -Phase(m_pcpxUf[i]);
        Mag(m_pcpxUf[i]) = Mag(cpxTmp);
        Ph(m_pcpxUf[i])  = Ph(cpxTmp);
    }
    m_bIsPolar = true;
    return *this;
}

template<>
AFComplexVector<fftw_complex, double>& AFComplexVector<fftw_complex, double>::ToRectangular()
{
    assert(m_bIsPolar);
    /*
     * It overwrites the complex 'polar' input vector U with its own rectangular
     * complex coordinates.
     * Here the fftwf_complex type is reinterpretated from Re,Im, to Mag,Phase
     */
    
    // Devo verificare se la fase della componente DC o Fnyq è pi greca,
    // o multiplo intero se la fase non è un multiplo intero di 2pi allora
    // la assumo negativa.
    
    //a freq. zero ho solo componente reale
    Im(m_pcpxUf[0]) = 0.0;
    if( (fmod(Ph(m_pcpxUf[0]), M_PI) > 1.0) && (fmod(Ph(m_pcpxUf[0]), M_PI) < 3.0) )
        Re(m_pcpxUf[0]) = -Mag(m_pcpxUf[0]); //cioe' se il resto e' non zero,
    else
        Re(m_pcpxUf[0]) = Mag(m_pcpxUf[0]);

    //alla freq. di Nyquist, ho solo valore reale, la Fnyq e' il secondo elemento di h e l'ultimo di hpm
    Im(m_pcpxUf[m_smpcLength-1]) = 0.0;
    if( (fmod(Ph(m_pcpxUf[m_smpcLength-1]), M_PI) > 1.0) && (fmod(Ph(m_pcpxUf[m_smpcLength-1]), M_PI) < 3.0) )
        Re(m_pcpxUf[m_smpcLength-1]) = -Mag(m_pcpxUf[m_smpcLength-1]); //cioe' se il resto non e' zero,
    else
        Re(m_pcpxUf[m_smpcLength-1]) = Mag(m_pcpxUf[m_smpcLength-1]);

    fftw_complex cpxTmp;

    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)   // altre frequenze, conto fino ad L2
    {
        Re(cpxTmp) = Mag(m_pcpxUf[i]) * cos(Ph(m_pcpxUf[i]));
        Im(cpxTmp) = Mag(m_pcpxUf[i]) * sin(Ph(m_pcpxUf[i]));
        Re(m_pcpxUf[i]) = Re(cpxTmp);
        Im(m_pcpxUf[i]) = Im(cpxTmp);
    }
    m_bIsPolar = false;
    return *this;
}


// length setter
template<>
void AFComplexVector<fftwf_complex, float>::SetLength(const AFSampleCount smpcLength)
{
    assert(smpcLength > 0.0);
    
    if(m_smpcLength == 0)
    {
        m_smpcLength = smpcLength;
        if(m_pcpxUf) fftwf_free(m_pcpxUf);
        m_pcpxUf = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * m_smpcLength);
    }
    else
    {
        // create a temporary vector for storing purposes
        fftwf_complex* pcpxTmp = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * m_smpcLength);
        memcpy(pcpxTmp, m_pcpxUf, sizeof(fftwf_complex) * m_smpcLength);
        fftwf_free(m_pcpxUf);
        // enlarge the vector
        m_pcpxUf = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * smpcLength);
        memset(m_pcpxUf, 0, sizeof(fftwf_complex) * smpcLength);
        // copy backup to new vector
        memcpy(m_pcpxUf, pcpxTmp, sizeof(fftwf_complex) * m_smpcLength);
        fftwf_free(pcpxTmp);
        // set new length attribute
        m_smpcLength = smpcLength;
    }
}

template<>
void AFComplexVector<fftw_complex, double>::SetLength(const AFSampleCount smpcLength)
{
    assert(smpcLength > 0);
    
    if(m_smpcLength == 0)
    {
        m_smpcLength = smpcLength;
        if(m_pcpxUf) fftw_free(m_pcpxUf);
        m_pcpxUf = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * m_smpcLength);
    }
    else
    {
        // create a temporary vector for storing purposes
        fftw_complex* pcpxTmp = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * m_smpcLength);
        memcpy(pcpxTmp, m_pcpxUf, sizeof(fftw_complex) * m_smpcLength);
        fftw_free(m_pcpxUf);
        // enlarge the vector
        m_pcpxUf = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * smpcLength);
        memset(m_pcpxUf, 0, sizeof(fftw_complex) * smpcLength);
        // copy backup to new vector
        memcpy(m_pcpxUf, pcpxTmp, sizeof(fftw_complex) * m_smpcLength);
        fftw_free(pcpxTmp);
        // set new length attribute
        m_smpcLength = smpcLength;
    }
}


// init/destroy
template<>
void AFComplexVector<fftwf_complex, float>::Create(const AFSampleCount smpcLength, const bool bIsPolar)
{
    m_bIsPolar = bIsPolar;
    if((m_smpcLength = smpcLength) > 0)
    {
        m_pcpxUf = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * m_smpcLength);
#ifdef __AUDEBUG__
        if(!m_pcpxUf) fprintf(stderr, "Create float complex vector failed.\n");
#endif
        Clear();
    }
}

template<>
void AFComplexVector<fftwf_complex, float>::Destroy()
{
    if(m_pcpxUf) fftwf_free(m_pcpxUf);
}

template<>
void AFComplexVector<fftw_complex, double>::Create(const AFSampleCount smpcLength, const bool bIsPolar)
{
    m_bIsPolar = bIsPolar;
    if((m_smpcLength = smpcLength) > 0)
    {
        m_pcpxUf = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * m_smpcLength);
#ifdef __AUDEBUG__
        if(!m_pcpxUf) fprintf(stderr, "Create double complex vector failed.\n");
#endif
        
        Clear();
    }
}

template<>
void AFComplexVector<fftw_complex, double>::Destroy()
{
    if(m_pcpxUf)
    { fftw_free(m_pcpxUf); m_pcpxUf = 0; }
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
