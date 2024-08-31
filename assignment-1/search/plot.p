set terminal pdf
set output './search/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./search/data.dat" using 1:2 with linespoints title 'Minimum time'