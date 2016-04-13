#pragma once
#ifndef LOBBY_H
#define LOBBY_H



#include "main.h"
#include "UIObject.h"
#include "WorldObjectFactory.h"
// Component Includes
#include "Component.h"
#include "UIRenderComponent.h"
#include "UIInputComponent.h"
#include "UIComponent.h"

enum TEAM{
	RED = 1,
	BLUE = 2,
	NOTEAM = 3,
};

struct player{
	uint64_t playerId;
	string name;
	bool ready = false;
	int x, y;
	TEAM team;
	UIObjectFactory* playerSlot = new UIObjectFactory();
	UIObjectFactory* birdClass = new UIObjectFactory();
	int classType = CLASS_CHICKEN;
};

class Lobby{
public:
	Lobby();
	~Lobby();

	vector<player*> players;
	void runLobby();
private:
	void addPlayers(SystemUIObjectQueue &q);
	int playersReady;
	int numPlayers;
	int maxPlayers = 4;
	void assignPlayers(SceneManager* scene, RenderManager* rendMan);
	void updateLobby();
	void drawBirds(SystemUIObjectQueue &q);
};

#endif