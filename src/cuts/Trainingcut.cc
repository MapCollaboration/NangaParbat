//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/Trainingcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  TrainingCut::TrainingCut(TrainingCut const& cut, bool const& invert, std::vector<std::shared_ptr<NangaParbat::Cut>> const& kincuts):
    Cut{cut},
    _NMin(cut._NMin)
  {
    if (invert)
      _mask = !_mask;
    for (auto const& c : kincuts)
      _mask *= c->GetMask();
  }

  //_________________________________________________________________________________
  TrainingCut::TrainingCut(DataHandler const& dataset, std::vector<std::shared_ptr<NangaParbat::Cut>> const& kincuts, double const& TrainingFrac, int const& NMin):
    Cut{dataset, TrainingFrac, 1 - TrainingFrac},
    _NMin(NMin)
  {
    _mask.resize(dataset.GetBinning().size(), true);
    for (auto const& c : kincuts)
      _mask *= c->GetMask();
    EnforceCut();
  }

  //_________________________________________________________________________________
  void TrainingCut::EnforceCut()
  {
    const int Ndat_aftercut = std::count(std::begin(_mask), std::end(_mask), true);
    if (Ndat_aftercut <= _NMin)
      return;

    std::vector<bool> random_mask(Ndat_aftercut * _min, true);
    random_mask.resize(Ndat_aftercut, false);
    std::random_shuffle(random_mask.begin(), random_mask.end());

    int j = 0;
    for (bool & m : _mask)
      m = (m ? random_mask[j++] : m);
  }
}
