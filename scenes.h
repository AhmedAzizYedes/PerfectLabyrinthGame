#ifndef SCENES_H
#define SCENES_H

#include <stdlib.h>
#include "sceneManager.h"
#include "map.h"
#include "Personnage.h"
#include "Labyrinthe.h"

SceneID gameScene(sfRenderWindow* window,Labyrinthe* laby);
SceneID mainMenuScene(sfRenderWindow* window,Labyrinthe** laby);
SceneID winScene(sfRenderWindow* window);
#endif
