myenv: envmain.o libmyenv.so
	gcc -o myenv envmain.o -L. -lmyenv

envmain.o: envmain.c
	gcc -c $^

libmyenv.so: mysetenv.o myprintenv.o
	gcc -shared -o libmyenv.so $^

mysetenv.o: mysetenv.c
	gcc -fPIC -c $^

myprintenv.o: myprintenv.c
	gcc -fPIC -c $^

clean:
	rm -f myenv libmyenv.so *.o
