import banner
from PyInquirer import prompt
from examples import custom_style_3
from validators import *
import os

# Print banner
print(banner.banner())

# Folder containing the utilities
CliFolder = os.path.dirname(os.path.realpath(__file__))

# Create output folder
questions = [
    {
        "type": "input",
        "name": "Output folder",
        "message": "Type the name of the output folder:",
        "validate": NotOutputFolderValidator
    }
]
answers = prompt(questions, style=custom_style_3)
print(answers)
