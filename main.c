#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<string.h>
#include "biblio.h"
#include"biblio_hachage.h"


void menu(){
  printf("\nMenu: \n");
  printf("0-Sortie\n");
  printf("1-Affichage\n");
  printf("2-Recherce morceau uniques\n");
  printf("3-Recherce morceau numero\n");
  printf("4-Recherche morceau titre\n");
  printf("5-Recherce morceau artiste\n");
  printf("6-Supprime un morceau par num\n");
  printf("7-Affiche le temps de calcul pour recherche num\n");
  printf("8-Affiche le temps de calcul pour recherche titre\n");
  printf("9-Affiche le temps de calcul pour recherche artiste\n");
  


  printf("Votre choix : ");
}

int main(int argc, const char *argv[]) {
  if (argc!=3){
    printf("Erreur format : %s <NomFichierBiblio.txt> <NbLigneALire >",argv[0]);
    return 1;
  }

  

  const char *nomfic =argv[1];
  int nlignes=atoi(argv[2]);

  printf("Lecture:\n");
 
  Biblio *biblio =charge_n_entrees(nomfic,nlignes);


  int ch;
  do{
    menu();
    int lus= scanf("%d",&ch);
    if(lus==0){
      ch = 0;
    }
    switch(ch){

      case 0:
        ch=0;
        break;

      case 1:
        printf("Afficheage\n");
        affiche(biblio);
        break;
      case 2:
        {
          Biblio *Bunique = uniques(biblio);
          affiche(Bunique);
          libere_biblio(Bunique);
          break;
        }
      
      case 3:
        {
          int i;
          printf("Enter Numero: ");
          scanf("%d",&i);
          rechercheParNum(biblio, i);
          break;
        }
      case 4:
        {
          int i=0;
          while(getc(stdin)!='\n');
          char *c=malloc(sizeof(char)*100);
          printf("Enter Title: ");
          c[0]=getc(stdin);
          while(c[i]!='\n'){
            c[++i]=getc(stdin);
          }
          c[i]='\0';
          printf("\n");
          rechercheParTitre(biblio, c);
          free(c);
          break;
        }

        case 5:
        {
          int i=0;
          while(getc(stdin)!='\n');
          char *c=malloc(sizeof(char)*100);
          printf("Enter Artiste: ");
          c[0]=getc(stdin);
          while(c[i]!='\n'){
            c[++i]=getc(stdin);
          }
          c[i]='\0';
          printf("\n");
          affiche(extraireMorceauxDe(biblio, c));
          free(c);
          break;
        }

        case 6:
        {
          int i;
          printf("Enter Numero: ");
          scanf("%d",&i);
          supprime_morceau(biblio, i);
          affiche(biblio);
          break;
        }
//temps num
        case 7:
        {
        clock_t temps_initial=clock();
        rechercheParNum(biblio,100);
        rechercheParNum(biblio,1000);
        rechercheParNum(biblio,10000);
        rechercheParNum(biblio,100000);
        rechercheParNum(biblio,300599);
        rechercheParNum(biblio,1000000);
        clock_t temps_final=clock();
        printf("%f", (double)(temps_final-temps_initial) /CLOCKS_PER_SEC);
        break;
        }
//temps titre
        case 8:
        {
          clock_t temps_initial=clock();
        rechercheParTitre(biblio,"Stuck On A Feeling");
        rechercheParTitre(biblio,"Mirrors");
        rechercheParTitre(biblio,"Every Time I Close My Eyes");
        rechercheParTitre(biblio,"You Still Touch Me");
        rechercheParTitre(biblio,"I Wish That We Were Married");
        rechercheParTitre(biblio,"TestPasDansBiblio");
        clock_t temps_final=clock();
        printf("%f", (double)(temps_final-temps_initial) /CLOCKS_PER_SEC);
         
         break;
        }
//temps artiste
        case 9:
        {
          clock_t temps_initial=clock();
        Biblio *B=extraireMorceauxDe(biblio,"Amy Holland");
        libere_biblio(B);
        B=extraireMorceauxDe(biblio,"Debbie Gibson");
        libere_biblio(B);
        B=extraireMorceauxDe(biblio,"Sting");
        libere_biblio(B);
        B=extraireMorceauxDe(biblio,"Usher");
        libere_biblio(B);
        B=extraireMorceauxDe(biblio,"Drake");
        libere_biblio(B);
        B=extraireMorceauxDe(biblio,"ArtistePasDansBiblio");
        libere_biblio(B);
        clock_t temps_final=clock();
        printf("%f", (double)(temps_final-temps_initial) /CLOCKS_PER_SEC);
          break;
        }


        case 10:
        {
          unique_graphe(100,100,7000);
          break;
        }
      default:
        ch=0;
        break;
    }
  } while(ch !=0);
 
  libere_biblio(biblio);
  printf("Au revoir\n");
 

  return 0;
}
