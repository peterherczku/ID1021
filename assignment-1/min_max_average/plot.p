set terminal pdf
set output './min_max_average/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./min_max_average/data.dat" using 1:2 with linespoints title 'Min Time', \
     "./min_max_average/data.dat" using 1:3 with linespoints title 'Max Time', \
     "./min_max_average/data.dat" using 1:4 with linespoints title 'Avg Time'

set logscale x 10

set output './min_max_average/data_2.pdf'
plot "./min_max_average/data.dat" using 1:2 with linespoints title 'Min Time', \
     "./min_max_average/data.dat" using 1:3 with linespoints title 'Max Time', \
     "./min_max_average/data.dat" using 1:4 with linespoints title 'Avg Time'