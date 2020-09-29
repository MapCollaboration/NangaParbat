//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/cutfactory.h"
#include "NangaParbat/zcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::shared_ptr<Cut> CutFactory::GetInstance(DataHandler const& dataset, std::string const& name, double const& min, double const& max)
  {
    if (name == "zcut")
      return std::shared_ptr<NangaParbat::ZCut> {new NangaParbat::ZCut{dataset, min, max}};
    else
      throw std::runtime_error("[CutFactory::GetInstance]: Unknown cut.");
  }
}
