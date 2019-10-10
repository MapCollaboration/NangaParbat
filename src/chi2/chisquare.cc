//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/utilities.h"

#include <numeric>
#include <math.h>
#include <sys/stat.h>
#include <fstream>

#include <root/TGraph.h>
#include <root/TGraphErrors.h>
#include <root/TLegend.h>
#include <root/TMultiGraph.h>
#include <root/TCanvas.h>
#include <root/TAxis.h>
#include <root/TStyle.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  ChiSquare::ChiSquare(std::vector<std::pair<DataHandler, ConvolutionTable>> const& DSVect, Parameterisation& NPFunc, double const& qToQMax):
    _NPFunc(NPFunc),
    _qToQMax(qToQMax)
  {
    // The input parameterisation has to contain 2 functions, othewise
    // stop the code.
    if (_NPFunc.GetNumberOfFunctions() != 2)
      throw std::runtime_error("[ChiSquare::ChiSquare]: the number of functions of the input parameterisation is different from two");

    // Loop over the the blocks and and push them into the "_DSVect"
    // container.
    for (auto const& ds : DSVect)
      AddBlock(ds);
  }

  //_________________________________________________________________________________
  ChiSquare::ChiSquare(Parameterisation& NPFunc, double const& qToQMax):
    ChiSquare{{}, NPFunc, qToQMax}
  {
  }

  //_________________________________________________________________________________
  void ChiSquare::AddBlock(std::pair<DataHandler, ConvolutionTable> const& DSBlock)
  {
    // Push "DataHandler-ConvolutionTable" back
    _DSVect.push_back(DSBlock);

    // Determine number of data points that pass the cut qT / Q.
    const DataHandler::Kinematics kin  = DSBlock.first.GetKinematics();
    const std::vector<double>     qTv  = kin.qTv;
    const double                  Qmin = (kin.Intv1 ? kin.var1b.first : ( kin.var1b.first + kin.var1b.second ) / 2);

    // Run over the qTv vector, count how many data points pass
    // the cut and push the number into the "_ndata" vector.
    int idata = 0;
    for (auto const& qT : qTv)
      if (qT / Qmin < _qToQMax)
        idata++;
    _ndata.push_back(idata - (kin.IntqT ? 1 : 0));
  };

  //_________________________________________________________________________________
  std::vector<double> ChiSquare::GetResiduals(int const& ids, bool const& central) const
  {
    if (ids < 0 || ids >= (int) _DSVect.size())
      throw std::runtime_error("[ChiSquare::GetResiduals]: index out of range");

    // Get "DataHandler" and "ConvolutionTable" objects
    const DataHandler      dh = _DSVect[ids].first;
    const ConvolutionTable ct = _DSVect[ids].second;

    // Get experimental values
    std::vector<double> mean;
    if (central)
      mean = dh.GetMeanValues();
    else
      mean = dh.GetFluctutatedData();

    // Get predictions
    const std::vector<double> pred = ct.GetPredictions(_NPFunc.Function());

    // Check that the number of points in the DataHandler and
    // Convolution table objects is the same.
    if (mean.size() != pred.size())
      throw std::runtime_error("[ChiSquare::GetResiduals]: mismatch in the number of points");

    // Compute residuals only for the points that pass the cut qT
    // / Q, set the others to zero.
    std::vector<double> res(_ndata[ids], 0.);
    for (int j = 0; j < _ndata[ids]; j++)
      res[j] = mean[j] - pred[j];

    // Solve lower-diagonal system and return the result
    return SolveLowerSystem(dh.GetCholeskyDecomposition(), res);
  }

  //_________________________________________________________________________________
  std::vector<double> ChiSquare::GetResidualDerivatives(int const& ids, int const& ipar) const
  {
    if (ids < 0 || ids >= (int) _DSVect.size())
      throw std::runtime_error("[ChiSquare::GetResidualDerivatives]: index out of range");

    // Get "DataHandler" and "ConvolutionTable" objects
    const DataHandler      dh = _DSVect[ids].first;
    const ConvolutionTable ct = _DSVect[ids].second;

    // Get (fluctuated) experimental central values
    const std::vector<double> mean = dh.GetFluctutatedData();

    // Get predictions
    auto const dNP = [&] (double const& x, double const& b, double const& zeta, int const& ifun) -> double{ return _NPFunc.Derive(x, b, zeta, ifun, ipar); };
    const std::vector<double> dpred = ct.GetPredictions(_NPFunc.Function(), dNP);

    // Check that the number of points in the DataHandler and
    // Convolution table objects is the same.
    if (mean.size() != dpred.size())
      throw std::runtime_error("[ChiSquare::GetResidualDerivatives]: mismatch in the number of points");

    // Compute residuals only for the points that pass the cut qT
    // / Q, set the others to zero.
    std::vector<double> res(_ndata[ids], 0.);
    for (int j = 0; j < _ndata[ids]; j++)
      res[j] = - dpred[j];

    // Solve lower-diagonal system and return the result
    return SolveLowerSystem(dh.GetCholeskyDecomposition(), res);
  }

  //_________________________________________________________________________________
  std::pair<std::vector<double>, double> ChiSquare::GetSystematicShifts(int const& ids) const
  {
    if (ids < 0 || ids >= (int) _DSVect.size())
      throw std::runtime_error("[ChiSquare::GetResiduals]: index out of range");

    // Number of data points
    const int nd = _ndata[ids];

    // Get "DataHandler" and "ConvolutionTable" objects
    const DataHandler      dh = _DSVect[ids].first;
    const ConvolutionTable ct = _DSVect[ids].second;

    // Get experimental central values, uncorrelated and correlated
    // uncertainties. Rescale the multiplicative correlation if the t0
    // prescription is being used.
    const std::vector<double> fluc = dh.GetFluctutatedData();
    const std::vector<double> mean = dh.GetMeanValues();
    const std::vector<double> uncu = dh.GetUncorrelatedUnc();
    const std::vector<double> t0   = dh.GetT0();
    const std::vector<std::vector<double>> corra = dh.GetAddCorrelatedUnc();
    const std::vector<std::vector<double>> corrm = dh.GetMultCorrelatedUnc();
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
    const std::vector<double> pred = ct.GetPredictions(_NPFunc.Function());

    // Compute residuals only for the points that pass the cut qT / Q,
    // set the others to zero.
    std::vector<double> res(mean.size(), 0.);
    for (int j = 0; j < nd; j++)
      res[j] = fluc[j] - pred[j];

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
    return chi2 / ntot;
  }

  //_________________________________________________________________________________
  std::vector<double> ChiSquare::Derive() const
  {
    // Get number of parameters of the parametersation
    const int npars = _NPFunc.GetParameters().size();

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
  void ChiSquare::MakePlots(std::string const& path) const
  {
    // Create folder to store the plots
    const std::string outdir = path + "/plots/";
    mkdir(outdir.c_str(), ACCESSPERMS);

    for (int i = 0; i < (int) _DSVect.size(); i++)
      {
        // Number of data points
        const int nd = _ndata[i];

        // Get "DataHandler" and "ConvolutionTable" objects
        const DataHandler      dh = _DSVect[i].first;
        const ConvolutionTable ct = _DSVect[i].second;

        // Get predictions
        const std::vector<double> pred = ct.GetPredictions(_NPFunc.Function());

        // Get experimental central values, uncorrelated
        // uncertainties, and correlated shifts.
        const std::vector<double> mean   = dh.GetFluctutatedData();
        const std::vector<double> uncu   = dh.GetUncorrelatedUnc();
        const std::vector<double> shifts = GetSystematicShifts(i).first;

        // Get values of qT
        const std::vector<double> qT = dh.GetKinematics().qTv;

        // Get plotting labels
        const std::map<std::string, std::string> labels = dh.GetLabels();

        // Now produce plots with ROOT
        gStyle->SetImageScaling(3.);
        TGraphErrors* exp = new TGraphErrors{};
        TGraph* theo      = new TGraph{};
        TGraph* theoshift = new TGraph{};
        for (int j = 0; j < nd; j++)
          {
            const double x = (dh.GetKinematics().IntqT ? ( qT[j] + qT[j+1] ) / 2 : qT[j]);
            exp->SetPoint(j, x, mean[j]);
            exp->SetPointError(j, 0, uncu[j]);
            theo->SetPoint(j, x, pred[j]);
            theoshift->SetPoint(j, x, pred[j] + shifts[j]);
          }
        exp->SetLineColor(1);
        exp->SetMarkerStyle(20);
        exp->SetLineWidth(2);
        exp->SetMarkerSize(1.2);
        theo->SetLineColor(kBlue-7);
        theo->SetLineWidth(3);
        theoshift->SetLineColor(kPink-6);
        theoshift->SetLineWidth(3);

        // Adjust legend
        TLegend* leg = new TLegend{0.6, 0.92, 0.89, 0.72};
        leg->SetFillColor(0);
        leg->SetBorderSize(0);
        leg->AddEntry(exp, "Data", "lp");
        leg->AddEntry(theo, "Predictions");
        leg->AddEntry(theoshift, "Shifted predictions");
        leg->AddEntry((TObject*)0,("#it{#chi}^{2} = " + std::to_string(Evaluate(i))).c_str(), "");

        // Produce graph
        TMultiGraph* mg = new TMultiGraph{};
        TCanvas* c = new TCanvas{};
        c->SetLeftMargin(0.17);
        c->SetTopMargin(0.07);
        c->SetBottomMargin(0.15);
        c->SetFrameLineWidth(2);
        mg->Add(exp, "AP");
        mg->Add(theo, "AL");
        mg->Add(theoshift, "AL");
        mg->SetTitle(labels.at("title").c_str());
        mg->Draw("AL");
        // X axis
        mg->GetXaxis()->CenterTitle();
        mg->GetXaxis()->SetLabelSize(0.045);
        mg->GetXaxis()->SetTitleSize(0.05);
        mg->GetXaxis()->SetTickLength(0.02);
        mg->GetXaxis()->SetTitle(labels.at("xlabel").c_str());
        // Y axis
        mg->GetYaxis()->CenterTitle();
        mg->GetYaxis()->SetLabelSize(0.045);
        mg->GetYaxis()->SetTitleSize(0.05);
        mg->GetYaxis()->SetTickLength(0.015);
        mg->GetYaxis()->SetTitle(labels.at("ylabel").c_str());
        leg->Draw("SAME");

        // Save graph on file
        c->SaveAs((outdir + dh.GetName() + ".pdf").c_str());

        delete exp;
        delete theo;
        delete theoshift;
        delete leg;
        delete mg;
        delete c;
      }
  }

  //_________________________________________________________________________________
  YAML::Emitter& operator << (YAML::Emitter& os, ChiSquare const& chi2)
  {
    os.SetFloatPrecision(8);
    os.SetDoublePrecision(8);
    os << YAML::BeginMap;
    os << YAML::Key << "Global error function" << YAML::Value << chi2.Evaluate();
    os << YAML::Key << "Global chi2" << YAML::Value << chi2.Evaluate(-1, true);
    os << YAML::Key << "Non-perturbative function" << YAML::Value << chi2.GetNonPerturbativeFunction().LatexFormula();

    os << YAML::Key << "Parameters" << YAML::Value << YAML::Flow;
    os << YAML::BeginMap;
    for (int i = 0; i < (int) chi2.GetParameters().size(); i++)
      os << YAML::Key << chi2.GetNonPerturbativeFunction().GetParameterNames()[i] << YAML::Value << chi2.GetParameters()[i];
    os << YAML::EndMap;

    // Loop over the blocks
    os << YAML::Key << "Experiments" << YAML::Value << YAML::BeginSeq;
    for (int i = 0; i < (int) chi2._DSVect.size(); i++)
      {
        // Number of data points
        const int nd = chi2._ndata[i];

        // Get "DataHandler" and "ConvolutionTable" objects
        const DataHandler      dh = chi2._DSVect[i].first;
        const ConvolutionTable ct = chi2._DSVect[i].second;

        // Get predictions
        const std::vector<double> pred = ct.GetPredictions(chi2._NPFunc.Function());

        // Get systematic shifts and associated penalty
        const std::pair<std::vector<double>, double> sp = chi2.GetSystematicShifts(i);
        const std::vector<double> shifts = sp.first;

        // Get experimental central values and uncorrelated
        // uncertainties.
        const std::vector<double> mean = dh.GetMeanValues();
        const std::vector<double> fluc = dh.GetFluctutatedData();
        const std::vector<double> uncu = dh.GetUncorrelatedUnc();

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
        const std::vector<double> qT = dh.GetKinematics().qTv;

        // Get plotting labels
        const std::map<std::string, std::string> labels = dh.GetLabels();

        // Print predictions, experimental central value, uncorrelated
        // uncertainty and systemetic shift.
        os << YAML::BeginMap;
        os << YAML::Key << "Name" << YAML::Value << dh.GetName();
        os << YAML::Key << "Plot title" << YAML::Value << labels.at("title");
        os << YAML::Key << "xlabel" << YAML::Value << labels.at("xlabel");
        os << YAML::Key << "ylabel" << YAML::Value << labels.at("ylabel");
        os << YAML::Key << "Plot title python" << YAML::Value << labels.at("titlepy");
        os << YAML::Key << "xlabelpy" << YAML::Value << labels.at("xlabelpy");
        os << YAML::Key << "ylabelpy" << YAML::Value << labels.at("ylabelpy");
        os << YAML::Key << "partial error function" << YAML::Value << chi2c;
        os << YAML::Key << "partial chi2" << YAML::Value << chi2.Evaluate(i, true);
        os << YAML::Key << "penalty chi2" << YAML::Value << sp.second / nd;
        os << YAML::Key << "qT" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (int j = 0; j < nd; j++)
          os << (dh.GetKinematics().IntqT ? ( qT[j] + qT[j+1] ) / 2 : qT[j]);
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
