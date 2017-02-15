#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 10
#define TAILLEBAT 3
#define TAILLEFLOTTE 5

typedef struct cellule{
    int x;
    int y;
}cellule;

typedef struct bateau{
    cellule pos[TAILLEBAT];
}bateau;

typedef struct flotte{
    bateau nav[TAILLEFLOTTE];
}flotte;

enum BOOL{
    Vrai,Faux
};


void initcel(cellule *cel);
void Feu(cellule *tir);
void createcel(cellule *cel);
void createbateau(bateau *bateau1);
void modifflotte(flotte *flot,cellule *cel);
void modifbateau(bateau *bateau1,cellule *cel);
void modifcellule(cellule *cel1,cellule *cel2);
void initJoueur(flotte *flot);
void createflotte(flotte *flot);

int verifsortie(cellule *cel);
int verifcase(cellule *cel1,cellule *cel2);
int verifbateau(bateau *bateau1,cellule *cel);
int verifflotte(flotte *flot,cellule *cel);


int main(){

flotte J1,J2;
cellule tir;
cellule victoire;

victoire.x=-1;
victoire.y=-1;

    do{
        printf("J1\n");
        initJoueur(&J1);
        createflotte(&J1);

        printf("J2\n");
        initJoueur(&J2);
        createflotte(&J2);

        printf("J1\n");
        Feu(&tir);
        if(verifflotte(&J2,&tir)==Vrai){
            modifflotte(&J2,&tir);
        }

        printf("J2\n");
        Feu(&tir);
        if(verifflotte(&J1,&tir)==Vrai){
            modifflotte(&J1,&tir);
        }

    }while((verifflotte(&J1,&victoire)==Faux)||(verifflotte(&J2,&victoire)==Faux));

    if(verifflotte(&J1,&victoire)==Faux){
        printf("J2 gagner !!!!!\n");
    }else{
        printf("J1 gagner !!!!!\n");
    }

    return 0;
}

void initcel(cellule *cel){

    cel->x=0;
    cel->y=0;
}

//BUT: demande à l'utilisateur où il veut tirer
//ENTREE: une variable cellule
//SORTIE: les coordonnees du tir
void Feu(cellule *tir){

    do{
        printf("Choisissez votre tir, coordonee X(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&tir->x);
        printf("Choisissez votre tir, coordonee Y(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&tir->y);
        verifsortie(tir);
    }while((tir->x>TAILLE)&&(tir->x<0)&&(tir->y>TAILLE)&&(tir->y<0));
}

void modifflotte(flotte *flot,cellule *cel){

int i;

    for(i=0;i<TAILLEFLOTTE;i++){
        modifbateau(&flot->nav[i],cel);
    }
}

void modifbateau(bateau *navire,cellule *cel){

int i;

    for(i=0;i<TAILLEFLOTTE;i++){
        modifcel(&navire->pos[i],cel);
    }
}

void modifcel(cellule *cel1,cellule *cel2){

    if((cel1->x==cel2->x)&&(cel1->y==cel2->y)){
        cel1->x=(-1);
        cel1->y=(-1);
    }
}

//BUT:Demande a l'utilisateur où il veut placer son bateau
//ENTREE:Cellule du bateau vide, entrée utilisateur
//SORTIE:1 Cellule du bateau remplie
void createcel(cellule *cel){

    do{
        printf("Placez le bateau, coordonnee X(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&cel->x);
        printf("Placez le bateau, coordonnee Y(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&cel->y);
        verifsortie(cel);
    }while((cel->x>TAILLE)&&(cel->x<0)&&(cel->y>TAILLE)&&(cel->y<0));
}

//BUT:Crée un bateau
//ENTREE:Une variable bateau
//SORTIE: 1 variable bateau remplie correctemment
void createbateau(bateau *bateau1){

int i=0;

    for(i=1;i<TAILLEBAT;i++){
        srand(time(NULL));
        if(rand()%2==0){
            bateau1->pos[i].x=bateau1->pos[0].x+1;
            if(verifsortie(&bateau1->pos[i])==Vrai){
                bateau1->pos[i].x=bateau1->pos[0].x-1;
            }
        }else{
            bateau1->pos[i].y=bateau1->pos[0].y+1;
            if(verifsortie(&bateau1->pos[i])==Vrai){
                bateau1->pos[i].y=bateau1->pos[0].y-1;
            }
        }
    }
}

//BUT: vérifie si la cellule se situe dans le terrain
//ENTREE: une variable cellule
//SORTIE: affiche si la coordonnée est validée
int verifsortie(cellule *cel){
    if((cel->x<TAILLE)&&(cel->x>=0)&&(cel->y<TAILLE)&&(cel->y>=0)){
        printf("Coordonnee validee\n");
        return Vrai;
    }else{
        printf("Coordonnee non valide\n");
        return Faux;
    }
}

//BUT: permet de vérifier si les deux cellules se trouvent au même endroit
//ENTREE: deux cellules a comparer
//SORTIE: affiche vrai si les cellules ont les mêmes coordonnées
int verifcase(cellule *cel1,cellule *cel2){

    if((cel1->x==cel2->x)&&(cel1->y==cel2->y)){
        return Vrai;
    }else{
        return Faux;
    }
}

//BUT: vérifie si le bateau se trouve dans la bonne cellule
//ENTREE: 1 variable cellule et une variable bateau
//SORTIE: affiche vrai si le bateau se situe dans une bonne cellule
int verifbateau(bateau *bateau1,cellule *cel){

int i=0;

    for(i=0;i<TAILLEBAT;i++){
        if(verifcase(&bateau1->pos[i],cel)==Vrai){
            return Vrai;
        }
    }
    return Faux;
}


//BUT:Verifie si une cellule appartient a une flotte
//ENTREE:1 variable Cellule et une variable flotte
//SORTIE:Vrai si une Cellule appartient a une flotte
int verifflotte(flotte *flot,cellule *cel){

int i=0;

    for(i=0;i<TAILLEFLOTTE;i++){
        if(verifbateau(&flot->nav[i],cel)==Vrai){
            return Vrai;
        }
    }
    return Faux;
}

void initJoueur(flotte *flot){

int i,j;
int test=0;

    for(i=0;i<TAILLEFLOTTE;i++){
        initcel(&flot->nav[i].pos[0]);
        createcel(&flot->nav[i].pos[0]);
        for(j=0;j<TAILLEBAT;j++){
            if(verifflotte(&flot,&flot->nav[i].pos[j])==Vrai){
                test+=1;
            }
        }
    }
}

void createflotte(flotte *flot){

int i,j;
int test=0;

    for(i=0;i<TAILLEFLOTTE;i++){
        createbateau(&flot->nav[i]);
        for(j=0;j<TAILLEBAT;j++){
            if(verifflotte(&flot,&flot->nav[i].pos[j])==Vrai){
                test+=1;
            }
            if(test!=0){
                printf("Bateaux superposes\n"); // si deux bateaux possèdent les mêmes coordonnées
            }
        }
    }
}
