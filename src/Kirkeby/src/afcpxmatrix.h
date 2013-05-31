/**********************************************************************
 *
 *  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 *                       plugin collection
 *
 *  Common libraries
 *
 *  afcpxmatrix.h
 *
 *  Simone Campanini 2011
 *
 **********************************************************************/
#ifndef __AF_CPXMATRIX_H__
#define __AF_CPXMATRIX_H__

#include <afcomplex.h>

template<class T, class F>
class AFComplexMatrix
{
  private:
    AFComplexVector<T, F>** m_ppItem;
    
    AFSampleCount m_smpcRows;
    AFSampleCount m_smpcCols;
    
  public:
    // operators
    AFComplexMatrix& operator=(const AFComplexMatrix& Right);
    
    // Get-setters
    AFSampleCount GetRowsNo() const { return m_smpcRows; }
    AFSampleCount GetColsNo() const { return m_smpcCols; }

    AFComplexVector<T, F>& Item(const AFSampleCount smpcRow,
                             const AFSampleCount smpcCol) { return m_ppItem[smpcRow][smpcCol]; }
                            
    AFComplexVector<T, F>& GetItem(const AFSampleCount smpcRow,
                                const AFSampleCount smpcCol) { return m_ppItem[smpcRow][smpcCol]; }
    void SetItem(const AFSampleCount smpcRow,
                 const AFSampleCount smpcCol,
                 const AFComplexVector<T, F>& Item) { m_ppItem[smpcRow][smpcCol] = Item; }
                                         

    T* GetData(const AFSampleCount smpcRow,
               const AFSampleCount smpcCol) { return m_ppItem[smpcRow][smpcCol].GetData(); }
    void SetData(const AFSampleCount smpcRow,
                 const AFSampleCount smpcCol,
                 const T* pcpxUf) { return m_ppItem[smpcRow][smpcCol].SetData(pcpxUf); }
                                                        
    // init/destroy
    void Create(const AFSampleCount smpcRows,   const AFSampleCount smpcCols,
                const AFSampleCount smpcLength, const bool bIsPolar = false);
    void Destroy();
      
    // 'ctors
    AFComplexMatrix(const AFSampleCount smpcRows = 1,   const AFSampleCount smpcCols = 1,
                    const AFSampleCount smpcLength = 0, const bool bIsPolar = false)
    : m_smpcRows(smpcRows), m_smpcCols(smpcCols)
    { Create(smpcRows, smpcCols, smpcLength, bIsPolar); }

    ~AFComplexMatrix()
    { Destroy(); }
};

// ------------------------------------------------------------ Template class definitions ---------------------------

template<class T, class F>
AFComplexMatrix<T, F>& AFComplexMatrix<T, F>::operator=(const AFComplexMatrix& Right)
{
    if(this == &Right) return *this;
    assert(Right.m_ppItem[0][0] <= m_ppItem[0][0]);
    
    AFSampleCount smpcRow, smpcCol;    
    for(smpcRow = 0; smpcRow < m_smpcRows; smpcRow++)
        for(smpcCol = 0; smpcCol < m_smpcCols; smpcCol++)
            m_ppItem[smpcRow][smpcCol] = Right.m_ppItem[smpcRow][smpcCol];
        
    return *this;
}



template<class T, class F>
void AFComplexMatrix<T, F>::Create(const AFSampleCount smpcRows,   const AFSampleCount smpcCols,
                                   const AFSampleCount smpcLength, const bool bIsPolar)
{
    if(smpcRows == 0) return;
    
    m_smpcRows = smpcRows;
    m_smpcCols = smpcCols;
    
    m_ppItem = new AFComplexVector<T, F>* [m_smpcRows];
    
    AFSampleCount smpcRow, smpcCol;
    for(smpcRow = 0; smpcRow < m_smpcRows; smpcRow++)
    {
        m_ppItem[smpcRow] = new AFComplexVector<T, F> [m_smpcCols];
        for(smpcCol = 0; smpcCol < m_smpcCols; smpcCol++)
        {
            m_ppItem[smpcRow][smpcCol].Create(smpcLength, bIsPolar);
        }
    }   
}


template<class T, class F>
void AFComplexMatrix<T, F>::Destroy()
{
    for(AFSampleCount smpcRow = 0; smpcRow < m_smpcRows; smpcRow++)
        delete [] m_ppItem[smpcRow];
    delete [] m_ppItem;
}


#endif //__AF_CPXMATRIX_H__


