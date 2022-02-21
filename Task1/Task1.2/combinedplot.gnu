set style fill solid 0.25 border -1
set style boxplot outliers pointtype 7
set style data boxplot
set xrange [0:4]
set yrange [0:9000000]
set title "Combined Plot- Runtime Comparison"
set xlabel "Implementation"
set ylabel "Runtime in ns"
set term png
set output "combinedplots.png"
plot for [i=1:3] 'combinedplot.txt' using (i):i notitle
set terminal qt
