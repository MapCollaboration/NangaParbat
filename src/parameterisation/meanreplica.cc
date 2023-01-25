//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/meanreplica.h"
#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/listdir.h"

#include <fstream>
#include <sys/stat.h>
#include <memory>
#include <yaml-cpp/yaml.h>
#include <algorithm>

namespace NangaParbat
{
  //_________________________________________________________________________________
  MeanReplica::MeanReplica(std::string const& InputFolder, std::string const& FitConfigFile, std::vector<int> const& discard):
    Parameterisation{"MeanReplica", 2}
  {
    // Open configuration file
    const YAML::Node fitconfig = YAML::LoadFile(FitConfigFile);

    // Get parameterisation name as a string
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
          const bool dsc = (find(discard.begin(), discard.end(), std::stoi(folder.substr(folder.find_last_of("_") + 1, folder.size()))) != discard.end());
          try
            {
              const YAML::Node report = YAML::LoadFile(InputFolder + "/" + folder + "/Report.yaml");
              if (report["Status"].as<double>() == 1 && !dsc)
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

    std::cout << "\nTabulating central replica...\n" << std::endl;

    // Generate interpolation grid in x-space (logarithmic)
    const int nx = 100;
    const double xmin = 1e-6;
    const double xmax = 1;
    const double xstep = exp( log( xmax / xmin ) / ( nx - 1 ) );
    std::vector<double> xv;
    for (double x = xmin; x <= xmax + apfel::eps8; x *= xstep)
      xv.push_back(x);

    // Generate interpolation grid in bT-space (logarithmic)
    const int nbT = 100;
    const double bTmin = 1e-5;
    const double bTmax = 10;
    const double bTstep = exp( log( bTmax / bTmin ) / ( nbT - 1 ) );
    std::vector<double> bTv;
    for (double bT = bTmin; bT <= bTmax + apfel::eps8; bT *= bTstep)
      bTv.push_back(bT);

    // Generate interpolation grid in zeta-space (logarithmic)
    const int nzeta = 50;
    const double zetamin = 1;
    const double zetamax = 40000;
    const double zetastep = exp( log( zetamax / zetamin ) / ( nzeta - 1 ) );
    std::vector<double> zetav;
    for (double zeta = zetamin; zeta <= zetamax + apfel::eps8; zeta *= zetastep)
      zetav.push_back(zeta);

    // Tabulate mean replica
    _fNP1g.resize(nx, std::vector<std::vector<double>>(nbT, std::vector<double>(nzeta, 0.)));
    _fNP2g.resize(nx, std::vector<std::vector<double>>(nbT, std::vector<double>(nzeta, 0.)));
    for (int ix = 0; ix < nx; ix++)
      for (int ibT = 0; ibT < nbT; ibT++)
        for (int izeta = 0; izeta < nzeta; izeta++)
          {
            for (auto const& fNP : _NPFuncv)
              {
                _fNP1g[ix][ibT][izeta] += fNP->Evaluate(xv[ix], bTv[ibT], zetav[izeta], 0);
                _fNP2g[ix][ibT][izeta] += fNP->Evaluate(xv[ix], bTv[ibT], zetav[izeta], 1);
              }
            const int nrep = (int) _NPFuncv.size();
            _fNP1g[ix][ibT][izeta] /= nrep;
            _fNP2g[ix][ibT][izeta] /= nrep;
          }

    // Initialise "apfel::QGrid" objects that will provide the
    // interpolating functions.
    _xg    = std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double> {xv,    1});
    _bTg   = std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double> {bTv,   1});
    _zetag = std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double> {zetav, 1});
  }

  //_________________________________________________________________________________
  MeanReplica::~MeanReplica()
  {
    delete _NPFunc;
  }

  //_________________________________________________________________________________
  double MeanReplica::Evaluate(double const& x, double const& bT, double const& zeta, int const& ifunc) const
  {
    if (ifunc < 0 || ifunc >= this->_nfuncs)
      throw std::runtime_error("[MeanReplica::Evaluate]: function index out of range");
    /*
        // Calculate mean over replicas
        double sum = 0;
        for (auto const& fNP : _NPFuncv)
          sum += fNP->Evaluate(x, bT, zeta, ifunc);
        sum /= _NPFuncv.size();
    */
    // Interpolate
    const std::tuple<int, int, int> xbounds    = _xg->SumBounds(x);
    const std::tuple<int, int, int> bTbounds   = _bTg->SumBounds(bT);
    const std::tuple<int, int, int> zetabounds = _zetag->SumBounds(zeta);

    double result = 0;
    for (int ix = std::get<1>(xbounds); ix < std::get<2>(xbounds); ix++)
      for (int ibT = std::get<1>(bTbounds); ibT < std::get<2>(bTbounds); ibT++)
        for (int izeta = std::get<1>(zetabounds); izeta < std::get<2>(zetabounds); izeta++)
          result +=
            _xg->Interpolant(std::get<0>(xbounds), ix, x) *
            _bTg->Interpolant(std::get<0>(bTbounds), ibT, bT) *
            _zetag->Interpolant(std::get<0>(zetabounds), izeta, zeta) *
            (ifunc == 0 ? _fNP1g[ix][ibT][izeta] : _fNP2g[ix][ibT][izeta]);

    return result;
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
