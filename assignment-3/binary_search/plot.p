set terminal pdf
set output './binary_search/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in ns"

f(x) = a*log(x)+c

fit f(x) './binary_search/data.dat' using 1:2 via a, c

plot "./binary_search/data.dat" using 1:2 with linespoints title 'Time', \
                     f(x) title 'Logarithmic Fit' with lines lt rgb 'grey'