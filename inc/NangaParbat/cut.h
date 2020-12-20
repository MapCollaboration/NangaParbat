//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <valarray>

#include "NangaParbat/datahandler.h"

namespace NangaParbat
{
  /**
   * @brief Purely virtual mother class that implements the main
   * feautures of a cut function on a given dataset. Given a
   * DataHandler object as an input, it returns a mask of bools that
   * selects the points that pass the specific cut.
   */
  class Cut
  {
  public:
    /**
     * @brief The "Cut" copy constructor
     * @param cut: objects to be copied
     */
    Cut(Cut const& cut);

    /**
     * @brief The "Cut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     * @param min: mininum value
     * @param max: maximal value
     */
    Cut(DataHandler const& dataset, double const& min, double const& max);

    /**
     * @brief The "Cut" destructor
     */
    virtual ~Cut() {};

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    virtual void EnforceCut() = 0;

    /**
     * @brief Function that returns the cut mask
     */
    std::valarray<bool> GetMask() const { return _mask; }

  protected:
    DataHandler         const& _dataset; //!< The dataset to be processed
    double              const  _min;     //!< Minimal value
    double              const  _max;     //!< Maximal value
    std::valarray<bool>        _mask;    //!< Cut mask
  };
}
