//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/DWS.h"
#include "NangaParbat/PV17.h"
#include "NangaParbat/PV19.h"
#include "NangaParbat/PV19b.h"
#include "NangaParbat/QGG6.h"
#include "NangaParbat/QGG13.h"

#include<map>

namespace NangaParbat
{
  /**
   * @brief Map of currently available parameterisations. Each of them
   * must correspond to a header file containing a class deriving from
   * the NangaParbat::Parameterisation mother class.
   */
  const std::map<std::string, Parameterisation*> AvPars
  {
    {"DWS",   new NangaParbat::DWS{}},
    {"PV17",  new NangaParbat::PV17{}},
    {"PV19",  new NangaParbat::PV19{}},
    {"PV19b", new NangaParbat::PV19b{}},
    {"QGG6",  new NangaParbat::QGG6{}},
    {"QGG13", new NangaParbat::QGG13{}}
  };

  /**
   * @brief Utility function that returns a pointer to a
   * NangaParbat::Parameterisation object pointing to a specific
   * parameterisation.
   * @param name: name of the parameterisation
   */
  Parameterisation* GetParametersation(std::string const& name) { return AvPars.at(name); };
}
