#include "sceneManager.h"
#include "scenes.h"

SceneID sceneManager(sfRenderWindow* window,SceneID sceneId){
    Labyrinthe *laby = primLabyrinthe(5,10);;
    while (sceneId!=EXITSCENE){
        switch(sceneId){
            case MAINMENUSCENE:
                sceneId = mainMenuScene(window,&laby);
                break;
            case GAMESCENE:
                sceneId = gameScene(window,laby);
                break;
            case WINSCENE:
                sceneId = winScene(window);
                return sceneId;
                break;
        }
    }
    return EXITSCENE;
}
