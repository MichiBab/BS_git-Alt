# file makefile
.PHONY: clean

##########
targets = obj/hallo.o obj/haw.o obj/bs.o obj/print.o
targetsMain = hallo.o haw.o bs.o
##########

all: dirs projekt clean

projekt: $(targets) $(targetsMain)

dirs: 
	mkdir -p bin
	mkdir -p obj
	mkdir -p test

$(targets): src/$(@F:.o=.c)
	gcc -c src/$(@F:.o=.c)
	mv $(@F) obj/

$(targetsMain): 
	gcc obj/$@ obj/print.o -o test/$@.finished

install:
	cp test/* bin/

reset:
	rm -r obj
	rm -r test
	rm -r bin

clean:
	rm -f obj/*
