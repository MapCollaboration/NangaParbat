//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"

#include <iostream>
#include <fstream>
#include <math.h>

#include <apfel/timer.h>

//_________________________________________________________________________________
// Non-perturnative function
double fNP(double const&, double const& b, double const& zetaf)
{
  const double g1 = 0.02;
  const double g2 = 0.5;
  const double Q0 = 1.6;
  return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );
}

//_________________________________________________________________________________
// Main program
int main()
{
  // Vector of datafiles
  std::vector<NangaParbat::DataHandler> DHVect;

  // Test data
  DHVect.push_back(NangaParbat::DataHandler{"Test_data", YAML::LoadFile("../data/TestData/Table1.yaml")});
  // Push back CDF Run I
  //DHVect.push_back(NangaParbat::DataHandler{"CDF_Run_I", YAML::LoadFile("../data/HEPData-ins505738-v1-yaml/Table1.yaml")});

  // Allocate "FastInterface" object
  const NangaParbat::FastInterface FIObj{YAML::LoadFile("../cards/config.yaml")};

  // Compute tables
  const std::vector<YAML::Emitter> Tabs = FIObj.ComputeTables(DHVect);

  // Convolute table
  for (auto const& tab : Tabs)
    {
      // Convolution
      const NangaParbat::ConvolutionTable CTable{YAML::Load(tab.c_str())};
      for (auto const& p : CTable.Convolute(fNP))
	std::cout << p.first << "  " << p.second << std::endl;

      // Dump table to file
      std::ofstream fout("../tables/" + YAML::Load(tab.c_str())["name"].as<std::string>() + ".yaml");
      fout << tab.c_str() << std::endl;
      fout.close();

      // Performance test
      apfel::Timer t;
      for (int i = 0; i < 8000; i++)
	for (auto const& p : CTable.Convolute(fNP))
	  p.second;
      t.stop(true);
    }

  return 0;
}
