#include "test.h"



//#include "include\network\NetIncludes.h"

using namespace std;

void update();
void render(RenderManager*);
long double getCurrentTime();


int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){

	int numPlayers = 2;

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

	InputListener* listen = new InputListener();

	int something[] = { 2, 12, 13, 14 };
	vector<Player*> players;
	for (int i = 0; i < 4; i++){
		Player* player = new Player(i,50*i-50, 50*i-50);
		player->objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), something[i], player->posX, player->posY);
		players.push_back(player);
	}
	
	Player* localPlayer = players[0];

	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	int ID = -1;

	
	while (gameloop) {
		inputMan->update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		listen->getInput();


		localPlayer->update();

		








		for (int i = 0; i < NetworkManager::sInstance->test.size(); ++i){
			NetworkManager::sInstance->test.front().Read(ID);
			//cout << ID << endl;
			for (int j = 0; j < players.size(); ++j){
				if (ID == players[j]->ID){
					players[j]->updatePlayerFromNetwork(NetworkManager::sInstance->test.front());
					players[j]->update();
					NetworkManager::sInstance->test.pop();
				}
			}
			/*player2->Read(NetworkManager::sInstance->test.front());
			player2->update();*/
			//NetworkManager::sInstance->test.pop();
		}

		if (inputMan->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		sceneMan->AssembleScene();

	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	std::cout << renderMan << endl;

	log->close();
	return 0;
}



long double getCurrentTime(){
	long double sysTime = time(0);
	long double sysTimeMS = sysTime * 1000;

	return sysTimeMS;
}