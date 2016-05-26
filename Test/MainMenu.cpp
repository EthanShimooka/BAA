#include "MainMenu.h"


MainMenu::MainMenu()
{
	RenderManager::getRenderManager()->setCameraPoint(0, 0);
	RenderManager::getRenderManager()->zoom = 0.5;
	ResourceManager::GetResourceManager()->setCurrentScope(0);
	RenderManager::getRenderManager()->setBackground("Menu_bg.png");
	RenderManager::getRenderManager()->update();
	createButtons();
	SceneManager::GetSceneManager()->AssembleScene();
}


MainMenu::~MainMenu()
{
}

int MainMenu::runScene(){
	int buttonPressed = -2;

	while (true){
		buttonPressed = checkButtons();
		switch (buttonPressed){
		case BUTTON_PLAY:
			removeButtons();
			return SCENE_LOBBY;
		case BUTTON_QUIT:
			removeButtons();
			return SCENE_END;
		}
	}
}


void MainMenu::createButtons(){
	int w, h;
	float x, y;
	RenderManager* renderMan = RenderManager::getRenderManager();
	renderMan->getWindowSize(&w, &h);
	
	
	// play button
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(1 / 2.0)), (int)(h*(45 / 100.0)));
	playButt = bFactory.Spawn(3521, x, y, 19, 75.0f, 75.0f, 0.75f);
	GameObjects.AddObject(playButt);
	// quit button
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(1 / 2.0)), (int)(h*(55 / 100.0)));
	quitButt = bFactory.Spawn(3522, x, y, 22, 75.0f, 75.0f, 0.75f);
	GameObjects.AddObject(quitButt);
}

int MainMenu::checkButtons(){
	InputManager::getInstance()->update();
	if (dynamic_cast<ButtonLogicComponent*>(playButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed())
		return BUTTON_PLAY;
	if (dynamic_cast<ButtonLogicComponent*>(quitButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed())
		return BUTTON_QUIT;
	return BUTTON_NONE;
}

void MainMenu::removeButtons(){
	GameObjects.DeleteObjects();
}


