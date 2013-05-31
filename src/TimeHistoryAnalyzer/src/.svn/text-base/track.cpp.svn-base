/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection

  Time History Analyzer

  track.cpp

  Angelo Farina - Simone Campanini

**********************************************************************/

#include "track.h"

//----------------------------------------------------------------------------
// THASignalAudioTrack implementation
//----------------------------------------------------------------------------
void THASignalAudioTrack::Filter(const int nCh)
{
#ifdef __AUDEBUG__
   printf("[THASignalAudioTrack] FilterType : %d\n", m_nSelectedFilter);
#endif
   ResetFilteredTrack(nCh);

   switch(m_nSelectedFilter)
   {
       case FLT_LIN: LFilter(nCh);            break;
       case FLT_ITU: ITU_P56_Filter(nCh);     break;
       case FLT_IEC: AFilter(nCh);            break;
       case FLT_ISO: ISO_8041_Filter(nCh);    break;
       case FLT_UNI: UNI_9916_Filter(nCh);    break;
   }
}


#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfTHASignalAudioTrack);

//----------------------------------------------------------------------------
// THACalibrationAudioTrack implementation
//----------------------------------------------------------------------------
#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(TArrayOfTHACalibrationAudioTrack);


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
