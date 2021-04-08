#ifndef biblio_arbrelex_h
#define biblio_arbrelex_h

#include"biblio.h"

typedef struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
} CellMorceau;

typedef struct Noeud {
    struct Noeud *liste_car; //liste des choix possibles de caracteres
    struct Noeud *car_suiv; //caractere suivant dans la chaine
    CellMorceau *liste_morceaux; //liste des morceaux ayant le meme interprete
    char car;
} Noeud;

 struct Biblio {
    int nE;
    Noeud *A;
};
//creation d'un nouveau noeud
Noeud *creer_noeud(char c);
//la fonction insere un nouveau morceau dans la liste associee au dernier caractere du nom de l'artiste
void insere_morceau(Noeud **noeud ,int num, char *titre, char *artiste);
//la fonction libere la liste chainee de CellMorceau
void libere_CellMorceau(CellMorceau *c);
//fonction recursive qui libere chaque noeud d'un arbre
void libere_Noeud(Noeud *noeud);
void affiche_CellMorceau(CellMorceau *cell);
//fonction recursive qui fait appel a affiche_cellMorceau pour afficher les morceaux
void affiche_Noeud(Noeud *noeud);
//fonction qui supprime un element dans une liste chainee de CellMorceau
void supprimerCellMorceau( CellMorceau **list ,int num);
//rechercher un CellMorceau par numdans une liste chainee de CellMorceau
CellMorceau *rechercheCellMorceauNumero(CellMorceau *C, int num);
//fonction recursive qui fait appel a la fonction d'avant pour rechercer le num
CellMorceau *rechercheNoeudNumero(Noeud *noeud, int num);
//rechercher un CellMorceau par titre dans une liste chainee de CellMorceau
CellMorceau *rechercheCellMorceauTitre(CellMorceau *C, char *titre);
//fonction recursive qui fait appel a la fonction d'avant pour rechercer le num
CellMorceau *rechercheNoeudTitre(Noeud *noeud, char *titre);
//insere dans bunique juste une fois les morceaux de la liste list
void uniquesCellMorceau(Biblio *bunique, CellMorceau *list);
//fonction recursive qui fait appel a la fonction d'avant pour retourner une bibliotheque unique
void uniquesNoeud(Biblio *bunique, Noeud *noeud);
void unique_graphe(int borne_inf, int pas, int borne_sup);


#endif