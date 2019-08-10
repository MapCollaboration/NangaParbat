from PyInquirer import Validator, ValidationError
import os

# Validators
class OutputFolderValidator(Validator):
    def validate(self, document):
        dir = os.path.dirname(os.path.realpath(__file__)) + "/" + document.text
        exists = os.path.isdir(dir)
        if exists:
            raise ValidationError(message = "The folder '" + document.text + "' already exists", cursor_position = len(document.text))

class NotOutputFolderValidator(Validator):
    def validate(self, document):
        dir = os.path.dirname(os.path.realpath(__file__)) + "/../" + document.text
        exists = os.path.isdir(dir)
        if not exists:
            os.listdir()
            raise ValidationError(message = "The folder '" + document.text + "' does not exists", cursor_position = len(document.text))

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
