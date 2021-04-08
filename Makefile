CFLAGS = -g -Wall
all : Biblio_liste Biblio_arbre

parser.o : parser.c parser.h
	gcc ${CFLAGS} -c parser.c

biblio.o : biblio.c biblio.h parser.h
	gcc ${CFLAGS} -c biblio.c 

biblio_liste.o : biblio_liste.c biblio_liste.h biblio.h
	gcc ${CFLAGS} -c biblio_liste.c 

biblio_arbrelex.o : biblio_arbrelex.c biblio_arbrelex.h biblio.h
	gcc ${CFLAGS} -c biblio_arbrelex.c

biblio_tabdyn.o : biblio_tabdyn.c biblio_tabdyn.h biblio.h
	gcc ${CFLAGS} -c biblio_tabdyn.c

biblio_hachage.o : biblio_hachage.c biblio_hachage.h biblio.h
	gcc ${CFLAGS} -c biblio_hachage.c
main.o : main.c biblio_arbrelex.h biblio.h
	gcc ${CFLAGS} -c main.c


Biblio_liste : parser.o biblio_liste.o main.o biblio.o
	gcc ${CFLAGS} -o Biblio_liste parser.o biblio_liste.o main.o biblio.o

Biblio_arbre : parser.o biblio_arbrelex.o main.o biblio.o 
	gcc ${CFLAGS} -o Biblio_arbre parser.o biblio_arbrelex.o main.o biblio.o

Biblio_tabdyn : parser.o biblio_tabdyn.o main.o biblio.o
	gcc ${CFLAGS} -o Biblio_tabdyn parser.o biblio_tabdyn.o main.o biblio.o

Biblio_hachage : parser.o biblio_hachage.o main.o biblio.o
	gcc ${CFLAGS} -lm -o  Biblio_hachage parser.o biblio_hachage.o main.o biblio.o

clean :
	rm -f *.o Biblio_liste Biblio_arbre Biblio_hachage Biblio_tabdyn
