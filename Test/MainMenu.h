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
	
	//int konamiCode[10];
	std::vector<int> *konamiCode;// (10, 0);
	int konamiIndex;

	SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;

	GameObject* playButt;
	GameObject* quitButt;
	void checkKonami();
};

