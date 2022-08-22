//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/xzcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  XZCut::XZCut(DataHandler const& dataset, double const& betamin, double const& betamax, double const& alpha):
    Cut{dataset, betamin, betamax},
    _alpha(alpha)
  {
    EnforceCut();
  }

  //_________________________________________________________________________________
  void XZCut::EnforceCut()
  {
    const std::vector<DataHandler::Binning> bins = _dataset.GetBinning();
    _mask.resize(bins.size());
    for (int i = 0; i < (int) bins.size(); i++)
      if (bins[i].Intz)
        if (bins[i].Intx)
          _mask[i] = (bins[i].zmin - _alpha * bins[i].xmin - _min > 0 && bins[i].zmin - _alpha * bins[i].xmin - _max < 0 ? true : false);
        else
          _mask[i] = (bins[i].zmin - _alpha * bins[i].xav - _min > 0 && bins[i].zmin - _alpha * bins[i].xav - _max < 0 ? true : false);
      else if (bins[i].Intx)
        _mask[i] = (bins[i].zav - _alpha * bins[i].xmin - _min > 0 && bins[i].zav - _alpha * bins[i].xmin - _max < 0 ? true : false);
      else
        _mask[i] = (bins[i].zav - _alpha * bins[i].xav - _min > 0 && bins[i].zav - _alpha * bins[i].xav - _max < 0 ? true : false);
  }

  //_________________________________________________________________________________
  XZCutQuadratic::XZCutQuadratic(DataHandler const& dataset, double const& betamin, double const& betamax):
    Cut{dataset, betamin, betamax}
  {
    EnforceCut();
  }

  //_________________________________________________________________________________
  void XZCutQuadratic::EnforceCut()
  {
    const std::vector<DataHandler::Binning> bins = _dataset.GetBinning();
    _mask.resize(bins.size());
    for (int i = 0; i < (int) bins.size(); i++)
      if (bins[i].Intz)
        if (bins[i].Intx)
          _mask[i] = (pow(bins[i].zmin, 2) + pow(bins[i].xmin, 2) > _min && pow(bins[i].zmin, 2) + pow(bins[i].xmin, 2) < _max ? true : false);
        else
          _mask[i] = (pow(bins[i].zmin, 2) + pow(bins[i].xav, 2) > _min && pow(bins[i].zmin, 2) + pow(bins[i].xav, 2) < _max ? true : false);
      else if (bins[i].Intx)
        _mask[i] = (pow(bins[i].zav, 2) + pow(bins[i].xmin, 2) > _min && pow(bins[i].zav, 2) + pow(bins[i].xmin, 2) < _max ? true : false);
      else
        _mask[i] = (pow(bins[i].zav, 2) + pow(bins[i].xav, 2) > _min && pow(bins[i].zav, 2) + pow(bins[i].xav, 2) < _max ? true : false);
  }
}
