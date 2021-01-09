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
     * @param dataset: the DataHandler object subject to the cuts
     * @param kincuts: the vector kinematic cuts
     * @param TrainingFrac: Training fraction
     * @param rng: GSL random number object
     * @param NMin: Minimum number of points below which all points will be included in the training (default: 5)
     */
    TrainingCut(DataHandler                                    const& dataset,
                std::vector<std::shared_ptr<NangaParbat::Cut>> const& kincuts,
                double                                         const& TrainingFrac,
                gsl_rng*                                              rng,
                int                                            const& NMin = 10);

    /**
     * @brief The "TrainingCut" copy constructor
     * @param cut: objects to be copied
     * @param invert: whether to invert the map (default: false)
     * @param kincuts: vector of possible kinematic cuts to enforce (default: empty)
     */
    TrainingCut(TrainingCut const& cut, bool const& invert = false, std::vector<std::shared_ptr<NangaParbat::Cut>> const& kincuts = {});

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();
  private:
    gsl_rng* const _rng;
    int      const _NMin;
  };
}
