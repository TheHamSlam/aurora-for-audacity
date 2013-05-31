/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common Libraries
  
  afplot.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_AFPLOT_H__
#define __AURORA_AFPLOT_H__

#include <wxcmn.h>
#include <commdefs.h>

#include <wx/dcbuffer.h>

#ifndef __STAND_ALONE__
   #include <widgets/Ruler.h>
#endif

#include "afaxis.h"

// Some defines...
#define DECAY_PLOT_X_SIZE 540 // To be removed
#define DECAY_PLOT_Y_SIZE 250 // To be removed

#ifdef __WXOSX__
   #define PLOT_TITLE_FONT_SIZE  12
   #define AXIS_TITLE_FONT_SIZE  10
   #define LEGEND_FONT_SIZE      10
   #define DECAY_RULER_FONT_SIZE 10
#elif defined __WXMSW__
   #define PLOT_TITLE_FONT_SIZE  10
   #define AXIS_TITLE_FONT_SIZE   8
   #define LEGEND_FONT_SIZE       8
   #define DECAY_RULER_FONT_SIZE  8
#else
// In GTK a smaller font looks better..
   #define PLOT_TITLE_FONT_SIZE  8
   #define AXIS_TITLE_FONT_SIZE  6
   #define LEGEND_FONT_SIZE      6
   #define DECAY_RULER_FONT_SIZE 6
#endif

//----------------------------------------------------------------------------
// AFLegendEntry
/// \brief A plot legend item.
/// This class encapsulate a plot legend entry.
//----------------------------------------------------------------------------
class AFLegendEntry
{
  private:
	wxString m_wxszLabel;   ///< The legend label
	wxColour m_wxcolColour; ///< The plot color for this entry

  public:
	void SetLabel (wxString& wxszLabel)      { m_wxszLabel = wxszLabel; }
	void SetLabel (const wxChar* pwxchLabel) { m_wxszLabel = pwxchLabel; }
	void SetColour(const wxColour& wxcol)    { m_wxcolColour = wxcol; }

	wxString& GetLabel()  { return m_wxszLabel; }
	wxColour& GetColour() { return m_wxcolColour; }

	/// The default constructor
	AFLegendEntry()
     : m_wxszLabel(wxT("")), m_wxcolColour(wxNullColour) {}

	/// A constructor for complete legend entry creation.
	AFLegendEntry(wxString& wxszLabel, wxColour& wxcolColour)
	 : m_wxszLabel(wxszLabel), m_wxcolColour(wxcolColour) {}

	/// Another constructor for complete legend entry creation.
	AFLegendEntry(const wxChar* pwxchLabel, wxColour& wxcolColour)
	 : m_wxszLabel(pwxchLabel), m_wxcolColour(wxcolColour) {}
};
WX_DECLARE_OBJARRAY(AFLegendEntry, TArrayOfAFLegendEntry);

//----------------------------------------------------------------------------
// AFLegend
/// \brief The plot legend.
/// This class manage the legend entries and draw itself on the plot canvas.
//----------------------------------------------------------------------------
// sizes in pixel
#define LGD_MARGIN     5
#define LGD_BORDER     10
#define LGD_LINE_WIDTH 10

class AFLegend
{
  public:
	/// The four possible legend positions in the plot canvas.
	enum { TOP_LEFT = 100, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT };

  private:
	int    m_nPosition;            ///< The position

	wxRect m_wxrectBox;           ///< The bounding box
    wxSize m_wxsizeMaxLabelsDims; ///< Maximum sizes

	wxFont m_wxfntFont;           ///< The legend font
	bool   m_bShow;               ///< Visibility flag

	TArrayOfAFLegendEntry m_aEntries; ///< Legend items array

	/// Given the device context, this methods finds maximum width
	/// and height between all legend entries then stores them.
	void FindMaxLabelsDims(wxDC& dc);

  public:
	/// Clear the legend item array
	void Clear()    { if(m_aEntries.GetCount() > 0) m_aEntries.Clear(); }

	/// Add new item in the legend array
	void AddLabel   (wxString& wxszLabel, const wxColour& wxcolBrush = wxNullColour);

	/// Add new item in the legend array
	void AddLabel   (const wxChar* pwxchLabel, const wxColour& wxcolBrush = wxNullColour);

	/// Removes an existing item in the legend array
	void RemoveLabel(const int nIdx);

	/// Visibility check
	bool IsShown() const { return m_bShow; }

	/// Set visibility flag
	void Show(const bool bValue = true) { m_bShow = bValue; }

	/// Set legend position
	/// \param nPos - position, one of TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT
	void SetPosition(const int nPos)    {m_nPosition = nPos; }

	/// Draws the legend.
	/// \param dc - the device context
	/// \param wxrectClientArea - plot canvas bounding box
	void Draw(wxDC& dc, wxRect& wxrectClientArea);

	/// The constructor.
	/// \param nPosition - legend position in the plot canvas.
	AFLegend(const int nPosition = TOP_RIGHT);
};

//----------------------------------------------------------------------------
// AFPlotBase
//
/// \brief The Aurora plot base class.
/// All Aurora plots are based on this class, so it's designed to be quite
/// flexible and complete. It has contextual menu in the plot area with
/// clipboard copy, drag zoom, autorange and contextual menus in both horizontal
/// and vertical axes.\n
/// Anyway, this class shouldn't be instantiated directly, use, instead,
/// AFScope(), AFSScope(), AFChart(), AFBarPlot().
//----------------------------------------------------------------------------
class AFPlotBase: public wxControl
{
 public:
   /// Events IDs.
   enum { ID_COPY_BITMAP = 0X3000, ID_COPY_VECTORIAL,
          ID_SHOW_LEGEND_MCHK,
	      ID_SET_X_AXIS_RANGE,     ID_SET_Y_AXIS_RANGE,
	      ID_X_AUTORANGE_MCHK,     ID_Y_AUTORANGE_MCHK,
	      ID_SET_X_AXIS_DLG,       ID_SET_Y_AXIS_DLG };

 private:
    wxWindow* m_pwxwndParent;  ///< The plot parent window, usually a wxPanel or wxScrolledWindow.

    wxRect m_wxEnvRect;        ///< The entire plot bounding box (Maybe quite unused...).

    struct { bool     bShow;
             wxString wxszLabel;
             wxFont   wxfntFont; } m_Title; ///< Plot title properties
    
    wxColour m_wxcolCanvas,     ///< Canvas color.
             m_wxcolBackground, ///< Drawing area background color.
             m_wxcolBorders;    ///< Borders color.

 protected:
    AFAxisBase *m_pHorzAxis,  ///< The horizontal axis.
               *m_pVertAxis;  ///< The vertial axis.

    AFLegend   *m_pLegend;    ///< The legend.

    wxRect  m_wxrectClientArea; ///< The drawing area bounding box.

    int m_nWidth,               ///< The entire plot width
        m_nHeight;              ///< The entire plot height

    // Borders contain rulers and titles
    int m_nTBorder,            ///< Top border width.
        m_nBBorder,            ///< Bottom border width.
        m_nLBorder,            ///< Left border width.
        m_nRBorder;            ///< Right border width.

    bool m_bIsTBorderOn,       ///< Top border flag.
         m_bIsRBorderOn;       ///< Right border flag.

    bool m_bIsHorzAutorangeOn, ///< Horizontal axis autorange flag.
         m_bIsVertAutorangeOn; ///< Vertical axis autorange flag.
    
    bool m_bIsHorzRangeMutable, ///< False if horizontal is a categories axis.
         m_bIsVertRangeMutable; ///< False if vertical is a categories axis.

   /// Find maximum and minimum in a given data serie.
   /// \param pdbSerie - the data serie vector
   /// \param unLength - data serie vector length
   /// \param dbMin - the minimum value
   /// \param dbMax - the maximum value
   /// \param bIsLog - logarithmic flag...actually not working!!!
   virtual void Autorange(const double* pdbSerie, const size_t unLength,
		                  double& dbMin, double& dbMax, const bool bIsLog = false);

   /// Called in Draw(), if something has been changed since the last redraw,
   /// it have to recalculate vertical axis range.
   virtual void UpdateVerticalAxis  () = 0;

   /// Called in Draw(), if something has been changed since the last redraw,
   /// it have to recalculate horizontal axis range.
   virtual void UpdateHorizontalAxis() = 0;

   // --- Event handlers
   void OnPaint(wxPaintEvent& event);
   void OnRightButtonClick(wxMouseEvent& evt);
#if wxUSE_METAFILE
   void OnCopyVectorial(wxCommandEvent& evt);
#endif
   void OnShowSetXAxisRange(wxCommandEvent& evt);
   void OnShowSetYAxisRange(wxCommandEvent& evt);
   void OnXAutorangeMenuCheck(wxCommandEvent& evt);
   void OnYAutorangeMenuCheck(wxCommandEvent& evt);
   void OnShowLegendMenuCheck(wxCommandEvent& evt);

   void OnCopyBitmap(wxCommandEvent& evt);
   void OnChar(wxKeyEvent& evt);

   void OnMouseStartSelection(wxMouseEvent& evt);
   void OnMouseSelection(wxMouseEvent& evt);
   void OnMouseEndSelection(wxMouseEvent& evt);

   /// This pure virtual method should contains
   /// all the plot routines and MUST be implemented!
   virtual void Draw(wxDC& dc) = 0;

  private:
   /// This method inits the device context and calls Draw()
   /// \param dc - the device context
   /// \param sz - the window size.
   void UpdatePlot(wxDC& dc, const wxSize& sz);

   wxRect m_wxrectSelection; ///< The ruler selection region.
   bool   m_bIsSelectionOn;  ///< True when the user starts a drag selection action.

   /// Draws the selection region in the rulers.
   void   DrawSelectionRegion(wxDC& dc);

  public:

   // Plot dimensions
    int   GetWidth()                      const { return m_nWidth; }
    int   GetHeight()                     const { return m_nHeight; }
    int   GetClientAreaWidth()            const { return (m_nWidth  - (m_nLBorder + m_nRBorder)); }
    int   GetClientAreaHeight()           const { return (m_nHeight - (m_nTBorder + m_nBBorder)); }
    void  GetClientAreaSize(wxSize& size) const { size = wxSize(GetClientAreaWidth(),
                                                                GetClientAreaHeight()); }
    // Get client area top left coordinate
    int  GetClientAreaHorzOffset()         const { return m_nLBorder; }
    int  GetClientAreaVertOffset()         const { return m_nTBorder; }
    void GetClientAreaOffset(wxPoint& ofs) const { ofs.x = m_nLBorder;
                                                   ofs.y = m_nTBorder;}

    bool IsTopBorderOn()   const { return m_bIsTBorderOn; }
    bool IsRightBorderOn() const { return m_bIsRBorderOn; }

    void SetTopBorder(const bool bValue)    { m_bIsTBorderOn = bValue; }
    void SetRightBorder(const bool bValue)  { m_bIsRBorderOn = bValue; }

   // Plot attributes
   bool IsTitleOn () const                    { return m_Title.bShow; }
   void ShowTitle (const bool bValue = true)  { m_Title.bShow     = bValue; }
   void SetTitle  (const wxString& wxszTitle) { m_Title.wxszLabel = wxszTitle; }
   void SetTitle  (const wxChar* pwxchTitle)  { m_Title.wxszLabel = pwxchTitle; }
    
   void SetCanvasColour(wxColour& col)     { m_wxcolCanvas = col; }
   void SetBackgroundColour(wxColour& col) { m_wxcolBackground = col; }
   void SetBorderColour(wxColour& col)     { m_wxcolBorders = col; }
    
   /// Assign an horizontal axis to plot that owns it.
   void SetHorizontalAxis(AFAxisBase* pab) { m_pHorzAxis = pab; }

   /// Assign a vertical axis to plot that owns it.
   void SetVerticalAxis  (AFAxisBase* pab) { m_pVertAxis = pab; }

   /// Return a pointer to horizontal axis.
   AFAxisBase* GetHorizontalAxis() const { return m_pHorzAxis; }

   /// Return a pointer to vertical axis.
   AFAxisBase* GetVerticalAxis  () const { return m_pVertAxis; }

   bool IsHorzAxisAutorangeOn() const           { return m_bIsHorzAutorangeOn; }
   bool IsVertAxisAutorangeOn() const           { return m_bIsVertAutorangeOn; }
   void SetHorzAxisAutorange(const bool bValue) { m_bIsHorzAutorangeOn = (m_bIsHorzRangeMutable) ? bValue : false; }
   void SetVertAxisAutorange(const bool bValue) { m_bIsVertAutorangeOn = (m_bIsVertRangeMutable) ? bValue : false; }
    

   /// Return a pointer to the legend object.
   AFLegend* GetLegend ();

   /// Set legend visibility flag and redraw.
   void      ShowLegend(const bool bValue = true);

   /// The constructor.\n
   /// \param parent - parent window
   /// \param id - window identifier
   /// \param pos - window position
   /// \param size - window size
   /// \param style - window style.
   AFPlotBase(wxWindow* parent, wxWindowID id,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              const long style   = wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE);
   ~AFPlotBase();
};


//----------------------------------------------------------------------------
// SetAxisRangeDialog
/// \brief The dialog invoked from rulers contextual menu.
/// This dialog let the user choose the new axis extremes.
//----------------------------------------------------------------------------
#include <wx/statline.h>
class SetAxisRangeDialog : public wxDialog
{
  private:
	enum
	{
		ID_MIN_TC = 1000,
		ID_MIN_MU_ST,
		ID_MAX_MU_ST,
	};

	AFAxisBase* m_pAxis;

	int    m_nId;

	double m_dbMin,
	       m_dbMax;

    wxPanel*      m_pwxpnlUpper;
	wxStaticText* m_pwxstMinLbl;
	wxTextCtrl*   m_pwxtcMin;
	wxStaticText* m_pwxstMinMu;
	wxStaticText* m_pwxstMaxLbl;
	wxTextCtrl*   m_pwxtcMax;
	wxStaticText* m_pwxstMaxMu;
	wxStaticLine* m_staticline3;
	wxPanel*      m_pwxpnlLower;
	wxButton*     m_pwxbtnCancel;
	wxButton*     m_pwxbtnOk;

  protected:

	void OnCancel ( wxCommandEvent& event );
	void OnOk     ( wxCommandEvent& event );

  public:
    /// The constructor.
    /// \param parent - parent window
    /// \param id - window identifier
    /// \param pAxis - the axis to be modified
	/// \param title - the dialog title
    /// \param pos - window position
    /// \param size - window size
    /// \param style - window style.
    SetAxisRangeDialog(wxWindow* pParent,
    		           wxWindowID id,
    		           AFAxisBase* pAxis,
                       const wxString& title = wxT("Set Axis Range"), 
                       const wxPoint&    pos = wxDefaultPosition,
                       const wxSize&    size = wxDefaultSize,
                       long style = wxDEFAULT_DIALOG_STYLE);
};
#endif  // __AURORA_AFPLOT_H__

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


