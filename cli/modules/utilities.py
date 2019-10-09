from modules.bcolours import *
from collections import OrderedDict

def GetPertOrd(pertord):
    """
    Transforms the number of the perturbative order in the relative string.
    Input and output are string.
    If the input is not a string GetPertOrd() tries to convert it into the
    right format.
    """
    # Check that 'pertord' is a string, if not try to convert it.
    if type(pertord) is not str:
        print(bcolours.WARNING + "TypeError: the argument of GetPertOrd must be a string." + bcolours.ENDC)
        print(bcolours.WARNING + "Trying to convert it to a string." + bcolours.ENDC)
        pertord = str(pertord)

    # Check if the conversion succeded
    try:
        str(pertord)
    except:
        print(bcolours.FAIL + "Conversion failed. " + bcolours.ENDC)

    # Define the transition from number to name of the perturbative order
    stringord = ""
    if pertord == "1":
      stringord = "NLL"
    if pertord == "2":
      stringord = "NNLL"
    if pertord == "3":
      stringord = "N3LL"
    if pertord == "-1":
      stringord = "NLLp"
    if pertord == "-2":
      stringord = "NNLLp"
    return stringord

def GetLatexFormula(param):
    """
    Function to get the formula of the chosen parameterisation chosen in latex format.
    Returns an OrderedDict().
    param   --- String, name of the parameterisation.
    """
    if param == "PV19":
        latexformula = OrderedDict([("parameterisation","$$f_{\\rm NP}(x,\\zeta, b_T)=\\frac{\\exp\\left[ - \\frac{1}{2} g_2 \\log\\left(\\frac{\\zeta}{Q_0^2}\\right) b_T^2 \\right]}{1 + g_1^2(x) b_T^2}$$"),("g1","$$g_1(x) = N_1 \\frac{x^{\\sigma}(1-x)^{\\alpha}}{\\hat{x}^{\\sigma}(1-\\hat{x})^{\\alpha}}$$"),("Q02","$$Q_0^2 = 1\\;{\\rm GeV}^2$$"),("xhat","$$\\hat{x} = 0.1$$")])
    else:
        latexformula = OrderedDict([("empty", "latex formula not avaliable yet")])
        print(bcolours.WARNING + "Latex formula for this parameterisation not yet avaliable" + bcolours.ENDC)

    return latexformula

def GetLatexNames(rows):
    """
    Function to get the Latex format of the parameters name from the fitconfig.
    rows  --- Tuple of strings. The elements of this tuple will be converted into latex formulas.
    """
    for l, elemrows in enumerate(rows):
        elemrows = list(elemrows)
        if l == 0:
            elemrows[0] = "$g_2$"
        if l == 1:
            elemrows[0] = "$N_1$"
        if l > 1:
            elemrows[0] = "$\\" + elemrows[0] + "$"
        elemrows = tuple(elemrows)
        rows[l] = elemrows
    return rows

def TableOfInitialParameters(parameters):
    """
    Function to put initial parameters in the right format for the table in markdown.
    Returns headers and rows (in this order) for the table.
    parameters  --- OrderedDict (Yaml node). Parameters to put in the rows of the table.
    """
    headers = []
    rows = []
    for iter, v in enumerate(parameters):

        # unpack the OrderedDict
        headings, data = [x for x in zip(*parameters[iter].items())]

        ######## for as many tables as parameters:
        # put data and headings in the right format for the table
        # data = [data]
        # headings = [he for he in headings]
        # create one table for each parameter and put it in the markdown
        # writemarkdown.table(mdout, data, headings)

    ########### for only one table with all info:
        rows.append(data)
        headers = [he for he in headings]
    return headers, rows


def TableOfMeanChi2(replicafolder, outfolder):
    """
    Function to put the mean chi2 of the experiments in the right format for the
    table in markdown.
    Returns headers and rows (in this order) for the table.

    replicafolder ---  Folder of the report of the mean of the good replicas.
    outfolder     ---  String, is the folder where the output of the fit is stored.
    """
    headers = ["name", "# points ", "$\chi2$"]
    rows = []
    with open(outfolder + "/" + replicafolder + "/Report.yaml", "r") as meanrep:
        reportmeanrep = yaml.load(meanrep, Loader=yaml.RoundTripLoader)

        globalchi2mean = reportmeanrep["Global chi2"]
        totpoints = 0

        for expdata in reportmeanrep["Experiments"]:
            expname = expdata["Name"]

            npoints = len(expdata["Predictions"])
            totpoints += npoints

            pchi2 = expdata["partial chi2"]
            penaltychi2 = expdata["penalty chi2"]

            onerow = (expname, npoints, pchi2)
            rows.append(onerow)

        lastrow = ("Total", totpoints, globalchi2mean)
        rows.append(lastrow)
        
    return headers, rows
