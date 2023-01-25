#!/usr/bin/env python3
import yaml
import string
from tempfile import mkstemp
from shutil import move
from os import fdopen, remove

# Read fiducial cross-section file
with open("FiducialCrossSections.yaml", 'r') as stream:
    factors = yaml.safe_load(stream)

# Replace relevant line in the interpolation table
for exp in factors:
    for f in factors[exp]:
        print("Replacing factor in " + f["file"])

        # Create temp file
        fh, abs_path = mkstemp()
        with fdopen(fh, "w") as new_file:
            line_index = 9
            lines = None
            with open(f["file"]) as old_file:
                lines = old_file.readlines()

            #del lines[line_index]
            lines.insert(line_index, '\n')
            lines.insert(line_index, 'prefactor2: ' + str(f["fidcs"]))

            with open(f["file"]) as old_file:
                new_file.writelines(lines)
                #for line in old_file:
                    #if "prefactor" in line:
                        #line=line.replace(line,line+"NEW_TEXT")
                    #new_file.write(line.replace("prefactor", "prefactor" + str(f["fidcs"])))
                    #with open("path_to_file", "r") as f:
                #contents = f.readlines()

            #contents.insert(6, Eccolo)

            #with open("path_to_file", "w") as old_file:
            #        contents = "".join(contents)
            #        f.write(contents)

        # Remove original file
        remove(f["file"])

        # Move new file
        move(abs_path, f["file"])
