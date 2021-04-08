#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "biblio_hachage.h"
#include "parser.h"

// typedef struct _collision{
//     char *artiste;
//     struct _collision *suiv;
// }Collision;



Biblio *nouvelle_biblio(void){
    Biblio *B = (Biblio *) malloc ( sizeof( Biblio));
    B->nE = 0;
    B->m = TAILLE_TABLE;
    B->T=malloc(sizeof(CellMorceau *)*TAILLE_TABLE);
    CellMorceau **tab=B->T;
    for(int i=0; i<TAILLE_TABLE; i++)
        tab[i]=NULL;
    return B;
}

// fonction qui nous aide en faisant le graphe pour visualiser le comportement d'une table de hachage en fonction de sa dimension
// Biblio *nouvelle_biblio_m(int m){
//     Biblio *B = (Biblio *) malloc ( sizeof( Biblio));
//     B->nE = 0;
//     B->m = m;
//     B->T=malloc(sizeof(CellMorceau *)*m);
//     CellMorceau **tab=B->T;
//     for(int i=0; i<m; i++)
//         tab[i]=NULL;
//     return B;
// }

//fonctions qui gerent la structure Collision cree pour pouvoir compter le nombre de collisions pour differentes fonctions cles
// Collision *newCol(char *artiste){
//     Collision *col=malloc(sizeof(Collision));
//     col->suiv=NULL;
//     col->artiste=strdup(artiste);
//     return col;
// }
// Collision *insereCol(Collision *liste, Collision *col){
//     if(liste==NULL) return col;
//     col->suiv=liste;
//     liste=col;
//     return liste;

// }



void libere_CellMorceau(CellMorceau *c){
    //on verifie si la liste existe
    if(c==NULL) return;
    while(c){
        CellMorceau *tmp=c;
        c=c->suiv;
        free(tmp->artiste);
        free(tmp->titre);
        free(tmp);
  }
}

void libere_biblio( Biblio *B){
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int capacite = B->m;
    CellMorceau **tab = B->T;
    //on parcourt tout le tableau de hachage
    while( k<capacite){
        if ( tab[k] != NULL ){
            libere_CellMorceau( tab[k]);
        }
        k++;
    }
    free(B->T);
    free(B);
}

void affiche_CellMorceau(CellMorceau *cell){
    if(cell==NULL) return;
    CellMorceau *temp=cell;
    while(temp){
        if(temp->artiste!=NULL && temp->titre!=NULL)
            printf("\t%d\t%s\t%s\n",temp->num,temp->titre, temp->artiste);
        temp=temp->suiv;
    }
}



CellMorceau *nouveau_morceau( int num , char *titre, char *artiste){
    CellMorceau *M = malloc (sizeof (CellMorceau));
    M->num = num;
    M->titre = strdup(titre);
    M->artiste = strdup(artiste);
    M->suiv=NULL;
    return M;
}
//la premiere fonction cle, la fonction donnee dans l'enonce
unsigned int fonction_cle1(const char *artiste){
    int s=0;
    
    for(int i=0;artiste[i]!='\0';i++){
        s+=artiste[i];
    }
    return s;
}
//une fonction cle plus efficace qui prend en compte aussi la position du caractere dans le nom de l'artiste
unsigned long fonction_cle2(const char *artiste){
    int s=0;
    
    for(int i=0;artiste[i]!='\0';i++){
        s+=artiste[i]*(i+1);
    }
    return s;
}

//fonction trouvee apres un peu de recherche, tres efficace mais impossible de trouver par nous memes

// unsigned long fonction_cle3(const char* artiste){
//     int len = strlen(artiste);
//     unsigned long hash = 5381;
//     unsigned int i = 0;

//     for(i=0; i < len; i++){
//         if(i != len-1)
//             hash = ((hash * 33) ^ artiste[i]) + artiste[i+1];
//         else
//         {
//             hash = ((hash * 33) ^ artiste[i]) + artiste[i-1];
//         }
//     }
//     return hash + len;
// }

//fonction qui transforme la clef pour pouvoir etre utilisee dans la table de hachage
unsigned int fonction_hachage(unsigned long cle, int m){
    unsigned int L=floor(cle*A);
    double res=floor(m*(cle*A-L));
    return (int) res;
}

//fonction qui retourne le nombre de collisions d'une table de hachage
// int collisions(Biblio *B){
//     int nb=0;
//     int i=0;
//     int k=0;
//     int nE=B->nE;
//     int m=B->m;
//     CellMorceau **tab=B->T;
//     Collision *col=NULL;
//     Collision *collision=NULL;

//     while(i<nE && k<m){
//         if(tab[k]!=NULL){
//             int cpt=-1;            
//             CellMorceau *liste=tab[k];
//             collision=NULL;
//             col=collision;
//             while(liste!=NULL){
//                 col=collision;
//                 while(col!=NULL){
//                     if(strcmp(col->artiste,liste->artiste)==0){
//                         break;
//                     }
//                     else{
//                         col=col->suiv;
//                     }
//                 }
//                 if(col==NULL){
//                     Collision *new=newCol(liste->artiste);
//                     collision=insereCol(collision,new);
//                     cpt++;
//                 }
//                 liste=liste->suiv;            
//             }
//             i++;
//             nb+=cpt;          

//         }
//         k++;
//     }

//     return nb;
// }

void affiche(Biblio *B){
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return;
    }

    // printf("Le nombre de collisions est : %d \n \n",collisions(B));
    // return;
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int capacite = B->m;
    CellMorceau **tab = B->T;
    while( i<nE && k<capacite){
        if(tab[k]!=NULL){
            //si la case de la table n'est pas vide, on affiche son contenu
           affiche_CellMorceau(tab[k]);
        //on increment le compteur de morceaux parcourus
        i++;
        }         
        //on increment le compteur des cases parcourues
        k++;
    }
    printf("Nombre de morceaux : %d\n \n", B->nE);


}


void insere ( Biblio *B, int num, char *titre, char *artiste){
    if( B == NULL){
        printf("L'insertion a echoue la biblioteque pointe vers NULL\n");
        return ;
    }
    //on trouve la clef pour chaque morceau et on insere dans le tableau de hachage
    unsigned int hash=fonction_hachage(fonction_cle2(artiste), B->m);
    //si le tableau est nul on cree le morceau et on l'insere dirctement
    if(B->T[hash]==NULL){
        B->T[hash]=nouveau_morceau(num,titre,artiste);
        B->nE++;
        return;
    }
    //si le tableau n'est pas nul, on insere le nouveau morceau en tete d'une liste chainee qui gere les collisions
    else{
        CellMorceau *new=nouveau_morceau(num,titre,artiste);
        new->suiv=B->T[hash];
        B->T[hash]=new;
        B->nE++;
        return;
    }
 }

//la recherche d'un certain morceau dans une liste chainee
CellMorceau *rechercheNumCellMorceau(CellMorceau *C, int num){
    //on verifie si la liste est vide
    if (C == NULL)
        return NULL;
    CellMorceau *cell = C;
    while ( cell ){
        //si en parcourat la liste on trouve le morceau on l'affiche
        if (cell->num == num){
            printf("\nLe num %d correspond au titre suivant :\n" , num);
            printf("%d\t%s\t%s\n", cell->num, cell->titre, cell->artiste);
            return cell;
        }
        //sinon on passe a la suite
        cell = cell->suiv;
    }
    return NULL;
}


CellMorceau *rechercheParNum(Biblio *B, int num){
    //verifie si la bibliotheque existe
     if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    //verifie si la table de hachage existe
    if ( B->T == NULL){
        printf("Erreur le tableau de hachage n'est pas alloue\n");
        return NULL;
    }
    CellMorceau **tab=B->T;
    int i=0,k=0;
    while(i<B->nE && k<B->m){
        if(tab[k]!=NULL){
            CellMorceau *res=rechercheNumCellMorceau(tab[k],num);
            if(res){
                return res;
            }
            i++;
        }
        k++;
    }
    printf("Le morceau %d n'est pas dans cette biblioteque\n",num);
    return NULL;

}
//la recherche d'un certain morceau dans une liste chainee
CellMorceau *rechercheTitreCellMorceau(CellMorceau *C, const char *titre){
    if (C == NULL)
        return NULL;
    CellMorceau *cell = C;
    while ( cell ){
        //si en parcourat la liste on trouve le morceau on l'affiche
        if (!strcmp(cell->titre,titre)){
            return cell;
        }
        cell = cell->suiv;
    }
    return NULL;
}


CellMorceau *rechercheParTitre(Biblio *B, char* titre){
    //verifie si la bibliotheque existe
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    //verifie si la table existe
    if ( B->T == NULL){
        printf("Erreur d'allocation du tableau de hachage\n");
        return NULL;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE;
    int m=B->m;
    CellMorceau **tab = B->T;
    while( i<nE && k<m){
        if ( tab[k] != NULL ){
            CellMorceau *res=rechercheTitreCellMorceau(tab[k],titre);
            if(res){
                printf("%d\t%s\t%s\n", res->num, res->titre, res->artiste);
                return res;
            }
            i++;
        }
        k++;
}
    printf("Il n'y a pas de morceaux %s dans cette biblioteque\n",titre);
    return NULL;
}
Biblio *extraireMorceauxDe(Biblio* B, char *artiste){
    //verifie si la bibliotheque existe
   if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    //verifie si la table de hachage existe
    if ( B->T == NULL){
        printf("Erreur d'allocation du tableau de hachage\n");
        return NULL;
    }
    Biblio *b=nouvelle_biblio(); 
 
    int m = B->m;
    CellMorceau **tab = B->T;
    //on trouve l'index du morceau a l'aide de la fonction cle et fonction hachage
    unsigned int hashKey=fonction_hachage(fonction_cle2(artiste),m);
    CellMorceau *liste=tab[hashKey];
    //on parcourt la liste de la case qui gere les collisions
    while(liste!=NULL){
        if (strcmp(artiste, liste->artiste)==0 ){
            insere(b,liste->num,liste->titre,liste->artiste);
        }
        liste=liste->suiv;
    }
    if(b==NULL)
        printf("Il n'y a pas de morceaux de %s dans cette biblioteque\n",artiste);
    return b;
}

void supprimerCellMorceau( CellMorceau **list , int num){
    CellMorceau *tmp=*list;
    CellMorceau *prev;
    if(tmp==NULL){
        printf("Error");
        return;
    }

    if(num==tmp->num){
        (*list)=(*list)->suiv;
        free(tmp->artiste);
        free(tmp->titre);
        free(tmp);
        return;
    }
 

     while(tmp!=NULL && tmp->num!=num){
        prev=tmp;
        tmp=tmp->suiv;
    }

    if(tmp==NULL) {
        printf("Not Found");
        return;
    }
    prev->suiv=tmp->suiv;
    free(tmp->titre);
    free(tmp->artiste);
    free(tmp);
}


void supprime_morceau(Biblio *B, int num){
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return;
    }
    int m = B->m;
    CellMorceau *morceauNum=rechercheParNum(B, num);
    char *artiste=morceauNum->artiste;
    unsigned int hashKey=fonction_hachage(fonction_cle2(artiste),m);
    CellMorceau *liste=B->T[hashKey];
    while(liste!=NULL){
        if (strcmp(artiste, liste->artiste)==0  && strcmp(artiste, liste->artiste)==0){
            supprimerCellMorceau(&liste,num);
             B->T[hashKey]=liste;
            (B->nE)--;
            return;
        }
        liste=liste->suiv;
    }
}

Biblio *uniques(Biblio *B){
    if (B==NULL){
        printf("Erreur d'allocation de la bibliotheque");
        return NULL;
    }
    if(B->T ==NULL){
        printf("Erreur d'allocation du tableau de hachage");
        return NULL;
    }

    Biblio *bunique=nouvelle_biblio();
    int i=0;
    int k=0;
    int nE=B->nE;
    int m=B->m;
    CellMorceau **tab=B->T;
    while(i<nE && k<m){
        if(tab[k]!=NULL){
            CellMorceau *curr=tab[k];
            CellMorceau *next=tab[k];
            insere(bunique, curr->num, curr->titre, curr->artiste);
            while(curr->suiv!=NULL && curr!=NULL){
                next=curr->suiv;
                while((next!=NULL) && ((strcmp(curr->artiste,next->artiste)!=0) || (strcmp(curr->titre,next->titre)!=0))){
                     next=next->suiv;      
                }
                if(next==NULL)
                    insere(bunique, curr->num, curr->titre, curr->artiste);
                curr=curr->suiv;
            }
            i++;
        }
        k++;
    }
    return bunique;
}

void unique_graphe(int borne_inf, int pas, int borne_sup){
    FILE *f=fopen("unique_hachage.txt","w");
    Biblio *B, *bunique;
    clock_t temps_initial;
    clock_t temps_final;
    for (int i = borne_inf; i<=borne_sup; i+=pas){
    B=charge_n_entrees("BiblioMusicale.txt",i);
        temps_initial=clock();
        bunique=uniques(B);
        temps_final=clock();
        libere_biblio(bunique);

        fprintf(f,"%d %f\n",i,( (double)temps_final-temps_initial) /CLOCKS_PER_SEC);
    }
    fclose(f);

}
//fonction qui nous permets d'obtenir le graphes pour differentes dimensions de la table de hachage
// Biblio *charge_n_entrees_m(const char *nom_fichier, int n, int m){
//  FILE *f=fopen(nom_fichier, "r");
//  if(f==NULL){
//   printf("Erreur d'ouverture du fichier");
//   return NULL;
//   }
//  Biblio* B=nouvelle_biblio_m(m);
//  char *artiste=NULL;
//  char *titre=NULL;
//  int nb;
//  int taille;
//  int i=n;
 
//  while(i!=0 && end_of_file(f)==0){
//    i--;
//    parse_int(f,&nb);
//    parse_char(f,'\t');
//    parse_string(f,&titre,&taille,'\t');
//    parse_char(f,'\t');
//    parse_string(f,&artiste,&taille,'\n');  
//    parse_char(f,'\n');
//    insere(B,nb,titre,artiste);
//   }
//   free(titre);
//   free(artiste);
//   fclose(f);
//   return B;
// }

//fonction pour faire le graphe de la table de hachage en fonction de sa dimension

// void unique_graphe_dim_m(int borne_inf, int pas, int borne_sup){
//     FILE *f=fopen("unique_hachage_dimension.txt","w");
//     Biblio *B, *bunique;
//     clock_t temps_initial;
//     clock_t temps_final;
//     for (int i = borne_inf; i<=borne_sup; i+=pas){
//     B=charge_n_entrees_m("BiblioMusicale.txt",300600,i);
//         printf("%d \n",i);
//         temps_initial=clock();
//         bunique=uniques(B);
//         temps_final=clock();
//         libere_biblio(bunique);

//         fprintf(f,"%d %f\n",i,( (double)temps_final-temps_initial) /CLOCKS_PER_SEC);
//     }
//     fclose(f);

// }



    
