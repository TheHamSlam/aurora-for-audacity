/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  Common Libraries

  afcharts.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_AFCHARTS_H__
#define __AURORA_AFCHARTS_H__

#include "afdataplot.h"

//----------------------------------------------------------------------------
// AFChartBase
//----------------------------------------------------------------------------
//  This template act as a base class for bar and line charts class templates
//----------------------------------------------------------------------------

template <class TArrayOfDataSeries, class TDataSerie>
class AFChartBase: public AFDataPlot<TArrayOfDataSeries, TDataSerie>
{
  protected:
    AFAxis*             m_pLevelAxis;
    AFCategoriesAxis*   m_pCategoriesAxis;

    virtual void UpdateHorizontalAxis() {}
    virtual void UpdateVerticalAxis();

  public:

    AFAxis*           GetLevelAxis     () { return m_pLevelAxis; }
    AFCategoriesAxis* GetCategoriesAxis() { return m_pCategoriesAxis; }

    // --- ctors
    AFChartBase(wxWindow *parent, wxWindowID id,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize);
    ~AFChartBase() {}
};

// ------------------ AFChartBase Template definitions ------------------------

template<class TArrayOfDataSeries, class TDataSerie>
void AFChartBase<TArrayOfDataSeries, TDataSerie>::UpdateVerticalAxis()
{
    if(this->m_aDataSeries.GetCount() == 0) return;
    
    this->GetLegend()->Clear();

    size_t unSerie;
    for(unSerie = 0; unSerie < this->m_aDataSeries.GetCount(); unSerie++)
    {
    	if(this->m_aDataSeries[unSerie].IsShown())
        {
            this->GetLegend()->AddLabel(this->m_aDataSeries[unSerie].GetLabel(),
                                        this->m_aDataSeries[unSerie].GetLineColour());
        }
    }

    double dbLmin =  1.0e+12,
    	   dbLmax = -1.0e+12;

    if(this->m_bIsVertAutorangeOn)
    {

        double dbLmin1 = 1.0e+12, dbLmax1 = -1.0e+12;
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
    }
    else
    {
    	m_pLevelAxis->GetRange(dbLmin, dbLmax);
    }
    m_pLevelAxis->SetRange(dbLmin, dbLmax);
}


template<class TArrayOfDataSeries, class TDataSerie>
AFChartBase<TArrayOfDataSeries, TDataSerie>::AFChartBase(wxWindow *parent, wxWindowID id,
                                                         const wxPoint& pos, const wxSize& size)
 : AFDataPlot<TArrayOfDataSeries, TDataSerie>(parent, id, pos, size),
    m_pLevelAxis(0),
    m_pCategoriesAxis(0)
{
    this->m_pVertAxis = new AFAxis(wxVERTICAL);
    this->m_pHorzAxis = new AFCategoriesAxis();
    m_pLevelAxis      = static_cast<AFAxis*>(this->m_pVertAxis);
    m_pCategoriesAxis = static_cast<AFCategoriesAxis*>(this->m_pHorzAxis);
    
    this->m_bIsHorzRangeMutable = false; //The horizontal axis range cannot be changed!
}


//----------------------------------------------------------------------------
// AFBarPlot
//----------------------------------------------------------------------------
//  This is a template of a 'bar chart' type plot, where there is a categories
//  axis and a level axis.
//----------------------------------------------------------------------------
template <class TArrayOfDataSeries, class TDataSerie>
class AFBarPlot: public AFChartBase<TArrayOfDataSeries, TDataSerie>
{
 protected:

    void Draw(wxDC &dc);

  public:

    // --- ctors
    AFBarPlot(wxWindow *parent, wxWindowID id,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize)
     : AFChartBase<TArrayOfDataSeries, TDataSerie>(parent, id, pos, size)
    {}

    ~AFBarPlot() {}
};

// ------------------ AFBarPlot Template definitions ------------------------
template<class TArrayOfDataSeries, class TDataSerie>
void AFBarPlot<TArrayOfDataSeries, TDataSerie>::Draw(wxDC& dc)
{
    int nPlotWidth  = this->GetClientAreaWidth(),
        nPlotHeight = this->GetClientAreaHeight(),
        nXofs       = this->GetClientAreaHorzOffset() + int(this->m_pCategoriesAxis->GetCategoriesStart()),
        nYofs       = this->GetClientAreaVertOffset(),

        nShownSeriesCount = 0,
        nCategoriesCount  = int(this->m_pCategoriesAxis->GetCategoriesCount()),
        nCategoriesStep   = int(this->m_pCategoriesAxis->GetCategoriesStep());

    for(size_t un = 0; un < this->m_aDataSeries.GetCount(); un++)
        if(this->m_aDataSeries[un].IsShown())
            nShownSeriesCount++;

    wxPen   pen;
    wxBrush brush;

    // -------------------- Bars horizontal spacing things... --------------------

    int nBarHeight = 0,
        nBarWidth  = int( ceil(0.67*(nPlotWidth/(nShownSeriesCount* nCategoriesCount))));

    if( nBarWidth < 10)
        nBarWidth = 10; // 10 pixel is the minimum size

    int nBarSpace = 6, // px
        nBarsWidth = (nBarWidth*nShownSeriesCount + nBarSpace*(nShownSeriesCount-1)),
        nBarsSpace = nCategoriesStep - nBarsWidth;

    while(nBarsSpace < nBarSpace)
    {
        // Prevents bar groups overlap
        nBarSpace--;
        if(nBarWidth > 10) nBarWidth--;
        nBarsWidth = (nBarWidth*nShownSeriesCount + nBarSpace*(nShownSeriesCount-1));
        nBarsSpace = nCategoriesStep - nBarsWidth;
    }
    nXofs -= nBarsWidth/2;

    // -------------------- Bars vertical scaling things --------------------

    double dbYmax, dbYmin;
    this->m_pLevelAxis->GetRange(dbYmin, dbYmax);

    double dbYRange = dbYmax - dbYmin,
           dbYScale = nPlotHeight/dbYRange;

    int nZeroPos = int(dbYmax*nPlotHeight/dbYRange);


    wxRect wxrectBar(0,             // x
                     nYofs + ( (nZeroPos > nPlotHeight) ? nPlotHeight
                                                        : ((nZeroPos < 0) ? 0 : nZeroPos) ),     // y
                     nBarWidth,     // width
                     nPlotHeight);  // height

    // -------------------- Bars draw cycle --------------------
    int k;
    size_t unSerie;
    for(int nCat=0; nCat < nCategoriesCount; nCat++)
    {
        for(unSerie = 0, k= 0; unSerie < this->m_aDataSeries.GetCount(); unSerie++)
        {
            if(this->m_aDataSeries[unSerie].IsShown())
            {
                pen.SetColour(this->m_aDataSeries[unSerie].GetLineColour());
                brush.SetColour(this->m_aDataSeries[unSerie].GetFillColour());
                dc.SetPen(pen);
                dc.SetBrush(brush);

//                wxrectBar.x = nXofs + nCat*(nBarWidth + nBarSpace);
                wxrectBar.x = nXofs + nCat*(nBarsWidth + nBarsSpace) + k*(nBarWidth + nBarSpace);
                k++;

                nBarHeight = int( ceil(dbYScale * (this->m_aDataSeries[unSerie].GetData(nCat))) );

                if(nZeroPos > nPlotHeight)
                {
                    if(nBarHeight > 0)
                        nBarHeight -= nZeroPos - nPlotHeight;
                    else
                        nBarHeight += nZeroPos - nPlotHeight;
                }
                else if(nZeroPos < 0)
                {
                    if(nBarHeight > 0)
                        nBarHeight += nZeroPos;
                    else
                        nBarHeight -= nZeroPos;
                }

                // Bar clipping
                if((nBarHeight > 0) && (wxrectBar.y - nBarHeight) < nYofs)
                    nBarHeight = wxrectBar.y - nYofs;
                else if((nBarHeight < 0) && (wxrectBar.y - nBarHeight) > (nYofs + nPlotHeight))
                    nBarHeight = -(nYofs + nPlotHeight - wxrectBar.y);

                wxrectBar.height = -nBarHeight;

                dc.DrawRectangle(wxrectBar);
            }
        }
    }
}

//----------------------------------------------------------------------------
// AFLinePlot
//----------------------------------------------------------------------------
//  This is a template of a 'line chart' type plot, where there is a categories
//  axis and a level axis.
//----------------------------------------------------------------------------
template <class TArrayOfDataSeries, class TDataSerie>
class AFLinePlot: public AFChartBase<TArrayOfDataSeries, TDataSerie>
{
  protected:

    void Draw(wxDC &dc);

  public:

    // --- ctors
    AFLinePlot(wxWindow *parent, wxWindowID id,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize)
    : AFChartBase<TArrayOfDataSeries, TDataSerie>(parent, id, pos, size)
    {}

    ~AFLinePlot() {}
};

// ------------------ AFLinePlot Template definitions ------------------------

template<class TArrayOfDataSeries, class TDataSerie>
void AFLinePlot<TArrayOfDataSeries, TDataSerie>::Draw(wxDC& dc)
{
    int nPlotHeight      = this->GetClientAreaHeight(),
        nSeriesCount     = int(this->m_aDataSeries.GetCount()),
        nCategoriesCount = int(this->m_pCategoriesAxis->GetCategoriesCount()),
        nCategoriesStart = int(this->m_pCategoriesAxis->GetCategoriesStart()),
        nCategoriesStep  = int(this->m_pCategoriesAxis->GetCategoriesStep()),

        nXofs = this->GetClientAreaHorzOffset() + nCategoriesStart,
        nYofs = this->GetClientAreaVertOffset();

    double dbYmax, dbYmin;
    this->m_pLevelAxis->GetRange(dbYmin, dbYmax);

    double dbYRange = dbYmax - dbYmin,
           dbYScale = nPlotHeight/dbYRange;

    wxPen pen;

    int nX0, nY0, nX1, nY1;
    size_t unCat, unSerie;

    const double* pdbSerie;

    for(unSerie = 0; unSerie < size_t(nSeriesCount); unSerie++)
    {
        if(this->m_aDataSeries[unSerie].IsShown())
        {
            pen.SetColour(this->m_aDataSeries[unSerie].GetLineColour());
            dc.SetPen(pen);

            pdbSerie = this->m_aDataSeries[unSerie].GetData();

            nY0 = (int) ceil( dbYScale * (dbYRange - (pdbSerie[0]  - dbYmin)) );
            if(nY0 < 0) nY0 = 0;
            else if(nY0 > nPlotHeight)  nY0 = nPlotHeight;

            if(nY0 < 0) nY0 = 0;
            if(nY0 > nPlotHeight) nY0 = nPlotHeight - 1;

            for(unCat = 1; unCat < size_t(nCategoriesCount-1); unCat++, nY0 = nY1)
            {
                nX0 = nXofs + unCat*nCategoriesStep;
                nX1 = nX0 + nCategoriesStep;

                nY1 = (int) ceil( dbYScale * (dbYRange - (pdbSerie[unCat]  - dbYmin)) );
                if(nY1 < 0) nY1 = 0;
                else if(nY1 > nPlotHeight) nY1 = nPlotHeight;

                dc.DrawLine( nX0,
                             nYofs + ((nY0 < nPlotHeight) ? nY0 : nPlotHeight),
                             nX1,
                             nYofs + ((nY1 < nPlotHeight) ? nY1 :nPlotHeight) );
            }
        }
    }
}

#endif  // __AURORA_AFCHARTS_H__

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
