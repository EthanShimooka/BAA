#include "test.h"
#include <functional>
#include <crtdbg.h>

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

	int numPlayers = 1;

	// don't need to change this line
	int numLobbyPlayer = 0;


	if (numPlayers != 1){
		if (!GamerServices::StaticInit())
			std::cout << "Failed to initialize Steam" << "\n";

		if (!NetworkManager::StaticInit())
			std::cout << "NetworkManager::StaticInit() failed!" << "\n";

		while (true){
			GamerServices::sInstance->Update();
			NetworkManager::sInstance->ProcessIncomingPackets();
			if (numLobbyPlayer != NetworkManager::sInstance->GetPlayerCount()){
				numLobbyPlayer = NetworkManager::sInstance->GetPlayerCount();
				NetworkManager::sInstance->GetAllPlayersInLobby();
				cout << endl << endl;
			}
			//cout << "state: " << NetworkManager::sInstance->GetState() << endl;
			if (NetworkManager::sInstance->GetState() == 4)
				break;
			if (NetworkManager::sInstance->GetPlayerCount() == numPlayers){
				//NetworkManager::sInstance->GetAllPlayersInLobby();
				NetworkManager::sInstance->TryReadyGame();
			}
		}
	}


	InputManager* input = InputManager::getInstance();
	AudioManager* audioMan = AudioManager::getAudioInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(1600, 900, false, "Birds At Arms");
	renderMan->setBackground("tempbackground.png");
	resourceMan->loadFromXMLFile("source.xml");
	renderMan->zoom = 0.25;

	audioMan->loadAllAudio();
	std::cout << audioMan->audioObjects.size() << std::endl;
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");
	input->update();
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
	GameObject * player = NULL;

	/// try to join a game and give each user a unique character in the game
	if (numPlayers != 1){
		map< uint64_t, string > loby = NetworkManager::sInstance->getLobbyMap();

		for (auto &iter : loby){
			bool local = false;
			if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
				local = true;
				cout << "Local Player ID: " << iter.second << ", " << iter.first << endl;
				player = GameObjects.AddObject(pFactory.Spawn(iter.first, local));
			}
			else{
				GameObjects.AddObject(pFactory.Spawn(iter.first, local));
			}
		}
	}
	/// create a local player with ID of 10000
	else{
		player = GameObjects.AddObject(pFactory.Spawn(10000, true));
	}

	for (int i = 0; i < 3; i++){

		GameObjects.AddObject(plFactory.Spawn((321556 + (i)), (i * 340), 240, 0));
		GameObjects.AddObject(plFactory.Spawn((543543 + i), (i * 340), -240, 0));
		GameObjects.AddObject(plFactory.Spawn((322556 + (i)), (-i * 340), 240, 0));
		GameObjects.AddObject(plFactory.Spawn((543643 + i), (-i * 340), -240, 0));


	}




	//GameObjects.AddObject(mFactory.Spawn(2000, -100, -100, 200, true));


	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	int var = 0;


	float size = 6;
	float ratio = 0.7;
	int armswing = size;
	int moveSpd = 1;
	int pressed = 0;
	int pressedTime = 3;
	int rotation = 0;


	audioMan->playByName("bgmfostershome.ogg");
	int mousecounter = 5;
	renderMan->zoom = 0.6;

	///*auto spawning minion variables

	int minionCounter = 0;
	time_t spawnTimer1 = time(0);
	time_t spawnEvery1 = 2;
	time_t spawnTimer2 = time(0);
	time_t spawnEvery2 = 3;

	//*/
	for (int j = -800; j <= 800; j += 200){
		for (float i = 0.01; i <= 8; i += 3){
			(sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101002, j, 0, i))->setScale(.25);
		}
	}
	for (int j = -340 * 2; j <= 340 * 2; j += 340){
		for (float i = 3; i <= 8; i += 3){
			(sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101003, j, 250, i));
			(sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101003, j, -250, i));
		}
	}
	SDLRenderObject * fount = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101004, 40, 150, 0.005);

	fount->setScale(0.5);
	list<motion> motions;
	motions.push_back(makeMotion(keyframeAnimate(fount, 0, 15), 0, 1));
	Animation * runWater = new Animation(20,motions);
	int aniCounter = 0;

	while (gameloop) {

		runWater->animate(float(aniCounter)/20);
		aniCounter++;
		aniCounter = aniCounter % 20;
		

		if (input->isKeyDown(KEY_Q)){
			if (renderMan->cameraPoint.z < -5){
				renderMan->cameraPoint.z += 1;
			}
		}
		if (input->isKeyDown(KEY_W)){
			renderMan->cameraPoint.z -= 1;
		}
		if (input->isKeyDown(KEY_E)){
			renderMan->flippedScreen = !renderMan->flippedScreen;
		}
		
		mousecounter++;
		////////////////////////////////////

		if (numPlayers != 1)  NetworkManager::sInstance->UpdateDelay();
		if (player){
			renderMan->setCameraPoint(player->posX, 0);
		}
		int length = 20;
		float loop = (var % length);

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

		if (input->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		//cout << "spawnTimer1 + spawnEvery1: " << (spawnTimer1 + spawnEvery1) << " currenttime: " << time(0) << endl;
		if ((spawnTimer1 + spawnEvery1) <= time(0)) {
			spawnTimer1 = time(0);
			GameObjects.AddObject(mFactory.Spawn(minionCounter++, -500, -100, 200, true));
		}
		if ((spawnTimer2 + spawnEvery2) <= time(0)) {
			spawnTimer2 = time(0);
			GameObjects.AddObject(mFactory.Spawn(minionCounter++, -500, 0, 200, true));
		}

		input->update();

		sceneMan->AssembleScene();

	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	std::cout << renderMan << endl;

	log->close();
	printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");

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