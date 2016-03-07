#ifndef GAME_H
#define GAME_H

#include "test.h"

class Game{
public:
	Game();
	~Game();

	void mainMenu(InputManager* input, RenderManager* renderMan, SceneManager* sceneMan);

	void joinLobby();
	void play();
	void inLobby();
};



#endif