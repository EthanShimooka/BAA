#include "test.h"


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

	int numPlayers = 1;

	if (numPlayers != 1){
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
	}
	

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

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

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
	FeatherObjectFactory fFactory;
	PlatformObjectFactory plFactory;

	if (numPlayers != 1){
		map< uint64_t, string > loby = NetworkManager::sInstance->getLobbyMap();

		for (auto &iter : loby){
			bool local = false;
			if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
				local = true;
				cout << "Local Player ID: " << iter.second << ", " << iter.first << endl;
			}
			GameObjects.AddObject(pFactory.Spawn(iter.first, local));
		}
	}
	else{
		GameObjects.AddObject(pFactory.Spawn(10000, true));
	}

	for (uint64_t i = 0; i < 1; ++i) {
		//NOTE: there are currently issues ith the setPos function
		//it only updates the gameobject x,y but the physics compnent (currently)
		//overrides it with the collision box's location
		GameObjects.AddObject(mFactory.Spawn(i))->setPos(i * 50, i * 50);
		//GameObjects.AddObject(fFactory.Spawn(i * 4))->setPos(i * 50 + 5, i * 50 + 5);
	}
	GameObjects.AddObject(plFactory.Spawn(123456))->setPos(0, 400);
	



	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	

	while (gameloop) {
		inputMan->update();
		if (numPlayers != 1)  NetworkManager::sInstance->UpdateDelay();


		//physics testing stuff
		PhysicsListener listener;
		GameWorld* gameWorld = GameWorld::getInstance();
		gameWorld->physicsWorld->SetContactListener(&listener);




		gameWorld->update(); //update physics world
		//end physics testing stuff

		sysInput.InputUpdate(GameObjects.alive_objects);
		sysRenderer.RenderUpdate(GameObjects.alive_objects);
		sysLogic.LogicUpdate(GameObjects.alive_objects);
		if (numPlayers != 1) sysNetwork.NetworkUpdate(GameObjects.alive_objects);
		sysPhysics.PhysicsUpdate(GameObjects.alive_objects);


		if (inputMan->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		inputMan->update();

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