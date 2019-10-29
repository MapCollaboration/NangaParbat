#!/bin/bash
#
#SBATCH --job-name=NPfit
#SBATCH --output=output.txt
#SBATCH --array=0-300
#SBATCH --partition=12hr

srun /home/bertone/Codes/NangaParbat/cli/../run/RunFit /home/bertone/Codes/NangaParbat/cli/../run/../testPV19/ /home/bertone/Codes/NangaParbat/cli/../run/../testPV19/fitconfig.yaml /home/bertone/Codes/NangaParbat/cli/../run/../testPV19/data /home/bertone/Codes/NangaParbat/cli/../run/../testPV19/tables $SLURM_ARRAY_TASK_ID n n
