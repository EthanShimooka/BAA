#ifndef GAME_H
#define GAME_H

#include "test.h"

class Game{
public:
	Game();
	~Game();

	UIType mainMenu(InputManager* input, RenderManager* renderMan, SceneManager* sceneMan);
};



#endif