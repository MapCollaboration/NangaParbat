//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/minimisation.h"

#include <ROOT/Minuit2/MnUserParameters.h>
#include <ROOT/Minuit2/FunctionMinimum.h>
#include <ROOT/Minuit2/MnPrint.h>

#include <ceres/ceres.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  bool MinuitMinimiser(ChiSquare const& chi2, YAML::Node const& parameters)
  {
    std::cout << "\nMinimising with Minuit...\n" << std::endl;

    // Define "Minuit" object
    NangaParbat::FcnMinuit fcn{chi2};

    // Create Minuit parameters with name, starting value, step and,
    // when available, upper and lower bounds.
    ROOT::Minuit2::MnUserParameters upar;
    for (auto const p : parameters)
      {
        upar.Add(p["name"].as<std::string>(), p["starting_value"].as<double>(), p["step"].as<double>());

        // Set limits if required
        if (p["lower_bound"])
          upar.SetLowerLimit(p["name"].as<std::string>(), p["lower_bound"].as<double>());

        if (p["upper_bound"])
          upar.SetUpperLimit(p["name"].as<std::string>(), p["upper_bound"].as<double>());

        // Fix parameter if required
        if (p["fix"] && p["fix"].as<bool>())
          upar.Fix(p["name"].as<std::string>());
      }

    // Create MIGRAD minimiser
    ROOT::Minuit2::MnMigrad minimiser{fcn, upar};

    // Increase verbosity of Minuit
    minimiser.Minimizer().Builder().SetPrintLevel(2);

    // Minimise
    ROOT::Minuit2::FunctionMinimum min = minimiser();

    // Output of Minuit
    std::cout << "minimum: " << min << std::endl;

    // Before returning, retrieve best-fit parameters and set them in
    // the chi2 to make sure they will be used outside this function.
    std::vector<double> BestFitParameters;
    for (auto const p : upar.Parameters())
      BestFitParameters.push_back(p.Value());
    fcn.SetParameters(BestFitParameters);

    // Return minimisation status
    return min.IsValid();
  }

  //_________________________________________________________________________________
  bool CeresMinimiser(ChiSquare const& chi2, YAML::Node const& parameters)
  {
    std::cout << "\nMinimising with Ceres...\n" << std::endl;

    // Allocate "Problem" instance
    ceres::Problem problem{};

    // Number of parameters to be fitted
    const int npars = parameters.size();

    // Define cost function
    ceres::DynamicNumericDiffCostFunction<FcnCeres> *cost_function = new ceres::DynamicNumericDiffCostFunction<FcnCeres>(new FcnCeres{chi2});

    // Add one single parameter block
    cost_function->AddParameterBlock(npars);

    // Set number of residuals
    int nres = 0;
    for (auto const n : chi2.GetDataPointNumbers())
      nres += n;
    cost_function->SetNumResiduals(nres);

    // Fill in initial parameter array
    double initPars[npars];
    std::vector<int> fixedpars;
    int i = 0;
    for (auto const p : parameters)
      {
        // Fill in initial parameter array
        initPars[i++] = p["starting_value"].as<double>();

        // Fix parameter if required
        if (p["fix"] && p["fix"].as<bool>())
          fixedpars.push_back(i-1);
      }

    // Add residual block
    problem.AddResidualBlock(cost_function, NULL, initPars);

    // Fix constant parameters
    problem.SetParameterization(initPars, new ceres::SubsetParameterization{npars, fixedpars});

    // Set upper and lower bounds if required
    i = 0;
    for (auto const p : parameters)
      {
        if (p["lower_bound"])
          problem.SetParameterLowerBound(initPars, i, p["lower_bound"].as<double>());

        if (p["upper_bound"])
          problem.SetParameterUpperBound(initPars, i, p["upper_bound"].as<double>());

        i++;
      }

    // Option object
    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    options.function_tolerance = 1e-5;
    options.max_num_iterations = 1000;

    // Summary object
    ceres::Solver::Summary summary;

    // Do the minimisation
    ceres::Solve(options, &problem, &summary);

    // Full report
    std::cout << summary.FullReport() << std::endl;

    // Return minimisation status
    return summary.IsSolutionUsable();
  }

  //_________________________________________________________________________________
  bool NoMinimiser(ChiSquare const& chi2, YAML::Node const& parameters)
  {
    std::cout << "\nNo minimiser, computing predictions only...\n" << std::endl;

    // Fill in initial parameter array
    std::vector<double> initPars;
    for (auto const p : parameters)
      initPars.push_back(p["starting_value"].as<double>());

    // Set the parameters of the parameterisation
    NangaParbat::FcnMinuit fcn{chi2};
    fcn.SetParameters(initPars);

    // Return minimisation status
    return true;
  }

  //_________________________________________________________________________________
  FcnMinuit::FcnMinuit(ChiSquare const& chi2):
    _chi2(chi2)
  {
  }

  //_________________________________________________________________________________
  double FcnMinuit::operator()(std::vector<double> const& pars) const
  {
    // Set the parameters of the parameterisation
    _chi2.SetParameters(pars);

    // Evaluate and return total chi2 (normalised to the total number
    // of points).
    return _chi2.Evaluate();
  }

  //_________________________________________________________________________________
  FcnCeres::FcnCeres(ChiSquare const& chi2):
    _chi2(chi2)
  {
  }

  //_________________________________________________________________________________
  bool FcnCeres::operator()(double const* const* parameters, double* residuals) const
  {
    // Put parameters into a vector.
    const int Np = _chi2.GetNumberOfParameters();

    std::vector<double> vpars(Np);
    for (int ip = 0; ip < Np; ip++)
      vpars[ip] = parameters[0][ip];

    // Set the parameters of the parameterisation
    _chi2.SetParameters(vpars);

    // Now get residuals for all experiments and put them in the array
    int j = 0;
    for (int iexp = 0; iexp < (int) _chi2.GetNumberOfExperiments(); iexp++)
      {
        const std::vector<double> vres = _chi2.GetResiduals(iexp);
        for (int i = 0; i < (int) vres.size(); i++)
          residuals[j++] = vres[i];
      }
    return true;
  }
}
