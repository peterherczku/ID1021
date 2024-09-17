set terminal pdf
set output './insertion/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./insertion/data.dat" using 1:2 with linespoints title 'Time'