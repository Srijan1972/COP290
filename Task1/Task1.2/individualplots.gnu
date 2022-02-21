set xrange [0:1000000000]
set yrange [0:2000000]
set title "Runtime for MKL at different values of n,m,k"
set xlabel "n*m*k"
set ylabel "Time in ns"
set term png
set output "mklplot.png"
plot 'mklplot.txt' using 1:2:3 with yerrorbars
set terminal qt

set xrange [0:1000000000]
set yrange [0:2000000]
set title "Runtime for openblas at different values of n,m,k"
set xlabel "n*m*k"
set ylabel "Time in ns"
set term png
set output "openblasplot.png"
plot 'openblasplot.txt' using 1:2:3 with yerrorbars
set terminal qt

set xrange [0:1000000000]
set yrange [0:2000000]
set title "Runtime for pthread at different values of n,m,k"
set xlabel "n*m*k"
set ylabel "Time in ns"
set term png
set output "pthreadplot.png"
plot 'pthreadplot.txt' using 1:2:3 with yerrorbars
set terminal qt