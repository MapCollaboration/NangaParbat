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
     * @brief This function returns a vector of predictions with a
     * two user-given non-perturbative functions.
     * @param fNP1: the first non-perturbative input function
     * @param fNP2: the second non-perturbative input function
     * @return a vector of predictions.
     */
    std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP1,
				       std::function<double(double const&, double const&, double const&)> const& fNP2) const;

    /**
     * @brief This function returns a vector of predictions with a
     * two user-given non-perturbative functions.
     * @param fNP: the (indexed) non-perturbative input function
     * @return a vector of predictions.
     */
    std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const;

    /**
     * @brief This function returns a vector of predictions with a
     * a user-given non-perturbative function  assuming that first
     * and second functions are equal.
     * @param fNP: the first non-perturbative input function
     * @return a vector of predictions.
     * @note WARNING: This function is meant to be used for internal purposes
     * because it "decides" how to use the function "fNP" and may
     * behave in an unexpected way.
     */
    std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP) const;

    /**
     * @defgroup ConvolutionTableGetters Getter functions to retrieve
     * the feauture of the convolution table
     */
    ///@{
    std::string         GetName()       const { return _name; }
    int                 GetProcess()    const { return _proc; }
    int                 GetObservable() const { return _obs; }
    double              GetCME()        const { return _Vs; }
    std::vector<double> GetqTBins()     const { return _qTv; }
    ///@}

  private:
    std::string                                                    _name;  //!< Name of the table
    int                                                            _proc;  //!< Index of the process (0: DY, 1: SIDIS)
    int                                                            _obs;   //!< Index of the observable
    double                                                         _Vs;    //!< Center of mass energy
    bool                                                           _IntqT; //!< Whether the bin are integrated in qT or not
    std::vector<double>                                            _qTv;   //!< Vector of qT
    std::vector<double>                                            _z;     //!< Unscaled Ogata coordinate
    std::vector<double>                                            _Qg;    //!< Grid in Q
    std::vector<double>                                            _xig;   //!< Grid in xi
    std::map<double,std::vector<std::vector<std::vector<double>>>> _W;     //!< The weights
  };
}
