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
	/*if (team won){
	text = "Victory!";
	}
	else{
	text = "Defeat!";
	}*/
	text = "Victory!";
	textHUD = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 7000, (float)2*SCREEN_WIDTH/6, (float)3*SCREEN_HEIGHT/7, true);
	textHUD->setResourceObject(renderMan->renderText(text.c_str(), 160, 32, 240, 70, "BowlbyOneSC-Regular"));
	sceneMan->AssembleScene();
	Sleep(3000);
}