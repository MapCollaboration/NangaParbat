//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//         Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/factories.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"

#include <LHAPDF/LHAPDF.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 5 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./GridInterpolation <grid main folder> <grid name> <n. repl.> <output>\n" << std::endl;
      exit(-10);
    }

  const std::string Folder = std::string(argv[1]);
  const std::string Name   = std::string(argv[2]);
  const std::string Output = std::string(argv[4]);

  // Select flavour
  const int ifl = 2; // quark up

  // Read Kinematics
  YAML::Node kin = YAML::LoadFile("inputs/GridInterpolation.yaml");

  const std::vector<double> kTg = kin["qToQ"].as<std::vector<double>>();
  const std::vector<double> Qg  = kin["Q"].as<std::vector<double>>();
  const std::vector<double> xg  = kin["x"].as<std::vector<double>>();
  const std::vector<double> zg  = kin["z"].as<std::vector<double>>();

  // ===========================================================================
  // Read info file
  std::cout << "\n";
  std::cout << "Reading info file: "  + Folder + "/"  + Name + "/" + Name + ".info" +  "  ..." << std::endl;
  YAML::Node const& infofile = YAML::LoadFile(Folder + "/"  + Name + "/" + Name + ".info");

  // Read type of TMD distribution
  const std::string pf = infofile["TMDType"].as<std::string>();

  // Create directory to store the output
  mkdir(Output.c_str(), ACCESSPERMS);
  std::cout << "Creating folder " + Output << std::endl;
  std::cout << "\n";

  // Start intepolation
  std::cout << "Starting interpolation of " + std::string(argv[2]) +  " ..." << std::endl;

  // Read TMDs in grid
  NangaParbat::TMDGrid* TMDs = NangaParbat::mkTMD(Name, Folder, std::stoi(argv[3]));

  // Read grids and test interpolation
  for (int iq = 0; iq < (int) Qg.size(); iq++)
    {
      const double Q  = Qg[iq];
      
      for (int ix = 0; ix < (int) xg.size(); ix++)
        {
          const double x  = xg[ix];

          /*
          // Values of kT
          const double kTmin = Q * 1e-4;
          const double kTmax = 3 * Q;
          const int    nkT   = 40;
          const double kTstp = (kTmax - kTmin)/ nkT;
          */

          // Fill vectors with grid interpolation
          std::vector<double> gridinterp;
          // for (double kT = kTmin; kT <= kTmax * ( 1 + 1e-5 ); kT += kTstp)
          for (const double kT : kTg)
              gridinterp.push_back(TMDs->Evaluate(x , kT , Q).at(ifl));

          // YAML Emitter
          YAML::Emitter em;

          em << YAML::BeginMap;
          em << YAML::Key << "ifl" << YAML::Value << ifl;
          em << YAML::Key << "Q"   << YAML::Value << Q;
          em << YAML::Key << "x"   << YAML::Value << x;
          em << YAML::Key << "kT"  << YAML::Value << YAML::Flow << YAML::BeginSeq;
          // for (double kT = kTmin; kT <= kTmax * ( 1 + 1e-5 ); kT += kTstp)
          for (const double kT : kTg)
            em << kT;
          em << YAML::EndSeq;
          em << YAML::Key << "Grid interpolation" << YAML::Value << YAML::Flow << YAML::BeginSeq;
          for (int i = 0; i < (int) gridinterp.size(); i++)
            em << gridinterp[i];
          em << YAML::EndSeq;
          em << YAML::EndMap;

          // Produce output file
          std::ofstream fout(Output + "/" + Name + (pf == "pdf" ? "_PDF_Q_" + std::to_string(Q) + "_x_" : "_FF_Q_" + std::to_string(Q) + "_z_")  + std::to_string(x) + ".yaml");
          fout << em.c_str() << std::endl;
          fout.close();
        }
    }
  delete TMDs;
  return 0;
}
