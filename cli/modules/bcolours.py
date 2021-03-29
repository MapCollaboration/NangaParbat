# Colours from: http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#16-colors

class bcolours:
    HEADER     = "\033[95m"
    OKBLUE     = "\033[94m"
    OKGREEN    = "\033[92m"
    WARNING    = "\033[93m"
    FAIL       = "\033[91m"
    ENDC       = "\033[0m"
    BOLD       = "\033[1m"
    UNDERLINE  = "\033[4m"

    BMAGENTA   = "\u001b[31;1m"
    BYELLOW    = "\u001b[33;1m"
    BBLUE      = "\u001b[34;1m"
    LPINK      = "\u001b[38;5;210m"
    LORANGE    = "\u001b[38;5;208m"
    GIULIA     = "\u001b[38;5;199m"
    LBLUE      = "\u001b[38;5;$123m"
    ANSWERBLUE = "\u001b[38;5;$32m"

    # Set colors for the NangaParbat Report cli
    REPORT     = LPINK
    ACTREPORT  = LORANGE

# Plot's colors, from https://www.colorhexa.com
    borgogna        = "#660033"
    tangerineyellow = "#ffcc00"
    celestial       = "#00b3ff"
    meadow          = "#669900"
    seablue         = "#00c4b4"
    answerblue      = "#2196f3"

# Color blind palette,
# from https://davidmathlogic.com/colorblind/#%23648FFF-%23785EF0-%23DC267F-%23FE6100-%23FFB000
    pal_blue    = "#648FFF"
    pal_teal    = "#785EF0"
    pal_red     = "#DC267F"
    pal_orange  = "#FE6100"
    pal_yellow  = "#FFB000"

########## To change the question's style and colors:
# from: https://codeburst.io/building-beautiful-command-line-interfaces-with-python-26c7e1bb54df

# from PyInquirer import style_from_dict, Token
#
# style = style_from_dict({
#     Token.QuestionMark: '#E91E63 bold',
#     Token.Selected: '#673AB7 bold',
#     Token.Instruction: '',  # default
#     Token.Answer: '#2196f3 bold',
#     Token.Question: '',
# })
#
# answers = prompt(questions, style = style)
