set terminal pdf
set output './median/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./median/data.dat" using 1:2 with linespoints title 'Median Time'