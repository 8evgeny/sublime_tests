program: program.c libthird.so
	gcc -o program program.c -L. -lthird \
	-Wl,-rpath,.

libthird.so: third.o libfirst.so libsecond.a
	gcc -shared -o libthird.so third.o -L. \
	-lfirst -lsecond -Wl,-rpath,.

third.o: third.c
	gcc -c -fPIC third.c

libfirst.so: first.c
	gcc -shared -fPIC -o libfirst.so first.c

libsecond.a: second.o
	ar rv libsecond.a second.o

second.o: second.c
	gcc -c second.c

clean:
	rm -f program libfirst.so libsecond.a \
	libthird.so *.o
