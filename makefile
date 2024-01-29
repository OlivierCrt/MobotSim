all: main

main: main.o traitementTexte.o traitementImage.o traitementCommande.o
	gcc main.o traitementTexte.o traitementImage.o traitementCommande.o -o main

main.o: main.c
	gcc -c main.c -o main.o

traitementTexte.o: traitementTexte.c
	gcc -c traitementTexte.c -o traitementTexte.o

traitementImage.o: traitementImage.c
	gcc -c traitementImage.c -o traitementImage.o

traitementCommande.o: traitementCommande.c
	gcc -c traitementCommande.c -o traitementCommande.o

clean:
	rm -f main main.o traitementTexte.o traitementImage.o traitementCommande.o

