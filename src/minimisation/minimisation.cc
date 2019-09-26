//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/minimisation.h"
#include "NangaParbat/fcnminuit.h"
#include "NangaParbat/fcnceres.h"

#include <root/Minuit2/MnUserParameters.h>
#include <root/Minuit2/MnMigrad.h>
#include <root/Minuit2/FunctionMinimum.h>
#include <root/Minuit2/MnPrint.h>
#include <ceres/ceres.h>
#include <gsl/gsl_randist.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  bool MinuitMinimiser(ChiSquare const& chi2, YAML::Node const& parameters, gsl_rng* rng)
  {
    std::cout << "\nMinimising with Minuit...\n" << std::endl;

    // Create Minuit parameters with name, starting value, step and,
    // when available, upper and lower bounds.
    ROOT::Minuit2::MnUserParameters upar;
    for (auto const p : parameters)
      {
        // If the GSL random-number generator object is NULL use the
        // central value as starting parameters, otherwise fluctuate
        // them (gaussianly) according to the step.
        double pstart = p["starting_value"].as<double>();
        if (rng !=  NULL)
          pstart += gsl_ran_gaussian(rng, p["step"].as<double>());

        upar.Add(p["name"].as<std::string>(), pstart, p["step"].as<double>());

        // Set limits if required
        if (p["lower_bound"])
          upar.SetLowerLimit(p["name"].as<std::string>(), p["lower_bound"].as<double>());

        if (p["upper_bound"])
          upar.SetUpperLimit(p["name"].as<std::string>(), p["upper_bound"].as<double>());

        // Fix parameter if required
        if (p["fix"] && p["fix"].as<bool>())
          upar.Fix(p["name"].as<std::string>());
      }

    if (chi2.GetNonPerturbativeFunction().HasGradient())
      {
        // Define "Minuit" fcn
        NangaParbat::FcnMinuitGrad fcn{chi2};

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
        fcn.SetParameters(min.UserParameters().Params());

        // Return minimisation status
        return min.IsValid();
      }
    else
      {
        // Define "Minuit" fcn
        NangaParbat::FcnMinuit fcn{chi2};

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
        fcn.SetParameters(min.UserParameters().Params());

        // Return minimisation status
        return min.IsValid();
      }
  }

  //_________________________________________________________________________________
  bool CeresMinimiser(ChiSquare const& chi2, YAML::Node const& parameters, gsl_rng* rng)
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
        // If the GSL random-number generator object is NULL use the
        // central value as starting parameters, otherwise fluctuate
        // them (gaussianly) according to the step.
        double pstart = p["starting_value"].as<double>();
        if (rng !=  NULL)
          pstart += gsl_ran_gaussian(rng, p["step"].as<double>());

        // Fill in initial parameter array
        initPars[i++] = pstart;

        // Fix parameter if required
        if (p["fix"] && p["fix"].as<bool>())
          fixedpars.push_back(i-1);
      }

    // Add residual block
    problem.AddResidualBlock(cost_function, NULL, initPars);

    // Fix constant parameters
    if (!fixedpars.empty())
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
    //options.function_tolerance = 1e-5;
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
  bool NoMinimiser(ChiSquare const& chi2, YAML::Node const& parameters, gsl_rng* rng)
  {
    std::cout << "\nNo minimiser, computing predictions only...\n" << std::endl;

    // Fill in initial parameter array
    std::vector<double> initPars;
    for (auto const p : parameters)
      {
        // If the GSL random-number generator object is NULL use the
        // central value as starting parameters, otherwise fluctuate
        // them (gaussianly) according to the step.
        double pstart = p["starting_value"].as<double>();
        if (rng !=  NULL)
          pstart += gsl_ran_gaussian(rng, p["step"].as<double>());

        initPars.push_back(pstart);
      }

    // Set the parameters of the parameterisation
    NangaParbat::FcnMinuit fcn{chi2};
    fcn.SetParameters(initPars);

    // Return minimisation status
    return true;
  }
}
