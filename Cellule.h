#ifndef Cellule_h
#define Cellule_h

#include <stdbool.h>

typedef enum Position Position;
enum Position {
HAUT,BAS,GAUCHE,DROITE
};

typedef struct Cellule Cellule;
struct Cellule{
int id;
bool mur[4] ;
};

Cellule* nouvelleCellule(int id);
void detruireCellule(Cellule* cell);
void destructionMurCellule(Cellule* c, Position pos);
void constructionMurCellule(Cellule* c, Position pos);
#endif // graph_h

