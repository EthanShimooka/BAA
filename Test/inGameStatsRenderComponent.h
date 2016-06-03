#pragma once
#include "RenderComponent.h"
#include "Stats.h"
#include "TextAlignment.h"
#include "include\network\NetIncludes.h"

class inGameStatsRenderComponent :
	public RenderComponent
{
public:
	inGameStatsRenderComponent(int _background = 1212, float scale = 1);
	~inGameStatsRenderComponent();

	int background = -1;
	bool on;
	bool team;
	std::string layer;
	SceneManager* sceneMan;
	RenderManager* rendMan;
	TextAlignment statsTexts;
	TextAlignment scoreTexts;
	void toggleOn(bool on);
	void toggleOn();
	void createText();
	void updateText();
	void createScoreText();
	void Update();

	TextAlignment::COLOR* purple;
	TextAlignment::COLOR* yellow;

};

