#pragma once
#include "main.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();
	
	virtual int runScene() = 0;
};

typedef enum {
	SCENE_MENU = 1,
	SCENE_LOBBY = 2,
	SCENE_GAME = 3,
	SCENE_GAMEOVER = 4,
	SCENE_END = 5,
} SCENES;
