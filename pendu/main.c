//LENNY MORICONI

//BUT : Programme qui demande à un joueur 1 de saisir une chaîne de caractère à trouver, puis à un joueur 2 de saisir un caractère afin de deviner le mot. Le joueur 2 a le droit à 7 erreurs. Le mot à trouver doit contenir au minimum 3 caractères.
//ENTREE : Chaîne de caractères à trouver saisie par joueur 1, caractère proposé par joueur 2.
//SORTIE : A chaque saisie de joueur 2 : nombre d'essais restants, mot caché complété des éventuels caractères trouvés par joueur 2, "Faux !" si proposition erronée, sinon "Correct !".

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  //permet l'utilisation des fonctions "isupper()" et "tolower()"

//CONSTANTES
#define TAILLE 30   //taille maximale d'une chaîne de caractères
#define VIE 7       //nombre d'erreurs que le joueur 2 peut commettre
#define MIN 3       //taille minimale du mot à trouver

int main()
{
//DECLARATIONS VARIABLES
    char mot[TAILLE]="";
    char motCache[TAILLE]="";   //mot caché de longueur égale au mot à trouver et complété des caractères trouvés par joueur 2
    char saisie='.';            //variable set à '.' pour ne pas la laisser vide
    int cptEssai=VIE;
    int longueurMot=0;
    int i=0;
    int trouve=0;   //booleen

//PROGRAMME PRINCIPAL

    //boucle tant que le mot à trouver ne fait pas une taille de minimum 3 caractères

    while(strlen(mot)<MIN){
        printf("Joueur 1, saisissez un mot d'au moins %d lettres a trouver :\n",MIN);
        gets(mot);
        if(strlen(mot)<MIN){
            printf("!!! Le mot doit contenir au moins %d lettres !!!",MIN);
            getc(stdin);
            fflush(stdin);
        }
        system("cls");
    }

    longueurMot=strlen(mot);

    //vérifie que le mot saisi par joueur 1 est en minuscules, sinon change les caractères en minuscules

    for(i=0;i<longueurMot;i++){
        if(isupper(mot[i])!=0){
            mot[i]=tolower(mot[i]);
        }
    }

    //créer le mot caché contenant autant de lettres que le mot à trouver et complété des caractères trouvés par le joueur 2

    for(i=0;i<longueurMot;i++){
        strcat(motCache,"*");
    }

    //le joueur 2 propose des lettres tant qu'il n'a pas trouvé toutes les lettres du mot à trouver ou qu'il n'a pas commis 7 erreurs

    while(strcmp(motCache,mot)!=0 && cptEssai>0){
        trouve=0;       //réinitialisation de la variable
        printf("Mot a trouver : %s\n",motCache);
        printf("Joueur 2, proposez une lettre. Il vous reste %d essai(s) :\n",cptEssai);
        saisie=getchar();
        if(isupper(saisie)!=0){
            saisie=tolower(saisie);   //si le caractère saisi par le joueur 2 est en majuscule, on le transforme en minuscule
        }
        fflush(stdin);

        //boucle for pour vérifier si la lettre proposée est dans le mot à trouver, si c'est le cas alors on incrémente la variable "trouve"

        for(i=0;i<longueurMot;i++){
            if(saisie==mot[i]){
                motCache[i]=saisie;
                trouve++;
            }
        }

        //si la valeur de "trouve" est toujours à zéro alors la lettre proposée n'est pas dans le mot à trouver, le joueur 2 perd donc une vie

        if(trouve==0){
            cptEssai=cptEssai-1;
            printf("Faux !");
            getc(stdin);
            fflush(stdin);
        }
        else{
            printf("Correct !");
            getc(stdin);
            fflush(stdin);
        }

        system("cls");
    }

    //lorsqu'on sort de la boucle while, si le joueur 2 a encore des vies, cela signifie qu'il a forcément trouvé le mot (victoire), sinon c'est qu'il a commis 7 erreurs (défaite)

    if(cptEssai!=0)
        printf("Bravo !\n");
    else
        printf("Vous avez perdu...\n");



    system("pause");
    return 0;
}
