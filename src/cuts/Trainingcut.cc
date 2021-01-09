//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/Trainingcut.h"

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

    std::vector<bool> random_mask(floor(Ndat_aftercut * ( 1 - _min )), false);
    random_mask.resize(Ndat_aftercut, true);
    std::random_shuffle(random_mask.begin(), random_mask.end(), [=] (long unsigned n) -> long unsigned { return gsl_rng_uniform_int(_rng, n); });

    int j = 0;
    for (bool & m : _mask)
      m = (m ? random_mask[j++] : m);
  }
}
