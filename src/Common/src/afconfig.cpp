/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common Libraries

  afconfig.cpp

  Simone Campanini

*******************************************************************//**

\class AFConfig
\brief Configuration file manager class

  This class manages configuration files.

*//*******************************************************************/

//#include <wxcmn.h>

#include "afconfig.h"

double AFConfig::StringToDouble(wxString& wxszStr) 
{
   double dbVal = 0.0;
   if(wxszStr.ToDouble(&dbVal)) return dbVal;
   return 0.0;
}

AFSample AFConfig::StringToSample(wxString& wxszStr) 
{
   double dbVal = 0.0;
   if(wxszStr.ToDouble(&dbVal)) return AFSample(dbVal);
   return AFSample(0.0);
}

AFSampleCount AFConfig::StringToSampleCount(wxString& wxszStr) {

   long lnVal = 0.0;
   if(wxszStr.ToLong(&lnVal)) return AFSampleCount(lnVal);
   return AFSampleCount(0);
}

bool AFConfig::StringToBool(wxString& wxszStr) 
{
   if(wxszStr.CmpNoCase(wxT("true")) == 0) return true;
   return false;
}

AFSampleCount AFConfig::Read(const wxString& wxszKey, const AFSampleCount& smpcDefaultVal)
{
   wxString wxszValue;
   if(!wxConfig::Read(wxszKey, &wxszValue)) return smpcDefaultVal;
   return StringToSampleCount(wxszValue);
}

double AFConfig::Read(const wxString& wxszKey, const double& dbDefaultVal)
{
    wxString wxszValue;
    if(!wxConfig::Read(wxszKey, &wxszValue)) return dbDefaultVal;
    return StringToDouble(wxszValue);
}

AFSample AFConfig::Read(const wxString& wxszKey, const AFSample& smpDefaultVal)
{
    wxString wxszValue;
    if(!wxConfig::Read(wxszKey, &wxszValue)) return smpDefaultVal;
    return StringToSample(wxszValue);
}

bool AFConfig::Read(const wxString& wxszKey, double* pdbValue)
{
   wxString wxszStrValue;
   if(!wxConfig::Read(wxszKey, &wxszStrValue)) return false;
   *pdbValue = StringToDouble(wxszStrValue);
   return true;
}

bool AFConfig::Read(const wxString& wxszKey, AFSampleCount* psmpcValue)
{
   wxString wxszStrValue;
   if(!wxConfig::Read(wxszKey, &wxszStrValue)) return false;
   *psmpcValue = StringToSampleCount(wxszStrValue);
   return true;
}

bool AFConfig::Read(const wxString& wxszKey, AFSample* psmpValue)
{
   wxString wxszStrValue;
   if(!wxConfig::Read(wxszKey, &wxszStrValue)) return false;
   *psmpValue = StringToSample(wxszStrValue);
   return true;
}

bool AFConfig::Read(const wxString& wxszKey, bool* pbValue)
{
   wxString wxszStrValue;
   if(!wxConfig::Read(wxszKey, &wxszStrValue)) return false;
   *pbValue = StringToBool(wxszStrValue);
   return true;
}

bool AFConfig::Read(const wxString& wxszKey, int* pnValue)
{
   wxString wxszStrValue;
   if(!wxConfig::Read(wxszKey, &wxszStrValue)) return false;
   *pnValue = StringToInt(wxszStrValue);
   return true;
}

bool AFConfig::Write(const wxString& wxszKey, const AFSampleCount smpcValue)
{
   wxString wxszStrValue;
   wxszStrValue << smpcValue; 
   return wxConfig::Write(wxszKey, wxszStrValue);
}

bool AFConfig::Write(const wxString& wxszKey, const double dbValue)
{
   wxString wxszStrValue;
   wxszStrValue << dbValue;
   return wxConfig::Write(wxszKey, wxszStrValue);
}

bool AFConfig::Write(const wxString& wxszKey, const AFSample smpValue)
{
   wxString wxszStrValue;
   wxszStrValue << smpValue;
   return wxConfig::Write(wxszKey, wxszStrValue);
}

bool AFConfig::Write(const wxString& wxszKey, const bool bValue)
{
   wxString wxszStrValue;
   if(bValue) wxszStrValue << wxT("true");
   else       wxszStrValue << wxT("false");
   return wxConfig::Write(wxszKey, wxszStrValue);
}

bool AFConfig::Write(const wxString& wxszKey, const int nValue)
{
    wxString wxszStrValue;
	wxszStrValue << nValue;
	return wxConfig::Write(wxszKey, wxszStrValue);
}

bool AFConfig::SetAudacityVersionNo(wxString& wxszValue)
{
   return wxConfig::Write(AUDACITY_VERSION_KEY, wxszValue); 
}

const wxChar* AFConfig::GetAudacityVersionNo()
{
    wxString wxszStrValue;
    if(!wxConfig::Read(AUDACITY_VERSION_KEY, &wxszStrValue))
    {
        wxszStrValue = wxT("1.3.14-alpha-Sep 22 2011");
        SetAudacityVersionNo(wxszStrValue);
    }
    return wxszStrValue.c_str();
}

AFConfig::AFConfig()
  : wxConfig(wxAURORA_NAME)
{}

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

