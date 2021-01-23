//
// Author: Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#include "NangaParbat/tostringwprecision.h"


namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string to_string_with_precision(const double a_value, const int n)
  {
      std::ostringstream out;
      out.precision(n);
      out << std::fixed << a_value;
      return out.str();
  }
}
