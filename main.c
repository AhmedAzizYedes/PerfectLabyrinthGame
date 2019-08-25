#define SCREENWIDTH 10
#define SCREENHEIGHT 5

#include <stdlib.h>
#include "sceneManager.h"



int main(){
    /* Create the main window */
    sfVideoMode mode = {(1+2*10)*32, (2+3*5)*32, 32}; // 672 ,544
    sfRenderWindow* window;
    window = sfRenderWindow_create(mode, "Labyrinthe", sfClose, NULL); //sfResize |
    if (!window)
        return EXIT_FAILURE;

    // SET WINDOW ICON
    sfImage* icon;
    icon = sfImage_createFromFile("images/icon.png");
    if (!icon)
        return EXIT_FAILURE;
    sfWindow_setIcon(window, 32, 32,sfImage_getPixelsPtr(icon));
    sfImage_destroy  ( icon ) ;

    /* SCENE MANAGER */
    sceneManager(window,MAINMENUSCENE);

    /* EXIT */
    sfRenderWindow_close(window);
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
