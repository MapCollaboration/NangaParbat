import pyfiglet
from bcolours import *

def banner():
    banner = banner = pyfiglet.figlet_format("NangaParbat", font = "slant")
    return bcolours.OKGREEN + bcolours.BOLD + "\nWelcome to:\n" + banner + bcolours.ENDC
