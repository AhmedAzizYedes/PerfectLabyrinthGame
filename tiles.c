#include <stdbool.h>
#include "tiles.h"

Tile* createTile(TileID tileID,sfSprite* spriteTile){
    int i;
    Tile* tile = (Tile*) malloc(sizeof(Tile));
    tile->tileID=tileID;
    tile->sprite=spriteTile;
    switch (tileID){
        case ZLIZ:
            tile->info = (char*) malloc(sizeof(char));
            *(tile->info)=false;
            break;
        case MUR:
            tile->info = (char*) malloc(sizeof(char)*4);
            for(i=0;i<4;i++)
                tile->info[i]=false;
            break;
        case ZLIZMUR:
            tile->info = (char*) malloc(sizeof(char)*4);
            for(i=0;i<4;i++)
                tile->info[i]=false;
            break;
        case EMPTY:
            tile->info=NULL;
            break;
        case EXIT:
            tile->info=NULL;
            break;
    }
    return tile;
}

void drawTile(sfRenderWindow* window,Tile* tile,int i,int j){
    sfIntRect rectangle = {0,0,32,32};
    sfVector2f position = {j,i};
    sfSprite_setPosition (tile->sprite,  position);
    switch (tile->tileID){
        case ZLIZ:
            if(*(tile->info)!=false)
                rectangle.left=32;
            sfSprite_setTextureRect(tile->sprite, rectangle);
            sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            break;
        case MUR:
            if (tile->info[LEFT] && tile->info[RIGHT]){
                rectangle.top=32;
                rectangle.left=32;
            }
            else if(tile->info[LEFT]){
                rectangle.top=32;
                rectangle.left=64;
            }
            else if(tile->info[RIGHT]){
                rectangle.top=32;
                rectangle.left=0;
            }
            else{
                rectangle.top=0;
                rectangle.left=64;
            }
            sfSprite_setTextureRect(tile->sprite, rectangle);
            sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            break;
        case ZLIZMUR:
            rectangle.top=96;
            rectangle.left=32;
            sfSprite_setTextureRect(tile->sprite, rectangle);
            sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            if (!tile->info[LEFT]){
                rectangle.top=96;
                rectangle.left=0;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            if(!tile->info[RIGHT]){
                rectangle.top=96;
                rectangle.left=64;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            if(!tile->info[UP]){
                rectangle.top=64;
                rectangle.left=32;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            if(!tile->info[DOWN]){
                rectangle.top=128;
                rectangle.left=32;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            if(!tile->info[DOWN] && !tile->info[RIGHT]){
                rectangle.top=128;
                rectangle.left=64;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            if(!tile->info[DOWN] && !tile->info[LEFT]){
                rectangle.top=128;
                rectangle.left=0;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            if(!tile->info[UP] && !tile->info[RIGHT]){
                rectangle.top=64;
                rectangle.left=64;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            if(!tile->info[UP] && !tile->info[LEFT]){
                rectangle.top=64;
                rectangle.left=0;
                sfSprite_setTextureRect(tile->sprite, rectangle);
                sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            }
            break;
        case EXIT:
            rectangle.top=160;
            rectangle.left=32;
            sfSprite_setTextureRect(tile->sprite, rectangle);
            sfRenderWindow_drawSprite(window, tile->sprite, NULL);
            break;
    }
}
void destroyTile(Tile* tile){
    free(tile->info);
    free(tile);
}
