# Command Line Interface (CLI)

Io order to facilitate the usage of the code, we provide frontend command-line interfaces that help the user access the main functionalities.

## Produce interpolation tables
The pyhton program ``tables.py`` produces fast interpolation tables according to the parameters set by the user.

## Prepare and run a fit
The python program ``fit.py`` prepares and runs a fit. The results of the fit will be put in a new folder created by ``fit.py`` itself with a name chosen from the user. 
Answering the questions asked by the command line interface the user can choose: 
- the experiments to include in the fit (among the avaliable ones),
- the perturbative level to which the calculations in the fit will be carried (and consequently the convolution tables associated with it), 
- the minimiser to use (``none`` gives only predictions, and the other two avaliable choices are ``minuit`` and ``ceres``), 
- the random-number seed for the generation of the Monte-Carlo replicas, 
- the maximum value ``qT / Q`` allowed in the fit, 
- the cut on the value of the error function (used for the report), 
- if to use or not the ``t0 prescription`` and with which parameters, 
- the parameterisation for the non-perturbative function (among those that are avaliable) and the initial parameters, 
- if to fluctuate or not the initial parameters, 
- the number of Monte-Carlo replicas.

## Produce a report of a fit
The pyhton program ``report.py`` produces a report starting form the output folder of the fit. 
 
