#pragma once
#include "RenderComponent.h"
#include "Stats.h"
#include "TextAlignment.h"
#include "include\network\NetIncludes.h"

class inGameStatsRenderComponent :
	public RenderComponent
{
public:
	inGameStatsRenderComponent(int _background = 1, float scale = 1);
	~inGameStatsRenderComponent();

	int background = -1;
	bool on;
	std::string layer;
	SceneManager* sceneMan;
	RenderManager* rendMan;
	TextAlignment statsTexts;
	void toggleOn(bool on);
	void toggleOn();
	void createText();
	void updateText();
};

