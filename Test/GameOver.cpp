#include "GameOver.h"
#include "inGameStatsRenderComponent.h"

GameOver::GameOver()
{
	renderMan = RenderManager::getRenderManager();
	sceneMan  = SceneManager::GetSceneManager();
	createButtons();
	createText();
	sceneMan->AssembleScene();
}

GameOver::~GameOver()
{
	removeButtons();
	removeText();
}

int GameOver::runScene(){
	int buttonPressed = -2;
	inGameStatsRenderComponent inGameStats;
	while (true){
		
		InputManager::getInstance()->update();
		if (InputManager::getInstance()->isKeyDown(KEY_TAB)){
			inGameStats.toggleOn(true);
		}
		else{
			inGameStats.toggleOn(false);
		}
		buttonPressed = checkButtons();
		if (buttonPressed == BUTTON_MENU)
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
	COLOR *color = nullptr;


	///for testing
	Stats::incBaseHealthLost_purple();
	int kills, deaths;
	Stats::addPlayer(NetworkManager::sInstance->GetMyPlayerId(), 2);
	Stats::addPlayer((uint64_t)12634098216351089, 1);
	Stats::incPlayerDied(NetworkManager::sInstance->GetMyPlayerId(), (uint64_t)12634098216351089);
	Stats::playerDied(NetworkManager::sInstance->GetMyPlayerId(), kills, deaths);
	std::cout << kills << " " << deaths << std::endl;
	InputManager::getInstance()->update();
	/////

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
		// have to devide by 1049088.0 to acount for resolution change
		victoryDefeatText->setResourceObject(renderMan->renderText(text.c_str(), color->r, color->g, color->b, ((w * h) * victoryDefeatFontSize) / 1049088.0, "BowlbyOneSC-Regular"));
		victoryDefeatText->setPos((w / 2.0) - (victoryDefeatText->getWidth() / 2.0), (h / 8.0) - (victoryDefeatText->getHeight() / 2.0));
		delete color;
	}

	createStatsText();
	
}

void GameOver::removeText(){
	if (victoryDefeatText){
		victoryDefeatText->setVisible(false);
		sceneMan->RemoveObject(victoryDefeatText, sceneMan->findLayer("layer1"));
	}
	for (auto& iter : statsTexts){
		iter->setVisible(false);
		sceneMan->RemoveObject(iter, sceneMan->findLayer("layer1"));
	}
}

void GameOver::createInGameStatsText(std::string text, COLOR* color, TEXT_POS pos){
	std::cout << text << std::endl;
	SDLRenderObject* sdlText;
	int w, h;
	float x, y;
	renderMan->getWindowSize(&w, &h);
	sdlText = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	// have to devide by 1049088.0 to acount for resolution change
	sdlText->setResourceObject(renderMan->renderText(text.c_str(), color->r, color->g, color->b, ((w * h) * statsFontSize) / 1049088.0, "BowlbyOneSC-Regular"));
	sdlText->setPos((pos * w / 4.0) - (sdlText->getWidth() / 2.0), (h / 4.5) - (sdlText->getHeight() / 2.0) + totalOffest);
	totalOffest += offset;
	statsTexts.push_back(sdlText);
}

void GameOver::findOffest(){
	int w, h;
	renderMan->getWindowSize(&w, &h);
	offset = (((w * h) * statsFontSize) / 1049088.0) * 2;
	totalOffest = offset;
}

void GameOver::createStatsText(){
	findOffest();
	COLOR *yellowColor = new COLOR(255, 255, 0);
	COLOR *purpleColor = new COLOR(200, 0, 200);

	createInGameStatsText(std::to_string(Stats::baseHealthLost_yellow()) + " nest health lost", yellowColor, LEFT);
	createInGameStatsText(std::to_string(Stats::otherTeamMinionsKilled_yellow()) + " minions killed", yellowColor, LEFT);
	createInGameStatsText(std::to_string(Stats::otherTeamPlayersKilled_yellow()) + " enemies killed", yellowColor, LEFT);
	createInGameStatsText(std::to_string(Stats::feathersFired_yellow()) + " feathers thrown", yellowColor, LEFT);
	createInGameStatsText(std::to_string(Stats::abilitiesUsed_yellow()) + " abilities used", yellowColor, LEFT);
	// reseting the offest
	totalOffest = offset;
	createInGameStatsText(std::to_string(Stats::baseHealthLost_purple()) + " nest health lost", purpleColor, RIGHT);
	createInGameStatsText(std::to_string(Stats::otherTeamMinionsKilled_purple()) + " minions killed", purpleColor, RIGHT);
	createInGameStatsText(std::to_string(Stats::otherTeamPlayersKilled_purple()) + " enemies killed", purpleColor, RIGHT);
	createInGameStatsText(std::to_string(Stats::feathersFired_purple()) + " feathers thrown", purpleColor, RIGHT);
	createInGameStatsText(std::to_string(Stats::abilitiesUsed_purple()) + " abilities used", purpleColor, RIGHT);

	delete yellowColor;
	delete purpleColor;
}