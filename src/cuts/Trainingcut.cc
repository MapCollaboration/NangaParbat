//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/Trainingcut.h"

#include <gsl/gsl_randist.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  TrainingCut::TrainingCut(DataHandler                                    const& dataset,
                           std::vector<std::shared_ptr<NangaParbat::Cut>> const& kincuts,
                           double                                         const& TrainingFrac,
                           gsl_rng*                                              rng,
                           int                                            const& NMin):
    Cut{dataset, TrainingFrac, 1 - TrainingFrac},
    _rng(rng),
    _NMin(NMin)
  {
    _mask.resize(dataset.GetBinning().size(), true);
    for (auto const& c : kincuts)
      _mask *= c->GetMask();
    EnforceCut();
  }

  //_________________________________________________________________________________
  TrainingCut::TrainingCut(TrainingCut const& cut, bool const& invert, std::vector<std::shared_ptr<NangaParbat::Cut>> const& kincuts):
    Cut{cut},
    _rng(nullptr),
    _NMin(cut._NMin)
  {
    if (invert)
      _mask = !_mask;
    for (auto const& c : kincuts)
      _mask *= c->GetMask();
  }

  //_________________________________________________________________________________
  void TrainingCut::EnforceCut()
  {
    const int Ndat_aftercut = std::count(std::begin(_mask), std::end(_mask), true);
    if (Ndat_aftercut <= _NMin || _min == 1)
      return;

    bool random_mask[Ndat_aftercut];
    for (int i = 0; i < Ndat_aftercut; i++)
      if (i < floor(Ndat_aftercut * ( 1 - _min )))
        random_mask[i] = false;
      else
        random_mask[i] = true;
    gsl_ran_shuffle(_rng, random_mask, Ndat_aftercut, sizeof(bool));

    int j = 0;
    for (bool & m : _mask)
      m = (m ? random_mask[j++] : m);
  }
}
