set terminal pdf
set output './binary_search/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in ns"

plot "./binary_search/data.dat" using 1:2 with linespoints title 'Time'