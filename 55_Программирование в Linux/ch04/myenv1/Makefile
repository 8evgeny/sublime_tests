myenv: envmain.o libmyenv.a
	gcc -o myenv envmain.o -L. -lmyenv

envmain.o: envmain.c
	gcc -c $^

libmyenv.a: mysetenv.o myprintenv.o
	ar rv $@ $^

mysetenv.o: mysetenv.c
	gcc -c $^

myprintenv.o: myprintenv.c
	gcc -c $^

clean:
	rm -f myenv libmyenv.a *.o
