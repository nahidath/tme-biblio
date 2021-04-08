#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include"biblio_liste.h"


Biblio* nouvelle_biblio(void){
  Biblio* B = (Biblio*) malloc(sizeof(Biblio));
  B->L=NULL;
  B->nE=0;
  return B;
}

//la fonction insere un nouveau morceau en tete de la liste chainee
void insere(Biblio *B, int num, char *titre, char *artiste){
  CellMorceau *new=(CellMorceau*)malloc(sizeof(CellMorceau));
  
  new->num=num;
  new->artiste=strdup(artiste);
  new->titre=strdup(titre);

  new->suiv=B->L;
  B->L=new;
  B->nE++;
  }


void libere_CellMorceau(CellMorceau *c){
  while(c){
    CellMorceau *tmp=c;
    c=c->suiv;
    free(tmp->artiste);
    free(tmp->titre);
    free(tmp);
  }
}

void libere_biblio(Biblio *B){
    libere_CellMorceau(B->L);
    free(B);
  }


void affiche(Biblio *B){
  CellMorceau *temp=B->L;
  if(temp==NULL) return;
  while(temp){
    printf("%d\t%s\t%s\n",temp->num,temp->titre, temp->artiste);
    temp=temp->suiv;
  }
  printf("Nombre de morceaux dans la bibliotheque %d\n",B->nE);
}



CellMorceau *rechercheParNum(Biblio *B, int num){
  //verifie si la bibliotheque etait bien allouee
    if(B==NULL){
    printf("Erreur d'allocation de la bibliotheque");
    return NULL;
  }
  
  CellMorceau *temp = B->L;
  //on parcourt la liste jusqu'a la fin
  while(temp!=NULL){
    //si on trouve le morceau correspondant au numero, on l'affiche et on sort de la fonction en le retournant
    if(temp->num==num){
      printf("%d\t%s\t%s\n",temp->num,temp->titre, temp->artiste);
      return temp;
    }
    else{
      //si le morceau courant ne corresponde pas, on pase au morceau suivant
      temp=temp->suiv;
    }
  }
  //si on sort de la boucle sans rien retourner, cela signifie que le num se trouve pas dans la bibliotheque
  printf("Le morceau num %d n'existe pas dans la bibliotheque\n",num);
  return NULL;
}

CellMorceau *rechercheParTitre(Biblio *B, char* titre){
   //verifie si la bibliotheque etait bien allouee
  if(B==NULL){
    printf("Erreur d'allocation de la bibliotheque");
    return NULL;
  }
  CellMorceau *temp=B->L;
  //on parcourt la liste jusqu'a la fin
  while(temp!=NULL){
    //si le du morceau courant corresponde au titre cherche, on affiche et on retourne le morceau
    if(strcmp(temp->titre,titre)==0){
      printf("%d\t%s\t%s\n",temp->num,temp->titre, temp->artiste);
      return temp;
    }
    //sinon on passe a la suite
    else
      temp=temp->suiv;
    
  }
  //si on est sortie de la boucle sans rien retourner, cela signifie que le titre ne se trouve pas dans la bibliotheque
  printf("Le morceau  %s n'existe pas dans la bibliotheque\n",titre);

  return NULL;
}

//la fonction cree une nouvelle bibliotheque avec tous les morceaux de l'artiste donne en parametre
Biblio *extraireMorceauxDe(Biblio* B,char *artiste){
   //verifie si la bibliotheque etait bien allouee
  if(B==NULL){
    printf("Erreur d'allocation de la bibliotheque");
    return NULL;
  }
  //la bibliotheque qui va contenir les morceaux de l'artiste
  Biblio *biblioArtiste=nouvelle_biblio();
  CellMorceau *morceaux=B->L;  

  //on parcourt la liste
  while(morceaux!=NULL){
    //si l'artiste du morceau courant correspond a l'artiste recherche, on insere le morceau dans la bibliotheque de l'artiste
    if(strcmp(morceaux->artiste,artiste)==0){
      insere(biblioArtiste,morceaux->num,morceaux->titre,artiste);
    }
    //sinon on passe a la suite
    morceaux=morceaux->suiv;
  }
  //si aucun morceu etait insere, cela signifie que l'artiste ne se trouve pas dans la bibliotheque
  if(biblioArtiste->L==NULL)
    printf("L'artiste %s n'existe pas dans la bibliotheque\n",artiste);
  return biblioArtiste;
}

void supprime_morceau(Biblio *B, int num){
  //verifie si la bibliotheque etait bien allouee
  if(B==NULL){
    printf("Erreur d'allocation de la bibliotheque");
    return;
  }
  CellMorceau *tmp=B->L;
  CellMorceau *prev;
  //on verifie s'il y a des morceaux dans la bibliotheque
  if(tmp==NULL){
    printf("Aucun morceau dans la bibliotheque");
    return;
  }

  //si la premiere case de la liste doit etre supprimee
  if(num==tmp->num){
    B->L=B->L->suiv;
    free(tmp->artiste);
    free(tmp->titre);
    free(tmp);
    (B->nE)--;
    return;
  }
 
  //on avance dans la liste jusqu'au moment ou on trouve le morceau avec le numero num ou jusqu'a la fin de la liste
  while(tmp!=NULL && tmp->num!=num){
      prev=tmp;
      tmp=tmp->suiv;
    }
  //si on a parcuru toute la liste, cela signifie que le numero num ne se trouve pas dans la bibliotheque
  if(tmp==NULL) {
    printf("Not Found");
    return;
    }
  //on elibere la memoire allouee pour la case qu'on veut supprimer
  prev->suiv=tmp->suiv;
  free(tmp->titre);
  free(tmp->artiste);
  free(tmp);
  }

//la fonction renvoie une bibliotheque ou chaque morceau se trouve une seule fois
Biblio *uniques(Biblio *B){
  Biblio *bunique=nouvelle_biblio();
  CellMorceau *curr=B->L;
  CellMorceau *next=B->L;
  //on insere le premier morceau de la bibliotheque
  insere(bunique, curr->num, curr->titre, curr->artiste);
  //on parcours la liste avec deux pointers
    while(curr->suiv!=NULL && curr!=NULL){ 
        next=curr->suiv;
        //le pointer next parcours la liste a partir du pointer curr jusqu'a la fin de la liste
        //on avance dans la liste en comparant les morceaux; si ils sont differents on avance;
        //on sort de la boucle lorsque on rencontre un doublon ou si on est arrive a la fin de la liste
        while((next!=NULL) && ((strcmp(curr->artiste,next->artiste)!=0) || (strcmp(curr->titre,next->titre)!=0))){
            next=next->suiv;      
        }
        //si on est arrive a la fin de la liste sans avoir trouve de doublon, on insere le morceau represente par le pointer curr
        if(next==NULL)
          insere(bunique,curr->num,curr->titre,curr->artiste);
        curr=curr->suiv;
    }  
   return bunique;
  }
  //fonction qui cree un fichier pour pouvoir faire les graphes
  void unique_graphe(int borne_inf, int pas, int borne_sup){
    FILE *f=fopen("unique_liste.txt","w");
    Biblio *B, *bunique;
    clock_t temps_initial;
    clock_t temps_final;
    for (int i = borne_inf; i<=borne_sup; i+=pas){
        B=charge_n_entrees("BiblioMusicale.txt",i);
        temps_initial=clock();
        bunique=uniques(B);
        temps_final=clock();
        libere_biblio(bunique);
        printf("%d \n",i);

        fprintf(f,"%d %f\n",i,( (double)temps_final-temps_initial) /CLOCKS_PER_SEC);

    }
        fclose(f);


}


