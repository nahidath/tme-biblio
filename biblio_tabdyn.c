#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "biblio_tabdyn.h"


Biblio *nouvelle_biblio(void){
    Biblio *B = (Biblio *) malloc ( sizeof( Biblio));
    B->nE = 0;
    B->capacite = 0;
    B->T = NULL;
    return B;
}

CellMorceau *nouveau_morceau( int num , char *titre, char *artiste){
    CellMorceau *M = malloc (sizeof (CellMorceau));
    M->num = num;
    M->titre = strdup(titre);
    M->artiste = strdup(artiste);
    return M;
}


void affiche(Biblio *B){
    //verifie si la bibliotheque existe
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    //verifie si la bibliotheque contient des morceaux
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int capacite = B->capacite;
    CellMorceau *tab = B->T;
    //on parcourt le tableu jusqu'a la fin ou jusuq'au moment ou on a verifie tous les morceaux dans la bibliotheque
    while( i<nE && k<capacite){
        //on verifie si la case courrente du tableau est vide
        if (tab[k].artiste != NULL && tab[k].titre != NULL){
            printf("%d\t%s\t%s\n", tab[k].num, tab[k].titre, tab[k].artiste);
            //on increment le compteur de morceaux parcourus
            i++;
        }
        //on increment le compteur des cases parcourues
        k++;
    }
    printf("Nombre de morceaux : %d\n \n", B->nE);
}

void libere_CellMorceau(CellMorceau *t){
    free(t->titre);
    free(t->artiste);
}

void libere_biblio( Biblio *B){
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int capacite = B->capacite;
    CellMorceau *tab = B->T;
    //on parcourt le tableu jusqu'a la fin ou jusuq'au moment ou on a verifie tous les morceaux dans la bibliotheque
    while( i<nE && k<capacite){
        //on verifie si la case courrente du tableau est vide
        if ( &tab[k] != NULL ){
            //si elle n;est pas vide, on libere l'espace memoire
            libere_CellMorceau( &tab[k]);
            //on increment le compteur de morceaux parcourus
            i++;
        }
        //on increment le compteur des cases parcourues
        k++;
    }
    free(B->T);
    free(B);
}


void insere ( Biblio *B, int num, char *titre, char *artiste){
    // Si B est NULL, on quitte la fonction
    if( B == NULL){
        printf("L'insertion a echoue la biblioteque pointe vers NULL\n");
        return ;
    }

    //Si B->T est NULL, on cree un morceau et le faire pointer sur B->T
    if(B->T == NULL){
        B->T = nouveau_morceau(num, titre, artiste);
        B->nE = 1;
        B->capacite = 1;
        return;
    }
    
    // Si le tableau est arrive a sa capacite max, on double la capacite et on insere recursivement
    if(B->nE == B->capacite){
        B->capacite = B->capacite * 2;
        B->T = realloc(B->T, sizeof(CellMorceau)*B->capacite);
        for(int i = B->nE; i< (B->capacite); i++){
            ((B->T)+ i)->titre = NULL;
            ((B->T)+ i)->artiste = NULL;
            ((B->T)+ i)->num = 0;
        }
        insere(B, num, titre, artiste);
        return;
    }
    
    // Si le tableau a de la place, on insere a la premiere place disponible
    int i = 0;
    while(i < B->capacite){
        // Recherche de la premiere case vide
        if(((B->T)+ i)->titre == NULL){
            (B->T[i]).titre = strdup(titre);
            (B->T[i]).artiste = strdup(artiste);
            (B->T[i]).num = num;
            B->nE++;
            return;
        }

        i++;
    }
}


void supprime_morceau(Biblio *B, int num){
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return ;
    }
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return ;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int capacite = B->capacite;
    int nE= B->nE; 
    CellMorceau *tab = B->T;
    while(i<nE && k<capacite){
        if ( tab[k].artiste != NULL && tab[k].titre != NULL){
            if ( tab[k].num==num ){
                tab[k].artiste=NULL;
                tab[k].titre=NULL;
                tab[k].num = 0;
                (B->nE)--;
                return ;
            }
            i++;    
        }    
        k++;
    }
    printf("La suppression a echoue\n");
}


 Biblio *uniques(Biblio *B){

    if (B == NULL){
        printf("La biblioteque est null ");
        return B;
    }
    Biblio *final = nouvelle_biblio();
    if (B->T == NULL){
        return final;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int capacite = B->capacite;
    CellMorceau *tab = B->T;
    //on parcourt le tableu jusqu'a la fin ou jusuq'au moment ou on a verifie tous les morceaux dans la bibliotheque
    while( i<nE && k<capacite){
        //on verifie si la case courrente du tableau est vide
        if ( tab[k].artiste != NULL && tab[k].titre != NULL){
            //boolean qui verifie si le morceau se trouve encore une fois dans la liste
            int bool=0;
            int j=0, t=0;
            while(j<k && t<nE){
                //on verifie si la case courrente du tableau est vide
                if ( tab[j].artiste != NULL && tab[j].titre != NULL){ 
                    //si on trouve encore une fois le meme morceau on change le bool 
                    if(strcmp(tab[k].titre,tab[j].titre)==0 && strcmp(tab[k].artiste,tab[j].artiste)==0){
                        bool=1;
                        break;                    
                    }
                     //on increment le compteur de morceaux parcourus pour le deuxieme while
                    t++;
                }
            //on increment le compteur des cases parcourues pour le deuxieme while
            j++;
            }
            //si le morceau se trouvera pas a la suite du tableau, on l'insere
            if(!bool)
                 insere( final , tab[k].num, tab[k].titre , tab[k].artiste);
            i++;
        }
        k++;
    }
    return final;
}

CellMorceau *rechercheParNum(Biblio *B, int num){
    //verifie si la bibliotheque existe
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    //verifie si la bibliotheque contient des morceaux
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return NULL;
    }
    int i = 0; // indice pour les cases non-vides
    int k = 0; // indice pour toutes les cases
    int nE= B->nE; 
    int capacite = B->capacite;
    CellMorceau *tab = B->T;
    //on parcourt le tableasu jusqu'a la fin ou jusuq'au moment ou on a verifie tous les morceaux dans la bibliotheque
    while( i<nE && k<capacite){
        //on verifie si la case courrente du tableau est vide
        if ( &tab[k] != NULL ){
        //on verifie si la case courrente du tableau corresponde a notre recherche
            if (num == tab[k].num){
                printf("\nLe num %d correspond au morceaux suivant :\n" , num);
                printf("%d\t%s\t%s\n", tab[k].num, tab[k].titre, tab[k].artiste);
                return tab+k;
            }
            i++;
        }
        k++;
    }
    printf("Le morceau %d n'est pas dans cette biblioteque\n",num);
    return NULL;
}

Biblio *extraireMorceauxDe(Biblio *B , char *artiste){
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return NULL;
    }
    Biblio *b=nouvelle_biblio();
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int capacite = B->capacite;
    CellMorceau *tab = B->T;
    while( i<nE && k<capacite){
        if ( &tab[k] != NULL ){
        //on verifie si la case courrente du tableau corresponde a notre recherche
            if ( !strcmp(artiste, tab[k].artiste) ){
           
                insere(b, tab[k].num, tab[k].titre, tab[k].artiste);
            }
            i++;
        }
        k++;
    }
    if(b==NULL)
        printf("Il n'y a pas de morceaux de %s dans cette biblioteque\n",artiste);
    return b;
}

CellMorceau *rechercheParTitre(Biblio *B , char *titre){
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return NULL;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int capacite = B->capacite;
    CellMorceau *tab = B->T;
    while( i<nE && k<capacite){
        if ( &tab[k] != NULL ){
            if (!strcmp(titre , tab[k].titre)){
                printf("\nLe titre %s correspond au morceau suivant :\n" , titre);
                printf("%d\t%s\t%s\n", tab[k].num, tab[k].titre, tab[k].artiste);
                return tab+k;
            }
            i++;
        }
        k++;
    }
    printf("Il n'y a pas de morceaux %s dans cette biblioteque\n",titre);
    return NULL;
    
}

void unique_graphe(int borne_inf, int pas, int borne_sup){
    FILE *f=fopen("unique_tabdyn.txt","w");
    Biblio *B, *bunique;
    clock_t temps_initial;
    clock_t temps_final;
    B=charge_n_entrees("BiblioMusicale.txt",300000);
    for (int i = borne_inf; i<=borne_sup; i+=pas){
        B->nE=i;
        temps_initial=clock();
        bunique=uniques(B);
        temps_final=clock();
        libere_biblio(bunique);
        printf("%d\n",i);

        fprintf(f,"%d %f\n",i,( (double)temps_final-temps_initial) /CLOCKS_PER_SEC);
    }
    fclose(f);

}