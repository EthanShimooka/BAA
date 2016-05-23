#pragma once
#include "Scene.h"
class MainMenu :
	public Scene
{
public:
	MainMenu();
	~MainMenu();
	int runScene();

private:
	void createButtons();
	int checkButtons();
	void removeButtons();
	

	SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;

	GameObject* playButt;
	GameObject* quitButt;
};

