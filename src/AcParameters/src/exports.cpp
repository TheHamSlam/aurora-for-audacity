/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters

  exports.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AcParametersExports
\brief Data exports manager

  This class manages all Acoustics Parameters exports to/from
  files and clipboard.

*//*******************************************************************/


#include <wx/filename.h>
#include <wx/progdlg.h>
#include <wx/textfile.h>

#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include <vector>

#include <commdefs.h>
#include <afconfig.h>
#include <afexports.h>

#include "afacpar.h"

#ifndef __STAND_ALONE__
   #include "acpar.h"
#else
   #include "acparsa.h"
#endif


#include "exports.h"



const wxChar* const AcParametersExports::m_awxpchParamLabels[] = {

    wxT("Signal [dB]"),    wxT("Noise [dB]"),      wxT("strenGth [dB]"),  
    wxT("C50 [dB]"),       wxT("C80 [dB]"),        wxT("D50 [%]"),        
    wxT("Ts [ms]"),        wxT("EDT [s]"),         wxT("Tuser [s]"),  
    wxT("T20 [s]"),        wxT("T30 [s]"),

    wxT("Peakiness [dB]"), wxT("Millisecs [dB]"),  wxT("Impulsivs [dB]"),

    wxT("St1 [dB]"),       wxT("St2 [dB]"),        wxT("StLate [dB]"),
    wxT("IACC"),           wxT("IACC delay [ms]"), wxT("IACC width [ms]"),
    wxT("JLF"),            wxT("JLFC"),            wxT("LJ [dB]")
};


void AcParametersExports::StoreParametersTable(wxTextFile& fo, const int nFileType)
{
   int type = (m_pAp->GetBandsCount() > 12) ? 3 : 1;

   wxString wxszValue, wxszLine, wxszCaption;
   
   //Title generation
   wxszLine << wxT("Aurora ") << wxAURORA_VERSION 
            << wxT(" - ISO3382 Acoustical Parameter File");
   fo.AddLine(wxszLine, wxTextFileType_Dos);
   wxszLine = wxT("ISO 3382 OCTAVE BAND ACOUSTICAL PARAMETERS\n");
   fo.AddLine(wxszLine, wxTextFileType_Dos);

   //Caption generation
   wxszCaption.Clear();
   wxszCaption << wxT("Filename") << m_awxchSeparator[nFileType];
   wxszCaption << wxT("Frq.band [Hz]");
   
   int nPar, nBd;
   for(nBd = 0; nBd < int(m_pAp->GetBandsCount()); nBd++)
   {
      wxszCaption << m_awxchSeparator[nFileType] << ::AuroraGetBandLabel(nBd, type);
   }

   for(int nCh = 0; nCh < m_pAp->GetChannelsCount(); nCh++)
   {
      wxszLine.Clear();
      wxszLine << wxT("Channel ") << (nCh+1) << wxT(" Parameters\n");
      fo.AddLine(wxszLine,    wxTextFileType_Dos);  
      fo.AddLine(wxszCaption, wxTextFileType_Dos);  

      for(nPar=0; nPar < AcParameters::N_PARAMETERS; nPar++)
      {
         wxszLine = m_paAudioData->Item(nCh).GetName();
         wxszLine << m_awxchSeparator[nFileType];

         wxszLine << m_awxpchParamLabels[nPar];
         if( (m_pAp->GetMode() == AcParameters::APM_BINAURAL) &&
        	             (nPar == AcParameters::AP_IACC) )
         {
        	 switch(m_pAp->GetIACCSpan())
        	 {
        	     case AcParameters::IS_EARLY: wxszLine << wxT(" (Early)"); break;
        	     case AcParameters::IS_LATE:  wxszLine << wxT(" (Late)");  break;
        	     case AcParameters::IS_ALL:   wxszLine << wxT(" (All)");   break;
        	 }
         }
         
          for(nBd=0; nBd < int(m_pAp->GetBandsCount()); nBd++)
          {
        	  if(m_paResults[nCh].IsParameterValid(nPar, nBd))
        		  wxszValue.Printf(wxT("%.3f"),
        				           m_paResults[nCh].GetParameter(nPar, nBd));
        	  else
        		  wxszValue = wxT("--");

               wxszLine << m_awxchSeparator[nFileType] << wxszValue;
 
         }
         fo.AddLine(wxszLine,wxTextFileType_Dos); 
      }
      wxszLine.Printf(wxT("\nRTU = RT User (%4.1f dB, %4.1f dB)\n"),
    		          m_pAp->GetUserMinLevel(),
                      m_pAp->GetUserMaxLevel());

      fo.AddLine(wxszLine,wxTextFileType_Dos);

   }
}

void AcParametersExports::StoreEchogram(wxTextFile& fo)
{
   wxString wxszStr, wxszLine, wxszCaption;

   AFSampleCount nBd, i, j;

   // Create 1 ms RMS Impulse Response
   AFSample *psmpData;

   AFSampleCount smpcDecimationStep = 
                    AFSampleCount(m_paAudioData->Item(CH_LEFT).GetRate() / 1000.0), // 1 ms rate
                 smpcRmsDataLength  = 
                    (m_paAudioData->Item(CH_LEFT).GetLength() / smpcDecimationStep) + 1;

   double dbScaleFactor = pow( 10.0, m_pAp->GetFullScale()/10.0) / m_pAp->GetRate();

   int bandsCount = (int)m_pAp->GetBandsCount();
   double** aadbRmsIr = new double* [bandsCount];
   for(nBd = 0; nBd < bandsCount; nBd++)
	   aadbRmsIr[nBd] = new double [smpcRmsDataLength];

   //Header generation
   wxszStr.Clear();
   wxszStr << wxT("Aurora ") << wxAURORA_VERSION 
           << wxT(" - Energetic Impulse Response File");
   fo.AddLine(wxszStr, wxTextFileType_Dos); 
   wxszStr.Printf(wxT("N. Impulse Responses = %d"), m_pAp->GetChannelsCount());
   fo.AddLine(wxszStr,wxTextFileType_Dos);
   wxszStr.Printf(wxT("Time resolution = 1 ms"));
   fo.AddLine(wxszStr,wxTextFileType_Dos);

   int nCh = 0; 
   while(nCh < m_pAp->GetChannelsCount())
   {
	   for(nBd = 0; nBd < bandsCount; nBd++)
	   {
		   memset(aadbRmsIr[nBd], 0, smpcRmsDataLength*sizeof(double));

		   m_paAudioData->Item(nCh).ApplyFilter(nBd);

		   psmpData = m_paAudioData->Item(nCh).GetFilteredData();

		   for(i = m_paAudioData->Item(nCh).GetFirstArrivalTime(); 
               i < m_paAudioData->Item(nCh).GetLength(); 
               i++)
		   {
			   j = AFSampleCount( i / smpcDecimationStep );
			   aadbRmsIr[nBd][j] += psmpData[i] * psmpData[i];
		   }

		   // Rescale buffer values to obtain correct dB levels
		   for(i = 0; i < smpcRmsDataLength; i++)
		   {  aadbRmsIr[nBd][i] *= dbScaleFactor; }
	   }

      wxszStr.Printf(wxT("Impulse Response n. = %d"), nCh + 1);
      fo.AddLine(wxszStr, wxTextFileType_Dos); 
      wxszStr.Printf(wxT("N. of points=  %d"), int(smpcRmsDataLength));
      fo.AddLine(wxszStr, wxTextFileType_Dos); 
      
      for(i = 0; i < smpcRmsDataLength; i++)
      {
         wxszLine.Clear();
         for(nBd = 0; nBd < bandsCount; nBd++)
         {
            wxszStr.Printf(wxT("%e "), aadbRmsIr[nBd][i]);
            wxszLine.Append(wxszStr);
         }
         fo.AddLine(wxszLine, wxTextFileType_Dos); 
      }
      nCh++;
   }

   // clear memory
   for(nBd = 0; nBd < bandsCount; nBd++)
	   delete [] aadbRmsIr[nBd];

   delete [] aadbRmsIr;
}

bool AcParametersExports::BuildParametersTable(wxString &wxszDataBuffer, 
                                               const int nDest, 
                                               const int nFileType)
{
   int type = (m_pAp->GetBandsCount() > 12) ? 3 : 1;

   wxString wxszStr, wxszLine, wxszCaption;

   wxszDataBuffer.Clear();
   
   //Title generation
   wxszDataBuffer << wxT("Aurora ") << wxAURORA_VERSION 
                  << wxT(" - ISO3382 Acoustical Parameter Table\n")
                  << wxT("ISO 3382 OCTAVE BAND ACOUSTICAL PARAMETERS\n\n");

   //Caption generation
   wxszCaption << wxT("Filename")      << m_awxchSeparator[nFileType];
   wxszCaption << wxT("Frq.band [Hz]") << m_awxchSeparator[nFileType];
   
   int nBd, nPar;
   int bandsCount = int(m_pAp->GetBandsCount());
   for(nBd=0; nBd < bandsCount; nBd++)
   {
	   wxszCaption << ::AuroraGetBandLabel(nBd, type)
	               << m_awxchSeparator[nFileType];
   }
   
   for(int nCh = 0; nCh < m_pAp->GetChannelsCount(); nCh++)
   {
      wxszLine.Clear();   
      wxszLine << wxT("Channel ") << (nCh+1) << wxT(" Parameters\n\n");
      wxszDataBuffer << wxszLine;
      wxszDataBuffer << (wxszCaption + LINE_BREAK);
      
      for(nPar = 0; nPar < AcParameters::N_PARAMETERS; nPar++)
      {
         wxszLine = m_paAudioData->Item(nCh).GetName();
		 wxszLine << m_awxchSeparator[nFileType] << m_awxpchParamLabels[nPar];
         
         for(nBd = 0; nBd < bandsCount; nBd++)
         {
        	 if(m_paResults[nCh].IsParameterValid(nPar, nBd))
        	 {	 wxszStr.Printf(wxT("%.3f"),
        				        m_paResults[nCh].GetParameter(nPar, nBd)); }
        	 else
        	 {   wxszStr = wxT("--");  }

             wxszLine << m_awxchSeparator[nFileType] << wxszStr;
         }
         wxszDataBuffer << (wxszLine + LINE_BREAK);
      }
      wxszLine.Printf(wxT("\nRTU = RT User (%.1f dB, %.1f dB)\n\n"),
                      m_pAp->GetUserMinLevel(),
                      m_pAp->GetUserMaxLevel());
                  
      wxszDataBuffer << wxszLine;
   }
   return true;
}


bool AcParametersExports::SaveToFile()
{
   bool bRetVal = true;
   int  nType = FT_PARAMETER_TXT;
   
   wxString wxszName(wxT("AP_"));
   wxszName << m_paAudioData->Item(CH_LEFT).GetName();
   wxFileName wxfnName(wxszName);
   wxfnName.ClearExt();

   wxFileDialog* pFileDlg = 
        new wxFileDialog(0,
		                 wxT("Save results to file"),
		                 wxT(""),
		                 wxfnName.GetFullName(),
                         wxT("Parameter File (*.txt)|*.txt|Parameter File (*.csv)|*.csv|Ramsete Echogram (*.prn)|*.prn"),
                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
#ifdef __AUDEBUG__                        
   printf("done\n"); fflush(stdout);
#endif
   
	if(pFileDlg->ShowModal() != wxID_OK)
	{
	   pFileDlg->Destroy();
	   return false;
	}

	wxfnName = pFileDlg->GetPath();
	nType = pFileDlg->GetFilterIndex();

	wxfnName.SetExt(wxString(m_awxchExtension[nType]));

	//pFileDlg->SetPath(m_wxszFileName);

	wxTextFile resultsFile;

	if(wxfnName.FileExists())
	{
		if(!resultsFile.Open(wxfnName.GetFullPath()))
		{
			::wxMessageBox(wxT("Cannot open file for writing"),
						   wxT("Error"),
						   wxOK | wxICON_ERROR);
			pFileDlg->Destroy();
			return false;
		}
		resultsFile.Clear();
	}
	else
	{
		if(!resultsFile.Create(wxfnName.GetFullPath()))
		{
			::wxMessageBox(wxT("Cannot create file. Check permissions."),
						   wxT("Error"),
						   wxOK | wxICON_ERROR);
			pFileDlg->Destroy();
			return false;
		}
	}

	//file writing
	switch(nType)
	{
		case FT_PARAMETER_TXT:
			StoreParametersTable(resultsFile, FF_TXT);
			break;
		case FT_PARAMETER_CSV:
			StoreParametersTable(resultsFile, FF_CSV);
			break;
		case FT_RAMSETE_ECHOGRAM_PRN:
			StoreEchogram(resultsFile);
			break;
	}

	 //flush data to file.
	if( !resultsFile.Write(wxTextFileType_Dos) )
	{
		::wxMessageBox(wxT("Write error."),
					   wxT("Error"),
					   wxOK | wxICON_ERROR);
		bRetVal =  false;
	}
	else
	{
		::wxMessageBox(wxT("Datas successifully saved."),
					   wxT("Info"),
					   wxOK | wxICON_INFORMATION);
    }
	//Close file.
	resultsFile.Close();

    pFileDlg->Destroy();

    return bRetVal;
}

void AcParametersExports::AppendResultsToFile()
{
   int type = (m_pAp->GetBandsCount() > 12) ? 3 : 1;

   wxString wxszLine, wxszStr;
   const wxChar* shLabels[] = { wxT("Lsg"), wxT("Lno"), wxT("StG"), wxT("C50"),
		                        wxT("C80"), wxT("D50"), wxT("t_s"), wxT("EDT"),
		                        wxT("Tus"), wxT("T20"), wxT("T30"), wxT("Pkn"),
		                        wxT("Mls"), wxT("Imp"), wxT("St1"), wxT("St2"),
		                        wxT("StL"),
		                        wxT("IACC"), wxT("tIACC"), wxT("wIACC"),
		                        wxT("JLF"),  wxT("JLFC"),  wxT("LJ") }; // 23

   int nCh, nPar, nBd;

   wxString wxszCaption = wxT("Filename");

   for(nPar = 0; nPar < 23; nPar++)
   {
	   for(nBd = 0; nBd < (int)m_pAp->GetBandsCount(); nBd++)
	   {
           wxszCaption << wxT("\t") << shLabels[nPar] << wxT("_")
        		       << ::AuroraGetBandLabel(nBd, type);
	   }
   }

   wxTextFile* pAppendFile = new wxTextFile();
   if( !pAppendFile->Open(m_wxszAppendToFileFn) )
   {
       if( !pAppendFile->Create(m_wxszAppendToFileFn))
       {
           ::wxMessageBox(wxT("Error on file creation."),
                          wxT("Error"),
           		          wxOK | wxICON_ERROR);

           delete pAppendFile;
           return;
       }
   }

   wxszLine = wxT("Aurora ");
   wxszLine << wxAURORA_VERSION << wxT(" - ISO3382 Acoustical Parameter File\n");
   pAppendFile->AddLine(wxszLine, wxTextFileType_Dos);
   pAppendFile->AddLine(wxszCaption, wxTextFileType_Dos);

   for(nCh = 0; nCh < int(m_paAudioData->GetCount()); nCh++)
   {
		wxszLine = m_paAudioData->Item(nCh).GetName();
		wxszLine << wxT(" Ch ") << (nCh+1);
		for(nPar = 0; nPar < AcParameters::N_PARAMETERS; nPar++)
		{
			for(nBd = 0; nBd < (int)m_pAp->GetBandsCount(); nBd++)
			{
				if(m_paResults[nCh].IsParameterValid(nPar, nBd))
					wxszStr.Printf(wxT("\t%7.3f"), 
                                   m_paResults[nCh].GetParameter(nPar, nBd));
				else
					wxszStr = wxT("\t--");

				wxszLine << wxszStr;
			}
		}
		pAppendFile->AddLine(wxszLine, wxTextFileType_Dos);

		if(!pAppendFile->Write(wxTextFileType_Dos))
		{
			::wxMessageBox(wxT("Write error."),
						   wxT("Error"),
						   wxOK | wxICON_ERROR);
		    //Close file.
			pAppendFile->Close();
			delete pAppendFile;
            return;
		}
    }

    ::wxMessageBox(wxT("Data appended to file."),
                   wxT("Info"),
   		           wxOK | wxICON_INFORMATION);
	//Close file.
	pAppendFile->Close();
	delete pAppendFile;
}

AcParametersExports::AcParametersExports(wxWindow *pParent, 
                                         TArrayOfAPAudioTracks* paAudioData, 
                                         AcParameters *pAp)
  : AFExports(pParent),
    m_pAp(pAp),
    m_paAudioData(paAudioData),
    m_paDecay(m_pAp->GetDecaysArray()),
    m_paResults(m_pAp->GetResultsArray()),
    m_wxszAppendToFileFn(wxT("AcousticParameters.txt"))
{
//    m_pAp->GetIrFileName(m_pAp->GetActiveChannel(), &m_wxszIrName);
//    m_wxszFileName = wxT("AP_") + m_wxszIrName;
	m_wxszFileName = wxT("AP_ir");
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
