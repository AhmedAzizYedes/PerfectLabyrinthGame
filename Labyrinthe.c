#include <stdio.h>
#include <stdlib.h>

#include "Labyrinthe.h"

Labyrinthe *initialisationLabyrinthe(int n,int m){
    Labyrinthe *laby = malloc(sizeof(Labyrinthe));

    if (laby == NULL )
    {
        exit(EXIT_FAILURE);
    }

    laby->n=n;
    laby->m=m;
    laby->c0 = (Cellule**) malloc(n*m*sizeof(Cellule*));

    int i,j;
    for (i=0;i<n;i++)
        for (j=0;j<m;j++)
            laby->c0[i*m+j]=nouvelleCellule(i*m+j);
    return laby;
}

void afficherLabyrinthe(Labyrinthe *laby){
    int n=laby->n,m=laby->m;
    int i,j;

    printf(" ");
    for (j=0;j<m*2-1;j++)
        printf("_");
    printf(" \n");

    for (i=0;i<n;i++){
        printf("|");
        for (j=0;j<m;j++){
            if (laby->c0[i*m+j]->mur[BAS] == true )
                printf("_");
            else
                printf(" ");

            if (laby->c0[i*m+j]->mur[DROITE] == true ){
                printf("|");
            }
            else
                printf(" ");
        }
        printf("\n");
    }

}
void destructionMur(Labyrinthe* laby,int i,int j, Position pos){
    int n = laby->n;
    int m = laby->m;
    switch (pos){
        case HAUT:
            if (i!=0){
                laby->c0[i*m+j]->mur[HAUT] = false;
                laby->c0[(i-1)*m+j]->mur[BAS] = false;
            }
            break;
        case BAS:
            if (i!=n){
                laby->c0[i*m+j]->mur[BAS] = false;
                laby->c0[(i+1)*m+j]->mur[HAUT] = false;
            }
            break;
        case GAUCHE:
            if (j!=0){
                laby->c0[i*m+j]->mur[GAUCHE] = false;
                laby->c0[i*m+j-1]->mur[DROITE] = false;
            }
            break;
        case DROITE:
            if (j!=m){
                laby->c0[i*m+j]->mur[DROITE] = false;
                laby->c0[i*m+j+1]->mur[GAUCHE] = false;
            }
            break;
    }
}
void constructionMur(Labyrinthe* laby,int i,int j, Position pos){
    int n = laby->n;
    int m = laby->m;
    switch (pos){
        case HAUT:
            if (i!=0){
                laby->c0[i*m+j]->mur[HAUT] = true;
                laby->c0[(i-1)*m+j]->mur[BAS] = true;
            }
            break;
        case BAS:
            if (i!=n){
                laby->c0[i*m+j]->mur[BAS] = true;
                laby->c0[(i+1)*m+j]->mur[HAUT] = true;
            }
            break;
        case GAUCHE:
            if (j!=0){
                laby->c0[i*m+j]->mur[GAUCHE] = true;
                laby->c0[i*m+j-1]->mur[DROITE] = true;
            }
            break;
        case DROITE:
            if (j!=m){
                laby->c0[i*m+j]->mur[DROITE] = true;
                laby->c0[i*m+j+1]->mur[GAUCHE] = true;
            }
            break;
    }
}
int idCellule(Labyrinthe* laby,int id,Position pos){
    int i = id / laby->m;
    int j = id % laby->m;
    if (((i < 0) || (i >= laby->n)) || ((j < 0) || (j >= laby->m)))
        return -2;
    switch (pos){
    case DROITE:
        if ((j+1)>=laby->m)
            return -1;
        else
            return (i*laby->m)+j+1;
        break;
    case GAUCHE:
        if ((j-1)<0)
            return -1;
        else
            return (i*laby->m)+j-1;
        break;
    case BAS:
        if ((i+1)>=laby->n)
            return -1;
        else
            return ((i+1)*laby->m)+j;
        break;
    case HAUT:
        if ((i-1)<0)
            return -1;
        else
            return ((i-1)*laby->m)+j;
        break;
    }
}
bool estIsole(Labyrinthe* laby,int id){
    int i = id / laby->m;
    int j = id % laby->m;
    if (((i < 0) || (i >= laby->n)) || ((j < 0) || (j >= laby->m)))
        return false;
    else
        return (laby->c0[id]->mur[DROITE] && laby->c0[id]->mur[GAUCHE] &&laby->c0[id]->mur[HAUT] &&laby->c0[id]->mur[BAS]);
}
void detruireLabyrinthe(Labyrinthe* laby){
    int i,j;
    for(i=0;i<laby->n;i++)
        for(j=0;j<laby->m;j++)
            detruireCellule(laby->c0[i*laby->m+j]);
    free(laby->c0);
    free(laby);
}
