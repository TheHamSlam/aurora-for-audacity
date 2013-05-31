/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Invert Kirkeby

  kirk.h

  Angelo Farina - Simone Campanini

***********************************************************************/
#ifndef __AURORA_KIRKEBY_KIRK_H__
#define __AURORA_KIRKEBY_KIRK_H__


#include <Audacity.h>
#include <widgets/ProgressDialog.h>

#include "afkirk.h"

#include <afconfig.h>

class Kirkeby : public AFKirkeby
{
  private:
     ProgressDialog *mProgressDlg;

     AFConfig mCfg;
     
  protected:
        
     void InitProgressMeter();
     void UpdateProgressMeter(int step, int total);
     void DestroyProgressMeter();

  public:
      void ReadConfigurationValues();
      void StoreConfigurationValues();
      
      Kirkeby(const int nRows = 1, const int nCols = 1);
      ~Kirkeby();
};

#endif // __AURORA_KIRKEBY_AFKIRK_H__

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


