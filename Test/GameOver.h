#pragma once
#include "Scene.h"
class GameOver :
	public Scene
{
public:
	GameOver(int localTeam, int purpleHealthRemaining, int yellowHealthRemaining);
	/// Destructor
	~GameOver();
	int runScene();
	

private:

	// Factories
	SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;

	GameObject* mainMenuButt;
	int localTeam;
	int purpleHealthLost, yellowHealthLost;
	void createButtons();
	int checkButtons();
	void removeButtons();
	void createText();
	void removeText();
	/// For drawing win/loss text
	SDLRenderObject* victoryDefeatText;
	

	int buttonID;
};

