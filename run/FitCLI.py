from __future__ import print_function, unicode_literals

import pyfiglet
import regex
from pprint import pprint
from PyInquirer import style_from_dict, Token, prompt, Separator
from PyInquirer import Validator, ValidationError
from examples import custom_style_3
import os
from ruamel import yaml

class bcolours:
    HEADER    = "\033[95m"
    OKBLUE    = "\033[94m"
    OKGREEN   = "\033[92m"
    WARNING   = "\033[93m"
    FAIL      = "\033[91m"
    ENDC      = "\033[0m"
    BOLD      = "\033[1m"
    UNDERLINE = "\033[4m"

banner = pyfiglet.figlet_format("NangaParbat", font = "slant")
print(bcolours.OKGREEN + bcolours.BOLD + "\nWelcome to:")
print(banner + bcolours.ENDC)

# Folder containing the utilities
RunFolder = os.path.dirname(os.path.realpath(__file__))

# Validators
class OutputFolderValidator(Validator):
    def validate(self, document):
        dir = RunFolder + "/../" + document.text
        exists = os.path.isdir(dir)
        if exists:
            raise ValidationError(message = "The folder '" + document.text + "' already exists", cursor_position = len(document.text))

class FloatValidator(Validator):
    def validate(self, document):
        try:
            float(document.text)
        except ValueError:
            raise ValidationError(message = "Please enter a number", cursor_position = len(document.text))

class IntegerValidator(Validator):
    def validate(self, document):
        try:
            int(document.text)
            if int(document.text) < 0:
                raise ValidationError(message = "The number has to be non negative", cursor_position = len(document.text))
        except ValueError:
            raise ValidationError(message = "Please enter an integer number", cursor_position = len(document.text))

# Output folder
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
tables = [d for d in os.listdir(RunFolder + "/../tables/") if os.path.isdir(os.path.join(RunFolder + "/../tables/",d))]

questions = [
    {
        "type": "list",
        "name": "tables",
        "message": "Choose amogst the following sets of tables:",
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

# Fit configuration card
print(bcolours.HEADER + bcolours.BOLD + "\nConfiguration of the fit parameters:" + bcolours.ENDC)
questions = [
    {
        "type": "input",
        "name": "Description",
        "message": "Type a short descrition of the fit:"
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
        "default": "1234",
        "validate": IntegerValidator
    },
    {
        "type": "input",
        "name": "qToQmax",
        "message": "Enter the maximum value qT / Q allowed in the fit:",
        "default": "0.2",
        "validate": FloatValidator
    },
    {
        "type": "confirm",
        "name": "t0prescription",
        "message": "Do you want to use the t0 prescription?",
        "default": True
    },
    {
        "type": "list",
        "name": "Parameterisation",
        "message": "Select minimiser:",
        "choices": ["DWS", "PV17", "PV19"],
    }
]
fitconfig = prompt(questions, style=custom_style_3)

# Now initialise parameters according to the parameterisation chosen
if fitconfig["Parameterisation"] == "DWS":
    fitconfig["t0parameters"] = [0.01, 0.1]
    fitconfig["Parameters"] = [
        {"name": "g1", "starting_value": 0.01, "step": 0.001, "fix": False},
        {"name": "g2", "starting_value": 0.1,  "step": 0.005, "fix": False}
        ]
elif fitconfig["Parameterisation"] == "PV17":
    fitconfig["t0parameters"] = [0.13, 0.285, 2.98, 0.173, 0.39]
    fitconfig["Parameters"] = [
        {"name": "g2",     "starting_value": 0.13,  "step": 0.001, "fix": False},
        {"name": "N1",     "starting_value": 0.285, "step": 0.003, "fix": False},
        {"name": "alpha",  "starting_value": 2.98,  "step": 0.030, "fix": False},
        {"name": "sigma",  "starting_value": 0.173, "step": 0.002, "fix": False},
        {"name": "lambda", "starting_value": 0.39,  "step": 0.005, "fix": True }
        ]
elif fitconfig["Parameterisation"] == "PV19":
    fitconfig["t0parameters"] = [0.0327043, 0.46221, 0.450088, 0.5, 0, 0]
    fitconfig["Parameters"] = [
        {"name": "g2",     "starting_value": 0.0327043, "step": 0.001, "fix": False},
        {"name": "N1",     "starting_value": 0.46221,   "step": 0.003, "fix": False},
        {"name": "alpha",  "starting_value": 0.450088,  "step": 0.010, "fix": False},
        {"name": "sigma",  "starting_value": 0.5,       "step": 0.005, "fix": False},
        {"name": "lambda", "starting_value": 0,         "step": 0.005, "fix": True },
        {"name": "delta",  "starting_value": 0,         "step": 0.002, "fix": True }
        ]

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
    for p in pars["Parameters"]:
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
        for p in t0["t0parameters"]:
            questions = [
                {
                    "type": "input",
                    "name": "value",
                    "message": "Enter new value for the " + str(t0["t0parameters"].index(p)) + "-th parameter:",
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
        "message": "Enter the number of Monte-Carlo replicas you want to run:",
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

# Define commands to run the fit according to the host chosen
if answer["Host"] == "Locally":
    command = ""
elif answer["Host"] == "Slurm":
    command = "sbatch"
    print(bcolours.FAIL + bcolours.BOLD + "Slurm not enabled yet" + bcolours.ENDC)
    exit()

print(bcolours.OKBLUE + "\nLaunching the fits...\n" + bcolours.ENDC)

# Now launch fits to Monte-Carlo replicas (this includes a fit to the
# central values, i.e. replica 0)
for i in range(int(answer["Number of replicas"]) + 1):
    os.system(command + " " + RunFolder + "/RunFit " + outfolder + "/ " + outfolder + "/fitconfig.yaml " + outfolder + "/data " + outfolder + "/tables " + str(i))
