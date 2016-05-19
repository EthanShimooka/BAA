#pragma once
#include "Scene.h"
#include "ButtonObjectFactory.h"

class Lobby //: 
	//public Scene
{
public:
	Lobby();
	~Lobby();
	int runScene();

private:
	int numPlayersReady;
	int numPlayers;
	bool ready;
	int selected;

	// Factories
	SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;

	// buttons and slots
	vector<GameObject*> classButt;
	vector<GameObject*> slots;
	vector<GameObject*> readySlots;
	GameObject* readyButt;
	GameObject* backButt;

	uint64_t buttonID;
	SDLRenderObject * playersInLobby;

	// creating buttons, slots, and ...
	void createButtons();
	void createSlots();
	void createClassButts();
	void createPlayerCount();

	// removing buttons, slots, and ...
	void removeButtons();
	void removeSlots();
	void removePlayerCount();
	void removeAllButtons();

	void changePlayerSelectionImage();
	void setFreeSlotsToDefault(int firstSlot);
	int  checkButtons();
	void playerSelection(int classType);
	void playerReady(int value);
	void updateLobby();	
};