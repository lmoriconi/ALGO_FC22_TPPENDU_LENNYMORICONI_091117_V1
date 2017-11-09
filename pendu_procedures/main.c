//LENNY MORICONI

//BUT : Programme qui demande à un joueur 1 de saisir une chaîne de caractère à trouver, puis à un joueur 2 de saisir un caractère afin de deviner le mot. Le joueur 2 a le droit à 7 erreurs. Le mot à trouver doit contenir au minimum 3 caractères.
//ENTREE : Chaîne de caractères à trouver saisie par joueur 1, caractère proposé par joueur 2.
//SORTIE : A chaque saisie de joueur 2 : nombre d'essais restants, mot caché complété des éventuels caractères trouvés par joueur 2, "Faux !" si proposition erronée, sinon "Correct !".

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//CONSTANTES
#define TAILLE 30   //taille maximale d'une chaîne de caractères
#define VIE 7       //nombre d'erreurs que le joueur 2 peut commettre
#define MIN 3       //taille minimale du mot à trouver

//PROTOTYPES
void saisieMot(char mot[TAILLE],int *ptLongueurMot);        //saisie du mot à trouver par le joueur 1
void minuscule(char mot[TAILLE], int longueurMot);          //vérifie que le mot saisi par joueur 1 est en minuscule et change les caractères qui sont en majuscules
void cacherMot(char ptMotCache[TAILLE],int longueurMot);    //crée un mot caché qui sera complété des éventuelles bonnes réponses du joueur 2
void proposition(char *ptSaisie,char motCache[TAILLE],int cptEssai);    //proposition d'un caractère par joueur 2
void comparer(char motCache[TAILLE],char mot[TAILLE],char saisie,int longueurMot,int *ptCptEssai);  //compare la proposition du joueur 2 avec les lettres du mot à trouver

int main()
{
//DECLARATIONS VARIABLES
    char mot[TAILLE]="";
    char motCache[TAILLE]="";
    char saisie='.';    //variable set à '.' pour ne pas la laisser vide
    int cptEssai=VIE;
    int longueurMot=0;

//PROGRAMME PRINCIPAL
    saisieMot(mot,&longueurMot);

    minuscule(mot,longueurMot);

    cacherMot(motCache,longueurMot);

    //le joueur 2 propose des lettres tant qu'il n'a pas trouvé toutes les lettres du mot à trouver ou qu'il n'a pas commis 7 erreurs

    while(strcmp(motCache,mot)!=0 && cptEssai>0){
        proposition(&saisie,motCache,cptEssai);
        comparer(motCache,mot,saisie,longueurMot,&cptEssai);
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

//DEFINITION PROCEDURES

//BUT : procédure qui demande au joueur 1 de saisir une chaîne de caractères à trouver et qui vérifie que la taille de ce mot est supérieure ou égale à 3 caractères
//ENTREE : une chaîne de caractère saisie par le joueur 1
//SORTIE : un message d'erreur si la taille de la chaîne est inférieure à 3 caractères

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

//BUT : procédure qui vérifie que le mot saisi par joueur 1 dans "saisieMot" est en minuscules, sinon change les caractères en minuscules
//ENTREE : chaîne de caractère saisie par joueur 1 dans "saisieMot"
//SORTIE : chaîne de caractère en minuscules

void minuscule(char mot[TAILLE], int longueurMot){
    int i = 0;
    for(i=0;i<longueurMot;i++){
        if(isupper(mot[i])!=0){
            mot[i]=tolower(mot[i]);
        }
    }
}

//BUT : procédure qui crée un mot caché de taille égale au mot à trouver et visible avant chaque saisie par le joueur 2. Ce mot caché informe le joueur 2 sur la taille du mot à trouver et affiche les éventuels caractères corrects trouvés ce dernier.

void cacherMot(char motCache[TAILLE],int longueurMot){
    int i=0;
    for(i=0;i<longueurMot;i++){
        motCache=strcat(motCache,"*");
    }
}

//BUT : procédure qui affiche le mot caché, le nombre d'essais restants et propose au joueur 2 de saisir un caractère, transforme le caractère saisi en minuscule si joueur 2 a saisi une majuscule
//ENTREE : joueur 2 saisit un caractère
//SORTIE : mot caché complété des éventuels caractères déjà trouvés, nombre d'essais restants

void proposition(char *ptSaisie,char motCache[TAILLE],int cptEssai){
    printf("Mot a trouver : %s\n",motCache);
    printf("Joueur 2, proposez une lettre. Il vous reste %d essai(s) :\n",cptEssai);
    *ptSaisie=getchar();
    if(isupper(*ptSaisie)!=0){
        *ptSaisie=tolower(*ptSaisie);   //si le caractère saisi par le joueur 2 est en majuscule, on le transforme en minuscule
    }
    fflush(stdin);
}

//BUT : procédure qui vérifie si le caractère saisit par le joueur 2 dans la procédure "proposition" est dans le mot à trouver
//ENTREE : caractère saisit par le joueur 2 dans la procédure "proposition"
//SORTIE : si le caractère saisit existe dans le mot à trouver, alors le programme affiche "Correct !", sinon "Faux !"

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
