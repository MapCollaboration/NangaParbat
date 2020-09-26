//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

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
     * @brief The "Cut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     */
    Cut(DataHandler const& dataset);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    virtual void EnforceCut() = 0;

    /**
     * @brief Function that returns the cut mask
     */
    std::vector<bool> GetMask() const { return _mask; }

  protected:
    DataHandler       const& _dataset; //!< The dataset to be processed
    std::vector<bool>        _mask;    //!< Cut mask 
  };
}
