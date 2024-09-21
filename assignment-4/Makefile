all: report.pdf
report.pdf: report.tex ./selection/data.pdf ./insertion/data.pdf ./merge/data.pdf ./insertion_inline/data.pdf
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

./insertion_inline/data.pdf: ./insertion_inline/data.dat ./insertion_inline/plot.p
	gnuplot ./insertion_inline/plot.p

./insertion_inline/data.dat: ./insertion_inline/a.out
	./insertion_inline/a.out > ./insertion_inline/data.dat

./insertion_inline/a.out: ./insertion_inline/main.c
	gcc ./insertion_inline/main.c -lm -o ./insertion_inline/a.out

./merge/data.pdf: ./merge/data.dat ./merge/plot.p
	gnuplot ./merge/plot.p

./merge/data.dat: ./merge/a.out
	./merge/a.out > ./merge/data.dat

./merge/a.out: ./merge/main.c
	gcc ./merge/main.c -lm -o ./merge/a.out