#ifndef biblio_h
#define biblio_h

typedef struct Biblio Biblio;
typedef struct CellMorceau CellMorceau;


Biblio *nouvelle_biblio(void);
Biblio *charge_n_entrees(const char *nom_fichier, int n);
void libere_biblio(Biblio *B);
void insere(Biblio *B, int num, char *titre, char *artiste);
void affiche(Biblio *B);
Biblio *uniques(Biblio *B);
CellMorceau *rechercheParNum(Biblio *B, int num);
CellMorceau *rechercheParTitre(Biblio *B, char* titre);
Biblio *extraireMorceauxDe(Biblio* B, char *artiste);

void supprime_morceau(Biblio *B, int num);
void unique_graphe(int borne_inf, int pas, int borne_sup);
#endif
