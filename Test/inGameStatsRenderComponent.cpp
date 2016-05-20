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
	std::string text = "asdfasdfasdf";
	for (auto& iter : map){
		//text = 
		statsTexts.createText(text, color, TextAlignment::MIDDLE);
	}
	delete color;
}