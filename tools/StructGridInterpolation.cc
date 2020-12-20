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
      std::cout << "Syntax: ./StructGridInterpolation <grid main folder> <grid name> <n. repl.> <output>\n" << std::endl;
      std::cout << "<grid main folder>: relative path to the folder where the grids are;" << std::endl;
      std::cout << "<n. repl>: number of the replica grid to interpolate. \n" << std::endl;
      exit(-10);
    }

  const std::string Folder = std::string(argv[1]);
  const std::string Name   = std::string(argv[2]);
  const std::string Output = std::string(argv[4]);

  // Select flavour
  const int ifl = 2; // quark up

  // Read values
  YAML::Node kin = YAML::LoadFile("inputs/StructGridInterpolation.yaml");

  const std::vector<double> qTgoQ = kin["qToQ"].as<std::vector<double>>();
  const std::vector<double> Qg    = kin["Q"].as<std::vector<double>>();
  const std::vector<double> xg    = kin["x"].as<std::vector<double>>();
  const std::vector<double> zg    = kin["z"].as<std::vector<double>>();

  // ===========================================================================
  // Read info file
  std::cout << "\n";
  std::cout << "Reading info file: "  + Folder + "/"  + Name + "/" + Name + ".info" +  "  ..." << std::endl;
  YAML::Node const& infofile = YAML::LoadFile(Folder + "/"  + Name + "/" + Name + ".info");

  // Create directory to store the output
  mkdir(Output.c_str(), ACCESSPERMS);
  std::cout << "Creating folder " + Output << std::endl;
  std::cout << "\n";

  // Start intepolation
  std::cout << "Starting interpolation of " + std::string(argv[2]) +  " ..." << std::endl;

  // Read Structure function in grid
  NangaParbat::StructGrid* SFs = NangaParbat::mkSF(Name, Folder, std::stoi(argv[3]));

  // Read grids and test interpolation
  for (int iq = 0; iq < (int) Qg.size(); iq++)
    {
      const double Q  = Qg[iq];

      for (int ix = 0; ix < (int) xg.size(); ix++)
        {
          const double x  = xg[ix];

          for (int iz = 0; iz < (int) zg.size(); iz++)
            {
              // value of z
              const double z  = zg[iz];

              /*
              // Values of qT
              const double qTmin = Q * 1e-4;
              const double qTmax = 3 * Q;
              const int    nqT   = 40;
              const double qTstp = (qTmax - qTmin)/ nqT;
              */

              // Fill vectors with grid interpolation
              std::vector<double> gridinterp;
              // for (double qT = qTmin; qT <= qTmax * ( 1 + 1e-5 ); qT += qTstp)
              //   gridinterp.push_back(SFs->Evaluate(x ,z, qT, Q));
              for (const double qToQ : qTgoQ)
                gridinterp.push_back(SFs->Evaluate(x ,z, qToQ * Q, Q));

              // YAML Emitter
              YAML::Emitter em;

              em << YAML::BeginMap;
              em << YAML::Key << "ifl" << YAML::Value << ifl;
              em << YAML::Key << "Q"   << YAML::Value << Q;
              em << YAML::Key << "x"   << YAML::Value << x;
              em << YAML::Key << "z"   << YAML::Value << z;
              em << YAML::Key << "qT"  << YAML::Value << YAML::Flow << YAML::BeginSeq;
              // for (double qT = qTmin; qT <= qTmax * ( 1 + 1e-5 ); qT += qTstp)
                // em << qT;
              for (const double qToQ : qTgoQ)
                em << qToQ * Q;
              em << YAML::EndSeq;
              em << YAML::Key << "Grid interpolation" << YAML::Value << YAML::Flow << YAML::BeginSeq;
              for (int i = 0; i < (int) gridinterp.size(); i++)
                em << gridinterp[i];
              em << YAML::EndSeq;
              em << YAML::EndMap;

              // Produce output file
              std::ofstream fout(Output + "/" + infofile["StructFuncType"].as<std::string>() + "_Q_" + std::to_string(Q) + "_x_" + std::to_string(x) + "_z_"  + std::to_string(z) + ".yaml");
              fout << em.c_str() << std::endl;
              fout.close();
            }
        }
    }

  delete SFs;

  return 0;
}
