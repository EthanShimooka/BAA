#include "GameEnd.h"

GameEnd::GameEnd(){

}

GameEnd::~GameEnd(){

}

//void GameEnd::runGameEnd(vector<player*> players, GameObject* leftBase, GameObject* rightBase){
void GameEnd::runGameEnd(int localTeam, GameObject* leftBase, GameObject* rightBase){
	//display win/loss text respectively, some kind of animation, wait for a few seconds then return
	RenderManager* renderMan = RenderManager::getRenderManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	std::string text = "If this displays it's a bug";
	int switchOn;
	/*player* me = players[0];

	for (unsigned int i = 0; i < players.size(); i++){
		if (GamerServices::sInstance->GetLocalPlayerId() == players[i]->playerId){
			me = players[i];
		}
	}*/

	if (leftBase->health == rightBase->health){
		switchOn = 1;
	}
	else if (leftBase->health > rightBase->health){
		switchOn = 2;
	}
	else if (leftBase->health < rightBase->health){
		switchOn = 3;
	}
	//Left team is purple, right team is yellow
	switch (switchOn)
	{
	case 1://tie
		text = "No Contest!";
		break;
	case 2://leftWins
		if (localTeam == TEAM_PURPLE) text = "Victory!";
		else text = "Defeat!";
		break;
	case 3://rightWins
		if (localTeam == TEAM_PURPLE) text = "Defeat!";
		else text = "Victory!";
		break;
	default:
		break;
	}

	textHUD = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 7000, (float)2 * SCREEN_WIDTH / 6, (float)3 * SCREEN_HEIGHT / 7, true);
	if (localTeam == TEAM_PURPLE) textHUD->setResourceObject(renderMan->renderText(text.c_str(), 160, 32, 240, 70, "BowlbyOneSC-Regular"));
	else if (localTeam == TEAM_YELLOW) textHUD->setResourceObject(renderMan->renderText(text.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular"));
	sceneMan->AssembleScene();
	Sleep(3000);
}