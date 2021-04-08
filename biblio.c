#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parser.h"
#include"biblio.h"

Biblio *charge_n_entrees(const char *nom_fichier, int n){
 FILE *f=fopen(nom_fichier, "r");
 if(f==NULL){
  printf("Erreur d'ouverture du fichier");
  return NULL;
  }
 Biblio* B=nouvelle_biblio();
 char *artiste=NULL;
 char *titre=NULL;
 int nb;
 int taille;
 int i=n;
 
 while(i!=0 && end_of_file(f)==0){
   i--;
   parse_int(f,&nb);
   parse_char(f,'\t');
   parse_string(f,&titre,&taille,'\t');
   parse_char(f,'\t');
   parse_string(f,&artiste,&taille,'\n');  
   parse_char(f,'\n');
   insere(B,nb,titre,artiste);
  }
  free(titre);
  free(artiste);
  fclose(f);
  return B;
}
