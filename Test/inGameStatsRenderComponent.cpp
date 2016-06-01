#include "inGameStatsRenderComponent.h"
#include "SystemGameObjectQueue.h"



inGameStatsRenderComponent::inGameStatsRenderComponent(int _background, float scale)
{
	sceneMan = SceneManager::GetSceneManager();
	layer = "layer1";
	int w, h;
	RenderManager::getRenderManager()->getWindowSize(&w, &h);
	purple = new TextAlignment::COLOR(160, 32, 240);
	yellow = new TextAlignment::COLOR(250, 165, 10);
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer(layer), _background, -5, 1, true);
	objRef->setPos(w / 2.0f, h / 2.0f);
	background = _background;
	objRef->setScale(scale);
	createText();
	createScoreText();
	toggleOn(false);
}


inGameStatsRenderComponent::~inGameStatsRenderComponent()
{
	sceneMan->RemoveObject(objRef);
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
	std::string text = "";
	int teamYellow = 0;
	int teamPurple = map.size() / 2 + map.size() % 2;
	for (auto& iter : map){
		if (iter.second.team == 2){
			text = GamerServices::sInstance->GetRemotePlayerName(iter.first) + ": " + std::to_string(iter.second.kills) + '/' + std::to_string(iter.second.deaths);
			statsTexts.updateText(text, teamPurple++, purple);
		}
		if (iter.second.team == 1) {
			text = GamerServices::sInstance->GetRemotePlayerName(iter.first) + ": " + std::to_string(iter.second.kills) + '/' + std::to_string(iter.second.deaths);
			statsTexts.updateText(text, teamYellow++, yellow);
		}
	}
}

void inGameStatsRenderComponent::createScoreText(){
	std::string text = "0";
	scoreTexts.setFontSize(80);
	scoreTexts.setStartingYPos(0.92);
	scoreTexts.setStartingXPos(0.20);
	scoreTexts.createText(text, yellow, 0.045);
	scoreTexts.resetOffset();
	scoreTexts.createText(text, purple, 0.955);
}

void inGameStatsRenderComponent::Update(){
	scoreTexts.updateText(std::to_string(Stats::baseHealth_purple()), 0, yellow);
	scoreTexts.updateText(std::to_string(Stats::baseHealth_yellow()), 1, purple);
}