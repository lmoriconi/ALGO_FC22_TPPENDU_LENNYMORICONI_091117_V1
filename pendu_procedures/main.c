//LENNY MORICONI

//BUT : Programme qui demande � un joueur 1 de saisir une cha�ne de caract�re � trouver, puis � un joueur 2 de saisir un caract�re afin de deviner le mot. Le joueur 2 a le droit � 7 erreurs. Le mot � trouver doit contenir au minimum 3 caract�res.
//ENTREE : Cha�ne de caract�res � trouver saisie par joueur 1, caract�re propos� par joueur 2.
//SORTIE : A chaque saisie de joueur 2 : nombre d'essais restants, mot cach� compl�t� des �ventuels caract�res trouv�s par joueur 2, "Faux !" si proposition erron�e, sinon "Correct !".

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//CONSTANTES
#define TAILLE 30   //taille maximale d'une cha�ne de caract�res
#define VIE 7       //nombre d'erreurs que le joueur 2 peut commettre
#define MIN 3       //taille minimale du mot � trouver

//PROTOTYPES
void saisieMot(char mot[TAILLE],int *ptLongueurMot);        //saisie du mot � trouver par le joueur 1
void minuscule(char mot[TAILLE], int longueurMot);          //v�rifie que le mot saisi par joueur 1 est en minuscule et change les caract�res qui sont en majuscules
void cacherMot(char ptMotCache[TAILLE],int longueurMot);    //cr�e un mot cach� qui sera compl�t� des �ventuelles bonnes r�ponses du joueur 2
void proposition(char *ptSaisie,char motCache[TAILLE],int cptEssai);    //proposition d'un caract�re par joueur 2
void comparer(char motCache[TAILLE],char mot[TAILLE],char saisie,int longueurMot,int *ptCptEssai);  //compare la proposition du joueur 2 avec les lettres du mot � trouver

int main()
{
//DECLARATIONS VARIABLES
    char mot[TAILLE]="";
    char motCache[TAILLE]="";
    char saisie='.';    //variable set � '.' pour ne pas la laisser vide
    int cptEssai=VIE;
    int longueurMot=0;

//PROGRAMME PRINCIPAL
    saisieMot(mot,&longueurMot);

    minuscule(mot,longueurMot);

    cacherMot(motCache,longueurMot);

    //le joueur 2 propose des lettres tant qu'il n'a pas trouv� toutes les lettres du mot � trouver ou qu'il n'a pas commis 7 erreurs

    while(strcmp(motCache,mot)!=0 && cptEssai>0){
        proposition(&saisie,motCache,cptEssai);
        comparer(motCache,mot,saisie,longueurMot,&cptEssai);
        system("cls");
    }

    //lorsqu'on sort de la boucle while, si le joueur 2 a encore des vies, cela signifie qu'il a forc�ment trouv� le mot (victoire), sinon c'est qu'il a commis 7 erreurs (d�faite)

    if(cptEssai!=0)
        printf("Bravo !\n");
    else
        printf("Vous avez perdu...\n");



    system("pause");
    return 0;
}

//DEFINITION PROCEDURES

//BUT : proc�dure qui demande au joueur 1 de saisir une cha�ne de caract�res � trouver et qui v�rifie que la taille de ce mot est sup�rieure ou �gale � 3 caract�res
//ENTREE : une cha�ne de caract�re saisie par le joueur 1
//SORTIE : un message d'erreur si la taille de la cha�ne est inf�rieure � 3 caract�res

void saisieMot(char mot[TAILLE],int *ptLongueurMot){
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
    *ptLongueurMot=strlen(mot);
}

//BUT : proc�dure qui v�rifie que le mot saisi par joueur 1 dans "saisieMot" est en minuscules, sinon change les caract�res en minuscules
//ENTREE : cha�ne de caract�re saisie par joueur 1 dans "saisieMot"
//SORTIE : cha�ne de caract�re en minuscules

void minuscule(char mot[TAILLE], int longueurMot){
    int i = 0;
    for(i=0;i<longueurMot;i++){
        if(isupper(mot[i])!=0){
            mot[i]=tolower(mot[i]);
        }
    }
}

//BUT : proc�dure qui cr�e un mot cach� de taille �gale au mot � trouver et visible avant chaque saisie par le joueur 2. Ce mot cach� informe le joueur 2 sur la taille du mot � trouver et affiche les �ventuels caract�res corrects trouv�s ce dernier.

void cacherMot(char motCache[TAILLE],int longueurMot){
    int i=0;
    for(i=0;i<longueurMot;i++){
        motCache=strcat(motCache,"*");
    }
}

//BUT : proc�dure qui affiche le mot cach�, le nombre d'essais restants et propose au joueur 2 de saisir un caract�re, transforme le caract�re saisi en minuscule si joueur 2 a saisi une majuscule
//ENTREE : joueur 2 saisit un caract�re
//SORTIE : mot cach� compl�t� des �ventuels caract�res d�j� trouv�s, nombre d'essais restants

void proposition(char *ptSaisie,char motCache[TAILLE],int cptEssai){
    printf("Mot a trouver : %s\n",motCache);
    printf("Joueur 2, proposez une lettre. Il vous reste %d essai(s) :\n",cptEssai);
    *ptSaisie=getchar();
    if(isupper(*ptSaisie)!=0){
        *ptSaisie=tolower(*ptSaisie);   //si le caract�re saisi par le joueur 2 est en majuscule, on le transforme en minuscule
    }
    fflush(stdin);
}

//BUT : proc�dure qui v�rifie si le caract�re saisit par le joueur 2 dans la proc�dure "proposition" est dans le mot � trouver
//ENTREE : caract�re saisit par le joueur 2 dans la proc�dure "proposition"
//SORTIE : si le caract�re saisit existe dans le mot � trouver, alors le programme affiche "Correct !", sinon "Faux !"

void comparer(char motCache[TAILLE],char mot[TAILLE],char saisie,int longueurMot,int *ptCptEssai){
    int i=0;
    int trouve=0;   //booleen
    for(i=0;i<longueurMot;i++){
        if(saisie==mot[i]){
            motCache[i]=saisie;
            trouve++;
        }
    }
    if(trouve==0){
        *ptCptEssai=(*ptCptEssai)-1;
        printf("Faux !");
        getc(stdin);
        fflush(stdin);
    }
    else{
        printf("Correct !");
        getc(stdin);
        fflush(stdin);
    }
}
