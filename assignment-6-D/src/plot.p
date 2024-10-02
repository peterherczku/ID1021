set terminal pdf
set output './src/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in ns"
set yrange [0:25]

plot "./src/data.dat" using 1:2 with linespoints title 'Time'