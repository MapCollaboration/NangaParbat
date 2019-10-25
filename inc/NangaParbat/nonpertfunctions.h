//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/DWS.h"
#include "NangaParbat/PV17.h"
#include "NangaParbat/PV19.h"
#include "NangaParbat/QGG6.h"
#include "NangaParbat/QGG12.h"

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
    {"DWS", new NangaParbat::DWS{}},
    {"PV17", new NangaParbat::PV17{}},
    {"PV19", new NangaParbat::PV19{}},
    {"QGG6", new NangaParbat::QGG6{}},
    {"QGG12", new NangaParbat::QGG12{}}
  };

  /**
   * @brief Utility function that returns a pointer to a
   * NangaParbat::Parameterisation object pointing to a specific
   * parameterisation.
   * @param name: name of the parameterisation
   */
  Parameterisation* GetParametersation(std::string const& name) { return AvPars.at(name); };
}
