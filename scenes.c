#include "scenes.h"
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>

SceneID gameScene(sfRenderWindow* window,Labyrinthe* laby){
    SceneID scene = GAMESCENE;
    /* VARIABLES */
    sfEvent event;
    sfColor color;
    color = sfColor_fromRGB(0,0,0);
    srand(time(NULL));
    int sortie = 1+2*(rand() % laby->m);
    Carte* carte= creerCarte(laby,"images/tiles.png",sortie);
    Personnage* perso = creerPersonnage("images/goku.png",2,1);
    perso->i = carte->n-3;
    perso->j = 1+2*(rand() % laby->m);

    carte->i= (carte->n >= 17)? carte->n-17 : 0;
    if (carte->m < 21)
        carte->j=0;
    else
        carte->j= (perso->j>=10)? ((perso->j + 10 < carte->m)? perso->j -10: carte->m-21): 0;
    /*GAME LOOP*/
    while (sfRenderWindow_isOpen(window) && scene==GAMESCENE){
        // Process events
        while (sfRenderWindow_pollEvent(window, &event)){
            switch (event.type){
            case sfEvtKeyPressed:
                if (sfKeyboard_isKeyPressed (sfKeyRight))
                    personnageBouger(window,carte,perso,RIGHT);
                if (sfKeyboard_isKeyPressed (sfKeyLeft))
                    personnageBouger(window,carte,perso,LEFT);
                if (sfKeyboard_isKeyPressed (sfKeyDown)){
                    personnageBouger(window,carte,perso,DOWN);
                }
                if ( sfKeyboard_isKeyPressed (sfKeyUp)){
                    if ((perso->i == 2)&&(perso->j==sortie)){
                        characterSpriteState(perso,UP,1);
                        dessinerCarte(window,carte,0,0);
                        dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);
                        scene=sceneManager(window,WINSCENE);
                    }

                    else
                        personnageBouger(window,carte,perso,UP);
                }
                if (sfKeyboard_isKeyPressed(sfKeyEscape))
                    scene=MAINMENUSCENE;
                break;
            case sfEvtClosed:
                //sfRenderWindow_close(window);

                scene=EXITSCENE;
                break;
            }
        }
    // Clear the screen
    sfRenderWindow_clear(window, color);
    // Draw the sprite
    dessinerCarte(window,carte,0,0);
    dessinerPersonnage(window,perso,(perso->i-carte->i)*32,(perso->j-carte->j)*32);

    // Update the window
    sfRenderWindow_display(window);
    }
    // Cleanup resources
    detruirePersonnage(perso);
    detruireCarte(carte);
    //return MAINMENU;
    return scene;
}
SceneID mainMenuScene(sfRenderWindow* window,Labyrinthe** laby){
    SceneID scene = MAINMENUSCENE;
    /* VARIABLES */
    int n = (*laby)->n;
    int m = (*laby)->m;
    char N[4]="";
    char M[4]="";
    sprintf(N, "%d",n);
    sprintf(M, "%d",m);
    sfEvent event;
    sfColor color = sfColor_fromRGB(0,0,0);

    sfTexture* backgroundTexture = sfTexture_createFromFile("images/Labyrinth.jpg", NULL);
    sfSprite* backgroundSprite = sfSprite_create();
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);

    sfTexture* playTexture = sfTexture_createFromFile("images/jouer.png", NULL);
    sfSprite* playSprite = sfSprite_create();
    sfSprite_setTexture(playSprite, playTexture, sfTrue);
    setSpritePosition(playSprite,400,475);
    sfIntRect rectangle1 = {0,0,208,98};
    sfSprite_setTextureRect(playSprite, rectangle1);
    sfVector2f factors2 = {.75,.75};
    sfSprite_scale (playSprite,factors2);

    sfTexture* genTexture = sfTexture_createFromFile("images/generer.png", NULL);
    sfSprite* genSprite = sfSprite_create();
    sfSprite_setTexture(genSprite, genTexture, sfTrue);
    setSpritePosition(genSprite,75,475);
    sfIntRect rectangle2 = {0,0,294,98};
    sfSprite_setTextureRect(genSprite, rectangle2);
    sfSprite_scale (genSprite,factors2);

/*LARGEUR LONGEUR*/
sfFont* font;
    sfText* text_long;
    sfText* text_larg;
    sfText* text_n;
    sfText* text_m;
    font = sfFont_createFromFile("Police/CHILLER.ttf");
    if (!font)
        return EXIT_FAILURE;

    text_long = sfText_create();
    sfText_setString(text_long, "Longueur =");
    sfText_setFont(text_long, font);
    sfText_setCharacterSize(text_long, 50);
    sfVector2f  position_long ={45,0};
    sfText_setPosition(text_long, position_long);

    sfTexture* leftarrow1Texture = sfTexture_createFromFile("images/left.png", NULL);
    sfSprite* leftarrow1Sprite = sfSprite_create();
    sfSprite_setTexture(leftarrow1Sprite, leftarrow1Texture, sfTrue);
    setSpritePosition(leftarrow1Sprite,220,20);
    sfVector2f factors3 = {0.15,0.15};
    sfSprite_scale (leftarrow1Sprite,factors3);

    sfTexture* leftarrow2Texture = sfTexture_createFromFile("images/left.png", NULL);
    sfSprite* leftarrow2Sprite = sfSprite_create();
    sfSprite_setTexture(leftarrow2Sprite, leftarrow2Texture, sfTrue);
    setSpritePosition(leftarrow2Sprite,520,20);
    sfSprite_scale (leftarrow2Sprite,factors3);

    sfTexture* rightarrow1Texture = sfTexture_createFromFile("images/right.png", NULL);
    sfSprite* rightarrow1Sprite = sfSprite_create();
    sfSprite_setTexture(rightarrow1Sprite, rightarrow1Texture, sfTrue);
    setSpritePosition(rightarrow1Sprite,330,20);
    sfSprite_scale (rightarrow1Sprite,factors3);

    sfTexture* rightarrow2Texture = sfTexture_createFromFile("images/right.png", NULL);
    sfSprite* rightarrow2Sprite = sfSprite_create();
    sfSprite_setTexture(rightarrow2Sprite, rightarrow2Texture, sfTrue);
    setSpritePosition(rightarrow2Sprite,620,20);
    sfSprite_scale (rightarrow2Sprite,factors3);

    text_n = sfText_create();
    sfText_setString(text_n, N);
    sfText_setFont(text_n, font);
    sfText_setCharacterSize(text_n, 50);
    sfVector2f  position_n ={260,0};
    sfText_setPosition(text_n, position_n);

    text_larg = sfText_create();
    sfText_setString(text_larg, "Largeur =");
    sfText_setFont(text_larg, font);
    sfText_setCharacterSize(text_larg, 50);
    sfVector2f  position_larg ={370,0};
    sfText_setPosition(text_larg, position_larg);

    text_m = sfText_create();
    sfText_setString(text_m, M);
    sfText_setFont(text_m, font);
    sfText_setCharacterSize(text_m, 50);
    sfVector2f  position_m ={550,0};
    sfText_setPosition(text_m, position_m);

    sfVector2u arrowSize = sfTexture_getSize(rightarrow2Texture);
    arrowSize.x*=factors3.x;
    arrowSize.y*=factors3.y;
    sfVector2i mousePos;
    /*GAME LOOP*/
    while (sfRenderWindow_isOpen(window) && scene==MAINMENUSCENE){
        // Process events
        mousePos = sfMouse_getPosition  ( window );
        while (sfRenderWindow_pollEvent(window, &event)){
            switch (event.type){
            case sfEvtKeyPressed:
                //scene=GAMESCENE;
                break;

            case sfEvtClosed:
                //sfRenderWindow_close(window);
                scene=EXITSCENE;
                break;
            case sfEvtMouseButtonPressed:
                if (((mousePos.x < 400+(int) (0.75*208)) && (mousePos.x>400)) && ((mousePos.y < 475+(int) (0.75*89)) && (mousePos.y>475)))
                    if (event.mouseButton.button == sfMouseLeft)
                        scene=GAMESCENE;
                if (((mousePos.x < 75+(int) (0.75*294)) && (mousePos.x>75)) && ((mousePos.y < 475+(int) (0.75*98)) && (mousePos.y>475)))
                    if (event.mouseButton.button == sfMouseLeft){
                        detruireLabyrinthe(*laby);
                        (*laby) =primLabyrinthe(n,m);
                    }
                if (((mousePos.x < 220+arrowSize.x) && (mousePos.x>220)) && ((mousePos.y < 20+arrowSize.y) && (mousePos.y>20)))
                    if (event.mouseButton.button == sfMouseLeft)
                        if(n>1){
                            n = n-1;
                            sprintf(N, "%d",n);
                            sfText_setString(text_n, N);
                        }
                if (((mousePos.x < 330+arrowSize.x) && (mousePos.x>330)) && ((mousePos.y < 20+arrowSize.y) && (mousePos.y>20)))
                    if (event.mouseButton.button == sfMouseLeft){
                            n = n+1;
                            sprintf(N, "%d",n);
                            sfText_setString(text_n, N);
                        }
                if (((mousePos.x < 520+arrowSize.x) && (mousePos.x>520)) && ((mousePos.y < 20+arrowSize.y) && (mousePos.y>20)))
                    if (event.mouseButton.button == sfMouseLeft)
                        if(m>1){
                            m = m-1;
                            sprintf(M, "%d",m);
                            sfText_setString(text_m, M);
                        }
                if (((mousePos.x < 620+arrowSize.x) && (mousePos.x>620)) && ((mousePos.y < 20+arrowSize.y) && (mousePos.y>20)))
                    if (event.mouseButton.button == sfMouseLeft){
                            m = m+1;
                            sprintf(M, "%d",m);
                            sfText_setString(text_m, M);
                        }

                break;
            }
        }
    // Clear the screen
    sfRenderWindow_clear(window, color);


    // Draw sprites
    sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
    sketchMap(window,*laby);
    sfRenderWindow_drawText(window, text_long, NULL);
    sfRenderWindow_drawText(window, text_larg, NULL);
    sfRenderWindow_drawSprite(window, leftarrow1Sprite, NULL);
    sfRenderWindow_drawSprite(window, leftarrow2Sprite, NULL);
    sfRenderWindow_drawSprite(window, rightarrow1Sprite, NULL);
    sfRenderWindow_drawSprite(window, rightarrow2Sprite, NULL);
    sfRenderWindow_drawText(window, text_n, NULL);
    sfRenderWindow_drawText(window, text_m, NULL);
    if (((mousePos.x < 400+(int) (0.75*208)) && (mousePos.x>400)) && ((mousePos.y < 475+(int) (0.75*89)) && (mousePos.y>475)))
        rectangle1.top=98;
    else
        rectangle1.top=0;
    sfSprite_setTextureRect(playSprite, rectangle1);
    sfRenderWindow_drawSprite(window, playSprite, NULL);


    if (((mousePos.x < 75+(int) (0.75*294)) && (mousePos.x>75)) && ((mousePos.y < 475+(int) (0.75*98)) && (mousePos.y>475)))
        rectangle2.top=89;
    else
        rectangle2.top=0;
    sfSprite_setTextureRect(genSprite, rectangle2);
    sfRenderWindow_drawSprite(window, genSprite, NULL);

    // Update the window
    sfRenderWindow_display(window);
    }
    // Cleanup resources
    sfSprite_destroy(playSprite);
    sfTexture_destroy(playTexture);
    sfSprite_destroy(genSprite);
    sfTexture_destroy(genTexture);
    sfSprite_destroy(backgroundSprite);
    sfTexture_destroy(backgroundTexture);
    sfSprite_destroy(leftarrow1Sprite);
    sfTexture_destroy(leftarrow1Texture);
    sfSprite_destroy(leftarrow2Sprite);
    sfTexture_destroy(leftarrow2Texture);
    sfSprite_destroy(rightarrow1Sprite);
    sfTexture_destroy(rightarrow1Texture);
    sfSprite_destroy(rightarrow2Sprite);
    sfTexture_destroy(rightarrow2Texture);
    sfText_destroy(text_long);
    sfText_destroy(text_larg);
    sfText_destroy(text_n);
    sfText_destroy(text_m);
    //return MAINMENU;
    return scene;
}
SceneID winScene(sfRenderWindow* window){
    SceneID scene = WINSCENE;
    /* VARIABLES */
    sfEvent event;
    sfTexture* texture = sfTexture_createFromFile("images/youwin.png", NULL);
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    setSpritePosition(sprite,0,200);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    /*WIN LOOP*/
    while (sfRenderWindow_isOpen(window) && scene==WINSCENE){
        // Process events
        while (sfRenderWindow_pollEvent(window, &event)){
            switch (event.type){
            case sfEvtKeyPressed:
                if (sfKeyboard_isKeyPressed(sfKeyEscape))
                    scene=MAINMENUSCENE;
                break;

            case sfEvtClosed:
                //sfRenderWindow_close(window);
                scene=EXITSCENE;
                break;
            case sfEvtMouseButtonPressed:
                scene=MAINMENUSCENE;
                break;
            }
        }

    }
    // Cleanup resources
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    //return MAINMENU;
    return scene;
}
