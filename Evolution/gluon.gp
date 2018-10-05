set term postscript enhanced color 'Times-Roman,18' size 10,5.83
set termopt enhanced

################################################################
set out "gluon.eps"

set xrange[0:10]

f(x) = 1

set key right top font 'Times-Roman,18'

set ylabel "APFEL++ / arTeMiDe" font 'Times-Roman,22'
set xlabel "b_T [1/GeV]" font 'Times-Roman,22'


set title "TMD PDFs at the initial scale (no f_{NP}), x = 0.139, LO matching"
set yrange[0.995:1.005]
plot "gluon.dat" index 0 u 1:($3/$4) w l lt 7 lw 5 lc rgb "red"        t "Gluon", \
     f(x) w l lt 4 lc rgb "black" notitle

set title "TMD PDFs at the initial scale (no f_{NP}), x = 0.139, NLO matching"
plot "gluon.dat" index 1 u 1:($3/$4) w l lt 7 lw 5 lc rgb "red"        t "Gluon", \
     f(x) w l lt 4 lc rgb "black" notitle

set title "TMD PDFs at the initial scale (no f_{NP}), x = 0.139, NNLO matching"
set yrange[0.5:1.5]
plot "gluon.dat" index 2 u 1:($3/$4) w l lt 7 lw 5 lc rgb "red"        t "Gluon", \
     f(x) w l lt 4 lc rgb "black" notitle
