#include "test.h"


using namespace std;


void render(RenderManager*);

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

		/*while (true){
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
*/
	InputManager* input = InputManager::getInstance();

	InputManager* inputMan = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	renderMan->setBackground("tempbackground.png");
	resourceMan->loadFromXMLFile("source.xml");

	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");


	//Buttons objects
	LButton* gButton = new LButton();

	gButton->setPosition(0, 0);
	std::cout << gButton->getXPosition() << " " << gButton->getYPosition() << std::endl;
	std::cout << input->getMouseX() << " " << input->getMouseY() << std::endl;
	gButton->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 19, gButton->getXPosition(), gButton->getYPosition(),true);
	std::cout << gButton->obj->posX << " " << gButton->obj->posY << std::endl;
	bool loop = true;
	while (loop){

		/*if (input->isKeyDown(KEY_ESCAPE))
			loop = false;*/
		SDL_Event e;

		gButton->handleEvent(&e);
	
		input->update();

		sceneMan->AssembleScene();

		render(renderMan);
	}
	///  SYSTEMS

	SystemNetworkUpdater sysNetwork;
	SystemRenderUpdater sysRenderer;
	SystemInputUpdater sysInput;
	SystemLogicUpdater sysLogic;
	SystemPhysicsUpdater sysPhysics;


	//SystemGameObjectQueue world;

	/// ENTITIES
	PlayerObjectFactory pFactory;
	MinionObjectFactory mFactory;

	map< uint64_t, string > loby = NetworkManager::sInstance->getLobbyMap();

	for (auto &iter : loby){
		bool local = false;
		if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
			local = true;
			cout << "Local Player ID: " << iter.second << ", " << iter.first << endl;
		}
		GameObjects.AddObject(pFactory.Spawn(iter.first, local));
	}

	for (uint64_t i = 0; i < 4; ++i)
		GameObjects.AddObject(mFactory.Spawn(i));



	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	int ID = -1;

	/*while (gameloop) {
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
			//cout << ID << endl;
			for (int j = 0; j < players.size(); ++j){
				if (ID == players[j]->ID){
					players[j]->Read(NetworkManager::sInstance->test.front());
					players[j]->update();
					NetworkManager::sInstance->test.pop();
				}
			}
		}
	
	while (gameloop) {
		inputMan->update();
		NetworkManager::sInstance->UpdateDelay();


		sysInput.InputUpdate(GameObjects.alive_object);
		sysRenderer.RenderUpdate(GameObjects.alive_object);
		sysLogic.LogicUpdate(GameObjects.alive_object);
		sysNetwork.NetworkUpdate(GameObjects.alive_object);
		sysPhysics.PhysicsUpdate(GameObjects.alive_object);


		if (inputMan->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		inputMan->update();

		sceneMan->AssembleScene();

		//render(renderMan);
	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	}*/

	std::cout << renderMan << endl;

	log->close();
	return 0;
}


void render(RenderManager* renderMan) {
	renderMan->update();
}