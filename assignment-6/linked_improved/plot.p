set terminal pdf
set output './linked_improved/enqueue.pdf'

set title ""

set xlabel "n"
set ylabel "time in ns"
set yrange [0:25]

plot "./linked_improved/data.dat" using 1:2 with linespoints title 'Time'