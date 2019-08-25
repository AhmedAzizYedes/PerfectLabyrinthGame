#include "map.h"

Carte* creerCarte(Labyrinthe* laby,char* path,int sortie){
    Carte* carte;
    carte = (Carte*) malloc(sizeof(Carte));
    carte->texture = sfTexture_createFromFile(path, NULL);
    if (!carte->texture)
        exit (EXIT_FAILURE);
    sfSprite* spriteTile= sfSprite_create();
    sfSprite_setTexture(spriteTile, carte->texture, sfTrue);
    int i,j;

    carte->n=2+(laby->n)*3;
    carte->m=1+(laby->m)*2;
    carte->i=0;
    carte->j=0;
    carte->carte = (Tile**) malloc(carte->n * carte->m * sizeof(Tile*));
    /*******************************/
    /* REMPLISSAGE PAR EMPTY TILES */
    /*******************************/
    for(i=0;i<carte->n;i++)
        for(j=0;j<carte->m;j++)
            carte->carte[i*carte->m+j]=createTile(EMPTY,spriteTile);
    /***********************************/
    /* REMPLISSAGE DES MURS EXTERIEURS */
    /***********************************/
    for(j=0;j<carte->m;j++){
        carte->carte[j]=createTile(ZLIZMUR,spriteTile);
        carte->carte[(carte->n-1)*carte->m+j]=createTile(MUR,spriteTile);
    }

    for(i=1;i<carte->n-1;i++){
        carte->carte[carte->m*i]=createTile(ZLIZMUR,spriteTile);
        carte->carte[carte->m*i+carte->m-1]=createTile(ZLIZMUR,spriteTile);
    }
    /**********************************************************/
    /* Placement des elements du Labyrinthe laby dans la carte*/
    /**********************************************************/

    for(i=0;i<laby->n;i++)
        for(j=0;j<laby->m;j++){
            destroyTile(carte->carte[(2+3*i)*carte->m + (1+2*j)]);
            carte->carte[(2+3*i)*carte->m + (1+2*j)]=createTile(ZLIZ,spriteTile);
            if (laby->c0[i*laby->m+j]->mur[DROITE] == true)
            {
                destroyTile(carte->carte[(2+3*i)*carte->m + (2+2*j)]);
                carte->carte[(2+3*i)*carte->m + (2+2*j)]=createTile(ZLIZMUR,spriteTile);
            }
            else{
                destroyTile(carte->carte[(2+3*i)*carte->m + (2+2*j)]);
                carte->carte[(2+3*i)*carte->m + (2+2*j)]=createTile(ZLIZ,spriteTile);
            }
            if (laby->c0[i*laby->m+j]->mur[BAS] == true)
            {
                destroyTile(carte->carte[(3+3*i)*carte->m + (1+2*j)]);
                carte->carte[(3+3*i)*carte->m + (1+2*j)]=createTile(ZLIZMUR,spriteTile);
            }
            else{
                destroyTile(carte->carte[(3+3*i)*carte->m + (1+2*j)]);
                carte->carte[(3+3*i)*carte->m + (1+2*j)]=createTile(ZLIZ,spriteTile);
            }
        }
    /**********************************************************/
    /* Placement des elements du Labyrinthe laby dans la carte*/
    /**********************************************************/
    Tile* workingTile;
    int empty = (carte->n-2)*carte->m-2*(carte->n-2)-3*(laby->n*(laby->m-1))-2*laby->n;
    while (empty>0)
        for(i=1;i<carte->n-1;i++)
            for(j=1;j<carte->m-1;j++){
            workingTile = carte->carte[i*carte->m + j];
            switch (workingTile->tileID){
            case EMPTY:
                if ((carte->carte[i*carte->m + j-1]->tileID == ZLIZMUR || carte->carte[i*carte->m + j+1]->tileID == ZLIZMUR || carte->carte[(i-1)*carte->m + j]->tileID == ZLIZMUR ) && (carte->carte[(i+1)*carte->m + j]->tileID != ZLIZ)){
                    destroyTile(workingTile);
                    carte->carte[i*carte->m + j] = createTile(ZLIZMUR,spriteTile);
                }
                else if ((carte->carte[(i-1)*carte->m + j]->tileID == ZLIZMUR ) && (carte->carte[(i+1)*carte->m + j]->tileID == ZLIZ)){
                    destroyTile(workingTile);
                    carte->carte[i*carte->m + j] = createTile(MUR,spriteTile);
                }
                else if ((carte->carte[(i-1)*carte->m + j]->tileID == ZLIZ) && (carte->carte[(i+1)*carte->m + j]->tileID == ZLIZ)){
                    destroyTile(workingTile);
                    carte->carte[i*carte->m + j] = createTile(ZLIZ,spriteTile);
                }
                else if (carte->carte[(i+1)*carte->m + j]->tileID == ZLIZMUR){
                    destroyTile(workingTile);
                    carte->carte[i*carte->m + j] = createTile(ZLIZMUR,spriteTile);
                }
                else
                    empty++;
                empty--;
                //if (((carte->carte[(i-1)*carte->m + j]->tileID == ZLIZ) && (carte->carte[(i+1)*carte->m + j]->tileID == ZLIZ)) || ((carte->carte[i*carte->m + j-1]->tileID == ZLIZ) && (carte->carte[i*carte->m + j+1]->tileID == ZLIZ))){
                //    destroyTile(workingTile);
                //    carte->carte[i*carte->m + j] = createTile(ZLIZ,spriteTile);
                //}
                break;
            default:
                break;
            }
            }
    /***************************************/
    /* Ajustement des parametres des TILES */
    /***************************************/
    for(i=0;i<carte->n;i++)
        for(j=0;j<carte->m;j++){
        workingTile = carte->carte[i*carte->m + j];
        switch (workingTile->tileID){
        case ZLIZ:
            if ((carte->carte[i*carte->m + j-1]->tileID == MUR) || (carte->carte[i*carte->m + j-1]->tileID == ZLIZMUR))
             carte->carte[i*carte->m + j]->info[0]=true;
            break;
        case MUR:
            if ((j>0) && (carte->carte[i*carte->m + j-1]->tileID != ZLIZ))
                carte->carte[i*carte->m + j]->info[LEFT]=true;
            if ((j<carte->m-1)&&(carte->carte[i*carte->m + j+1]->tileID != ZLIZ))
                carte->carte[i*carte->m + j]->info[RIGHT]=true;
            break;
        case ZLIZMUR:
            if ((j>0) && (carte->carte[i*carte->m + j-1]->tileID == ZLIZMUR))
                carte->carte[i*carte->m + j]->info[LEFT]=true;
            if ((j<carte->m-1)&&(carte->carte[i*carte->m + j+1]->tileID == ZLIZMUR))
                carte->carte[i*carte->m + j]->info[RIGHT]=true;
            if ((i>0) && (carte->carte[(i-1)*carte->m + j]->tileID == ZLIZMUR))
                carte->carte[i*carte->m + j]->info[UP]=true;
            if ((i<carte->n-1)&&(carte->carte[(i+1)*carte->m + j]->tileID == ZLIZMUR))
                carte->carte[i*carte->m + j]->info[DOWN]=true;
            break;
        default:
            break;
        }
        }
    if ((sortie > 0) && (sortie<carte->m)){
        destroyTile(carte->carte[carte->m+sortie]);
        carte->carte[carte->m+sortie]=createTile(EXIT,spriteTile);
    }
    return carte;
}
void dessinerCarte(sfRenderWindow* window,Carte* carte,int x,int y){
    int i;
    int j;

    int add1 = (carte->n > 17)? (2+3*5): carte->n;
    int add2 = (carte->m > 21)? (1+2*10): carte->m;
    for(i=carte->i;i<carte->i+add1;i++)
        for(j=carte->j;j<carte->j+add2;j++)
            drawTile(window,carte->carte[i*carte->m+j],(i-carte->i)*32+x,(j-carte->j)*32+y);

    if (x>0)
        for(j=carte->j;j<carte->j+add2;j++)
            drawTile(window,carte->carte[(carte->i-1)*carte->m+j],-32+x,(j-carte->j)*32+y);
    else if(x<0)
        for(j=carte->j;j<carte->j+add2;j++)
            drawTile(window,carte->carte[(carte->i+(2+3*5))*carte->m+j],17*32+x,(j-carte->j)*32+y);
    if (y>0)
        for(i=carte->i;i<carte->i+add1;i++)
            drawTile(window,carte->carte[i*carte->m+carte->j-1],(i-carte->i)*32+x,-32+y);
    else if (y<0)
        for(i=carte->i;i<carte->i+add1;i++)
            drawTile(window,carte->carte[i*carte->m+carte->j+1+2*10],(i-carte->i)*32+x,21*32+y);
}

void detruireCarte(Carte* carte){
    if (carte!=NULL){
        int i,j;
        sfSprite_destroy(carte->carte[0]->sprite);
        for(i=carte->i;i<carte->n;i++)
            for(j=carte->j;j<carte->m;j++)
                destroyTile(carte->carte[i*carte->m+j]);
        sfTexture_destroy(carte->texture);
        free(carte->carte);
        free(carte);
    }
}
void sketchMap(sfRenderWindow* window,Labyrinthe* laby){
    int n=laby->n,m=laby->m;
    int i,j;
    float hauteur = 400.0 / n;
    float largeur = 628.0 / m;
    sfColor color = sfColor_fromRGBA(255,255,255,175);
    sfColor color1 = sfColor_fromRGB(0,0,0);
    sfVector2f  origin  = {22,72};
    sfVector2f  size  = {628,400};
    sfRectangleShape* rectangle = sfRectangleShape_create();
    sfRectangleShape_setFillColor  ( rectangle,  color  );
    sfRectangleShape_setPosition( rectangle, origin);
    sfRectangleShape_setSize( rectangle, size);

    sfRectangleShape* hor = sfRectangleShape_create();
    sfRectangleShape_setFillColor  ( hor,  color1  );
    sfRectangleShape_setPosition( hor, origin);
    size.x=largeur;
    size.y=1;
    sfRectangleShape_setSize( hor, size);

    sfRectangleShape* ver = sfRectangleShape_create();
    sfRectangleShape_setFillColor  ( ver,  color1  );
    sfRectangleShape_setPosition( ver, origin);
    size.x=1;
    size.y=hauteur;
    sfRectangleShape_setSize( ver, size);

    sfRenderWindow_drawRectangleShape  ( window, rectangle,  NULL );

    for (i=0;i<n;i++)
        for (j=0;j<m;j++){
            if (laby->c0[i*m+j]->mur[BAS] == true ){
                origin.x=22+j*largeur;
                origin.y=72+(i+1)*hauteur;
                sfRectangleShape_setPosition( hor, origin);
                sfRenderWindow_drawRectangleShape  ( window,hor,NULL);
            }
            if (laby->c0[i*m+j]->mur[HAUT] == true ){
                origin.x=22+j*largeur;
                origin.y=72+i*hauteur;
                sfRectangleShape_setPosition( hor, origin);
                sfRenderWindow_drawRectangleShape  ( window,hor,NULL);
            }
            if (laby->c0[i*m+j]->mur[GAUCHE] == true ){
                origin.x=22+j*largeur;
                origin.y=72+i*hauteur;
                sfRectangleShape_setPosition( ver, origin);
                sfRenderWindow_drawRectangleShape  ( window,ver,NULL);
            }
            if (laby->c0[i*m+j]->mur[DROITE] == true ){
                origin.x=22+(j+1)*largeur;
                origin.y=72+i*hauteur;
                sfRectangleShape_setPosition( ver, origin);
                sfRenderWindow_drawRectangleShape  ( window,ver,NULL);
            }
        }

    sfRectangleShape_destroy (rectangle);
    sfRectangleShape_destroy (hor);
    sfRectangleShape_destroy (ver);
}
