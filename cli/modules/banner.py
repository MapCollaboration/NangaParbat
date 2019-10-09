import pyfiglet
from modules.bcolours import *

def banner():
    banner = banner = pyfiglet.figlet_format("NangaParbat", font = "slant")
    return bcolours.OKGREEN + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC

def reportbanner():
    banner = banner = pyfiglet.figlet_format("NangaParbat Report", font = "slant")
    return bcolours.ACTREPORT + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC
