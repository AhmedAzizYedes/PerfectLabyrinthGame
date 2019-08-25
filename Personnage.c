#include "Personnage.h"
Personnage* creerPersonnage(char* path,int i,int j){
    Personnage* perso = (Personnage*) malloc(sizeof(Personnage));
    if(perso == NULL)
        exit(EXIT_FAILURE);
    perso->texture = sfTexture_createFromFile(path, NULL);
    if (!perso->texture)
        exit(EXIT_FAILURE);
    perso->sprite = sfSprite_create();
    sfSprite_setTexture(perso->sprite, perso->texture, sfTrue);
    perso->i = i;
    perso->j = j;
    characterSpriteState(perso,DOWN,1);
    return perso;
}

void detruirePersonnage(Personnage* perso){
    if (perso!=NULL){
        sfSprite_destroy(perso->sprite);
        sfTexture_destroy(perso->texture);
        free(perso);
    }
}
void characterSpriteState(Personnage* perso,Direction dir,int state){
    perso->state=state;
    perso->dir=dir;
    sfIntRect rectangle = {32*perso->state,0,32,32};
    switch (perso->dir){
    case UP:
         rectangle.top=96;
        break;
    case DOWN:
         rectangle.top=0;
        break;
    case LEFT:
         rectangle.top=32;
        break;
    case RIGHT:
         rectangle.top=64;
        break;
    }
sfSprite_setTextureRect(perso->sprite, rectangle);
}

void setSpritePosition(sfSprite* sprite,int i,int j){
    sfVector2f position = {i,j};
    sfSprite_setPosition  (sprite,  position);
}
void dessinerPersonnage(sfRenderWindow* window,Personnage* perso,int i,int j){
    setSpritePosition(perso->sprite,j,i);
    sfRenderWindow_drawSprite(window, perso->sprite, NULL);
}
void personnageBouger(sfRenderWindow* window,Carte* carte,Personnage* perso,Direction dir){
    //sfTime delayTime = {82000};
    sfTime delayTime = {60000};
    int i;
    for(i=0;i<8;i++){
    if (i&1==0)
        characterSpriteState(perso,dir,i%3);
    else
        characterSpriteState(perso,dir,(i+1)%3);
    //dessinerCarte(window,carte,0,0);
    switch (dir){
    case UP:
        if(carte->carte[(perso->i-1)*carte->m+perso->j]->tileID==ZLIZ){
            if(((perso->i-carte->i) == 9) && ( carte->i > 0)){
                dessinerCarte(window,carte,i*4,0);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
            }
            else{
                dessinerCarte(window,carte,0,0);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32-i*4,(perso->j-carte->j)*32);
            }
        }
        else{
            dessinerCarte(window,carte,0,0);
            dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
        }
        break;
    case DOWN:
        if(carte->carte[(perso->i+1)*carte->m+perso->j]->tileID==ZLIZ){
            if(((perso->i-carte->i) == 9) && ( carte->i+17 < carte->n)){
                dessinerCarte(window,carte,-i*4,0);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
            }
            else{
                dessinerCarte(window,carte,0,0);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32+i*4,(perso->j-carte->j)*32);
            }
        }
        else{
            dessinerCarte(window,carte,0,0);
            dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
        }
        break;
    case RIGHT:
        if(carte->carte[perso->i*carte->m+perso->j+1]->tileID==ZLIZ){
            if(((perso->j-carte->j) == 11) && ( carte->j+21 < carte->m)){
                dessinerCarte(window,carte,0,-i*4);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
            }
            else{
                dessinerCarte(window,carte,0,0);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32+i*4);
            }
        }
        else{
            dessinerCarte(window,carte,0,0);
            dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
        }
        break;
    case LEFT:
        if(carte->carte[perso->i*carte->m+perso->j-1]->tileID==ZLIZ){
            if(((perso->j-carte->j) == 10) && ( carte->j > 0)){
                dessinerCarte(window,carte,0,i*4);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
            }
            else{
                dessinerCarte(window,carte,0,0);
                dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32-i*4);
            }
        }
        else{
            dessinerCarte(window,carte,0,0);
            dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
        }
        break;
    }
    sfRenderWindow_display(window);
    sfSleep(delayTime);
    }
    switch (dir){
    case UP:
        if(carte->carte[(perso->i-1)*carte->m+perso->j]->tileID==ZLIZ){
            if(((perso->i-carte->i) == 9) && ( carte->i > 0))
                carte->i--;
            perso->i--;
        }

        break;
    case DOWN:
        if(carte->carte[(perso->i+1)*carte->m+perso->j]->tileID==ZLIZ){
            if(((perso->i-carte->i) == 9) && ( carte->i+17 < carte->n))
                carte->i++;
            perso->i++;
        }
        break;
    case RIGHT:
        if(carte->carte[perso->i*carte->m+perso->j+1]->tileID==ZLIZ){
            if(((perso->j-carte->j) == 11) && ( carte->j+21 < carte->m))
                carte->j++;
            perso->j++;
        }
        break;
    case LEFT:
        if(carte->carte[perso->i*carte->m+perso->j-1]->tileID==ZLIZ){
            if(((perso->j-carte->j) == 10) && ( carte->j > 0))
                carte->j--;
            perso->j--;
        }
        break;
    }
    characterSpriteState(perso,dir,1);
    //sfSleep(delayTime);
}


