import os
import numpy as np
import matplotlib.pyplot as plt
from ruamel import yaml

import modules.bcolours as bcolours
from modules.bcolours import *


class fitresults:
    """
    The purpose of this class is to analise the results of the fit and to make plots.
    Each object (self) of this class has 4 arguments:
        outfolder      ---  String, is the folder where the output of the fit is stored.
                            Must contain the folder of the replicas:
                            ('replica_0',..., 'replica_n')
        goodreplicas   ---  Array of strings, contains the names of the replicas that
                            converged. All the replicas whose name is in the array will be
                            plotted.
        pdffolder      ---  String, name of the folder where to save the plot in pdf.
        pngfolder      ---  String, name of the folder where to save the plot in png.
    """

    def __init__(self, outfolder, goodreplicas, pdffolder, pngfolder):
        self.outfolder    = outfolder
        self.goodreplicas = goodreplicas
        self.pdffolder    = pdffolder
        self.pngfolder    = pngfolder

    def GlobalChi2(self):
        """
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        Returns an array whose elements are the global chisquares, one from each experiment considered.
        """
        # Chi2 array
        globalchi2 = [0 for i in range(len(self.goodreplicas))]

        for iter, grp in enumerate(self.goodreplicas):
            with open(self.outfolder + "/" + grp + "/Report.yaml", "r") as stream:
                singlereportinfo = yaml.load(stream, Loader=yaml.RoundTripLoader)

                # Fill chi2 array
                gc2 = singlereportinfo["Global chi2"]
                globalchi2[iter] = gc2

        return globalchi2


    def Rep0Chi2(self):
        """
        Function to get chi2 of the central replica.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        Returns a the chi2 of the replica0 as a string.
        """
        with open(self.outfolder + "/" + "replica_0" + "/Report.yaml", "r") as rep0:
            singlereportinforep0 = yaml.load(rep0, Loader=yaml.RoundTripLoader)
            rep0chi2 = singlereportinforep0["Global chi2"]

        return rep0chi2


    def RepMinChi2(self, replicamin):
        """
        Function to get chi2 of the central replica.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        Returns a string.

        replicamin   --- String. Name of the folder of the replica with minimum chi2.
        """
        with open(self.outfolder + "/" + replicamin + "/Report.yaml", "r") as repmin:
            reportrepmin = yaml.load(repmin, Loader=yaml.RoundTripLoader)
            repminchi2   = reportrepmin["Global chi2"]

        return repminchi2


    def Rep0Parameters(self, parameter):
        """
        Function to get the value of the final parameters of the central replica.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        Returns a string.

        parameter   --- String, name of the parameter to get.
        """
        with open(self.outfolder + "/" + "replica_0" + "/Report.yaml", "r") as rep0:
            singlereportinforep0 = yaml.load(rep0, Loader=yaml.RoundTripLoader)
            rep0par = singlereportinforep0["Parameters"][parameter]

        return rep0par

    def RepMinParameters(self, replicamin, parameter):
        """
        Function to get the value of the final parameters of the central replica.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        Returns a string.

        replicamin  ---  String. Name of the folder of the replica with minimum chi2.
        parameter   ---  String, name of the parameter to get.
        """
        with open(self.outfolder + "/" + replicamin + "/Report.yaml", "r") as repmin:
            reportrepmin = yaml.load(repmin, Loader = yaml.RoundTripLoader)
            repminpar = reportrepmin["Parameters"][parameter]

        return repminpar


    def GlobalErrorFunction(self):
        """
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        Returns an array whose elements are the global error functions, one from each experiment considered.
        """
        # Global error function array
        globalerrorfunc = [0 for i in range(len(self.goodreplicas))]

        for iter, grp in enumerate(self.goodreplicas):
            with open(self.outfolder + "/" + grp + "/Report.yaml", "r") as stream:
                singlereportinfo = yaml.load(stream, Loader=yaml.RoundTripLoader)

                # Fill global error function array
                gef = singlereportinfo["Global error function"]
                globalerrorfunc[iter] = gef

        return globalerrorfunc

    def PlotGlobalErrFunc(self):
        """
        Plots the histogram of the global errror function distribution.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        """

        # Define equally spaced bins and ticks
        nbins, majorticks, minorticks = self.BinsAndTicks(min(self.GlobalErrorFunction()), max(self.GlobalErrorFunction()))

        # Global Error function histogram
        fig = plt.figure()
        ax0 = fig.add_subplot(1, 1, 1)
        ax0.hist(self.GlobalErrorFunction(), bins = nbins, facecolor = bcolours.celestial, alpha = 1)

        # Set ticks and labels
        ax0.set_xticks(majorticks)
        ax0.set_xticks(minorticks, minor = True)
        ax0.set_xlabel("Values")
        ax0.set_ylabel("Global error function")
        ax0.set_title("Global error function distribution")

        # Save histogram
        histopdf = self.pdffolder + "/GlobalErrorFunction.pdf"
        fig.savefig(histopdf)
        histopng = self.pngfolder + "/GlobalErrorFunction.png"
        fig.savefig(histopng)
        plt.close()

        print(bcolours.ACTREPORT + "Creating Global Error Function histogram: '" + histopdf + bcolours.ENDC)


    def PlotGlobalChi2(self):
        """
        Plots the histogram of the global chi2 distribution, with the mean chisquare
        and the Rep0 chisquare.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).
        """
        # Get mean of the distribution without the chi2 of the central replica
        chi2woRep0 = self.GlobalChi2()
        if self.Rep0Chi2() in chi2woRep0:
            chi2woRep0.remove(self.Rep0Chi2())
        else:
            print(bcolours.WARNING + "Chi2 of replica0 not found in GlobalChi2() \n " + bcolours.ENDC)
        meanchi2 = np.mean(chi2woRep0)

        # Define equally spaced bins and ticks
        nbins, majorticks, minorticks = self.BinsAndTicks(min(self.GlobalChi2()), max(self.GlobalChi2()))

        # Global chi2 histogram
        fig = plt.figure()
        ax0 = fig.add_subplot(1, 1, 1)
        ax0.hist(self.GlobalChi2(), bins = nbins, facecolor = bcolours.tangerineyellow, alpha=1)

        # Plot mean and rep0 chisquare
        ax0.axvline(meanchi2,color = bcolours.borgogna, label = "Mean $\chi^2$ without $\chi^2_0$: " + str(round(meanchi2,3)))
        ax0.axvline(self.Rep0Chi2(),color = bcolours.meadow, label = "replica_0   $\chi^2$: " + str(round(self.Rep0Chi2(),3)))

        # Set ticks and labels
        ax0.legend()
        ax0.set_xticks(majorticks)
        ax0.set_xticks(minorticks, minor = True)
        # ax0.grid(which = 'both', linestyle = "dashdot")
        ax0.set_xlabel("Values")
        ax0.set_ylabel("$\chi^2$")
        ax0.set_title("$\chi^2$ distribution")

        # Save histogram
        histopdf = self.pdffolder + "/Globalchi2.pdf"
        fig.savefig(histopdf)
        histopng = self.pngfolder + "/Globalchi2.png"
        fig.savefig(histopng)
        plt.close()

        print(bcolours.ACTREPORT + "Creating Global Chi2 histogram: '" + histopdf + "' " + bcolours.ENDC)


    def PlotCutGlobalChi2(self, cut, replicamin):
        """
        Plots the histogram of the global chi2 distribution, with the mean chisquare
        and the Rep0 chisquare.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).

        cut         --- Float: where to cut the histogram, maximum value plotted.
        replicamin  --- String. Replica with the minimum chisquare, will be plotted ad a
                        vertical line.
        """
        # Get mean of the distribution without the chi2 of the central replica
        chi2woRep0 = self.GlobalChi2()
        if self.Rep0Chi2() in chi2woRep0:
            chi2woRep0.remove(self.Rep0Chi2())
        else:
            print(bcolours.WARNING + "Chi2 of replica0 not found in GlobalChi2() \n " + bcolours.ENDC)
        meanchi2 = np.mean(chi2woRep0)

        # Cut chi2 - !! remove the chi2 above the cut from GlobalChi2() from now on in this function.
        for elm in self.GlobalChi2():
            if elm > cut:
                self.GlobalChi2().remove(elm)

        # Define equally spaced bins and ticks
        nbins, majorticks, minorticks = self.BinsAndTicks(min(self.GlobalChi2()), cut)

        # Histogram
        fig = plt.figure()
        ax0 = fig.add_subplot(1, 1, 1)
        ax0.hist(self.GlobalChi2(), bins = nbins, facecolor = bcolours.tangerineyellow, alpha=1)

        # Plot mean, rep0 and replicamin's chisquare
        ax0.axvline(self.Rep0Chi2(), color = bcolours.meadow, label = "replica_0   $\chi^2$: " + str(round(self.Rep0Chi2(),3)))
        ax0.axvline(self.RepMinChi2(replicamin), color = bcolours.celestial, label = replicamin + " : " + str(round(self.RepMinChi2(replicamin),3)))
        if meanchi2 < cut:
            ax0.axvline(meanchi2, color = bcolours.borgogna, label = "Mean $\chi^2$ without $\chi^2_0$: " + str(round(meanchi2,3)))

        # Set ticks and labels
        ax0.legend()
        ax0.set_xticks(majorticks)
        ax0.set_xticks(minorticks, minor = True)
        # ax0.grid(which = 'both', linestyle = "dashdot")
        ax0.set_xlabel("Values")
        ax0.set_ylabel("$\chi^2$")
        ax0.set_title("$\chi^2$ distribution cut at: " + str(cut))

        # Save histogram
        histopdf = self.pdffolder + "/CutGlobalchi2.pdf"
        fig.savefig(histopdf)
        histopng = self.pngfolder + "/CutGlobalchi2.png"
        fig.savefig(histopng)
        plt.close()

        print(bcolours.ACTREPORT + "Creating Global Chi2 histogram cut at: " + str(cut) + ", '" + histopdf + "'\n " + bcolours.ENDC)


    def FinalParameters(self, parameter):
        """
        Returns an array whose elements are values of the chosen parameter, one from each experiment considered.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).

        parameter  ---  String, name of the parameter.
        """
        paramarray = [0 for i in range(len(self.goodreplicas))]

        for iter, grp in enumerate(self.goodreplicas):
            with open(self.outfolder + "/" + grp + "/Report.yaml", "r") as stream:
                singlereportinfo = yaml.load(stream, Loader=yaml.RoundTripLoader)

                # Fill array for the chosen parameter
                val = singlereportinfo["Parameters"][parameter]
                paramarray[iter] = val

        return paramarray


    def HistoParameter(self, parameter, replicamin):
        """
        Plots the histogram of the distribution of the parameter.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).

        parameter   ---  String, name of the parameter to plot in the histogram.
        replicamin  ---  String, name of the replica with the minimum chisquare.
        """
        FinParam = self.FinalParameters(parameter)

        # Remove outliers with conditions
        outliers = []
        for elem in FinParam:
            condition = 1000
            if elem > condition:
                FinParam.remove(elem)
                outliers.append(elem)
                print(bcolours.WARNING + "\nThere is an element over: " + str(condition) + " for " + parameter +". "+ bcolours.ENDC)
                print(bcolours.WARNING + "The element " + parameter + " = " + str(elem) + " will not be plotted. \n" + bcolours.ENDC)

        # print(self.FinalParameters(parameter))

        # Get mean of the distribution with and without outliers
        meanparam   = np.mean(self.FinalParameters(parameter))
        meanwoparam = np.mean(FinParam)

        # Define equally spaced bins and ticks
        nbins, majorticks, minorticks = self.BinsAndTicks(min(FinParam), max(FinParam))

        # Parameter histogram
        fig = plt.figure()
        ax0 = fig.add_subplot(1, 1, 1)
        ax0.hist(FinParam, bins = nbins, facecolor = bcolours.tangerineyellow, alpha = 0.8)

        # Plot mean, rep0 a minor replica value of the parameter
        ax0.axvline(self.Rep0Parameters(parameter), color = bcolours.meadow, label = "replica_0: " + str(round(self.Rep0Parameters(parameter), 3)))
        # Plot also the minimum replica's value if the min replica is not the central one
        if replicamin != "replica_0":
            ax0.axvline(self.RepMinParameters(replicamin, parameter), color = bcolours.celestial, label = replicamin + ": " + str(round(self.RepMinParameters(replicamin, parameter), 3)))
        if meanparam < max(FinParam):
            ax0.axvline(meanparam, color = bcolours.borgogna, label = "Mean: " + str(round(meanparam, 3)))
        else:
            ax0.axvline(meanwoparam, color = bcolours.borgogna, label = "Mean without outliers: " + str(round(meanwoparam, 3)))

        # If there are outliers put them in the text in the plot
        if len(outliers) != 0:
            for ol in outliers:
                ax0.text(0.10, 0.75, parameter + " = " + str(ol) + " not in the plot", transform = ax0.transAxes)

        # Set ticks and labels
        ax0.legend(prop={'size': 10})
        ax0.set_xticks(majorticks)
        ax0.set_xticks(minorticks, minor = True)
        # ax0.grid(which = 'both', linestyle = "dashdot")
        ax0.set_xlabel("Values")
        ax0.set_ylabel("Count")
        ax0.set_title(parameter + " distribution")

        # Remove "\" from name of parameter for the name of the plot
        parstring = parameter.translate({ord('\\'): None})

        # Save histogram
        histopdf = self.pdffolder + "/" + parstring + ".pdf"
        fig.savefig(histopdf)
        histopng = self.pngfolder + "/" + parstring + ".png"
        fig.savefig(histopng)
        plt.close()

        print(bcolours.ACTREPORT + "Creating histogram for the parameter: '" + parameter + "'" + bcolours.ENDC)


    def LogHistoParameter(self, parameter, replicamin):
        """
        Plots the histogram of the distribution of the parameter in logarithmic scale.
        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).

        parameter   ---  String, name of the parameter to plot in the histogram.
        replicamin  ---  String, name of the replica with the minimum chisquare.
        """
        # Get mean of the distribution
        meanparam = np.mean(self.FinalParameters(parameter))

        # Keep all elements > 0
        LogParameter = list(filter(lambda x: x > 0, self.FinalParameters(parameter)))
        # print(LogParameter)

        # Use non-equal bin sizes, such that they look equal on log scale.
        logbins = np.logspace(np.log10(min(LogParameter)), np.log10(max(LogParameter)), num = 50)#.tolist()

        # Histogram on log scale.
        fig = plt.figure()
        ax1 = fig.add_subplot(1, 1, 1)
        ax1.hist(LogParameter, bins = logbins, facecolor = bcolours.tangerineyellow, alpha = 0.8)
        # ax1.hist(self.FinalParameters(parameter), bins = logbins, facecolor = bcolours.tangerineyellow, alpha = 0.8)
        ax1.set_xticks(logbins, minor = True)
        ax1.set_xscale('log')

        # Plot mean, rep0 a minor replica value of the parameter
        ax1.axvline(meanparam, color = bcolours.borgogna, label = "Mean: " + str(round(meanparam,3)))
        ax1.axvline(self.Rep0Parameters(parameter), color = bcolours.meadow, label = "replica_0: " + str(round(self.Rep0Parameters(parameter),3)))
        if self.RepMinParameters(replicamin, parameter) > 0.0:
            ax1.axvline(self.RepMinParameters(replicamin, parameter), color = bcolours.celestial, label = replicamin + ": " + str(round(self.RepMinParameters(replicamin, parameter), 3)))
        else:
            ax1.axvline(1e-5, color = bcolours.celestial, label = replicamin + ": " + str(round(self.RepMinParameters(replicamin, parameter), 3)))

        ax1.legend(prop={'size': 10})
        ax1.set_xlabel("Values")
        ax1.set_ylabel("Count")
        ax1.set_title(parameter + " log distribution")

        # Remove "\" from name of parmeter for the name of the plot
        parstring = parameter.translate({ord('\\'): None})

        # Save histogram
        histopdf = self.pdffolder + "/Log_" + parstring + ".pdf"
        fig.savefig(histopdf)
        histopng = self.pngfolder + "/Log_" + parstring + ".png"
        fig.savefig(histopng)
        plt.close()

        print(bcolours.ACTREPORT + "Creating logarithmic histogram for the parameter: '" + parameter + "'" + bcolours.ENDC)

    def PlotExpsResults(self, replicamin):
        """
        Function to create plots from the result of the fit. It creates a pair of plots
        for each experiment, in the same figure: the plot of the replicas with the experimental
        data and the plot with histograms of the chisquare and the partial error function.

        Self is an element of the class fitresults(outfolder, goodreplicas, pdffolder, pngfolder).

        replicamin  --- String. Name of the replica with the minimum chisquare. This replica will have the label
                        in the plot.
        """
        print(bcolours.ACTREPORT + "\nCreating plots for each experiment in '" + self.pdffolder + "'" + bcolours.ENDC)
        print(bcolours.ACTREPORT + "Creating plots for each experiment in '" + self.pngfolder + "' \n" + bcolours.ENDC)

        with open(self.outfolder + "/" + "replica_0" + "/Report.yaml", "r") as rep0:
            singlereportinforep0 = yaml.load(rep0, Loader=yaml.RoundTripLoader)
            expkeys = [[] for n in range(len(singlereportinforep0["Experiments"]))]

            # Get the name of the experiments from replica_0
            for t, expdata in enumerate(singlereportinforep0["Experiments"]):
                expkeys[t] = expdata["Name"]

        for ek in range(len(expkeys)):
            partialerrfunc = []
            partialchi2 = []

            # Initialise (multi) plot
            fig, (ax1, ax2) = plt.subplots(nrows=1, ncols=2, figsize = (14, 7))
            # fig, (ax1, ax2) = plt.subplots(nrows=1, ncols=2, figsize=(10, 6))

            """ for three plots: one principal (bigger) and two smaller ones
            below the principal one:

            gridsize = (3, 2)
            fig = plt.figure(figsize=(12, 8))
            princplot = plt.subplot2grid(gridsize, (0, 0), colspan=2, rowspan=2)
            histo1 = plt.subplot2grid(gridsize, (2, 0))
            histo2 = plt.subplot2grid(gridsize, (2, 1))
            """
            for iter1, grp in enumerate(self.goodreplicas):
                with open(self.outfolder + "/" + grp + "/Report.yaml", "r") as stream:
                    singlereportinfo = yaml.load(stream, Loader=yaml.RoundTripLoader)

                    for expdata in singlereportinfo["Experiments"]:
                        if expdata["Name"] == expkeys[ek]:

                            # Gather information to plot
                            expname = expdata["Name"]

                            plottitle = expdata["Plot title python"]
                            xlabel = expdata["xlabelpy"]
                            ylabel = expdata["ylabelpy"]

                            perrfunc = expdata["partial error function"]
                            partialerrfunc.append(perrfunc)

                            pchi2 = expdata["partial chi2"]
                            partialchi2.append(pchi2)

                            qT = expdata["qT"]

                            predictions = expdata["Predictions"]
                            centralval = expdata["Central values"]
                            fluctudata = expdata["Fluctuated data"]
                            uncunc = expdata["Uncorrelated uncertainties"]
                            systshifts = expdata["Systematic shifts"]

                            # Obtain shifted predictions
                            shiftedpredictions = [sum(x) for x in zip(predictions, systshifts)]

                            # Plot all replicas, replica 0 and the minimumChi2 one with labels
                            if   grp == 'replica_0':
                                ax1.plot(qT, shiftedpredictions, label = grp, color = 'k')
                            elif grp == replicamin:
                                ax1.plot(qT, shiftedpredictions, label = grp)
                            else:
                                ax1.plot(qT, shiftedpredictions, linewidth = 0.5)

            # Plot data with experimental errors
            ax1.errorbar(qT, centralval, yerr = uncunc, color = "black", linestyle = "None", label = "data", marker = 'o', markersize = 2.5, capsize = 3, linewidth = 1)

            # Set title and labels
            fig.suptitle(plottitle)
            ax1.set_xlabel(xlabel)
            ax1.set_ylabel(ylabel)
            ax1.legend(prop={'size': 10})
            ax1.set_title("shifted predictions")

            # Define equally spaced bins and ticks for the histogram
            nbins, majorticks, minorticks = self.BinsAndTicks(min(partialchi2), max(partialchi2))

            """ useful info:
            For two histograms in one frame, one for the partial chi2 and the other for the partial error
            function distribution.:
                nbins = np.arange(start = startbin - 0.5, stop = max(max(partialchi2), max(partialerrfunc)) + 0.5, step = 0.25).tolist()
                ax2.hist([partialchi2,partialerrfunc], bins = nbins, histtype='bar', color= [bcolours.tangerineyellow, bcolours.celestial], label =["Partial $\chi^2$","Partial error function"])


            To (NOT) normalise the histogram (REMOVE) put density = 1  in ax2.hist().
            When more sets of data are plotted, each of them is normalised separately in the
            histogram (checked).


            If we want to check separately the partial chi2 and the partial error function distribution:
            for three plots: one principal (bigger) and two smaller ones:

            gridsize = (3, 2)
            fig = plt.figure(figsize=(12, 8))
            princplot = plt.subplot2grid(gridsize, (0, 0), colspan=2, rowspan=2)
            histo1 = plt.subplot2grid(gridsize, (2, 0))
            histo2 = plt.subplot2grid(gridsize, (2, 1))
            gif, (ax3, ax4) = plt.subplots(nrows=1, ncols=2, figsize=(10, 6))
            ax3.hist(partialchi2 , bins = nbins, histtype='bar', density =1, color= bcolours.tangerineyellow, label =["Partial $\chi^2$"])
            ax4.hist(partialerrfunc , bins = nbins, histtype='bar', density =1, color= bcolours.celestial, label =["Partial error function"])

            plotpdf_sep = pdffolder + "/" + expname + "_sep.pdf"
            plotpng_sep = pngfolder + "/" + expname + "_sep.png"
            gif.savefig(plotpng_sep)
            gif.savefig(plotpdf_sep)
            """
            # Plot histogram
            ax2.hist(partialchi2, bins = nbins, histtype='bar', color = bcolours.tangerineyellow, label =["Partial $\chi^2$"])

            # Set labels and ticks
            ax2.set_xticks(majorticks)
            ax2.set_xticks(minorticks, minor = True)
            ax2.set_xlabel("Values")
            ax2.set_ylabel("Count")
            ax2.legend(prop={'size': 9})

            # Save plot
            plotpdf = self.pdffolder + "/" + expname + ".pdf"
            fig.savefig(plotpdf)
            plotpng = self.pngfolder + "/" + expname + ".png"
            fig.savefig(plotpng)

            plt.close()

        print(bcolours.ACTREPORT + "All plots created! \n" + bcolours.ENDC)

    def BinsAndTicks(self, _min, _max):
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
        elif range >= 100 and range < 1000:
            nbins      = np.arange(start = round(startbin, 1) - 1, stop = round(_max, 1) + 1, step = 2.5).tolist()
            majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 20).tolist()
            minorticks = np.arange(start = round(startbin, 1) - 1, stop = round(_max, 1) + 1, step = 5).tolist()
        elif range >= 1000:
            nbins      = np.arange(start = round(startbin, 1) - 1, stop = round(_max, 1) + 1, step = 5).tolist()
            majorticks = np.arange(start = nbins[0], stop = nbins[-1], step = 50).tolist()
            minorticks = np.arange(start = round(startbin, 1) - 1, stop = round(_max, 1) + 1, step = 25).tolist()

        return nbins, majorticks, minorticks
