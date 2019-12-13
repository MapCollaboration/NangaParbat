//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/factories.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  TMDGrid* mkTMD(std::string const& name, int const& mem)
  {
    return new NangaParbat::TMDGrid{YAML::LoadFile(name + "/" + name + ".info"),
                                    YAML::LoadFile(name + "/" + name + "_" + std::to_string(mem) + ".yaml")};
  }

  //_________________________________________________________________________________
  std::vector<TMDGrid*> mkTMDs(std::string const& name)
  {
    const YAML::Node info = YAML::LoadFile(name + "/" + name + ".info");
    const int nmem = info["NumMembers"].as<int>();
    std::vector<TMDGrid*> tmds(nmem);
    for (int mem = 0; mem < nmem; mem++)
      tmds[mem] = new NangaParbat::TMDGrid{info, YAML::LoadFile(name + "/" + name + std::to_string(mem) + ".yaml")};
    return tmds;
  }
}
