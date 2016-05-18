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
	RenderManager* renderMan;
	SceneManager* sceneMan;
	
	enum TEXT_POS{
		LEFT = 1,
		MIDDLE = 2,
		RIGHT = 3,
	};

	// color
	struct COLOR{
		int r, g, b;

		COLOR(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {};
	};
	int offset;
	int totalOffest;
	int statsFontSize = 30;
	int victoryDefeatFontSize = 110;

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
	void createInGameStatsText(std::string text, COLOR* color, TEXT_POS pos);
	void createStatsText();
	void findOffest();
	/// For drawing win/loss text
	SDLRenderObject* victoryDefeatText;
	vector<SDLRenderObject*> statsText;
	

	int buttonID;
};

