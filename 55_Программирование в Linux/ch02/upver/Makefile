CC=gcc
CCFLAGS=-Wall
MAKE=make
CLEAN=rm -f
PROGRAM_NAME=upver
OBJECTS=readver/readver.o toup/toup.o

$(PROGRAM_NAME): make-readver make-toup upver.o
	$(CC) $(CCFLAGS) -o $(PROGRAM_NAME) $(OBJECTS) upver.o

upver.o: upver.c
	$(CC) $(CCFLAGS) -c -Ireadver -Itoup $^

make-readver:
	$(MAKE) -C readver readver.o

make-toup:
	$(MAKE) -C toup toup.o

clean:
	$(CLEAN) *.o $(PROGRAM_NAME)
	$(MAKE) -C readver clean
	$(MAKE) -C toup clean
