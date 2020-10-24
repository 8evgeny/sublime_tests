CC=gcc
CLEAN=rm -f
PROGRAM_NAME=printup

$(PROGRAM_NAME): print_up.o main.o
	$(CC) -o $(PROGRAM_NAME) print_up.o main.o

print_up.o: print_up.c
	$(CC) -c print_up.c

main.o: main.c
	$(CC) -c main.c

clean:
	$(CLEAN) *.o
	$(CLEAN) $(PROGRAM_NAME)
