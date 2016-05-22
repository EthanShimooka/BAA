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
		}
	}
}


void MainMenu::createButtons(){
	int w, h;
	RenderManager::getRenderManager()->getWindowSize(&w, &h);
	
	// play button
	playButt = bFactory.Spawn(3521, 200.0f, 150.0f, 19, (float)(w / 2.0 + 25), (float)(h / 2.0 - 25));
	GameObjects.AddObject(playButt);
}

int MainMenu::checkButtons(){
	InputManager::getInstance()->update();
	if (dynamic_cast<ButtonLogicComponent*>(playButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed())
		return BUTTON_PLAY;
	return BUTTON_NONE;
}

void MainMenu::removeButtons(){
	GameObjects.DeleteObjects();
}


