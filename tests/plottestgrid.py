import os
import numpy as np
import matplotlib.pyplot as plt
from ruamel import yaml

# in order to import modules from a folder in path '../cli/'
import sys
sys.path.insert(1, '../cli/') # insert at 1, 0 is the script path (or '' in REPL)
import modules.utilities as utilities


# Set folder
RunFolder = os.path.dirname(os.path.realpath(__file__))
# fol = sys.argv
Ofolder = "TestGrid_PV17FF_NLL/testresults"

testfiles = []
for tf in os.listdir(Ofolder):
    if tf[-4:] == "yaml":
        testfiles.append(tf)

for file in testfiles:
    # Read file to plot
    with open(Ofolder + "/" + file, "r") as test:
        toplot = yaml.load(test, Loader = yaml.RoundTripLoader)
        print("Loading output to plot: " + file)

    if (str(toplot["GridoverDirect"][0])[-2:] != "an"):
        # Exstract data
        ifl = toplot["ifl"]
        Q   = toplot["Q"]
        x   = toplot["x"]
        kT  = toplot["kT"]

        tgrid = toplot["Grid interpolation"]
        direct = toplot["Direct calculation"]
        gridodir = toplot["GridoverDirect"]

        # Plots
        fig, (ax1, ax2) = plt.subplots(nrows = 2, ncols = 1, figsize = (10, 6))

        plt.suptitle("TMDGrids PV19 test - " + "flavour = " + str(ifl) + "\n" + "Q = " + str(Q) + " , x = " + str(x))

        # Define equally spaced bins and ticks for x axis
        nticks_x, majorticks, minorticks = utilities.BinsAndTicks(min(kT), max(kT))

        # Upper plot
        ax1.set_xlabel("kT")
        ax1.set_ylabel(r"$xf(x, k_T, Q)$")

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

        # Lower plot
        ax2.set_xlabel("kT")
        ax2.set_ylabel("Grid / Direct")

        ax2.plot(kT, gridodir,  linewidth = 1.5, color = "g", alpha = 0.3, label = "Grid / Direct")
        ax2.plot(kT, gridodir,  linewidth = 1.5, color = "g", alpha = 0.4, marker = 'o', markersize = 3)
        ax2.axhline(1, linewidth = 0.8, color = "black")

        # Ticks and settings y axis
        ax2.set_xticks(majorticks)
        ax2.set_xticks(minorticks, minor=True)

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
# Way to have automatic ticks custom spaced
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
