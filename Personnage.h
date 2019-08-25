#ifndef PERSO_H
#define PERSO_H

#include "map.h"

typedef struct Personnage Personnage;
struct Personnage{
    sfTexture* texture;
    sfSprite* sprite;
    int i,j;
    Direction dir;
    int state;
};
Personnage* creerPersonnage(char* path,int i, int j);
void detruirePersonnage(Personnage* perso);
void dessinerPersonnage(sfRenderWindow* window,Personnage* perso,int i,int j);
void characterSpriteState(Personnage* perso,Direction dir,int state);
void setSpritePosition(sfSprite* sprite,int i,int j);
void personnageBouger(sfRenderWindow* window,Carte* carte,Personnage* perso,Direction dir);
#endif
