//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/cut.h"
#include <algorithm>

namespace NangaParbat
{
  /**
   * @brief Derivation of the class Cut to impose Cross Validation cut.
   * 
   */
  class TrainingCut: public Cut
  {
  public:
    /**
     * @brief The "Trainingcut" constructor
     * @param Cut: the cut object
     * @param TrainingFrac: Training fraction
     * @param TestingFrac: Testing fraction
     */
    TrainingCut(std::valarray<bool> const &KinematicMask, DataHandler const &dataset, double const &TrainingFrac, double const &TestingFrac=0);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();

  };
}
