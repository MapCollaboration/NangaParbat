//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/cut.h"

namespace NangaParbat
{
  /**
   * @brief Derivation of the class Cut to impose cut on the variable
   * "x".
   */
  class XCut: public Cut
  {
  public:
    /**
     * @brief The "ZCut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     * @param xmin: mininum value
     * @param xmax: maximal value
     */
    XCut(DataHandler const& dataset, double const& xmin, double const& xmax);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();
  };
}
