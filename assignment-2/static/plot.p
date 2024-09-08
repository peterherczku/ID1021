set terminal pdf
set output './static/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in ns"

plot "./static/data.dat" using 1:2 with linespoints title 'Time'