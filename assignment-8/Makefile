all: report.pdf
report.pdf: report.tex ./int_zip/data.dat ./string_zip/data.dat
	pdflatex -shell-escape report.tex

./int_zip/data.dat: ./int_zip/a.out
	./int_zip/a.out > ./int_zip/data.dat

./int_zip/a.out: ./int_zip/main.c
	gcc ./int_zip/main.c -lm -o ./int_zip/a.out

./string_zip/data.dat: ./string_zip/a.out
	./string_zip/a.out > ./string_zip/data.dat

./string_zip/a.out: ./string_zip/main.c
	gcc ./string_zip/main.c -lm -o ./string_zip/a.out