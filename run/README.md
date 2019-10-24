# Utilities

This folder contains the utility codes to be used to access the main functionalities of the code. The available codes are
the following.

- **AvailableDataSets**: this code is run as follows:
```Shell
./AvailableDataSets <path to data folder>
```
and displays the available datasets in the target folder ```<path to data folder>```. The target folder has be to be filled in by using the ```Filter``` utility (see below) in such a way that the data files are in the appropriate format.


- **CreateTables**: this code produces interpolation tables and is run as follows:
```Shell
./CreateTables <configuration file> <path to data folder> <output folder> <test tables? [y/n]> [optional selected datasets]
```
where ```<configuration file>``` has to point a file that contains the necessary information to do the calculation (*e.g.* see [config.yaml](../cards/config.yaml)), ```<path to data folder>``` is the path to the processed data files, ```<output folder>``` points to the forlder where the interpolation tables will be placed, and ```<test tables? [y/n]>``` tells the code whether, at the end of the compuation, the interpolation tables have to be tested against the direct computation. Finally, it is possibile to select one or more data sets through ```[optional selected datasets]``` for which interpolation tables will be produced. If left empty, interpolation tables for all the data files in the target data folder will be produced.

- **DirectPredictions**: this code computes direct prediction (without using interpolation tables) and is run as follows:
```Shell
./DirectPredictions <configuration file> <path to data folder> <parametrisation [DWS, PV17, PV19]>
```
where ```<configuration file>``` has to point a file that contains the necessary information to do the calculation (*e.g.* see [config.yaml](../cards/config.yaml)), ```<path to data folder>``` is the path to the processed data files, and ```<parametrisation [DWS, PV17, PV19]>``` is the particular parameterisation to be used for the computation.

- **Filter**: this codes formats the raw data files in a way suitable for the code and is run as follows:
```Shell
./Filter <path to raw-data folder> <path to processed data>
```
where ```<path to raw-data folder>``` is the path to the raw data files and ```<path to processed data>``` is the path to the folder where the processed data files will be placed.

- **RunFit**: this code runs a fit and is run as follows:
```Shell
./RunFit <output dir> <fit configuration file> <path to data folder> <path to tables folder> <replica ID> <fluctuate initial parameters? [y/n] <calculate mean replica? [y/n]>
```
where ```<output dir>``` is the output directory, ```<configuration file>``` points to the fit configuration file (*e.g.* see [fitPV17.yaml](../cards/fitPV17.yaml), ```<path to data folder>``` is the path to the data files to be fitted , ```<path to tables folder> ```is the path to the corresponding interpolation tables to be used, and ```<replica ID>``` is the replica ID number (0 correcponds to central values). The last two options are booleans: ```<fluctuate initial parameters? [y/n]``` tells the code whether or not to fluctuate the starting parameters of each replica with a gaussian noise (according to what is written in ```src/minimisation/minimisation.cc```), while ```<calculate mean replica? [y/n]>``` tells the code whether or not to calculate the mean of the predictions of all the replicas. This last option uses ```src/parameterisation/meanreplica.cc```) and in order to work properly has to be chosen after a fit has already been performed.

- **PlotTMDs**: this code produces plot of TMD distributions in transverse-momentum space and is run as follows:
```Shell
./PlotTMDs <configuration file> <report file> <output folder>
```
