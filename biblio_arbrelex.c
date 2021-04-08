#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include"biblio_arbrelex.h"




Biblio *nouvelle_biblio(){
    Biblio *B=(Biblio*)malloc(sizeof(Biblio));
    B->nE=0;
    B->A=NULL;
    return B;
}

Noeud *creer_noeud(char c){
    Noeud *new = malloc(sizeof(Noeud));
    //on verifie s'il y a une erreur d'allocation
    if (new==NULL){
        printf("Erreur d'allocation");
        return NULL;
    }
    //on initialise chaque case de la structure CellMorceau
    new->liste_car=NULL;
    new->car_suiv=NULL;
    new->liste_morceaux=NULL;
    new->car=c;
    return new;
}

//la fonction insere un nouveau morceau dans la liste associee au dernier caractere du nom de l'artiste
void insere_morceau(Noeud **noeud ,int num, char *titre, char *artiste){
    //on verifie si le noeud ou on veut inserer le morceau existe
    if(noeud==NULL){
        printf("Error! Le noeud n'existe pas");
        return;
    }
    //on cree un nouveau morceau
    CellMorceau *new = (CellMorceau*)malloc(sizeof(CellMorceau));
    new->num=num;
    new->artiste=strdup(artiste);
    new->titre=strdup(titre);

    //on insere le nouveau morceau en tete de la liste chainee
    CellMorceau *liste=(*noeud)->liste_morceaux;
    new->suiv=liste;
    (*noeud)->liste_morceaux=new;

}
//fonction qui libere une liste chainee de CellMorceau
void libere_CellMorceau(CellMorceau *c){
    if(c==NULL) return;
  while(c){
    CellMorceau *tmp=c;
    c=c->suiv;
    free(tmp->artiste);
    free(tmp->titre);
    free(tmp);
  }
}
//fonction recursive pour liberer les noeuds de l'arbre
void libere_Noeud(Noeud *noeud){
    if(noeud==NULL) return;
    //pour liberer les listes des morceaux
    libere_CellMorceau(noeud->liste_morceaux);
    //pour liberer l'arbre en largeur
    libere_Noeud(noeud->liste_car);
    //pour liberer l'arbre en profondeur
    libere_Noeud(noeud->car_suiv);
    //liberer le noeud courrant
    free(noeud);
}

void libere_biblio(Biblio *B){
    if(B==NULL) return;
    libere_Noeud(B->A);
    free(B);
}
//fonction qui affiche les morceaux d'un artiste
void affiche_CellMorceau(CellMorceau *cell){
    if(cell==NULL) return;
    CellMorceau *temp=cell;
    printf("Morceaux de %s : \n",cell->artiste);
    while(temp){
        printf("\t%d\t%s\t%s\n",temp->num,temp->titre, temp->artiste);
        temp=temp->suiv;
    }
}
//fonction recursive pour afficher la bibliotheque
void affiche_Noeud(Noeud *noeud){
    if (noeud==NULL) return;
    if(noeud->liste_morceaux!=NULL)
        //affiche les morceaux d'un artiste
        affiche_CellMorceau(noeud->liste_morceaux);
    //on parcourt l'arbre en profondeur
    affiche_Noeud(noeud->car_suiv);
    //on parcourt l'arbre en largeur
    affiche_Noeud(noeud->liste_car);
}

void affiche(Biblio *B){
    if(B==NULL)return;
    affiche_Noeud(B->A);
    printf("Il y a %d morceaux dans la bibliotheque\n",B->nE);
}




void insere(Biblio *B, int num, char *titre, char *artiste){
    int i=0;
    Noeud *tmp,*tmp2;
    //on verifie si la bibliotheque existe
    if(B==NULL){
        printf("Error");
        return;
    }
    B->nE++;
    //le cas de base: si l'arbre est vide on cree les noeuds correspondantes aux lettres de l'artise et on insere en meme temps la liste avec ses morceaux
    if(B->A==NULL){
       
        B->A=creer_noeud(artiste[0]);
        tmp=NULL;
        Noeud *cell=B->A;
        //on parcourt le nom de l'artiste caractere par  caractere et on cree en profondeur les noeuds correspondantes a ces caracteres;
        for(i=1;i<strlen(artiste);i++){
            tmp=creer_noeud(artiste[i]);
            //on ajoute le noeud cree aux noeuds de l'arbre, en profondeur
            cell->car_suiv=tmp;
            cell=tmp;
        }
        //pour le dernier caractere de l'artiste, on insere aussi son morceau sur le pointer liste_morceau
        insere_morceau(&cell,num,titre,artiste);
        return;
    }
     Noeud *cell=B->A;
    //si l'arbre n'est pas vide on le parcours, en essayant de trouver ou il faut inserer le nouveau morceau
    int len = strlen(artiste);
    //on parcours l'arbre noeud par noeud
    while(cell){
        //on essaye premierement parcourir l'arbre en profondeur (car_suiv)
        //on parcours l'artiste caractere par caractere; si le caractere courant = lettre dans le noeud courant, la condition est verifiee et on passe a la lettre suivante
        if ( artiste[i] == cell->car){
            i++;
            //on verifie si on est arrive a la fin du nom de l'artiste; si c'est le cas, il nous reste a inserer les morceaux correspondandes a l'artiste sur le pointer qui s'en occupe
            if ( artiste[i] == '\0' ){
                insere_morceau(&cell, num , titre , artiste);
                return;
            }
            //on avance dans l'arbre en profondeur
            if ( cell->car_suiv !=NULL){
                cell = cell->car_suiv;
            }
            else{
                //si les noeud ne sont pas encore crees, on rajoute les caracteres qui manquent a car_suiv
                while( i <len){
                    tmp =creer_noeud ( artiste[i] );
                    cell->car_suiv = tmp;
                    cell = tmp;
                    i++;
                }
                //on finit par l'insertion des morceaux
                insere_morceau(&cell, num , titre, artiste);
                return;
            }
        //si la lettre ne corresponde plus au caractere du noeud parcuru en profondeur, on passe aux autres caracteres possibles (liste_car)
        //on commence le parcours en largeur
        }else{
            tmp2 = cell;
            cell=cell->liste_car;
        }
    }
    //on rajoute les caracteres qui manquent a list_car
    cell = tmp2;
    //on cree le premier noeud dans liste_car et pour les autres caracteres on insere les noeud en profondeur, cad dans car_suiv
    cell->liste_car =creer_noeud(artiste[i]);
    i++;
    cell = cell->liste_car;
    while( i <len ){
        tmp =creer_noeud ( artiste[i] );
        cell->car_suiv = tmp;
        cell = tmp;
        i++;
    }
    //a la fin on insere le morceau correspondant
    insere_morceau(&cell, num , titre, artiste);
}


//fonction qui supprime un morceau dans une liste a partir de son numero
void supprimerCellMorceau( CellMorceau **list ,int num){
    //on verifie si la liste existe
    if (*list == NULL)
        return;

    CellMorceau *trash = NULL;
    //Si le premier element doit etre supprime
    if ( (*list)->num==num  ){ 
        trash = *list; 
        CellMorceau* tmp = (*list)->suiv;
        *list = tmp;  
        free(trash->titre);
        free(trash->artiste);
        free(trash);
        return;
    }
    CellMorceau *cell = *list;
    CellMorceau *tmp = cell;
    cell = cell->suiv;
    //on parcourt la liste jusqu'a la fin
    while( cell ){
        //si on trouve le numero recherche on enleve le morceau de la liste,  en liberant aussi la memoire
        if ( cell->num==num ){
            trash = cell ;
            tmp->suiv= cell->suiv;
            cell = tmp->suiv;
            free(trash->titre);
            free(trash->artiste);
            free(trash);
            return;
        }
        //si le numero n'est pas le numero recherche, on passe a la suite
        else {
            tmp = cell;
            cell = tmp->suiv;
        }
    }
}




//rechercher un CellMorceau dans une liste chainee de CellMorceau
CellMorceau *rechercheCellMorceauNumero(CellMorceau *C, int num){
    //on verifie si la liste est vide
    if (C == NULL)
        return NULL;
    CellMorceau *cell = C;
    //on parcourt la liste
    while ( cell ){
        //si le numero de la case currente corresponde au numero recherche on l'affiche
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
//fonction recursive pour recherche par numero
CellMorceau *rechercheNoeudNumero(Noeud *noeud, int num){
    ///on verifie si le noeud existe
    if (noeud == NULL)
        return NULL;
    CellMorceau *l ;
    //si le noeud correspond au dernier caractere d'un nom d'un artiste(cad la liste de morceaux n'est pas vide), on recherche le numero dans la liste chainee
    if (noeud->liste_morceaux != NULL){
        l = rechercheCellMorceauNumero(noeud->liste_morceaux, num);
    }
    //si on a trouve le morceau dans la liste chainee liste_morceaux, on le retourne.
    if (l)
        return l;
    //si le noeud courant ne corresponde pas au dernier caractere d'un artiste on parcourt l'arbre
    //premierement en profondeur
    CellMorceau *car_suiv=rechercheNoeudNumero(noeud->car_suiv,num);
    //si la recherche en profondeur marche, on retourne le resultat
    if(car_suiv)
        return car_suiv;
    //deuxiemement, en largeur, si la recherche en profondeur s'arrete
    CellMorceau *liste_car=rechercheNoeudNumero(noeud->liste_car, num);
    if(liste_car)
        return liste_car;
    return NULL;
}

CellMorceau *rechercheParNum(Biblio *B, int num){
    //on verifie si la bibliotheque existe
    if (B == NULL){
        printf("La Biblioteque est vide \n");
        return NULL;
    }
    //on commence la recherche par la racine
    CellMorceau *res=rechercheNoeudNumero(B->A, num);
    if(res)
        return res;
    printf("Le num n'appartient pas a la bibliotheque");
    return NULL;
}

CellMorceau *rechercheCellMorceauTitre(CellMorceau *C, char *titre){
    //on verifie si la liste est vide
    if (C == NULL)
        return NULL;
    CellMorceau *cell = C;
    //on parcourt la liste
    while ( cell ){
        if (!strcmp(cell->titre,titre)){
            //si on trouve le morceau recherche on l'affiche
            printf("%d\t%s\t%s\n", cell->num, cell->titre, cell->artiste);
            return cell;
        }
        //sinon on passe a la suite
        cell = cell->suiv;
    }
    return NULL;
}
//fonction recursive pour recherche par titre
CellMorceau *rechercheNoeudTitre(Noeud *noeud, char *titre){
    ///on verifie si le noeud existe
    if (noeud == NULL)
        return NULL;
    //si le noeud correspond au dernier caractere d'un nom d'un artiste(cad la liste de morceaux n'est pas vide), on recherche le numero dans la liste chainee
    CellMorceau *l=rechercheCellMorceauTitre(noeud->liste_morceaux, titre);
    //si on a trouve le morceau dans la liste chainee liste_morceaux, on le retourne.
    if (l)
        return l;
    //si le noeud courant ne corresponde pas au dernier caractere d'un artiste on parcourt l'arbre
    //premierement en profondeur
    CellMorceau *car_suiv=rechercheNoeudTitre(noeud->car_suiv, titre);
    if(car_suiv)
        return car_suiv;
    //deuxiemement, en largeur, si la recherche en profondeur s'arrete
    CellMorceau *liste_car=rechercheNoeudTitre(noeud->liste_car, titre);
    if(liste_car)
        return liste_car;
    return NULL;
}

CellMorceau *rechercheParTitre(Biblio *B, char *titre){
    //on verifie si la bibliotheque existe
    if (B == NULL){
        printf("La Biblioteque est vide\n");
        return NULL;
    }
    //on commence la recherche par la racine
    CellMorceau *res= rechercheNoeudTitre(B->A, titre);
    if(res)
        return res;

    printf("Il n'y a aucun morceau %s dans cette biblioteque \n", titre);
    return NULL;
 }

Biblio *extraireMorceauxDe(Biblio *B, char *artiste){
    //on cree la bibliotheque
    Biblio *b=nouvelle_biblio();
    Noeud *cell = B->A;
    int i = 0; 
    //on parcourt la liste
    while(cell != NULL){
        //on essaie trouver les morceaux en parcourant l'arbre en profondeur
        if ( artiste[i] == cell->car){
            i++;
            //si on est arrive a la fin du nom on peut inserer les morceaux de la liste chainee dans la nouvelle bibliotheque
            if ( artiste[i] == '\0' ){
                CellMorceau *morceaux=cell->liste_morceaux;
                while(morceaux){
                    insere(b,morceaux->num,morceaux->titre,morceaux->artiste);
                    morceaux=morceaux->suiv;
                }
                return b;
            }
            //si on est pas arrive a la fin du nom, on passe au noeud suivant en profondeur, s'il existe
            if ( cell->car_suiv != NULL)
                cell = cell->car_suiv;
        }
        //sinon on fait un pas en largeur
        else{
            cell=cell->liste_car;
        }
    }
    //si la bibliotheque est nulle
    if(b->A==NULL)
        printf ( "Il n'y a aucun morceau de %s dans cette biblioteque\n", artiste);
    return NULL;
 }


void supprime_morceau(Biblio *B, int num){
    //on verifie si la bibliotheque est vide
    if (B->A == NULL){
        return ;
    }
    //on diminue le nombre de morceaux dans la bibliotheque
    (B->nE)--;
    int i = 0;
    //on recherche le nom de l'artiste a l'aide de la fonction deja creee
    CellMorceau *tmp=rechercheParNum(B, num);
    char *artiste=tmp->artiste;
    //on recherche dans l'arbre la liste des morceaux de l'artiste
    Noeud *cell = B->A;
    while(cell){
        if ( artiste[i] == cell->car){
            i++;
            if ( cell->car_suiv !=NULL ){
                cell = cell->car_suiv;
            }
            else
                break;
        }
        else
            cell=cell->liste_car;
    }

    if (cell == NULL ){
        printf("La suppression du morceau numero %d n'a pas eu lieu\n", num);
    }
    else{
        //on supprime le morceau correspondant au numero
        supprimerCellMorceau(&(cell->liste_morceaux) , num);
    }
}
//fonction qui renvoie par le parametre list une liste des morceaux sans doublons
void uniquesCellMorceau(Biblio *bunique, CellMorceau *list){
    CellMorceau *curr=list;
  CellMorceau *next=list;
  //on insere le premier morceau dans la liste
  insere(bunique,curr->num,curr->titre,curr->artiste);
  //on parcourt la liste avec deux pointers
    while(curr->suiv!=NULL && curr!=NULL){ 
        next=curr->suiv;
        //si on est pas encore arrive a la fin de la liste et si morceaux sont differentes, on avance avec le pointer next
        while((next!=NULL) && ((strcmp(curr->artiste,next->artiste)!=0) || (strcmp(curr->titre,next->titre)!=0))){
            next=next->suiv;      
        }
        //si next est nul cela veut dire qu'on est arrive a la fin de la liste sans avoir trouve des dublons, donc on peut inserer le morceau
        if(next==NULL)
       insere(bunique,curr->num,curr->titre,curr->artiste);
        curr=curr->suiv;
    }  
}

//fonction recursive qui applique la fonction unique pour une liste dans la profondeur et dans la largeur d'un arbre
void uniquesNoeud(Biblio *bunique, Noeud *noeud){
    if (noeud == NULL){
        return;
    }
    if (noeud->liste_morceaux != NULL){
        uniquesCellMorceau(bunique, noeud->liste_morceaux);
    }
    uniquesNoeud(bunique, noeud->car_suiv);
    uniquesNoeud(bunique, noeud->liste_car);
}

Biblio *uniques(Biblio *B){
    if(B==NULL){
        printf("La bibliotheque est vide");
        return NULL;
    }
    Biblio *bunique=nouvelle_biblio();
    uniquesNoeud(bunique, B->A);
    return bunique;
}

void unique_graphe(int borne_inf, int pas, int borne_sup){
    FILE *f=fopen("unique_arbre.txt","w");
    Biblio *bunique,*B;
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