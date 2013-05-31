/**********************************************************************
 * 
 *  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 *                       plugin collection
 * 
 *  Common libraries
 * 
 *  afvector.h
 * 
 *  Simone Campanini 2011
 * 
 **********************************************************************/
#ifndef __AF_VECTOR_H__
#define __AF_VECTOR_H__

#include <commdefs.h>

template <class F>
class AFVector
{
  protected:
    F* m_pfUt;
    AFSampleCount  m_smpcLength;

    F m_fMax;
    AFSampleCount m_smpcMaxPosition;
    F m_fMin;
    AFSampleCount m_smpcMinPosition;
    
  public:
    void Clear();
    void ShiftLeft(const AFSampleCount smpcLength);
    
    void FadeIn(const AFSampleCount smpcDuration);
    void FadeOut(const AFSampleCount smpcDuration);

    // Multiply-ACcumulate
    const AFVector& Mac(const AFVector& Left, const AFVector& Right, const AFSampleCount smpcLength, const AFSampleCount unFrom = 0);
    const AFVector& Mac(const AFVector& Left, const AFVector& Right);
    const AFVector& Mac(const F fLeft, const AFVector& Right);
      
    // operators
    const AFVector& operator<<(const AFSampleCount smpcOfs);
    
    AFVector operator+(const AFVector& Right);
    AFVector operator-(const AFVector& Right);
    AFVector operator*(const AFVector& Right);
    AFVector operator/(const AFVector& Right);
    
    AFVector operator+(const F smpRight);
    AFVector operator-(const F smpRight);
    AFVector operator*(const F smpRight);
    AFVector operator/(const F smpRight);

//     friend AFVector operator+(const F fLeft, const AFVector& Right);
//     friend AFVector operator-(const F fLeft, const AFVector& Right);
//     friend AFVector operator*(const F fleft, const AFVector& Right);
    
    AFVector& operator+=(const AFVector& Right);
    AFVector& operator-=(const AFVector& Right);
    AFVector& operator*=(const AFVector& Right);
    AFVector& operator/=(const AFVector& Right);

    AFVector& operator+=(const F smpRight);
    AFVector& operator-=(const F smpRight);
    AFVector& operator*=(const F smpRight);
    AFVector& operator/=(const F smpRight);

    const AFVector& operator=(const AFVector& Right);
    const AFVector& operator=(const F* psmpRight);
    
    // Retrieve item
    F& operator[](const AFSampleCount nIdx) const { return m_pfUt[nIdx]; }
    F& Item(const AFSampleCount nIdx)        const { return m_pfUt[nIdx]; }
    F GetItem(const AFSampleCount nIdx)     const { return m_pfUt[nIdx]; }

    void SetItem(const AFSampleCount nIdx, const F fValue) { m_pfUt[nIdx] = fValue; }

    F GetFirst() const { return m_pfUt[0]; }
    F GetLast()  const { return m_pfUt[m_smpcLength-1]; }
    
    F Abs(const AFSampleCount nIdx) const { return fabsf(m_pfUt[nIdx]); }
    F Sqr(const AFSampleCount nIdx) const { return m_pfUt[nIdx] * m_pfUt[nIdx]; }

    F GetMax();
    F GetMin();
    F GetAbsMax();

    AFSampleCount GetMaxPosition() const { return m_smpcMaxPosition; }
    AFSampleCount GetMinPosition() const { return m_smpcMinPosition; }
    AFSampleCount GetAbsMaxPosition();

    void Store(AFVector& Dest);
    void Store(AFVector& Dest, const AFSampleCount smpcLength, const AFSampleCount unFrom);

    // Retrieve vector
    F* GetData() { return m_pfUt; }
    virtual void SetData(const F* pfUt) { memcpy(m_pfUt, pfUt, sizeof(F) * m_smpcLength); }
    
    F* GetData(const AFSampleCount smpcOfs) { return (m_pfUt + smpcOfs); }
    virtual void SetData(const F* pfUt, const AFSampleCount smpcLength, const AFSampleCount smpcOfs = 0) { memcpy(m_pfUt + smpcOfs, pfUt, sizeof(F) * smpcLength); }
    
    // length set-getters
    AFSampleCount Length()    const { return m_smpcLength; }
    AFSampleCount GetLength() const { return m_smpcLength; }
    void SetLength(const AFSampleCount smpcLength);
    
    // init/destroy
    void Create(const AFSampleCount smpcLength);
    void Destroy();
    
    // 'ctors
    AFVector(const AFSampleCount smpcLength = 0)
    : m_pfUt(0), m_smpcLength(smpcLength),
      m_fMax(0), m_smpcMaxPosition(0),
      m_fMin(0), m_smpcMinPosition(0)
    { Create(smpcLength); }
    
    ~AFVector()
    { Destroy(); }
};

#endif //__AF_VECTOR_H__

// ------------------------------------------------------------ Template class definitions ---------------------------

template<class F>
inline void AFVector<F>::Clear()
{
    if(m_pfUt)
        memset(m_pfUt, 0, sizeof(F) * m_smpcLength);
}

template<class F>
inline void AFVector<F>::ShiftLeft(const AFSampleCount smpcOfs)
{
    assert(m_pfUt > 0 && smpcOfs > 0);
    memmove(m_pfUt, m_pfUt + smpcOfs, sizeof(F) * (m_smpcLength - smpcOfs));
    memset(m_pfUt + (m_smpcLength - smpcOfs), 0, sizeof(F) * smpcOfs);
}

template<class F>
void AFVector<F>::FadeIn(const AFSampleCount smpcDuration)
{
    AFSampleCount smpcL = (smpcDuration > m_smpcLength) ? m_smpcLength : smpcDuration;
    for(AFSampleCount i = 0; i < smpcL; i++)
        m_pfUt[i] *= (1.0 - cos(M_PI*i/F(smpcL))) / 2.0;
        
}

template<class F>
void AFVector<F>::FadeOut(const AFSampleCount smpcDuration)
{
    AFSampleCount smpcL = (smpcDuration > m_smpcLength) ? m_smpcLength : smpcDuration;
    for(AFSampleCount i = 0; i < smpcL; i++)
        m_pfUt[m_smpcLength - smpcL + i] *= (1.0 - cos(M_PI*i/F(smpcL))) / 2.0;
}


template<class F>
inline const AFVector<F>& AFVector<F>::Mac(const AFVector& Left, const AFVector& Right, const AFSampleCount smpcLength, const AFSampleCount unFrom)
{
    // core methods that uses current class as accumulator in wich is stored the operands products.
    for(AFSampleCount i = 0; i < smpcLength; i++)
        m_pfUt[i + unFrom] += ( Left.m_pfUt[i] * Right.m_pfUt[i] );
    return *this;
}

template<class F>
inline const AFVector<F>& AFVector<F>::Mac(const AFVector& Left, const AFVector& Right)
{
    // core methods that uses current class as accumulator in wich is stored the operands products.
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] += ( Left.m_pfUt[i] * Right.m_pfUt[i] );
    return *this;
}

template<class F>
inline const AFVector<F>& AFVector<F>::Mac(const F fLeft, const AFVector& Right)
{
    // core methods that uses current class as accumulator in wich is stored the operands products.
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] += ( fLeft * Right.m_pfUt[i] );
    return *this;
}


// operators
template<class F>
inline const AFVector<F>& AFVector<F>::operator<<(const AFSampleCount smpcRight)
{
    assert(m_pfUt > 0 && smpcRight > 0);
    memcpy(m_pfUt, m_pfUt + smpcRight, sizeof(F) * (m_smpcLength - smpcRight));
    memmove(m_pfUt + (m_smpcLength - smpcRight), 0, sizeof(F) * smpcRight);
    return *this;
}

template<class F>
AFVector<F> AFVector<F>::operator+(const AFVector& Right)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = m_pfUt[i] + Right.m_pfUt[i];
    return V;
}

template<class F>
AFVector<F> AFVector<F>::operator-(const AFVector& Right)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = m_pfUt[i] - Right.m_pfUt[i];
    return V;
}

template<class F>
AFVector<F> AFVector<F>::operator*(const AFVector& Right)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = m_pfUt[i] * Right.m_pfUt[i];
    return V;
}

template<class F>
AFVector<F> AFVector<F>::operator/(const AFVector& Right)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)
        V.m_pfUt[i] = m_pfUt[i]/Right.m_pfUt[i];
    return V;
}

template<class F>
AFVector<F> AFVector<F>::operator+(const F fRight)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = m_pfUt[i] + fRight;
    return V;
}

template<class F>
AFVector<F> AFVector<F>::operator-(const F fRight)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = m_pfUt[i] - fRight;
    return V;
}

template<class F>
AFVector<F> AFVector<F>::operator*(const F fRight)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = m_pfUt[i] * fRight;
    return V;
}

template<class F>
AFVector<F> AFVector<F>::operator/(const F fRight)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = m_pfUt[i] / fRight;
    return V;
}

//friends
/*AFVector operator+(const F fLeft, const AFVector& Right)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = fLeft + Right.m_pfUt[i] 
    return V;
}

AFVector operator-(const F smpLeft, const AFVector& Right)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = fLeft - Right.m_pfUt[i]
    return V;
}

AFVector operator*(const F smpleft, const AFVector& Right)
{
    AFVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        V.m_pfUt[i] = fLeft * Right.m_pfUt[i]
    return V;
}*/
// end of friends

template<class F>
inline AFVector<F>& AFVector<F>::operator+=(const AFVector& Right)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] = m_pfUt[i] + Right.m_pfUt[i];
    return *this;
}

template<class F>
inline AFVector<F>& AFVector<F>::operator-=(const AFVector& Right)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] = m_pfUt[i] - Right.m_pfUt[i];
    return *this;
}

template<class F>
inline AFVector<F>& AFVector<F>::operator*=(const AFVector& Right)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] = m_pfUt[i] * Right.m_pfUt[i];
    return *this;
}

template<class F>
inline AFVector<F>& AFVector<F>::operator+=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] += fRight;
    return *this;
}

template<class F>
inline AFVector<F>& AFVector<F>::operator-=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] -= fRight;
    return *this;
}

template<class F>
inline AFVector<F>& AFVector<F>::operator*=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] *= fRight;
    return *this;
}

template<class F>
inline AFVector<F>& AFVector<F>::operator/=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        m_pfUt[i] /= fRight;
    return *this;
}

template<class F>
inline const AFVector<F>& AFVector<F>::operator=(const AFVector& Right)
{
    if(this == &Right) return *this;
    assert(Right.m_smpcLength >= m_smpcLength);
    
    memcpy(m_pfUt, Right.m_pfUt, sizeof(F) * m_smpcLength);
    m_smpcLength = Right.m_smpcLength;
    m_fMax = Right.m_fMax;
    m_fMin = Right.m_fMin;
    return *this;
}

template<class F>
inline const AFVector<F>& AFVector<F>::operator=(const F* pfRight)
{
    if(m_pfUt == pfRight) return *this;
    memcpy(m_pfUt, pfRight, sizeof(F) * m_smpcLength);
    return *this;
}

// length setter
template<class F>
void AFVector<F>::SetLength(const AFSampleCount smpcLength)
{
    assert(smpcLength > 0);
    
    if(m_smpcLength == 0)
    {
        m_smpcLength = smpcLength;
        if(m_pfUt) delete [] m_pfUt;
        m_pfUt = new F [m_smpcLength];
    }
    else
    {
        // create a temporary vector for storing purposes
        F* psmpTmp = new F [m_smpcLength];
        memcpy(psmpTmp, m_pfUt, sizeof(F) * m_smpcLength);
        delete [] m_pfUt;
        // enlarge the vector
        m_pfUt = new F [smpcLength];
        memset(m_pfUt, 0, sizeof(F) * smpcLength);
        // copy backup to new vector
        memcpy(m_pfUt, psmpTmp, sizeof(F) * m_smpcLength);
        delete [] psmpTmp;
        // set new length attribute
        m_smpcLength = smpcLength;
    }
}

template<class F>
F AFVector<F>::GetMax()
{
    if(m_fMax == 0.0)
        for(AFSampleCount i = 0; i < m_smpcLength; i++)
        {
            if(m_pfUt[i] > m_fMax)
            {
                m_fMax = m_pfUt[i];
                m_smpcMaxPosition = i;
            }
        }
    return m_fMax;
}

template<class F>
F AFVector<F>::GetMin()
{
    if(m_fMin == 0.0)
        for(AFSampleCount i = 0; i < m_smpcLength; i++)
        {
            if(m_pfUt[i] < m_fMin)
            {
                m_fMin = m_pfUt[i];
                m_smpcMinPosition = i;
            }
        }
        
    return m_fMin;
}

template<class F>
inline void AFVector<F>::Store(AFVector& Dest)
{
    memcpy(Dest.m_pfUt, m_pfUt, sizeof(F) * m_smpcLength);
}

template<class F>
inline void AFVector<F>::Store(AFVector& Dest, const AFSampleCount smpcLength, const AFSampleCount unFrom)
{
    memcpy(Dest.m_pfUt, m_pfUt + unFrom, sizeof(F) * smpcLength);
}

// two times creation/destroy
template<class F>
void AFVector<F>::Create(const AFSampleCount smpcLength)
{
    if((m_smpcLength = smpcLength) > 0)
    {
        m_pfUt = new F [m_smpcLength];
        Clear();
    }
}

template<class F>
void AFVector<F>::Destroy()
{
    if(m_pfUt)
    { delete [] m_pfUt; m_pfUt = 0; }
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
