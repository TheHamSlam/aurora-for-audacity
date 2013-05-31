/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Acoustical Parameters
  
  plot.h

  Simone Campanini

**********************************************************************/

#ifndef __AURORA_ACPARAM_PLOT__
#define __AURORA_ACPARAM_PLOT__

#include <afcharts.h>
#include <afscope.h>

#include "data.h"

class APAudioTrack;
class TSchroederDecay;

//----------------------------------------------------------------------------
// APDecayPlot declaration
//
/// \brief The decay plot for Acoustical Parameter module.
/// This class is designed to show a decay plot, tipically obtained from
/// a room Impulse Response by Schroeder backward integration.
//----------------------------------------------------------------------------
class APDecayPlot: public AFScope <TArrayOfAFTimeDataSerie, AFTimeDataSerie>
{
  public:
	/// Append data serie to plot.
	/// \param pData - a pointer to an object that holds decay datas
	void AddSerie(AFTimeDataSerie* pData); // Not exactly what I want: this is already defined in AFDataPlot!

	/// Append data serie to plot.
	/// \param psmpData - a pointer to a vector that holds decay datas
	/// \param unLength - data vector length
	/// \param dbRate - data sample rate in hertz
	/// \param nHandlerType - data handler identifier
	/// \param wxcolLine - line color
	/// \param wxcolBrush - brush color, not really necessary..
	void AddSerie(AFSample* psmpData,
			      const size_t unLength,
			      const double dbRate,
			      const int nHandlerType,
	              wxColour& wxcolLine = wxNullColour, wxColour& wxcolBrush = wxNullColour);

	void AddSerie(APAudioTrack& track,
			      const int nHandlerType,
	              wxColour& wxcolLine = wxNullColour, wxColour& wxcolBrush = wxNullColour);

	void AddSerie(TSchroederDecay& decay,
			      const int nHandlerType,
	              wxColour& wxcolLine = wxNullColour, wxColour& wxcolBrush = wxNullColour);

	/// Replace a data serie
	/// \param nIdx - index of data serie to be replaced
	/// \param psmpData - a pointer to a vector that holds new datas
	/// \param unLength - data vector length
    void ReplaceSerie(const size_t nIdx, AFSample* psmpData, const size_t unLength);
    void ReplaceSerie(const size_t nIdx, APAudioTrack& track);
    void ReplaceSerie(const size_t nIdx, TSchroederDecay& decay);

    /// The constructor
    /// \param parent - pointer to parent window/widget
    /// \param id - widget ID
    /// \param pos - widgets position
    /// \param size - widget size
    APDecayPlot(wxWindow *parent, wxWindowID id,
	            const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxSize(DECAY_PLOT_X_SIZE, DECAY_PLOT_Y_SIZE))
    : AFScope<TArrayOfAFTimeDataSerie, AFTimeDataSerie>(parent, id, pos, size)
    {}
};

//----------------------------------------------------------------------------
// APBarPlot declaration
//
/// \brief The decay plot for Acoustical Parameter module.
/// This class is used to represent graphically the values of the
/// acoustical parameters by octave band. Currently it accepts only
/// 12 values data series: the 10 octave bands, plus A filtered and
/// the flat average (Lin).
//----------------------------------------------------------------------------
class APBarPlot: public AFBarPlot<TArrayOfAFDataSerie, AFDataSerie>
{
  public:
    /// Append a data serie.
	/// \param adbData - vector holding the parameter values
	/// \param unLength - vector length...but for the current version
	///                   MUST be 12.
	/// \param wxcolLine - line color
	/// \param wxcolBrush - brush color, not really necessary..
   void AddSerie(const double* adbData,
		         const size_t unLength,
                 wxColour& wxcolLine = wxNullColour,
                 wxColour& wxcolBrush = wxNullColour);

    /// Replace a data serie
	/// \param nIdx - index of data serie to be replaced
	/// \param adbData - a pointer to a vector that holds new datas
	/// \param unLength - data vector length...12!
   void ReplaceSerie(const size_t nIdx, const double* adbData, const size_t unLength);

   /// Returns a pointer to horizontal axis.
   AFCategoriesAxis* GetBandsAxis() { return GetCategoriesAxis(); }

   /// The constructor
   /// \param parent - pointer to parent window/widget
   /// \param id - widget ID
   /// \param pos - widgets position
   /// \param size - widget size
   APBarPlot(wxWindow *parent,
		     wxWindowID id,
		     const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize)
   : AFBarPlot<TArrayOfAFDataSerie, AFDataSerie>(parent, id, pos, size)
   {}

};

#endif  // __AURORA_ACPARAM_PLOT__

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


