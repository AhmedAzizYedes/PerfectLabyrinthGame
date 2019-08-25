#ifndef TILES_H
#define TILES_H

#include "stdbool.h"
#include <SFML/Graphics.h>

typedef enum Direction Direction;
enum Direction{
UP,DOWN,LEFT,RIGHT
};

typedef enum {
    ZLIZ,MUR,ZLIZMUR,EMPTY,EXIT
} TileID;

typedef struct {
    TileID tileID;
    bool* info;
    sfSprite* sprite;
} Tile;

Tile* createTile(TileID tileID,sfSprite* spriteTile);
void drawTile(sfRenderWindow* window,Tile* tile,int i,int j);
void destroyTile(Tile* tile);
#endif
