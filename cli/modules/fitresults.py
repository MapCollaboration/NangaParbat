import os
import numpy as np
import matplotlib.pyplot as plt
import modules.bcolours as bcolours
import modules.writemarkdown as writemarkdown
import modules.utilities as utilities

from ruamel import yaml
from statistics import mean
from matplotlib.pyplot import cm
from modules.bcolours import *

class fitresults:
    """
    The purpose of this class is to analise the results of the fit and to make plots.
    Each object (self) of this class has 4 arguments:
        reports      ---  Array of reports in yaml format of the replicas that
                          converged.
        report0      ---  Report in yaml format of the central replica.
        report_mean  ---  Report in yaml format of the mean replica.
        reportfolder ---  String, name of the folder where to place the report.
        mdout        ---  File of the report in markdown format
    """

    def __init__(self, reports, report0, report_mean, reportfolder, mdout):
        with open(reportfolder + "/../fitconfig.yaml", "r") as fc:
            fitconfig = yaml.load(fc, Loader = yaml.RoundTripLoader)
        self.reports      = reports
        self.report0      = report0
        self.report_mean  = report_mean
        self.reportfolder = reportfolder
        self.pdffolder    = reportfolder + "/plots/"
        self.pngfolder    = reportfolder + "/pngplots/"
        self.mdout        = mdout
        self.chi2s        = [rep["Global chi2"] for rep in self.reports]
        self.Efcns        = [rep["Global error function"] for rep in self.reports]
        self.parameters   = dict(zip(self.report0["Parameters"].keys(), [[r["Parameters"][p] for r in self.reports] for p in self.report0["Parameters"].keys()]))
        self.fixed        = dict(zip(self.report0["Parameters"].keys(), [p["fix"] for p in fitconfig["Parameters"]]))


    def StatisticalEstimators(self):
        """
        Writes some relevant statistical estimatos
        """
        self.mdout.write("$N_{rep}$ = " + str(len(self.reports)) + "  \n")
        self.mdout.write("$\chi_{0}^2$ = " + str(round(self.report0["Global chi2"], 4)) + "  \n")
        self.mdout.write("$\chi_{mean}^2$ = " + str(round(self.report_mean["Global chi2"], 4)) + "  \n")
        self.mdout.write(r"$\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = " + str(round(np.mean(self.chi2s), 4)) + " $\pm$ " + str(round(np.std(self.chi2s), 4)) + "  \n")
        self.mdout.write(r"$\langle E \rangle \pm \sigma_{E}$ = " + str(round(np.mean(self.Efcns), 4)) + " $\pm$ " + str(round(np.std(self.Efcns), 4)) + "  \n")
        self.mdout.write("\n")


    def ProcessParameters(self):
        """
        Print the tables with the fitted parameters
        """
        headings = ["Parameter", "Central replica", "Average over replicas", "Fixed"]
        par = [(name, self.report0["Parameters"][name], str(round(np.mean(val), 8)) + " $\pm$ "+ str(round(np.std(val), 8)),
                self.fixed[name]) for name, val in self.parameters.items()]
        writemarkdown.table(self.mdout, par, headings)


    def PlotCorrelationMatrix(self):
        """
        Plots the correlation matrix over the available replicas of the fitted parameters.
        """
        # Gather parameters for all replicas
        parameters = dict(zip(self.report0["Parameters"].keys(), [[r["Parameters"][p] for r in self.reports] for p in self.report0["Parameters"].keys()]))

        # Compute correlation matrix
        corr = np.corrcoef(list(parameters.values()))

        # Convert nan's due to fixed parameters to 0
        corr[np.isnan(corr)] = 0

        # Now set the diagonal to one
        np.fill_diagonal(corr, 1)

        # Plot covariance matrix
        fig, ax = plt.subplots()
        im = ax.imshow(corr, vmin = -1, vmax = 1, cmap=cm.coolwarm)
        labels = list(self.report0["Parameters"].keys())
        ax.set_xticks(np.arange(len(labels)))
        ax.set_yticks(np.arange(len(labels)))
        ax.set_xticklabels(labels)
        ax.set_yticklabels(labels)
        cbar = fig.colorbar(im, ticks=[-1, -0.5, 0, 0.5, 1])
        cbar.ax.set_yticklabels(["-1", "-0.5", "0", "0.5", "1"])
        ax.set_title("Correlation matrix")
        fig.tight_layout()
        plt.savefig(self.pdffolder + "CorrelationMatrix.pdf")
        plt.savefig(self.pngfolder + "CorrelationMatrix.png")
        plt.close()

        # Include plot in the report
        writemarkdown.mdincludefig(self.mdout, "pngplots/CorrelationMatrix.png", "Fitted parameter correlation matrix")


    def PlotGlobalErrFunc(self):
        """
        Plots the histogram of the global errror function distribution.
        """
        # Define equally spaced bins and ticks
        #nbins, majorticks, minorticks = utilities.BinsAndTicks(min(self.Efcns), max(self.Efcns))

        # Global Error function histogram
        fig = plt.figure()
        ax0 = fig.add_subplot(1, 1, 1)
        #ax0.hist(self.Efcns, bins = nbins, facecolor = bcolours.celestial, alpha = 1, label = "E")
        ax0.hist(self.Efcns, bins = 20, facecolor = bcolours.celestial, alpha = 1, label = "E")
        ax0.legend()

        # Set ticks and labels
        #ax0.set_xticks(majorticks)
        #ax0.set_xticks(minorticks, minor = True)
        ax0.set_xlabel("$E$")
        ax0.set_ylabel("Counts")
        ax0.set_title("Global error function distribution")

        # Save histogram
        fig.savefig(self.pdffolder + "/GlobalErrorFunction.pdf")
        fig.savefig(self.pngfolder + "/GlobalErrorFunction.png")
        plt.close()

        # Include plot in the report
        writemarkdown.mdincludefig(self.mdout, "pngplots/GlobalErrorFunction.png", "Global error function distribution")


    def PlotGlobalChi2(self):
        """
        Plots the histogram of the global chi2 distribution.
        """
        # Define equally spaced bins and ticks
        #nbins, majorticks, minorticks = utilities.BinsAndTicks(min(self.chi2s), max(self.chi2s))

        # Global chi2 histogram
        fig = plt.figure()
        ax0 = fig.add_subplot(1, 1, 1)
        #ax0.hist(self.chi2s, bins = nbins, facecolor = bcolours.tangerineyellow, alpha = 1, label = "$\chi^2$")
        ax0.hist(self.chi2s, bins = 20, facecolor = bcolours.tangerineyellow, alpha = 1, label = "$\chi^2$")
        ax0.legend()

        # Set ticks and labels
        #ax0.set_xticks(majorticks)
        #ax0.set_xticks(minorticks, minor = True)
        # ax0.grid(which = 'both', linestyle = "dashdot")
        ax0.set_ylabel("Counts")
        ax0.set_xlabel("$\chi^2$")
        ax0.set_title("Global $\chi^2$ distribution")

        # Save histogram
        fig.savefig(self.pdffolder + "/Globalchi2.pdf")
        fig.savefig(self.pngfolder + "/Globalchi2.png")
        plt.close()

        # Include plot in the report
        writemarkdown.mdincludefig(self.mdout, "pngplots/Globalchi2.png", "Global $\chi^2$ distribution")


    def HistoParameters(self):
        """
        Plots the histogram of the distribution of the parameters.
        """
        i = 0
        for pk in self.parameters:
            p = self.parameters[pk]

            # Define equally spaced bins and ticks
            #nbins, majorticks, minorticks = utilities.BinsAndTicks(min(p), max(p))

            # Parameter histogram
            fig = plt.figure()
            ax0 = fig.add_subplot(1, 1, 1)
            #ax0.hist(p, bins = nbins, facecolor = bcolours.tangerineyellow, alpha = 0.8, label = pk)
            ax0.hist(p, bins = 20, facecolor = bcolours.meadow, alpha = 0.8, label = pk)
            ax0.legend()

            # Set ticks and labels
            #ax0.set_xticks(majorticks)
            #ax0.set_xticks(minorticks, minor = True)
            # ax0.grid(which = 'both', linestyle = "dashdot")
            ax0.set_xlabel(pk)
            ax0.set_ylabel("Counts")
            ax0.set_title(pk + " distribution")

            # Save histogram
            fig.savefig(self.pdffolder + "/param" + str(i) + ".pdf")
            fig.savefig(self.pngfolder + "/param" + str(i) + ".png")
            plt.close()

            # Include plot in the report
            writemarkdown.mdincludefig(self.mdout, "pngplots/param" + str(i) + ".png", pk + " distribution")
            i += 1


    def Chi2Table(self):
        """
        Prints the tables with the breakdown of the single experiments computed
        with: central replica, mean replica and as averages over replicas.
        """
        headings = ["Experiment", "Number of points", "$\chi_{D}^2$", "$\chi_{\lambda}^2$", "$\chi^2$"]

        # Total number of points
        ntot = 0
        for e in self.report0["Experiments"]:
            ntot += len(e["qT"])

        # Central replica
        self.mdout.write("Central-replica $\chi^2$'s:\n")
        par = [(e["Name"], len(e["qT"]), round(e["partial chi2"] - e["penalty chi2"], 4), round(e["penalty chi2"], 4), round(e["partial chi2"], 4))
                for e in self.report0["Experiments"]]
        par.append(("Total", ntot, "-", "-", round(self.report0["Global chi2"], 4)))
        writemarkdown.table(self.mdout, par, headings)

        # Mean replica
        self.mdout.write("Mean-replica $\chi^2$'s:\n")
        par = [(e["Name"], len(e["qT"]), round(e["partial chi2"] - e["penalty chi2"], 4), round(e["penalty chi2"], 4), round(e["partial chi2"], 4))
                for e in self.report_mean["Experiments"]]
        par.append(("Total", ntot, "-", "-", round(self.report_mean["Global chi2"], 4)))
        writemarkdown.table(self.mdout, par, headings)

        # Average over replicas
        self.mdout.write("Average-over-replicas $\chi^2$'s:\n")
        par = []
        for e in self.report0["Experiments"]:
            c2 = []
            c2p = []
            c2d = []
            for r in self.reports:
                # Select experiment
                for exp in r["Experiments"]:
                    if exp["Name"] == e["Name"]:
                        break
                c2.append(exp["partial chi2"])
                c2p.append(exp["penalty chi2"])
                c2d.append(exp["partial chi2"] - exp["penalty chi2"])
            par.append((e["Name"], len(e["qT"]),
                        str(round(np.mean(c2d), 4)) + " $\pm$ " + str(round(np.std(c2d), 4)),
                        str(round(np.mean(c2p), 4)) + " $\pm$ " + str(round(np.std(c2p), 4)),
                        str(round(np.mean(c2),  4)) + " $\pm$ " + str(round(np.std(c2),  4))))
        par.append(("Total", ntot, "-", "-", str(round(np.mean(self.chi2s), 4)) + " $\pm$ " + str(round(np.std(self.chi2s),  4))))
        writemarkdown.table(self.mdout, par, headings)


    def PlotTMDs(self, dist, ifl, Q, x):
        """
        Function that creates plots of TMD distributions, replica bly replica using the code ./run/PlotsTMDs
        """
        # First of of the code creates the input file containg
        # parameterisation and sets of parameters
        param = {"Parameterisation": self.report0["Parameterisation"]}
        pars = [val for name, val in self.parameters.items()]
        tpars = {"Parameters": [list(row) for row in zip(*pars)]}
        with open(self.reportfolder + "/Parameters.yaml", "w") as ofile:
            yaml.dump(param, ofile, Dumper = yaml.RoundTripDumper)
            yaml.dump(tpars, ofile, Dumper = yaml.RoundTripDumper)

        # Now the code ./run/PlotsTMDs is run with the appropriate input
        print(bcolours.ACTREPORT + "Producing TMD plots...\n" + bcolours.ENDC)
        os.system(self.reportfolder + "/../../run/PlotTMDs " + self.reportfolder + "/../tables/config.yaml "
                  + self.reportfolder + "/tmds.yaml " + dist + " " + str(ifl) + " " + str(Q) + " " + str(x)
                  + " " + self.reportfolder +"/Parameters.yaml")

        # Finally the plot is produced and included in the report
        with open(self.reportfolder +"/tmds.yaml", "r") as fc:
            tmds = yaml.load(fc, Loader = yaml.RoundTripLoader)

        fig = plt.figure()
        ax0 = fig.add_subplot(1, 1, 1)
        ax0.set_yscale("log")
        ax0.set_xlim(0, 20)

        # plot single replicas
        for p in tmds["TMD"]:
            ax0.plot(tmds["qT"], p, linewidth = 0.5, color = "b", alpha = 0.3)

        # Plot mean replica
        ax0.plot(tmds["qT"], np.mean(tmds["TMD"], axis = 0), label = "Mean replica", color = "r")

        ax0.set_xlabel("$k_T$ [GeV]")
        ax0.set_ylabel(r"$xf(x, k_T, Q, Q^2)$")
        ax0.set_title("TMD distribution")

        # Save plot
        tmdplot = "tmd_" + str(ifl) + "_" + str(Q) + "_" + str(x)
        fig.savefig(self.pdffolder + "/" + tmdplot + ".pdf")
        fig.savefig(self.pngfolder + "/" + tmdplot + ".png")
        plt.close()

        # Include plot in the report
        writemarkdown.mdincludefig(self.mdout, "pngplots/" + tmdplot + ".png", "TMD " + dist.upper()
                                   + " of the " + str(ifl) + "-th flavour at $Q = " + str(Q) + "$ GeV and $x = " + str(x) + "$")


    def PlotExpResults(self):
        """
        Function that creates plots from the result of the fit. It creates a pair of plots
        for each experiment in the same figure: the plot of the replicas with the experimental
        data and the plot with histograms of the chisquare and the partial error function.
        """
        for e in self.report0["Experiments"]:
            print("Plotting " + e["Name"] + "...")
            # Gather global information about the particular experiment
            expname    = e["Name"]
            plottitle  = e["Plot title python"]
            xlabel     = e["xlabelpy"]
            ylabel     = e["ylabelpy"]
            qT         = e["qT"]
            centralval = e["Central values"]
            uncunc     = e["Uncorrelated uncertainties"]
            pred0      = [sum(x) for x in zip(e["Predictions"], e["Systematic shifts"])]

            # Select experiment for mean replica
            for exp in self.report_mean["Experiments"]:
                if exp["Name"] == expname:
                    break
            pred_mean = [sum(x) for x in zip(exp["Predictions"], exp["Systematic shifts"])]

            
            # Initialise (multi) plot
            """ for three plots: one principal (bigger) and two smaller
            below the principal one:

            gridsize = (3, 2)
            fig = plt.figure(figsize = (12, 8))
            princplot = plt.subplot2grid(gridsize, (0, 0), colspan=2, rowspan=2)
            histo1 = plt.subplot2grid(gridsize, (2, 0))
            histo2 = plt.subplot2grid(gridsize, (2, 1))
            """
            fig, (ax1, ax2) = plt.subplots(nrows = 1, ncols = 2, figsize = (14, 7))
            #fig, (ax1, ax2) = plt.subplots(nrows = 1, ncols = 2, figsize = (10, 6))

            # Set title and labels
            fig.suptitle(plottitle)
            ax1.set_xlabel(xlabel)
            ax1.set_ylabel(ylabel)

            # Loop over replicas
            partialchi2 = []
            for r in self.reports:
                # Select experiment
                for exp in r["Experiments"]:
                    if exp["Name"] == expname:
                         break

                # Get replica-specific quantities
                partialchi2.append(exp["partial chi2"])
                predictions = [sum(x) for x in zip(exp["Predictions"], exp["Systematic shifts"])]

                # Draw the plot
                ax1.plot(qT, predictions, linewidth = 0.5, color = "b", alpha = 0.3)

            # Draw plot of the central and mean replica
            ax1.plot(qT, pred0, label = "Central replica", color = "k")
            ax1.plot(qT, pred_mean, label = "Mean replica", color = "r")

            # Plot data with experimental errors
            ax1.errorbar(qT, centralval, yerr = uncunc, color = "black", linestyle = "None", label = "data", marker = 'o', markersize = 2.5, capsize = 3, linewidth = 2)
            ax1.legend()

            # Define equally spaced bins and ticks for the histogram
            #nbins, majorticks, minorticks = utilities.BinsAndTicks(min(partialchi2), max(partialchi2))

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
            #ax2.hist(partialchi2, bins = nbins, histtype='bar', color = bcolours.tangerineyellow, label = "$\chi^2$")
            ax2.hist(partialchi2, bins = 20, histtype='bar', color = bcolours.tangerineyellow, label = "$\chi^2$")
            ax2.legend()

            # Set labels and ticks
            #ax2.set_xticks(majorticks)
            #ax2.set_xticks(minorticks, minor = True)
            ax2.set_xlabel("$\chi^2$")
            ax2.set_ylabel("Counts")

            # Save plot
            fig.savefig(self.pdffolder + "/" + expname + ".pdf")
            fig.savefig(self.pngfolder + "/" + expname + ".png")
            plt.close()

            # Include plot in the report
            writemarkdown.mdincludefig(self.mdout, "pngplots/" + expname + ".png", expname + " data-theory comparison")
