//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/factories.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"

#include <LHAPDF/LHAPDF.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./TestConvolution <set 1> <set 2>\n" << std::endl;
      exit(-10);
    }

  // Kinematics
  const double Q = 5;
  const double x = 0.1;
  const double z = 0.3;

  // Fully differential results
  const int PerturbativeOrder = 1;

  // Get non-perturbative functions
  const NangaParbat::Parameterisation* fNP = NangaParbat::GetParametersation("PV17");

  // Open LHAPDF sets
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF("MMHT2014lo68cl");
  LHAPDF::PDF* distff  = LHAPDF::mkPDF("DSS14_NLO_PiSum");

  // Get heavy-quark thresholds from the PDF LHAPDF set
  std::vector<double> Thresholds;
  for (auto const& v : distpdf->flavors())
    if (v > 0 && v < 7)
      Thresholds.push_back(distpdf->quarkThreshold(v));

  // Alpha_s
  const auto AlphasPDF = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };
  const auto AlphasFF  = [&] (double const& mu) -> double{ return distff->alphasQ(mu); };

  // Charges
  const std::function<std::vector<double>(double const&)> Bq = [] (double const&) -> std::vector<double> { return apfel::QCh2; };

  // Setup APFEL++ x-space grids
  const apfel::Grid gpdf{{{60, 1e-4, 3}, {60, 1e-1, 3}, {50, 6e-1, 3}, {50, 8e-1, 3}}};
  const apfel::Grid gff{{{60, 1e-2, 3}, {50, 6e-1, 3}, {50, 8e-1, 3}}};

  // Rotate PDF set into the QCD evolution basis
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x, mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distff->xfxQ(x, mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated
  const auto EvolvedPDFs = [=,&gpdf] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(gpdf, RotPDFs, mu)};
  };
  const auto EvolvedFFs = [=,&gff] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(gff, RotFFs, mu)};
  };

  // Tabulate collinear PDFs and FFs
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, 0.5, distpdf->qMax(), 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabFFs{EvolvedFFs, 100, 0.5, distff->qMax(), 3, Thresholds};
  const auto CollFFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabFFs.Evaluate(mu); };

  // Initialize TMD objects
  const auto TmdObjPDF = apfel::InitializeTmdObjectsLite(gpdf, Thresholds);
  const auto TmdObjFF  = apfel::InitializeTmdObjectsLite(gff,  Thresholds);

  // Build evolved TMD PDFs and FFs
  const auto EvTMDPDFs = BuildTmdPDFs(TmdObjPDF, CollPDFs, AlphasPDF, PerturbativeOrder, 1);
  const auto EvTMDFFs  = BuildTmdPDFs(TmdObjFF,  CollFFs,  AlphasFF,  PerturbativeOrder, 1);

  //apfel::OgataQuadrature DEObj{0, 1e-9, 0.00001};
  apfel::DoubleExponentialQuadrature DEObj{};
  const int nf = apfel::NF(Q, Thresholds);
  const std::function<apfel::DoubleObject<apfel::Distribution>(double const&)> Lumib = [=] (double const& bs) -> apfel::DoubleObject<apfel::Distribution>
  {
    const std::map<int, apfel::Distribution> xF = QCDEvToPhys(EvTMDPDFs(bs, Q, Q * Q).GetObjects());
    const std::map<int, apfel::Distribution> xD = QCDEvToPhys(EvTMDFFs(bs, Q, Q * Q).GetObjects());
    apfel::DoubleObject<apfel::Distribution> L{};
    for (int i = 1; i <= nf; i++)
      {
        L.AddTerm({Bq(0)[i-1], xF.at(i), xD.at(i)});
        L.AddTerm({Bq(0)[i-1], xF.at(-i), xD.at(-i)});
      }
    return L;
  };
  const std::function<double(double const&)> bInt = [=] (double const& b) -> double
  {
    return 2 * M_PI * b * fNP->Evaluate(z, b, Q * Q, 1) * fNP->Evaluate(x, b, Q * Q, 0) * Lumib(NangaParbat::bstarmin(b, Q)).Evaluate(x, z) / z / z;
  };

  // Read in grid and convolute them
  NangaParbat::TMDGrid* TMD1 = NangaParbat::mkTMD(argv[1]);
  NangaParbat::TMDGrid* TMD2 = NangaParbat::mkTMD(argv[2]);
  const auto conv1 = Convolution(TMD1, TMD2, Bq, 1);
  const auto conv2 = Convolution(TMD1, TMD2, Bq, 0.9);
  const auto conv3 = Convolution(TMD1, TMD2, Bq, 0.8);
  const auto conv4 = Convolution(TMD1, TMD2, Bq, 0.7);
  const auto conv5 = Convolution(TMD1, TMD2, Bq, 0.6);
  const auto conv6 = Convolution(TMD1, TMD2, Bq, 0.5);

  // Values of qT
  const int nqT = 30;
  const double qTmin = Q * 1e-4;
  const double qTmax = 0.5 * Q;
  const double qTstp = ( qTmax - qTmin ) / ( nqT - 1 );
  std::vector<double> qTv;
  std::cout << std::scientific;
  for (double qT = qTmin; qT <= qTmax; qT += qTstp)
    std::cout << qT / Q << "\t" << DEObj.transform(bInt, qT) << "\t"
              << conv1(x, z, Q, qT) << "\t"
              << conv2(x, z, Q, qT) << "\t"
              << conv3(x, z, Q, qT) << "\t"
              << conv4(x, z, Q, qT) << "\t"
              << conv5(x, z, Q, qT) << "\t"
              << conv5(x, z, Q, qT) << "\t"
              << conv6(x, z, Q, qT) << "\t"
              << std::endl;

  delete TMD1;
  delete TMD2;
  return 0;
}
