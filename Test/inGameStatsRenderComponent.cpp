#include "inGameStatsRenderComponent.h"


inGameStatsRenderComponent::inGameStatsRenderComponent(int _background, float scale)
{
	sceneMan = SceneManager::GetSceneManager();
	rendMan = RenderManager::getRenderManager();
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
	for (auto& iter : statsTexts){
		iter->setVisible(on);
	}
}

void inGameStatsRenderComponent::toggleOn(){
	on = !on;
	objRef->setVisible(on);
	for (auto& iter : statsTexts){
		iter->setVisible(on);
	}
}

void inGameStatsRenderComponent::createText(){
	Stats::mapStat map = Stats::getPlayersStatsMap();
	COLOR* color = new COLOR(255, 0, 0);
	for (auto& iter : map){
		createInGameStatsText(std::to_string(iter.second.deaths), color, _LEFT);
	}
}

void inGameStatsRenderComponent::createInGameStatsText(std::string text, COLOR* color, _TEXT_POS pos){
	std::cout << text << std::endl;
	SDLRenderObject* sdlText;
	int w, h;
	float x, y;
	rendMan->getWindowSize(&w, &h);
	sdlText = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	// have to devide by 1049088.0 to acount for resolution change
	sdlText->setResourceObject(rendMan->renderText(text.c_str(), color->r, color->g, color->b, ((w * h) * statsFontSize) / 1049088.0, "BowlbyOneSC-Regular"));
	sdlText->setPos((pos * w / 4.0) - (sdlText->getWidth() / 2.0), (h / 4.5) - (sdlText->getHeight() / 2.0) + totalOffest);
	totalOffest += offset;
	statsTexts.push_back(sdlText);
}
