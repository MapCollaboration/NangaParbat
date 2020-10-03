//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@ateneopv.it
//


#include "NangaParbat/factories.h"

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
      std::cout << "Syntax: ./GridsConvolution <directory with TMD grids> <name of TMD PDF set> <name of TMD FF set> <replica ID> \n" << std::endl;
      std::cout << "<replica ID>: number of the replica to select to do the convolution. \n" << std::endl;
      exit(-10);
    }

  // Read Kinematics
  YAML::Node kin = YAML::LoadFile("inputs/GridsConvolution.yaml");

  const double qToQcut = kin["qT/Q cut"].as<double>();
  const std::vector<double> qTv = kin["qToQ"].as<std::vector<double>>();
  const std::vector<double> Qv  = kin["Q"].as<std::vector<double>>();
  const std::vector<double> xv  = kin["x"].as<std::vector<double>>();
  const std::vector<double> zv  = kin["z"].as<std::vector<double>>();

  // Read in grid
	std::cout << "Read TMD grids " << std::endl;
  NangaParbat::TMDGrid* TMDPDFs = NangaParbat::mkTMD(argv[2],argv[1],std::stoi(argv[4]));
  NangaParbat::TMDGrid* TMDFFs  = NangaParbat::mkTMD(argv[3],argv[1],std::stoi(argv[4]));

  // Create directory to store yaml output
  const std::string outdir = "testGridsConvolution";
  mkdir(outdir.c_str(), ACCESSPERMS);
  std::cout << "Creating folder " + outdir  + " if not already existing." << std::endl;

  // Output.dat
  std::ofstream outdat;
  outdat.open(outdir + "/" + "NangaGridsConv.dat", std::ios::out);
  outdat    << " Qm          "
  	        << " qTm         "
            << " xm          "
            << " zm          "
            << " F_UUT_grids "
            << std::endl;

  // Fully differential calculation
  for (int iQ = 0; iQ < (int) Qv.size(); iQ++)
    {
      for (int ix = 0; ix < (int) xv.size(); ix++)
      	{
      	  for (int iz = 0; iz < (int) zv.size(); iz++)
      	    {
              // Initialize results vector
              std::vector<double> fgrids;

              // Kinematics
              const double Qm = Qv[iQ];
              const double xm = xv[ix];
              const double zm = zv[iz];

              for (int iqT = 0; iqT < (int) qTv.size(); iqT++)
            		{
                  // qT points
            		  const double qTm = Qm * qTv[iqT];

                  // EW charges
            		  const std::vector<double> Bq = apfel::QCh2;

            		  // Convolution in kT space from grids
                  const auto conv = Convolution(TMDPDFs, TMDFFs, [] (double const&) -> std::vector<double> { return apfel::QCh2; }, qToQcut);
                  const double gridFUUT = conv(xm, zm, Qm, qTm) / zm / (2 * M_PI);
                  fgrids.push_back(gridFUUT);

                  // Output.dat
                  outdat   << std::scientific
                           << Qm  << " "
                    			 << qTm << " "
                      	   << xm  << " "
                    		   << zm  << " "
                       		 << fgrids[iqT] << " "
                           << std::endl;
            		}

              // YAML Emitter
              YAML::Emitter em;

              em << YAML::BeginMap;
              em << YAML::Key << "Q"   << YAML::Value << Qm;
              em << YAML::Key << "x"   << YAML::Value << xm;
              em << YAML::Key << "z"   << YAML::Value << zm;
              em << YAML::Key << "qT"  << YAML::Value << YAML::Flow << YAML::BeginSeq;
              for (int iqT = 0; iqT < (int) qTv.size(); iqT++)
                em << Qm * qTv[iqT];
              em << YAML::EndSeq;
              em << YAML::Key << "FUUT convolution" << YAML::Value << YAML::Flow << YAML::BeginSeq;
              for (int i = 0; i < (int) fgrids.size(); i++)
                em << fgrids[i];
              em << YAML::EndSeq;
              em << YAML::EndMap;

              // Produce output file
              std::ofstream fout(outdir + "/FUUT_Q_" + std::to_string(Qm) + "_x_" + std::to_string(xm) + "_z_" + std::to_string(zm) + ".yaml");
              fout << em.c_str() << std::endl;
              fout.close();
      	    }
      	}
    }

  outdat.close();

  delete TMDPDFs;
  delete TMDFFs;
  return 0;
}
