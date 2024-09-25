set terminal pdf
set output './reverse_append/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"
set yrange [0:15]

plot "./reverse_append/data.dat" using 1:2 with linespoints title 'Time'