//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Stefano Carrazza: stefano.carrazza@cern.ch
//

// APFEL++
#include <apfel/apfelxx.h>

// YAML
#include <yaml-cpp/yaml.h>

// Minuit
#include <ROOT/Minuit2/Minuit2Minimizer.h>
#include <ROOT/Minuit2/FCNBase.h>
#include <ROOT/Minuit2/MnMigrad.h>
#include <ROOT/Minuit2/MnMachinePrecision.h>
#include <ROOT/Minuit2/MnUserParameters.h>
#include <ROOT/Minuit2/FunctionMinimum.h>
#include <ROOT/Minuit2/MnPrint.h>
#include <ROOT/Minuit2/MnHesse.h>

// Standard libs
#include <cmath>
#include <map>
#include <iomanip>

//using namespace apfel;
using namespace std;

class Quad4F: public ROOT::Minuit2::FCNBase
{
public:
  Quad4F() {}

  ~Quad4F() {}

  double operator()(const std::vector<double>& par) const
  {
    double x = par[0];
    double y = par[1];
    double z = par[2];
    double w = par[3];

    //return ( (1./70.)*(21*x*x + 20*y*y + 19*z*z - 14*x*z - 20*y*z) + w*w );
    return x*x + y*y + z*z + w*w;
  }

  double Up() const {return 1.;}
};

int main()
{
  Quad4F fcn;

  //test constructor
  ROOT::Minuit2::MnUserParameters upar;
  upar.Add("x", 1., 0.1);
  upar.Add("y", 1., 0.1);
  upar.Add("z", 1., 0.1);
  upar.Add("w", 1., 0.1);

  ROOT::Minuit2::MnMigrad migrad(fcn, upar);
  ROOT::Minuit2::FunctionMinimum min = migrad();
  cout << "minimum: " << min << endl;

  return 0;
}

