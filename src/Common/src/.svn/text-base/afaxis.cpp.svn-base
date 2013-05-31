/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  Common Libraries

  afaxis.cpp

  Simone Campanini

**********************************************************************/

#include "afaxis.h"

//----------------------------------------------------------------------------
// AFAxisBase implementation
//----------------------------------------------------------------------------

void AFAxisBase::SetFormat(const int nFormat)
{
	wxASSERT_MSG(nFormat >= RF_INT && nFormat <= RF_LINEARdB,
			     wxT("AFAxisBase: Wrong format."));

	m_nRulerFormat = nFormat;
    m_pRuler->SetFormat((Ruler::RulerFormat)m_nRulerFormat);
}

void AFAxisBase::SetRulerFonts(const wxFont &wxfntMinor, const wxFont &wxfntMajor, const wxFont &wxfntMinorMinor)
{
	m_pRuler->SetFonts(wxfntMinor, wxfntMajor, wxfntMinorMinor);
}

void AFAxisBase::SetBounds(wxDC& dc, wxRect& wxrectBox, int nGridLength)
{
    SetBounds( dc,
    		   wxrectBox.x,
    		   wxrectBox.y,
    		   wxrectBox.x + wxrectBox.width,
    		   wxrectBox.y + wxrectBox.height,
    		   nGridLength );
}

void AFAxisBase::SetBounds(wxDC& dc, int nLeft, int nTop, int nRight, int nBottom, int nGridLength)
{
	int nWidth  = nRight - nLeft,
        nHeight = nBottom - nTop;

	// calculate ruler box size
    m_pRuler->GetMaxSize(&m_wxrectRulerBox.width, &m_wxrectRulerBox.height);

    m_wxrectRulerBox.x = nLeft;
    m_wxrectRulerBox.y = nTop;

    // calculate title size
    wxSize wxsizeTitle(0,0);
    if(m_Title.bShow)
    {
    	dc.SetFont(m_Title.wxfntFont);
    	wxsizeTitle = dc.GetTextExtent(m_Title.wxszLabel);
    }

    switch(m_nOrientation)
    {
        case wxHORIZONTAL:
        	m_wxrectRulerBox.width = nWidth;
    	    m_wxrectAxisBox = m_wxrectRulerBox;
    	    m_wxrectAxisBox.height += wxsizeTitle.GetHeight();
    	    break;

        case wxVERTICAL:
    	    m_wxrectRulerBox.height = nHeight;
    	    m_wxrectAxisBox = m_wxrectRulerBox;
    	    m_wxrectAxisBox.width += wxsizeTitle.GetHeight();
    	    m_wxrectRulerBox.x    += wxsizeTitle.GetHeight();
    	    break;
    }
/*
    printf("[ruler] w h: %d %d\n", m_wxrectRulerBox.width, m_wxrectRulerBox.height);
    printf("[canvas] l t r b: %d %d %d %d\n", nLeft, nTop, nRight, nBottom);
    printf("[ruler] l t r b: %d %d %d %d\n", m_wxrectRulerBox.x,
        		            m_wxrectRulerBox.y,
        		            m_wxrectRulerBox.x + m_wxrectRulerBox.width,
        		            m_wxrectRulerBox.y + m_wxrectRulerBox.height);
*/
    // If this is not a categories axis, set here the bounds
    if(!IsCategories())
        m_pRuler->SetBounds(m_wxrectRulerBox.x,
    	                    m_wxrectRulerBox.y,
    		                m_wxrectRulerBox.x + m_wxrectRulerBox.width,
    		                m_wxrectRulerBox.y + m_wxrectRulerBox.height);

	switch(m_nOrientation)
	{
		case wxHORIZONTAL:
		{
			if(m_Title.bShow)
			{
				m_Title.wxptPos.x = m_wxrectRulerBox.x + (m_wxrectRulerBox.width - wxsizeTitle.GetWidth())/2;
				m_Title.wxptPos.y = m_wxrectRulerBox.GetBottom();
			}
			if(m_Grid.bShow)
			{
				m_Grid.nLenght   = -nGridLength;        // m_nHeight - (m_nTBorder + m_nBBorder)
				m_Grid.wxptOfs.x = m_wxrectRulerBox.x;  // m_nLBorder
				m_Grid.wxptOfs.y = nTop;                // m_nTBorder + 1
			}
		}
		break;

		case wxVERTICAL :
		{
			if(m_Title.bShow)
			{
				m_Title.wxptPos.x = m_wxrectAxisBox.x;
				m_Title.wxptPos.y = m_wxrectAxisBox.y  + (m_wxrectAxisBox.height + wxsizeTitle.GetWidth())/2;
			}
			if(m_Grid.bShow)
			{
				m_Grid.nLenght   = nGridLength; // (m_nWidth  - (m_nLBorder + m_nRBorder)) - 2,
				m_Grid.wxptOfs.x = m_wxrectRulerBox.x + m_wxrectRulerBox.width; // m_nLBorder + 1,
				m_Grid.wxptOfs.y = nTop;                                        // m_nTBorder
			}
		}
		break;
    }
//	printf("[title] x y : %d %d\n", m_Title.wxptPos.x, m_Title.wxptPos.y);
//	printf("[grid] l x y : %d %d %d\n\n", m_Grid.nLenght, m_Grid.wxptOfs.x, m_Grid.wxptOfs.y); fflush(stdout);
}

void AFAxisBase::GetSize(int& nWidth, int& nHeight)
{
    nWidth  = m_wxrectAxisBox.GetWidth();
    nHeight = m_wxrectAxisBox.GetHeight();
}

wxSize AFAxisBase::GetSize()
{
    wxSize sz(m_wxrectAxisBox.GetWidth(),
    		  m_wxrectAxisBox.GetHeight());
    return sz;
}

int  AFAxisBase::GetWidth(wxDC& dc)
{
    m_pRuler->GetMaxSize(&m_wxrectRulerBox.width, &m_wxrectRulerBox.height);

    if(m_nOrientation == wxVERTICAL)
    {
        // calculate title size
        wxSize wxsizeTitle(0,0);
        if(m_Title.bShow)
        {
    	    dc.SetFont(m_Title.wxfntFont);
    	    wxsizeTitle = dc.GetTextExtent(m_Title.wxszLabel);
        }

  	    m_wxrectAxisBox = m_wxrectRulerBox;
        m_wxrectAxisBox.width += wxsizeTitle.GetHeight();
    }
	return m_wxrectAxisBox.width;
}

int  AFAxisBase::GetHeight(wxDC& dc)
{
    m_pRuler->GetMaxSize(&m_wxrectRulerBox.width, &m_wxrectRulerBox.height);

    if(m_nOrientation == wxHORIZONTAL)
    {
        // calculate title size
        wxSize wxsizeTitle(0,0);
        if(m_Title.bShow)
        {
    	    dc.SetFont(m_Title.wxfntFont);
    	    wxsizeTitle = dc.GetTextExtent(m_Title.wxszLabel);
        }

  	    m_wxrectAxisBox = m_wxrectRulerBox;
        m_wxrectAxisBox.height += wxsizeTitle.GetHeight();
    }
	return m_wxrectAxisBox.height;
}

void AFAxisBase::DrawTitles(wxDC& dc)
{
	if(m_Title.bShow)
	{
		dc.SetFont(m_Title.wxfntFont);
		switch(m_nOrientation)
		{
		    case wxHORIZONTAL:
	            dc.DrawText( m_Title.wxszLabel,
	                         m_Title.wxptPos.x,
	                         m_Title.wxptPos.y );
	            break;

		    case wxVERTICAL :
	            dc.DrawRotatedText( m_Title.wxszLabel,
	            		            m_Title.wxptPos.x,
	            		            m_Title.wxptPos.y,
	                                90.0 );
	            break;
	    }
	}
}

void AFAxisBase::DrawGrid(wxDC& dc)
{
    if(m_Grid.bShow)
    	m_pRuler->DrawGrid( dc,
    			            m_Grid.nLenght,
                            true,
                            true,
                            m_Grid.wxptOfs.x,
                            m_Grid.wxptOfs.y );
}

void AFAxisBase::Draw(wxDC& dc)
{
	DrawTitles(dc);
    DrawGrid(dc);
    m_pRuler->Draw(dc);
}

AFAxisBase::AFAxisBase(const int nOrientation)
  : m_pRuler(0),
    m_nOrientation(nOrientation),
    m_wxrectAxisBox(0,0,100,100),  m_wxrectRulerBox(0,0,100,100), // x,y,w,h
    m_nRulerFormat(RF_INT),
    m_wxszName(wxT("Name")),  m_wxszMeasureUnit(wxT(" ")),
    m_wxfntMajor(RULER_FONT_SIZE, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD),
    m_wxfntMinor(RULER_FONT_SIZE, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
    m_wxfntMinorMinor(RULER_FONT_SIZE-1, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL)
{
	m_Grid.bShow     = false;
	m_Grid.nLenght   = 0;
	m_Grid.wxptOfs.x = 0;
	m_Grid.wxptOfs.y = 0;

	m_Title.bShow = false;
	m_Title.wxszLabel = wxT("Axis title");
	m_Title.wxfntFont.SetPointSize(AXIS_TITLE_FONT_SIZE);
	m_Title.wxfntFont.SetFamily(wxFONTFAMILY_SWISS);
	m_Title.wxfntFont.SetStyle(wxFONTSTYLE_NORMAL);
	m_Title.wxfntFont.SetWeight(wxFONTWEIGHT_NORMAL);
	m_Title.wxptPos.x = 0;
	m_Title.wxptPos.y = 0;

	m_pRuler = new Ruler();
	m_pRuler->SetOrientation(m_nOrientation); // required
	m_pRuler->SetBounds(0, 0, 100, 100);      // required
	m_pRuler->SetRange(0.0, 100.0);           // required

	if(m_nOrientation == wxHORIZONTAL)
		m_pRuler->SetFlip(true); // usually the x ruler stays on bottom

	m_pRuler->SetFonts(m_wxfntMinor, m_wxfntMajor, m_wxfntMinorMinor);
}

AFAxisBase::~AFAxisBase()
{
	if(m_pRuler) delete m_pRuler;
}

//----------------------------------------------------------------------------
// AFAxis implementation
//----------------------------------------------------------------------------
void AFAxis::Update()
{
	if(m_nOrientation == wxVERTICAL)
		m_pRuler->SetRange(m_dbMax, m_dbMin);
	else
		m_pRuler->SetRange(m_dbMin, m_dbMax);

	m_pRuler->SetLog(m_bIsLog);
}

void AFAxis::SetPixelRange(const int nMin, const int nMax)
{
	if(m_bIsLog)
    {
        double dbLength = (m_nOrientation == wxVERTICAL) ? double(m_wxrectRulerBox.height)
                                                         : double(m_wxrectRulerBox.width);
        double dbMin = pow(m_dbMax/m_dbMin, nMin/dbLength) * m_dbMin;
        m_dbMax = pow(m_dbMax/m_dbMin, nMax/dbLength) * m_dbMin;
        m_dbMin = dbMin;
    }
    else
	{
        double dbScale = (m_nOrientation == wxVERTICAL) ? (m_dbMax-m_dbMin)/m_wxrectRulerBox.height
                                                        : (m_dbMax-m_dbMin)/m_wxrectRulerBox.width;
        double dbMin = m_dbMin;
        m_dbMin = nMin * dbScale + dbMin;
		m_dbMax = nMax * dbScale + dbMin;
	}
    //printf("[afaxis] scaled to %f %f", m_dbMin, m_dbMax); fflush(stdout);
}

void AFAxis::SetRange(const double dbMin, const double dbMax)
{
	m_dbMin = dbMin, m_dbMax = dbMax;
	//printf("[afaxis] got %.3f %.3f\n", m_dbMin, m_dbMax); fflush(stdout);
}

void AFAxis::SetRange(const double dbMin, const double dbMax, const int nFormat, const bool bIsLog)
{
	m_dbMin = dbMin, m_dbMax = dbMax;
	if(nFormat >= 0)
		SetFormat(nFormat);
	SetLog(bIsLog);
}

void AFAxis::SetLog(const bool bValue)
{
	m_bIsLog = bValue;
	if(m_bIsLog && (m_dbMin == 0.0))
	{
		// This is necessary, otherwise there is the
		// possibility of division by 0 error
		m_dbMin = 1.0;
	    while(m_dbMin >= m_dbMax) m_dbMin /= 10.0;
	}
}

void AFAxis::Draw(wxDC& dc)
{
	Update();
	DrawTitles(dc);
    DrawGrid(dc);
    m_pRuler->Draw(dc);
}

AFAxis::AFAxis(const int nOrientation)
  :  AFAxisBase(nOrientation),
     m_dbMin(0), m_dbMax(100), m_bIsLog(false)
{
	m_pRuler->SetRange(m_dbMin, m_dbMax);
}


//----------------------------------------------------------------------------
// AFCategoriesAxis implementation
//----------------------------------------------------------------------------

void AFCategoriesAxis::AddCategories(const wxChar* apwxchCat[], const size_t unCount)
{
	//m_awxszCategories.Alloc(unCount);
	wxString wxszCat;
	for(size_t un = 0; un < unCount; un++)
	{
		wxszCat = apwxchCat[un];
		m_Categories.awxszLabels.Add(wxszCat);
	}
	m_Categories.nCount = int(m_Categories.awxszLabels.GetCount());
}

void AFCategoriesAxis::AddCategories(const wxArrayString& awxszCat)
{
	for(size_t un = 0; un < awxszCat.GetCount(); un++)
	{
		m_Categories.awxszLabels.Add(awxszCat[un]);
	}
	m_Categories.nCount = int(m_Categories.awxszLabels.GetCount());
}

void AFCategoriesAxis::Draw(wxDC& dc)
{
	wxASSERT_MSG(m_Categories.nCount > 0,
				 wxT("AFCategoriesAxis: No categories present."));

    m_Categories.nStep  = GetWidth()/m_Categories.nCount;   // labels step
	m_Categories.nStart = m_Categories.nStep/2;             // labels start coordinate

	//The following call is needed, because the Custom Ruler
    //functions are buggy: they never invalidata the device
    //context, so labels coordinates won't be updated.
	//A call to SetCustomMajorLabels reset everything but
	//don't force the label positions calculus. This
	//SetBounds, followed with another SetBounds with real
	//parameters cause the device context invalidation.
	//This problem cause to me a big waste of time and
	//some shame....[sc]
	m_pRuler->SetBounds(0, 0, GetWidth(), GetHeight());

	m_pRuler->SetCustomMode(true);
	m_pRuler->SetCustomMajorLabels( &m_Categories.awxszLabels,
					                 m_Categories.nCount,
									 m_Categories.nStart,
									 m_Categories.nStep );
    // l t r b
    m_pRuler->SetBounds(m_wxrectRulerBox.x,
    		            m_wxrectRulerBox.y,
    		            m_wxrectRulerBox.x + m_wxrectRulerBox.width,
    		            m_wxrectRulerBox.y + m_wxrectRulerBox.height);
	DrawTitles(dc);
	DrawGrid(dc);
	m_pRuler->Draw(dc);
}

// --- 'ctors
AFCategoriesAxis::AFCategoriesAxis()
  : AFAxisBase(wxHORIZONTAL)
{
	m_Categories.nCount =  0;
	m_Categories.nStart =  0;
	m_Categories.nStep  = 10;

//	m_pRuler->SetCustomMode(true); // it cannot be set here...
    m_pRuler->SetMinor(false);
    m_pRuler->SetLog(false);
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

