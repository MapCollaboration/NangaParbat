//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <vector>
#include <utility>

#include <apfel/apfelxx.h>
#include <yaml-cpp/yaml.h>
#include <gsl/gsl_rng.h>

namespace NangaParbat
{
  /**
   * @brief The "DataHandler" class provides a common interface to all
   * datasets. It provides methods to get kinematics, central values,
   * uncertainties, etc.
   */
  class DataHandler
  {
  public:

    /**
     * @brief The process enumerator
     */
    enum Process: int {UnknownProcess = -1, DY = 0, SIDIS = 1, SIA = 2};

    /**
     * @brief Structure containing the kinematic information of one
     * single data set.
     */
    struct Kinematics
    {
      Kinematics();
      bool empty() const;
      int                                    ndata;    //!< Number of data points
      double                                 Vs;       //!< Center of mass energy
      std::vector<double>                    qTv;      //!< Vector of qT values
      std::vector<std::pair<double, double>> qTmap;    //!< Map of qT bounds to associate to the single bins
      std::vector<double>                    qTfact;   //!< Possible bin-by-bin prefactors to multiply the theoretical predictions
      std::pair<double, double>              var1b;    //!< Variable 1 integration bounds
      std::pair<double, double>              var2b;    //!< Variable 2 integration bounds
      std::pair<double, double>              var3b;    //!< Variable 3 integration bounds
      bool                                   IntqT;    //!< Whether the bins in qTv are integrated over
      bool                                   Intv1;    //!< Whether the bins variable 1 are integrated over
      bool                                   Intv2;    //!< Whether the bins variable 2 are integrated over
      bool                                   Intv3;    //!< Whether the bins variable 3 are integrated over
      bool                                   PSRed;    //!< Whether there is a final-state PS reduction
      double                                 pTMin;    //!< Minimum pT of the final-state leptons
      std::pair<double, double>              etaRange; //!< Allowed range in eta of the final-state leptons
    };

    /**
     * @brief The "DataHandler" constructor.
     * @param name: the name associated to the data set
     * @param datafile: the YAML:Node with the interpolation table
     * @param rng: GSL random number object
     * @param fluctuation: ID of the fluctuation (i.e. Monte-Carlo replica ID) (default: 0, i.e. no fluctuations)
     * @param t0: vector of predictions to be used for the t0-prescription
     */
    DataHandler(std::string const& name, YAML::Node const& datafile, gsl_rng* rng = NULL, int const& fluctuation = 0, std::vector<double> const& t0 = {});

    virtual ~DataHandler() {};

    /**
     * @brief Function that sets the covariance matrix replacing that
     * computed in the constructor. The Choleski is also recomputed.
     * @param covmat: the new covariance matrix
     */
    void SetCovarianceMatrix(apfel::matrix<double> const& covmat);

    /**
     * @brief Function that updates the covariance matrix computed in
     * the constructor. The Choleski is also recomputed.
     * @param covmat: the new covariance matrix
     */
    void UpdateCovarianceMatrix(apfel::matrix<double> const& covmat);

    /**
     * @brief Function that returns the name of the dataset
     */
    std::string GetName() const { return _name; };

    /**
     * @brief Function that returns the process code
     */
    Process GetProcess() const { return _proc; };

    /**
     * @brief Function that returns the target isoscalarity
     * @note The code always assumes that one of the hadrons has
     * isoscalarity 1, meaning that it's a single hadron whose
     * distributions don't need to be manipulated.
     */
    double GetTargetIsoscalarity() const { return _targetiso; };

    /**
     * @brief Function that returns the possible identified hadron
     * species in the final state.
     */
    std::string GetHadron() const { return _hadron; };

    /**
     * @brief Function that returns the charge of the identified final
     * state.
     */
    int GetCharge() const { return _charge; };

    /**
     * @brief Function that returns the quark-tagged compoments. Zero
     * corresponds to total.
     */
    std::vector<apfel::QuarkFlavour> GetTagging() const { return _tagging; };

    /**
     * @brief Function that returns any possible constant prefactor to
     * be used to multiply the theoretical predictions.
     */
    double GetPrefactor() const { return _prefact; };

    /**
     * @brief Function that returns the kinematic object
     */
    Kinematics GetKinematics() const { return _kin; };

    /**
     * @brief Function that returns the mean values
     */
    std::vector<double> GetMeanValues() const { return _means; };

    /**
     * @brief Function that returns the fluctuated data
     */
    std::vector<double> GetFluctutatedData() const { return _fluctuations; };

    /**
     * @brief Function that returns the sum in quadrature of the
     * uncorrelated uncertainties.
     */
    std::vector<double> GetUncorrelatedUnc() const { return _uncor; };

    /**
     * @brief Function that returns the additive correlated systematic
     * uncertainties.
     */
    std::vector<std::vector<double>> GetAddCorrelatedUnc() const { return _corra; };

    /**
     * @brief Function that returns the multiplicative correlated
     * systematic uncertainties.
     */
    std::vector<std::vector<double>> GetMultCorrelatedUnc() const { return _corrm; };

    /**
     * @brief Function that returns the all the correlated systematic
     * uncertainties (additive first and multiplicative second).
     */
    std::vector<std::vector<double>> GetCorrelatedUnc() const { return _corr; };

    /**
     * @brief Function that returns the covariance matrix of the
     * correlated uncertainties.
     */
    apfel::matrix<double> GetCovarianceMatrix() const { return _covmat; };

    /**
     * @brief Function that returns the Cholesky decomposition of the
     * covariance matrix.
     */
    apfel::matrix<double> GetCholeskyDecomposition() const { return _CholL; };

    /**
     * @brief Function that returns the set of t0 predictions
     */
    std::vector<double> GetT0() const { return _t0; };

    /**
     * @brief Function that returns the plotting labels.
     */
    std::map<std::string, std::string> GetLabels() const { return _labels; };

    virtual int GetNkins() const { return -1; }; //FF_SIDIS

  protected:

    std::string                        _name;         //!< Name of the dataset
    Process                            _proc;         //!< The process
    double                             _targetiso;    //!< Isoscalarity of the target
    std::string                        _hadron;       //!< Hadron species identified in the final state
    double                             _charge;       //!< Charge of the identified final state
    std::vector<apfel::QuarkFlavour>   _tagging;      //!< Possible quark-tagged components
    double                             _prefact;      //!< Possible overall prefactor to multiply the theoretical predictions
    Kinematics                         _kin;          //!< Kinematics block
    std::vector<double>                _means;        //!< Vector of central values
    std::vector<double>                _uncor;        //!< Vector of uncorrelated uncertainties
    std::vector<std::vector<double>>   _corra;        //!< Additive correlated uncertainties
    std::vector<std::vector<double>>   _corrm;        //!< Multiplicative correlated uncertainties
    std::vector<std::vector<double>>   _corr;         //!< All correlated uncertainties
    apfel::matrix<double>              _covmat;       //!< Covariance matrix
    apfel::matrix<double>              _CholL;        //!< Cholesky decomposition of the covariance matrix
    std::map<std::string, std::string> _labels;       //!< Labels used for plotting
    std::vector<double>                _fluctuations; //!< Vector of fluctuated data
    std::vector<double>                _t0;           //!< Vector of t0-predictions

    friend std::ostream& operator << (std::ostream& os, DataHandler const& DH);
  };

  std::ostream& operator << (std::ostream &os, DataHandler const& DH);
}
