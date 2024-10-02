all: report.pdf
report.pdf: report.tex ./src/data.pdf
	pdflatex -shell-escape report.tex

./src/data.pdf: ./src/data.dat ./src/plot.p
	gnuplot ./src/plot.p

./src/data.dat: ./src/a.out
	./src/a.out > ./src/data.dat

./src/a.out: ./src/main.c
	gcc ./src/main.c -lm -o ./src/a.out