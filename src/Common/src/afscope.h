/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common Libraries
  
  afscope.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_AFSCOPE_H__
#define __AURORA_AFSCOPE_H__

#include "afdataplot.h"
//----------------------------------------------------------------------------
// AFScopeBase
//----------------------------------------------------------------------------
// \brief This acts as a base class for AFScope and AFSScope class templates.
/// This class should not be instantiated directly, use, instead,
/// AFScope(), AFSScope(), AFChart(), AFBarPlot().
//----------------------------------------------------------------------------
template <class TArrayOfDataSeries, class TDataSerie>
class AFScopeBase : public AFDataPlot<TArrayOfDataSeries, TDataSerie>
{
  protected:
   AFAxis *m_pTimeAxis,
          *m_pLevelAxis;
 
   virtual void UpdateHorizontalAxis();
   
   void Draw(wxDC& dc);

 public:   
   // --- set/getters

   /// Returns a pointer to horizontal (Time) axis.
   AFAxis* GetTimeAxis () { return m_pTimeAxis; }

   /// Returns a pointer to vertical (Level, usually) axis.
   AFAxis* GetLevelAxis() { return m_pLevelAxis; }

   /// Returns a pointer to horizontal (Time) axis.
   virtual AFAxis* GetHorzAxis() { return m_pTimeAxis; }

   /// Returns a pointer to vertical (Level, usually) axis.
   virtual AFAxis* GetVertAxis() { return m_pLevelAxis; }

   /// The constructor.
   /// \param parent - parent window
   /// \param id - window identifier
   /// \param pos - window position
   /// \param size - window size
   AFScopeBase(wxWindow *parent,
		       wxWindowID id,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize );
   ~AFScopeBase() {}
};

// --------------------- AFScopeBase Template definitions ------------------------

template <class TArrayOfDataSeries, class TDataSerie>
void AFScopeBase<TArrayOfDataSeries, TDataSerie>::UpdateHorizontalAxis()
{
    if(this->m_aDataSeries.GetCount() == 0)
    	return;

    double dbTmin, dbTmax;
    m_pTimeAxis->GetRange(dbTmin, dbTmax);

    // Range check
    // NB: All time series should have the same length
    if(!this->m_aDataSeries[0].IsOk(dbTmin, dbTmax))
    {
       this->SetHorzAxisAutorange(true);
    }

    if(this->m_bIsHorzAutorangeOn)
    {
        dbTmin = (m_pTimeAxis->IsLog()) ? 1.0 : 0.0;
        dbTmax = this->m_aDataSeries[0].GetMax();
    }

    m_pTimeAxis->SetRange(dbTmin, dbTmax);
}

template <class TArrayOfDataSeries, class TDataSerie>
void AFScopeBase<TArrayOfDataSeries, TDataSerie>::Draw(wxDC& dc)
{   
    int nPlotWidth  = this->GetClientAreaWidth(),
        nPlotHeight = this->GetClientAreaHeight(),
        nXofs       = this->GetClientAreaHorzOffset(),
        nYofs       = this->GetClientAreaVertOffset();

    double dbYmin   = m_pLevelAxis->GetMin(),
           dbYRange = m_pLevelAxis->GetMax() - dbYmin,
           dbYScale = nPlotHeight/dbYRange;

    wxPen pen;
    wxBrush brush;

    const double* pdbData;

    //------------- Draw waveform ----------------
    for(size_t unSerie = 0; unSerie < this->m_aDataSeries.GetCount(); unSerie++)
    {
        if(this->m_aDataSeries[unSerie].IsShown())
        {
            pdbData =  this->m_aDataSeries[unSerie].GetData();
            if(!pdbData) continue;

            pen.SetColour(this->m_aDataSeries[unSerie].GetLineColour());
            dc.SetPen(pen);

            int nX0 = 0, nY0 = 0, nX1 = 0, nY1 = 0;

            // Scaling formula: (Lrange - (L - Lmin)) * H/Lrange
            // where L is the series level, H the plot height.
            nY0 = (int) ceil( dbYScale * (dbYRange - (pdbData[0]  - dbYmin)) );

            if(nY0 < 0) nY0 = 0;
            if(nY0 > nPlotHeight) nY0 = nPlotHeight - 1;

            for(nX0 = 0, nX1 = 1; nX1 < (nPlotWidth-1); nX0++, nX1++, nY0 = nY1)
            {
                nY1 = (int) ceil( dbYScale * (dbYRange - (pdbData[nX1] - dbYmin)) );

                if(nY1 < 0) nY1 = 0;
                if(nY1 > nPlotHeight) nY1 = nPlotHeight - 1;

                dc.DrawLine(nX0 + nXofs, nY0 + nYofs, nX1 + nXofs, nY1 + nYofs);
            }
        }
    }
}

template <class TArrayOfDataSeries, class TDataSerie>
AFScopeBase<TArrayOfDataSeries, TDataSerie>::AFScopeBase(wxWindow*  parent, 
                                                         wxWindowID id,
                                                         const wxPoint& pos, 
                                                         const wxSize& size)
  : AFDataPlot<TArrayOfDataSeries, TDataSerie>(parent, id, pos, size),
    m_pTimeAxis(0),
    m_pLevelAxis(0)
{
    this->m_pHorzAxis = new AFAxis();
    this->m_pVertAxis = new AFAxis(wxVERTICAL);
	m_pLevelAxis = static_cast<AFAxis*>(this->m_pVertAxis);
	m_pTimeAxis  = static_cast<AFAxis*>(this->m_pHorzAxis);
    
    m_pLevelAxis->SetName(wxT("Level"));
    m_pTimeAxis->SetName(wxT("Time"));
}


//----------------------------------------------------------------------------
// AFScope
//----------------------------------------------------------------------------
/// This is a template of a 'scope' type plot, designed to show a continuous
/// time-dependend set of real data; it has an horizontal time axis and a
/// vertical 'level' axis.
//----------------------------------------------------------------------------
template <class TArrayOfDataSeries, class TDataSerie>
class AFScope : public AFScopeBase<TArrayOfDataSeries, TDataSerie>
{
  protected:
   virtual void UpdateVerticalAxis();

 public:
   /// The constructor.
   /// \param parent - parent window
   /// \param id - window identifier
   /// \param pos - window position
   /// \param size - window size
   AFScope(wxWindow *parent,
		   wxWindowID id,
           const wxPoint& pos = wxDefaultPosition,
           const wxSize& size = wxDefaultSize )
    : AFScopeBase<TArrayOfDataSeries, TDataSerie>(parent, id, pos, size)
    {}

   ~AFScope() {}
};

// --------------------- AFScope Template definitions ------------------------


template <class TArrayOfDataSeries, class TDataSerie>
void AFScope<TArrayOfDataSeries, TDataSerie>::UpdateVerticalAxis()
{
    if(this->m_aDataSeries.GetCount() == 0) return;

    double dbTmin, dbTmax;
    this->m_pTimeAxis->GetRange(dbTmin, dbTmax);
    
    this->GetLegend()->Clear();

    size_t unSerie;
    for(unSerie = 0; unSerie < this->m_aDataSeries.GetCount(); unSerie++)
    {
        if(this->m_aDataSeries[unSerie].IsShown())
        {
            this->m_aDataSeries[unSerie].CalculateDataSerie(this->GetClientAreaWidth(), dbTmin, dbTmax);

            this->GetLegend()->AddLabel(this->m_aDataSeries[unSerie].GetLabel(),
                                        this->m_aDataSeries[unSerie].GetLineColour());
        }
    }

    if(this->m_bIsVertAutorangeOn)
    {
        double dbLmin = 1.0e+12, dbLmax = -1.0e-12;
//        this->m_pLevelAxis->GetRange(dbLmin, dbLmax);

        double dbLmin1 = 0, dbLmax1 = 0;
        for(unSerie = 0; unSerie < this->m_aDataSeries.GetCount(); unSerie++)
        {        
            if(this->m_aDataSeries[unSerie].IsShown())
            {
               this->Autorange(this->m_aDataSeries[unSerie].GetData(),
                               this->m_aDataSeries[unSerie].GetLength(),
                               dbLmin1, dbLmax1);

               dbLmin = (dbLmin1 < dbLmin) ? dbLmin1 : dbLmin;
               dbLmax = (dbLmax1 > dbLmax) ? dbLmax1 : dbLmax;
            }
        }
        this->m_pLevelAxis->SetRange(dbLmin, dbLmax);
    }
}

//----------------------------------------------------------------------------
// AFSScope
//----------------------------------------------------------------------------
/// This is a template of a 'spectral scope' type plot, designed to show an
/// audio spectrum; it has an horizontal logarithmic frequency axis and a
/// vertical 'level' axis.
//----------------------------------------------------------------------------
template <class TArrayOfDataSeries, class TDataSerie>
class AFSScope : public AFScopeBase<TArrayOfDataSeries, TDataSerie>
{
 protected:
   AFAxis* m_pFreqAxis;

   virtual void UpdateVerticalAxis();
   
 public:   
   /// Returns a pointer to horizontal (Frequency) axis.
   AFAxis* GetFreqAxis () { return m_pFreqAxis; }

   /// Returns a pointer to horizontal (Frequency) axis.
   virtual AFAxis* GetHorzAxis() { return m_pFreqAxis; }

   /// The constructor.
   /// \param parent - parent window
   /// \param id - window identifier
   /// \param pos - window position
   /// \param size - window size
   AFSScope(wxWindow *parent,
		    wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize )
     : AFScopeBase<TArrayOfDataSeries, TDataSerie>(parent, id, pos, size),
       m_pFreqAxis(this->m_pTimeAxis) // Simply an alias...
    { m_pFreqAxis->SetName(wxT("Frequency")); }
};


// -------------------- AFSScope Template definitions -----------------------

template <class TArrayOfDataSeries, class TDataSerie>
void AFSScope<TArrayOfDataSeries, TDataSerie>::UpdateVerticalAxis()
{
    double dbFmin, dbFmax;
    m_pFreqAxis->GetRange(dbFmin, dbFmax);

    size_t unSerie;
    if(this->m_aDataSeries.GetCount() == 0) return;
    for(unSerie = 0; unSerie < this->m_aDataSeries.GetCount(); unSerie++)
    {
        if(this->m_aDataSeries[unSerie].IsShown())
        {
        	printf("[afsscope] fmin fmax : %.3f %.3f\n", dbFmin, dbFmax); fflush(stdout);
            // TODO :: manage log axis!!!!!!!!!!!!!            This is the only difference between AFScope and AFSScope v
            this->m_aDataSeries[unSerie].CalculateDataSerie(this->GetClientAreaWidth(), dbFmin, dbFmax, m_pFreqAxis->IsLog());
//          this->m_aDataSeries[unSerie].CalculateDataSerie(this->GetClientAreaWidth(), dbTmin, dbTmax);

            if(this->GetLegend())
            {
                this->GetLegend()->AddLabel(this->m_aDataSeries[unSerie].GetLabel(),
                                            this->m_aDataSeries[unSerie].GetLineColour());
            }
        }
    }
    
    if(this->m_bIsVertAutorangeOn)
    {
    	printf("[afsscope] autoranging\n"); fflush(stdout);
        double dbLmin = 1.0e+12, dbLmax = -1.0e-12;
//        this->m_pLevelAxis->GetRange(dbLmin, dbLmax);
        double dbLmin1 = 0, dbLmax1 = 0;
        this->Autorange(this->m_aDataSeries[0].GetData(),
                        this->m_aDataSeries[0].GetLength(),
                        dbLmin1, dbLmax1);

        for(unSerie = 1; unSerie < this->m_aDataSeries.GetCount(); unSerie++)
        {
            this->Autorange(this->m_aDataSeries[unSerie].GetData(),
                            this->m_aDataSeries[unSerie].GetLength(),
                            dbLmin1, dbLmax1);

            dbLmin = (dbLmin1 < dbLmin) ? dbLmin1 : dbLmin;
            dbLmax = (dbLmax1 > dbLmax) ? dbLmax1 : dbLmax;
        }
        this->m_pLevelAxis->SetRange(dbLmin, dbLmax);

    } else printf("[afsscope] NO autoranging\n"); fflush(stdout);    
}

#endif  // __AURORA_AFSCOPE_H__

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

