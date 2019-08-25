#ifndef MAP_H
#define MAP_H
#include <stdlib.h>
#include "tiles.h"
#include "Labyrinthe.h"

typedef struct {
    Tile** carte;
    sfTexture* texture;
    unsigned int n;
    unsigned int m;
    unsigned int i;
    unsigned int j;
} Carte;

Carte* creerCarte(Labyrinthe* laby,char* path,int sortie);
void dessinerCarte(sfRenderWindow* window,Carte* carte,int x,int y);
void detruireCarte(Carte* carte);
void sketchMap(sfRenderWindow* window,Labyrinthe* laby);
#endif
