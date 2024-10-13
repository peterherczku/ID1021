set terminal pdf
set output './src/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./src/data.dat" using 1:2 with linespoints title 'Time'