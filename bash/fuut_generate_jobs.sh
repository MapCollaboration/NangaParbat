
# Folder to use (results of the fit)
fitfolder="tRep105"

# TMD PDF grids name 
TMDPDFgrids="grid_pdf"

# TMDFF grids name                                                                                                                                    
TMDFFgrids="grid_ff_Pip"

# output name
Output="grid_FUUT"

# ------------------------------------------------------------------

for (( i=105; i<106; i++ ))
do
    rm -f job_$i.sh
    echo "#!/bin/bash "                               >> job_$i.sh
    echo "#SBATCH --job-name=grid_fuut_$i "           >> job_$i.sh
    echo "#SBATCH -p 1week "                          >> job_$i.sh
    echo "#SBATCH -o grid_fuut_$i.txt "               >> job_$i.sh
    echo "#SBATCH -e errors.txt "                     >> job_$i.sh

    
    echo mkdir Replica_$i                                                              >> job_$i.sh
    echo mkdir Replica_$i/tables                                                       >> job_$i.sh
    echo cp ../FitResults/$fitfolder/tables/config.yaml Replica_$i/tables/             >> job_$i.sh
    echo cp ../FitResults/$fitfolder/fitconfig.yaml Replica_$i/                        >> job_$i.sh
    echo cp -R ../FitResults/$fitfolder/replica_$i Replica_$i/                         >> job_$i.sh
    echo "./../tests/FUUTGridProduction ../FitResults/${fitfolder} ${TMDPDFgrids} ${TMDFFgrids} ${Output}"          >> job_$i.sh
done

# ------------------------------------------------------------------
## example: cycle on job names
#jobnames=(name1 name2 name3)
#for i in ${jobnames[@]}
#do
#done
