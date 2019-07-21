//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  class ConvolutionTable
  {
  public:
    /**
     * @brief The "ConvolutionTable" constructor.
     * @param table: the YAML:Node with the interpolation table
     */
    ConvolutionTable(YAML::Node const& table);

    /**
     * @brief The "ConvolutionTable" constructor.
     * @param infile: the name of interpolation table in YAML format
     */
    ConvolutionTable(std::string const& infile);

    /**
     * @brief This function convolutes the input convolution table with
     * two user-given non-perturbative functions.
     * @param fNP1: the first non-perturbative input function
     * @param fNP2: the second non-perturbative input function
     * @return a map that associates each value of qT to a prediction.
     */
    std::map<double,double> Convolute(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                      std::function<double(double const&, double const&, double const&)> const& fNP2) const;

    /**
     * @brief This function convolutes the input convolution table
     * with a user-given non-perturbative function assuming that first
     * and second functions are equal.
     * @param fNP: the non-perturbative input function
     * @return a map that associates each value of qT to a prediction.
     */
    std::map<double,double> Convolute(std::function<double(double const&, double const&, double const&)> const& fNP) const;

    /**
     * @brief This function returns a vector of predictions given two
     * user-given non-perturbative functions.
     * @param fNP1: the first non-perturbative input function
     * @param fNP2: the second non-perturbative input function
     * @return a vector of predictions.
     */
    std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                       std::function<double(double const&, double const&, double const&)> const& fNP2) const;

    /**
     * @brief This function returns a vector of predictions given a
     * single user-given non-perturbative function.
     * @param fNP: the non-perturbative input functions parameterised by an index
     * @return a vector of predictions.
     */
    std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP) const;

    /**
     * @brief This function returns a vector of predictions with a
     * single user-given non-perturbative function.
     * @param fNP: the (indexed) non-perturbative input function
     * @return a vector of predictions.
     * @note WARNING: This function is meant to be used for internal
     * purposes because it "decides" internally how to use the
     * function "fNP" and may behave unexpectedly.
     */
    std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const;

    /**
     * @brief This function returns a vector of predictions given two
     * user-given non-perturbative function.
     * @param fNP: the non-perturbative input functions parameterised by an index
     * @param dNP: a second non-perturbative input function
     * parameterised by an index that is meant to return the
     * derivarive of the first function w.r.t. to some parameter of
     * "fNP"
     * @return a vector of predictions.
     * @note WARNING: This function is meant to be used for internal
     * purposes because it "decides" internally how to use the
     * function "fNP" and may behave unexpectedly. Specifically, this
     * is used to compute the anaylitic derivative of the chi2 used
     * duering the minimisation.
     */
    std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP,
                                       std::function<double(double const&, double const&, double const&, int const&)> const& dNP) const;

    /**
     * @name Getters
     * Functions to retrieve the feauture of the convolution table
     */
    ///@{
    std::string                      GetName()    const { return _name; }
    int                              GetProcess() const { return _proc; }
    double                           GetCME()     const { return _Vs; }
    std::vector<std::vector<double>> GetqTBins()  const { return _qTmap; }
    ///@}

  private:
    std::string                                                    _name;    //!< Name of the table
    int                                                            _proc;    //!< Index of the process (0: DY, 1: SIDIS)
    double                                                         _Vs;      //!< Center of mass energy
    bool                                                           _IntqT;   //!< Whether the bin are integrated in qT or not
    std::vector<double>                                            _qTv;     //!< Vector of qT bin-bounds
    std::vector<std::vector<double>>                               _qTmap;   //!< Vector of bounds for each qT bin
    std::vector<double>                                            _qTfact;  //!< Bin-by-bin factors
    double                                                         _prefact; //!< Overall prefactor
    std::vector<double>                                            _z;       //!< Unscaled Ogata coordinate
    std::vector<double>                                            _Qg;      //!< Grid in Q
    std::vector<double>                                            _xig;     //!< Grid in xi
    std::map<double,std::vector<std::vector<double>>>              _PSRed;   //!< The phase-space reduction factors
    std::map<double,std::vector<std::vector<double>>>              _dPSRed;  //!< The derivative of the phase-space reduction factors
    std::map<double,std::vector<std::vector<std::vector<double>>>> _W;       //!< The weights
  };
}
