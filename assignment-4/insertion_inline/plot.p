set terminal pdf
set output './insertion_inline/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./insertion_inline/data.dat" using 1:2 with linespoints title 'Time'