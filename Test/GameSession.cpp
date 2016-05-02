#include "vld.h"
#include "GameSession.h"
#include <functional>
#include <crtdbg.h>
#include "Invoke.h"
/**
*  GameSession.cpp
*  Authors:
*  Date 4/2/2016
*  Description :
 MAIN LOOP

*/

// Constructor

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
	MidPlatShieldObjectFactory psFactory;
	FanObjectFactory fanFactory;
	WellObjectFactory wellFactory;
	LauncherObjectFactory launchFactory;


	for (int i = 0; i < 6; i++){
		GameObjects.AddObject(plFactory.Spawn((500000 + (i)), (float)(i * 414), (SCREEN_HEIGHT / 3.35f), 1));//bot
		GameObjects.AddObject(plFactory.Spawn((501000 + i), (float)(i * 414), -(SCREEN_HEIGHT / 3.35f), 2));
		GameObjects.AddObject(plFactory.Spawn((502000 + (i)), (float)(-i * 414), (SCREEN_HEIGHT / 3.35f), 1));//bot
		GameObjects.AddObject(plFactory.Spawn((503000 + i), (float)(-i * 414), -(SCREEN_HEIGHT / 3.35f), 2));
	}
	
	GameObjects.AddObject(mpFactory.Spawn(505000 , (float)(-1800), 0, 0));
	GameObjects.AddObject(mpFactory.Spawn(505001, (float)(1800), 0, 0));
	

	//GameObjects.AddObject(psFactory.Spawn((508000), (float)(-110), 0, 0));

	//BASES
	rightBase = mbFactory.Spawn(506003, -975, 0, 0, TEAM_YELLOW);
	leftBase = mbFactory.Spawn(506004, 975, 0, 0, TEAM_PURPLE);
	GameObjects.AddObject(rightBase);
	GameObjects.AddObject(leftBase);

	//WELLS
	GameObjects.AddObject(wellFactory.Spawn(506005, -1550, (SCREEN_HEIGHT / 3.4f), 0, TEAM_YELLOW));
	GameObjects.AddObject(wellFactory.Spawn(506006, 1550, (SCREEN_HEIGHT / 3.4f), 0, TEAM_PURPLE));


	//LAUNCHERS
	GameObjects.AddObject(launchFactory.Spawn(506007, -1450, (SCREEN_HEIGHT / 4.0f), 0, TEAM_YELLOW));
	GameObjects.AddObject(launchFactory.Spawn(506008, 1450, (SCREEN_HEIGHT / 4.0f), 0, TEAM_PURPLE));

	//FANS                                 ID,POSX,POSY,FORCEX,FORCEY,ANGLE
	GameObjects.AddObject(fanFactory.Spawn(54001, -350, -150, 5, 10, 90));
	GameObjects.AddObject(fanFactory.Spawn(54001, -350, 150, 5, -10, -90));
	GameObjects.AddObject(fanFactory.Spawn(54001, 350, -150, -5, 10, 90));
	GameObjects.AddObject(fanFactory.Spawn(54001, 350, 150, -5, -10, -90));

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

	renderMan->setBackground("tempbackground.png");

	//add the birdseed reference to player logic
	UIObject* birdseedMeter = HUDFactory.Spawn(BIRDSEED_BAR, 30, 30);
	queue.AddObject(HUDFactory.Spawn(BIRDSEED_SHELL, 30, 30));
	queue.AddObject(birdseedMeter);
	PlayerLogicComponent* playerLogic = dynamic_cast<PlayerLogicComponent*>(player->GetComponent(COMPONENT_LOGIC));
	playerLogic->birdseedHUD = dynamic_cast<UIRenderComponent*>(birdseedMeter->GetComponent(COMPONENT_RENDER))->objRef;
	playerLogic->defaultRect = playerLogic->birdseedHUD->renderRect;

	//add a timer to top of screen
	UIObject* countdownTimer = HUDFactory.Spawn(TIMER, SCREEN_WIDTH - 200, 30);
	queue.AddObject(countdownTimer);
	playerLogic->timerHUD = dynamic_cast<UIRenderComponent*>(countdownTimer->GetComponent(COMPONENT_RENDER))->objRef;
	//load crosshair
	UIObject* crosshair = HUDFactory.Spawn(CROSSHAIR, 0, 0);
	queue.AddObject(crosshair);
	PlayerRenderComponent* playerRender = dynamic_cast<PlayerRenderComponent*>(player->GetComponent(COMPONENT_RENDER));
	playerRender->crosshairRef = dynamic_cast<UIRenderComponent*>(crosshair->GetComponent(COMPONENT_RENDER))->objRef;

	// add charge meter reference to player logic
	// also needs playerrendercomponent for xpos/ypos
	UIObject* chargeMeter = HUDFactory.Spawn(CHARGE_BAR, (SCREEN_WIDTH - 300), 0);
	UIObject* chargeShell = HUDFactory.Spawn(CHARGE_SHELL, (SCREEN_WIDTH - 300), 0);
	queue.AddObject(chargeMeter);
	queue.AddObject(chargeShell);
	playerLogic->chargeHUD = dynamic_cast<UIRenderComponent*>(chargeMeter->GetComponent(COMPONENT_RENDER))->objRef;
	playerLogic->chargeRect = playerLogic->chargeHUD->renderRect;
	playerRender->chargebarMeterRef = dynamic_cast<UIRenderComponent*>(chargeMeter->GetComponent(COMPONENT_RENDER))->objRef;
	playerRender->chargebarShellRef = dynamic_cast<UIRenderComponent*>(chargeShell->GetComponent(COMPONENT_RENDER))->objRef;

	//add ui components to show player kills
	std::vector<std::pair<SDLRenderObject*, clock_t>> killHUD;
	for (int i = 0; i < 5; i++){
		UIObject* currKillHUD = HUDFactory.Spawn(KILL_NOTIFICATION,SCREEN_WIDTH-250,130+i*30);
		SDLRenderObject* currKillObj = dynamic_cast<UIRenderComponent*>(currKillHUD->GetComponent(COMPONENT_RENDER))->objRef;
		killHUD.push_back(std::pair<SDLRenderObject*, clock_t>(currKillObj, clock()));

	}
	playerLogic->killHUD = killHUD;
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

	//SCREEN WIDTH SCREEN HEIGHT, coordinates received from renMan seem to be offset so width and height are currently set larger than they should be.
	RenderManager* renMan = RenderManager::getRenderManager();
	int width = SCREEN_WIDTH + (SCREEN_WIDTH/2);
	int height = SCREEN_HEIGHT * 2;
	int left, right, top, bot;
	left = right = top = bot = 0;

	for (unsigned int i = 0; i < GameObjects.alive_objects.size(); i++) {
		left = right = top = bot = 0;
		SDLRenderObject* obj = dynamic_cast<RenderComponent*>(GameObjects.alive_objects[i]->GetComponent(COMPONENT_RENDER))->objRef;

		renMan->worldCoordToWindowCoord(left, top, obj->posX, obj->posY, obj->posZ);
		renMan->worldCoordToWindowCoord(right, bot, (obj->posX + obj->width), (obj->posY + obj->height), obj->posZ);

		if ((right < -width / 2) || (left > width) || (top > height / 2) || (bot < -height / 2)){ //if object is out of screen bounds, dont draw.
			obj->setVisible(false);
		}
		else{
			obj->setVisible(true);
		}
	}
}


// Run contains the main Gameloop
// TODO: create arguements once lobby system is implemented.

int GameSession::Run(vector<player*> players){

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

	numPlayers = NetworkManager::sInstance->GetPlayerCount();
	
	//std::cout << NetworkManager::sInstance->GetLobbyId() << std::endl;
	for (const auto& iter : NetworkManager::sInstance->lobbyInfoMap){
		std::cout << iter.first << std::endl;
		std::cout << "\tClass:" << iter.second.classType << std::endl;
	}

	GameObject * player = NULL;

	/// try to join a game and give each user a unique character in the game
	//if (numPlayers != 1){
	map< uint64_t, string > lobby = NetworkManager::sInstance->getLobbyMap();
	int i = 0;
	bool local = true;
	for (auto &iter : lobby){
		int classType = NetworkManager::sInstance->lobbyInfoMap.find(iter.first)->second.classType;
		//int classType = 6;
		if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
			std::cout << "Gamesession.cpp (215) Local Player ID: " << iter.second << ", " << iter.first << std::endl;
			player = GameObjects.AddObject(pFactory.Spawn(iter.first, (classType % 1000) / 100 + 1, (i % 2) + 1, local));
		}
		else{
			GameObjects.AddObject(pFactory.Spawn(iter.first, (classType % 1000) / 100 + 1, (i % 2) + 1, !local));
		}
		++i;
	}
		
	//}
	/// create a local player with ID of 10000
	/*else{
		player = GameObjects.AddObject(pFactory.Spawn(10000, CLASS_CHICKEN, TEAM_PURPLE, true));
	}*/



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
	audioMan->playByName("bgmBAAGameplay.ogg");
	int mousecounter = 5;
	renderMan->zoom = 0.6f;
	


	//World Loading
	GameSession::LoadWorld();
	GameSession::LoadPlayers();
	GameSession::LoadHUD(player);

	///*auto spawning minion variables
	int minionCounter = 10000;

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

	bool firstTime = true;
	Timing::sInstance.SetCountdownStart();
	NetworkManager::sInstance->SetState(NetworkManager::NMS_Playing);
	std::cout << NetworkManager::sInstance->GetState() << std::endl;


	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	string fpscounter = "";
	SDLRenderObject * fpsHUD = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	fpsHUD->setResourceObject(renderMan->renderText(fpscounter.c_str(), 255, 0, 0, 20, "VT323-Regular"));
	fpsHUD->setPos(0, 0);


	bool gameEnd = false;

	while (gameloop) {
		current_ticks = clock();

		//std::cout << NetworkManager::sInstance->GetState() << std::endl;
		runWater->animate(float(aniCounter) / 20);
		aniCounter++;
		aniCounter = aniCounter % 20;

		/*if (input->isKeyDown(KEY_Q)){
			if (renderMan->cameraPoint.z < -5){
				renderMan->cameraPoint.z += 1;
			}
		}
		if (input->isKeyDown(KEY_W)){
			renderMan->cameraPoint.z -= 1;
		}
		if (input->isKeyDown(KEY_E)){
			renderMan->flippedScreen = !renderMan->flippedScreen;
		}*/

		/*clock_t t;
		t = clock();*/

		if (input->isKeyDown(KEY_F)){
			std::cout << "Number of feathers: " << GameObjects.dead_feathers.size() << std::endl;
		}

		if (input->isKeyDown(KEY_M)){
			std::cout << "Number of minions: " << GameObjects.dead_minions.size() << std::endl;
		}

		if (input->isKeyDown(KEY_L)){
			std::cout << "Alive Objects: " << GameObjects.alive_objects.size() << std::endl;
		} 

		if (input->isKeyDown(KEY_Y)) {
			renderMan->ShakeScreen(.2f, .5f);
		}
		
		mousecounter++;
		////////////////////////////////////

		if (numPlayers != 1)  NetworkManager::sInstance->UpdateDelay();

		//CAMERA MOVEMENT - based on player position
		if (!gameEnd){
			if (player){
				//Camera Shake
				if ((!rightBase->isAlive || !leftBase->isAlive) && !endedBaseShake) {
					endedBaseShake = true;
					renderMan->ShakeScreen(1, 1);
				}
				int mousePos = input->getMouseX();
				int wid, hei;
				renderMan->getWindowSize(&wid, &hei);
				float xRatio = (mousePos - wid / 2) / float(wid / 2);
				float xPlus = (wid / 4) - 20;
				//std::cout << xRatio << std::endl;
				renderMan->setCameraPoint(player->posX + xRatio*xPlus, 0);

			}
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
		sysPhysics.PhysicsUpdate(GameObjects.alive_objects);
		sysClass.ClassUpdate(GameObjects.alive_objects);
		if (numPlayers != 1) sysNetwork.NetworkUpdate(GameObjects.alive_objects);

		//updates all timers
		Invoke::UpdateTimers();

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
			//GameObjects.AddObject(mFactory.Spawn(minionCounter++, -900, 0, TEAM_YELLOW));
			//GameObjects.AddObject(mFactory.Spawn(minionCounter++, 900, 0, TEAM_PURPLE));

		}
		input->update();
		sceneMan->AssembleScene();

		//triggers endgame screen
		if (Timing::sInstance.GetTimeRemainingS() <= 0 || leftBase->health <= 0 || rightBase->health <= 0) {
			gameEnd = true;//so the mouse stops registering 
			int myTeam;
			for (unsigned int i = 0; i < players.size(); i++){
				if (GamerServices::sInstance->GetLocalPlayerId() == players[i]->playerId){
					myTeam = players[i]->team;
				}
			}

		GameEnd end = GameEnd::GameEnd();
		end.runGameEnd(myTeam, leftBase, rightBase);
		gameloop = false;
		}

		firstTime = false;
		/*t = clock() - t;
		std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;*/

		

		delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;
		//std::cout <<" FPS : " << fps << std::endl;
		fpscounter = std::to_string(fps);

		//renderMan->renderText(fpscounter.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular");
		fpsHUD->setResourceObject(renderMan->renderText(fpscounter.c_str(), 0, 20, 240, 20, "VT323-Regular"));

	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////

	std::cout << renderMan << std::endl;
	std::cout << renderMan << std::endl;

	log->close();


	GameWorld::getInstance()->~GameWorld();
	return 0;
}

