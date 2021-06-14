#!/usr/bin/env python3
import yaml
import string
from tempfile import mkstemp
from shutil import move
from os import fdopen, remove

# Read fiducial cross-section file
with open("FiducialCrossSectionsAle1.yaml", 'r') as stream:
    factors = yaml.safe_load(stream)

# Replace relevant line in the interpolation table
for exp in factors:
    for f in factors[exp]:
        print("Replacing factor in " + f["file"])

        # Create temp file
        fh, abs_path = mkstemp()
        with fdopen(fh, "w") as new_file:
            with open(f["file"]) as old_file:
                for line in old_file:
                    new_file.write(line.replace("prefactor2: 1", "prefactor2: " + str(f["fidcs"])))

        # Remove original file
        remove(f["file"])

        # Move new file
        move(abs_path, f["file"])
