#!/bin/bash
#
#SBATCH --job-name=NPfit
#SBATCH --output=output.txt
#SBATCH --array=0-300
#SBATCH --partition=12hr

srun /home/bertone/Codes/NangaParbat/cli/../run/RunFit /home/bertone/Codes/NangaParbat/cli/../run/../PV19x_N3LL/ /home/bertone/Codes/NangaParbat/cli/../run/../PV19x_N3LL/fitconfig.yaml /home/bertone/Codes/NangaParbat/cli/../run/../PV19x_N3LL/data /home/bertone/Codes/NangaParbat/cli/../run/../PV19x_N3LL/tables $SLURM_ARRAY_TASK_ID
