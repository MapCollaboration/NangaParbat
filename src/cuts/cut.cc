//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/cut.h"

namespace NangaParbat
{

  //_________________________________________________________________________________
  Cut::Cut(Cut const &cut):
    _dataset(cut._dataset),
    _min(cut._min),
    _max(cut._max),
    _mask(cut._mask)
  {
  }
  
  //_________________________________________________________________________________
  Cut::Cut(DataHandler const& dataset, double const& min, double const& max):
    _dataset(dataset),
    _min(min),
    _max(max),
    _mask({})
  {
  }

}
