//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/chisquare.h"

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
double bstar(double const& b, double const&)
{
  const double bmax = 1;
  return b / sqrt( 1 + pow(b / bmax, 2) );
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
  const std::vector<YAML::Emitter> Tabs = FIObj.ComputeTables(DHVect, bstar);

  // Dump table to file
  for (auto const& tab : Tabs)
    {
      std::ofstream fout("../tables/" + YAML::Load(tab.c_str())["name"].as<std::string>() + ".yaml");
      fout << tab.c_str() << std::endl;
      fout.close();
    }

  // Define Chi2 object
  NangaParbat::ChiSquare chi2;

  // Convolute table
  for (int j = 0; j < (int) Tabs.size(); j++)
    {
      // Convolution table
      const NangaParbat::ConvolutionTable CTable{YAML::Load(Tabs[j].c_str())};

      // Append dataset to the chi2 object
      chi2.AddBlock(std::make_pair(DHVect[j], CTable));

      for (auto const& p : CTable.GetPredictions(fNP))
	std::cout << p << std::endl;

      // Compute chi2
      std::cout << chi2.Evaluate(fNP) << std::endl;

      // Performance test
      //apfel::Timer t;
      //for (int i = 0; i < 8000; i++)
      //  for (auto const& p : CTable.Convolute(fNP))
      //    p.second;
      //t.stop(true);
    }
  return 0;
}
