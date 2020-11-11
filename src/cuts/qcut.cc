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
      _mask[i] = (bins[i].Qav > _min && bins[i].Qav < _max ? true : false);
  }
}
