//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/direxists.h"

#include <sys/stat.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  bool dir_exists(std::string const& dir)
  {
    struct stat buffer;
    if (stat(dir.c_str(), &buffer) == 0)
      return true;
    else
      return false;
  }
}
