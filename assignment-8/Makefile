all: report.pdf
report.pdf: report.tex ./int_zip/data.dat ./improved/data.dat ./buckets/data.dat ./string_zip/data.dat ./key_index/data.dat ./collisions/data.dat
	pdflatex -shell-escape report.tex

./improved/data.dat: ./improved/a.out
	./improved/a.out > ./improved/data.dat

./improved/a.out: ./improved/main.c
	gcc ./improved/main.c -lm -o ./improved/a.out

./buckets/data.dat: ./buckets/a.out
	./buckets/a.out > ./buckets/data.dat

./buckets/a.out: ./buckets/main.c
	gcc ./buckets/main.c -lm -o ./buckets/a.out

./collisions/data.dat: ./collisions/a.out
	./collisions/a.out > ./collisions/data.dat

./collisions/a.out: ./collisions/main.c
	gcc ./collisions/main.c -lm -o ./collisions/a.out

./key_index/data.dat: ./key_index/a.out
	./key_index/a.out > ./key_index/data.dat

./key_index/a.out: ./key_index/main.c
	gcc ./key_index/main.c -lm -o ./key_index/a.out

./int_zip/data.dat: ./int_zip/a.out
	./int_zip/a.out > ./int_zip/data.dat

./int_zip/a.out: ./int_zip/main.c
	gcc ./int_zip/main.c -lm -o ./int_zip/a.out

./string_zip/data.dat: ./string_zip/a.out
	./string_zip/a.out > ./string_zip/data.dat

./string_zip/a.out: ./string_zip/main.c
	gcc ./string_zip/main.c -lm -o ./string_zip/a.out