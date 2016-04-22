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



class Lobby{
public:
	Lobby();
	~Lobby();

	void runLobby();

private:
	//vector<player*> players;
	void addSlots(SystemUIObjectQueue &q);
	void deleteBirds(SystemUIObjectQueue &q);
	int playersReady;	
	int numPlayers;
	int maxPlayers = 4;
	int inLobbyNow;
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