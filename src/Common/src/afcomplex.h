/**********************************************************************
 * 
 *  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 *                       plugin collection
 * 
 *  Common libraries
 * 
 *  afcomplex.h
 * 
 *  Simone Campanini 2011
 * 
 **********************************************************************/
#ifndef __AF_COMPLEX_H__
#define __AF_COMPLEX_H__

#include <commdefs.h>

#include <fftw3.h>


#ifndef _FFTW_REIM__
    #define Re(c) c[0]         // real part of c fftw[f]_complex
    #define Im(c) c[1]         // imag part of c fftw[f]_complex
    #define Mod(c)    sqrt(c[0]*c[0] + c[1]*c[1]) // Module, where 'c' is a fftw[f]_complex
    #define SqrMod(c)     (c[0]*c[0] + c[1]*c[1])  // Square module, where 'c' is a fftw[f]_complex
    #define Magnitude(c)    sqrt(c[0]*c[0] + c[1]*c[1])  // Magnitude and Mod should be alias.
    #define SqrMagnitude(c)      (c[0]*c[0] + c[1]*c[1])
    #define Phase(c)        (-atan2(c[1], c[0]))
    #define DegPhase(c)     (-(atan2(c[1], c[0]) * 180) / M_PI)

// Macros for fftw[f]_complex reinterpretation, Mag,Phase instead of Re,Im
    #define Mag(c) c[0]
    #define Ph(c)  c[1]
#endif

template<class T, class F>
class AFComplexVector
{
  protected:
    T* m_pcpxUf;
    AFSampleCount m_smpcLength;
    
    bool m_bIsPolar;
    
  public:
      
    // conversion methods
    AFComplexVector& ToRectangular();
    AFComplexVector& ToPolar();

    void UnwrapPhase();

    // Data mamipulation
    void Clear();
    void ShiftLeft(const AFSampleCount smpcLength);

    // MultiplyACcumulate
    const AFComplexVector& Mac(const AFComplexVector& Left, const AFComplexVector& Right, const AFSampleCount smpcLength, const AFSampleCount smpcFrom = 0);
    const AFComplexVector& Mac(const AFComplexVector& Left, const AFComplexVector& Right);
    const AFComplexVector& Mac(const F fLeft, const AFComplexVector& Right);
    
    // operators
    AFComplexVector operator+(const AFComplexVector& Right);
    AFComplexVector operator-(const AFComplexVector& Right);
    AFComplexVector operator*(const AFComplexVector& Right);
    AFComplexVector operator/(const AFComplexVector& Right);
    
    AFComplexVector operator+(const F fRight);
    AFComplexVector operator-(const F fRight);
    AFComplexVector operator*(const F fRight);
    AFComplexVector operator/(const F fRight);

//     friend  AFComplexVector operator+(const F fLeft, const AFComplexVector& Right);
//     friend  AFComplexVector operator-(const F fLeft, const AFComplexVector& Right);
//     friend  AFComplexVector operator*(const F fLeft, const AFComplexVector& Right);
    
    AFComplexVector& operator+=(const AFComplexVector& Right);
    AFComplexVector& operator-=(const AFComplexVector& Right);
    AFComplexVector& operator*=(const AFComplexVector& Right);
    AFComplexVector& operator/=(const AFComplexVector& Right);

    AFComplexVector& operator+=(const F fRight);
    AFComplexVector& operator-=(const F fRight);
    AFComplexVector& operator*=(const F fRight);
    AFComplexVector& operator/=(const F fRight);
    
    const AFComplexVector& operator=(const AFComplexVector& Right);
    const AFComplexVector& operator=(const T* pcpxRight);

    // Retrieve item
    T& operator[](const AFSampleCount smpcIdx) const { return m_pcpxUf[smpcIdx]; }
    T& Item(const AFSampleCount smpcIdx)       const { return m_pcpxUf[smpcIdx]; }
    T& GetItem(const AFSampleCount smpcIdx)    const { return m_pcpxUf[smpcIdx]; }
    F  GetItem(const AFSampleCount smpcIdx,
               const AFSampleCount smpcReIm)   const { return m_pcpxUf[smpcIdx][smpcReIm]; }

    F Real(const AFSampleCount smpcIdx) const { return Re(m_pcpxUf[smpcIdx]); }
    F Imag(const AFSampleCount smpcIdx) const { return Im(m_pcpxUf[smpcIdx]); }
    F Magn(const AFSampleCount smpcIdx) const { return Mag(m_pcpxUf[smpcIdx]); }
    F Phas(const AFSampleCount smpcIdx) const { return Ph(m_pcpxUf[smpcIdx]); }
    F GetReal(const AFSampleCount smpcIdx) const { return Re(m_pcpxUf[smpcIdx]); }
    F GetImag(const AFSampleCount smpcIdx) const { return Im(m_pcpxUf[smpcIdx]); }
    F GetMagn(const AFSampleCount smpcIdx) const { return Mag(m_pcpxUf[smpcIdx]); }
    F GetPhas(const AFSampleCount smpcIdx) const { return Ph(m_pcpxUf[smpcIdx]); }

    void SetItem(const AFSampleCount smpcIdx,
                 const AFSampleCount smpcReIm, const F fValue)  { m_pcpxUf[smpcIdx][smpcReIm] = fValue; }
    void SetItem(const AFSampleCount smpcIdx,
                 const F fReal, const F fImag)  { Re(m_pcpxUf[smpcIdx]) = fReal;
                                                  Im(m_pcpxUf[smpcIdx]) = fImag; }
                              
    void SetReal(const AFSampleCount smpcIdx, const F fValue)  { Re(m_pcpxUf[smpcIdx]) = fValue; }
    void SetImag(const AFSampleCount smpcIdx, const F fValue)  { Im(m_pcpxUf[smpcIdx]) = fValue; }
    void SetMagn(const AFSampleCount smpcIdx, const F fValue)  { Mag(m_pcpxUf[smpcIdx]) = fValue; }
    void SetPhas(const AFSampleCount smpcIdx, const F fValue)  { Ph(m_pcpxUf[smpcIdx])  = fValue; }
    
    T* GetFirst() const { return m_pcpxUf[0]; }
    T* GetLast()  const { return m_pcpxUf[m_smpcLength-1]; }
    
    F GetDC() const { return Re(m_pcpxUf[0]); }
    F GetNy() const { return Re(m_pcpxUf[m_smpcLength-1]); }
    void SetDC(const F fValue) { Re(m_pcpxUf[0]) = fValue; }
    void SetNy(const F fValue) { Re(m_pcpxUf[m_smpcLength-1]) = fValue; }
    
    F Module(const AFSampleCount smpcIdx)       const { return (m_bIsPolar) ? Mag(m_pcpxUf[smpcIdx]) : Mod(m_pcpxUf[smpcIdx]); }
    F Argument(const AFSampleCount smpcIdx)     const { return (m_bIsPolar) ? Ph(m_pcpxUf[smpcIdx])  : Phase(m_pcpxUf[smpcIdx]); }
    F SquareModule(const AFSampleCount smpcIdx) const { return (m_bIsPolar) ? Mag(m_pcpxUf[smpcIdx]) * Mag(m_pcpxUf[smpcIdx])
                                                                            : SqrMod(m_pcpxUf[smpcIdx]); }
    void Store(AFComplexVector& Dest);
    void Store(AFComplexVector& Dest, const AFSampleCount smpcLength, const AFSampleCount smpcFrom = 0);

    void StoreModule(F* Dest);
    void StoreModule(F* Dest, const AFSampleCount smpcLength, const AFSampleCount smpcFrom = 0);
    void StorePhase(F* Dest);
    void StorePhase(F* Dest, const AFSampleCount smpcLength, const AFSampleCount smpcFrom = 0);

    // Retrieve vector
    T* GetData() { return m_pcpxUf; }
    void SetData(const T* pcpxUf) { memcpy(m_pcpxUf, pcpxUf, sizeof(T) * m_smpcLength); }

    T* GetData(const AFSampleCount smpcOfs) { return (m_pcpxUf + smpcOfs); }
    void SetData(const T* pcpxUf, const AFSampleCount smpcLength, const AFSampleCount smpcOfs = 0)  { memcpy(m_pcpxUf + smpcOfs, pcpxUf, sizeof(T) * smpcLength); }
                                                                          
    // length set-getters
    AFSampleCount Length()    const { return m_smpcLength; }
    AFSampleCount GetLength() const { return m_smpcLength; }
    void SetLength(const AFSampleCount smpcLength);

    // checkers
    bool IsPolar()       const { return  m_bIsPolar; }
    bool IsRectangular() const { return !m_bIsPolar; }

    // init/destroy
    void Create(const AFSampleCount smpcLength, const bool bIsPolar = false);
    void Destroy();
    
    // 'ctors
    AFComplexVector(const AFSampleCount smpcLength = 0, const bool bIsPolar = false)
    : m_pcpxUf(0), m_smpcLength(smpcLength), m_bIsPolar(bIsPolar)
    { Create(smpcLength, bIsPolar); }
    
    ~AFComplexVector()
    { Destroy(); }
};

// ------------------------------------------------------------ Template class definitions ---------------------------

template<class T, class F>
inline void AFComplexVector<T, F>::Clear()
{
    if(m_pcpxUf)
        memset(m_pcpxUf, 0, sizeof(T) * m_smpcLength);
}

template<class T, class F>
inline void AFComplexVector<T, F>::ShiftLeft(const AFSampleCount smpcOfs)
{
    assert(m_pcpxUf > 0 && smpcOfs > 0);
    memmove(m_pcpxUf, m_pcpxUf + smpcOfs, sizeof(T) * (m_smpcLength - smpcOfs));
    memset(m_pcpxUf + (m_smpcLength - smpcOfs), 0, sizeof(T) * smpcOfs);
}

template<class T, class F>
inline const AFComplexVector<T, F>& AFComplexVector<T, F>::Mac(const AFComplexVector& Left, const AFComplexVector& Right,
                                                               const AFSampleCount smpcLength, const AFSampleCount smpcFrom)
{
    // core methods that uses current class as accumulator in wich is stored the operands products.
    for(AFSampleCount i = 0; i < smpcLength; i++)
    {
        Re(m_pcpxUf[i + smpcFrom]) += ( Re(Left.m_pcpxUf[i]) * Re(Right.m_pcpxUf[i]) - Im(Left.m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) );
        Im(m_pcpxUf[i + smpcFrom]) += ( Re(Left.m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) + Re(Left.m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) );
    }
    return *this;
}

template<class T, class F>
inline const AFComplexVector<T, F>& AFComplexVector<T, F>::Mac(const AFComplexVector& Left, const AFComplexVector& Right)
{
    // core methods that uses current class as accumulator in wich is stored the operands products.
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(m_pcpxUf[i]) += ( Re(Left.m_pcpxUf[i]) * Re(Right.m_pcpxUf[i]) - Im(Left.m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) );
        Im(m_pcpxUf[i]) += ( Re(Left.m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) + Re(Left.m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) );
    }
    return *this;
}

template<class T, class F>
inline const AFComplexVector<T, F>& AFComplexVector<T, F>::Mac(const F fLeft, const AFComplexVector& Right)
{
    // core methods that uses current class as accumulator in wich is stored the operands products.
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(m_pcpxUf[i]) += ( fLeft * Re(Right.m_pcpxUf[i]) );
        Im(m_pcpxUf[i]) += ( fLeft * Im(Right.m_pcpxUf[i]) );
    }
    return *this;
}

// operators
template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator+(const AFComplexVector& Right)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) + Re(Right.m_pcpxUf[i]);
        Im(V.m_pcpxUf[i]) = Im(m_pcpxUf[i]) + Im(Right.m_pcpxUf[i]);
    }
    return V;
}

template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator-(const AFComplexVector& Right)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) - Re(Right.m_pcpxUf[i]);
        Im(V.m_pcpxUf[i]) = Im(m_pcpxUf[i]) - Im(Right.m_pcpxUf[i]);
    }
    return V;
}

template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator*(const AFComplexVector& Right)
{
    AFComplexVector V(m_smpcLength);

    // At DC, and Fnyquist, we have only real part
    V.SetDC( GetDC()*Right.GetDC() );
    V.SetNy( GetNy()*Right.GetNy() );
    
    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)
    {
        Re(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) * Re(Right.m_pcpxUf[i]) - Im(m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]);
        Im(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) + Re(m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]);
    }
    return V;
}

template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator/(const AFComplexVector& Right)
{
    assert(!m_bIsPolar);
    AFComplexVector V(m_smpcLength, m_bIsPolar);
    
    // At DC, and Fnyquist, we have only real part
    V.SetDC( (Right.GetDC() != 0) ? GetDC() / Right.GetDC() : GetDC() / F(exp(-32.0)) );
    V.SetNy( (Right.GetNy() != 0) ? GetNy() / Right.GetNy() : GetNy() / F(exp(-32.0)) );
    
    F fDen;
    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)
    {
        if((fDen = SqrMod(Right.m_pcpxUf[i])) != 0)
        {
            Re(V.m_pcpxUf[i]) = (Re(m_pcpxUf[i])*Re(Right.m_pcpxUf[i]) + Im(m_pcpxUf[i])*Im(Right.m_pcpxUf[i])) / fDen;
            Im(V.m_pcpxUf[i]) = (Im(m_pcpxUf[i])*Re(Right.m_pcpxUf[i]) - Re(m_pcpxUf[i])*Im(Right.m_pcpxUf[i])) / fDen;
        }
        else
        {
            //A.Farina: if smpDen == 0, cannot perform division. We assume the result is 0.
            Re(V.m_pcpxUf[i]) = 0;
            Im(V.m_pcpxUf[i]) = 0;
        }
    }
    return V;
}

template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator+(const F fRight)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        Re(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) + fRight;
    return V;
}

template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator-(const F fRight)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        Re(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) - fRight;
    return V;
}

template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator*(const F fRight)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) * fRight;
        Im(V.m_pcpxUf[i]) = Im(m_pcpxUf[i]) * fRight;
    }
    return V;
}

template<class T, class F>
AFComplexVector<T, F> AFComplexVector<T, F>::operator/(const F fRight)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(V.m_pcpxUf[i]) = Re(m_pcpxUf[i]) / fRight;
        Im(V.m_pcpxUf[i]) = Im(m_pcpxUf[i]) / fRight;
    }
    return V;
}

// friends
/*template<class T, class F>
AFComplexVector<T, F> operator+(const F fLeft, const AFComplexVector& Right)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(V.m_pcpxUf[i]) = fLeft + Re(Right.m_pcpxUf[i]);
    }
    return V;
}

template<class T, class F>
AFComplexVector<T, F> operator-(const F fLeft, const AFComplexVector& Right)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(V.m_pcpxUf[i]) = fLeft + Re(Right.m_pcpxUf[i]);
    }
    return V;
}

template<class T, class F>
AFComplexVector<T, F> operator*(const F fLeft, const AFComplexVector& Right)
{
    AFComplexVector V(m_smpcLength);
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(V.m_pcpxUf[i]) = fLeft * Re(Right.m_pcpxUf[i]);
        Im(V.m_pcpxUf[i]) = fLeft * Im(Right.m_pcpxUf[i]);
    }
    return V;
}*/
// end of friends

template<class T, class F>
AFComplexVector<T, F>& AFComplexVector<T, F>::operator+=(const AFComplexVector& Right)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(m_pcpxUf[i]) = Re(m_pcpxUf[i]) + Re(Right.m_pcpxUf[i]);
        Im(m_pcpxUf[i]) = Im(m_pcpxUf[i]) + Im(Right.m_pcpxUf[i]);
    }
    return *this;
}

template<class T, class F>
AFComplexVector<T, F>& AFComplexVector<T, F>::operator-=(const AFComplexVector& Right)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(m_pcpxUf[i]) = Re(m_pcpxUf[i]) - Re(Right.m_pcpxUf[i]);
        Im(m_pcpxUf[i]) = Im(m_pcpxUf[i]) - Im(Right.m_pcpxUf[i]);
    }
    return *this;
}

template<class T, class F>
AFComplexVector<T, F>& AFComplexVector<T, F>::operator*=(const AFComplexVector& Right)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(m_pcpxUf[i]) = Re(m_pcpxUf[i]) * Re(Right.m_pcpxUf[i]) - Im(m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]);
        Im(m_pcpxUf[i]) = Re(m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]) + Re(m_pcpxUf[i]) * Im(Right.m_pcpxUf[i]);
    }
    return *this;
}

template<class T, class F>
AFComplexVector<T, F>& AFComplexVector<T, F>::operator/=(const AFComplexVector& Right)
{
    assert(!m_bIsPolar);
    
    // At DC, and Fnyquist, we have only real part
    SetDC( (Right.GetDC() != 0) ? GetDC() / Right.GetDC() : GetDC() / expf(-32) );
    SetNy( (Right.GetNy() != 0) ? GetNy() / Right.GetNy() : GetNy() / expf(-32) );
    
    F fDen;
    for(AFSampleCount i = 1; i < (m_smpcLength-1); i++)
    {
        if((fDen = SqrMod(Right.pcpxU[i])) != 0)
        {
            Re(m_pcpxUf[i]) = (Re(m_pcpxUf[i])*Re(Right.m_pcpxUf[i]) + Im(m_pcpxUf[i])*Im(Right.m_pcpxU[i])) / fDen;
            Im(m_pcpxUf[i]) = (Im(m_pcpxUf[i])*Re(Right.m_pcpxUf[i]) - Re(m_pcpxUf[i])*Im(Right.m_pcpxU[i])) / fDen;
        }
        else
        {
            //A.Farina: if smpDen == 0, cannot perform division. We assume the result is 0.
            Re(m_pcpxUf[i]) = 0;
            Im(m_pcpxUf[i]) = 0;
        }
    }
    return *this;
}

template<class T, class F>
inline AFComplexVector<T, F>& AFComplexVector<T, F>::operator+=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        Re(m_pcpxUf[i]) = Re(m_pcpxUf[i]) + fRight;
    return *this;
}

template<class T, class F>
inline AFComplexVector<T, F>& AFComplexVector<T, F>::operator-=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
        Re(m_pcpxUf[i]) = Re(m_pcpxUf[i]) - fRight;
    return *this;
}

template<class T, class F>
inline AFComplexVector<T, F>& AFComplexVector<T, F>::operator*=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(m_pcpxUf[i]) = Re(m_pcpxUf[i]) * fRight;
        Im(m_pcpxUf[i]) = Im(m_pcpxUf[i]) * fRight;
    }
    return *this;
}

template<class T, class F>
inline AFComplexVector<T, F>& AFComplexVector<T, F>::operator/=(const F fRight)
{
    for(AFSampleCount i = 0; i < m_smpcLength; i++)
    {
        Re(m_pcpxUf[i]) = Re(m_pcpxUf[i]) / fRight;
        Im(m_pcpxUf[i]) = Im(m_pcpxUf[i]) / fRight;
    }
    return *this;
}

template<class T, class F>
inline const AFComplexVector<T, F>& AFComplexVector<T, F>::operator=(const AFComplexVector& Right)
{
    if(this == &Right) return *this;
    if(Right.m_smpcLength >= m_smpcLength)
    {
        memcpy(m_pcpxUf, Right.m_pcpxUf, sizeof(T) * m_smpcLength);
        m_smpcLength = Right.m_smpcLength;
    }
    //else throw exception!!!
    return *this;
}

template<class T, class F>
inline const AFComplexVector<T, F>& AFComplexVector<T, F>::operator=(const T* pcpxRight)
{
    if(m_pcpxUf == pcpxRight) return *this;
    memcpy(m_pcpxUf, pcpxRight, sizeof(T) * m_smpcLength);
    return *this;
}

template<class T, class F>
inline void AFComplexVector<T, F>::Store(AFComplexVector& Dest)
{
    memcpy(Dest.m_pcpxUf, m_pcpxUf, sizeof(T) * m_smpcLength);
}

template<class T, class F>
inline void AFComplexVector<T, F>::Store(AFComplexVector& Dest, const AFSampleCount smpcLength, const AFSampleCount smpcFrom)
{                                         
    memcpy(Dest.m_pcpxUf, m_pcpxUf + smpcFrom, sizeof(T) * smpcLength);
}

template<class T, class F>
void AFComplexVector<T, F>::StoreModule(F* dest)
{
	if(m_bIsPolar)
	{
        for(size_t i = 0; i < m_smpcLength; i++)
    	    dest[i] = Mag(m_pcpxUf[i]);
	}
	else
	{
        for(size_t i = 0; i < m_smpcLength; i++)
    	    dest[i] = Mod(m_pcpxUf[i]);
	}
}

template<class T, class F>
void AFComplexVector<T, F>::StoreModule(F* dest, const AFSampleCount smpcLength, const AFSampleCount smpcFrom)
{
	if(m_bIsPolar)
	{
        for(size_t i = smpcFrom; i < smpcFrom + smpcLength; i++)
    	    dest[i] = Mag(m_pcpxUf[i]);
	}
	else
	{
        for(size_t i = smpcFrom; i < smpcFrom + smpcLength; i++)
    	    dest[i] = Mod(m_pcpxUf[i]);
	}
}

template<class T, class F>
void AFComplexVector<T, F>::StorePhase(F* dest)
{
	if(m_bIsPolar)
	{
        for(size_t i = 0; i < m_smpcLength; i++)
    	    dest[i] = Ph(m_pcpxUf[i]);
	}
	else
	{
        for(size_t i = 0; i < m_smpcLength; i++)
    	    dest[i] = Phase(m_pcpxUf[i]);
	}
}

template<class T, class F>
void AFComplexVector<T, F>::StorePhase(F* dest, const AFSampleCount smpcLength, const AFSampleCount smpcFrom)
{
	if(m_bIsPolar)
	{
        for(size_t i = smpcFrom; i < smpcFrom + smpcLength; i++)
    	    dest[i] = Ph(m_pcpxUf[i]);
	}
	else
	{
        for(size_t i = smpcFrom; i < smpcFrom + smpcLength; i++)
    	    dest[i] = Phase(m_pcpxUf[i]);
	}
}


template<class T, class F>
void AFComplexVector<T, F>::UnwrapPhase()
{
    assert(m_bIsPolar);  //Operation valid only on Polar form
    
    //AFSampleCount smpcN = smpcLength/2; // Farina's
    
    // W conterrà i valori della fase modulo 2pi
    
    F* fUnwrappedPhase = new F [m_smpcLength];
    memset(fUnwrappedPhase, 0, m_smpcLength * sizeof(F));
    
    F fTwoPi = F(2.0*M_PI);
    AFSampleCount i;
    
    //Ricerco il minimo del vettore
    F fMinPhase = Ph(m_pcpxUf[0]);   // TODO: Is this the correct initialization??
    for(i=0; i < m_smpcLength; i++)
        fMinPhase = (Ph(m_pcpxUf[i]) < fMinPhase) ? Ph(m_pcpxUf[i]) : fMinPhase;
    
    F fPhaseDiff;
    for(i = 0; i < m_smpcLength; i++)
    {
        fPhaseDiff = (Ph(m_pcpxUf[i]) - fMinPhase)/fTwoPi;
        
        if(fPhaseDiff > 0)   //se e' positivo, allora devo usare il floor, cioe' l'int + piccolo
            fUnwrappedPhase[i] = F(Ph(m_pcpxUf[i]) - fTwoPi*floor(fPhaseDiff));
        else if(fPhaseDiff < 0) //se e' negativo, devo usare ceil, cioe' l'int +grande
            fUnwrappedPhase[i] = F(Ph(m_pcpxUf[i]) - fTwoPi*ceil(fPhaseDiff));
        else
            fUnwrappedPhase[i] = fMinPhase; // cioe' sono nel caso "zero"
    }
    
    //Calcolo le differenze tra termini cosecutivi, cioe': [X(2)-X(1)  X(3)-X(2) ... X(n)-X(n-1)]
    F fHop = 0, fPrevHop = 0;
    
    if(fUnwrappedPhase[0] > fTwoPi)
        fPrevHop = -fTwoPi;
    else if(fUnwrappedPhase[0] < fTwoPi)
        fPrevHop = fTwoPi;
    
    Ph(m_pcpxUf[0]) = fUnwrappedPhase[0] + fPrevHop;
    
    for(i = 1; i < m_smpcLength; i++)
    {
        //Cerco i salti, costruisco l'array dei salti,
        //sommo la fase alla correzione e
        //sovrascrivo il vettore in uscita
        
        if((fUnwrappedPhase[i]-fUnwrappedPhase[i-1]) > fTwoPi)
            fHop = fPrevHop - fTwoPi;
        else if((fUnwrappedPhase[i]-fUnwrappedPhase[i-1]) < fTwoPi)
            fHop = fPrevHop + fTwoPi;
        
        Ph(m_pcpxUf[i]) = fUnwrappedPhase[i] + fHop;
        fPrevHop = fHop;
    }
}







#endif //__AF_COMPLEX_H__


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

