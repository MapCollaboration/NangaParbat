import os
import subprocess
import re

from PyInquirer import prompt, Separator
from examples import custom_style_3
from ruamel import yaml

import modules.banner as banner
import modules.bcolours as bcolours
import modules.validators as validators
from modules.bcolours import *
from modules.validators import *

# Print banner
print(banner.tablebanner())

# Folder containing the utilities
RunFolder = os.path.dirname(os.path.realpath(__file__)) + "/../run"

# Create output folder
questions = [
    {
        "type": "input",
        "name": "Output folder",
        "message": "Type the name of the output folder:",
        "validate": OutputFolderValidator
    }
]
answers = prompt(questions, style = custom_style_3)

# Create output folder
outfolder = RunFolder + "/../" + answers["Output folder"]
print(bcolours.OKBLUE + "\nCreating output folder '" + outfolder + "' and running the filter...\n" + bcolours.ENDC)
os.mkdir(outfolder)

# Run Filter in the output folder
os.system(RunFolder + "/Filter " + RunFolder + "/../rawdata/ " + outfolder + "/data")

# Open "dataset.yaml" file to select experiments
with open(outfolder + "/data/datasets.yaml", "r") as stream:
    datasets = yaml.load(stream, Loader = yaml.RoundTripLoader)

# Read the datasets and assume that they are all included
print(bcolours.HEADER + bcolours.BOLD + "\nSelection of the data sets:" + bcolours.ENDC)
choices = []
for exp in datasets:
    choices.append(Separator(exp + ":"))
    for ds in datasets[exp]:
        choices.append({"name": ds["name"], "checked": True})

questions = [
    {
        "type": "checkbox",
        "qmark": "-",
        "message": "Select data sets:",
        "name": "experiments",
        "choices": choices,
        "validate": lambda answer: "You must choose at least one experiment." \
            if len(answer) == 0 else True
    }
]
answers = prompt(questions, style = custom_style_3)

# Now remove from the "datasets" node all the datasets that have been
# excluded
for exp in datasets:
    restart = True
    while restart:
        for ds in datasets[exp]:
            if ds == datasets[exp][-1]:
                restart = False
            if not ds["name"] in answers["experiments"]:
                del datasets[exp][datasets[exp].index(ds)]
                break

# List of selected datasets
selds = []
for exp in datasets:
    for ds in datasets[exp]:
        selds.append(ds["name"])
            
# Dump new dataset file to disk
with open(outfolder + "/data/datasets.yaml", "w") as outfile:
    yaml.dump(datasets, outfile, Dumper = yaml.RoundTripDumper)

# Load default config file
pathconfig = RunFolder + "/../cards/config.yaml"
with open(pathconfig, "r") as stream:
    confdef = yaml.load(stream, Loader = yaml.RoundTripLoader)

print(bcolours.HEADER + bcolours.BOLD + "\nThe default configuration file is: \n" + pathconfig + "\n" + bcolours.ENDC)
print(bcolours.OKBLUE + yaml.dump(confdef, Dumper = yaml.RoundTripDumper) + "\n" + bcolours.ENDC)

# Choice of default file
question = [
    {
        "type": "confirm",
        "name": "Default file",
        "message": "Do you want to start from a different default file?",
        "default": False
    }
]
answer = prompt(question, style = custom_style_3)

if answer["Default file"]:
    question = [
        {
            "type": "input",
            "name": "New config yaml file",
            "message": "Path of the yaml configuration file (from NangaParbat/ ):",
            "validator": NotOutputYamlFileValidator()
        }
    ]
    answer = prompt(question, style = custom_style_3)
    newfpath = RunFolder + "/../" + answer["New config yaml file"]

    with open(newfpath, "r") as stream:
        cfg = yaml.load(stream, Loader = yaml.RoundTripLoader)

    # Show the new default configuration file
    print(bcolours.HEADER + bcolours.BOLD + "\nThe default configuration file is: \n" + newfpath + "\n" + bcolours.ENDC)
    print(bcolours.OKBLUE + yaml.dump(cfg, Dumper = yaml.RoundTripDumper) + "\n" + bcolours.ENDC)

else:
    cfg = confdef

# List of available bstar
avbstar = ((re.search("===(.*)===", str(subprocess.run([RunFolder + "/AvailableBstar", "python"], stdout = subprocess.PIPE)))).group(1)).split()

# Fit configuration card - possibility to change the default
print(bcolours.HEADER + bcolours.BOLD + "\nConfiguration of the parameters:" + bcolours.ENDC)
questions = [
    {
        "type": "input",
        "name": "PDF set",
        "message": "Type the name of the PDF set:",
        "default": cfg["pdfset"]["name"]
    },
    {
        "type": "input",
        "name": "PDF member",
        "message": "Enter the member ID of the PDF set:",
        "default": str(cfg["pdfset"]["member"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "FF set",
        "message": "Type the name of the FF set:",
        "default": cfg["ffset"]["name"]
    },
    {
        "type": "input",
        "name": "FF member",
        "message": "Enter the member ID of the FF set:",
        "default": str(cfg["ffset"]["member"]),
        "validate": IntegerValidator
    },
    {
        "type": "list",
        "name": "bstar",
        "message": "Select bstar prescription:",
        "choices": avbstar
    },
    {
        "type": "list",
        "name": "Perturbative order",
        "message": "Select perturbative order:",
        "choices": ["LL", "NLL", "NLLp", "NNLL", "NNLLp", "N3LL"]
    },
    {
        "type": "input",
        "name": "Initial scale variation",
        "message": "Enter the initial scale variation factor:",
        "default": str(cfg["TMDscales"]["Ci"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "Final scale variation",
        "message": "Enter the final scale variation factor:",
        "default": str(cfg["TMDscales"]["Cf"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "aref",
        "message": "Enter the reference value of the fine-structure constant:",
        "default": str(cfg["alphaem"]["aref"]),
        "validate": FloatValidator
    },
    {
        "type": "input",
        "name": "Qref",
        "message": "Enter the reference scale of the fine-structure constant:",
        "default": str(cfg["alphaem"]["Qref"]),
        "validate": FloatValidator
    },
    {
        "type": "confirm",
        "name": "arun",
        "message": "Do you want the fine-structure constant to run?",
        "default": cfg["alphaem"]["run"]
    },
    {
        "type": "input",
        "name": "Ogata points",
        "message": "Enter the number of points to use for the Ogata quadrature:",
        "default": str(cfg["nOgata"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "nQgrid",
        "message": "Enter the number of points of the grid in Q:",
        "default": str(cfg["Qgrid"]["n"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "idQgrid",
        "message": "Enter the interpolation degree of the grid in Q:",
        "default": str(cfg["Qgrid"]["InterDegree"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "epsQgrid",
        "message": "Enter the integration accuracy on the grid in Q:",
        "default": str(cfg["Qgrid"]["eps"]),
        "validate": FloatValidator
    },
    {
        "type": "input",
        "name": "nxigrid",
        "message": "Enter the number of points of the grid in xi:",
        "default": str(cfg["xigrid"]["n"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "idxigrid",
        "message": "Enter the interpolation degree of the grid in xi:",
        "default": str(cfg["xigrid"]["InterDegree"]),
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "epsxigrid",
        "message": "Enter the integration accuracy on the grid in xi:",
        "default": str(cfg["xigrid"]["eps"]),
        "validate": FloatValidator
    },
    {
        "type": "input",
        "name": "qToverQmax",
        "message": "Enter the cut on qT/Q for the table production:",
        "default": str(cfg["qToverQmax"]),
        "validate": FloatValidator
    }
]

# PDF x-space grid
questions.append(
    {
        "type": "input",
        "name": "nxgrid PDF",
        "message": "Enter the number of x-space subgrids for the PDFs:",
        "default": str(len(cfg["xgridpdf"])),
        "validate": IntegerValidator
    }
    )
for i in range(len(cfg["xgridpdf"])):
    questions.extend([
        {
            "type": "input",
            "name": "nxpdf" + str(i),
            "message": "Enter the number of points for the " + str(i) +"-th PDF subgrid:",
            "default": str(cfg["xgridpdf"][i][0]),
        "validate": IntegerValidator
        },
        {
            "type": "input",
            "name": "xminpdf" + str(i),
            "message": "Enter the lower bound for the " + str(i) +"-th PDF subgrid:",
            "default": str(cfg["xgridpdf"][i][1]),
        "validate": FloatValidator
        },
        {
            "type": "input",
            "name": "idpdf" + str(i),
            "message": "Enter the interpolation degree for the " + str(i) +"-th PDF subgrid:",
            "default": str(cfg["xgridpdf"][i][2]),
        "validate": IntegerValidator
        }
        ])

# FF x-space grid
questions.append(
    {
        "type": "input",
        "name": "nxgrid FF",
        "message": "Enter the number of x-space subgrids for the FFs:",
        "default": str(len(cfg["xgridff"])),
        "validate": IntegerValidator
    }
    )
for i in range(len(cfg["xgridff"])):
    questions.extend([
        {
            "type": "input",
            "name": "nxff" + str(i),
            "message": "Enter the number of points for the " + str(i) +"-th FF subgrid:",
            "default": str(cfg["xgridff"][i][0]),
        "validate": IntegerValidator
        },
        {
            "type": "input",
            "name": "xminff" + str(i),
            "message": "Enter the lower bound for the " + str(i) +"-th FF subgrid:",
            "default": str(cfg["xgridff"][i][1]),
        "validate": FloatValidator
        },
        {
            "type": "input",
            "name": "idff" + str(i),
            "message": "Enter the interpolation degree for the " + str(i) +"-th FF subgrid:",
            "default": str(cfg["xgridff"][i][2]),
        "validate": IntegerValidator
        }
        ])

# Configuration of the tables
inconfig = prompt(questions, style = custom_style_3)

# Construct config file

# Print configuration in yaml
with open(outfolder + "/config.yaml", "w") as outfile:
    pdfset = {"pdfset": {"name": inconfig["PDF set"], "member": inconfig["PDF member"]}}
    yaml.dump(pdfset, outfile, Dumper = yaml.RoundTripDumper)

    ffset = {"ffset": {"name": inconfig["FF set"], "member": inconfig["FF member"]}}
    yaml.dump(ffset, outfile, Dumper = yaml.RoundTripDumper)

    bstar = {"bstar": inconfig["bstar"]}
    yaml.dump(bstar, outfile, Dumper = yaml.RoundTripDumper)

    ptmap = {"LL": 0, "NLL": 1, "NLLp": -1, "NNLL": 2, "NNLLp": -2, "N3LL": 3}
    pto = {"PerturbativeOrder": ptmap[inconfig["Perturbative order"]]}
    yaml.dump(pto, outfile, Dumper = yaml.RoundTripDumper)

    scales = {"TMDscales": {"Ci": inconfig["Initial scale variation"], "Cf": inconfig["Final scale variation"]}}
    yaml.dump(scales, outfile, Dumper = yaml.RoundTripDumper)

    alphaem = {"alphaem": {"aref": inconfig["aref"], "Qref": inconfig["Qref"], "run": inconfig["arun"]}}
    yaml.dump(alphaem, outfile, Dumper = yaml.RoundTripDumper)

    nOgata = {"nOgata": inconfig["Ogata points"]}
    yaml.dump(nOgata, outfile, Dumper = yaml.RoundTripDumper)

    Qgrid = {"Qgrid": {"n": inconfig["nQgrid"], "InterDegree": inconfig["idQgrid"], "eps": inconfig["epsQgrid"]}}
    yaml.dump(Qgrid, outfile, Dumper = yaml.RoundTripDumper)

    xigrid = {"xigrid": {"n": inconfig["nxigrid"], "InterDegree": inconfig["idxigrid"], "eps": inconfig["epsxigrid"]}}
    yaml.dump(xigrid, outfile, Dumper = yaml.RoundTripDumper)

    qToverQmax = {"qToverQmax": inconfig["qToverQmax"]}
    yaml.dump(qToverQmax, outfile, Dumper = yaml.RoundTripDumper)

    xgridpdf = {"xgridpdf": [[inconfig["nxpdf" + str(i)], inconfig["xminpdf" + str(i)], inconfig["idpdf" + str(i)]] for i in range(int(inconfig["nxgrid PDF"]))]}
    yaml.dump(xgridpdf, outfile, Dumper = yaml.RoundTripDumper)

    xgridff = {"xgridff": [[inconfig["nxff" + str(i)], inconfig["xminff" + str(i)], inconfig["idff" + str(i)]] for i in range(int(inconfig["nxgrid FF"]))]}
    yaml.dump(xgridff, outfile, Dumper = yaml.RoundTripDumper)

# Questions concerning the fit
print(bcolours.HEADER + bcolours.BOLD + "\nFit parameters: " + bcolours.ENDC)
questions = [
    {
        "type": "list",
        "name": "Host",
        "message": "Where do you want to run?",
        "choices": ["Locally", "Slurm"],
    }
]
answer = prompt(questions, style = custom_style_3)

# Now launch the production of tables. Run the fits according to the
# host chosen
print(bcolours.OKBLUE + "\nLaunching the fits...\n" + bcolours.ENDC)
if answer["Host"] == "Locally":
    os.system(RunFolder + "/CreateTables " + outfolder + "/config.yaml " + outfolder + "/data " + outfolder + "/ n")
elif answer["Host"] == "Slurm":
    f = open(outfolder + "/submit_tables.sh", "w+")
    f.write("#!/bin/bash\n")
    f.write("#\n")
    f.write("#SBATCH --job-name=NPtables\n")
    f.write("#SBATCH --output=output.txt\n")
    f.write("#SBATCH --array=0-" + str(len(selds)-1) + "\n")
    f.write("#SBATCH --partition=12hr\n")
    f.write("\n")
    f.write("DS=( ")
    for s in selds:
        f.write(s + " ")
    f.write(")\n\n")
    f.write("srun " + RunFolder + "/CreateTables " + outfolder + "/config.yaml " + outfolder + "/data " + outfolder + "/ n ${DS[$SLURM_ARRAY_TASK_ID]}\n")
    f.close()
    os.system("sbatch " + outfolder + "/submit_tables.sh")

