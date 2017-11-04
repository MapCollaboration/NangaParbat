set term postscript enhanced color 'Times-Roman,18' size 10,5.83
set termopt enhanced

################################################################
set out "Qdist.eps"

set xrange[20:200]
set yrange[0.000001:0.5]
set logscale y

set key right top font 'Times-Roman,18'

set ylabel "d{/Symbol s}/dyqQd(q_T^2) [pb/GeV^3]" font 'Times-Roman,22'
set xlabel "Q [GeV]" font 'Times-Roman,22'

set title "Drell Yan distribution, {/Symbol @\326\140}s = 13 TeV, y = 0, q_T = 5 GeV, APFEL++" font 'Times-Roman,20'

plot "Qdist.dat" index 0 u 1:3 w l lt 7 lw 5 lc rgb "blue"       t "{/Symbol gg} contribution", \
     "Qdist.dat" index 0 u 1:4 w l lt 7 lw 5 lc rgb "orange"     t "ZZ contribution", \
     "Qdist.dat" index 0 u 1:5 w l lt 7 lw 5 lc rgb "dark-green" t "{/Symbol g}Z contribution", \
     "Qdist.dat" index 0 u 1:2 w l lt 7 lw 5 lc rgb "red"        t "Total"
     
