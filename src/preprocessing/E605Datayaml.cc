/*
 Author: Chiara Bissolotti
*/

#include "yaml-cpp/yaml.h"
#include <math.h>

// to print to an output file
#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <apfel/apfelxx.h>

int main()
{

  // Reading dataprelim.yaml which contains the list of data files to be produced
  const YAML::Node dataprelim = YAML::LoadFile("DataTables/dataprelim.yaml");

  for (auto const& exp : dataprelim)
    {
      for (auto const& ds : exp.second)
        {
          const std::string dataprelimfile = "/Users/ChiaraBisso/PhD/DrYFruIT/DataTables/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
          // Loading Data File
          YAML::Node datafile = YAML::LoadFile(dataprelimfile);

          // Reading and editing the data file
          for (auto var : datafile["dependent_variables"])
            {
              for (auto vs : var["values"])
                {
                  double unc = 0;
                  double add = 0;
                  for (auto err : vs["errors"])
                    {
                      if (err["label"].as<std::string>() == "add")
                        add = err["value"].as<double>() * vs["value"].as<double>();
                      if (err["label"].as<std::string>() == "unc")
                        unc = err["value"].as<double>();
                      const double unc_new = sqrt( pow(unc, 2) + pow(add, 2)); // sum in quadrature of the uncorrelated errors

                      for (auto err : vs["errors"])
                        {
                          if (err["label"].as<std::string>() == "unc")
                            err["value"] = unc_new; // editing value
                        }
                      vs["errors"].remove(2); // removing the residual line labeled 'add', which is always the third item
                    }
                }
            }

          // printing output on file
          std::ofstream newdatafile("/Users/ChiaraBisso/PhD/DrYFruIT/DataTables/" + exp.first.as<std::string>() + "/" + ds["name"].as<std::string>() + ".yaml", std::ios::out);
          newdatafile << datafile << std::endl;
          newdatafile.close();

          // on terminal (just to check)
          //std::cout << datafile << std::endl;
        }
    }
  return 0;

}

/*
// ---------------     to edit a line in a .yaml file    -----------------------

 YAML::Node basenode = YAML::LoadFile("/Users/ChiaraBisso/PhD/DrYFruIT/DataTables/E605try.yaml"); // not declared const because this is going to be changed

 //label
  YAML::Emitter orig;
  orig << basenode["dependent_variables"][0]["values"][1]["errors"][2]["label"];
  std::cout << "\n" << "Here's the orig result:\n" << orig.c_str() << std::endl;

  YAML::Node node; // starts out as a null
   node["keylabel"] = "unc"; // define the map with the new label I want to put into the other YAML::Node

  YAML::Emitter change;
  basenode["dependent_variables"][0]["values"][1]["errors"][2]["label"] = node["keylabel"]; // editing one of the data nodes
  change << basenode["dependent_variables"][0]["values"][1]["errors"][2]["label"]; // dumping it back
  std::cout << "\n" << "Here's the changed result:\n" << change.c_str() << std::endl;

 // value
  YAML::Emitter onum;
  onum << basenode ["dependent_variables"][0]["values"][1]["errors"][2]["value"];
  std::cout << "\n" << "Here's the onum result:\n" << onum.c_str() << std::endl;

  node["keyvalue"] = 9999;

  YAML::Emitter cnum;
  basenode["dependent_variables"][0]["values"][1]["errors"][2]["value"] = node["keyvalue"]; // editing one of the data nodes
  cnum << basenode["dependent_variables"][0]["values"][1]["errors"][2]["value"]; // dumping it back
  std::cout << "\n" << "Here's the changed num result:\n" << cnum.c_str() << std::endl;

 //changed total line
  YAML::Emitter total;
  total << basenode["dependent_variables"][0]["values"][1]["errors"];
  std::cout << "\n" << "Here's the changed total result:\n" << total.c_str() << std::endl;
*/
