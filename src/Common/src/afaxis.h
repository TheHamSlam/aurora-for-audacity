/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  Common Libraries

  afaxis.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_AFAXIS_H__
#define __AURORA_AFAXIS_H__

#include <commdefs.h>

#ifndef __STAND_ALONE__
   #include <widgets/Ruler.h>
#endif

#ifdef __WXOSX__
   #define AXIS_TITLE_FONT_SIZE  10
   #define RULER_FONT_SIZE 10
#elif defined __WXMSW__
   #define PLOT_TITLE_FONT_SIZE  10
   #define AXIS_TITLE_FONT_SIZE   8
   #define RULER_FONT_SIZE  8
#else
// In GTK a smaller font looks better..
   #define AXIS_TITLE_FONT_SIZE  6
   #define RULER_FONT_SIZE 6
#endif

class AFPlotBase;

//----------------------------------------------------------------------------
// AFAxisBase
/// \brief The Aurora plot axis base class
/// This class manages all phisical axis properties. It encapsulates an
/// Audacity Ruler object.
//----------------------------------------------------------------------------

class AFAxisBase
{
  public:
	/// Orientation macros
	enum { RF_HORIZONTAL = wxHORIZONTAL,
		   RF_VERTICAL   = wxVERTICAL };

	/// Rulers types
	enum { RF_INT        = Ruler::IntFormat,
	       RF_REAL       = Ruler::RealFormat,
	       RF_REALLOG    = Ruler::RealLogFormat,
	       RF_TIME       = Ruler::TimeFormat,
	       RF_LINEARdB   = Ruler::LinearDBFormat/*,
	       RF_CATEGORIES*/
	     };

  protected:
	Ruler *m_pRuler;         ///< The ruler (taken from the Audacity widget, Ruler)

    int    m_nOrientation;   ///< Stores the axis orientation

    wxRect m_wxrectAxisBox,  ///< The entire axis bounding box
           m_wxrectRulerBox; ///< The ruler bounding box

    int  m_nRulerFormat;     ///< Stores the ruler format

    struct { bool    bShow;
             int     nLenght;
             wxPoint wxptOfs; } m_Grid;   ///< Grid properties

    struct { bool     bShow;
             wxString wxszLabel;
             wxFont   wxfntFont;
             wxPoint  wxptPos; } m_Title; ///< Axis title properties

    wxString m_wxszName,         ///< The axis name
             m_wxszMeasureUnit;  ///< The axis measure unit

    wxFont   m_wxfntMajor,       ///< Font for major labels
             m_wxfntMinor,       ///< Font for minor labels
             m_wxfntMinorMinor;  ///< Font for minor minor labels

  public:

    /// Get a pointer to the axis ruler
    /// \return A pointer to Audacity Ruler object
    Ruler* GetRuler() { return m_pRuler; }

    /// True, if is a category axis
    virtual bool IsCategories() { return false; }

    /// Check if the axis title is shown
    bool IsTitleOn()  const { return m_Title.bShow; }

    /// Set title visibility status
    void ShowTitle(const bool bValue = true) { m_Title.bShow = bValue; }

    /// Toggle title visibility status
    void ToggleTitle()  { m_Title.bShow = !m_Title.bShow; }

    /// Set axis title
    /// \param label - The title string
    void SetTitle(const wxString& label)  { m_Title.wxszLabel = label; }

    /// Set axis title
    /// \param label - The title string
    void SetTitle(const wxChar* label)   { m_Title.wxszLabel = label; }

    /// Set axis title font
    /// \param font - The choosed title font
    void SetTitleFont(wxFont& font)      { m_Title.wxfntFont = font; }

    /// Set ruler format
    /// \param nFormat - The selected format, one of RF_INT, RF_REAL, RF_REALLOG, RF_TIME, RF_LINEARdB
    virtual void SetFormat(const int nFormat);
    int  GetType()   const { return m_nRulerFormat; } // TO BE REMOVED

    /// Get current ruler format
    int  GetFormat() const { return m_nRulerFormat; }

    /// Check grid visibilty
    bool IsGridOn()   const { return m_Grid.bShow; }
    /// Set grid visibility
    void ShowGrid(const bool bValue = true)   { m_Grid.bShow = bValue; }

    /// Set ruler fontset
    void SetRulerFonts(const wxFont &wxfntMinor, const wxFont &wxfntMajor, const wxFont &wxfntMinorMinor);

    /// Set axis bounding box doing complete axis sizing.
    /// \param dc - axis device context
    /// \param wxrectBox - axis external edges
    /// \param nGridLength - length of grid lines (0 to turn off grid)
    void  SetBounds(wxDC& dc, wxRect& wxrectBox, int nGridLength = 0);
    /// Set axis bounding box doing complete axis sizing.
    /// \param dc - axis device context
    /// \param nLeft, nTop, nRight, nBottom - axis external edges
    /// \param nGridLength - length of grid lines (0 to turn off grid)
    void  SetBounds(wxDC& dc, int nLeft, int nTop, int nRight, int nBottom, int nGridLength = 0);

    /// Get axis bounding box
    wxRect& GetBounds     () { return m_wxrectAxisBox; }

    /// Get ruler bounding box (contained in the axis bounding box)
    wxRect& GetRulerBounds() { return m_wxrectRulerBox; }

    void   GetSize(int& nWidth, int& nHeight);
    wxSize GetSize();

    int  GetWidth (wxDC& dc);
    int  GetHeight(wxDC& dc);
    int  GetWidth () const { return m_wxrectAxisBox.width;  }
    int  GetHeight() const { return m_wxrectAxisBox.height; }

    wxString& GetName()                   { return m_wxszName; }
    void SetName(wxString& wxszName)      { m_wxszName = wxszName; }
    void SetName(const wxChar* pwxchName) { m_wxszName = pwxchName; }
    
    wxString& GetMeasureUnit()                 { return m_wxszMeasureUnit; }
    void SetMeasureUnit(wxString& wxszMu)      { m_wxszMeasureUnit = wxszMu; }
    void SetMeasureUnit(const wxChar* pwxchMu) { m_wxszMeasureUnit = pwxchMu; }

  protected:
    /// Draws axis titles
    void DrawTitles(wxDC& dc);

    /// Draws axis grid
    void DrawGrid(wxDC& dc);

  public:
    /// Empty method
    virtual void SetPixelRange(const int nMin, const int nMax) {}

    /// Empty method
    virtual void GetRange(double& dbMin, double& dbMax) {}

    /// Empty method
    virtual void SetRange(const double dbMin, const double dbMax) {}

    /// Draws everything.
    virtual void Draw(wxDC& dc);

public:
    /// The constructor.
    /// \param nOrientation - The axis orientation.
	AFAxisBase(const int nOrientation = RF_HORIZONTAL);
	virtual ~AFAxisBase();

};

//----------------------------------------------------------------------------
// AFAxis
/// \brief Generic continuous numbers axis.
/// This axis is designed to represent continuous set of real numbers, like a time
/// axis, for example. The axis can be linear or logarithmic as well.
//----------------------------------------------------------------------------
class AFAxis : public AFAxisBase
{
  protected:

    double m_dbMin,  ///< Lower number set extreme
           m_dbMax;  ///< Higher number set extreme
    bool   m_bIsLog; ///< Logarithmic flag

  private:
    void Update();

  public:
    /// This method takes two coordinates, convert them to the
    /// corresponding values represented in the ruler and set
    /// these values as new rulers extremes. It's a scaling
    /// function.
    /// \param nMin - lower coordinate
    /// \param nMax - higher coordinate
    void SetPixelRange(const int nMin, const int nMax);

    /// Set axis extremes.
    /// \param dbMin - lower coordinate
    /// \param dbMax - higher coordinate
    void SetRange(const double dbMin, const double dbMax);

    /// Set axis extremes and some other propertes.
    /// \param dbMin - lower coordinate
    /// \param dbMax - higher coordinate
    /// \param nFormat - ruler format, one of RF_INT, RF_REAL, RF_REALLOG, RF_TIME, RF_LINEARdB
    /// \param bIsLog - set logarithmic flag
    void SetRange(const double dbMin, const double dbMax, const int nFormat, const bool bIsLog = false);

    /// Get current axis range.
    void GetRange(double& dbMin, double& dbMax) { dbMin = m_dbMin, dbMax = m_dbMax; }

    /// Get axis lower extreme
    double& GetMin() { return m_dbMin; }

    /// Get axis higher extreme
    double& GetMax() { return m_dbMax; }

    bool IsLog() const { return m_bIsLog; }
    void SetLog(const bool bValue);

    void Draw(wxDC& dc);

    /// The constructor.
    /// \param nOrientation - The axis orientation.
	AFAxis(const int nOrientation = RF_HORIZONTAL);
};

//----------------------------------------------------------------------------
// AFCategoriesAxis
/// \brief Generic category axis.
/// This class is designed to manage a finite set of values, or categories,
/// like a spreadsheet chart.
//----------------------------------------------------------------------------
class AFCategoriesAxis : public AFAxisBase
{
  protected:

	/// Categories properties.
    struct {wxArrayString awxszLabels;
    	    int           nCount;
            int           nStart;
            int           nStep; } m_Categories;

  public:
    /// Of course always true (Deprecated)
    bool IsCategories() { return true; }

    /// Empty: in this class format setting has no effect.
    void SetFormat(const int nFormat) {}

    /// Add categories as array of wxChar.
    /// \param apwxchCat - the array
    /// \param unCount - the number of array's elements
    void AddCategories(const wxChar* apwxchCat[], const size_t unCount);

    /// Add categories as array of wxString
    /// \param awxszCat - the array
    void AddCategories(const wxArrayString& awxszCat);

    /// Get the number of stored categories
    int GetCategoriesCount() const { return m_Categories.nCount; }

    /// Get the position of the first categories element in the axis
    int GetCategoriesStart() const { return m_Categories.nStart; }

    /// Get the step between categories elements in the axis
    int GetCategoriesStep () const { return m_Categories.nStep; }

    virtual void Draw(wxDC& dc);

    /// The constructor.\n
    /// In the current implementation this type of axis can be only horizontal.
	AFCategoriesAxis();
	~AFCategoriesAxis() {}
};




#endif /* __AURORA_AFAXIS_H__ */

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
