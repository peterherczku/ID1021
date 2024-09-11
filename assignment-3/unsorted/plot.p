set terminal pdf
set output './unsorted/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in ns"

plot "./unsorted/data.dat" using 1:2 with linespoints title 'Time'