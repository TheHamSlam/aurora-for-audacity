/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Time History Analyzer

  data.cpp

  Simone Campanini

*******************************************************************//**

\class AFTimeDataSerie
\brief The time data storage class.

*//*******************************************************************/

#include "data.h"

//----------------------------------------------------------------------------
// AFTimeDataSerie implementation
//----------------------------------------------------------------------------

void AFTimeDataSerie::Decimate(const size_t unWindowLength, double& dbTLo, double& dbTHi)
{
    //Samples that come in a single pixel
    AFSampleCount iMax = (AFSampleCount) floor( ((dbTHi - dbTLo) * m_dbRate)/unWindowLength );
    AFSampleCount k, i;

    for(k = 0; k < unWindowLength; k++)
    {
        if((i = k*iMax) > m_unVectorLength)
            m_aTData[k] = -200.0; // -infty
        else
            m_aTData[k] = m_pTVector[i] + m_dbFullScale;
    }
}


void AFTimeDataSerie::CalculateDataSerie(const size_t unWindowLength, double& dbTLo, double& dbTHi)
{
    // No calculation is needed: use existing datas.
    if(m_unLength != unWindowLength)
    {
        Destroy();
        m_unLength = unWindowLength;
        Init();
    }

    switch(m_nHandlerType)
    {
        case HT_RMS:       Rms(unWindowLength, dbTLo, dbTHi);      break;
        case HT_DECIMATE : Decimate(unWindowLength, dbTLo, dbTHi); break;
        default:           Decimate(unWindowLength, dbTLo, dbTHi); break;
    }

}

bool AFTimeDataSerie::IsOk(const double dbTLo, const double dbTHi)
{
    if((dbTLo < 0) || (dbTHi < 0))    // Time cannot be negative
        return false;

    if(dbTLo >= dbTHi)                // We cannot reverse time!
        return false;

    if((dbTHi-dbTLo) < 1.0/m_dbRate)  // Time interval smaller than
        return false;                 // sampling time are not accepted

    return true;
}

#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfAFTimeDataSerie);

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
