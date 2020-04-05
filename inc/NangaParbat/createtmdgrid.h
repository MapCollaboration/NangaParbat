//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <vector>
#include <memory>
#include <yaml-cpp/yaml.h>
#include <apfel/apfelxx.h>

namespace NangaParbat
{
  /**
   * @brief Structure that contains the 3D grid in Q,x, and qT
   */
  struct ThreeDGrid
  {
    // Grid in Q
    std::vector<double> Qg
    {
      1.000000e+00, 1.224745e+00, 1.581139e+00,
      1.788854e+00, 2.236068e+00, 2.828427e+00,
      3.162278e+00, 4.750000e+00, 6.324555e+00,
      8.000000e+00, 1.264911e+01, 2.000000e+01,
      2.529822e+01, 4.242641e+01, 7.483315e+01,
      9.118760e+01, 1.341641e+02, 2.366432e+02,
      3.162278e+02, 5.656854e+02, 1.000000e+03,
      1.341641e+03, 2.366432e+03, 4.242641e+03,
      5.656854e+03, 1.000000e+04
    };

    // Grid in x
    std::vector<double> xg
    {
      1.000000e-05, 2.000000e-05, 4.000000e-05, 6.000000e-05, 8.000000e-05,
      1.000000e-04, 2.000000e-04, 4.000000e-04, 6.000000e-04, 8.000000e-04,
      1.000000e-03, 2.000000e-03, 4.000000e-03, 6.000000e-03, 8.000000e-03,
      1.000000e-02, 2.000000e-02, 4.000000e-02, 6.000000e-02, 8.000000e-02,
      1.000000e-01, 1.500000e-01, 2.000000e-01, 2.500000e-01, 3.000000e-01,
      3.500000e-01, 4.000000e-01, 4.500000e-01, 5.000000e-01, 5.500000e-01,
      6.000000e-01, 6.500000e-01, 7.000000e-01, 7.500000e-01, 8.000000e-01,
      8.500000e-01, 9.000000e-01, 9.250000e-01, 9.500000e-01, 9.750000e-01,
      1.000000e+00
    };

    // Grid in qT/Q
    std::vector<double> qToQg
    {
      0.001,
      0.01, 0.05, 0.10, 0.15,
      0.20, 0.25, 0.30, 0.35,
      0.40, 0.45, 0.50, 0.55,
      0.60, 0.65, 0.70, 0.75,
      0.80, 0.85, 0.90, 0.95,
      1
    };
  };

  /**
   * @brief Map of perturbative orders
   */
  const std::map<int, std::string> PtOrderMap{{0, "LL"}, {1, "NLL"}, {-1, "NLL'"}, {2, "NNLL"}, {-2, "NNLL'"}, {3, "NNNLL"}};

  /**
   * @brief This function encapsulates and streamlines the production
   * of an interpolation grid strting from the report produced by a
   * NangaParbat fit.
   * @param ReportFolder: path to the report folder
   * @param Output: name of the output grid
   */
  void ProduceTMDGrid(std::string const& ReportFolder, std::string const& Output);

  /**
   * @brief Function that produces the TMD interpolation grid in
   * momentum space. This is suppose to resamble an LHAPDF grid for
   * the TMDs. We use plain YAML format.
   * @param config: the YAML not with the theory settings
   * @param parameterisation: the parameterisation type
   * @param params: the vector of parameters to be used for the tabulation
   * @param pf: whether PDFs ("pdf") of FFs ("ff")
   * @return a YAML emitter
   */
  std::unique_ptr<YAML::Emitter> EmitTMDGrid(YAML::Node          const& config,
                                             std::string         const& parameterisation,
                                             std::vector<double> const& params,
                                             std::string         const& pf,
                                             ThreeDGrid          const& tdg = ThreeDGrid{});

  /**
   * @brief Function that produces the info file of the TMD set. This
   * is suppose to resamble an LHAPDF info file for the TMDs. We use
   * plain YAML format.
   * @param config: the YAML not with the theory settings
   * @param pf: whether PDFs ("pdf") of FFs ("ff")
   * @return a YAML emitter
   */
  std::unique_ptr<YAML::Emitter> EmitTMDInfo(YAML::Node  const& config,
                                             int         const& NumMembers,
                                             std::string const& pf,
                                             std::string const& SetDesc = "Set produced with NangaParbat + APFEL++",
                                             std::string const& Authors = "A. Bacchetta, V. Bertone, C. Bissolotti, G. Bozzi, F. Delcarro, F. Piacenza, M. Radici",
                                             std::string const& Reference = "arXiv:xxxx.xxxxx",
                                             std::string const& SetIndex = "000000",
                                             std::string const& Format = "TMDlib1",
                                             std::string const& DataVersion = "1",
                                             std::string const& ErrorType = "Monte Carlo");
}
