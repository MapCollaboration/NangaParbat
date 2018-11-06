//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/computetables.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/testdata.h"

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
int main(int argc, char **argv)
{
  if (argc != 2)
    {
      std::cout << "\nusage: ./CreateTable config.yaml\n" << std::endl;
      exit(-1);
    }

  // Compute table
  const YAML::Node config  = YAML::LoadFile(argv[1]);
  const std::vector<NangaParbat::DataHandler> DHVect = {NangaParbat::TestData{13000, 66, 116, -1, 1, {1, 3}}};
  const std::vector<YAML::Emitter> Tabs = NangaParbat::ComputeTables(config, DHVect);

  // Convolute table
  for (auto const& tab : Tabs)
    {
      // Convolution
      const NangaParbat::ConvolutionTable CTable{YAML::Load(tab.c_str())};
      for (auto const& p : CTable.Convolute(fNP))
	std::cout << p.first << "  " << p.second << std::endl;

      // Dump table to file
      std::ofstream fout("../tables/" + YAML::Load(tab.c_str())["name"].as<std::string>());
      fout << tab.c_str() << std::endl;
      fout.close();

      // Performance test
      apfel::Timer t;
      for (int i = 0; i < 8000; i++)
	for (auto const& p : CTable.Convolute(fNP))
	  p.second;
      t.stop();
    }

  return 0;
}
