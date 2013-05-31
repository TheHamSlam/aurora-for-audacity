/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  track.cpp

  Angelo Farina - Simone Campanini

***********************************************************************/

#include "track.h"

bool STIAudioTrack::FindFirstArrivalTime(const double dbThreshold, const int nCh)
{
    if(m_pdbMax[nCh] == 0.0) FindMax(nCh);
    
    double dbRelativeThreshold = dbThreshold * m_pdbMax[nCh];
    
    m_psmpcFAT[nCh] = 0;
    while( (m_psmpcFAT[nCh] < m_smpcLen) && 
           (fabs(m_apsmpTrack[nCh][m_psmpcFAT[nCh]++]) < dbRelativeThreshold) );
    
    AFSampleCount smpc1ms = AFSampleCount(0.001 * m_dbRate);
    if(m_psmpcFAT[nCh] > smpc1ms) 
        m_psmpcFAT[nCh] -= smpc1ms;
    else
        m_psmpcFAT[nCh] = 0;
    
    if(m_psmpcFAT[nCh] == m_smpcLen) return false;
    return true;    
}

void STIAudioTrack::STIOctaveFilter(const int nCh, const double dbFc)
{
    // A.Farina
    // Slightly modified (coefficients) octave filter for STI
    // calculations (but I don't know really)
    
    double f0, fQ;
    // Band filtering with six-poles IIR filter
    // first filter (2 poles)
    f0 = 0.75f * dbFc;
    fQ = 8.0f;
    Filter(BPF, nCh, f0, fQ); 
    // second filter (2 poles)
    f0 = dbFc;
    fQ = 4.0f;
    Filter(BPF, nCh, f0, fQ); 
    // third filter (2 poles)
    f0 = 1.3f * dbFc;
    fQ = 8.0f;
    Filter(BPF, nCh, f0, fQ); 
}

void STIAudioTrack::CalculateMTF(const int nCh, double* adbMTFTable)
{
    double dbSum = 0.0; // TODO: this should be a class attribute
    double dbSinTot, dbCosTot;
    double adbOM[] = {0.63, 0.8, 1.0, 1.25, 1.6, 2.0, 2.5, 3.15, 4.0, 5.0, 6.3, 8.0, 10.0, 12.5};
        
    AFSample* psmpTrackSqm = new AFSample [m_smpcLen];  //TODO: This should be done only one time in the class!
    
    AFSampleCount n;
    for(n = 0; n < m_smpcLen; n++)   //TODO: This should be done only one time in the class!
    {
        psmpTrackSqm[n] = m_apsmpFilteredTrack[nCh][n] * m_apsmpFilteredTrack[nCh][n];
        dbSum += psmpTrackSqm[n];
    }
    
    AFSampleCount k;
    for(k = 0; k < 14; k++)
    {
        dbCosTot = 0.0;
        dbSinTot = 0.0;
        for(n = m_psmpcFAT[nCh]; n < m_smpcLen; n++)
        {
            dbCosTot += psmpTrackSqm[n] * cos(2*M_PI*adbOM[k]*(n - m_psmpcFAT[nCh])/m_dbRate);
            dbSinTot += psmpTrackSqm[n] * sin(2*M_PI*adbOM[k]*(n - m_psmpcFAT[nCh])/m_dbRate);
        }
        adbMTFTable[k] = sqrt(dbCosTot*dbCosTot + dbSinTot*dbSinTot) / dbSum;
    }
    delete [] psmpTrackSqm;
}

void STIAudioTrack::CalculateMTF_STItel(const int nCh, const int nBand, double* adbMTF_STItel)
{
    double dbSum = 0.0;
    double dbSinTot, dbCosTot;
    double adbOMSTItel[] = {1.12, 11.33, 0.71, 2.83, 6.97, 1.78, 4.53};
        
    AFSample* psmpTrackSqm = new AFSample [m_smpcLen];
    
    AFSampleCount n;
    for(n = 0; n < m_smpcLen; n++)
    {
        psmpTrackSqm[n] = m_apsmpFilteredTrack[nCh][n] * m_apsmpFilteredTrack[nCh][n];
        dbSum += psmpTrackSqm[n];
    }
    
    dbCosTot = 0.0;
    dbSinTot = 0.0;
    for(n = m_psmpcFAT[nCh]; n < m_smpcLen; n++)
    {
        dbCosTot += psmpTrackSqm[n] * cos(2*M_PI*adbOMSTItel[nBand-2]*(n - m_psmpcFAT[nCh])/m_dbRate);
        dbSinTot += psmpTrackSqm[n] * sin(2*M_PI*adbOMSTItel[nBand-2]*(n - m_psmpcFAT[nCh])/m_dbRate);
    }
    adbMTF_STItel[nBand-2] = sqrt(dbCosTot*dbCosTot + dbSinTot*dbSinTot) / dbSum;
    
    delete [] psmpTrackSqm;
}

void STIAudioTrack::CalculateMTF_RaSTI(const int nCh, double* adbMTF_RaSTITable)
{
    double dbSum = 0.0;
    double dbSinTot, dbCosTot;
    double adbOMRaSTI[] = {0.7, 1.4, 2.8, 5.6, 11.2};
        
    AFSample* psmpTrackSqm = new AFSample [m_smpcLen];
    
    AFSampleCount n;
    for(n = 0; n < m_smpcLen; n++)
    {
        psmpTrackSqm[n] = m_apsmpFilteredTrack[nCh][n] * m_apsmpFilteredTrack[nCh][n];
        dbSum += psmpTrackSqm[n];
    }
    
    AFSampleCount k;
    for(k = 0; k < 5; k++)
    {
        dbCosTot = 0.0;
        dbSinTot = 0.0;
        for(n = m_psmpcFAT[nCh]; n < m_smpcLen; n++)
        {
            dbCosTot += psmpTrackSqm[n] * cos(2*M_PI*adbOMRaSTI[k]*(n - m_psmpcFAT[nCh])/m_dbRate);
            dbSinTot += psmpTrackSqm[n] * sin(2*M_PI*adbOMRaSTI[k]*(n - m_psmpcFAT[nCh])/m_dbRate);
        }
        adbMTF_RaSTITable[k] = sqrt(dbCosTot*dbCosTot + dbSinTot*dbSinTot) / dbSum;
    }
    delete [] psmpTrackSqm;
}

STIAudioTrack::STIAudioTrack(const int nChannels, const double dbRate)
 : AFAudioTrack( dbRate, nChannels)
 { }
 
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
 
