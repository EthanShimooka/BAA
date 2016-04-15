#include "vld.h"
#include "GameSession.h"
#include <functional>
#include <crtdbg.h>
/**
*  GameSession.cpp
*  Authors:
*  Date 4/2/2016
*  Description :
 MAIN LOOP

*/

// Constructor

std::unordered_map<uint64_t, player*> playersInLobby;

GameSession::GameSession(){
}

// Destructor

GameSession::~GameSession(){
}

//variables used to keep track of bases and for camera shaking
GameObject* leftBase;
GameObject* rightBase;
bool endedBaseShake = false;
//time_t startShake;
//time_t shakeTimer = 1;
// Loads non-player Objects

void GameSession::LoadWorld(){

	PlatformObjectFactory plFactory;
	MidPlatObjectFactory mpFactory;
	MidBaseObjectFactory mbFactory;

	for (int i = 0; i < 4; i++){
		GameObjects.AddObject(plFactory.Spawn((500000 + (i)), (float)(i * 340), (SCREEN_HEIGHT / 3.1f), 0));
		GameObjects.AddObject(plFactory.Spawn((501000 + i), (float)(i * 340), -(SCREEN_HEIGHT / 3.1f), 0));
		GameObjects.AddObject(plFactory.Spawn((502000 + (i)), (float)(-i * 340), (SCREEN_HEIGHT / 3.1f), 0));
		GameObjects.AddObject(plFactory.Spawn((503000 + i), (float)(-i * 340), -(SCREEN_HEIGHT / 3.1f), 0));
	}
	for (int i = 0; i < 3; i++){
		GameObjects.AddObject(mpFactory.Spawn(504000 + i, (float)(-i * 350), 0, 0));
		GameObjects.AddObject(mpFactory.Spawn(505000 + i, (float)(i * 350), 0, 0));
	}
	rightBase = mbFactory.Spawn(506001, 975, -40, 0);
	leftBase = mbFactory.Spawn(506002, -975, -40, 0);
	GameObjects.AddObject(rightBase);
	GameObjects.AddObject(leftBase);

}

// Loads player Objects from session arguments (instantiated player list).
// Chara selections are transfered into object factory calls. 

void GameSession::LoadPlayers(){
	
}

void GameSession::LoadHUD(GameObject* player){
	//initialize HUD info for the player. Should only be called once
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SystemUIObjectQueue queue;
	UIObjectFactory HUDFactory;
	//add the birdseed reference to player logic
	UIObject* birdseedMeter = HUDFactory.Spawn(BIRDSEED_BAR);
	queue.AddObject(HUDFactory.Spawn(BIRDSEED_SHELL));
	queue.AddObject(birdseedMeter);
	PlayerLogicComponent* playerLogic = dynamic_cast<PlayerLogicComponent*>(player->GetComponent(COMPONENT_LOGIC));
	playerLogic->birdseedHUD = dynamic_cast<UIRenderComponent*>(birdseedMeter->GetComponent(COMPONENT_RENDER))->objRef;
	playerLogic->defaultRect = playerLogic->birdseedHUD->renderRect;
	
	//add a timer to top of screen
	UIObject* countdownTimer = HUDFactory.Spawn(TIMER);
	queue.AddObject(countdownTimer);
	playerLogic->timerHUD = dynamic_cast<UIRenderComponent*>(countdownTimer->GetComponent(COMPONENT_RENDER))->objRef;
	//load crosshair
	UIObject* crosshair = HUDFactory.Spawn(CROSSHAIR);
	queue.AddObject(crosshair);
	PlayerRenderComponent* playerRender = dynamic_cast<PlayerRenderComponent*>(player->GetComponent(COMPONENT_RENDER));
	playerRender->crosshairRef = dynamic_cast<UIRenderComponent*>(crosshair->GetComponent(COMPONENT_RENDER))->objRef;

	// add charge meter reference to player logic
	// also needs playerrendercomponent for xpos/ypos
	UIObject* chargeMeter = HUDFactory.Spawn(CHARGE_BAR);
	UIObject* chargeShell = HUDFactory.Spawn(CHARGE_SHELL);
	queue.AddObject(chargeMeter);
	queue.AddObject(chargeShell);
	playerLogic->chargeHUD = dynamic_cast<UIRenderComponent*>(chargeMeter->GetComponent(COMPONENT_RENDER))->objRef;
	playerLogic->chargeRect = playerLogic->chargeHUD->renderRect;
	playerRender->chargebarMeterRef = dynamic_cast<UIRenderComponent*>(chargeMeter->GetComponent(COMPONENT_RENDER))->objRef;
	playerRender->chargebarShellRef = dynamic_cast<UIRenderComponent*>(chargeShell->GetComponent(COMPONENT_RENDER))->objRef;
}

//////////////////////////////////////////////////////////////////////////

void cullObjects(){
	for (unsigned int i = 0; i < GameObjects.dead_objects.size(); i++) {
		dynamic_cast<RenderComponent*>(GameObjects.dead_objects[i]->GetComponent(COMPONENT_RENDER))->objRef->setVisible(false);
	}
	for (unsigned int i = 0; i < GameObjects.dead_feathers.size(); i++) {
		dynamic_cast<RenderComponent*>(GameObjects.dead_feathers[i]->GetComponent(COMPONENT_RENDER))->objRef->setVisible(false);
	}
	for (unsigned int i = 0; i < GameObjects.dead_minions.size(); i++) {
		dynamic_cast<RenderComponent*>(GameObjects.dead_minions[i]->GetComponent(COMPONENT_RENDER))->objRef->setVisible(false);
	}

	//SCREEN WIDTH SCREEN HEIGHT COME FIX WHEN CONFIG SETS THEM
	RenderManager* renMan = RenderManager::getRenderManager();
	int width = 3000;
	int height = 2000;
	int left, right, top, bot;
	left = right = top = bot = 0;

	for (unsigned int i = 0; i < GameObjects.alive_objects.size(); i++) {
		left = right = top = bot = 0;
		SDLRenderObject* obj = dynamic_cast<RenderComponent*>(GameObjects.alive_objects[i]->GetComponent(COMPONENT_RENDER))->objRef;

		renMan->worldCoordToWindowCoord(left, top, obj->posX, obj->posY, obj->posZ);
		renMan->worldCoordToWindowCoord(right, bot, (obj->posX + obj->width), (obj->posY + obj->height), obj->posZ);

		if ((right < -width / 2) || (left > width / 2) || (top > height / 2) || (bot < -height / 2)){ //if object is out of screen bounds, dont draw.
			obj->setVisible(false);
		}
		else{
			obj->setVisible(true);
		}
	}
}


// Run contains the main Gameloop
// TODO: create arguements once lobby system is implemented.

int GameSession::Run(){

	// temp
	int numLobbyPlayer = 0;
	int numPlayers = 1;
	//


	/// MANAGERS

	LogManager* log = LogManager::GetLogManager();
	InputManager* input = InputManager::getInstance();
	AudioManager* audioMan = AudioManager::getAudioInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	log->create("log.txt");
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
	SystemClassUpdater sysClass;



	/// ENTITIES
	PlayerObjectFactory pFactory;
	MinionObjectFactory mFactory;
	FeatherObjectFactory fFactory;
	PlatformObjectFactory plFactory;
	MidPlatObjectFactory mpFactory;

	while (NetworkManager::sInstance->GetState() < NetworkManager::NMS_Starting){
		Start menu;
		menu.mainMenu();

		Lobby lobby;
		lobby.runLobby();
	}


	numPlayers = NetworkManager::sInstance->GetPlayerCount();
	
	//std::cout << NetworkManager::sInstance->GetLobbyId() << std::endl;

	GameObject * player = NULL;

	/// try to join a game and give each user a unique character in the game
	if (numPlayers != 1){
		map< uint64_t, string > lobby = NetworkManager::sInstance->getLobbyMap();

		for (auto &iter : lobby){
			bool local = false;
			if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
				local = true;
				std::cout << "Local Player ID: " << iter.second << ", " << iter.first << std::endl;
				player = GameObjects.AddObject(pFactory.Spawn(iter.first, CLASS_CHICKEN, local));
			}
			else{
				GameObjects.AddObject(pFactory.Spawn(iter.first, CLASS_CHICKEN, local));
			}
		}
	}
	/// create a local player with ID of 10000
	else{
		player = GameObjects.AddObject(pFactory.Spawn(10000, CLASS_CHICKEN, true));
	}



	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////

	bool gameloop = true;
	int var = 0;
	renderMan->zoom = 0.5;

	float size = 6;
	float ratio = 0.7f;
	int armswing = (int)size;
	int moveSpd = 1;
	int pressed = 0;
	int pressedTime = 3;
	int rotation = 0;
	audioMan->playByName("bgmfostershome.ogg");
	int mousecounter = 5;
	renderMan->zoom = 0.6f;


	//World Loading
	GameSession::LoadWorld();
	GameSession::LoadPlayers();
	GameSession::LoadHUD(player);

	///*auto spawning minion variables

	int minionCounter = 0;
	time_t spawnTimer1 = time(0);
	time_t spawnEvery1 = 2;
	time_t spawnTimer2 = time(0);
	time_t spawnEvery2 = 3;

	//*/
	for (int j = -800; j <= 800; j += 200){
		for (float i = 0.01f; i <= 8; i += 3){
			(sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101002, (float)j, 0, i))->setScale(.25);
		}
	}
	for (int j = -340 * 2; j <= 340 * 2; j += 340){
		for (float i = 3; i <= 8; i += 3){
			(sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101003, (float)j, 250, i));
			(sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101003, (float)j, -250, i));
		}
	}
	SDLRenderObject * fount = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101004, 40, 150, 0.005f);

	fount->setScale(0.5);
	list<motion> motions;
	motions.push_back(makeMotion(keyframeAnimate(fount, 0, 15), 0, 1));
	Animation * runWater = new Animation(20, motions);
	int aniCounter = 0;

	//SDL_Cursor* cursor = renderMan->cursorToCrosshair();

	bool firstTime = true;
	Timing::sInstance.SetCountdownStart();
	NetworkManager::sInstance->SetState(NetworkManager::NMS_Playing);
	std::cout << NetworkManager::sInstance->GetState() << std::endl;
	while (gameloop) {

		//std::cout << NetworkManager::sInstance->GetState() << std::endl;
		runWater->animate(float(aniCounter) / 20);
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

		if (input->isKeyDown(KEY_F)){
			std::cout << "Number of feathers: " << GameObjects.dead_feathers.size() << std::endl;
		}

		if (input->isKeyDown(KEY_M)){
			std::cout << "Number of minions: " << GameObjects.dead_minions.size() << std::endl;
		}
		if (input->isKeyDown(KEY_Y)) {
			renderMan->ShakeScreen(.2, .5);
		}
		
		mousecounter++;
		////////////////////////////////////

		if (numPlayers != 1)  NetworkManager::sInstance->UpdateDelay();

		//CAMERA MOVEMENT - based on player position
		if (player){
			//Camera Shake
			if ((!rightBase->isAlive || !leftBase->isAlive) && !endedBaseShake) {
				endedBaseShake = true;
				renderMan->ShakeScreen(1, 1);
			}
			renderMan->setCameraPoint(player->posX, 0);
			
		}
		
		int length = 20;
		float loop = (float)(var % length);

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
		sysClass.ClassUpdate(GameObjects.alive_objects);

		if (input->isKeyDown(KEY_ESCAPE))
			gameloop = false;


		//OBJECT POOLING - moves recently dead objects to respective dead pool
		for (unsigned int i = 0; i < GameObjects.alive_objects.size(); i++){
			if (!GameObjects.alive_objects[i]->isAlive){
				//object has died this last gameloop. send it to the object pool
				//std::cout << "ID: " << GameObjects.alive_objects[i]->ID << std::endl;
				if (GameObjects.alive_objects[i]->type == OBJECT_FEATHER){
					GameObjects.dead_feathers.push_back(GameObjects.alive_objects[i]);
				}
				else if (GameObjects.alive_objects[i]->type == OBJECT_MINION){
					GameObjects.dead_minions.push_back(GameObjects.alive_objects[i]);
				}
				else {
					GameObjects.dead_objects.push_back(GameObjects.alive_objects[i]);
				}
				GameObjects.alive_objects.erase(GameObjects.alive_objects.begin() + i);
			}
		}
		
		if (!firstTime) //allows culling to start after all initialization happens
			cullObjects();

		if (Timing::sInstance.SpawnMinions()){
			GameObjects.AddObject(mFactory.Spawn(minionCounter++, -800, 0, 1));
			GameObjects.AddObject(mFactory.Spawn(minionCounter++,  800, 0, 2));

		}
		input->update();
		sceneMan->AssembleScene();

		//triggers endgame screen
		if (Timing::sInstance.GetTimeRemainingS() <= 0 || leftBase->health <= 0 || rightBase->health <= 0) {
			GameEnd end = GameEnd::GameEnd();
			end.runGameEnd();
			gameloop = false;
		}

		firstTime = false;
	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	
	// Loop freeing memoru
	//for (unsigned int i = 0; i < GameObjects.alive_objects.size(); i++){
	//	GameObjects.DeleteObjects(GameObjects.alive_objects[i]->ID);
	//}
	std::cout << renderMan << std::endl;
	//renderMan->freeCursor(cursor);
	std::cout << renderMan << std::endl;

	log->close();
	//printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");

	GameWorld::getInstance()->~GameWorld();
	return 0;
}
