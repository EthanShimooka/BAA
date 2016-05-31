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
	SystemRenderUpdater sysRenderer;
	SystemLogicUpdater sysLogic;
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
		sysRenderer.RenderUpdate(GameObjects.alive_objects);
		sysLogic.LogicUpdate(GameObjects.alive_objects);
		SceneManager::GetSceneManager()->AssembleScene();
	}
}


void MainMenu::createButtons(){
	int w, h;
	float x, y;
	RenderManager* renderMan = RenderManager::getRenderManager();
	renderMan->getWindowSize(&w, &h);
	
	
	// play button
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(0.91f)), (int)(h*(0.75f)));
	playButt = bFactory.Spawn(3521, x, y, 19, 55.0f, 75.0f, 0.3f);
	ButtonRenderComponent* playRender = dynamic_cast<ButtonRenderComponent*>(playButt->GetComponent(COMPONENT_RENDER));
	playRender->addSecondSprite(31);
	GameObjects.AddObject(playButt);
	// quit button
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(0.91f)), (int)(h*(0.9f)));
	quitButt = bFactory.Spawn(3522, x, y, 22, 55.0f, 75.0f, 0.3f);
	ButtonRenderComponent* quitRender = dynamic_cast<ButtonRenderComponent*>(quitButt->GetComponent(COMPONENT_RENDER));
	quitRender->addSecondSprite(32);
	GameObjects.AddObject(quitButt);

	//configure buttons to work with controller
	ButtonLogicComponent* playLogic = dynamic_cast<ButtonLogicComponent*>(playButt->GetComponent(COMPONENT_LOGIC));
	playLogic->setNavButtons(NULL, quitButt, NULL, NULL);
	playLogic->selectButton();
	ButtonLogicComponent* quitLogic = dynamic_cast<ButtonLogicComponent*>(quitButt->GetComponent(COMPONENT_LOGIC));
	quitLogic->setNavButtons(playButt, NULL, NULL, NULL);
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


