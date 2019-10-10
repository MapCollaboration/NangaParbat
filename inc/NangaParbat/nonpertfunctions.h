//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/DWS.h"
#include "NangaParbat/PV17.h"
#include "NangaParbat/PV19.h"
#include "NangaParbat/QGG6.h"
#include "NangaParbat/QGG12.h"

namespace NangaParbat
{
  Parameterisation* GetParametersation(std::string const& name)
  {
    Parameterisation *NPFunc;
    if (name == "DWS")
      NPFunc = new NangaParbat::DWS{};
    else if (name == "PV17")
      NPFunc = new NangaParbat::PV17{};
    else if (name == "PV19")
      NPFunc = new NangaParbat::PV19{};
    else if (name == "QGG6")
      NPFunc = new NangaParbat::QGG6{};
    else if (name == "QGG12")
      NPFunc = new NangaParbat::QGG12{};
    else
      throw std::runtime_error("[GetParametersation]: Unknown parameterisation");

    return NPFunc;
  }
}
