![alt text](https://github.com/vbertone/NangaParbat/raw/master/doc/NangaParbatPanoramic.png
 "Nanga Parbat")

# Nanga Parbat: a TMD fitting framework

Nanga Parbat is a fitting framework aimed at the determination of the
non-perturbative component of TMD distributions.

## Download

You can obtain NangaParbat directly from the github repository:

https://github.com/MapCollaboration/NangaParbat

For the last development branch you can clone the master code:

```Shell
git clone git@github.com:MapCollaboration/NangaParbat.git
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

Most of these libraries can be installed through standard package managers such as [``Homebrew``](https://brew.sh) on MacOS and ``apt-get`` on Linux.

NangaParbat also has a __lite version__, that does not require all the dependencies listed above. The mandatory dependencies are ``yaml-cpp``, ``eigen3``, ``LHAPDF6``, ``APFEL++``. 

During the installation, NangaParbat detects if one or more libraries among ``GSL``, ``ROOT`` or ``ceres-solver`` are missing and installs and compiles only the part of the code that is possible to run.


## Installation 

The code can be compiled using the following procedure:

```Shell
cd NangaParbat
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/your/installation/path/ ..
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
and following the instructions. Any such fit relies on the dataset, the interpolation tables, and the TMD parameterisations currently present in the code. It is however possible to generate new interpolation tables using the ``cli/tables.py`` utility that gives the possibility change the theory settings (perturbative order, collinear PDF set, etc.). Including more parameterisations and new experimental datasets is also possible but requires some additional work on the core of the code. Feel free to contact us should you want to extend the code in this respect.

Once the fit is complete (including a number of Monte Carlo replicas), it is possible to create a summary report of the fit by running ``cli/report.py``. This will create a document (in markdown and html format) that collects the main statistical features of the fit, histograms, data-theory comparison plots, and TMD plots.

## Documentation

Some further general documentation can be found at the following links:

- [command line interface](doc/CommandLineInterface.md)
- [utilities](run/)
- [raw data files](rawdata/)
- [preprocessed data files](data/)
- [convolution prefactors](doc/ConvTablesPrefactors.md)

Code documentation generated with Doxygen can be found [here](https://vbertone.github.io/NangaParbat/html/index.html).

## Public results

The reports linked below have been generated using the CLI ``cli/report.py``.

### PV19 fit

Fit of the TMD PDFs of the proton to Drell-Yan data as published in [[JHEP 07 (2020) 117](https://arxiv.org/pdf/1912.07550.pdf)]:

- fit at [N3LL](https://vbertone.github.io/NangaParbat/results/PV19/N3LL/index.html),
- fit at [NNLL'](https://vbertone.github.io/NangaParbat/results/PV19/NNLLp/index.html),
- fit at [NNLL](https://vbertone.github.io/NangaParbat/results/PV19/NNLL/index.html),
- fit at [NLL'](https://vbertone.github.io/NangaParbat/results/PV19/NLLp/index.html).

### MAPTMD22 fit

Simultaneous fit of the TMD PDFs of the proton and of the TMD FFs of ligh hadrons to Drell-Yan and SIDIS data as published in [[JHEP 10 (2022) 127](https://arxiv.org/pdf/2206.07598.pdf)]:

- fit at [N3LL](https://vbertone.github.io/NangaParbat/results/MAPTMD22/N3LL/index.html).
- fit at [N3LL](FitResults/MAP22_N3LL/Report/Report.html).

### MAPTMD22Pion fit

Fit of the TMD PDFs of the pion to Drell-Yan data as published in [[Phys.Rev.D 107 (2023) 1, 014014](https://arxiv.org/pdf/2210.01733.pdf)]:

- fit at [N3LL](https://vbertone.github.io/NangaParbat/results/MAPTMD22Pion/N3LL/index.html).

## TMD grids

TMD and structure functions grids compatible with the NangaParbat specifications are made
available through the [TMDlib](https://syncandshare.desy.de/index.php/s/GjjcwKQC93M979e?path=%2FTMD%20grid%20files) library.
Grids of the TMD PDFs and FFs, and the SIDIS F_UUT structure functions from the PV17 fit can also be found [here](https://drive.google.com/drive/folders/1cXHZKS0OmY7woUBR2zw_Nf6RmAQYimjl?usp=sharing).

## Use of TMD grids

In ``tools/`` there are some test codes that can be run by the user in
order to interpolate the TMD and structure function grids provided at
the link above. This part of NangaParbat is compiled also in the lite
version.

The interpolation of the grids can be done with
``TMDGridInterpolation.cc`` for TMDs and with
``StructGridInterpolation.cc`` for structure functions, while
``GridsConvolution.cc`` does the convolution between a TMD PDF grid
and a TMD FF grid. The input files, where the user can choose the
kinematical points for the interpolation and the convolution, are in
``tools/inputs/``.

## References

- *Extraction of Pion Transverse Momentum Distributions from Drell-Yan data*; Matteo Cerutti, Lorenzo Rossi, Simone Venturini, Alessandro Bacchetta, Valerio Bertone, Chiara Bissolotti, and Marco Radici [[Phys.Rev.D 107 (2023) 1, 014014](https://arxiv.org/pdf/2210.01733.pdf)].
- *Unpolarized transverse momentum distributions from a global fit of Drell-Yan and semi-inclusive deep-inelastic scattering data*; Alessandro Bacchetta, Valerio Bertone, Chiara Bissolotti, Giuseppe Bozzi, Matteo Cerutti, Fulvio Piacenza, Marco Radici, Andrea Signori [[JHEP 10 (2022) 127](https://arxiv.org/pdf/2206.07598.pdf)].
- *Transverse-momentum-dependent parton distributions up to N3LL from Drell-Yan data*; Alessandro Bacchetta, Valerio Bertone, Chiara Bissolotti, Giuseppe Bozzi, Filippo Delcarro, Fulvio Piacenza, Marco Radici [[JHEP 07 (2020) 117](https://arxiv.org/pdf/1912.07550.pdf)].

## Contacts

- Valerio Bertone: valerio.bertone@cern.ch
- Alessandro Bacchetta: alessandro.bacchetta@unipv.it
- Chiara Bissolotti: cbissolotti@anl.gov
- Matteo Cerutti: matteo.cerutti@pv.infn.it
- Lorenzo Rossi: lorenzo.rossi@pv.infn.it

## Credits

NangaParbat has been developed with the support of the European
Research Council (ERC) under the European Union's Horizon 2020
research and innovation program (grant agreement No. 647981, 3DSPIN).

<img src="resources/3DSPIN_ERC_logo.png" alt="3DSPIN log" height="200"/>
