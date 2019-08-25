#ifndef sceneManager_h
#define sceneManager_h

#include <SFML/Graphics.h>

typedef enum SceneID SceneID;
enum SceneID{
    MAINMENUSCENE,GAMESCENE,EXITSCENE,WINSCENE
};
SceneID sceneManager(sfRenderWindow* window,SceneID sceneId);
#endif
