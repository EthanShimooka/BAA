#pragma once
#include "RenderComponent.h"
#include "Stats.h"

class inGameStatsRenderComponent :
	public RenderComponent
{
public:
	inGameStatsRenderComponent(int _background = -1, float scale = 1);
	~inGameStatsRenderComponent();

	int background = -1;
	bool on;
	std::string layer;
	SceneManager* sceneMan;
	RenderManager* rendMan;
	void toggleOn(bool on);
	void toggleOn();
	std::vector<SDLRenderObject*> statsTexts;

	enum _TEXT_POS{
		_LEFT = 1,
		_MIDDLE = 2,
		_RIGHT = 3,
	};

	// color
	struct COLOR{
		int r, g, b;

		COLOR(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {};
	};
	int offset;
	int totalOffest;
	int statsFontSize = 30;

	void createText();
	void createInGameStatsText(std::string text, COLOR* color, _TEXT_POS pos);
};

