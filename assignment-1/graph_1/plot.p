set terminal pdf
set output './graph_1/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./graph_1/data.dat" using 1:2 with linespoints title 'Min Time', \
     "./graph_1/data.dat" using 1:3 with linespoints title 'Max Time', \
     "./graph_1/data.dat" using 1:4 with linespoints title 'Avg Time'

set logscale x 10

set output './graph_1/data_2.pdf'
plot "./graph_1/data.dat" using 1:2 with linespoints title 'Min Time', \
     "./graph_1/data.dat" using 1:3 with linespoints title 'Max Time', \
     "./graph_1/data.dat" using 1:4 with linespoints title 'Avg Time'