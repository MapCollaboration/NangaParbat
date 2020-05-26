for f in Report_*.yaml
do
    dir="$(echo $f | sed s/Report/replica/ | sed s/.yaml//g)"
    mkdir ../"$dir"
    cp -i "$f" ../$dir/Report.yaml
done
