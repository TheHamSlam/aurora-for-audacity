/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  exports.cpp

  Angelo Farina - Simone Campanini

**********************************************************************/

//#include <Audacity.h>
//#include <widgets/ProgressDialog.h>

#include "exports.h"
#include "version.h"

void THAExports::StoreParametersTable(wxTextFile *fo, int nFileType)
{
    wxString wxszDataBuffer;
    BuildParametersTable(wxszDataBuffer, nFileType);
    fo->AddLine(wxszDataBuffer, wxTextFileType_Dos);
}

void THAExports::StoreTimeHistory(wxTextFile *fo, int nFileType)
{
   wxString wxszValue, wxszLine;

#ifdef __AUDEBUG__
   printf("Generation of time history file started..."); fflush(stdout); // **** DEBUG
#endif

   double  dbTau         = 0.001, // 1 ms
           dbCurrentTime = 0.0;

   int nCh,
       nChnls = m_paSignalTracks->GetCount();

   double* adbFullScale = new double [nChnls];

   for(nCh = 0; nCh < nChnls; nCh++)
      adbFullScale[nCh] = m_paSignalTracks->Item(nCh).GetFullScale();

    // inizializzo a zero il progress meter
// ProgressDialog progress(wxT("Time History Analyzer"),
//                         wxT("Saving Slow Time History..."));

   AFSampleCount i,
                 smpcLength = m_pResults[TimeHistoryAnalyzer::TC_SLOW].GetBufferLength();

   if(m_nCurrentPlotType == TimeHistoryAnalyzer::TC_SLOW)
   {
     // Save a sample every second, discarding others
     wxszLine  = wxT("Time (s)");
     wxszLine << m_awxchSeparator[nFileType];
     for(nCh = 0; nCh < nChnls; nCh++)
     {
        //Header generation
        wxszLine << wxT("Slow ") << m_paSignalTracks->Item(nCh).GetName();
        wxszLine << wxT(" [") << (nCh+1) << wxT("]");
        wxszLine << m_awxchSeparator[nFileType];
     }
     fo->AddLine(wxszLine, wxTextFileType_Dos);
          
     for(i = 999; i < smpcLength; i += 1000)
     {
        wxszLine.Printf(wxT("%.6f"), dbCurrentTime);
        for(nCh = 0; nCh < nChnls; nCh++)
        {
           wxszValue.Printf(wxT("%.3f"), float(m_pResults[nCh].m_aadbBuffers[TimeHistoryAnalyzer::TC_SLOW][i] + adbFullScale[nCh]));
           wxszLine << m_awxchSeparator[nFileType];
           wxszLine << wxszValue;
        }
        fo->AddLine(wxszLine, wxTextFileType_Dos);
        
//      if((step % 100) == 0)   // to speedup not update at every step      
//         if(progress.Update(step, nStep) <= 0) break;

        dbCurrentTime += 1.0; // 1 s
     }
       
   } 
   else 
   {
       // Save a sample every millisecond
       
      //Header generation
      wxszLine  = wxT("Time (ms)")         + m_awxchSeparator[nFileType];
      for(nCh = 0; nCh < nChnls; nCh++)
      {
         wxszLine << wxT("RMS (1 ms) ") << m_paSignalTracks->Item(nCh).GetName();
         wxszLine << wxT(" [") << (nCh+1) << wxT("]");
         wxszLine << m_awxchSeparator[nFileType];
      }
      for(nCh = 0; nCh < nChnls; nCh++)
      {
         wxszLine << wxT("ITU (30 ms) ") << m_paSignalTracks->Item(nCh).GetName();
         wxszLine << wxT(" [") << (nCh+1) << wxT("]");
         wxszLine << m_awxchSeparator[nFileType];
      }
      for(nCh = 0; nCh < nChnls; nCh++)
      {
         wxszLine << wxT("Impulse ") << m_paSignalTracks->Item(nCh).GetName();
         wxszLine << wxT(" [") << (nCh+1) << wxT("]");
         wxszLine << m_awxchSeparator[nFileType];
      }
      for(nCh = 0; nCh < nChnls; nCh++)
      {
         wxszLine << wxT("Fast ") << m_paSignalTracks->Item(nCh).GetName();
         wxszLine << wxT(" [") << (nCh+1) << wxT("]");
         wxszLine << m_awxchSeparator[nFileType];
      }
      for(nCh = 0; nCh < nChnls; nCh++)
      {
         wxszLine << wxT("Slow ") << m_paSignalTracks->Item(nCh).GetName();
         wxszLine << wxT(" [") << (nCh+1) << wxT("]");
         wxszLine << m_awxchSeparator[nFileType];
      }
      fo->AddLine(wxszLine, wxTextFileType_Dos);
                            
      for(i = 0; i < smpcLength; i++)
      {
         wxszLine.Printf(wxT("%.6f"), dbCurrentTime);
         
         for(nCh = 0; nCh < nChnls; nCh++)
         {
            wxszValue.Printf(wxT("%.3f"), float(m_pResults[nCh].m_aadbBuffers[TimeHistoryAnalyzer::TC_RMS][i] + adbFullScale[nCh]));
            wxszLine << m_awxchSeparator[nFileType];
            wxszLine << wxszValue;
         }
         for(nCh = 0; nCh < nChnls; nCh++)
         {
            wxszValue.Printf(wxT("%.3f"), float(m_pResults[nCh].m_aadbBuffers[TimeHistoryAnalyzer::TC_ITU][i] + adbFullScale[nCh]));
            wxszLine << m_awxchSeparator[nFileType];
            wxszLine << wxszValue;
         }
         for(nCh = 0; nCh < nChnls; nCh++)
         {
            wxszValue.Printf(wxT("%.3f"), float(m_pResults[nCh].m_aadbBuffers[TimeHistoryAnalyzer::TC_IMP][i] + adbFullScale[nCh]));
            wxszLine << m_awxchSeparator[nFileType];
            wxszLine << wxszValue;
         }
         for(nCh = 0; nCh < nChnls; nCh++)
         {
            wxszValue.Printf(wxT("%.3f"), float(m_pResults[nCh].m_aadbBuffers[TimeHistoryAnalyzer::TC_FAST][i] + adbFullScale[nCh]));
            wxszLine << m_awxchSeparator[nFileType];
            wxszLine << wxszValue;
         }
         for(nCh = 0; nCh < nChnls; nCh++)
         {
            wxszValue.Printf(wxT("%.3f"), float(m_pResults[nCh].m_aadbBuffers[TimeHistoryAnalyzer::TC_SLOW][i] + adbFullScale[nCh]));
            wxszLine << m_awxchSeparator[nFileType];
            wxszLine << wxszValue;
         }
         fo->AddLine(wxszLine, wxTextFileType_Dos);

             //ProgressMeter(ci,i,Nstep);
//      if((step % 100) == 0)   // to speedup not update at every step      
//         if(progress.Update(step, nStep) <= 0) break;
         dbCurrentTime += dbTau; // 1 s
       }
       // distruggo il progress meter, ho finito!
       //ProgressDestroy(ci);
   }

   delete [] adbFullScale;
   
   printf("done.\n");
}


bool THAExports::BuildParametersTable(wxString &wxszDataBuffer, const int nDest, const int nFileType)
{
   int nParIdx = 0;
   wxString wxszLine, wxszValue;

   wxszDataBuffer.Clear();
   
   //Title generation
   wxszLine  = wxT("Aurora - Time History Analyzer (v.");
//   wxszLine << wxAURORA_VERSION;
   wxszLine << ::AuroraModuleVersionNumber(THA_VERSION_TYPE, THA_RELEASE_CANDIDATE) << wxT(")");
   wxszLine << wxT(" - Results of ITU-T P56 Calculations");
   wxszLine << LINE_BREAK;
   
   wxszDataBuffer.Append(wxszLine);

   // Caption generation
   wxszLine  = wxT("Channel");
   wxszLine << m_awxchSeparator[nFileType];
   wxszLine << wxT("Leq (dB)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("SEL (dB)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("Total Duration (s)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("Active SpeenCh Level (dB)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("Threshold Level (dB)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("Activity Ratio (%)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("Max Peak SPL (dB)")  << m_awxchSeparator[nFileType];
   wxszLine << wxT("Max Impulse SPL (dB)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("Max Fast SPL (dB)")  << m_awxchSeparator[nFileType];
   wxszLine << wxT("Max Slow SPL (dB)")  << m_awxchSeparator[nFileType];
   wxszLine << wxT("Event Duration (s)") << m_awxchSeparator[nFileType];
   wxszLine << wxT("Impulsive Event")    << LINE_BREAK;
      
   wxszDataBuffer.Append(wxszLine);

   int nChnlsCount = int(m_paSignalTracks->GetCount());

   for(int nCh = 0; nCh < nChnlsCount; nCh++)
   {
       // Parameters
      //wxszLine = mThan->GetTrackName(nCh); // TODO Add track names
      wxszLine.Printf(wxT("Ch %d"), nCh);
      wxszLine << wxT(" [") << (nCh+1) << wxT("]");
      wxszLine << m_awxchSeparator[nFileType];
      
      for(nParIdx = TimeHistoryAnalyzer::THA_AVG; nParIdx <= TimeHistoryAnalyzer::THA_DUR; nParIdx++)
      {
       
         wxszValue.Printf(wxT("%.2f"), m_pResults[nCh].GetParameter(nParIdx));
         wxszLine << wxszValue << m_awxchSeparator[nFileType];
      }
      wxszValue =  (m_pResults[nCh].IsImpulsive()) ? wxT("yes") : wxT("no");
      wxszLine << wxszValue << LINE_BREAK;
      
      wxszDataBuffer.Append(wxszLine);
   }
   
   // Parameters
   wxszLine = wxT("Average");
   wxszLine << m_awxchSeparator[nFileType];
   for(nParIdx = TimeHistoryAnalyzer::THA_AVG; nParIdx <= TimeHistoryAnalyzer::THA_DUR; nParIdx++)
   {
       wxszValue.Printf(wxT("%.2f"), m_pResults[nChnlsCount].GetParameter(nParIdx));
       wxszLine << wxszValue << m_awxchSeparator[nFileType];
   }
   wxszValue = (m_pResults[nChnlsCount].IsImpulsive()) ?  wxT("yes") : wxT("no");
   wxszLine << wxszValue << LINE_BREAK;
    
    wxszDataBuffer.Append(wxszLine);
    
    return true;
}
 
bool THAExports::SaveToFile() 
{
   int type = FT_PARAMETER_TXT;
   
   wxFileDialog saveFileDialog(m_pParent,
		                       wxT("Save results to file"),
		                       wxT(""),
		                       m_wxszFileName,
                               wxT("Parameter File (*.txt)|*.txt|Parameter File (*.csv)|*.csv|Time History (*.txt)|*.txt|Time History (*.csv)|*.csv"),
                               wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

   if(saveFileDialog.ShowModal() != wxID_OK)
	   return false;

	m_wxszFileName = saveFileDialog.GetPath();
	type = saveFileDialog.GetFilterIndex();

	m_wxszFileName << m_awxchExtension[type];
	saveFileDialog.SetPath(m_wxszFileName);

	wxTextFile * resultsFile = new wxTextFile();
	if( resultsFile->Create(m_wxszFileName) || resultsFile->Open(m_wxszFileName) )
	{
		//file writing
		resultsFile->Clear();

		switch(type)
		{
			case FT_PARAMETER_TXT:
			   StoreParametersTable(resultsFile, FF_TXT);
			   break;
			case FT_PARAMETER_CSV:
			   StoreParametersTable(resultsFile, FF_CSV);
			   break;
			case FT_TIME_HISTORY_TXT:
			   StoreTimeHistory(resultsFile, FF_TXT);
			   break;
			case FT_TIME_HISTORY_CSV:
			   StoreTimeHistory(resultsFile, FF_CSV);
			   break;
		}

		//flush data to file.
		if( ! resultsFile->Write(wxTextFileType_Dos))
		{
		   ::wxMessageBox(wxT("Write error."),
						  wxT("Error"), wxOK | wxICON_ERROR);
		   //Close file.
		   resultsFile->Close();
		}
		else
		{
			//Close file.
			resultsFile->Close();
			::wxMessageBox(wxT("Datas successifully saved."),
						   wxT("Success"), wxOK | wxICON_INFORMATION);
		}
	}
	else
	{
		 ::wxMessageBox(wxT("Error on file creation."),
						wxT("Error"), wxOK | wxICON_ERROR);
	}

	delete resultsFile;

   return true;
}

// ---- ctors
THAExports::THAExports(wxWindow* pParent,
                       TArrayOfTHASignalAudioTrack*   paSignalTracks,
                       TimeHistoryAnalyzer::TResults* pResults)
 : AFExports(pParent),
   m_paSignalTracks(paSignalTracks),
   m_pResults(pResults)
{
   m_wxszFileName = wxT("ITUP56");
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
