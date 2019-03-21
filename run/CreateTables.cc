//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"

#include <fstream>

#include <apfel/timer.h>

//_________________________________________________________________________________
double bstar(double const& b, double const&)
{
  const double bmax = 1;
  return b / sqrt( 1 + pow(b / bmax, 2) );
}

//_________________________________________________________________________________
// Main program
int main()
{
  // Allocate "FastInterface" object reading the parameters from an
  // input card.
  const NangaParbat::FastInterface FIObj{YAML::LoadFile("../cards/config.yaml")};

  // Vector of datafiles
  std::vector<NangaParbat::DataHandler> DHVect;
  // Test data
  //DHVect.push_back(NangaParbat::DataHandler{"Test_data", YAML::LoadFile("../data/TestData/Table1.yaml")});
  // Push back CDF Run I
  //DHVect.push_back(NangaParbat::DataHandler{"CDF_RunI", YAML::LoadFile("../data/CDF_RunI/CDF_RunI.yaml")}); \
  // Push back CDF Run II
  DHVect.push_back(NangaParbat::DataHandler{"CDF_RunII", YAML::LoadFile("../data/CDF_RunII/CDF_RunII.yaml")});
  // Push back D0 Run I
  //DHVect.push_back(NangaParbat::DataHandler{"D0_RunI", YAML::LoadFile("../data/D0_RunI/D0_RunI.yaml")}); \
  // Push back D0 Run II
  //DHVect.push_back(NangaParbat::DataHandler{"D0_RunII", YAML::LoadFile("../data/D0_RunII/D0_RunII.yaml")});

  // Compute tables
  const std::vector<YAML::Emitter> Tabs = FIObj.ComputeTables(DHVect, bstar);

  // Dump table to file
  for (auto const& tab : Tabs)
    {
      std::ofstream fout("../tables/" + YAML::Load(tab.c_str())["name"].as<std::string>() + ".yaml");
      fout << tab.c_str() << std::endl;
      fout.close();
    }

  return 0;
}
