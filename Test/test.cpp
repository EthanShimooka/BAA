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

	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	/*if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit())
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";

	while (true){
		GamerServices::sInstance->Update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		cout << "state: " << NetworkManager::sInstance->GetState() << endl;
		if (NetworkManager::sInstance->GetState() == 4)
			break;
		if (NetworkManager::sInstance->GetPlayerCount() == 2){
			NetworkManager::sInstance->GetAllPlayersInLobby();
			NetworkManager::sInstance->TryReadyGame();
		}
	}*/

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


	Square* player1 = new Square(100, 100, 1);
	player1->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2, player1->x, player1->y);
	Square* player2 = new Square(200, 200, 2);
	player2->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, player2->x, player2->y);


	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;

	while (gameloop) {
		//NetworkManager::sInstance->ProcessIncomingPackets();
		listen->getInput();

		player2->x += listen->input_x;
		player2->y += listen->input_y;

		//cout << player1->obj->posX << "," << player2->obj->posX<< endl;

		player2->update();

		/*OutputMemoryBitStream outData;
		outData.Write(NetworkManager::sInstance->kPosCC);
		player2->Write(outData);
		NetworkManager::sInstance->sendPacketToAllPeers(outData);*/

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