//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/utilities.h"
#include "NangaParbat/nonpertfunctions.h"

#include <fstream>
#include <cstring>
#include <algorithm>
#include <apfel/timer.h>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 4 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./PlotTMDs <configuration file> <report file> <output folder>\n" << std::endl;
      exit(-10);
    }

  // Read configuration file
  const YAML::Node config = YAML::LoadFile(argv[1]);

  // Read report
  const YAML::Node report = YAML::LoadFile(argv[2]);

  return 0;
}
