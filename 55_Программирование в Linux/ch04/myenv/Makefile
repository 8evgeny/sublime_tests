libmyenv.a: mysetenv.o myprintenv.o
	ar rv $@ $^

mysetenv.o: mysetenv.c
	gcc -c $^

myprintenv.o: myprintenv.c
	gcc -c $^

clean:
	rm -f libmyenv.a *.o
