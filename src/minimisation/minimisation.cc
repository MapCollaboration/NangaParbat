//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/minimisation.h"
#include "NangaParbat/fcnminuit.h"
#include "NangaParbat/fcnceres.h"

#include <root/Minuit2/MnUserParameters.h>
#include <root/Minuit2/MnMigrad.h>
#include <root/Minuit2/MnScan.h>
#include <root/Minuit2/MnPlot.h>
#include <root/Minuit2/FunctionMinimum.h>
#include <root/Minuit2/MnPrint.h>
#include <ceres/ceres.h>
#include <gsl/gsl_randist.h>

#include <fstream>
#include <sys/stat.h>

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
        if (rng !=  NULL && !p["fix"].as<bool>())
          pstart += gsl_ran_gaussian(rng, p["step"].as<double>());

        upar.Add(p["name"].as<std::string>(), pstart, p["step"].as<double>());

        // Set limits if required
        if (p["lower_bound"])
          upar.SetLowerLimit(p["name"].as<std::string>(), p["lower_bound"].as<double>());

        if (p["upper_bound"])
          upar.SetUpperLimit(p["name"].as<std::string>(), p["upper_bound"].as<double>());

        // Fix parameter if required
        if (p["fix"].as<bool>())
          upar.Fix(p["name"].as<std::string>());
      }

    if (chi2.GetNonPerturbativeFunction()->HasGradient())
      {
        // Define "Minuit" fcn
        NangaParbat::FcnMinuitGrad fcn{chi2};

        // Create MIGRAD minimiser
        ROOT::Minuit2::MnMigrad minimiser{fcn, upar};

        // Increase verbosity of Minuit
        minimiser.Minimizer().Builder().SetPrintLevel(2);

        // Minimise
        ROOT::Minuit2::FunctionMinimum min = minimiser(10000);

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
        ROOT::Minuit2::FunctionMinimum min = minimiser(10000);

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

    // Define cost function
    ceres::DynamicNumericDiffCostFunction<FcnCeres> *cost_function = new ceres::DynamicNumericDiffCostFunction<FcnCeres>(new FcnCeres{chi2});

    // Set number of residuals
    cost_function->SetNumResiduals(chi2.GetDataPointNumber());

    // Fill in initial parameter array
    std::vector<double*> initPars;
    for (auto const p : parameters)
      {
        // Add a parameter block for each parameter
        cost_function->AddParameterBlock(1);

        // If the GSL random-number generator object is NULL use the
        // central value as starting parameters, otherwise fluctuate
        // them (gaussianly) according to the step.
        double pstart = p["starting_value"].as<double>();
        if (rng !=  NULL && !p["fix"].as<bool>())
          pstart += gsl_ran_gaussian(rng, p["step"].as<double>());

        // Fill in initial parameter array
        initPars.push_back(new double(pstart));
      }

    // Add residual block
    problem.AddResidualBlock(cost_function, NULL, initPars);

    // Set upper and lower bounds if required
    int i = 0;
    for (auto const p : parameters)
      {
        // Fix parameter if required
        if (p["fix"].as<bool>())
          {
            // If the parameter is fixed set lower and upper bound
            // within an epsilon from the starting value. Workaround
            // to avoid that the code crushes.
            problem.SetParameterLowerBound(initPars[i], 0, *initPars[i] - 1e-8);
            problem.SetParameterUpperBound(initPars[i], 0, *initPars[i] + 1e-8);

            // This is the correct procedure that seems to make the
            // code crush.
            //problem.SetParameterBlockConstant(initPars[i]);
          }
        else
          {
            if (p["lower_bound"])
              problem.SetParameterLowerBound(initPars[i], 0, p["lower_bound"].as<double>());

            if (p["upper_bound"])
              problem.SetParameterUpperBound(initPars[i], 0, p["upper_bound"].as<double>());
          }
        i++;
      }

    // Option object
    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    options.max_num_iterations           = 1000;
    //options.function_tolerance           = 1e-5;
    //options.minimizer_type               = ceres::LINE_SEARCH;
    //options.trust_region_strategy_type   = ceres::DOGLEG;

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
  bool MinuitScan(ChiSquare const& chi2, YAML::Node const& parameters, std::string const& outfolder)
  {
    std::cout << "\nMinuit scanning...\n" << std::endl;

    // Create Minuit parameters with name, starting value, step and,
    // when available, upper and lower bounds.
    ROOT::Minuit2::MnUserParameters upar;
    std::vector<double> initPars;
    for (auto const p : parameters)
      upar.Add(p["name"].as<std::string>(), p["starting_value"].as<double>(), p["step"].as<double>());

    // Define "Minuit" fcn
    NangaParbat::FcnMinuit fcn{chi2};

    // Initialise scanner
    ROOT::Minuit2::MnScan scan{fcn, upar};

    // Produce YAML output
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Parameters scan" << YAML::Value << YAML::BeginSeq;
    for (int p = 0; p < (int) upar.Params().size(); p++)
      {
        // Perform the scan. The number of points in the scan is 41
        // and the range is 2 standard deviations (= two times the
        // step of the parameter) by default (Scan from Minuit2).
        std::vector<std::pair<double,double>> points = scan.Scan(p);

        out << YAML::BeginMap;
        out << YAML::Key << "name" << YAML::Value << upar.GetName(p);

        out << YAML::Key << "parameter value" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int i = 0; i < (int) points.size(); i++)
          out << points[i].first;
        out << YAML::EndSeq;
        out << YAML::Key << "fcn value" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int i = 0; i < (int) points.size(); i++)
          out << points[i].second;
        out << YAML::EndSeq;
        out << YAML::EndMap;

        // On terminal. Notice that the 0-th entry is the minimum of
        // the previous scan and this scan is done with the best of
        // the previous parameter.
        for (int i = 0; i < (int) points.size(); i++)
          std::cout << std::scientific << i << ": " << points[i].first << ", " << points[i].second << std::endl;

        ROOT::Minuit2::MnPlot plot{};
        plot(points);
      }
    out << YAML::EndSeq;
    out << YAML::EndMap;

    // Create output directory
    const std::string OutputFolder = outfolder + "/scan";
    mkdir((OutputFolder).c_str(), ACCESSPERMS);

    // Print out
    std::ofstream fout(OutputFolder + "/ParameterScan.yaml");
    fout << out.c_str() << std::endl;
    fout.close();

    // Set best parameters after the scan
    fcn.SetParameters(scan.Parameters().Params());

    // Return status
    return true;
  }
}
