all: main

main: main.o ismael.o olivier.o solal.o
	gcc main.o ismael.o olivier.o solal.o -o main

main.o: main.c
	gcc -c main.c -o main.o

ismael.o: ismael.c
	gcc -c ismael.c -o ismael.o

olivier.o: olivier.c
	gcc -c olivier.c -o olivier.o

solal.o: solal.c
	gcc -c solal.c -o solal.o

clean:
	rm -f main main.o ismael.o olivier.o solal.o
