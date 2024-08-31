all: report.pdf

report.pdf: report.tex ./min_max_average/data.pdf ./min_max_average/data_2.pdf ./median/data.pdf ./search/data.pdf ./duplicates/data.pdf
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

./min_max_average/data_2.pdf: ./min_max_average/data.dat
	gnuplot ./min_max_average/plot.p

./min_max_average/data.pdf: ./min_max_average/data.dat
	gnuplot ./min_max_average/plot.p

./min_max_average/data.dat: ./min_max_average/a.out
	./min_max_average/a.out > ./min_max_average/data.dat

./min_max_average/a.out: ./min_max_average/main.c
	gcc ./min_max_average/main.c -lm -o ./min_max_average/a.out