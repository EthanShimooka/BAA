#include "GameOver.h"

struct COLOR{
	int r, g, b;

	COLOR(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {};
};

GameOver::GameOver()
{
	createButtons();
	createText();
	SceneManager::GetSceneManager()->AssembleScene();
}

GameOver::~GameOver()
{
	removeButtons();
	removeText();
}

int GameOver::runScene(){
	int buttonPressed = -2;

	while (true){
		buttonPressed = checkButtons();
		if (buttonPressed == BUTTON_MENU)
			return SCENE_MENU;
	}
}

void GameOver::createButtons(){
	RenderManager* renderMan = RenderManager::getRenderManager();

	int w, h;
	float x, y;
	renderMan->getWindowSize(&w, &h);

	// menu button
	renderMan->windowCoordToWorldCoord(x, y, w*(7 / 8.0), h*(90 / 100.0));
	mainMenuButt = bFactory.Spawn(buttonID++, x, y, 23, 75.0f, 75.0f, 0.75f);
	GameObjects.AddObject(mainMenuButt);

}

int GameOver::checkButtons(){
	InputManager::getInstance()->update();
	if (dynamic_cast<ButtonLogicComponent*>(mainMenuButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed())
		return BUTTON_MENU;
	return BUTTON_NONE;
}

void GameOver::removeButtons(){
	GameObjects.DeleteObjects();
}

void GameOver::createText(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	std::string text = "";
	COLOR *color = nullptr;

	if (Stats::baseHealthLost_purple() == Stats::baseHealthLost_yellow()){
		text = "No Contest!";
		color = new COLOR(255, 255, 0);
	}
	else if (Stats::baseHealthLost_purple() < Stats::baseHealthLost_yellow()){
		if (Stats::getLocalTeam() == TEAM_PURPLE){
			text = "Victory!";
			color = new COLOR(0, 153, 0);
		}
		else{
			text = "Defeat!";
			color = new COLOR(204, 0, 0);
		}
	}
	else if (Stats::baseHealthLost_purple() > Stats::baseHealthLost_yellow()){
		if (Stats::getLocalTeam() == TEAM_PURPLE){
			text = "Defeat!";
			color = new COLOR(204, 0, 0);
		}
		else{
			text = "Victory!";
			color = new COLOR(0, 153, 0);
		}
	}
	if (color != nullptr){
		// victory and defeat text
		int w, h;
		float x, y;
		renderMan->getWindowSize(&w, &h);
		victoryDefeatText = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
		victoryDefeatText->setPos(w * (2.4 / 7.0), h * (2.3 / 6.0));
		victoryDefeatText->setResourceObject(renderMan->renderText(text.c_str(), color->r, color->g, color->b, 150, "VT323-Regular"));
		delete color;
	}

}

void GameOver::removeText(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	if (victoryDefeatText){
		victoryDefeatText->setVisible(false);
		sceneMan->RemoveObject(victoryDefeatText, sceneMan->findLayer("layer1"));
	}
}

