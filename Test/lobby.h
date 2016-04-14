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
	bool visible;
	int x, y;
	TEAM team;
	UIObject* playerSlot = new UIObject();
	UIObjectFactory* readyButton = new UIObjectFactory();
	int playerChoice;
	UIObjectFactory* birdClass = new UIObjectFactory();
};

extern std::unordered_map<uint64_t, player*> playersInLobby;

class Lobby{
public:
	Lobby();
	~Lobby();

	void runLobby();



private:
	vector<player*> players;
	void addSlots(SystemUIObjectQueue &q);
	int playersReady;
	int numPlayers;
	int maxPlayers = 4;
	void assignPlayers(RenderManager* rendMan);
	void updateLobby();
	void addNewPlayers();
	void drawBirds(SystemUIObjectQueue &q);
	vector<UIObject*> Birds;
	int teamRed;
	void countdown(SystemUIObjectQueue &q);
	void cleanUP(SystemUIObjectQueue &q);
};

#endif