#ifndef _BIBLIO_LISTE_H_
#define _BIBLIO_LISTE_H_

#include "biblio.h"


struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    CellMorceau *L;
    int nE;
};
//fonction qui libere la memoire dans une liste chainee
void libere_CellMorceau(CellMorceau *c);
//fonction qui cree un fichier pour pouvoir faire les graphes pour le temps de la fonction unique
void unique_graphe(int borne_inf, int pas, int borne_sup);

#endif