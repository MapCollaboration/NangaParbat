set term postscript enhanced color 'Times-Roman,18' size 10,5.83
set termopt enhanced

################################################################
set out "CrossSection.eps"

set xrange[0:31]
set yrange[0:0.02]

set key right top font 'Times-Roman,18'

set ylabel "d{/Symbol s}/dyqQdq_T [pb/GeV^2]" font 'Times-Roman,22'
set xlabel "q_T [GeV]" font 'Times-Roman,22'

set label 2 "Drell Yan distribution" at 15, 0.0175 font 'Times-Roman,20'
set label 3 "{/Symbol @\326\140}s = 13 TeV, Q = M_Z, y = 2.5" at 15, 0.016 font 'Times-Roman,20'

plot "CrossSection.dat" index 0 u 1:2 w l lt 7 lw 5 lc rgb "red" t "APFEL++"
