//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <yaml-cpp/yaml.h>

#include <NangaParbat/parameterisation.h>

namespace NangaParbat
{
  /**
   * @brief Class that implements the methods fot the numerical
   * convolution of the interpolation tables with user-given
   * non-perturbative functions.
   */
  class ConvolutionTable
  {
  public:
    /**
     * @brief The "ConvolutionTable" constructor.
     * @note This constructor is supposed to be used only when
     * inherinting this class as it does not fully define a
     * "ConvolutionTable" object.
     */
    ConvolutionTable();

    /**
     * @brief The "ConvolutionTable" constructor.
     * @param table: the YAML:Node with the interpolation table
     * @param acc: the Ogata-quadrature required accuracy (default: 10<SUP>-7</SUP>)
     * @param qToQmax: maximum value allowed for the ratio qT /Q (default: 100)
     * @note The accuracy has to be intended as the best accuracy over
     * the tabulated Ogata-quadrature points. This accuracy may not be
     * met within the tabulated points.
     */
    ConvolutionTable(YAML::Node const& table, double const& qToQmax = 100, double const& acc = 1e-7);

    /**
     * @brief The "ConvolutionTable" constructor.
     * @param infile: the name of interpolation table in YAML format
     * @param acc: the Ogata-quadrature required accuracy (default: 10<SUP>-7</SUP>)
     * @param qToQmax: maximum value allowed for the ratio qT /Q (default: 100)
     * @note The accuracy has to be intended as the best accuracy over
     * the tabulated Ogata-quadrature points. This accuracy may not be
     * met within the tabulated points.
     */
    ConvolutionTable(std::string const& infile, double const& qToQmax = 100, double const& acc = 1e-7);

    /**
     * @brief This function convolutes the input convolution table with
     * two user-given non-perturbative functions.
     * @param fNP1: the first non-perturbative input function
     * @param fNP2: the second non-perturbative input function
     * @return a map that associates each value of qT to a prediction.
     */
    std::map<double, double> Convolute(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                       std::function<double(double const&, double const&, double const&)> const& fNP2) const;

    /**
     * @brief This function convolutes the input convolution table
     * with a user-given non-perturbative function assuming that first
     * and second functions are equal.
     * @param fNP: the non-perturbative input function
     * @return a map that associates each value of qT to a prediction.
     */
    std::map<double, double> Convolute(std::function<double(double const&, double const&, double const&)> const& fNP) const;

    /**
     * @brief This function returns a vector of predictions given two
     * user-given non-perturbative functions.
     * @param fNP1: the first non-perturbative input function
     * @param fNP2: the second non-perturbative input function
     * @return a vector of predictions.
     */
    virtual std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                               std::function<double(double const&, double const&, double const&)> const& fNP2) const;

    /**
     * @brief This function returns a vector of predictions given a
     * single user-given non-perturbative function.
     * @param fNP: the non-perturbative input functions parameterised by an index
     * @return a vector of predictions.
     */
    virtual std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP) const;

    /**
     * @brief This function returns a vector of predictions with a
     * single user-given non-perturbative function.
     * @param fNP: the (indexed) non-perturbative input function
     * @return a vector of predictions.
     * @note WARNING: This function is meant to be used for internal
     * purposes because it "decides" internally how to use the
     * function "fNP" and may behave unexpectedly.
     */
    virtual std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const;

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
    virtual  std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP,
                                                std::function<double(double const&, double const&, double const&, int const&)> const& dNP) const;

    /**
     * @name Getters
     * Functions to retrieve the feauture of the convolution table
     */
    ///@{
    std::string                      GetName()       const { return _name; }
    int                              GetProcess()    const { return _proc; }
    double                           GetCME()        const { return _Vs; }
    std::vector<std::vector<double>> GetqTBins()     const { return _qTmap; }
    double                           GetCutqToverQ() const { return _qToQmax; }
    ///@}

    /**
     * @brief function that makes a 3D histogram of the weights as a
     * function of b<SUB>T</SUB> and x<SUB>1,2</SUB>. See:
     * https://root.cern/doc/v610/classTHistPainter.html for details.
     */
    void PlotWeights() const;

    /**
     * @brief This function prints the numerical accuracy of the
     * Hankel tranform for each single prediction. The estimate is
     * computed by comparing the last term of the quadrature summation
     * with the sum of all of them.
     * @param fNP1: the non-perturbative input function(s)
     */
    void NumericalAccuracy(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const;

  protected:
    virtual void SetInputFFs(std::function<std::map<int, double>(double const &, double const &)> const &InDistFunc){}; //FF_SIDIS
    virtual std::vector<double> GetGrid() const {}; //FF_SIDIS

  private:
    std::string                                              const _name;    //!< Name of the table
    int                                                      const _proc;    //!< Index of the process (0: DY, 1: SIDIS)
    double                                                   const _Vs;      //!< Center of mass energy
    bool                                                     const _IntqT;   //!< Whether the bin are integrated in qT or not
    std::vector<double>                                      const _qTv;     //!< Vector of qT bin-bounds
    std::vector<std::vector<double>>                         const _qTmap;   //!< Vector of bounds for each qT bin
    std::vector<double>                                      const _qTfact;  //!< Bin-by-bin factors
    double                                                   const _prefact; //!< Overall prefactor
    std::vector<double>                                      const _z;       //!< Unscaled Ogata coordinate
    std::vector<double>                                      const _Qg;      //!< Grid in Q
    std::vector<double>                                      const _xig;     //!< Grid in &xi;
    std::map<double,std::vector<std::vector<double>>>              _PSRed;   //!< The phase-space reduction factors
    std::map<double,std::vector<std::vector<double>>>              _dPSRed;  //!< The derivative of the phase-space reduction factors
    std::map<double,std::vector<std::vector<std::vector<double>>>> _W;       //!< The weights
    double                                                         _qToQmax; //!< Maximum value allowed for the ratio qT / Q
    double                                                         _acc;     //!< The Ogata-quadrature accuracy
  };
}
