#include "test.h"
#include <functional>
#include <crtdbg.h>

//#include "include\network\NetIncludes.h"


using namespace std;

void update();
void render(RenderManager*);
long double getCurrentTime();

typedef float(*ease_function)(float);

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
		GameObjects.AddObject(plFactory.Spawn((321556+(i)), (i * 340), 240, 0));
		GameObjects.AddObject(plFactory.Spawn((543543+i), (i * 340), -240, 0));
		GameObjects.AddObject(plFactory.Spawn((322556 + (i)), (-i * 340), 240, 0));
		GameObjects.AddObject(plFactory.Spawn((543643 + i), (-i * 340), -240, 0));
	}


	

	//GameObjects.AddObject(mFactory.Spawn(2000, -100, -100, 200, true));


	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	int var = 0;

<<<<<<< HEAD
	renderMan->zoom = 0.5;
=======
	/*
	auto up = rotateTransform(arm, 0, 180);
	auto down = rotateTransform(arm, 180, 0);

	auto arcarm = moveEllipseArc(arm, 12, 14, 0, 4, -180, 360);
	auto arcbody = moveEllipseArc(armor, 0, 0, 5, 2, 0, -360);
	*/
>>>>>>> refs/remotes/origin/master
	float size = 6;
	float ratio = 0.7;
	int armswing = size;
	int moveSpd = 1;
	int pressed = 0;
	int pressedTime = 3;
	int rotation = 0;

<<<<<<< HEAD
	while (gameloop) {


=======
		//arm->rotation = var * 2;
		//base->posX += listen->input_x;
		//base->posY += listen->input_y;
		
		if (input->isKeyDown(KEY_DOWN)){
			base->posY += moveSpd;
		}
		if (input->isKeyDown(KEY_UP)){
			base->posY -= moveSpd;
		}
		if (input->isKeyDown(KEY_LEFT)){
			base->posX -= moveSpd;
		}
		if (input->isKeyDown(KEY_RIGHT)){
			base->posX += moveSpd;
		}
		if (input->isKeyDown(KEY_A) && !pressed){
			renderMan->flippedScreen = !renderMan->flippedScreen;
			pressed = pressedTime;
		}
		if (input->isKeyDown(KEY_Q) && !pressed){
			//base->setVisible(!base->isVisible());
			base->setFlippedH(!base->isFlippedH());
			pressed = pressedTime;
		}
		if (input->isKeyDown(KEY_W) && !pressed){
			//base->setVisible(!base->isVisible());
			base->setFlippedV(!base->isFlippedV());
			pressed = pressedTime;
		}
		if (pressed > 0)pressed--;
		if (input->isKeyDown(KEY_1)){
			base->setRotation(++rotation);
		}
		if (input->isKeyDown(KEY_2)){
			base->setRotation(--rotation);
		}
		if (input->isKeyDown(KEY_3)){
			base->setScale(2.0);
		}
		else if (input->isKeyDown(KEY_4)){
			base->setScale(0.5);
		}
		else if (input->isKeyDown(KEY_5)){
			base->setScale(2.0, 1.0);
		}
		else base->setScale(1.0);
		if (armswing > size && input->isKeyDown(KEY_Z)){
			armswing = 0;
		}
		if (armswing <= size){
			if (armswing < size*ratio)up(ease_QuadIn(float(armswing) / (size*ratio)));
			else down(ease_QuadOut(float(armswing - (size*ratio)) / (size*(1 - ratio))));
			cout << float(armswing) << endl;
			armswing += 1;
		}
		else{
			arcarm(float(var % 12) / 12);
		}
		arcbody(float(var % 12) / 12);
		*/
		//arm->posX = 31 + armor->posX;
		//arm->posY = 43 + armor->posY;
	
	//audioMan->playByName("bgmfostershome.ogg");
	int mousecounter = 5;
	renderMan->zoom = 0.6;
	
	///*auto spawning minion variables
	
	int minionCounter = 0;
	time_t spawnTimer1 = time(0);
	time_t spawnEvery1 = 2;
	time_t spawnTimer2 = time(0);
	time_t spawnEvery2 = 3;

	//*/
	while (gameloop) {


		//for (int i = 0; i < GameObjects.alive_objects.size(); i++){
		//	if (!GameObjects.alive_objects[i]->isAlive){
		//		cout << "Is Dead: " << GameObjects.alive_objects[i]->ID << endl;
		//		if (GameObjects.alive_objects[i]->type == OBJECT_FEATHER) { 
		//			//if a feather is no longer alive, add to dead_feathers
		//			GameObjects.dead_feathers.push_back(GameObjects.alive_objects[i]);
		//		}
		//		else if (GameObjects.alive_objects[i]->type == OBJECT_MINION) { 
		//			//if a minion is no longer alive, add to dead_minions
		//			GameObjects.dead_minions.push_back(GameObjects.alive_objects[i]);
		//		} else { 
		//			//if a anything else is no longer alive, add to dead_objects
		//			GameObjects.dead_objects.push_back(GameObjects.alive_objects[i]);
		//		}
		//		GameObjects.alive_objects.erase(GameObjects.alive_objects.begin() + i);
		//	}
		//}

		////test inputs, delete if you want//
		
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
		/* if (input->isMouseDown(MOUSE_LEFT) && mousecounter>5){ //spawn minion on click location
			float x = 0;
			float y = 0;
			renderMan->windowCoordToWorldCoord(x, y, input->getMouseX(), input->getMouseY());
			sceneMan->InstantiateObject(sceneMan->findLayer("layer2"),12,x,y);
			mousecounter = 0;
		} */
		mousecounter++;
		////////////////////////////////////

>>>>>>> refs/remotes/origin/master
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

		//render(renderMan);
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