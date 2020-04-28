import numpy as np
import matplotlib.pyplot as plt
from ruamel import yaml
from scipy.special import loggamma
from modules.bcolours import *


def GetPertOrd(pertord):
    """
    Transforms the number of the perturbative order in the relative string.
    Input and output are string.
    If the input is not a string GetPertOrd() tries to convert it into the
    right format.
    """
    # Check that 'pertord' is a string, if not try to convert it.
    if type(pertord) is not str:
        print(bcolours.WARNING + "TypeError: the argument of GetPertOrd must be a string." + bcolours.ENDC)
        print(bcolours.WARNING + "Trying to convert it to a string." + bcolours.ENDC)
        pertord = str(pertord)

    # Check if the conversion succeded
    try:
        str(pertord)
    except:
        print(bcolours.FAIL + "Conversion failed. " + bcolours.ENDC)

    # Define the transition from number to name of the perturbative order
    stringord = ""
    if pertord == "1":
      stringord = "NLL"
    if pertord == "2":
      stringord = "NNLL"
    if pertord == "3":
      stringord = "N3LL"
    if pertord == "-1":
      stringord = "NLLp"
    if pertord == "-2":
      stringord = "NNLLp"
    return stringord


def BinsAndTicks(_min, _max):
    """
    Define equally spaced bins and ticks for a distribution.
    Returns the division in bins (nbins), the position of the major and minor ticks (majorticks and minorticks).
    Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).

    _min  --- Float (or int). Minimum to plot.
    _max  --- Float (or int). Maximum to plot.
    """
    # Get the range for the x axis
    range = _max - _min

    # First bin starts at the multiple of 0.5 nearest to the minimum of the distribution
    start = round(_min, 2)
    startbin = np.floor(start / 0.5) * 0.5

    if  range <=  0.5:
        nbins      = np.arange(start = startbin - 0.1, stop = round(_max, 2) + 0.1, step = 0.01).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 0.05).tolist()
        minorticks = nbins
    elif range > 0.5 and range < 1:
        nbins      = np.arange(start = startbin - 0.5, stop = round(_max, 2) + 0.5, step = 0.1).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 0.2).tolist()
        minorticks = nbins
    elif range >= 1 and range < 3:
        nbins      = np.arange(start = startbin - 0.5, stop = round(_max, 2) + 0.5, step = 0.1).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 0.5).tolist()
        minorticks = nbins
    elif range >= 3 and range < 7:
        nbins      = np.arange(start = round(startbin, 1) - 0.5, stop = round(_max, 1) + 0.5, step = 0.1).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 0.5).tolist()
        minorticks = nbins
    elif range >= 7 and range < 25:
        nbins      = np.arange(start = round(startbin, 1) - 0.5, stop = round(_max, 1) + 0.5, step = 0.25).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 1).tolist()
        minorticks = np.arange(start = round(startbin, 1) - 0.5, stop = round(_max, 1) + 0.5, step = 0.5).tolist()
    elif range >= 25 and range < 50:
        nbins      = np.arange(start = round(startbin, 1) - 0.5, stop = round(_max, 1) + 0.5, step = 0.5).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 5).tolist()
        minorticks = np.arange(start = round(startbin, 1) - 0.5, stop = round(_max, 1) + 0.5, step = 1).tolist()
    elif range >= 50 and range < 100:
        nbins      = np.arange(start = round(startbin, 1) - 1, stop = round(_max, 1) + 1, step = 1).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 10).tolist()
        minorticks = np.arange(start = round(startbin, 1) - 1, stop = round(_max, 1) + 1, step = 5).tolist()
    elif range >= 100 and range < 500:
        nbins      = np.arange(start = np.floor((round(startbin, 1))/ 5) * 5, stop = round(_max, 1), step = 2.5).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 20).tolist()
        minorticks = np.arange(start = round(startbin, 1) - 5, stop = round(_max, 1) + 1, step = 5).tolist()
    elif range >= 500 and range < 1000:
        nbins      = np.arange(start = np.floor((round(startbin, 1))/ 5) * 5, stop = round(_max, 1), step = 5).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 50).tolist()
        minorticks = np.arange(start = round(startbin, 1) - 5, stop = round(_max, 1) + 1, step = 10).tolist()
    elif range >= 1000:
        nbins      = np.arange(start = np.floor((round(startbin, 1))/ 5) * 5, stop = round(_max, 1), step = 25).tolist()
        majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 50).tolist()
        minorticks = np.arange(start = round(startbin, 1) - 5, stop = round(_max, 1) + 1, step = 25).tolist()

    return nbins, majorticks, minorticks


def FindOutliers(a, perc, n):
    """
    This function gets the list 'a' as an input, finds average and standard
    deviation within a given (symmetric) percentile, and identifies the
    index of the elements that are beyond 'n' standard deviations away
    from the mean value.
    """

    # if the percentile is less than zero or more that 50 exit
    if perc < 0 or perc >= 50:
        raise ValueError("Percentile out of range")

    # Transform list into a numpy array
    a = np.array(a)

    # Trim the input array removing the tails
    b = a[(a < np.percentile(a, 100 - perc, interpolation = "nearest")) & (a > np.percentile(a, perc, interpolation = "nearest"))]

    # Compute averange and standard deviation of the trimmed array
    av = np.mean(b)
    sd = np.std(b)

    # Now collect outliers' index
    outliers = []
    for i in range(len(a)):
        if a[i] < av - n * sd or a[i] > av + n * sd:
            outliers.append(i)

    return outliers


def PlotScan(path):
    with open(path + "/ParameterScan.yaml", "r") as stream:
        ps = yaml.load(stream, Loader = yaml.RoundTripLoader)

    # Plot
    for p in ps["Parameters scan"]:
        # Set title and labels
        plt.xlabel(p["name"])
        plt.ylabel("Error function")

        # Plot the starting point separately from the points obtained whith the scan
        plt.plot(p["parameter value"][1:], p["fcn value"][1:], label = "Scan", color = bcolours.answerblue)
        plt.plot(p["parameter value"][0], p["fcn value"][0], label = "starting value", marker = 'o', color = bcolours.borgogna)
        plt.legend()

        # Save plot
        plt.savefig(path + "/" + p["name"] + ".pdf")
        plt.close()


def chi2dist(k, x):
    """
    chi2 distribution for 'k' degrees of freedom rearranged to avoid
    overflow problem for large values of 'k'.
    """
    x = np.array(x, dtype = np.float128)
    return np.exp( - k / 2 * np.log(2) + ( k / 2 - 1 ) * np.log(x) - x / 2 - loggamma(k/2))
