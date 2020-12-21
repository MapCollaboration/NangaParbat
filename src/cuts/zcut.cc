//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/zcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  ZCut::ZCut(DataHandler const& dataset, double const& zmin, double const& zmax):
    Cut{dataset, zmin, zmax}
  {
    EnforceCut();
  }

  //_________________________________________________________________________________
  void ZCut::EnforceCut()
  {
    const std::vector<DataHandler::Binning> bins = _dataset.GetBinning();
    _mask.resize(bins.size());
    for (int i = 0; i < (int) bins.size(); i++)
      if (bins[i].Intz)
        _mask[i] = (bins[i].zmin > _min && bins[i].zmax < _max ? true : false);
      else
        _mask[i] = (bins[i].zav > _min && bins[i].zav < _max ? true : false);
  }
}
