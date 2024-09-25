all: report.pdf
report.pdf: report.tex ./benchmark/data.pdf ./reverse_append/data.pdf
	pdflatex -shell-escape report.tex

./benchmark/data.pdf: ./benchmark/data.dat ./benchmark/plot.p
	gnuplot ./benchmark/plot.p

./benchmark/data.dat: ./benchmark/a.out
	./benchmark/a.out > ./benchmark/data.dat

./benchmark/a.out: ./benchmark/main.c
	gcc ./benchmark/main.c -lm -o ./benchmark/a.out

./reverse_append/data.pdf: ./reverse_append/data.dat ./reverse_append/plot.p
	gnuplot ./reverse_append/plot.p

./reverse_append/data.dat: ./reverse_append/a.out
	./reverse_append/a.out > ./reverse_append/data.dat

./reverse_append/a.out: ./reverse_append/main.c
	gcc ./reverse_append/main.c -lm -o ./reverse_append/a.out