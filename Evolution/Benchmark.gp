set term postscript enhanced color 'Times-Roman,18' size 10,5.83
set termopt enhanced

################################################################
set out "Benchmark.eps"

set xrange[0:10]

f(x) = 1

set key right top font 'Times-Roman,18'

set ylabel "APFEL++ / arTeMiDe" font 'Times-Roman,22'
set xlabel "b_T [1/GeV]" font 'Times-Roman,22'

set title "Evolution factors at {/Symbol @\326\140}{/Symbol z}_f = {/Symbol m}_f = M_Z ({/Symbol m}_i = {/Symbol m}_0), full NNLO"
set yrange[0.99:1.01]
plot "Benchmark.dat" index 0 u 1:($3/$9)  w l lt 7 lw 5 lc rgb "red"  t "R_g", \
     "Benchmark.dat" index 0 u 1:($4/$10) w l lt 7 lw 5 lc rgb "blue" t "R_q", \
     f(x) w l lt 4 lc rgb "black" notitle

set title "TMD PDFs at {/Symbol @\326\140}{/Symbol z}_f = {/Symbol m}_f = M_Z ({/Symbol m}_i = {/Symbol m}_0), x = 0.139, full NNLO"
set yrange[0.98:1.02]
plot "Benchmark.dat" index 0 u 1:($6/$12) w l lt 7 lw 5 lc rgb "blue"       t "Singlet", \
     "Benchmark.dat" index 0 u 1:($7/$13) w l lt 7 lw 5 lc rgb "orange"     t "Total valence", \
     "Benchmark.dat" index 0 u 1:($8/$14) w l lt 7 lw 5 lc rgb "dark-green" t "T_3", \
     f(x) w l lt 4 lc rgb "black" notitle

set yrange[0.2:1.5]
plot "Benchmark.dat" index 0 u 1:($5/$11) w l lt 7 lw 5 lc rgb "red"        t "Gluon", \
     f(x) w l lt 4 lc rgb "black" notitle

set yrange[0.98:1.02]
set title "TMD PDFs at {/Symbol @\326\140}{/Symbol z}_f = {/Symbol m}_f = M_Z ({/Symbol m}_i = {/Symbol m}_0), x = 0.139, NLO matching"
set yrange[0.98:1.02]
plot "Benchmark.dat" index 0 u 1:($15/$19) w l lt 7 lw 5 lc rgb "red"        t "Gluon", \
     "Benchmark.dat" index 0 u 1:($16/$20) w l lt 7 lw 5 lc rgb "blue"       t "Singlet", \
     "Benchmark.dat" index 0 u 1:($17/$21) w l lt 7 lw 5 lc rgb "orange"     t "Total valence", \
     "Benchmark.dat" index 0 u 1:($18/$22) w l lt 7 lw 5 lc rgb "dark-green" t "T_3", \
     f(x) w l lt 4 lc rgb "black" notitle

set ylabel "NLO / NNLO matching" font 'Times-Roman,22'
set title "Gluon TMD PDFs at {/Symbol @\326\140}{/Symbol z}_f = {/Symbol m}_f = M_Z ({/Symbol m}_i = {/Symbol m}_0), x = 0.139"
set yrange[0.5:1.2]
plot "Benchmark.dat" index 0 u 1:($19/$11) w l lt 7 lw 5 lc rgb "red"  t "arTeMiDe", \
     "Benchmark.dat" index 0 u 1:($15/$5)  w l lt 7 lw 5 lc rgb "blue" t "APFEL++",\
     f(x) w l lt 4 lc rgb "black" notitle

set ylabel "APFEL++ / arTeMiDe" font 'Times-Roman,22'
set title "Drell-Yan at {/Symbol @\326\140}s = 8 TeV, y = 2.5, Q = M_Z, narrow-width approximation, full NNLO"
set xrange[1:30]
set yrange[0.95:1.1]
set xlabel "q_T [GeV]" font 'Times-Roman,22'
plot "Benchmark.dat" index 1 u 1:($2/$3) w l lt 7 lw 5 lc rgb "red" t "d{/Symbol s}/dyd(q_T^2) [pb/GeV^2]", \
     f(x) w l lt 4 lc rgb "black" notitle

