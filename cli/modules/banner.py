import pyfiglet
from modules.bcolours import *

def banner():
    banner = pyfiglet.figlet_format("NangaParbat", font = "slant")
    return bcolours.ANSWERBLUE + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC
    # return bcolours.OKGREEN + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC

def reportbanner():
    banner = pyfiglet.figlet_format("NangaParbat Report", font = "slant")
    return bcolours.ACTREPORT + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC
