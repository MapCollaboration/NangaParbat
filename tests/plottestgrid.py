import os
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt
from ruamel import yaml

# in order to import modules from a folder in path '../cli/'
sys.path.insert(1, '../cli/')         # insert at 1, 0 is the script path (or '' in REPL)
import modules.utilities as utilities
import modules.MatplotlibSettings     # this will override some of the settings of this script
                                      # in favor of the plot settings in the module MatplotlibSettings

"""
Usage:
python3 plottestgrid.py <folder> <distribution name> <distribution type (PDF/FF)>

<folder>             - output of NangaParbat/tests/GridProduction.cc
<distribution name>  - distribution name, string that goes in the plot title.
<distribution type>  - distribution type (PDF or FF), string that goes in the plot
                       title.
"""

# Parse arguments
parser = argparse.ArgumentParser(prog = "plottestgrid.py",
                                 usage = " \n python3 plottestgrid.py <folder> <distribution name> <distribution type (PDF/FF)> \n",
                                 description = "Script to plot the output of the grid test done with tests/GridPriduction.cc")

parser.add_argument('folder',            help = 'output folder of NangaParbat/tests/GridProduction.cc')
parser.add_argument('distribution name', help = 'string that goes in the plot title.')
parser.add_argument('distribution type', help = 'PDF or FF, string that goes in the plot title.')

# Print error if the required arguments are not given
try:
    options = parser.parse_args()
except:
    parser.print_help()
    sys.exit(0)

# Arguments
fold     = sys.argv[1]
distname = sys.argv[2]
distype  = sys.argv[3]

# Set folder
RunFolder = os.path.dirname(os.path.realpath(__file__))
Ofolder = fold + "/testresults"

testfiles = []
for tf in os.listdir(Ofolder):
    if tf[-4:] == "yaml":
        testfiles.append(tf)

for file in testfiles:
    # Read file to plot
    with open(Ofolder + "/" + file, "r") as test:
        toplot = yaml.load(test, Loader = yaml.RoundTripLoader)
        print("Loading output to plot: " + file)

    if (str(toplot["Grid over direct"][0])[-2:] != "an"):
        # Exstract data
        ifl = toplot["ifl"]
        Q   = toplot["Q"]
        x   = toplot["x"]
        kT  = toplot["kT"]

        tgrid    = toplot["Grid interpolation"]
        direct   = toplot["Direct calculation"]
        gridodir = toplot["Grid over direct"]

        # Plots
        fig, (ax1, ax2) = plt.subplots(nrows = 2, ncols = 1, figsize = (14, 8), sharex = "all", gridspec_kw = dict(width_ratios = [1], height_ratios = [4, 1]))
        plt.subplots_adjust(wspace = 0, hspace = 0)

        """
        wspace = 0.2  # the amount of width reserved for space between subplots,
                      # expressed as a fraction of the average axis width
        hspace = 0.2  # the amount of height reserved for space between subplots,
                      # expressed as a fraction of the average axis height
        """

        if distype == "FF" or distype == "ff":
            plt.suptitle("TMDGrids " +  distname + " " + distype + " flavour = " + str(ifl) + "\n" + "Q = " + str(Q) + "[GeV] , z = " + str(x))
        elif distype == "PDF" or distype == "pdf":
            plt.suptitle("TMDGrids " +  distname + " " + distype + " flavour = " + str(ifl) + "\n" + "Q = " + str(Q) + "[GeV] , x = " + str(x))

        # Define equally spaced bins and ticks for x axis
        nticks_x, majorticks, minorticks = utilities.BinsAndTicks(min(kT), max(kT))

        # ---  Upper plot ---

        # Labels
        if distype == "FF" or distype == "ff":
            ax1.set_xlabel(r"$p_{\perp}$ [GeV]")
            ax1.set_ylabel(r"$zD_1(z, p_{\perp}; Q^2)$")
        elif distype == "PDF" or distype == "pdf":
            ax1.set_xlabel(r"$k_T$ [GeV]")
            ax1.set_ylabel(r"$xf_1(x, k_T; Q^2)$")

        # Plot in log scale
        ax1.set_yscale("log")
        ax1.plot(kT, tgrid,  linewidth = 1.5, color = "r", alpha = 0.3, label = "grid interpolation")
        ax1.plot(kT, tgrid,  linewidth = 1.5, color = "r", alpha = 0.4, marker = 'o', markersize = 3)

        ax1.plot(kT, direct, linewidth = 1.5, color = "b", alpha = 0.3, label = "direct calculation")
        ax1.plot(kT, direct, linewidth = 1.5, color = "b", alpha = 0.4, marker = 'o', markersize = 3)

        ax1.axhline(0, linewidth = 0.8, color = "black")

        # Ticks
        ax1.set_xticks(majorticks)
        ax1.set_xticks(minorticks, minor=True)
        ax1.legend()

        # Start x axis from 0
        ax1.set_xlim(left = 0)

        # --- Lower plot ---

        # Labels
        if distype == "FF" or distype == "ff":
            ax2.set_xlabel(r"$p_{\perp}$ [GeV]")
        elif distype == "PDF" or distype == "pdf":
            ax2.set_xlabel(r"$k_T$ [GeV]")
        ax2.set_ylabel("Grid / Direct")

        # Plot
        ax2.plot(kT, gridodir,  linewidth = 1.5, color = "g", alpha = 0.3, label = "Grid / Direct")
        ax2.plot(kT, gridodir,  linewidth = 1.5, color = "g", alpha = 0.4, marker = 'o', markersize = 3)
        ax2.axhline(1, linewidth = 0.8, color = "black")

        # Ticks and settings
        ax2.set_xticks(majorticks)
        ax2.set_xticks(minorticks, minor=True)

        # Start x axis from 0
        ax2.set_xlim(left = 0)

        # Ticks for y axis
        # First tick starts at the multiple of 0.25 nearest to the minimum of the distribution
        ystart = round(min(gridodir), 2)
        start_yticks = np.floor(ystart / 0.25) * 0.25
        ax2.set_ylim(bottom = start_yticks, top = max(gridodir) + 0.1)

        nticks_y, majorticks_y, minorticks_y = utilities.BinsAndTicks(min(gridodir), max(gridodir))
        ax2.set_yticks(majorticks_y)
        ax2.set_yticks(minorticks_y, minor=True)

        ax2.legend()

        # Create directory for the plots if it does not exist
        plotspath = Ofolder + "/plots"
        try:
            os.mkdir(plotspath)
            print ("Creating '/plots' directory")
        except FileExistsError:
            pass

        # Save plot
        fig.savefig(plotspath + "/" + file[:-5] + ".pdf")
        plt.close()

print("Plots completed!")

"""
# Another way to have automatic ticks custom spaced
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)

# Make a plot with major ticks that are multiples of 20 and minor ticks that
# are multiples of 5.  Label major ticks with '%d' formatting but don't label
# minor ticks.
# '%d' formatting for integers, '%.2f' decimals.
ax1.xaxis.set_major_locator(MultipleLocator(10))
ax1.xaxis.set_major_formatter(FormatStrFormatter('%d'))

# For the minor ticks, use no labels; default NullFormatter.
ax1.xaxis.set_minor_locator(MultipleLocator(5))
"""
