#include "MainMenu.h"


MainMenu::MainMenu()
{
	RenderManager::getRenderManager()->zoom = 0.5;
	ResourceManager::GetResourceManager()->setCurrentScope(0);
	RenderManager::getRenderManager()->setBackground("Menu_bg.png");
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
	RenderManager::getRenderManager()->getWindowSize(&w, &h);
	
	// play button
	playButt = bFactory.Spawn(3521, 200.0f, 90.0f, 19);
	GameObjects.AddObject(playButt);
	quitButt = bFactory.Spawn(3522, 200.0f, 150.0f, 22);
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


