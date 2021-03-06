/**********************************************************************
 *
 *  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 *                       plugin collection
 *
 *  Common libraries
 *
 *  gpfuncts.cpp
 *
 *  Simone Campanini 2011
 *
 **********************************************************************/
#include <wx/settings.h>

#include "gpfuncts.h"

// Octave band labels array
const wxChar* g_awxpchBandLabels[] = {
	wxT("31.5"), wxT("63"), wxT("125"), wxT("250"), wxT("500"),
	wxT("1k"),   wxT("2k"), wxT("4k"),  wxT("8k"),  wxT("16k"),
	wxT("A"),    wxT("Lin")
};

const wxChar* g_awxpchThirdOctaveBandLabels[] = {
	wxT("25"),   wxT("31.5"),  wxT("40"),    wxT("50"),   wxT("63"),
	wxT("80"),   wxT("100"),   wxT("125"),   wxT("160"),  wxT("200"),
	wxT("250"),  wxT("315"),   wxT("400"),   wxT("500"),  wxT("630"),
	wxT("800"),  wxT("1k"),    wxT("1.25k"), wxT("1.6k"), wxT("2k"),
	wxT("2.5k"), wxT("3.15k"), wxT("4k"),    wxT("5k"),   wxT("6.3k"),
	wxT("8k"),   wxT("10k"),   wxT("12.5k"), wxT("16k"),  wxT("20k"),
	wxT("A"),    wxT("Lin")
};

// Octave band center frequencies array
const double g_adbOctaveBandFcb[] = {
    31.5,    63.0,  125.0,  250.0,  500.0, 1000.0,  2000.0, 4000.0, 8000.0, 16000.0,
    11000.0, 11000.0
};

const double g_adbOneThirdOctaveBandFcb[] = {
                               25.0,   31.5,   40.0,   50.0,   63.0,   80.0,   100.0,
	125.0,   160.0,   200.0,   250.0,  315.0,  400.0,  500.0,  630.0,  800.0,  1000.0,
	1250.0,  1600.0,  2000.0,  2500.0, 3150.0, 4000.0, 5000.0, 6300.0, 8000.0, 10000.0,
	12500.0, 16000.0, 20000.0,
    12000.0, 12000.0
};


const wxChar* AuroraGetBandLabel(const int nBand, const int type)
{ 
	if(type == 3)
	    return AuroraGetThirdOctaveBandLabel(nBand);

	return AuroraGetOctaveBandLabel(nBand);
}

const wxChar* AuroraGetOctaveBandLabel(const int nBand)
{
    if(nBand < 0 || nBand > 11)
    { return wxT("---"); }

    switch(nBand)
    {
        case 10: // A
            return wxT("A");
        case 11: // Lin
            return wxT("Lin");
        default:
        	return g_awxpchThirdOctaveBandLabels[3*nBand + 1];
    }
    return wxT("---");
}

const wxChar* AuroraGetThirdOctaveBandLabel(const int nBand)
{
    if(nBand < 0 || nBand > 31)
    { return wxT("---"); }

    switch(nBand)
    {
        case 30: // A
            return wxT("A");
        case 31: // Lin
            return wxT("Lin");
        default:
        	return g_awxpchThirdOctaveBandLabels[nBand];
    }
    return wxT("---");
}

const double AuroraGetOctaveBandFcb(const int nBand)
{
    if(nBand < 0 || nBand > 11)
    { return 0.0; }

    switch(nBand)
    {
        case 10: // A
        case 11: // Lin
            return 12000.0;
        default:
        	return g_adbOneThirdOctaveBandFcb[3*nBand + 1];
    }
    return 0.0;
}

const double AuroraGetThirdOctaveBandFcb(const int nBand)
{
    if(nBand >= 0 && nBand < 32)
        return g_adbOneThirdOctaveBandFcb[nBand];
    return 0.0;
}

// Generate Module version numbert
wxString AuroraModuleVersionNumber(const int nType, const int nRc)
{
	wxDateTime wxdtNow;
	wxdtNow.ParseDate(wxT(__DATE__));

	wxString wxszVersion;
	wxszVersion << wxdtNow.GetYear() - 2000 << wxT(".");
	wxszVersion << wxdtNow.GetMonth() << wxT(".");
	wxszVersion << wxdtNow.GetDay();

	switch(nType)
	{
	    case ART_ALPHA: wxszVersion << wxT("-alpha");     break;
	    case ART_BETA:  wxszVersion << wxT("-beta");      break;
	    case ART_RC:    wxszVersion << wxT("-RC") << nRc; break;
	}

	return wxszVersion;
}

// Various utilities
long TextPtrToLong(wxTextCtrl* pTc)
{
    long l = 0;
    wxString str;
    
    if(!pTc->IsEmpty())
        str = pTc->GetValue();
    
    if(str.ToLong(&l)) return int(l);
    else return 0;
}

int TextPtrToInt(wxTextCtrl* pTc)
{
    return int(::TextPtrToLong(pTc));
}

double TextPtrToDouble(wxTextCtrl* pTc)
{
    double d = 0.0;
    wxString str;
    
    if(!pTc->IsEmpty())
        str = pTc->GetValue();
    
    if(str.ToDouble(&d)) return d;
    else return 0.0;
}

double StringToDouble(wxString& str)
{
    double d = 0.0;
    if(str.ToDouble(&d)) return d;
    else return 0.0;
}

long StringToLong(wxString& str)
{
   long l = 0;
   if(str.ToLong(&l)) return l;
   else return 0;
}

int StringToInt(wxString& str)
{
   long l = 0;
   if(str.ToLong(&l)) return int(l);
   else return 0;
}

int AuroraNearTwoPower(const double dbValue)
{
    int nExp = 0;
    while(dbValue > pow(2.0, double(nExp++)));
    return int(pow(2.0, --nExp));
}

int AuroraNearTwoPowerExp(const double dbValue)
{
    int nExp = 0;
    while(dbValue > pow(2.0, double(nExp++)));
    return --nExp;
}

void AuroraGetAudacityChannelName(wxString& wxszDest, const int nChnl)
{
    switch(nChnl)
    {
        case 0: wxszDest = wxT("left");  break;
        case 1: wxszDest = wxT("right"); break;
        case 2: wxszDest = wxT("mono");  break;
        default: wxszDest.Printf(wxT("%d"), nChnl); 
    }
}


void AuroraChooseColour(wxColour& colour, const int nCh)
{
    switch(nCh) 
    {
        case 0:  colour.Set(  0,128,255); break;  // Aqua        
        case 1:  colour.Set(255,  0,128); break;  // Strawberry
        case 2:  colour.Set(  0,  0,128); break;  // Midnight
        case 3:  colour.Set(  0,128,  0); break;  // Clover
        case 4:  colour.Set(255,255,  0); break;  // Lemon
        case 5:  colour.Set(255,128,  0); break;  // Tangerine
        case 6:  colour.Set(255,  0,  0); break;  // Maraschino
        case 7:  colour.Set(  0,  0,255); break;  // Spring
            
        default: 
        {
            unsigned char uchCol = (unsigned char)(nCh*8);            
            colour.Set(uchCol, uchCol, uchCol); 
            break;
        }
    }
    
}

void AuroraChooseColour(wxColour& colour, const unsigned char uchChnl)
{
    unsigned char uchRed, uchGreen, uchBlue;
    
    switch(uchChnl)
    {
        case 0: uchRed =   0; uchGreen = 128; uchBlue = 255; break; // Aqua
        case 1: uchRed = 255; uchGreen =   0; uchBlue = 128; break; // Strawberry
        case 2: uchRed =   0; uchGreen =   0; uchBlue = 128; break; // Midnight
        case 3: uchRed =   0; uchGreen = 128; uchBlue =   0; break; // Clover
        case 4: uchRed = 255; uchGreen = 255; uchBlue =   0; break; // Lemon
        case 5: uchRed = 255; uchGreen = 128; uchBlue =   0; break; // Tangerine
        case 6: uchRed = 255; uchGreen =   0; uchBlue =   0; break; // Maraschino
        case 7: uchRed =   0; uchGreen =   0; uchBlue = 255; break; // Spring
            
        default:
            uchRed   = 255 * ((uchChnl & 4) >> 2) - 127 * ((uchChnl & 32) >> 5);
            uchGreen = 255 * ((uchChnl & 2) >> 1) - 127 * ((uchChnl & 16) >> 4);
            uchBlue  = 255 *  (uchChnl & 1)       - 127 * ((uchChnl &  8) >> 3);
            break;
    }
    
    colour.Set(uchRed, uchGreen, uchBlue);    
}

wxColour AuroraGetCanvasColour()
{
    wxSystemColour syscol;
#if defined __WXOSX__
    syscol = wxSYS_COLOUR_WINDOWFRAME; 
#elif defined __WXMSW__
    syscol = wxSYS_COLOUR_WINDOW;
#else // GTK   
    syscol = wxSYS_COLOUR_WINDOWFRAME;
#endif
    return wxSystemSettings::GetColour(syscol);
}

void AuroraUpdateGridBackgroundColor(wxGrid* pwxGrid)
{
    ::AuroraUpdateGridBackgroundColor(pwxGrid, -1, -1);
}

void AuroraUpdateGridBackgroundColor(wxGrid* pwxGrid, const int nRowsCount, const int nColsCount)
{
	// This is a dirty trick to solve the 'ugly white borders'
	// of the wxGrid: we have to default the grid's background
	// color to the window/panel color where the grid is
	// placed, then call this function that changes every
	// cell background color to white. It works!

    pwxGrid->SetDefaultCellBackgroundColour(::AuroraGetCanvasColour());
    
    int nRows = (nRowsCount < 0) ? pwxGrid->GetNumberRows() : nRowsCount;
    int nCols = (nColsCount < 0) ? pwxGrid->GetNumberCols() : nColsCount;
    
	int nRow, nCol;
	for(nRow = 0; nRow < nRows; nRow++)
		for(nCol = 0; nCol < nCols; nCol++)
			pwxGrid->SetCellBackgroundColour(nRow, nCol, *wxWHITE);

	pwxGrid->ForceRefresh();
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
