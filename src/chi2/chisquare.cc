//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/linearsystems.h"

#include <numeric>
#include <math.h>
#include <sys/stat.h>
#include <fstream>

namespace NangaParbat
{
  //_________________________________________________________________________________
  ChiSquare::ChiSquare(std::vector<std::pair<DataHandler*, ConvolutionTable*>> DSVect, Parameterisation* NPFunc):
    _NPFunc(NPFunc)
  {
    // The input parameterisation has to contain 2 functions, othewise
    // stop the code.
    if (_NPFunc->GetNumberOfFunctions() != 2)
      throw std::runtime_error("[ChiSquare::ChiSquare]: the number of functions of the input parameterisation is different from two");

    // Loop over the the blocks and and push them into the "_DSVect"
    // container.
    for (auto const& ds : DSVect)
      AddBlock(ds);
  }

  //_________________________________________________________________________________
  ChiSquare::ChiSquare(Parameterisation* NPFunc):
    ChiSquare{{}, NPFunc}
  {
  }

  //_________________________________________________________________________________
  void ChiSquare::AddBlock(std::pair<DataHandler*, ConvolutionTable*> DSBlock)
  {
    // Push "DataHandler-ConvolutionTable" back
    _DSVect.push_back(DSBlock);

    // Determine number of data points that pass the cut qT / Q.
    const DataHandler::Kinematics kin      = DSBlock.first->GetKinematics();
    //const double                  qToQMax = DSBlock.second->GetCutqToverQ();
    const DataHandler::Process    proc     = DSBlock.first->GetProcess();
    const std::vector<double>     cutParam = DSBlock.second->GetcutParam();
    const std::vector<double>     qTv      = kin.qTv;

    if (proc == 0) //DY
      {
        int idata = 0;

        const double Qmin = (kin.Intv1 ? kin.var1b.first : ( kin.var1b.first + kin.var1b.second ) / 2);

        double qToQMax = std::min(cutParam[0], cutParam[1]);

        for (auto const& qT : qTv)
          if (qT / Qmin < qToQMax)
            idata++;

        _ndata.push_back(idata - (kin.IntqT ? 1 : 0));

        // Data the pass all the cuts
        const std::valarray<bool> cm = DSBlock.second->GetCutMask();
        _ndatac.push_back(std::count(std::begin(cm), std::end(cm), true));
      }
    else if (proc == 1) //SIDIS
      {
        const double Qmin  = (kin.Intv1 ? kin.var1b.first : DSBlock.first->GetBinning()[0].Qav);
        const double zmin  = (kin.Intv3 ? kin.var3b.first : DSBlock.first->GetBinning()[0].zav);

        // Run over the qTv vector, count how many data points pass
        // the cut and push the number into the "_ndata" vector.
        int idata = 0;

        double qToQMax = std::min(std::min(cutParam[0] / zmin, cutParam[1]) + cutParam[2] / Qmin / zmin, 1.0);
        // double qToQMax = std::min(cutParam[0] / zmin, cutParam[1]) + cutParam[2] / Qmin / zmin;

        for (auto const& qT : qTv)
          if (qT / Qmin / zmin < qToQMax)
            idata++;

        _ndata.push_back(idata - (kin.IntqT ? 1 : 0));

        // Data the pass all the cuts
        const std::valarray<bool> cm = DSBlock.second->GetCutMask();
        _ndatac.push_back(std::count(std::begin(cm), std::end(cm), true));
      }
    else
      {
        throw std::runtime_error("[Chisquare::AddBlock]: Only SIDIS or DY data sets can be treated here.");
      }
  };

  //_________________________________________________________________________________
  std::vector<double> ChiSquare::GetResiduals(int const& ids, bool const& central) const
  {
    if (ids < 0 || ids >= (int) _DSVect.size())
      throw std::runtime_error("[ChiSquare::GetResiduals]: index out of range");

    // Get "DataHandler" and "ConvolutionTable" objects
    DataHandler      *dh = _DSVect[ids].first;
    ConvolutionTable *ct = _DSVect[ids].second;

    // Get experimental values
    const std::vector<double> cntr = dh->GetMeanValues();
    std::vector<double> mean;
    if (central)
      mean = cntr;
    else
      mean = dh->GetFluctutatedData();

    // Get predictions
    const std::vector<double> pred = ct->GetPredictions(_NPFunc->Function());

    // Check that the number of points in the DataHandler and
    // Convolution table objects is the same.
    if (mean.size() != pred.size())
      throw std::runtime_error("[ChiSquare::GetResiduals]: mismatch in the number of points");

    // Get cut mask
    const std::valarray<bool> cm = ct->GetCutMask();

    // Compute residuals only for the points that pass the cuts, set
    // the others to zero.
    std::vector<double> res(_ndata[ids], 0.);
    for (int j = 0; j < _ndata[ids]; j++)
      res[j] = mean[j] - (cm[j] ? pred[j] : cntr[j]);

    // Solve lower-diagonal system and return the result
    return SolveLowerSystem(dh->GetCholeskyDecomposition(), res);
  }

  //_________________________________________________________________________________
  std::vector<double> ChiSquare::GetResidualDerivatives(int const& ids, int const& ipar) const
  {
    if (ids < 0 || ids >= (int) _DSVect.size())
      throw std::runtime_error("[ChiSquare::GetResidualDerivatives]: index out of range");

    // Get "DataHandler" and "ConvolutionTable" objects
    DataHandler      *dh = _DSVect[ids].first;
    ConvolutionTable *ct = _DSVect[ids].second;

    // Get (fluctuated) experimental central values
    const std::vector<double> mean = dh->GetFluctutatedData();

    // Get predictions
    auto const dNP = [&] (double const& x, double const& b, double const& zeta, int const& ifun) -> double{ return _NPFunc->Derive(x, b, zeta, ifun, ipar); };
    const std::vector<double> dpred = ct->GetPredictions(_NPFunc->Function(), dNP);

    // Check that the number of points in the DataHandler and
    // Convolution table objects is the same.
    if (mean.size() != dpred.size())
      throw std::runtime_error("[ChiSquare::GetResidualDerivatives]: mismatch in the number of points");

    // Get cut mask
    const std::valarray<bool> cm = ct->GetCutMask();

    // Compute residuals only for the points that pass the cuts, set
    // the others to zero.
    std::vector<double> res(_ndata[ids], 0.);
    for (int j = 0; j < _ndata[ids]; j++)
      res[j] = (cm[j] ? - dpred[j] : 0);

    // Solve lower-diagonal system and return the result
    return SolveLowerSystem(dh->GetCholeskyDecomposition(), res);
  }

  //_________________________________________________________________________________
  std::pair<std::vector<double>, double> ChiSquare::GetSystematicShifts(int const& ids) const
  {
    if (ids < 0 || ids >= (int) _DSVect.size())
      throw std::runtime_error("[ChiSquare::GetResiduals]: index out of range");

    // Number of data points
    const int nd = _ndata[ids];

    // Get "DataHandler" and "ConvolutionTable" objects
    DataHandler      *dh = _DSVect[ids].first;
    ConvolutionTable *ct = _DSVect[ids].second;

    // Get experimental central values, uncorrelated and correlated
    // uncertainties. Rescale the multiplicative correlation if the t0
    // prescription is being used.
    const std::vector<double> fluc = dh->GetFluctutatedData();
    const std::vector<double> mean = dh->GetMeanValues();
    const std::vector<double> uncu = dh->GetUncorrelatedUnc();
    const std::vector<double> t0   = dh->GetT0();
    const std::vector<std::vector<double>> corra = dh->GetAddCorrelatedUnc();
    const std::vector<std::vector<double>> corrm = dh->GetMultCorrelatedUnc();
    std::vector<std::vector<double>> corr(mean.size());
    for (int j = 0; j < nd; j++)
      {
        std::vector<double> c = corra[j];
        double t0fact = 1;
        if (!t0.empty())
          t0fact = t0[j] / mean[j];
        for (auto const m : corrm[j])
          c.push_back(t0fact * m);
        corr[j] = c;
      }

    // Get predictions
    const std::vector<double> pred = ct->GetPredictions(_NPFunc->Function());

    // Get cut mask
    const std::valarray<bool> cm = ct->GetCutMask();

    // Compute residuals only for the points that pass the cuts, set
    // the others to zero.
    std::vector<double> res(mean.size(), 0.);
    for (int j = 0; j < nd; j++)
      res[j] = fluc[j] - (cm[j] ? pred[j] : mean[j]);

    // Construct matrix A and vector rho
    const int nsys = corr[0].size();
    apfel::matrix<double> A;
    A.resize(nsys, nsys, 0.);
    std::vector<double> rho(nsys, 0.);
    for(int alpha = 0; alpha < nsys; alpha++)
      {
        for(int j = 0; j < nd; j++)
          rho[alpha] += res[j] * corr[j][alpha] * mean[j] / pow(uncu[j], 2);

        A(alpha, alpha) = 1;
        for(int beta = 0; beta < nsys; beta++)
          for(int j = 0; j < nd; j++)
            A(alpha, beta) += corr[j][alpha] * corr[j][beta] * pow(mean[j], 2) / pow(uncu[j], 2);
      }

    // Solve A * lambda = rho to obtain the nuisance parameters
    const std::vector<double> lambda = SolveSymmetricSystem(A, rho);

    // Compute systematic shifs
    std::vector<double> shifts(mean.size(), 0.);
    for (int j = 0; j < nd; j++)
      for(int alpha = 0; alpha < nsys; alpha++)
        shifts[j] += lambda[alpha] * corr[j][alpha] * mean[j];

    // Compute penalty
    double penalty = 0;
    for(int alpha = 0; alpha < nsys; alpha++)
      penalty += pow(lambda[alpha], 2);

    // Solve A * lambda = rho to obtain the nuisance parameters lambda
    // and return the result.
    return std::make_pair(shifts, penalty);
  }

  //_________________________________________________________________________________
  double ChiSquare::Evaluate(int const& ids, bool const& central) const
  {
    // Define index range
    int istart = 0;
    int iend   = _DSVect.size();
    if (ids >= istart && ids < iend)
      {
        istart = ids;
        iend   = ids + 1;
      }

    // Initialise chi2 and number of data points
    double chi2 = 0;
    int ntot = 0;

    // Loop over the the blocks
    for (int i = istart; i < iend; i++)
      {
        // Get residuals
        const std::vector<double> x = GetResiduals(i, central);

        // Compute contribution to the chi2 as absolute value of "x"
        chi2 += std::inner_product(x.begin(), x.end(), x.begin(), 0.);

        // Increment number of points
        ntot += _ndata[i];
      }

    return (ntot == 0 ? 0 : chi2 / ntot);
  }

  //_________________________________________________________________________________
  std::vector<double> ChiSquare::Derive() const
  {
    // Get number of parameters of the parametersation
    const int npars = _NPFunc->GetParameters().size();

    // Number of data sets
    const int nsets = _DSVect.size();

    // Allocate vector of derivatives
    std::vector<double> ders(npars);

    // Get all residuals at once
    std::vector<std::vector<double>> vx(nsets);
    for (int i = 0; i < nsets; i++)
      vx[i] = GetResiduals(i);

    // Loop over parameters
    for (int ipar = 0; ipar < npars; ipar++)
      {
        // Initialise chi2 and number of data points
        double dchi2 = 0;
        int ntot = 0;

        // Loop over the the blocks
        for (int i = 0; i < nsets; i++)
          {
            // Get residuals and its derivatives to construct the
            // derivative of the chi2.
            const std::vector<double> dx = GetResidualDerivatives(i, ipar);

            for (int j = 0; j < (int) dx.size(); j++)
              dchi2 += 2 * vx[i][j] * dx[j];

            // Increment number of points
            ntot += _ndata[i];
          }
        ders[ipar] = dchi2 / ntot;
      }
    return ders;
  }

  //_________________________________________________________________________________
  YAML::Emitter& operator << (YAML::Emitter& os, ChiSquare const& chi2)
  {
    os.SetFloatPrecision(8);
    os.SetDoublePrecision(8);
    os << YAML::BeginMap;
    os << YAML::Key << "Global error function" << YAML::Value << chi2.Evaluate();
    os << YAML::Key << "Global chi2" << YAML::Value << chi2.Evaluate(-1, true);
    os << YAML::Key << "Parameterisation" << YAML::Value << chi2._NPFunc->GetName();
    os << YAML::Key << "Non-perturbative function" << YAML::Value << chi2.GetNonPerturbativeFunction()->LatexFormula();

    os << YAML::Key << "Parameters" << YAML::Value << YAML::Flow;
    os << YAML::BeginMap;
    for (int i = 0; i < (int) chi2.GetParameters().size(); i++)
      os << YAML::Key << chi2.GetNonPerturbativeFunction()->GetParameterNames()[i] << YAML::Value << chi2.GetParameters()[i];
    os << YAML::EndMap;

    // Loop over the blocks
    os << YAML::Key << "Experiments" << YAML::Value << YAML::BeginSeq;
    for (int i = 0; i < (int) chi2._DSVect.size(); i++)
      {
        // Number of data points
        const int nd = chi2._ndata[i];

        // Get "DataHandler" and "ConvolutionTable" objects
        DataHandler      * dh = chi2._DSVect[i].first;
        ConvolutionTable * ct = chi2._DSVect[i].second;

        // Get predictions
        const std::vector<double> pred = ct->GetPredictions(chi2._NPFunc->Function());

        // Get systematic shifts and associated penalty
        const std::pair<std::vector<double>, double> sp = chi2.GetSystematicShifts(i);
        const std::vector<double> shifts = sp.first;

        // Get experimental central values and uncorrelated
        // uncertainties.
        const std::vector<double> mean = dh->GetMeanValues();
        const std::vector<double> fluc = dh->GetFluctutatedData();
        const std::vector<double> uncu = dh->GetUncorrelatedUnc();

        // Compute chi2 starting from the penalty
        double chi2n = sp.second;
        for(int j = 0; j < nd; j++)
          chi2n += pow( ( fluc[j] - pred[j] - shifts[j] ) / uncu[j], 2);
        chi2n /= nd;

        // Make sure that the chi2 computed in terms of the nuisance
        // parameters agrees with that computed using the covariance
        // matrix.
        const double chi2c = chi2.Evaluate(i);
        if (std::abs(( chi2c - chi2n ) / chi2c) > 1e-5)
          throw std::runtime_error("[ChiSquare::operator<<]: chi2 reconstruction failed");

        // Get values of qT
        const std::vector<double> qT = dh->GetKinematics().qTv;

        // Get plotting labels
        const std::map<std::string, std::string> labels = dh->GetLabels();

        // Print predictions, experimental central value, uncorrelated
        // uncertainty and systemetic shift.
        os << YAML::BeginMap;
        os << YAML::Key << "Name" << YAML::Value << dh->GetName();
        // os << YAML::Key << "Plot title" << YAML::Value << labels.at("title");
        // os << YAML::Key << "xlabel" << YAML::Value << labels.at("xlabel");
        // os << YAML::Key << "ylabel" << YAML::Value << labels.at("ylabel");
        os << YAML::Key << "Plot title python" << YAML::Value << labels.at("titlepy");
        os << YAML::Key << "xlabelpy" << YAML::Value << labels.at("xlabelpy");
        os << YAML::Key << "ylabelpy" << YAML::Value << labels.at("ylabelpy");
        os << YAML::Key << "partial error function" << YAML::Value << chi2c;
        os << YAML::Key << "partial chi2" << YAML::Value << chi2.Evaluate(i, true);
        os << YAML::Key << "penalty chi2" << YAML::Value << sp.second / nd;
        os << YAML::Key << "qT" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int j = 0; j < nd; j++)
          os << (dh->GetKinematics().IntqT ? ( qT[j] + qT[j+1] ) / 2 : qT[j]);
        os << YAML::EndSeq;
        os << YAML::Key << "Predictions" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int j = 0; j < nd; j++)
          os << pred[j];
        os << YAML::EndSeq;
        os << YAML::Key << "Central values" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int j = 0; j < nd; j++)
          os << mean[j];
        os << YAML::EndSeq;
        os << YAML::Key << "Fluctuated data" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int j = 0; j < nd; j++)
          os << fluc[j];
        os << YAML::EndSeq;
        os << YAML::Key << "Uncorrelated uncertainties" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int j = 0; j < nd; j++)
          os << uncu[j];
        os << YAML::EndSeq;
        os << YAML::Key << "Systematic shifts" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int j = 0; j < nd; j++)
          os << shifts[j];
        os << YAML::EndSeq;
        os << YAML::EndMap;
      }
    os << YAML::EndSeq;
    os << YAML::EndMap;
    return os;
  }
}
