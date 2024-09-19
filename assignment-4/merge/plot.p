set terminal pdf
set output './merge/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./merge/data.dat" using 1:2 with linespoints title 'Time'