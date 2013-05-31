/**********************************************************************
 * 
 *  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 *                       plugin collection
 *
 *  Common libraries
 *
 *  afktrack.h
 *
 *  Angelo Farina - Simone Campanini
 *
 **********************************************************************/
#ifndef __AF_KTRACK_H__
#define __AF_KTRACK_H__

#include <commdefs.h>
#include <afvector.h>
#include <afcomplex.h>


class AFKTrack : public AFVector<AFSample>, AFComplexVector<fftwf_complex, float>
{
  private:
    double  m_dbSamplerate;
    char    m_szName [255];
      
  public:
    void FFT();
    void IFFT();

    // operators
    const AFKTrack& operator=(const AFKTrack& Right);
    
    // Init/deinit
    bool Create(const AFSampleCount smpcLength = 0, const double dbSamplerate = 48000);
    bool Destroy();
    
    // Get-setters
    const char* GetName() const { return m_szName; }
    void SetName(const char* pszName) { strcpy(m_szName, pszName); }

    // 'ctors
    AFKTrack();
    AFKTrack(const AFSampleCount smpcLength, const double dbSamplerate = 48000, const char* pszName = 0);
    ~AFKTrack();
};

#endif // __AF_KTRACK_H__


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
