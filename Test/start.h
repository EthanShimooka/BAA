#pragma once

#ifndef START_H
#define START_H

#include "main.h"
#include "ButtonObjectFactory.h"

class Start{
public:
	Start();
	~Start();

	void mainMenu();

	void joinLobby();
	void play();
	void inLobby();
	int waitForInput();
	void removeButtons();

	SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;
	/*SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	SystemLogicUpdater sysLogic;*/

	GameObject* playButt;
};



#endif