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

    for (int i = 0; i < (int) bins.size(); i++)  
      {
        double W2 = 0;
        if (bins[i].Intx)
          if (bins[i].IntQ)
	    W2 += pow(bins[i].Qmin, 2) * ( 1 / bins[i].xmax - 1 );
          else
	    W2 += pow(bins[i].Qav, 2) * ( 1 / bins[i].xmax - 1 );
        else
	  if (bins[i].IntQ)
	    W2 += pow(bins[i].Qmin, 2) * ( 1 / bins[i].xav - 1 );
	  else
	    W2 += pow(bins[i].Qav, 2) * ( 1 /bins[i].xav - 1 );
	_mask[i] = (sqrt(W2) > _min && sqrt(W2) < _max ? true : false);
      }
  }
}
