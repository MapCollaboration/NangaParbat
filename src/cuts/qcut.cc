//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/qcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  QCut::QCut(DataHandler const& dataset, double const& Qmin, double const& Qmax):
    Cut{dataset, Qmin, Qmax}
  {
    EnforceCut();
  }

  //_________________________________________________________________________________
  void QCut::EnforceCut()
  {
    const std::vector<DataHandler::Binning> bins = _dataset.GetBinning();
    _mask.resize(bins.size());
    for (int i = 0; i < (int) bins.size(); i++)
      if (bins[i].IntQ)
        _mask[i] = (bins[i].Qmin > _min && bins[i].Qmax < _max ? true : false);
      else
        _mask[i] = (bins[i].Qav > _min && bins[i].Qav < _max ? true : false);
  }
}
