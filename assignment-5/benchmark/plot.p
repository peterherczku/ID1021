set terminal pdf
set output './benchmark/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./benchmark/data.dat" using 1:2 with linespoints title 'Time'