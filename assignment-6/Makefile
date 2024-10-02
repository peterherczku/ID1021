all: report.pdf
report.pdf: report.tex ./linked_queue/enqueue.pdf ./linked_queue/dequeue.pdf ./linked_improved/enqueue.pdf
	pdflatex -shell-escape report.tex

./linked_queue/enqueue.pdf: ./linked_queue/data.dat ./linked_queue/plot.p
	gnuplot ./linked_queue/plot.p

./linked_queue/dequeue.pdf: ./linked_queue/data.dat ./linked_queue/plot.p
	gnuplot ./linked_queue/plot.p

./linked_queue/data.dat: ./linked_queue/a.out
	./linked_queue/a.out > ./linked_queue/data.dat

./linked_queue/a.out: ./linked_queue/main.c
	gcc ./linked_queue/main.c -lm -o ./linked_queue/a.out

./linked_improved/enqueue.pdf: ./linked_improved/data.dat ./linked_improved/plot.p
	gnuplot ./linked_improved/plot.p

./linked_improved/data.dat: ./linked_improved/a.out
	./linked_improved/a.out > ./linked_improved/data.dat

./linked_improved/a.out: ./linked_improved/main.c
	gcc ./linked_improved/main.c -lm -o ./linked_improved/a.out