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
print(banner.banner())

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
answers = prompt(questions, style=custom_style_3)

# Create output folder
outfolder = RunFolder + "/../" + answers["Output folder"]
print(bcolours.OKBLUE + "\nCreating output folder '" + outfolder + "' and running the filter...\n" + bcolours.ENDC)
os.mkdir(outfolder)

# Run Filter in the output folder
os.system(RunFolder + "/Filter " + RunFolder + "/../rawdata/ " + outfolder + "/data")

# Open "dataset.yaml" file to select experiments to fit
with open(outfolder + "/data/datasets.yaml", "r") as stream:
    datasets = yaml.load(stream, Loader=yaml.RoundTripLoader)

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
answers = prompt(questions, style=custom_style_3)

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

# Dump new dataset file to disk
with open(outfolder + "/data/datasets.yaml", "w") as outfile:
    yaml.dump(datasets, outfile, Dumper=yaml.RoundTripDumper)

# Collect available sets of tables
tables = [d for d in os.listdir(RunFolder + "/../tables/") if os.path.isdir(os.path.join(RunFolder + "/../tables/", d))]

questions = [
    {
        "type": "list",
        "name": "tables",
        "message": "Choose amongst the following sets of tables:",
        "choices": tables,
    }
]
answers = prompt(questions, style=custom_style_3)

# Print features of the chosen interpolation tables
print(bcolours.HEADER + bcolours.BOLD + "\nFeatures of the chosen interpolation tables:" + bcolours.ENDC)
with open(RunFolder + "/../tables/" + answers["tables"] + "/config.yaml", "r") as stream:
    feats = yaml.load(stream, Loader=yaml.RoundTripLoader)
    print(bcolours.OKBLUE + yaml.dump(feats, Dumper=yaml.RoundTripDumper) + bcolours.ENDC)

# Ask for confirmation
questions = [
    {
        "type": "confirm",
        "name": "ConfirmTables",
        "message": "Confirm choice of the interpolation tables?",
        "default": True
    }
]
confirm = prompt(questions, style=custom_style_3)
if not confirm["ConfirmTables"]:
    print(bcolours.FAIL + bcolours.BOLD + "\nquitting\n" + bcolours.ENDC)
    exit()

# Create symbolic link to the chosen interpolation tables
os.system("ln -s " + RunFolder + "/../tables/" + answers["tables"] + " " + outfolder + "/tables")

# List of available parameterisations
avpars = ((re.search("===(.*)===", str(subprocess.run([RunFolder + "/AvailableParameterisations", "python"], stdout=subprocess.PIPE)))).group(1)).split()

# Choice of parameterisation
print(bcolours.HEADER + bcolours.BOLD + "\nChoice of parameterisation:" + bcolours.ENDC)
question = [
    {
        "type": "list",
        "name": "Parameterisation",
        "message": "Select parameterisation:",
        "choices": avpars
    }
]
answer = prompt(question, style=custom_style_3)
param  = answer["Parameterisation"]

if param == "DWS":
    pathfitconfig = RunFolder + "/../cards/fitDWS.yaml"
    with open(pathfitconfig, "r") as stream:
        fitconfdef = yaml.load(stream, Loader=yaml.RoundTripLoader)

elif param == "PV17":
    pathfitconfig = RunFolder + "/../cards/fitPV17.yaml"
    with open(pathfitconfig, "r") as stream:
        fitconfdef = yaml.load(stream, Loader=yaml.RoundTripLoader)

elif param == "PV19":
    pathfitconfig = RunFolder + "/../cards/fitPV19.yaml"
    with open(pathfitconfig, "r") as stream:
        fitconfdef = yaml.load(stream, Loader=yaml.RoundTripLoader)

# Choice of default file
print(bcolours.HEADER + bcolours.BOLD + "\nThe default fit configuration file is: \n" + pathfitconfig + "\n" + bcolours.ENDC)
print(bcolours.OKBLUE + yaml.dump(fitconfdef, Dumper=yaml.RoundTripDumper) + "\n" + bcolours.ENDC)

question = [
    {
        "type": "confirm",
        "name": "Default file",
        "message": "Do you want to start from a different default file?",
        "default": False
    }
]
answer = prompt(question, style=custom_style_3)

if answer["Default file"]:
    question = [
        {
            "type": "input",
            "name": "New fitconfig yaml file",
            "message": "Path of the yaml fit configuration file (from NangaParbat/ ):",
            "validator": NotOutputYamlFileValidator()
        }
    ]
    answer = prompt(question, style=custom_style_3)
    newfpath = RunFolder + "/../" + answer["New fitconfig yaml file"]

    with open(newfpath, "r") as stream:
        fitcfg = yaml.load(stream, Loader=yaml.RoundTripLoader)

    # Show the new default fit configuration file
    print(bcolours.HEADER + bcolours.BOLD + "\nThe default fit configuration file is: \n" + newfpath + "\n" + bcolours.ENDC)
    print(bcolours.OKBLUE + yaml.dump(fitcfg, Dumper=yaml.RoundTripDumper) + "\n" + bcolours.ENDC)

else:
    fitcfg = fitconfdef

# Fit configuration card - possibility to change the default
print(bcolours.HEADER + bcolours.BOLD + "\nConfiguration of the fit parameters:" + bcolours.ENDC)
questions = [
    {
        "type": "input",
        "name": "Description",
        "message": "Type a short description of the fit:",
        "default": fitcfg["Description"]
    },
    {
        "type": "list",
        "name": "Minimiser",
        "message": "Select minimiser:",
        "choices": ["none", "minuit", "ceres"],
    },
    {
        "type": "input",
        "name": "Seed",
        "message": "Enter the random-number seed for the generation of the Monte-Carlo replicas:",
        "default": fitcfg["Seed"],
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "qToQmax",
        "message": "Enter the maximum value qT / Q allowed in the fit:",
        "default": fitcfg["qToQmax"],
        "validate": FloatValidator
    },
    {
        "type": "input",
        "name": "Error function cut",
        "message": "Enter the cut on the value of the error function (used for the report):",
        "default": fitcfg["Error function cut"],
        "validate": FloatValidator
    },
    {
        "type": "confirm",
        "name": "t0prescription",
        "message": "Do you want to use the t0 prescription?",
        "default": fitcfg["t0prescription"]
    },
    {
        "type": "confirm",
        "name": "Paramfluct",
        "message": "Do you want to fluctuate the initial parameters?",
        "default": False
    }
]

# Configure fit
fitconfig = prompt(questions, style=custom_style_3)
fitconfig["Parameterisation"] = param
fitconfig["Parameters"] = fitcfg["Parameters"]
fitconfig["t0parameters"] = fitcfg["t0parameters"]

# Switch to fluctuate the initial parameters gaussianly around the
# central value according to the step.
if fitconfig["Paramfluct"]:
    Paramfluct = "y"
else:
    Paramfluct = "n"

# Report default parameters
print(bcolours.HEADER + bcolours.BOLD + "\nDefault starting parameters:" + bcolours.ENDC)
for p in fitconfig["Parameters"]:
    print(p["name"] + " = " + str(p["starting_value"]) + " (step = " + str(p["step"]) + ", fixed: " + str(p["fix"]) + ")")

# Allow the user to change the parameters
questions = [
    {
        "type": "confirm",
        "name": "ConfirmParameters",
        "message": "Do you want to change the starting parameters?",
        "default": False
    }
]
answer = prompt(questions, style=custom_style_3)

if answer["ConfirmParameters"]:
    newpars = []
    print()
    for p in fitconfig["Parameters"]:
        print( bcolours.OKBLUE + "Modify parameter " + p["name"] + ":" + bcolours.ENDC)
        questions = [
            {
                "type": "input",
                "name": "starting_value",
                "message": "Enter new starting value:",
                "validate": FloatValidator,
                "default": str(p["starting_value"])
            },
            {
                "type": "input",
                "name": "step",
                "message": "Enter new step:",
                "validate": FloatValidator,
                "default": str(p["step"])
            },
            {
                "type": "confirm",
                "name": "fix",
                "message": "Do you want to fix the parameter?",
                "default": p["fix"]
            }
        ]
        np = prompt(questions, style=custom_style_3)
        np["name"] = p["name"]
        newpars.append(np)

    fitconfig["Parameters"] = newpars
    print(bcolours.HEADER + bcolours.BOLD + "\nNew starting parameters:" + bcolours.ENDC)
    for p in fitconfig["Parameters"]:
        print(p["name"] + " = " + str(p["starting_value"]) + " (step = " + str(p["step"]) + ", fixed: " + str(p["fix"]) + ")")

if fitconfig["t0prescription"]:
    # Report default t0 parameters
    print(bcolours.HEADER + bcolours.BOLD + "\nT0 parameters: " + bcolours.ENDC, fitconfig["t0parameters"])

    # Allow the user to change the parameters
    questions = [
        {
            "type": "confirm",
            "name": "Confirmt0parameters",
            "message": "Do you want to change the t0 parameters?",
            "default": False
        }
    ]
    answer = prompt(questions, style=custom_style_3)

    if answer["Confirmt0parameters"]:
        newpars = []
        for p in fitconfig["t0parameters"]:
            questions = [
                {
                    "type": "input",
                    "name": "value",
                    "message": "Enter new value for the " + str(fitconfig["t0parameters"].index(p)) + "-th parameter:",
                    "validate": FloatValidator,
                    "default": str(p)
                }
            ]
            np = prompt(questions, style=custom_style_3)
            newpars.append(np["value"])

        fitconfig["t0parameters"] = newpars
        print(bcolours.HEADER + bcolours.BOLD + "\nNew T0 parameters: " + bcolours.ENDC, fitconfig["t0parameters"])

# Print configuration in yaml
with open(outfolder + "/fitconfig.yaml", "w") as outfile:
    yaml.dump(fitconfig, outfile, Dumper=yaml.RoundTripDumper)

# Questions concerning the fit
print(bcolours.HEADER + bcolours.BOLD + "\nFit parameters: " + bcolours.ENDC)
questions = [
    {
        "type": "input",
        "name": "Number of replicas",
        "message": "Enter the number of Monte-Carlo replicas that you want to run:",
        "default": "0",
        "validate": IntegerValidator
    },
    {
        "type": "list",
        "name": "Host",
        "message": "Where do you want to run?",
        "choices": ["Locally", "Slurm"],
    }
]
answer = prompt(questions, style=custom_style_3)

# Now launch fits to Monte-Carlo replicas (this includes a fit to the
# central values, i.e. replica 0). Run the fits according to the host chosen
print(bcolours.OKBLUE + "\nLaunching the fits...\n" + bcolours.ENDC)
if answer["Host"] == "Locally":
    for i in range(int(answer["Number of replicas"]) + 1):
        os.system(RunFolder + "/RunFit " + outfolder + "/ " + outfolder + "/fitconfig.yaml " + outfolder + "/data " + outfolder + "/tables " + str(i) + " " + Paramfluct + " n")
elif answer["Host"] == "Slurm":
    f = open(outfolder + "/submit.sh", "w+")
    f.write("#!/bin/bash\n")
    f.write("#\n")
    f.write("#SBATCH --job-name=NPfit\n")
    f.write("#SBATCH --output=output.txt\n")
    f.write("#SBATCH --array=0-" + answer["Number of replicas"] + "\n")
    f.write("#SBATCH --partition=12hr\n")
    f.write("\n")
    f.write("srun " + RunFolder + "/RunFit " + outfolder + "/ " + outfolder + "/fitconfig.yaml " + outfolder + "/data " + outfolder + "/tables $SLURM_ARRAY_TASK_ID " + Paramfluct + " n\n")
    f.close()
    os.system("sbatch " + outfolder + "/submit.sh")
