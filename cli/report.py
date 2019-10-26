import os

from PyInquirer import prompt
from examples import custom_style_3
from ruamel import yaml

from modules.bcolours import *
from modules.fitresults import *
from modules.validators import *

import modules.banner as banner
import modules.writemarkdown as writemarkdown
import modules.utilities as utilities

# Print banner
print(banner.reportbanner())

# Folder containing the utilities
CliFolder = os.path.dirname(os.path.realpath(__file__))

# Prompt for output folder
questions = [
    {
        "type": "input",
        "name": "Output folder",
        "message": "Type the name of the fit result folder: ",
        "validate": NotOutputFolderValidator
    }
]
answers = prompt(questions, style = custom_style_3)

# Set folder with the info for the report (output of the fit)
outfolder = CliFolder + "/../" + answers["Output folder"]
print(bcolours.ACTREPORT + "\nFolder with info for the report: '" + outfolder + "'" + bcolours.ENDC)

# Create report folder
reportfolder = outfolder + "/Report"
print(bcolours.ACTREPORT + "Creating folder for the final report: '" + reportfolder + "'" + bcolours.ENDC)
os.mkdir(reportfolder)

# Create report file
reportfile = reportfolder + "/Report.md"
print(bcolours.ACTREPORT + "Creating final report file: '" + reportfile + "'" + bcolours.ENDC)

# Read fit configuration file
with open(outfolder + "/fitconfig.yaml", "r") as fc:
    fitconfig = yaml.load(fc, Loader = yaml.RoundTripLoader)
    print(bcolours.ACTREPORT + "Loading fit configuration file: '" + outfolder + "/fitconfig.yaml'" + bcolours.ENDC)

# Read tables configuration file
with open(outfolder + "/tables/config.yaml", "r") as tc:
    config = yaml.load(tc, Loader = yaml.RoundTripLoader)
    print(bcolours.ACTREPORT + "Loading tables configuration file: '" + outfolder + "/tables/config.yaml'\n" + bcolours.ENDC)

# Now run "RunFit" to generate the central replica
print(bcolours.ACTREPORT + "Generating mean replica...\n" + bcolours.ENDC)
os.system(CliFolder + "/../run/RunFit " + outfolder + "/ " + outfolder + "/fitconfig.yaml " + outfolder + "/data " + outfolder + "/tables 0 n y")

print(bcolours.ACTREPORT + "\nSelecting usable replicas..." + bcolours.ENDC)

# Select replicas accordig to whether the fit has converged and the
# global error-function value is within the cut.
reports = []
for rf in os.listdir(outfolder):
    try:
        with open(outfolder + "/" + rf + "/Report.yaml", "r") as rep:
            report = yaml.load(rep, Loader = yaml.RoundTripLoader)
            if (int(report["Status"]) == 0) or (str(report["Global chi2"]) == "nan"):
                print("- " + rf + " did not converge.")
                print(bcolours.WARNING + "  chi2 = " + str(report["Global chi2"]) + bcolours.ENDC)
                continue
            if float(report["Global error function"]) > float(fitconfig["Error function cut"]):
                print("- " + rf + " does not pass the error-function cut.")
                print(bcolours.WARNING + "  chi2 = " + str(report["Global chi2"]) + bcolours.ENDC)
                continue
            if rf != "replica_0" and rf != "mean_replica":
                reports.append(report)
    except FileNotFoundError:
        pass
    except NotADirectoryError:
        pass

# Print the number of usable replicas
print(bcolours.REPORT + "\n" + "The number of usable replicas is: " + bcolours.BOLD + str(len(reports)) + bcolours.ENDC)

# Get report of the zero-th replica
with open(outfolder + "/replica_0/Report.yaml", "r") as rep:
    report0 = yaml.load(rep, Loader = yaml.RoundTripLoader)
    if int(report0["Status"]) == 0:
        print("- replica_0 did not converge.")
        sys.exit()
    if float(report0["Global error function"]) > float(fitconfig["Error function cut"]):
        print("- replica_0 does not pass the error-function cut.")
        sys.exit()

# Print the chi2 of replica 0
print(bcolours.REPORT + "The chi2 of the central replica is: " + bcolours.BOLD + str(report0["Global chi2"]) + bcolours.ENDC)

# Get report of the mean replica
with open(outfolder + "/mean_replica/Report.yaml", "r") as rep:
    report_mean = yaml.load(rep, Loader = yaml.RoundTripLoader)

# Print the chi2 of replica 0
print(bcolours.REPORT + "The chi2 of the mean replica is: " + bcolours.BOLD + str(report_mean["Global chi2"]) + "\n " + bcolours.ENDC)

# Create folder for plot.pdf and for plot.png
os.mkdir(reportfolder + "/plots")
os.mkdir(reportfolder + "/pngplots")

# Write final report in Markdown
with open(reportfile, "w+") as mdout:
    # Title
    writemarkdown.mdtitle(mdout, 1, "Report of the fit")

    # Summary of the fit
    writemarkdown.mdtitle(mdout, 2, "Fit summary")

    mdout.write("Description: "                          + fitconfig["Description"]        + "  \n")
    mdout.write("Minimiser: "                            + fitconfig["Minimiser"]          + "  \n")
    mdout.write("Random seed: "                          + fitconfig["Seed"]               + "  \n")
    mdout.write("Maximum values allowed for $q_T / Q$: " + fitconfig["qToQmax"]            + "  \n")
    mdout.write("Cut on the error function: "            + fitconfig["Error function cut"] + "  \n")
    mdout.write("Parameterisation: "                     + fitconfig["Parameterisation"]   + "  \n")
    mdout.write("Explicit formula:\n\n")
    mdout.write(report0["Non-perturbative function"] + "\n")

    # T0 parameters
    mdout.write("$t_0$ prescription: " + str(fitconfig["t0prescription"]) + "  \n")
    if fitconfig["t0prescription"]:
        headings = list(report0["Parameters"].keys())
        par = [tuple(fitconfig["t0parameters"])]
        writemarkdown.table(mdout, par, headings)

    # Summary of the tables
    writemarkdown.mdtitle(mdout, 2, "Theory summary")

    mdout.write("Collinear PDF set: " + config["pdfset"]["name"] + " member " + str(config["pdfset"]["member"]) + "  \n")
    mdout.write("Collinear FF set: "  + config["ffset"]["name"]  + " member " + str(config["ffset"]["member"])  + "  \n")
    mdout.write("Perturbative order: " + utilities.GetPertOrd(str(config["PerturbativeOrder"])) + "  \n")
    mdout.write(r"Reference value of the fine-structure constant: $\alpha(Q = " + str(config["alphaem"]["Qref"]) + r"\;{\rm GeV}) = " +
                str(config["alphaem"]["aref"]) + "$ (running " + str(config["alphaem"]["run"]) + ")  \n\n")

    ################################## Analysis ##################################

    # Upload results
    results = fitresults(reports, report0, report_mean, reportfolder, mdout)

    # Statistical estimators
    writemarkdown.mdtitle(mdout, 2, "Global statistical estimators")
    results.StatisticalEstimators()

    # Parameters
    writemarkdown.mdtitle(mdout, 2, "Parameters")
    results.ProcessParameters()
    results.PlotCorrelationMatrix()

    # Fit properties
    writemarkdown.mdtitle(mdout, 2, "Fit properties")
    results.PlotGlobalChi2()
    results.PlotGlobalErrFunc()
    results.HistoParameters()

    # Table of single chi2's
    writemarkdown.mdtitle(mdout, 2, "Table of $\chi^2$'s")
    results.Chi2Table()

    # Create plots of TMDs in kT space
    writemarkdown.mdtitle(mdout, 2, "TMDs in $k_T$ space")
    results.PlotTMDs("pdf", 1, 10, 0.1)

    # Create one set of plots for each experiment
    writemarkdown.mdtitle(mdout, 2, "Data-theory comparison")
    results.PlotExpResults()
    mdout.close()

# Copy pandoc relevant files in the report folder and produce report
# in html and tex format
os.system("cp " + CliFolder + "/PandocFiles/* " + reportfolder + "/.")
os.chdir(reportfolder)
os.system("bash pandoc_to_html.sh Report.md Report.html")
os.system("bash pandoc_to_pdf.sh Report.md Report.tex")
