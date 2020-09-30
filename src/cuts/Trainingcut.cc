//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/Trainingcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  TrainingCut::TrainingCut(std::valarray<bool> const &KinematicMask, DataHandler const &dataset, double const &TrainingFrac, double const &TestingFrac) : Cut{dataset, TrainingFrac, 1 - TrainingFrac}
  {
    _mask = KinematicMask;
    EnforceCut();
  }

  //_________________________________________________________________________________
  void TrainingCut::EnforceCut()
  {
    int Ndat_aftercut = std::count(&_mask[0], &_mask[_mask.size()-1], true);
    std::vector<bool> random_mask;

    if (Ndat_aftercut > 5)
    {
      int Ndat_training = int(Ndat_aftercut*_min);
      std::vector<bool> v_true;
      v_true.resize(Ndat_training, true);
      std::vector<bool> v_false;
      v_false.resize(Ndat_aftercut-Ndat_training, false);

      random_mask.insert(random_mask.end(), v_true.begin(), v_true.end());
      random_mask.insert(random_mask.end(), v_false.begin(), v_false.end());

      std::random_shuffle(random_mask.begin(), random_mask.end());

      int j=0;
      for (int i = 0; i < (int)_mask.size(); i++)
      {
        if (_mask[i])
        {
          _mask[i] = random_mask[j];
          j++;
        }
      }
    }
  }
}
