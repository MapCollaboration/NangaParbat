//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/wcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  WCut::WCut(DataHandler const& dataset, double const& Wmin, double const& Wmax):
    Cut{dataset, Wmin, Wmax}
  {
    EnforceCut();
  }

  //_________________________________________________________________________________
  void WCut::EnforceCut()
  {
    const std::vector<DataHandler::Binning> bins = _dataset.GetBinning();
    _mask.resize(bins.size());

    double W;
    for (int i = 0; i < (int) bins.size(); i++)  
      {
        W = pow(apfel::ProtonMass, 2);
        if (bins[i].Intx)
          if (bins[i].IntQ)
            {
              W += pow(bins[i].Qmin, 2) * (1/bins[i].xmax - 1);
              W = sqrt(W);
              _mask[i] = ( W - _min > 0 && W - _max < 0 ? true : false);
            }
          else
            {
              W += pow(bins[i].Qmin,2) * (1/bins[i].xav - 1);
              W = sqrt(W);
              _mask[i] = ( W - _min > 0 && W - _max < 0 ? true : false);
            }
        else if (bins[i].IntQ)
          {
            W += pow(bins[i].Qav, 2) * (1/bins[i].xmax - 1);
            W = sqrt(W);
            _mask[i] = ( W - _min > 0 && W - _max < 0 ? true : false);
          }
        else 
          {
            W = pow(bins[i].Qav, 2) * (1/bins[i].xav - 1);
            W = sqrt(W);
            _mask[i] = (W > _min && W < _max ? true : false); 
          } 
      }    
  }
}