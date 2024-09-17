all: report.pdf
report.pdf: report.tex ./selection/data.pdf ./insertion/data.pdf
	pdflatex -shell-escape report.tex

./selection/data.pdf: ./selection/data.dat ./selection/plot.p
	gnuplot ./selection/plot.p

./selection/data.dat: ./selection/a.out
	./selection/a.out > ./selection/data.dat

./selection/a.out: ./selection/main.c
	gcc ./selection/main.c -lm -o ./selection/a.out

./insertion/data.pdf: ./insertion/data.dat ./insertion/plot.p
	gnuplot ./insertion/plot.p

./insertion/data.dat: ./insertion/a.out
	./insertion/a.out > ./insertion/data.dat

./insertion/a.out: ./insertion/main.c
	gcc ./insertion/main.c -lm -o ./insertion/a.out