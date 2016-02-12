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

	int numPlayers = 4;

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

	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");

	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");

	InputListener* listen = new InputListener();

	vector<Square*> players;
	players.push_back(new Square(100, 100, 1));
	players[players.size() - 1]->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2, players[players.size() - 1]->x, players[players.size() - 1]->y);
	players.push_back(new Square(200, 100, 2));
	players[players.size() - 1]->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, players[players.size() - 1]->x, players[players.size() - 1]->y);
	players.push_back(new Square(300, 100, 3));
	players[players.size() - 1]->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 13, players[players.size() - 1]->x, players[players.size() - 1]->y);
	players.push_back(new Square(300, 200, 4));
	players[players.size() - 1]->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 14, players[players.size() - 1]->x, players[players.size() - 1]->y);
	

	//Square* player1 = new Square(100, 100, 1);
	//player1->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2, player1->x, player1->y);
	//Square* player2 = new Square(200, 200, 2);
	//player2->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, player2->x, player2->y);
	
	Square *localPlayer = players[3];

	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	int ID = -1;

	while (gameloop) {
		NetworkManager::sInstance->ProcessIncomingPackets();
		listen->getInput();
		

		localPlayer->x += listen->input_x;
		localPlayer->y += listen->input_y;

		//cout << player1->obj->posX << "," << player2->obj->posX<< endl;

		localPlayer->update();

		OutputMemoryBitStream outData;
		outData.Write(NetworkManager::sInstance->kPosCC);
		localPlayer->Write(outData);
		NetworkManager::sInstance->sendPacketToAllPeers(outData);
		//cout << "test size: " << NetworkManager::sInstance->test.size() << endl;
		for (int i = 0; i < NetworkManager::sInstance->test.size(); ++i){
			NetworkManager::sInstance->test.front().Read(ID);
			cout << ID << endl;
			for (int j = 0; j < players.size(); ++j){
				if (ID == players[j]->ID){
					players[j]->Read(NetworkManager::sInstance->test.front());
					players[j]->update();
					NetworkManager::sInstance->test.pop();
				}
			}
			/*player2->Read(NetworkManager::sInstance->test.front());
			player2->update();*/
			//NetworkManager::sInstance->test.pop();
		}

		if (input->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		input->update();
		

		sceneMan->AssembleScene();

		//render(renderMan);
	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	std::cout << renderMan << endl;

	log->close();
	return 0;
}


void init(){

}





void render(RenderManager* renderMan) {
	renderMan->update();
}

long double getCurrentTime(){
	long double sysTime = time(0);
	long double sysTimeMS = sysTime * 1000;

	return sysTimeMS;
}