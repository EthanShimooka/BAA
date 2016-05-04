#ifndef START_H
#define START_H

#include "main.h"

class Start{
public:
	Start();
	~Start();

	void mainMenu();

	void joinLobby();
	void play();
	void inLobby();

private:
	void startLobby(SystemUIObjectQueue queue, SystemRenderUpdater sysRend);
	void createMenu(SystemUIObjectQueue queue);
};
#endif