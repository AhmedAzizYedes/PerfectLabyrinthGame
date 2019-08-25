#ifndef Labyrinthe_h
#define Labyrinthe_h

#include "Cellule.h"

typedef struct Labyrinthe Labyrinthe;
struct Labyrinthe
{
    int n,m;
    Cellule** c0;
};

Labyrinthe *initialisationLabyrinthe(int n,int m);
void afficherLabyrinthe(Labyrinthe *laby);
void destructionMur(Labyrinthe* laby,int i,int j, Position pos);
void constructionMur(Labyrinthe* laby,int i,int j, Position pos);
int idCellule(Labyrinthe* laby,int id,Position pos);
bool estIsole(Labyrinthe* laby,int id);
void detruireLabyrinthe(Labyrinthe* laby);
//bool existeChemin(Labyrinthe* laby,int i0,int j0,int i1,int j1);
#endif
