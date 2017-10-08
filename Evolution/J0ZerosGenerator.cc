//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include <iostream>
#include <boost/math/special_functions/bessel.hpp>

using namespace std;

int main()
{
  const int perline = 4;
  const int lines   = 250;
  const int n       = perline * lines - 1;

  cout << setprecision(16);
  cout << "  const vector<double> j0Zeros{";
  for (int i = 1; i <= n; i++)
    {
      cout << boost::math::cyl_bessel_j_zero(0., i) << ", ";
      if (i % perline == 0)
	cout << endl << "      ";
    }
  cout << boost::math::cyl_bessel_j_zero(0., n+1) << "};" << endl;

  return 0;
}

