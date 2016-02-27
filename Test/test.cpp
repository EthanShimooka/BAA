#include "test.h"

using namespace std;

void update();
void render(RenderManager*);
long double getCurrentTime();


int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){

	int numPlayers = 1;

	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit())
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";

	while (true){
		GamerServices::sInstance->Update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		//cout << "state: " << NetworkManager::sInstance->GetState() << endl;
		if (NetworkManager::sInstance->GetState() == 4)
			break;
		if (NetworkManager::sInstance->GetPlayerCount() == numPlayers){
			//NetworkManager::sInstance->GetAllPlayersInLobby();
			NetworkManager::sInstance->TryReadyGame();
		}
	}

	InputManager* inputMan = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");

	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

	///  SYSTEMS

	SystemNetworkUpdater sysNetwork;
	SystemRenderUpdater sysRenderer;
	SystemInputUpdater sysInput;
	SystemLogicUpdater sysLogic;
	SystemPhysicsUpdater sysPhysics;


	SystemGameObjectQueue world;

	/// ENTITIES


	PlayerObjectFactory pFactory;
	 
	GameObjects.AddObject(pFactory.Spawn(1));


	//vector<Player*> players;

	//Player* localPlayer;
	map< uint64_t, string > loby = NetworkManager::sInstance->getLobbyMap();

	/*

	int i = 0;
	for (auto &iter : loby)
	{
		//cout << iter.second << endl;
		Player* player = new Player(iter.first, 50 * i - 50, 50 * i - 50);
		if (player->ID == NetworkManager::sInstance->GetMyPlayerId()){
			localPlayer = player;
			player->isNetworkControlled = false;
		}
		player->objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), something[i], player->posX, player->posY);
		players.push_back(player);
		i++;
	}

	for (int i = 0; i < players.size(); ++i){
		if (!players[i]->isNetworkControlled)
			cout << players[i]->ID << endl;
	}

	*/




	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	
	while (gameloop) {
		inputMan->update();
		NetworkManager::sInstance->UpdateDelay();



		sysInput.InputUpdate(GameObjects.alive_object);
		sysRenderer.RenderUpdate(GameObjects.alive_object);
		sysLogic.LogicUpdate(GameObjects.alive_object);
		sysNetwork.NetworkUpdate(GameObjects.alive_object);
		sysPhysics.PhysicsUpdate(GameObjects.alive_object);
		 
		//localPlayer->update();
		
		/*
		for (int i = 0; i < NetworkManager::sInstance->test.size(); ++i){
			//iterate though the queue, pop off packets, and create 
			//commands to give to gameobjects
			uint64_t UID;
			NetworkManager::sInstance->test.front().Read(UID);
			//process packet here
			for (int i = 0; i < players.size(); ++i){
				if (players[i]->ID == UID){
					//cout << "ID matched" << endl;
					players[i]->commands.push(NetworkManager::sInstance->test.front());
				}
			}
			NetworkManager::sInstance->test.pop();
		}


		for (int i = 0; i < players.size(); ++i){
			players[i]->update();
		}

		*/


		if (inputMan->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		sceneMan->AssembleScene();

	}

	std::cout << renderMan << endl;

	log->close();
	return 0;
}



long double getCurrentTime(){
	long double sysTime = time(0);
	long double sysTimeMS = sysTime * 1000;

	return sysTimeMS;
}