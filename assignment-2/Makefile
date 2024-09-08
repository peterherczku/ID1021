all: report.pdf
report.pdf: report.tex ./static/data.pdf
	pdflatex -shell-escape report.tex

./static/data.pdf: ./static/data.dat
	gnuplot ./static/plot.p

./static/data.dat: ./static/a.out
	./static/a.out > ./static/data.dat

./static/a.out: ./static/main.c
	gcc ./static/main.c -lm -o ./static/a.out
