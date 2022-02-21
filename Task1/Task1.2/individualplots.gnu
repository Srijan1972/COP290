set title "Runtime for MKL at different values of n,m,k"
set xlabel "n*m*k"
set ylabel "Time in ns"
set term png
set output "mklplot.png"
plot [0:4000000] [0:500000] 'mklplot.txt' with yerrorbars
set terminal qt

set xrange [0:4000000]
set yrange [0:20000000]
set title "Runtime for openblas at different values of n,m,k"
set xlabel "n*m*k"
set ylabel "Time in ns"
set term png
set output "openblasplot.png"
plot [0:4000000] [0:15000000] 'openblasplot.txt' with yerrorbars
set terminal qt

set xrange [0:4000000]
set yrange [0:20000000]
set title "Runtime for pthread at different values of n,m,k"
set xlabel "n*m*k"
set ylabel "Time in ns"
set term png
set output "pthreadplot.png"
plot [0:4000000] [0:15000000] 'pthreadplot.txt' with yerrorbars
set terminal qt