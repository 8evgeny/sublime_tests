# Makefile for printup

printup: print_up.o main.o
	gcc -o printup print_up.o main.o

print_up.o: print_up.c print_up.h
	gcc -c print_up.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o
	rm -f printup
