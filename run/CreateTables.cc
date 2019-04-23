//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"

#include <fstream>

#include <apfel/timer.h>

//_________________________________________________________________________________
// Define here the b* prescription
double bstar(double const& b, double const&)
{
  const double bmax = 1;
  return b / sqrt( 1 + pow(b / bmax, 2) );
}

//_________________________________________________________________________________
// b-min prescription
double bstarmin(double const& b, double const& Q)
{
  const double bmax = 1.122919;
  const double bmin = bmax / Q;
  const double bs = bmax * pow((1 - exp(-pow(b / bmax, 4)))/(1 - exp(-pow(b / bmin, 4))),0.25); // prescription with bmin
  return bs;
}

//_________________________________________________________________________________
// Main program
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if(argc < 4 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << std::endl;
      std::cout << "Invalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateTables <configuration file> <path to data folder> <output folder>" << std::endl;
      std::cout << std::endl;
      exit(-10);
    }

  // Allocate "FastInterface" object reading the parameters from an
  // input card.
  const NangaParbat::FastInterface FIObj{YAML::LoadFile(argv[1])};

  // Open datasets.yaml file that contains the list of tables to be
  // produced and push data sets into the a vector of DataHandler
  // objects.
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[2]) + "/datasets.yaml");
  std::vector<NangaParbat::DataHandler> DHVect;
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
	const std::string datafile = std::string(argv[2]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
	DHVect.push_back(NangaParbat::DataHandler{ds["name"].as<std::string>(), YAML::LoadFile(datafile)});
      }

  // Compute tables
  const std::vector<YAML::Emitter> Tabs = FIObj.ComputeTables(DHVect, bstarmin);

  // Dump table to file
  for (auto const& tab : Tabs)
    {
      std::ofstream fout(std::string(argv[3]) + YAML::Load(tab.c_str())["name"].as<std::string>() + ".yaml");
      fout << tab.c_str() << std::endl;
      fout.close();
    }

  return 0;
}
