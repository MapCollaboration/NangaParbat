#!/bin/bash
#
#SBATCH --job-name=NPfit
#SBATCH --output=output.txt
#SBATCH --array=0-300
#SBATCH --partition=12hr

srun /home/bissolotti/Codes/NangaParbat/cli/../run/RunFit /home/bissolotti/Codes/NangaParbat/cli/../run/../N2PV19x4BMfix/ /home/bissolotti/Codes/NangaParbat/cli/../run/../N2PV19x4BMfix/fitconfig.yaml /home/bissolotti/Codes/NangaParbat/cli/../run/../N2PV19x4BMfix/data /home/bissolotti/Codes/NangaParbat/cli/../run/../N2PV19x4BMfix/tables $SLURM_ARRAY_TASK_ID y n
