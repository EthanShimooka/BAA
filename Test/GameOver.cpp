#include "GameOver.h"

GameOver::GameOver()
{
	RenderManager::getRenderManager()->setCameraPoint(0, 0);
	RenderManager::getRenderManager()->setBackground("Menu_bg.png");
	renderMan = RenderManager::getRenderManager();
	sceneMan  = SceneManager::GetSceneManager();
	statsText = new TextAlignment(.25);
	createButtons();
	createText();
	sceneMan->AssembleScene();
}

GameOver::~GameOver()
{
	removeButtons();
	delete statsText;
}

int GameOver::runScene(){
	RenderManager::getRenderManager()->toggleCursor(true);
	int buttonPressed = -2;
	while (true){
		buttonPressed = checkButtons();
		if (buttonPressed == BUTTON_MENU || InputManager::getInstance()->isKeyDown(KEY_ESCAPE))
			return SCENE_MENU;
		sceneMan->AssembleScene();
	}
}

void GameOver::createButtons(){
	

	int w, h;
	float x, y;
	renderMan->getWindowSize(&w, &h);

	// menu button
	
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(0.91f)), (int)(h*(0.85f)));
	mainMenuButt = bFactory.Spawn(buttonID++, x, y, 23, 75.0f, 75.0f, 0.3f);
	if (RenderManager::getRenderManager()->flippedScreen)mainMenuButt->rotation = 180;
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
	std::string text = "";
	TextAlignment::COLOR *color = nullptr;


	if (Stats::baseHealth_purple() == Stats::baseHealth_yellow()){
		text = "No Contest!";
		color = new TextAlignment::COLOR(255, 255, 0);
	}
	else if (Stats::baseHealth_purple() < Stats::baseHealth_yellow()){
		if (Stats::getLocalTeam() == TEAM_PURPLE){
			text = "Victory!";
			color = new TextAlignment::COLOR(0, 153, 0);
		}
		else{
			text = "Defeat!";
			color = new TextAlignment::COLOR(204, 0, 0);
		}
	}
	else if (Stats::baseHealth_purple() > Stats::baseHealth_yellow()){
		if (Stats::getLocalTeam() == TEAM_PURPLE){
			text = "Defeat!";
			color = new TextAlignment::COLOR(204, 0, 0);
		}
		else{
			text = "Victory!";
			color = new TextAlignment::COLOR(0, 153, 0);
		}
	}
	// victory and defeat text
	statsText->setFontSize(110);
	statsText->setStartingYPos(1 / 8.0);
	statsText->createText(text, color, TextAlignment::MIDDLE);
	delete color;

	createStatsText();
	createStatsText2();

}

void GameOver::createStatsText2(){
	TextAlignment::COLOR *yellowColor = new TextAlignment::COLOR(255, 255, 0);
	TextAlignment::COLOR *purpleColor = new TextAlignment::COLOR(200, 0, 200);
	statsText->setStartingYPos(1 / 3.0f);
	statsText->setFontSize(180);
	// yellow team
	statsText->createText(std::to_string(Stats::baseHealth_purple()), yellowColor, 1 / 4.0);

	statsText->resetOffset();

	statsText->createText(std::to_string(Stats::baseHealth_yellow()), purpleColor, 3 / 4.0);

	delete yellowColor;
	delete purpleColor;
}



void GameOver::createStatsText(){
	TextAlignment::COLOR *yellowColor = new TextAlignment::COLOR(255, 255, 0);
	TextAlignment::COLOR *purpleColor = new TextAlignment::COLOR(200, 0, 200);
	statsText->setStartingYPos(1 / 3.0f);
	statsText->setFontSize(60);
	// yellow team
	statsText->createText("", yellowColor, 1 / 4.0);
//	statsText->setFontSize(30);

	statsText->createText("YELLOW TEAM", yellowColor, 1 / 4.0);


	// reset the offset
	statsText->resetOffset();
	// purple team
	//statsText->setFontSize(60);

	statsText->createText("", purpleColor, 3 / 4.0);
//	statsText->setFontSize(30);

	statsText->createText("PURPLE TEAM", purpleColor, 3 / 4.0);

	
	delete yellowColor;
	delete purpleColor;
}