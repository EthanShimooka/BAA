#pragma once
#include "Scene.h"
#include "Stats.h"

class GameOver :
	public Scene
{
public:
	GameOver();
	/// Destructor
	~GameOver();
	int runScene();
	

private:

	// Factories
	SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;

	GameObject* mainMenuButt;
	//int localTeam;
	//int purpleHealthLost, yellowHealthLost;
	void createButtons();
	int checkButtons();
	void removeButtons();
	void createText();
	void removeText();
	/// For drawing win/loss text
	SDLRenderObject* victoryDefeatText;
	

	int buttonID;
};

