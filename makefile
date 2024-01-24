all:main

main: txt.o main.o
	gcc -o main txt.o main.o

txt.o: txt.c txt.h
	gcc -c txt.c

main.o: main.c txt.h
	gcc -c main.c

clean:
	rm -f *.o main
