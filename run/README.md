# Utilities

This folder contains the utility codes to be used for the production
of the interpolation tables and for the fits. The available codes are
the following.

- **AvailableDataSets**: this codes is run as follows:
```Shell
./AvailableDataSets <path to data folder>
```
and displays the available datasets in the target folder ```<path to data folder>```.

- **CreateTables**: this codes is run as follows:
```Shell
./CreateTables <configuration file> <path to data folder> <output folder> <test tables? [y/n]> [optional selected datasets]
```

- **DirectPredictions**:
 this codes is run as follows:
```Shell
./DirectPredictions <configuration file> <path to data folder> <parametrisation [DWS, PV17, PV19]>
```

- **Filter**:
 this codes is run as follows:
```Shell
./Filter <path to raw-data folder> <path to processed data>
```

- **RunFit**: this codes is run as follows:
```Shell
./RunFit <fit configuration file> <path to data folder> <path to tables folder>
```
