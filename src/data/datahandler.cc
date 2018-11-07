//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/datahandler.h"

#include <iostream>

namespace NangaParbat
{
  //_________________________________________________________________________________
  DataHandler::DataHandler(std::string const& name, std::string const& datafolder):
    _datafolder(datafolder),
    _name(name)
  {
  }
}
