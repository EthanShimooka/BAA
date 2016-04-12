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
	std::cout << "Before textHUD calls" << std::endl;
	//Position currently hard-coded, needs to be fixed once we have global screen width/height variables
	textHUD = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 7000, 250, 300, true);
	textHUD->setResourceObject(renderMan->renderText(text.c_str(), 160, 32, 240, 70, "BowlbyOneSC-Regular"));
	std::cout << "Before assemblescene call" << std::endl;
	sceneMan->AssembleScene();
	std::cout << "Before sleep call" << std::endl;
	Sleep(3000);
}