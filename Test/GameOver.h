#pragma once
#include "Scene.h"
#include "Stats.h"
#include "TextAlignment.h"

class GameOver :
	public Scene
{
public:
	GameOver();
	~GameOver();
	int runScene();
	

private:
	RenderManager* renderMan;
	SceneManager* sceneMan;

	int statsFontSize = 30;
	int victoryDefeatFontSize = 110;

	// Factories
	SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;

	GameObject* mainMenuButt;

	void createButtons();
	int  checkButtons();
	void removeButtons();
	void createText();
	void createStatsText();
	TextAlignment *statsText;
	

	int buttonID;
};

