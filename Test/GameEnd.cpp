#include "GameEnd.h"

GameEnd::GameEnd(){

}

GameEnd::~GameEnd(){

}

void GameEnd::runGameEnd(){
	//display win/loss text respectively, some kind of animation, wait for a few seconds then return
	RenderManager* renderMan = RenderManager::getRenderManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	std::string text;
	int w, h;
	renderMan->getWindowSize(&w, &h);
	/*if (team won){
	text = "Victory!";
	}
	else{
	text = "Defeat!";
	}*/
	text = "Victory!";
	textHUD = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 7000, (float)3*w/7, (float)3*h/7, true);
	textHUD->setResourceObject(renderMan->renderText(text.c_str(), 160, 32, 240, 70, "BowlbyOneSC-Regular"));
	sceneMan->AssembleScene();
	Sleep(3000);
}