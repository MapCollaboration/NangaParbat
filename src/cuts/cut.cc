//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/cut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  Cut::Cut(DataHandler const& dataset, double const& min, double const& max):
    _dataset(dataset),
    _min(min),
    _max(max),
    _mask({})
  {
  }
}
