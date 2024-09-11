all: report.pdf
report.pdf: report.tex ./binary_recursive/data.pdf ./binary_search/data.pdf ./linear_sorted_with_optimization/data.pdf ./unsorted/data.pdf
	pdflatex -shell-escape report.tex

./binary_recursive/data.pdf: ./binary_recursive/data.dat
	gnuplot ./binary_recursive/plot.p

./binary_recursive/data.dat: ./binary_recursive/a.out
	./binary_recursive/a.out > ./binary_recursive/data.dat

./binary_recursive/a.out: ./binary_recursive/main.c
	gcc ./binary_recursive/main.c -lm -o ./binary_recursive/a.out

./binary_search/data.pdf: ./binary_search/data.dat
	gnuplot ./binary_recursive/plot.p

./binary_search/data.dat: ./binary_search/a.out
	./binary_search/a.out > ./binary_search/data.dat

./binary_search/a.out: ./binary_search/main.c
	gcc ./binary_search/main.c -lm -o ./binary_search/a.out

./linear_sorted_with_optimization/data.pdf: ./linear_sorted_with_optimization/data.dat
	gnuplot ./linear_sorted_with_optimization/plot.p

./linear_sorted_with_optimization/data.dat: ./linear_sorted_with_optimization/a.out
	./linear_sorted_with_optimization/a.out > ./linear_sorted_with_optimization/data.dat

./linear_sorted_with_optimization/a.out: ./linear_sorted_with_optimization/main.c
	gcc ./linear_sorted_with_optimization/main.c -lm -o ./linear_sorted_with_optimization/a.out

./unsorted/data.pdf: ./unsorted/data.dat
	gnuplot ./binary_recursive/plot.p

./unsorted/data.dat: ./unsorted/a.out
	./unsorted/a.out > ./unsorted/data.dat

./unsorted/a.out: ./unsorted/main.c
	gcc ./unsorted/main.c -lm -o ./unsorted/a.out
