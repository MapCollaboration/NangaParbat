//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/listdir.h"

#include <dirent.h>
#include <vector>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::vector<std::string> list_dir(std::string const& path)
  {
    struct dirent *entry;
    DIR *dir = opendir(path.c_str());

    if (dir == NULL)
      return {};

    std::vector<std::string> dirlist;
    while ((entry = readdir(dir)) != NULL)
      dirlist.push_back(entry->d_name);

    closedir(dir);
    return dirlist;
  }
}
