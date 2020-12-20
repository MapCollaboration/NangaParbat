//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
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
   * @brief Structure that contains the 4D grid in Q, x, z and qT.
   */
  struct FourDGrid
  {
    std::vector<double> Qg;       //!< Grid in Q
    std::vector<double> xg;       //!< Grid in x
    std::vector<double> zg;       //!< Grid in z
    std::vector<double> qToQg;    //!< Grid in  qT/Q
  };

  /**
   * @brief Function that returns FourDGrid object better tuned for
   * F_UUT, according to the input string.
   */
  FourDGrid Inter4DGrid(std::string const& pf)
  {
    FourDGrid grid{};
    grid.Qg = std::vector<double>
    {
      1.000000e+00, 1.080000e+00, 1.118030e+00, 1.170000e+00, 1.224740e+00,
      1.300000e+00, 1.400000e+00, 1.581140e+00, 1.788850e+00, 2.000000e+00,
      2.236070e+00, 2.529820e+00, 2.828430e+00, 3.162280e+00, 3.464100e+00,
      4.750000e+00, 5.099020e+00, 6.324560e+00, 7.100000e+00, 8.000000e+00,
      1.000000e+01, 1.118030e+01, 1.224750e+01, 1.400000e+01, 1.581140e+01,
      1.788850e+01, 2.000000e+01, 2.236070e+01, 2.529820e+01, 2.828430e+01,
      3.162280e+01, 3.464100e+01, 4.750000e+01, 5.099020e+01, 6.324560e+01,
      7.100000e+01, 8.000000e+01, 1.000000e+02
    };
    grid.xg = std::vector<double>
    {
      1.000000e-05, 2.000000e-05, 4.000000e-05, 6.000000e-05, 8.000000e-05,
      1.000000e-04, 2.000000e-04, 4.000000e-04, 6.000000e-04, 8.000000e-04,
      1.000000e-03, 1.500000e-03, 2.000000e-03, 2.500000e-03, 3.000000e-03,
      3.500000e-03, 4.000000e-03, 4.500000e-03, 5.000000e-03, 5.500000e-03,
      6.000000e-03, 6.500000e-03, 7.000000e-03, 7.500000e-03, 8.000000e-03,
      8.500000e-03, 9.000000e-03, 9.250000e-03, 9.500000e-03, 9.750000e-03,
      1.000000e-02, 1.500000e-02, 2.000000e-02, 2.500000e-02, 3.000000e-02,
      3.500000e-02, 4.000000e-02, 4.500000e-02, 5.000000e-02, 5.500000e-02,
      6.000000e-02, 6.500000e-02, 7.000000e-02, 7.500000e-02, 8.000000e-02,
      8.500000e-02, 9.000000e-02, 9.250000e-02, 9.500000e-02, 9.750000e-02,
      1.000000e-01, 1.500000e-01, 2.000000e-01, 2.500000e-01, 3.000000e-01,
      3.500000e-01, 4.000000e-01, 4.500000e-01, 5.000000e-01, 5.500000e-01,
      6.000000e-01, 6.500000e-01, 7.000000e-01, 7.500000e-01, 8.000000e-01
    };
    grid.zg = std::vector<double>
    {
      0.100, 0.125, 0.150, 0.175,
      0.200, 0.225, 0.250, 0.275,
      0.300, 0.325, 0.350, 0.375,
      0.400, 0.425, 0.450, 0.475,
      0.500, 0.525, 0.550, 0.575,
      0.600, 0.625, 0.650, 0.700,
      0.750, 0.80
    };
    grid.qToQg =
    {
      0.0001, 0.0010, 0.0025, 0.0050, 0.0075, 0.0100, 0.0200, 0.0300, 0.0400,
      0.0500, 0.0600, 0.0700, 0.0800, 0.0900, 0.1000, 0.1100, 0.1200, 0.1300,
      0.1400, 0.1500, 0.1600, 0.1700, 0.1800, 0.1900, 0.2000, 0.2200, 0.2400,
      0.2600, 0.2800, 0.3000, 0.3200, 0.3400, 0.3600, 0.3800, 0.4000, 0.4500,
      0.5000, 0.5500, 0.6000, 0.6500, 0.7000, 0.8000, 0.9000, 1
    };

    return grid;
  };

  // /**
  //  * @brief Map of perturbative orders
  //  */
  // const std::map<int, std::string> PtOrderMapSF{{0, "LL"}, {1, "NLL"}, {-1, "NLL'"}, {2, "NNLL"}, {-2, "NNLL'"}, {3, "NNNLL"}};

  /**
   * @brief This function encapsulates and streamlines the production
   * of an interpolation grid for a structure function starting from
   * TMD grids.
   * @param GridsDirectory: path to main folder
   * @param GridTMDPDFfolder: name of TMDPDF grids (subfolder of main folder)
   * @param GridTMDFFfolder: name of TMDFF grids (subfolder of main folder)
   * @param Output: name of the output grid
   * @param repID: number of the replica
   * @param structype: whether F_UUT or others (not implemented yet)
   */
  void ProduceStructGrid(std::string const& GridsDirectory,
                         std::string const& GridTMDPDFfolder,
                         std::string const& GridTMDFFfolder,
                         std::string const& Output,
                         std::string const& repID = "none",
                         std::string const& structype = "FUUT");

  /**
   * @brief Function that produces the structure function interpolation grid in
   * momentum space. This is supposed to resamble an LHAPDF grid.
   * We use plain YAML format.
   * @param GridsDirectory: path to main folder
   * @param GridTMDPDFfolder: name of TMDPDF grids (subfolder of main folder)
   * @param GridTMDFFfolder: name of TMDFF grids (subfolder of main folder)
   * @param repnumber: replica number
   * @param fdg: 4D grid used
   * @param qToQcut: cut for the convolution integral
   * @param pf: whether F_UUT or others (not implemented yet)
   * @return a YAML emitter
   */
  std::unique_ptr<YAML::Emitter> EmitStructGrid(std::string const& GridsDirectory,
                                                std::string const& GridTMDPDFfolder,
                                                std::string const& GridTMDFFfolder,
                                                int         const& repnumber,
                                                std::string const& pf,
                                                FourDGrid   const& fdg,
                                                int         const& qToQcut = 5);

  /**
   * @brief Function that produces the structure function interpolation grid in
   * momentum space. This is supposed to resamble an LHAPDF grid.
   * We use plain YAML format.
   * @param FitDirectory: path to main folder, output of NangaParbat fit
   * @param repnumber: replica number
   * @param fdg: 4D grid used
   * @param qToQcut: cut for the convolution integral
   * @param pf: whether F_UUT or others (not implemented yet)
   * @return a YAML emitter
   */
  std::unique_ptr<YAML::Emitter> EmitStructGridDirect(std::string const& FitDirectory,
                                                      int         const& repnumber,
                                                      std::string const& pf,
                                                      FourDGrid   const& fdg,
                                                      int         const& qToQcut);

  /**
   * @brief Function that produces the info file of the TMD set. This
   * is suppose to resamble an LHAPDF info file for the TMDs. We use
   * plain YAML format.
   * @param config: the YAML not with the theory settings
   * @param pf: whether PDFs ("pdf") of FFs ("ff")
   * @return a YAML emitter
   */
  std::unique_ptr<YAML::Emitter> EmitStructInfo(std::string      const& GridsDirectory,
                                                std::string      const& GridTMDPDFfolder,
                                                std::string      const& GridTMDFFfolder,
                                                YAML::Node       const& config,
                                                int              const& NumMembers,
                                                std::string      const& pf,
                                                FourDGrid        const& fdg,
                                                std::vector<int> const& Flavors = {-5, -4, -3, -2, -1, 1, 2, 3, 4, 5},
                                                std::string      const& SetDesc = "Set produced with NangaParbat + APFEL++ (please cite arXiv:1912.07550 and arXiv:1708.00911)",
                                                std::string      const& Target = "proton",
                                                std::string      const& Hadron = "Pip",
                                                std::string      const& Authors = "A. Bacchetta, F. Delcarro, C. Pisano, M. Radici, A. Signori",
                                                std::string      const& Reference = "arXiv:1703.10157",
                                                // std::string      const& Authors = "A. Bacchetta, V. Bertone, C. Bissolotti, G. Bozzi, F. Delcarro, F. Piacenza, M. Radici",
                                                // std::string      const& Reference = "arXiv:1912.07550",
                                                std::string      const& SetIndex = "000000",
                                                std::string      const& Format = "TMDlib2",
                                                std::string      const& DataVersion = "1",
                                                std::string      const& ErrorType = "Monte Carlo");
}
