set terminal pdf
set output './duplicates/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./duplicates/data.dat" using 1:2 with linespoints title 'Minimum Time'