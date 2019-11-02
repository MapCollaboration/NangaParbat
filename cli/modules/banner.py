import pyfiglet
from modules.bcolours import *

def fitbanner():
    banner = pyfiglet.figlet_format("NangaParbat Fit", font = "slant")
    return bcolours.ANSWERBLUE + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC
    # return bcolours.OKGREEN + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC

def reportbanner():
    banner = pyfiglet.figlet_format("NangaParbat Report", font = "slant")
    return bcolours.ACTREPORT + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC

def tablebanner():
    banner = pyfiglet.figlet_format("NangaParbat Tables", font = "slant")
    return bcolours.GIULIA + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC
