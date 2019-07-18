//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/utilities.h"

#include <numeric>
#include <math.h>

#include <ROOT/TGraph.h>
#include <ROOT/TGraphErrors.h>
#include <ROOT/TLegend.h>
#include <ROOT/TMultiGraph.h>
#include <ROOT/TCanvas.h>
#include <ROOT/TAxis.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  ChiSquare::ChiSquare(std::vector<std::pair<DataHandler,ConvolutionTable>> const& DSVect, Parameterisation& NPFunc, double const& qToQMax):
    _NPFunc(NPFunc),
    _qToQMax(qToQMax)
  {
    // The input parameterisation has to contain 2 functions, othewise
    // stop the code.
    if (_NPFunc.GetNumberOfFunctions() != 2)
      throw std::runtime_error("[ChiSquare::ChiSquare]: the number of functions of the input parameterisation is different from two");

    // Loop over the the blocks and and push them into the "_DSVect"
    // container.
    for (auto const& ds : _DSVect)
      AddBlock(ds);
  }

  //_________________________________________________________________________________
  ChiSquare::ChiSquare(Parameterisation& NPFunc, double const& qToQMax):
    ChiSquare{{}, NPFunc, qToQMax}
  {
  }

  //_________________________________________________________________________________
  void ChiSquare::AddBlock(std::pair<DataHandler,ConvolutionTable> const& DSBlock)
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
  std::vector<double> ChiSquare::GetResiduals(int const& ids) const
  {
    if (ids < 0 || ids >= _DSVect.size())
      throw std::runtime_error("[ChiSquare::GetResiduals]: index out of range");

    // Get "DataHandler" and "ConvolutionTable" objects
    const DataHandler      dh = _DSVect[ids].first;
    const ConvolutionTable ct = _DSVect[ids].second;

    // Get experimental central values
    const std::vector<double> mean = dh.GetMeanValues();

    // Get predictions
    auto const fNP = [&] (double const& x, double const& b, double const& zeta, int const& ifun) -> double{ return _NPFunc.Evaluate(x, b, zeta, ifun); };
    const std::vector<double> pred = ct.GetPredictions(fNP);

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
  double ChiSquare::Evaluate(int const& ids) const
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
        const std::vector<double> x = GetResiduals(i);

        // Compute contribution to the chi2 as absolute value of "x"
        chi2 += std::inner_product(x.begin(), x.end(), x.begin(), 0.);

        // Increment number of points
        ntot += _ndata[i];
      }
    return chi2 / ntot;
  }

  //_________________________________________________________________________________
  std::ostream& operator << (std::ostream& os, ChiSquare const& chi2)
  {
    // Loop over the the blocks
    for (int i = 0; i < (int) chi2._DSVect.size(); i++)
      {
        // Number of data points
        const int nd = chi2._ndata[i];

        // Get "DataHandler" and "ConvolutionTable" objects
        const DataHandler      dh = chi2._DSVect[i].first;
        const ConvolutionTable ct = chi2._DSVect[i].second;

        // Get experimental central values uncorrelated and correlated
        // uncertainties.
        const std::vector<double> mean = dh.GetMeanValues();
        const std::vector<double> uncu = dh.GetUncorrelatedUnc();
        const std::vector<std::vector<double>> corr = dh.GetCorrelatedUnc();

        // Get predictions
        auto const fNP = [&] (double const& x, double const& b, double const& zeta, int const& ifun) -> double{ return chi2._NPFunc.Evaluate(x, b, zeta, ifun); };
        const std::vector<double> pred = ct.GetPredictions(fNP);

        // Now compute systematic shifts. Compute residuals only for
        // the points that pass the cut qT / Q, set the others to
        // zero.
        std::vector<double> res(mean.size(), 0.);
        for (int j = 0; j < nd; j++)
          res[j] = mean[j] - pred[j];

        // Construct matrix A and vector rho
        const int nsys = corr[0].size();
        apfel::matrix<double> A;
        A.resize(nsys, nsys, 0.);
        std::vector<double>   rho(nsys, 0.);
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

        // Compute chi2 using the shifts
        double chi2n = 0;
        for(int j = 0; j < nd; j++)
          chi2n += pow( ( res[j] - shifts[j] ) / uncu[j], 2);

        // Compute penalty
        double penalty = 0;
        for(int alpha = 0; alpha < nsys; alpha++)
          penalty += pow(lambda[alpha], 2);

        // Add penalty to the chi2 and divide by the number of data
        // points.
        chi2n += penalty;
        chi2n /= nd;

        // Get values of qT
        const std::vector<double> qT = dh.GetKinematics().qTv;

        // Print predictions, experimental central value, uncorrelated
        // uncertainty and systemetic shift.
        os << std::scientific;
        os << "# Dataset name: " << dh.GetName() << " [chi2 (using the shifts) = " << chi2n << "]\n";
        os << "#\t"
           << "  qT [GeV]  \t"
           << "   pred.    \t"
           << "    exp.    \t"
           << "    unc.    \t"
           << "    shift   \t"
           << "shifted pred.\t"
           << "\n";
        for (int j = 0; j < nd; j++)
          os << j << "\t"
             << (dh.GetKinematics().IntqT ? ( qT[j] + qT[j+1] ) / 2 : qT[j]) << "\t"
             << pred[j] << "\t"
             << mean[j] << "\t"
             << uncu[j] << "\t"
             << shifts[j] << "\t"
             << pred[j] + shifts[j] << "\t"
             << "\n";
        os << "\n";

        // Now produce plots with ROOT
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
        theo->SetLineColor(kBlue-7);
        theo->SetLineWidth(3);
        theoshift->SetLineColor(kPink-6);
        theoshift->SetLineWidth(3);

        // Adjust legend
        TLegend* leg = new TLegend{0.7, 0.89, 0.89, 0.75};
        leg->SetFillColor(0);
        leg->AddEntry(exp, "Data", "lp");
        leg->AddEntry(theo, "Theory");
        leg->AddEntry(theoshift, "Theory + shifts");
        leg->AddEntry((TObject*)0,("#chi^{2} = " + std::to_string(chi2n)).c_str(), "");

        // Produce graph
        TMultiGraph* mg = new TMultiGraph{};
        TCanvas* c = new TCanvas{};
        mg->Add(exp, "AP");
        mg->Add(theo, "AL");
        mg->Add(theoshift, "AL");
        mg->SetTitle(dh.GetName().c_str());
        mg->Draw("AL");
        mg->GetXaxis()->SetTitle("q_{T} [GeV]");
        leg->Draw("SAME");

        // Save graph on file
        std::string outfile = dh.GetName() + ".pdf";
        c->SaveAs(outfile.c_str());

        delete exp;
        delete theo;
        delete theoshift;
        delete leg;
        delete mg;
        delete c;
      }
    return os;
  }
}
