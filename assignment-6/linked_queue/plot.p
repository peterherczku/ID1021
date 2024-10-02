set terminal pdf
set output './linked_queue/enqueue.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"

plot "./linked_queue/data.dat" using 1:2 with linespoints title 'Time'

set output './linked_queue/dequeue.pdf'
set xlabel "n"
set ylabel "time in ns"
set yrange [0:25]
plot "./linked_queue/data.dat" using 1:3 with linespoints title 'Time'