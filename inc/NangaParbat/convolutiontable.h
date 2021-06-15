//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <valarray>
#include <yaml-cpp/yaml.h>

#include <NangaParbat/parameterisation.h>
#include <NangaParbat/cut.h>

namespace NangaParbat
{
  /**
   * @brief Class that implements the methods fot the numerical
   * convolution of the interpolation tables with user-defined
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
     * @param cutParam: maximum value allowed for the ratio qT /Q (default: 100)
     * @param cuts: vector of cut objects (default: empty)
     * @param acc: the Ogata-quadrature required accuracy (default: 10<SUP>-7</SUP>)
     * @note The accuracy has to be intended as the best accuracy over
     * the tabulated Ogata-quadrature points. This accuracy may not be
     * met within the tabulated points.
     */
    //ConvolutionTable(YAML::Node const& table, double const& qToQmax = 100, std::vector<std::shared_ptr<Cut>> const& cuts = {}, double const& acc = 1e-7);
    ConvolutionTable(YAML::Node const& table, std::vector<double> const& cutParam = {}, std::vector<std::shared_ptr<Cut>> const& cuts = {}, double const& acc = 1e-7);

    /**
     * @brief The "ConvolutionTable" constructor.
     * @param infile: the name of interpolation table in YAML format
     * @param cutParam: maximum value allowed for the ratio qT /Q (default: 100)
     * @param cuts: vector of cut objects (default: empty)
     * @param acc: the Ogata-quadrature required accuracy (default: 10<SUP>-7</SUP>)
     * @note The accuracy has to be intended as the best accuracy over
     * the tabulated Ogata-quadrature points. This accuracy may not be
     * met within the tabulated points.
     */
    //ConvolutionTable(std::string const& infile, double const& qToQmax = 100, std::vector<std::shared_ptr<Cut>> const& cuts = {}, double const& acc = 1e-7);
    ConvolutionTable(std::string const& infile, std::vector<double> const& cutParam = {}, std::vector<std::shared_ptr<Cut>> const& cuts = {}, double const& acc = 1e-7);

    /**
     * @brief This function convolutes a Drell-Yan input convolution
     * table with a user-defined non-perturbative function.
     * @param fNP: the non-perturbative input function associated to PDFs
     * @return a map that associates each value of qT to a prediction.
     */
    std::map<double, double> ConvoluteDY(std::function<double(double const&, double const&, double const&)> const& fNP) const;

    /**
     * @brief This function convolutes a SIDIS input convolution
     * table with two user-defined non-perturbative functions.
     * @param fNP: the non-perturbative input function associated to PDFs
     * @param DNP: the non-perturbative input function associated to FFs
     * @return a map that associates each value of qT to a prediction.
     */
    std::map<double, double> ConvoluteSIDIS(std::function<double(double const&, double const&, double const&)> const& fNP,
                                            std::function<double(double const&, double const&, double const&)> const& DNP) const;

    /**
     * @brief This function returns a vector of predictions given two
     * user-defined non-perturbative functions.
     * @param fNP1: the first non-perturbative input function
     * @param fNP2: the second non-perturbative input function
     * @return a vector of predictions.
     */
    virtual std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                               std::function<double(double const&, double const&, double const&)> const& fNP2) const;

    /**
     * @brief This function returns a vector of predictions with a
     * single user-defined non-perturbative function.
     * @param fNP: the (indexed) non-perturbative input function
     * @return a vector of predictions.
     * @note WARNING: This function is meant to be used for internal
     * purposes because it "decides" internally how to use the
     * function "fNP" and may behave unexpectedly.
     */
    virtual std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const;

    /**
     * @brief This function returns a vector of predictions given two
     * user-defined non-perturbative function.
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
    //double                           GetCutqToverQ() const { return _qToQmax; }
    std::vector<double>              GetcutParam()   const { return _cutParam; }
    ///@}

    /**
     * @brief This function returns the mask of points that pass all
     * the cuts.
     */
    std::valarray<bool> GetCutMask() const { return _cutmask; };

  protected:
    std::string                                                           const _name;    //!< Name of the table
    int                                                                   const _proc;    //!< Index of the process (0: DY, 1: SIDIS)
    double                                                                const _Vs;      //!< Center of mass energy
    bool                                                                  const _IntqT;   //!< Whether the bin are integrated in qT or not
    std::vector<double>                                                   const _qTv;     //!< Vector of qT bin-bounds
    std::vector<std::vector<double>>                                      const _qTmap;   //!< Vector of bounds for each qT bin
    std::vector<double>                                                   const _qTfact;  //!< Bin-by-bin factors
    double                                                                const _prefact; //!< Overall prefactor
    std::vector<double>                                                   const _zOgata;  //!< Unscaled Ogata coordinate
    std::vector<double>                                                   const _Qg;      //!< Grid in Q
    std::vector<double>                                                         _xig;     //!< Grid in xi;
    std::vector<double>                                                         _xbg;     //!< Grid in xi;
    std::vector<double>                                                         _zg;      //!< Grid in xi;
    std::map<double,std::vector<std::vector<double>>>                           _PSRed;   //!< The phase-space reduction factors
    std::map<double,std::vector<std::vector<double>>>                           _dPSRed;  //!< The derivative of the phase-space reduction factors
    std::map<double,std::vector<std::vector<std::vector<double>>>>              _WDY;     //!< The weights for Drell-Yan
    std::map<double,std::vector<std::vector<std::vector<std::vector<double>>>>> _WSIDIS;  //!< The weights for SIDIS
    //double                                                                      _qToQmax; //!< Maximum value allowed for the ratio qT / Q for DY
    std::vector<double>                                                   const _cutParam; //!< The parameters needed to compute the ratio qT / Q
    double                                                                      _acc;     //!< The Ogata-quadrature accuracy
    std::vector<std::shared_ptr<Cut>>                                           _cuts;    //!< Cut objects
    std::valarray<bool>                                                         _cutmask; //!< Mask of points that pass the cuts
    YAML::Node                                                            const _table;   //!< [Temporary] Yaml node of the table

    /**
     * @name FF_SIDIS
     * Virtual functions required by FF_SIDIS
     */
    ///@{
  public:
    virtual void SetInputFFs(std::function<std::map<int, double>(double const &, double const &)> const &InDistFunc) {};
    virtual void SetInputFFs(std::function<apfel::Set<apfel::Distribution>(double const&)> const& InDistFunc) {};
    virtual std::vector<double> GetPredictions(std::function<double(double const&, double const&, double const&)> const&) const { return {}; };
    ///@}
  };
}
