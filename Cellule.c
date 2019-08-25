#include "Cellule.h"

Cellule* nouvelleCellule(int id){
    Cellule *c = malloc(sizeof(Cellule));
    c->id=id;
    int i;
    for (i=0;i<4;i++)
        c->mur[i]=true;
    return c;
}

void destructionMurCellule(Cellule* c, Position pos){
    c->mur[pos]=false;
}
void constructionMurCellule(Cellule* c, Position pos){
    c->mur[pos]=true;
}
void detruireCellule(Cellule* cell){
    free(cell);
}
