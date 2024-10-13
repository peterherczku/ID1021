all: report.pdf
report.pdf: report.tex ./src/a.out
	pdflatex -shell-escape report.tex

./src/a.out: ./src/main.c
	gcc ./src/main.c ./src/queue.c -lm -o ./src/a.out