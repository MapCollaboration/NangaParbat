for (( i=0; i<=3; i++))
do
    iiii=`printf %04d $i`
    echo $iiii
done

: '
# Example to produce padded numbers with 4 digits

for (( i=0; i<=2; i++))
do
    iiii=`printf %04d $i`
    echo prova
done
'
