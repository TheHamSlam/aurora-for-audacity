/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  exports.cpp

  Simone Campanini

*******************************************************************//**

\class STIShowExports
\brief Data exports manager

  This class manages all Acoustics Parameters exports to/from
  files and clipboard.

*//*******************************************************************/

#include "exports.h"

#include <commdefs.h>
// ----------------------------------------------------------------------------
// STISpectrumExport implementation
// ----------------------------------------------------------------------------
bool STISpectrumExports::BuildParametersTable(wxString& wxszDataBuffer, const int nDest, const int nFileType) 
{
    wxChar   wxchSeparator = m_awxchSeparator[nFileType];
    wxString wxszLineBreak(FILES_LINE_BREAK);
    if(nDest == DD_CLIPBOARD)
    {    
        wxszLineBreak = wxT("\n");
        wxchSeparator = wxT('\t');
    }

    wxszDataBuffer  = wxT("Background Noise Left (dB)");
    wxszDataBuffer += wxchSeparator;
    wxszDataBuffer += wxT("Background Noise Right (dB)");
    wxszDataBuffer += wxchSeparator;

    wxszDataBuffer += wxT("Signal Level Left (dB)");
    wxszDataBuffer += m_awxchSeparator[nFileType];
    wxszDataBuffer += wxT("Signal Level Right (dB)");
    wxszDataBuffer += wxchSeparator;

    wxszDataBuffer += wxT("Signal + Noise Level Left (dB)");
    wxszDataBuffer += wxchSeparator;
    wxszDataBuffer += wxT("Signal + Noise Level Right (dB)");
    wxszDataBuffer += wxchSeparator;

    wxszDataBuffer += wxszLineBreak;

    wxString wxszValue;
    for(int nBand = 2; nBand < 9; nBand++)
    {
        wxszValue.Printf(wxT("%f"), m_pAs->GetNoiseLevel(nBand, CH_LEFT));
        wxszDataBuffer += wxszValue + wxchSeparator;
        wxszValue.Printf(wxT("%f"), m_pAs->GetNoiseLevel(nBand, CH_RIGHT));
        wxszDataBuffer += wxszValue + wxchSeparator;

        wxszValue.Printf(wxT("%f"), m_pAs->GetSignalLevel(nBand, CH_LEFT));
        wxszDataBuffer += wxszValue + wxchSeparator;
        wxszValue.Printf(wxT("%f"), m_pAs->GetSignalLevel(nBand, CH_RIGHT));
        wxszDataBuffer += wxszValue + wxchSeparator;
        
        wxszValue.Printf(wxT("%f"), m_pAs->GetSigNoiseLevel(nBand, CH_LEFT));
        wxszDataBuffer += wxszValue + wxchSeparator;
        wxszValue.Printf(wxT("%f"), m_pAs->GetSigNoiseLevel(nBand, CH_RIGHT));
        wxszDataBuffer += wxszValue + wxchSeparator;

        wxszDataBuffer += wxszLineBreak;
    }
    return true;
}

bool STISpectrumExports::LoadFromFile(wxTextFile& wxtfSplData)
{
    // TODO: missin' error check on reading
    int nBand;
    double dbValue;
    wxString wxszDataBuffer;
    wxszDataBuffer = wxtfSplData.GetFirstLine();

    while(!wxtfSplData.Eof()) 
    {
        if(wxszDataBuffer.Contains(wxT("BACKGROUND NOISE LEFT")))
        {
            for( nBand = 2, wxszDataBuffer = wxtfSplData.GetNextLine(); 
                 (nBand < 9) && !wxtfSplData.Eof(); 
                 nBand++, wxszDataBuffer = wxtfSplData.GetNextLine() )
            {
                wxszDataBuffer.ToDouble(&dbValue);
                m_pAs->SetNoiseLevel(dbValue, nBand, CH_LEFT, true);
            }
        }
        else if(wxszDataBuffer.Contains(wxT("SIGNAL LEVEL LEFT")))
        {
            for( nBand = 2, wxszDataBuffer = wxtfSplData.GetNextLine(); 
                 (nBand < 9) && !wxtfSplData.Eof(); 
                 nBand++, wxszDataBuffer = wxtfSplData.GetNextLine() )
            {
                wxszDataBuffer.ToDouble(&dbValue);
                m_pAs->SetSignalLevel(dbValue, nBand, CH_LEFT, true);
            }
        }
        else if(wxszDataBuffer.Contains(wxT("BACKGROUND NOISE RIGHT")))
        {
            for( nBand = 2, wxszDataBuffer = wxtfSplData.GetNextLine(); 
                 (nBand < 9) && !wxtfSplData.Eof(); 
                 nBand++, wxszDataBuffer = wxtfSplData.GetNextLine() )
            {
                wxszDataBuffer.ToDouble(&dbValue);
                m_pAs->SetNoiseLevel(dbValue, nBand, CH_RIGHT, true);
            }
        }
        else if(wxszDataBuffer.Contains(wxT("SIGNAL LEVEL RIGHT")))
        {
            for( nBand = 2, wxszDataBuffer = wxtfSplData.GetNextLine(); 
                 (nBand < 9) && !wxtfSplData.Eof(); 
                 nBand++, wxtfSplData.GetNextLine() )
            {
                wxszDataBuffer.ToDouble(&dbValue);
                m_pAs->SetSignalLevel(dbValue, nBand, CH_RIGHT, true);
            }
        }
        else
        {
            wxszDataBuffer = wxtfSplData.GetNextLine();
        }
    }
    return true;
}

bool STISpectrumExports::SaveToFile(wxTextFile& wxtfSplData)
{
    const wxChar* awxpchNoiseCaption[]  = { wxT("---BACKGROUND NOISE LEFT (dB)--- "), 
                                            wxT("---BACKGROUND NOISE RIGHT (dB)---") };
    const wxChar* awxpchSignalCaption[] = { wxT("---SIGNAL LEVEL LEFT (dB)---     "),
                                            wxT("---SIGNAL LEVEL RIGHT (dB)---    ") };
    wxString wxszLine;

    int nBand;
    for(int nCh = 0; nCh < 2; nCh++)
    {
        wxszLine = awxpchNoiseCaption[nCh];
        wxtfSplData.AddLine(wxszLine, wxTextFileType_Dos);
        for(nBand = 2; nBand < 9; nBand++) // 125 Hz -> 8 kHz
        {
            wxszLine.Printf(wxT("%.1f"), m_pAs->GetNoiseLevel(nBand, nCh));
            wxtfSplData.AddLine(wxszLine, wxTextFileType_Dos);
        }
        wxszLine = awxpchSignalCaption[nCh];
        wxtfSplData.AddLine(wxszLine, wxTextFileType_Dos);
        for(nBand = 2; nBand < 9; nBand++) // 125 Hz -> 8 kHz
        {
            wxszLine.Printf(wxT("%.1f"), m_pAs->GetSignalLevel(nBand, nCh));
            wxtfSplData.AddLine(wxszLine, wxTextFileType_Dos);
        }
    }
    return wxtfSplData.Write(wxTextFileType_Dos);
}

bool STISpectrumExports::OpenSavePrompt(const int nType)
{
    bool bIsOpen = (nType == SAVE_PROMPT) ? false : true;
    bool bRetVal = true;

    m_pwxFileDlg = new wxFileDialog( 0,
                                     (bIsOpen ? wxT("Open SPL file") 
                                              : wxT("Save SPL values to file")), 
                                     wxT(""), 
                                     m_wxszFileName,
                                     wxT("Aurora SPL files (*.txt)|*.txt|All files|*.*"),
                                     (bIsOpen ? wxFD_OPEN | wxFD_FILE_MUST_EXIST 
                                              : wxFD_SAVE | wxFD_OVERWRITE_PROMPT) );
   
    if(m_pwxFileDlg->ShowModal() != wxID_OK)
    {
    	m_pwxFileDlg->Destroy();
    	return false;
    }

	m_wxszFileName = m_pwxFileDlg->GetPath();

	wxTextFile wxtfSplData(m_wxszFileName);

	if(bIsOpen)
	{
		bRetVal = wxtfSplData.Open();
	}
	else
	{
		if(wxtfSplData.Exists())
		{
			if((bRetVal = wxtfSplData.Open()))
				wxtfSplData.Clear();
		}
		else
		{
			bRetVal = wxtfSplData.Create();
		}
	}

	if(!bRetVal)
	{
	    ::wxMessageBox( (bIsOpen ? wxT("Error on file access.\nCheck permissions.")
                                 : wxT("Error on file access.\nCheck permissions/file existence.")),
                        wxT("Error"),
					    wxOK | wxICON_ERROR );
        m_pwxFileDlg->Destroy();
        return false;
	}

	if(bIsOpen)
		bRetVal = LoadFromFile(wxtfSplData);
	else
		bRetVal = SaveToFile(wxtfSplData);

	if(!bRetVal)
	{
	   wxMessageBox((bIsOpen) ? wxT("Error opening file.")
							  : wxT("Error writing file"),
					wxT("Error"),
					wxOK | wxICON_ERROR);
	}
	else if(!bIsOpen)
	{
		wxMessageBox(wxT("SPL datas successifully saved."),
					 wxT("Success"),
					 wxOK | wxICON_INFORMATION);
	}

	//Close file.
	wxtfSplData.Close();

    m_pwxFileDlg->Destroy();
    return bRetVal;
}

STISpectrumExports::STISpectrumExports(wxWindow* pParent, AuroraSTI* pAs, const bool bIsStereo)
  : AFExports(pParent), 
    m_pAs(pAs),
    m_bIsStereo(bIsStereo)
{
    m_wxszFileName = wxT("SPL.txt");
}


// ----------------------------------------------------------------------------
// STIShowExport implementation
// ----------------------------------------------------------------------------
bool STIShowExports::BuildParametersTable(wxString &wxszDataBuffer, const int nDest, const int nFileType)
{
    const wxChar *awxpchChnlName[] = { wxT("Left Channel STI"),
                                       wxT("Right Channel STI") };
                                        
    const wxChar* awxpchBands[] = { wxT(" 125"), wxT(" 250"), wxT(" 500"), wxT("1000"),
                                    wxT("2000"), wxT("4000"), wxT("8000") };
                                    
    const wxChar* awxpchPars[]  = { wxT("0.63 "), wxT("0.8  "), wxT("1    "), wxT("1.25 "),
                                    wxT("1.6  "), wxT("2    "), wxT("2.5  "), wxT("3.15 "),
                                    wxT("4    "), wxT("5    "), wxT("6.3  "), wxT("8    "),
                                    wxT("10   "), wxT("12.5 ") };

    wxChar   wxchSeparator = m_awxchSeparator[nFileType];
    wxString wxszLineBreak(FILES_LINE_BREAK);
    if(nDest == DD_CLIPBOARD)
    {    
        wxszLineBreak = wxT("\n");
        wxchSeparator = wxT('\t');
    }

    //Title generation
    wxszDataBuffer << wxT("Aurora ") << wxAURORA_VERSION << wxT(" - Speech Transmission Index calculation results");
    wxszDataBuffer << wxszLineBreak << wxszLineBreak << wxT("MTF and STI") << wxszLineBreak << wxszLineBreak; 

    int nBand, nPar;
    wxString wxszValue;
    for(int nCh = 0; nCh < (m_bIsStereo ? 2 : 1); nCh++)
    {
        // nome canale
        if(m_bIsStereo) 
            wxszDataBuffer << awxpchChnlName[nCh] << wxszLineBreak;
        else             
            wxszDataBuffer << wxT("Parameters") << wxszLineBreak;
        
        // parametri canale
        // scrivo la prima riga, quella con le bande
        wxszDataBuffer << wxT("F [Hz]");
        for(nBand = 0; nBand < 7; nBand++) 
        {
            wxszDataBuffer << wxchSeparator << awxpchBands[nBand];
        }
        wxszDataBuffer << wxszLineBreak;
        
        // scrivo i parametri
        // parametri: nome + parametro banda per banda
        for(nPar = 0; nPar < 14; nPar++)
        {
            wxszDataBuffer << awxpchPars[nPar];
            for(nBand = 0; nBand < 7; nBand++)
            {
                wxszValue.Printf(wxT("%.3f"), m_pAs->GetMtfTableValue(nPar, nBand, nCh));
                wxszDataBuffer << wxchSeparator << wxszValue;
            }
            wxszDataBuffer << wxszLineBreak;
        }
        
        // Scrivo i valori di STI di Banda
        wxszDataBuffer << wxszLineBreak << wxT("OCTAVE BAND STI values") << wxszLineBreak;
        
        // scrivo la prima riga, quella con le bande
        wxszDataBuffer << wxT("F [Hz]");
        for(nBand = 0; nBand < 7; nBand++)
        {
            wxszDataBuffer << wxchSeparator << awxpchBands[nBand];
        }
        wxszDataBuffer << wxszLineBreak;
        
        wxszDataBuffer << wxT("MTI");
        for(nBand = 0; nBand < 7; nBand++)
        {
            wxszDataBuffer << wxchSeparator;
            //tmp=MTI[i2*2+Chan];                                      TODO: Check MTI versus STIValue
            wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIValue(nBand, nCh));
            wxszDataBuffer << wxszValue;
        }
        wxszDataBuffer << wxszLineBreak;

        // Scrivo i valori di STI Complessivo
        wxszDataBuffer << wxszLineBreak << wxT("TOTAL STI values") << wxchSeparator;

        if(m_pAs->IsSNCorrection()) 
            wxszDataBuffer << wxT("Noise Corrected");
        else
            wxszDataBuffer << wxT("No Noise Corr.");
        wxszDataBuffer << wxchSeparator;

        if(m_pAs->IsMaskingCorrection()) 
            wxszDataBuffer << wxT("Mask Corrected");
        else
            wxszDataBuffer << wxT("No Mask Corr.");
        wxszDataBuffer << wxszLineBreak;

        wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIMale(nCh));
        wxszDataBuffer << wxT("STI Male =") << wxchSeparator;
        wxszDataBuffer << wxszValue << wxszLineBreak;

        wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIFemale(nCh));
        wxszDataBuffer << wxT("STI Female =") << wxchSeparator;
        wxszDataBuffer << wxszValue << wxszLineBreak;

        wxszValue.Printf(wxT("%.3f"), m_pAs->GetRaSTI(nCh));
        wxszDataBuffer << wxT("RaSTI =") << wxchSeparator;
        wxszDataBuffer << wxszValue << wxszLineBreak;

        wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTItel(nCh));
        wxszDataBuffer << wxT("STItel =") << wxchSeparator;
        wxszDataBuffer << wxszValue << wxszLineBreak;

        wxszValue.Printf(wxT("%.3f"), m_pAs->GetSTIpa(nCh));
        wxszDataBuffer << wxT("STIpa =") << wxchSeparator;
        wxszDataBuffer << wxszValue << wxszLineBreak;

        wxszDataBuffer << wxszLineBreak;
    }
    return true;
}


bool STIShowExports::SavePrompt()
{
   bool bRetVal = true;
   int  nType = FF_TXT;
   
   m_pwxFileDlg = new wxFileDialog( 0, 
                                    wxT("Save results to file"), 
                                    wxT(""), 
                                    m_wxszFileName,
                                    wxT("Tab separated file (*.txt)|*.txt|Comma separated File (*.csv)|*.csv"),
                                    wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
   
   if(m_pwxFileDlg->ShowModal() != wxID_OK)
   {
	   m_pwxFileDlg->Destroy();
	   return false;
   }

   m_wxszFileName = m_pwxFileDlg->GetPath();
   nType = m_pwxFileDlg->GetFilterIndex();

   if(!IsExtensionPresent(m_wxszFileName))
	   m_wxszFileName << m_awxchExtension[nType];
   m_pwxFileDlg->SetPath(m_wxszFileName);

   wxTextFile resultsFile(m_wxszFileName);

   if(resultsFile.Exists())
	   bRetVal = resultsFile.Open();
   else
	   bRetVal = resultsFile.Create();

   if(bRetVal)
   {
	   wxString wxszDataBuffer;
	   BuildParametersTable(wxszDataBuffer, DD_FILE, nType);
	   resultsFile.AddLine(wxszDataBuffer,wxTextFileType_Dos);

	   //flush data to file.
	   if((bRetVal = resultsFile.Write(wxTextFileType_Dos)))
	   {
		   wxMessageBox(wxT("Datas successifully saved."),
						wxT("Success"),
						wxOK | wxICON_INFORMATION);
	   }
	   else
	   {
		   wxMessageBox(wxT("Write error."),
						wxT("Error"),
						wxOK | wxICON_ERROR);
	   }
	   //Close file.
	   resultsFile.Close();
   }
   else
   {
	   wxMessageBox(wxT("Error on file creation."),
					wxT("Error"),
					wxOK | wxICON_ERROR);
   }

   m_pwxFileDlg->Destroy();
   
   return bRetVal;
}


STIShowExports::STIShowExports(wxWindow *pParent, AuroraSTI* pAs, const bool bIsStereo)
  : AFExports(pParent), 
    m_pAs(pAs),
    m_bIsStereo(bIsStereo)
{
    m_wxszFileName = wxT("STI");
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
