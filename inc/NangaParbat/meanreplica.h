//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti

#pragma once

#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/utilities.h"

#include <fstream>
#include <sys/stat.h>

namespace NangaParbat
{
  /**
   * @brief Parameterisation derived from the "Parameterisation"
   * mother class to compute the mean replica of a Monte Carlo set.
   */
  class MeanReplica: public NangaParbat::Parameterisation
  {
  public:
    MeanReplica(std::string const& InputFolder, std::string const& FitConfigFile):
      Parameterisation{"MeanReplica", 2}
    {
      // Open configuration file
      const YAML::Node fitconfig = YAML::LoadFile(FitConfigFile);

      // Allocate "Parameterisation" derived object using the same
      // parameterisation used in the fit.
      _NPFunc = NangaParbat::GetParametersation(fitconfig["Parameterisation"].as<std::string>());

      // Set the parameters to zero (this will not be used anywhere)
      this->_pars.resize(_NPFunc->GetParameterNames().size(), 0);

      // Select replicas according to whether the fit converged
      // (status = 1) and the global error function per data point is
      // less than a user-given cut.
      for (auto const& folder : NangaParbat::list_dir(InputFolder))
        if (folder.substr(0, 8) == "replica_")
          {
            try
              {
                const YAML::Node report = YAML::LoadFile(InputFolder + "/" + folder + "/Report.yaml");
                if (report["Status"].as<double>() == 1 && report["Global error function"].as<double>() < fitconfig["Error function cut"].as<double>())
                  {
                    std::vector<double> pars;
                    for (auto const& m : _NPFunc->GetParameterNames())
                      pars.push_back(report["Parameters"][m].as<double>());
                    _InPars.push_back(pars);
                  }
                else
                  std::cout << "[MeanReplica][Warning]: Replica in folder '" + folder + "' discarded." << std::endl;
              }
            catch (const YAML::Exception& ex)
              {
                std::cout << "[MeanReplica][Warning]: File 'Report.yaml' not found in folder '" + folder + "'." << std::endl;
              }
          }
    };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[MeanReplica::Evaluate]: function index out of range");

      // Calculate mean over the replicas
      double mean = 0;
      for (auto const& pars : _InPars)
        {
          _NPFunc->SetParameters(pars);
          mean += _NPFunc->Evaluate(x, b, zeta, ifunc);
        }
      mean /= (double) _InPars.size();
      return mean;
    };

    std::string LatexFormula() const
    {
      return _NPFunc->LatexFormula();
    };

    std::vector<std::string> GetParameterNames() const
    {
      return _NPFunc->GetParameterNames();
    };

  private:
    std::vector<std::vector<double>>  _InPars;
    NangaParbat::Parameterisation    *_NPFunc;
  };
}
