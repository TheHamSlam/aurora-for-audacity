/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Speech Transmission Index evaluator

  track.h

  Angelo Farina - Simone Campanini

***********************************************************************/
#ifndef __STI_TRACK_H__
#define __STI_TRACK_H__

#include <afaudio.h>

class STIAudioTrack : public AFAudioTrack
{
/*
 protected:
	double FindMax(const int nCh) { return 1.0; } // *** DEBUG
    double FindMin(const int nCh) { return 0.0; } // *** DEBUG
*/	
public:  
      bool FindFirstArrivalTime(const double dbThreshold, const int nCh);
      
      void STIOctaveFilter(const int nCh, const double dbFc);
      void CalculateMTF(const int nCh, double *adbMTFTable);    
      void CalculateMTF_STItel(const int nCh, const int nBand, double* adbMTF_STItel);
      void CalculateMTF_RaSTI(const int nCh, double *adbMTF_RaSTITable);
      
     // --- Ctors
      STIAudioTrack(const int nChannels = 1, const double dbRate = 44100.0);
};

#endif //__STI_TRACK_H__

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
