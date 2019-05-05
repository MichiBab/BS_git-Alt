# file makefile

.PHONY: clean

all: projekt

projekt: dirs projektHallo projektHaw projektBs clean

dirs: 
	mkdir -p bin
	mkdir -p obj
	mkdir -p test

projektHallo: obj/hallo.o obj/print.o
	gcc $^ -o test/$@

projektHaw: obj/print.o obj/haw.o 
	gcc $^ -o test/$@

projektBs: obj/print.o obj/bs.o 
	gcc $^ -o test/$@

obj/hallo.o: src/hallo.c
	gcc -c src/hallo.c 
	mv hallo.o obj/

obj/bs.o: src/bs.c
	gcc -c src/bs.c 
	mv bs.o obj/

obj/haw.o: src/haw.c
	gcc -c src/haw.c 
	mv haw.o obj/

obj/print.o: src/print.c
	gcc -c src/print.c
	mv print.o obj/

install:
	cp test/* bin/

clean:
	rm -f obj/*

