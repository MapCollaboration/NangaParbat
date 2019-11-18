# Utilities

This folder contains the utility codes to be used to access the main functionalities of the code. The available codes are
the following.

- **AvailableDataSets**: this code is run as follows:
```Shell
./AvailableDataSets <path to data folder>
```
and displays the available datasets in the target folder ```<path to data folder>```. The target folder has be to be filled in by using the ```Filter``` utility (see below) in such a way that the data files are in the appropriate format.

- **AvailableParameterisations**: this code is run as follows:
```Shell
./AvailableParameterisations [python]
```
and displays the available parameterisations that can be used in a TMD fit along with a brief description. The optional string ```python``` produces an output that is more easily readable by the python command line interface.

- **AvailableBstar**: this code is run as follows:
```Shell
./AvailableBstar [python]
```
and displays the available b* presciptions available that can be used for the production of interpolation tables. The optional string ```python``` produces an output that is more easily readable by the python command line interface.

- **CreateTables**: this code produces interpolation tables and is run as follows:
```Shell
./CreateTables <configuration file> <path to data folder> <output folder> <test tables? [y/n]> [optional selected datasets]
```
where ```<configuration file>``` has to point a file that contains the necessary information to do the calculation (*e.g.* see [config.yaml](../cards/config.yaml)), ```<path to data folder>``` is the path to the processed data files, ```<output folder>``` points to the forlder where the interpolation tables will be placed, and ```<test tables? [y/n]>``` tells the code whether, at the end of the compuation, the interpolation tables have to be tested against the direct computation. Finally, it is possibile to select one or more data sets through ```[optional selected datasets]``` for which interpolation tables will be produced. If left empty, interpolation tables for all the data files in the target data folder will be produced.

- **DirectPredictions**: this code computes direct prediction (without using interpolation tables) and is run as follows:
```Shell
./DirectPredictions <configuration file> <path to data folder> <parametrisation [DWS, PV17, PV19x, ...]>
```
where ```<configuration file>``` has to point a file that contains the necessary information to do the calculation (*e.g.* see [config.yaml](../cards/config.yaml)), ```<path to data folder>``` is the path to the processed data files, and ```<parametrisation [DWS, PV17, PV19]>``` is the particular parameterisation to be used for the computation.

- **Filter**: this codes formats the raw data files in a way suitable for the code and is run as follows:
```Shell
./Filter <path to raw-data folder> <path to processed data>
```
where ```<path to raw-data folder>``` is the path to the raw data files and ```<path to processed data>``` is the path to the folder where the processed data files will be placed.

- **RunFit**: this code runs a fit and is run as follows:
```Shell
./RunFit <output dir> <fit configuration file> <path to data folder> <path to tables folder> <replica ID>
```
where ```<output dir>``` is the output directory, ```<configuration file>``` points to the fit configuration file (*e.g.* see [fitPV17.yaml](../cards/fitPV17.yaml)), ```<path to data folder>``` is the path to the data files to be fitted , ```<path to tables folder> ```is the path to the corresponding interpolation tables to be used, and ```<replica ID>``` is the replica ID number (0 correcponds to central values).

- **ComputeMeanReplica**: this code computes the mean replica, i.e. the average over some Monte Carlo replicas, and produces a report:
```Shell
./ComputeMeanReplica <output dir> <fit configuration file> <path to data folder> <path to tables folder> [optional replicas to be discarded]
```
as above, ```<output dir>``` is the output directory, ```<configuration file>``` points to the fit configuration file, ```<path to data folder>``` is the path to the data files to be fitted , and ```<path to tables folder> ```is the path to the corresponding interpolation tables to be used. In addition, it is possible to provide a list of replicas that have to be discarded when computing the average.

- **PlotTMDs**: this code produces plot of TMD distributions in transverse-momentum space and is run as follows:
```Shell
./PlotTMDs <configuration file> <output file> <pdf/ff> <flavour ID> <Scale in GeV> <value of x> <parameters file>
```
where ```<configuration file>``` has to point a file that contains the necessary information to do the calculation (*e.g.* see [config.yaml](../cards/config.yaml)), ```<output file>```is the output file, ```<pdf/ff>``` to plot either a TMDF PDF or a TMD FF, ```<flavour ID>``` is the flavour ID according to the LHAPDF nomenclature, ```<Scale in GeV>``` is the values of the final scale in GeV,  ```<value of x>``` is the value of Bjorken ```x```, and ```<parameters file>``` is the file containing the relevant information about the parameterisation and the sets of parameters to be used. For example:
```Shell
Parameterisation: "PV19"
Parameters: [[0.015552259, 3.0373071, 21.251885, 5.6171274, 0, 0.81410783, 0.81823693, 64.628302, 4.0249303, 0, 0, 0.1, 0.017413234, 2], [0.015552259, 3.0373071, 21.251885, 5.6171274, 0, 0.81410783, 0.81823693, 64.628302, 4.0249303, 0, 0, 0.1, 0.017413234, 2]]
```
This will result in two sets of predictions, one for each set of parameters. The code produces a file in the ```YAML``` format reporting the relevant kinematics and the predictions for a fixed set of values of ```qT``` in GeV of ```x``` time the TMD distribution.
