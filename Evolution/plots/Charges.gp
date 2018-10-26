set term postscript enhanced color 'Times-Roman,18' size 10,5.83
set termopt enhanced

################################################################
set out "Charges.eps"

set xrange[50:200]
set yrange[0.00001:0.1]
set logscale y

set key right top font 'Times-Roman,18'

set ylabel "Electroweak charges" font 'Times-Roman,22'
set xlabel "Q [GeV]" font 'Times-Roman,22'

plot "Charges.dat" index 0 u 1:2 w l lt 7 lw 5 lc rgb "blue" t "Down", \
     "Charges.dat" index 0 u 1:3 w l lt 7 lw 5 lc rgb "red"  t "Up"     
