#include "GameOver.h"

GameOver::GameOver()
{
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
	std::string text = "";
	TextAlignment::COLOR *color = nullptr;


	if (Stats::baseHealthLost_purple() == Stats::baseHealthLost_yellow()){
		text = "No Contest!";
		color = new TextAlignment::COLOR(255, 255, 0);
	}
	else if (Stats::baseHealthLost_purple() < Stats::baseHealthLost_yellow()){
		if (Stats::getLocalTeam() == TEAM_PURPLE){
			text = "Victory!";
			color = new TextAlignment::COLOR(0, 153, 0);
		}
		else{
			text = "Defeat!";
			color = new TextAlignment::COLOR(204, 0, 0);
		}
	}
	else if (Stats::baseHealthLost_purple() > Stats::baseHealthLost_yellow()){
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
	
}

void GameOver::createStatsText(){
	TextAlignment::COLOR *yellowColor = new TextAlignment::COLOR(255, 255, 0);
	TextAlignment::COLOR *purpleColor = new TextAlignment::COLOR(200, 0, 200);
	statsText->setStartingYPos(1 / 3.0);
	statsText->setFontSize(30);
	// yellow team
	statsText->createText(std::to_string(Stats::baseHealthLost_yellow()) + " nest health lost", yellowColor, 1 / 4.0);
	statsText->createText(std::to_string(Stats::otherTeamMinionsKilled_yellow()) + " minions killed", yellowColor, 1 / 4.0);
	statsText->createText(std::to_string(Stats::otherTeamPlayersKilled_yellow()) + " enemies killed", yellowColor, 1 / 4.0);
	statsText->createText(std::to_string(Stats::feathersFired_yellow()) + " feathers thrown", yellowColor, 1 / 4.0);
	statsText->createText(std::to_string(Stats::abilitiesUsed_yellow()) + " abilities used", yellowColor, 1 / 4.0);
	// reset the offset
	statsText->resetOffset();
	// purple team
	statsText->createText(std::to_string(Stats::baseHealthLost_purple()) + " nest health lost", purpleColor, 3 / 4.0);
	statsText->createText(std::to_string(Stats::otherTeamMinionsKilled_purple()) + " minions killed", purpleColor, 3 / 4.0);
	statsText->createText(std::to_string(Stats::otherTeamPlayersKilled_purple()) + " enemies killed", purpleColor, 3 / 4.0);
	statsText->createText(std::to_string(Stats::feathersFired_purple()) + " feathers thrown", purpleColor, 3 / 4.0);
	statsText->createText(std::to_string(Stats::abilitiesUsed_purple()) + " abilities used", purpleColor, 3 / 4.0);

	delete yellowColor;
	delete purpleColor;
}