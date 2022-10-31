//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/cut.h"
#include "NangaParbat/datahandler.h"

#include <memory>

namespace NangaParbat
{
  class CutFactory
  {
  public:
    static std::shared_ptr<Cut> GetInstance(DataHandler const& dataset, std::string const& name, double const& min, double const& max, std::vector<double> const& params = {});
  };
}
