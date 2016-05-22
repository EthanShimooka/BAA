#include "inGameStatsRenderComponent.h"


inGameStatsRenderComponent::inGameStatsRenderComponent(int _background, float scale)
{
	sceneMan = SceneManager::GetSceneManager();
	
	layer = "layer1";
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer(layer), _background, 0, 0);
	background = _background;
	objRef->setScale(scale);
	createText();
	toggleOn(false);
}


inGameStatsRenderComponent::~inGameStatsRenderComponent()
{
}

void inGameStatsRenderComponent::toggleOn(bool on){
	this->on = on;
	objRef->setVisible(on);
	statsTexts.toggleAllOn(on);
}

void inGameStatsRenderComponent::toggleOn(){
	on = !on;
	objRef->setVisible(on);
	statsTexts.toggleAllOn(on);
}

void inGameStatsRenderComponent::createText(){
	Stats::mapStat map = Stats::getPlayersStatsMap();
	TextAlignment::COLOR* color = new TextAlignment::COLOR(255, 0, 0);
	std::string text = "";
	for (auto& iter : map){
		statsTexts.createText(text, color, TextAlignment::MIDDLE);
	}
	delete color;
}

void inGameStatsRenderComponent::updateText(){
	Stats::mapStat map = Stats::getPlayersStatsMap();
	TextAlignment::COLOR* purple = new TextAlignment::COLOR(200, 0, 200);
	TextAlignment::COLOR* yellow = new TextAlignment::COLOR(255, 255, 0);
	std::string text = "";
	int i = 0;
	for (auto& iter : map){
		if (iter.second.team == 2) continue;
		text = GamerServices::sInstance->GetRemotePlayerName(iter.first) + ": " + std::to_string(iter.second.kills) + '/' + std::to_string(iter.second.deaths);
		statsTexts.updateText(text, i, yellow);
		++i;
	}
	i = 0;
	for (auto& iter : map){
		if (iter.second.team == 1) continue;
		text = GamerServices::sInstance->GetRemotePlayerName(iter.first) + ": " + std::to_string(iter.second.kills) + '/' + std::to_string(iter.second.deaths);
		statsTexts.updateText(text, i, purple);
		++i;
	}
	delete purple;
	delete yellow;
}

