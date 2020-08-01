
# Folder to use (results of the fit)
fitfolder="PV17_NLL"

# TMDs to grid
#TMDtype="pdf"
TMDtype="ff"

# hadron for FF
had="Pip"
#had="Pim"
#had="Kp"
#had="Km"

# ------------------------------------------------------------------

# name of the grid AND the folder
if [ "$TMDtype" == "pdf" ]; then
    gridname="grid_${TMDtype}"
fi
if [ "$TMDtype" == "ff" ]; then
    gridname="grid_${TMDtype}_${had}"
fi


for (( i=0; i<300; i++ ))
do
    rm -f job_$i.sh
    echo "#!/bin/bash "                               >> job_$i.sh
    echo "#SBATCH --job-name=grid_${TMDtype}_$i "     >> job_$i.sh
    
    if [ "${TMDtype}" == "pdf" ]; then
        echo "#SBATCH -p 2hr "                        >> job_$i.sh
    fi
    if [ "${TMDtype}" == "ff" ]; then
        echo "#SBATCH -p 12hr "                       >> job_$i.sh
    fi
    
    echo "#SBATCH -o grid_${TMDtype}_$i.txt "         >> job_$i.sh
    echo "#SBATCH -e errors.txt "                     >> job_$i.sh

    
    echo mkdir Replica_$i                                                              >> job_$i.sh
    echo mkdir Replica_$i/tables                                                       >> job_$i.sh
    echo cp ../FitResults/$fitfolder/tables/config.yaml Replica_$i/tables/             >> job_$i.sh
    echo cp ../FitResults/$fitfolder/fitconfig.yaml Replica_$i/                        >> job_$i.sh
    echo cp -R ../FitResults/$fitfolder/replica_$i Replica_$i/                         >> job_$i.sh
    echo "./../run/CreateGrids Replica_$i $TMDtype ${gridname}"                        >> job_$i.sh
    
done

# ------------------------------------------------------------------
## example: cycle on job names
#jobnames=(name1 name2 name3)
#for i in ${jobnames[@]}
#do
#done
