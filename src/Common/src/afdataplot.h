/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common Libraries
  
  afdataplot.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_AFDATAPLOT_H__
#define __AURORA_AFDATAPLOT_H__

#include "afplot.h"

//----------------------------------------------------------------------------
// AFDataPlot
//----------------------------------------------------------------------------
/// \brief This is a template of a 'plot with data' (see afdata.h).
/// The 'next step' after AFPlotBase, with the addition of structures
/// (called \e data \e series) useful for represented data.\n
/// This class should not be instantiated directly, use, instead,
/// AFScope(), AFSScope(), AFChart(), AFBarPlot().
//----------------------------------------------------------------------------
template <class TArrayOfDataSeries, class TDataSerie>
class AFDataPlot : public AFPlotBase
{
  protected:
    TArrayOfDataSeries  m_aDataSeries; ///< The data series array.

  public:
   
   /// Set data serie visibility flag
   /// \param nIdx - data serie index
   /// \param bShow - visibility flag.
   virtual void ShowSerie(const size_t nIdx, const bool bShow = true);

   void AddSerie    (TDataSerie* pData) { m_aDataSeries.Add(pData); }

   void InsertSerie (const size_t nIdx, TDataSerie* pData);
   void ReplaceSerie(const size_t nIdx, TDataSerie* pData);
   void DeleteSerie (const size_t nIdx);
   void ClearSerie  () { if(m_aDataSeries.GetCount() > 0) m_aDataSeries.Clear(); }

   /// The constructor.
   /// \param parent - parent window
   /// \param id - window identifier
   /// \param pos - window position
   /// \param size - window size
   AFDataPlot(wxWindow *parent,
		      wxWindowID id,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize )
   : AFPlotBase(parent, id, pos, size)
   {}
   
   ~AFDataPlot() {}    
};


// ------------------------------------------ Template definitions ---------------------------------------------

template<class TArrayOfDataSeries, class TDataSerie>
void AFDataPlot<TArrayOfDataSeries, TDataSerie>::ShowSerie(const size_t unIdx, const bool bShow)
{
    wxASSERT_MSG(unIdx < m_aDataSeries.GetCount(),
                 wxT("Show request failed: index out of bounds."));
    m_aDataSeries[unIdx].Show(bShow);
}

template<class TArrayOfDataSeries, class TDataSerie>
void AFDataPlot<TArrayOfDataSeries, TDataSerie>::InsertSerie(const size_t unIdx, TDataSerie* pData)
{
    wxASSERT_MSG(unIdx < m_aDataSeries.GetCount(),
                 wxT("Insert request failed: index out of bounds."));
    m_aDataSeries.Insert(pData, unIdx);
}

template<class TArrayOfDataSeries, class TDataSerie>
void AFDataPlot<TArrayOfDataSeries, TDataSerie>::ReplaceSerie(const size_t unIdx, TDataSerie* pData)
{
    m_aDataSeries[unIdx] = *pData; // Be sure that = is overloaded...
}

template<class TArrayOfDataSeries, class TDataSerie>
void AFDataPlot<TArrayOfDataSeries, TDataSerie>::DeleteSerie(const size_t nIdx)
{
    wxASSERT_MSG(nIdx < m_aDataSeries.GetCount(),
                 wxT("Delete request failed: index out of bounds."));
    m_aDataSeries.RemoveAt(nIdx);
}

#endif  // __AURORA_AFDATAPLOT_H__

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
