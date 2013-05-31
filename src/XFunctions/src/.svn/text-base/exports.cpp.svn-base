/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  XFunctions

  exports.cpp

  Angelo Farina - Simone Campanini

**********************************************************************/
#include <commdefs.h>

#include <wx/wfstream.h>

#include "exports.h"
#include "plot.h"

int XFunctionsExports::GetShownPlotType(const int nPlot)
{
   size_t unType = 0;
   while( unType < m_paDataSeries[nPlot]->GetCount() &&
		  !m_paDataSeries[nPlot]->Item(unType).IsShown()) unType++;

   return int(unType);
}

wxString XFunctionsExports::GetDataLabel(const int nType)
{
   switch(nType)
   {
      case XFPlot::XPT_AUTOCORR_L: return wxT("Gll");
      case XFPlot::XPT_AUTOCORR_R: return wxT("Grr");
      case XFPlot::XPT_MAGNITUDE:  return wxT("Magnitude");
      case XFPlot::XPT_PHASE:      return wxT("Phase");
      case XFPlot::XPT_REAL:       return wxT("Real");
      case XFPlot::XPT_IMAGINARY:  return wxT("Imaginary");
      case XFPlot::XPT_ALPHA:      return wxT("Alpha");
      case XFPlot::XPT_COHERENCE:  return wxT("Coherence");
   }
   return wxT("");   
}

double XFunctionsExports::GetDataValue(XFSpectrumDataSerie& ds, const int unIdx, const double dbFrq, const double dbRate)
{
	// TODO  Change values according to plot.cpp
   switch(ds.GetHandlerId())
   {
	  case XFPlot::XPT_AUTOCORR_L: return Re(ds.Gll()[unIdx]);
	  case XFPlot::XPT_AUTOCORR_R: return Re(ds.Grr()[unIdx]);
	  case XFPlot::XPT_MAGNITUDE:  return Re(ds.Y()[unIdx]);
	  case XFPlot::XPT_PHASE:      return DegPhase(ds.Y()[unIdx]);
	  case XFPlot::XPT_REAL:       return Re(ds.Y()[unIdx]);
	  case XFPlot::XPT_IMAGINARY:  return Im(ds.Y()[unIdx]);
	  case XFPlot::XPT_COHERENCE:  return Re(ds.C()[unIdx]);
	  case XFPlot::XPT_ALPHA:
		  return (dbFrq > 24.0 && dbFrq < (dbRate/5.12)) // k < unSpectrumLength/2.56
				  ? 2.0*fabs(Re(ds.Glr()[unIdx])) /
                        ( ( Re(ds.Gll()[unIdx]) + Re(ds.Grr()[unIdx]) )/2.0 + fabs(Re(ds.Glr()[unIdx])) )
				  : 0.0;
   }
   return 0.0;
}

bool XFunctionsExports::BuildParametersTable(wxString &wxszDataBuffer, const int nDest, const int nFileType)
{
   if( (nFileType == FT_CLIPBOARD) &&
	   (m_paDataSeries[0]->Item(0).GetSpectrumLength() > MAX_CLIPBOARD_ROWS) )
	   return false;

   if( (nFileType < FT_CLIPBOARD) && (!m_pOutputStream) )
	   return false;

//   int type = (nFileType < FT_CLIPBOARD) ? nFileType : 0;
   
   wxChar   wxchSeparator = m_awxchSeparator[nFileType];
   wxString wxszLineBreak(FILES_LINE_BREAK);
   if(nDest == DD_CLIPBOARD)
   {
       wxszLineBreak = wxT("\n");
       wxchSeparator = wxT('\t');
   }
   
   wxString wxszLine; //, caption, value;

   if(nFileType == FT_CLIPBOARD)
      wxszDataBuffer.Clear();
   
   InitProgressMeter();
   
   //Title generation
   wxszLine  = wxT("Aurora - Cross Functions ");
   wxszLine << wxAURORA_VERSION;
   wxszLine << wxT(" - Spectral Values");
   wxszLine << wxszLineBreak;
   
   if(nFileType == FT_CLIPBOARD)
      wxszDataBuffer.Append(wxszLine);
   else
      m_pOutputStream->WriteString(wxszLine);
   
   wxszLine = wxT("Transform type: ");
   wxszLine << wxchSeparator << m_wxszXFnLabel << wxchSeparator;
   wxszLine << wxszLineBreak;
    
   if(nFileType == FT_CLIPBOARD)
      wxszDataBuffer.Append(wxszLine);
   else
      m_pOutputStream->WriteString(wxszLine);

   int nUpperPlotType = GetShownPlotType(0);
   int nLowerPlotType = GetShownPlotType(1);
   
   // Caption generation
   wxszLine  = wxT("Freq. [Hz]");
   wxszLine << wxchSeparator;
   
   if(m_bExportAll)
   {
       for(size_t unSerie = 0; unSerie < m_paDataSeries[0]->GetCount(); unSerie++)
           wxszLine << wxchSeparator << GetDataLabel(m_paDataSeries[0]->Item(unSerie).GetHandlerId());

       wxszLine << wxszLineBreak;
   }
   else 
   {
       wxszLine << GetDataLabel(nUpperPlotType) << wxchSeparator; // upper plot
       wxszLine << GetDataLabel(nLowerPlotType) << wxszLineBreak; // lower plot
   }
      
   if(nFileType == FT_CLIPBOARD)
      wxszDataBuffer.Append(wxszLine);
   else
      m_pOutputStream->WriteString(wxszLine);

   double dbFrq;
   double dbFrqSpan = m_dbFHi - m_dbFLo;
   double dbRate = m_paDataSeries[0]->Item(0).GetRate();

   size_t unSpectrumLength = m_paDataSeries[0]->Item(0).GetSpectrumLength();

	size_t unBegin = size_t( m_dbFLo * unSpectrumLength/(dbRate/2.0) );
	size_t unEnd   = size_t( m_dbFHi * unSpectrumLength/(dbRate/2.0) );

	if(m_bExportAll)
	{
		for(size_t k = unBegin; k < unEnd; k++)
		{
			dbFrq = double(k*dbFrqSpan/unSpectrumLength);
			wxszLine.Clear();
			wxszLine << dbFrq; // frequency slot
			for(size_t unSerie = 0; unSerie < m_paDataSeries[0]->GetCount(); unSerie++)
			{
				wxszLine << wxchSeparator << GetDataValue(m_paDataSeries[0]->Item(unSerie), k, dbFrq, dbRate);
			}
			wxszLine <<  wxszLineBreak;

			if(nFileType == FT_CLIPBOARD)
				wxszDataBuffer.Append(wxszLine);
			else
				m_pOutputStream->WriteString(wxszLine);

			if(!(k % 1000)) UpdateProgressMeter(k, unEnd);
		}
	}
	else
	{
		for(size_t k = unBegin; k < unEnd; k++)
		{
			dbFrq = double(k*dbFrqSpan/unSpectrumLength);
			wxszLine.Clear();
			wxszLine << dbFrq << wxchSeparator; // frequency slot
			wxszLine << GetDataValue(m_paDataSeries[0]->Item(nUpperPlotType), k, dbFrq, dbRate) << wxchSeparator;
			wxszLine << GetDataValue(m_paDataSeries[1]->Item(nLowerPlotType), k, dbFrq, dbRate) << wxszLineBreak;

			if(nFileType == FT_CLIPBOARD)
			wxszDataBuffer.Append(wxszLine);
			else
			m_pOutputStream->WriteString(wxszLine);

			if(!(k % 1000)) UpdateProgressMeter(k, unEnd);
		}
	}
   
   DestroyProgressMeter();
   
   return true;
}

bool XFunctionsExports::AppendTimeDelay(const double dbTriggerTime, const double dbMaxDelay)
{
	wxString wxszFn(wxT("timedelay.txt"));
	wxFFileOutputStream timeDelayFile(wxszFn, wxT("a+b")); //append
	if( !timeDelayFile.IsOk() )
	{
		  ::wxMessageBox( wxT("Error on file creation."),
						  wxT("Error"),
						  wxOK | wxICON_ERROR );
		  return false;
	}

	//file writing
	m_pOutputStream = new wxTextOutputStream(timeDelayFile);

	// Write file
	m_pOutputStream->WriteString( wxNow() + wxT(" "));
	m_pOutputStream->WriteDouble(dbTriggerTime * 1000.0);
	m_pOutputStream->WriteString(wxT(" ms, "));
	m_pOutputStream->WriteDouble(dbMaxDelay * 1000.0);
	m_pOutputStream->WriteString(wxT(" ms.\n"));

	timeDelayFile.Close();
	delete m_pOutputStream;
	m_pOutputStream = 0;

	return true;
}

bool XFunctionsExports::SaveToFile() 
{
   int nType = FT_SPECTRUM_TXT;
   
   wxFileDialog *pDlg;
   pDlg = new wxFileDialog( m_pParent,
		                    wxT("Save spectrum to file"),
		                    wxT(""),
		                    m_wxszFileName,
                            wxT("Spectrum File tab-separated (*.txt)|*.txt|Spectrum File comma-separated (*.csv)|*.csv"),
                            wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

   if(pDlg->ShowModal() != wxID_OK)
   {
	   pDlg->Destroy();
	   return false;
   }

	m_wxszFileName = pDlg->GetPath();
	nType = pDlg->GetFilterIndex();

	if(m_wxszFileName.Find(m_awxchExtension[nType]) == wxNOT_FOUND)
		m_wxszFileName << m_awxchExtension[nType];

	pDlg->SetPath(m_wxszFileName);

	wxFFileOutputStream wxstrmResultsFile(m_wxszFileName);
	if( !wxstrmResultsFile.IsOk() )
    {
       ::wxMessageBox( wxT("Error on file creation."),
                       wxT("Error"),
                       wxOK | wxICON_ERROR );
       pDlg->Destroy();

       return false;
    }

	//init text output stream
	wxString emptyString;
	m_pOutputStream = new wxTextOutputStream(wxstrmResultsFile);

	switch(nType)
	{
		case FT_SPECTRUM_TXT:
		   BuildParametersTable(emptyString, DD_FILE, FT_SPECTRUM_TXT);
		   break;
		case FT_SPECTRUM_CSV:
		   BuildParametersTable(emptyString, DD_FILE, FT_SPECTRUM_CSV);
		   break;
	}

	//Close file.
	wxstrmResultsFile.Close();
	::wxMessageBox( wxT("Datas successifully saved."),
					wxT("Success"),
					wxOK | wxICON_INFORMATION );

	delete m_pOutputStream;
	m_pOutputStream = 0;
    pDlg->Destroy();

	return true;
}

void XFunctionsExports::InitProgressMeter() 
{
   m_pProgressDlg = new ProgressDialog(wxT("Aurora Cross Functions"),
                                     wxT("Exporting data..."));}

bool XFunctionsExports::UpdateProgressMeter(const AFSampleCount step, const AFSampleCount total)
{  
   return (m_pProgressDlg->Update(int(step), int(total)) > 0) ? true : false;
}

void XFunctionsExports::DestroyProgressMeter()
{
   m_pProgressDlg->Destroy();
   m_pProgressDlg = 0;
}

// ---- ctors
XFunctionsExports::XFunctionsExports(wxWindow* pParent, const wxString& wxszXFnLabel)
 : AFExports(pParent),
   m_wxszXFnLabel(wxszXFnLabel),
   m_bExportAll(false),
   m_dbFLo(0), m_dbFHi(24000.0),
   m_pOutputStream(0),
   m_pProgressDlg(0)
{
   m_wxszFileName = wxT("XFN_") + m_wxszXFnLabel;
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
