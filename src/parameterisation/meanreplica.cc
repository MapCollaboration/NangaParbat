//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/meanreplica.h"
#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/utilities.h"

#include <fstream>
#include <sys/stat.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  MeanReplica::MeanReplica(std::string const& InputFolder, std::string const& FitConfigFile):
    Parameterisation{"MeanReplica", 2}
  {
    // Open configuration file
    const YAML::Node fitconfig = YAML::LoadFile(FitConfigFile);

    // Get paremetersisation name as a string
    const std::string parameterisation = fitconfig["Parameterisation"].as<std::string>();

    // Allocate "Parameterisation" derived object using the same
    // parameterisation used in the fit. This is used only to
    // retrieve information about the parameterisation.
    _NPFunc = NangaParbat::GetParametersation(parameterisation);

    // Set the parameters to zero (this will not be used anywhere)
    this->_pars.resize(_NPFunc->GetParameterNames().size(), 0);

    // Select replicas according to whether the fit converged (status
    // = 1) and the global error function per data point is less than
    // a user-given cut.
    for (auto const& folder : NangaParbat::list_dir(InputFolder))
      if (folder.substr(0, 8) == "replica_" && folder != "replica_0")
        {
          try
            {
              const YAML::Node report = YAML::LoadFile(InputFolder + "/" + folder + "/Report.yaml");
              if (report["Status"].as<double>() == 1 && report["Global error function"].as<double>() < fitconfig["Error function cut"].as<double>())
                {
                  std::vector<double> pars;
                  for (auto const& m : _NPFunc->GetParameterNames())
                    pars.push_back(report["Parameters"][m].as<double>());

                  // Allocate "Parameterisation" derived object
                  // using the same parameterisation used in the
                  // fit, set the parameters of the usable fits, and
                  // push it into a vector.
                  NangaParbat::Parameterisation *fNP = NangaParbat::GetParametersation(parameterisation);
                  fNP->SetParameters(pars);
                  _NPFuncv.push_back(fNP);
                }
              else
                std::cout << "[MeanReplica::MeanReplica]: Warning: Replica in folder '" + folder + "' discarded." << std::endl;
            }
          catch (const YAML::Exception& ex)
            {
              std::cout << "[MeanReplica::MeanReplica]: Warning: File 'Report.yaml' not found in folder '" + folder + "'." << std::endl;
            }
        }
  }

  //_________________________________________________________________________________
  MeanReplica::~MeanReplica()
  {
    delete _NPFunc;
  }

  //_________________________________________________________________________________
  double MeanReplica::Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
  {
    if (ifunc < 0 || ifunc >= this->_nfuncs)
      throw std::runtime_error("[MeanReplica::Evaluate]: function index out of range");

    // Calculate mean over replicas
    double sum = 0;
    for (auto const& fNP : _NPFuncv)
      sum += fNP->Evaluate(x, b, zeta, ifunc);

    return sum / (double) _NPFuncv.size();
  }

  //_________________________________________________________________________________
  std::string MeanReplica::LatexFormula() const
  {
    return _NPFunc->LatexFormula();
  }

  //_________________________________________________________________________________
  std::vector<std::string> MeanReplica::GetParameterNames() const
  {
    return _NPFunc->GetParameterNames();
  }
}
