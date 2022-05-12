//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/DWS.h"
#include "NangaParbat/PV17.h"
#include "NangaParbat/PV19.h"
#include "NangaParbat/PV19b.h"
#include "NangaParbat/PV19x.h"
#include "NangaParbat/MAP21test.h"
#include "NangaParbat/QGG6.h"
#include "NangaParbat/QGG13.h"
#include "NangaParbat/MAPTMDPion.h"
#include "NangaParbat/PV17Pion.h"
#include "NangaParbat/MAPTMDPion3.h"
#include "NangaParbat/MAPTMDPionw3.h"
#include "NangaParbat/MAPTMDPionwx4.h"
// #include "NangaParbat/MAPTMDPionw2x4.h"
// #include "NangaParbat/MAPTMDPionwx5.h"
// #include "NangaParbat/MAPTMDPionwx7.h"

#include <map>
#include <memory>

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
    //{"PV19",  new NangaParbat::PV19{}},
    {"PV19b", new NangaParbat::PV19b{}},
    {"PV19x", new NangaParbat::PV19x{}},
    {"MAP21test", new NangaParbat::MAP21test{}},
    {"PV17Pion",  new NangaParbat::PV17Pion{}},
    {"MAPTMDPion", new NangaParbat::MAPTMDPion{}},
    {"MAPTMDPion3", new NangaParbat::MAPTMDPion3{}},
    {"MAPTMDPionw3", new NangaParbat::MAPTMDPionw3{}},
    {"MAPTMDPionwx4", new NangaParbat::MAPTMDPionwx4{}}//,
    // {"MAPTMDPionw2x4", new NangaParbat::MAPTMDPionw2x4{}},
    // {"MAPTMDPionwx5", new NangaParbat::MAPTMDPionwx5{}},
    // {"MAPTMDPionwx7", new NangaParbat::MAPTMDPionwx7{}}
    //{"QGG6",  new NangaParbat::QGG6{}},
    //{"QGG13", new NangaParbat::QGG13{}}
  };
  /*
  const std::map<std::string, std::shared_ptr<Parameterisation>> AvParsSptr
  {
    {"DWS",   std::shared_ptr<NangaParbat::DWS>{new NangaParbat::DWS{}}},
    {"PV17",  std::shared_ptr<NangaParbat::PV17>{new NangaParbat::PV17{}}},
    //{"PV19",  std::shared_ptr<NangaParbat::PV19>{new NangaParbat::PV19{}}},
    {"PV19b", std::shared_ptr<NangaParbat::PV19b>{new NangaParbat::PV19b{}}},
    {"PV19x", std::shared_ptr<NangaParbat::PV19x>{new NangaParbat::PV19x{}}}//,
    //{"QGG6",  std::shared_ptr<NangaParbat::QGG6>{new NangaParbat::QGG6{}}},
    //{"QGG13", std::shared_ptr<NangaParbat::QGG13>{new NangaParbat::QGG13{}}}
  };
  */
  /**
   * @brief Utility function that returns a pointer to a
   * NangaParbat::Parameterisation object pointing to a specific
   * parameterisation.
   * @param name: name of the parameterisation
   */
  Parameterisation* GetParametersation(std::string const& name);
}
