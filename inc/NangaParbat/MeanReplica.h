#include "NangaParbat/NonPertFunctions.h"
#include "NangaParbat/utilities.h"

#include <fstream>
#include <sys/stat.h>


namespace NangaParbat
{
  /**
   * @brief Pavia 2019 parameterisation derived from the
   * "Parameterisation" mother class.
   */
  class MeanReplica: public NangaParbat::Parameterisation
  {
  public:
    MeanReplica(std::string const& InputFolder, std::string const& FitConfigFile):
      Parameterisation{"MeanReplica", 2},
      _InputFolder(InputFolder),
      _FitConfigFile(FitConfigFile)
    {
      // Allocate "Parameterisation" derived object
      const YAML::Node fitconfig = YAML::LoadFile(_FitConfigFile);

      _NPFunc = NangaParbat::GetParametersation(fitconfig["Parameterisation"].as<std::string>());

      // Select goodreplicas
      std::vector<std::string> goodreplicas(0);

      for (auto const folder : NangaParbat::list_dir(_InputFolder))
        {
          if (folder.substr(0, 8) == "replica_")
            {
              try
                {
                  const YAML::Node report = YAML::LoadFile(_InputFolder + "/" + folder + "/Report.yaml");
                  if (report["Status"].as<double>() == 1 && report["Global error function"].as<double>() < 4)
                      goodreplicas.push_back(folder);
                }
              catch (std::exception)
                {
                  std::cout << "[MeanReplica][Warning]: File 'Report.yaml' not found in folder '" + folder + "'." << std::endl;
                }
            }
        }

      for(std::string & folder : goodreplicas)
        {
          std::vector<double> singlereppar;
          const YAML::Node report = YAML::LoadFile(_InputFolder + "/" + folder + "/Report.yaml");

          // Fill array _InPars
          for (YAML::const_iterator it = report["Parameters"].begin(); it != report["Parameters"].end(); ++it)
            {
              singlereppar.push_back(it->second.as<double>());
            }
          _InPars.push_back(singlereppar);
        }
    };

  private:
    std::string                      const _InputFolder;
    std::string                      const _FitConfigFile;
    std::vector<std::vector<double>>       _InPars;
    NangaParbat::Parameterisation         *_NPFunc;

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[MeanReplica::Evaluate]: function index out of range");

      // Calculate mean of the replicas
      double mean = 0;
      for (auto const& pars : _InPars)
        {
          _NPFunc->SetParameters(pars);
          mean += _NPFunc->Evaluate(x, b, zeta, ifunc);
        }

      mean /= (double) _InPars.size();

      return mean;

    };
  };
}
