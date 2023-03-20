//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/xcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  XCut::XCut(DataHandler const& dataset, double const& xmin, double const& xmax):
    Cut{dataset, xmin, xmax}
  {
    EnforceCut();
  }

  //_________________________________________________________________________________
  void XCut::EnforceCut()
  {
    const std::vector<DataHandler::Binning> bins = _dataset.GetBinning();
    _mask.resize(bins.size());
    for (int i = 0; i < (int) bins.size(); i++)
      if (bins[i].Intx)
        _mask[i] = (bins[i].xmin > _min && bins[i].xmax < _max ? true : false);
      else
        _mask[i] = (bins[i].xav > _min && bins[i].xav < _max ? true : false);
  }
}
