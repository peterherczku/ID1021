set terminal pdf
set output './selection/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./selection/data.dat" using 1:2 with linespoints title 'Time'