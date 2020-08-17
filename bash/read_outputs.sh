
# Folder to put the grids (path)
fitfolder="../FitResults/PV17_NLL"

# TMDs for which the grids have been created
#TMDtype="pdf"
TMDtype="ff"

# hadron for FF for which the grids have been created
#had="Pip"
had="Pim"
#had="Kp"
#had="Km"

# -----------------------------------------------------------------------------------

# name of the grid AND the folder
if [ "$TMDtype" == "pdf" ]; then
    gridname="grid_${TMDtype}"
fi
if [ "$TMDtype" == "ff" ]; then
    gridname="grid_${TMDtype}_${had}"
fi

# path of the folder where to put the outputs
gridfolder=${fitfolder}/${gridname}

# Create directory to put the grids
mkdir $gridfolder

# Get info file (from replica zero, for example)
cp Replica_0/${gridname}/*.info $gridfolder/${gridname}.info
#mv Replica_0/${gridname}/*.info $gridfolder/

# Get replicas
for (( i=0; i<300; i++ ))
do
    iiii=`printf %04d $i`
    cp -r Replica_$i/${gridname}/*_${iiii}.yaml $gridfolder/${gridname}_${iiii}.yaml
done

# ------------------------------------------------------------------------------------

: '
***
This is a multiline comment in bash.
Example to produce padded numbers with 4 digits:

for (( i=0; i<=3; i++))
do
    iiii=`printf %04d $i`
    echo $iiii
done

For 3 digits, i.e. 001,`printf %03d $i` .
***
'
