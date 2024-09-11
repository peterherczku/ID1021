set terminal pdf
set output './linear_sorted_with_optimization/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in ns"

plot "./linear_sorted_with_optimization/data.dat" using 1:2 with linespoints title 'Time'