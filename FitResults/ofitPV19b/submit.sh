#!/bin/bash
#
#SBATCH --job-name=NPfit
#SBATCH --output=output.txt
#SBATCH --array=0-300
#SBATCH --partition=12hr

srun /home/bissolotti/Codes/NangaParbat/cli/../run/RunFit /home/bissolotti/Codes/NangaParbat/cli/../run/../ofitPV19b/ /home/bissolotti/Codes/NangaParbat/cli/../run/../ofitPV19b/fitconfig.yaml /home/bissolotti/Codes/NangaParbat/cli/../run/../ofitPV19b/data /home/bissolotti/Codes/NangaParbat/cli/../run/../ofitPV19b/tables $SLURM_ARRAY_TASK_ID y n
