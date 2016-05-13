#pragma once
#ifndef LOBBY_H
#define LOBBY_H

//#include "main.h"
#include "UIObject.h"
#include "UIObjectFactory.h"
#include "SystemInputUpdater.h"
#include "SystemRenderUpdater.h"
#include "SystemUIUpdater.h"
#include "GameSession.h"
#include "WorldObjectFactory.h"
// Component Includes
#include "Component.h"
#include "UIRenderComponent.h"
#include "UIInputComponent.h"
#include "UIComponent.h"

struct bird{
	UIType birdClass;
	int x, y;
	UIObject* birdPicture;
};

struct player;

class Lobby{
public:
	Lobby();
	~Lobby();

	void runLobby();

private:
	int readyCount;
	void addSlots(SystemUIObjectQueue &q);
	void deleteBirds(SystemUIObjectQueue &q);
	void deletePlayers();
	int playersReady;	
	int numPlayers;
	int maxPlayers = 4;
	int inLobbyNow;
	void assignPlayers();
	void updatePlayers();
	void updateLobby();
	void addNewPlayers();
	void drawBirds(SystemUIObjectQueue &q);
	vector<UIObject*> Birds;
	vector<UIObject*> bottomSlots;
	vector<UIObject*> topSlots;
	void countdown(SystemUIObjectQueue &q);
	void cleanUP(SystemUIObjectQueue &q);
	void createButtons(SystemUIObjectQueue &q);
	void checkPlayerInfo();
	void checkMyReady();
	int yellow, purple;
	void pickTeam();
	UIObject* teamYellow, *teamPurple;
	player* me;
	void beginGame(SystemUIObjectQueue &q);
};

#endif