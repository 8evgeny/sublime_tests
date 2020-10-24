CC=gcc
CLEAN=rm
CLEAN_FLAGS=-f
CLEAN_COMMAND=$(CLEAN) $(CLEAN_FLAGS)
PROGRAM_NAME=printup

$(PROGRAM_NAME): print_up.o main.o
	$(CC) -o $(PROGRAM_NAME) print_up.o main.o

print_up.o: print_up.c
	$(CC) -c print_up.c

main.o: main.c
	$(CC) -c main.c

clean:
	$(CLEAN_COMMAND) *.o
	$(CLEAN_COMMAND) $(PROGRAM_NAME)
