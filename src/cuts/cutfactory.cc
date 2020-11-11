//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/cutfactory.h"
#include "NangaParbat/zcut.h"
#include "NangaParbat/qcut.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::shared_ptr<Cut> CutFactory::GetInstance(DataHandler const& dataset, std::string const& name, double const& min, double const& max)
  {
    if (name == "zcut")
      return std::shared_ptr<NangaParbat::Cut> {new NangaParbat::ZCut{dataset, min, max}};
    else if (name == "Qcut")
      return std::shared_ptr<NangaParbat::Cut> {new NangaParbat::QCut{dataset, min, max}};
    else
      throw std::runtime_error("[CutFactory::GetInstance]: Unknown cut.");
  }
}
