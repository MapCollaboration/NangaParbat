![alt text](https://github.com/vbertone/NangaParbat/raw/master/doc/NangaParbatPanoramic.png
 "Nanga Parbat")

# Nanga Parbat: a TMD fitting framework

Nanga Parbat is a fitting framework aimed at the determination of the
non-perturbative component of the TMD distributions.

## Download

You can obtain NangaParbat directly from the github repository:

https://github.com/vbertone/NangaParbat/releases

For the last development branch you can clone the master code:

```Shell
git clone git@github.com:vbertone/NangaParbat.git
```

If you instead want to download a specific tag:

```Shell
git tag -l
git checkout tags/tag_name
```
## Dependencies

In order to install the code a number of external but relatively standard libraries are required. Here is the list:
- [``yaml-cpp``](https://github.com/jbeder/yaml-cpp),
- [``eigen3``](https://eigen.tuxfamily.org/dox/),
- [``ceres-solver``](http://ceres-solver.org),
- [``GSL``](https://www.gnu.org/software/gsl/doc/html/),
- [``ROOT``](https://root.cern.ch) with ``Minuit2``,
- [``LHAPDF6``](https://lhapdf.hepforge.org),
- [``APFEL++``](https://github.com/vbertone/apfelxx).

Most of these libraries can be installed through standard package managers such as [``Homerew``](https://brew.sh) on MacOS and ``apt-get`` on Linux.

## Installation 

The code can be compiled using the following procedure:

```Shell
cd NangaParbat
cmake -DCMAKE_INSTALL_PREFIX=/your/installation/path/ .
make && make install
```
By the default, if no prefix specification is given, the program will
be installed in the /usr/local folder. If you want (or need) to use a
different path, remember to export the NangaParbat /lib folder into the
LD_LIBRARY_PATH. More configuration options can be accessed by typing:

```Shell
ccmake .
```

## Running the code

Despite the core of the code is written in ``C++``, the main functionalities can be accessed through the [command-line-interface](doc/CommandLineInterface.md) utilities. If the installation was successful, it is possible to run a fit of TMD PDFs just by typing from the main folder:
```Shell
python3 cli/fit.py
```
and following the instructions. Any such fits relie on the dataset, the interpolation tables, and the TMD parameterisations currently present in the code. It is however possible to generate new interpolation tables using the ``cli/tables.py`` utility that gives the possibility change the theory settings (perturbative order, collinear PDF set, etc.). Including more parameterisations and new experimental datasets is also possible but requires some additional work on the core of the code. Feel free to contact us should you want to extend the code in this respect.

Once the fit is complete (including a number of Monte Carlo replicas), it is possible to create a summary report of the fit by running ``cli/report.py``. This will create a document (in markdown and html format) that collects the main statistical features of the fit, histograms, data-theory comparison plots, and TMD plots.

## Documentation

Some general documentation can be found at the following links:

- [command line interface](doc/CommandLineInterface.md)
- [raw data files](rawdata/)
- [preprocessed data files](data/)
- [utilities](run/)
- [convolution prefactors](doc/ConvTablesPrefactors.md)

Code documentation generated with Doxygen can be found [here](https://vbertone.github.io/NangaParbat/html/index.html).

## Public results

Some of our results can be found at the following links:

- [N3LL fit](https://vbertone.github.io/NangaParbat/results/PV19/N3LL/index.html)
- [NNLL' fit](https://vbertone.github.io/NangaParbat/results/PV19/NNLLp/index.html)

The reports above have been generated using the CLI ``cli/report.py``.

## References


## Contacts

- Valerio Bertone: valerio.bertone@cern.ch
- Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
