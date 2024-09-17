set terminal pdf
set output './merge/data.pdf'

set title ""

set xlabel "n"
set ylabel "time in us"
set xtics ("1×10^5" 100000, "2×10^5" 200000, "3×10^5" 300000, "4×10^5" 400000, "5×10^5" 500000, "6×10^5" 600000, "7×10^5" 700000, "8×10^5" 800000, "9×10^5" 900000)

f(x) = x*a*log(x)+c
g(x) = a*x + c

fit f(x) './merge/data.dat' using 1:2 via a, c
plot "./merge/data.dat" using 1:2 with linespoints title 'Time', \
    f(x) title 'Logarithmic Fit' with lines lt rgb 'grey'