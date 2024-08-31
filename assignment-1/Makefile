all: report.pdf

report.pdf: report.tex ./graph_1/data.pdf ./graph_1/data_2.pdf ./median/data.pdf ./search/data.pdf ./duplicates/data.pdf
	pdflatex -shell-escape report.tex

./duplicates/data.pdf: ./duplicates/data.dat
	gnuplot ./duplicates/plot.p

./duplicates/data.dat: ./duplicates/a.out
	./duplicates/a.out > ./duplicates/data.dat

./duplicates/a.out: ./duplicates/main.c
	gcc ./duplicates/main.c -lm -o ./duplicates/a.out

./search/data.pdf: ./search/data.dat
	gnuplot ./search/plot.p

./search/data.dat: ./search/a.out
	./search/a.out > ./search/data.dat

./search/a.out ./search/main.c:
	gcc ./search/main.c -lm -o ./search/a.out

./median/data.pdf: ./median/data.dat
	gnuplot ./median/plot.p

./median/data.dat: ./median/a.out
	./median/a.out > ./median/data.dat

./median/a.out: ./median/main.c
	gcc ./median/main.c -lm -o ./median/a.out

./graph_1/data_2.pdf: ./graph_1/data.dat
	gnuplot ./graph_1/plot.p

./graph_1/data.pdf: ./graph_1/data.dat
	gnuplot ./graph_1/plot.p

./graph_1/data.dat: ./graph_1/a.out
	./graph_1/a.out > ./graph_1/data.dat

./graph_1/a.out: ./graph_1/main.c
	gcc ./graph_1/main.c -lm -o ./graph_1/a.out