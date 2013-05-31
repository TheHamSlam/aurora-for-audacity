/**********************************************************************
 *
 *  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 *                       plugin collection
 *
 *  Common libraries
 *
 *  afmatrix.h
 *
 *  Simone Campanini 2011
 *
 **********************************************************************/
#ifndef __AF_MATRIX_H__
#define __AF_MATRIX_H__

#include <afvector.h>

template <class F>
class AFMatrix
{
  private:
    AFVector<F>** m_ppItem;
     
    AFSampleCount m_smpcRows;
    AFSampleCount m_smpcCols;
      
  public:
    // operators
    AFMatrix& operator=(const AFMatrix& Right);
      
    // Get-setters
    AFSampleCount GetRowsNo() const { return m_smpcRows; }
    AFSampleCount GetColsNo() const { return m_smpcCols; }
      
    AFVector<F>& Item(const AFSampleCount smpcRow,
                      const AFSampleCount smpcCol) { return m_ppItem[smpcRow][smpcCol]; }

    AFVector<F>& GetItem(const AFSampleCount smpcRow,
                         const AFSampleCount smpcCol) { return m_ppItem[smpcRow][smpcCol]; }
    void SetItem(const AFSampleCount smpcRow,
                 const AFSampleCount smpcCol,
                 const AFVector<F>& Item) { m_ppItem[smpcRow][smpcCol] = Item; }
                                                                        
                                                                       
    F* GetData(const AFSampleCount smpcRow,
               const AFSampleCount smpcCol) { return m_ppItem[smpcRow][smpcCol].GetData(); }
    void SetData(const AFSampleCount smpcRow,
                 const AFSampleCount smpcCol,
                 const F* pfUt) { return m_ppItem[smpcRow][smpcCol].SetData(pfUt); }
                                                                                                
                                                                                                // init/destroy
    void Create(const AFSampleCount smpcRows, const AFSampleCount smpcCols,
                const AFSampleCount smpcLength);
    void Destroy();

    // 'ctors
    AFMatrix(const AFSampleCount smpcRows = 1,   const AFSampleCount smpcCols = 1,
             const AFSampleCount smpcLength = 0)
    : m_smpcRows(smpcRows), m_smpcCols(smpcCols)
    { Create(smpcRows, smpcCols, smpcLength); }

    ~AFMatrix()
    { Destroy(); }
                                                                                                    
};

// ------------------------------------------------------------ Template class definitions ---------------------------

template<class F>
AFMatrix<F>& AFMatrix<F>::operator=(const AFMatrix& Right)
{
    if(this == &Right) return *this;
    assert(Right.m_ppItem[0][0] <= m_ppItem[0][0]);

    AFSampleCount smpcRow, smpcCol;
    for(smpcRow = 0; smpcRow < m_smpcRows; smpcRow++)
        for(smpcCol = 0; smpcCol < m_smpcCols; smpcCol++)
            m_ppItem[smpcRow][smpcCol] = Right.m_ppItem[smpcRow][smpcCol];
        
        return *this;
}

template<class F>
void AFMatrix<F>::Create(const AFSampleCount smpcRows, const AFSampleCount smpcCols,
                         const AFSampleCount smpcLength)
{
    if(smpcRows == 0) return;
    
    m_smpcRows = smpcRows;
    m_smpcCols = smpcCols;
    
    m_ppItem = new AFVector<F>* [m_smpcRows];
    
    AFSampleCount smpcRow, smpcCol;
    for(smpcRow = 0; smpcRow < m_smpcRows; smpcRow++)
    {
        m_ppItem[smpcRow] = new AFVector<F> [m_smpcCols];
        for(smpcCol = 0; smpcCol < m_smpcCols; smpcCol++)
        {
            m_ppItem[smpcRow][smpcCol].Create(smpcLength);
        }
    }
}

template<class F>
void AFMatrix<F>::Destroy()
{
    for(AFSampleCount smpcRow = 0; smpcRow < m_smpcRows; smpcRow++)
        delete [] m_ppItem[smpcRow];
    delete [] m_ppItem;
}



#endif //__AF_MATRIX_H__
