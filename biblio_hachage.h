#ifndef _BIBLIO_HACHAGE_H_
#define _BIBLIO_HACHAGE_H_

#include "biblio.h"
#include <math.h>

#define TAILLE_TABLE 524287
#define A 0.6180339887498949


typedef struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
    unsigned int cle;
} CellMorceau;


struct Biblio {
    int nE;
    int m;
    CellMorceau **T;    
};

void libere_CellMorceau(CellMorceau *c);
void affiche_CellMorceau(CellMorceau *cell);
CellMorceau *nouveau_morceau( int num , char *titre, char *artiste);
unsigned int fonction_cle1(const char *artiste);
unsigned long fonction_cle2(const char *artiste);
CellMorceau *rechercheNumCellMorceau(CellMorceau *C, int num);
CellMorceau *rechercheTitreCellMorceau(CellMorceau *C, const char *titre);
void supprimerCellMorceau( CellMorceau **list , int num);
void unique_graphe(int borne_inf, int pas, int borne_sup);

#endif