//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/factories.h"
#include "NangaParbat/numtostring.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  TMDGrid* mkTMD(std::string const& name, int const& mem)
  {
    std::cout << "[NangaParbat]: loading " << name + "/" + name + "_" + num_to_string(mem) + ".yaml" << std::endl;
    return new NangaParbat::TMDGrid{YAML::LoadFile(name + "/" + name + ".info"),
                                    YAML::LoadFile(name + "/" + name + "_" + num_to_string(mem) + ".yaml")};
  }

  //_________________________________________________________________________________
  std::vector<TMDGrid*> mkTMDs(std::string const& name)
  {
    const YAML::Node info = YAML::LoadFile(name + "/" + name + ".info");
    const int nmem = info["NumMembers"].as<int>();
    std::vector<TMDGrid*> tmds(nmem);
    for (int mem = 0; mem < nmem; mem++)
      tmds[mem] = new NangaParbat::TMDGrid{info, YAML::LoadFile(name + "/" + name + std::to_string(mem) + ".yaml")};
    return tmds;
  }

  //_________________________________________________________________________________
  std::function<double(double const&, double const&, double const&, double const&)> Convolution(TMDGrid                                           const* TMD1,
                                                                                                TMDGrid                                           const* TMD2,
                                                                                                std::function<std::vector<double>(double const&)> const& Charges,
                                                                                                double                                            const& IntEps)
  {
    return [=] (double const& x1, double const& x2, double const& Q, double const& qT) -> double
    {
      const std::vector<double> Bq = Charges(Q);
      apfel::Integrator integrandKT{
        [=] (double const& kT) -> double
        {
          apfel::Integrator integrandTheta{
            [=] (double const& theta) -> double
            {
              const std::map<int, double> d1 = TMD1->Evaluate(x1, kT, Q);
              const std::map<int, double> d2 = TMD2->Evaluate(x2, sqrt( pow(kT, 2) + pow(qT, 2) - 2 * kT * qT * cos(theta) ), Q);
              double lumi = 0;
              for (int i = 1; i <= 5; i++)
                lumi += Bq[i-1] * ( d1.at(i) * d2.at(-i) + d1.at(-i) * d2.at(i) );
              return lumi;
            }
          };
          return kT * integrandTheta.integrate(0, 2 * M_PI, IntEps);
        }
      };
      return integrandKT.integrate(0, Q, IntEps);
    };
  }

  //_________________________________________________________________________________
  std::function<double(double const&, double const&, double const&, double const&)> Convolution(TMDGrid                                           const* TMD,
                                                                                                std::function<std::vector<double>(double const&)> const& Charges,
                                                                                                double                                            const& IntEps)
  {
    return Convolution(TMD, TMD, Charges, IntEps);
  }
}
