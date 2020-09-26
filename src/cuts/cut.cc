//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/cut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  Cut::Cut(DataHandler const& dataset):
    _dataset(dataset),
    _mask({})
  {
  }
}
