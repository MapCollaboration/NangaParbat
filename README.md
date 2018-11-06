![alt text](https://github.com/vbertone/TMDs/raw/master/doc/NangaParbatPanoramic.jpg
 "Nanga Parbat")

# Nanga Parbat: to the top of TMDs

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

## Documetation

Code documentation generated with Doxygen can be found here:
https://vbertone.github.io/NangaParbat/html/index.html.

## Relevant references


## Contact Information

- Valerio Bertone: valerio.bertone@cern.ch
