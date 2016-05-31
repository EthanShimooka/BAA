#include "vld.h"
#include "GameSession.h"
#include <functional>
//#include <crtdbg.h>
#include "Invoke.h"
#include "inGameStatsRenderComponent.h"
#include "t.h"
#include "stats.h"
#include "BackgroundProps.h"


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
	GameObjects.DeleteObjects(); 
	std::cout << "layer1: " << SceneManager::GetSceneManager()->findLayer("layer1")->m_SceneObjects.size() << std::endl;
	std::cout << "layer2: " << SceneManager::GetSceneManager()->findLayer("layer2")->m_SceneObjects.size() << std::endl;
	SceneManager::GetSceneManager()->RemoveAllObjects();
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
	MidBirdObjectFactory midBirdFactory;

	// Bases should have an ID between 1-10
	uint64_t baseID = 1;
	// Wells should have an ID between 11-20
	uint64_t wellID = 11;
	// Launchers should have an ID between 21-20
	uint64_t launcherID = 21;
	// Walls should have an ID between 31-40
	uint64_t WallID = 31;
	// Platforms should have an ID between 101-200
	uint64_t platformID = 101;
	// Fans should have an ID between 201-300
	uint64_t fanID = 201;

	uint64_t birdID = 384;


	//PLATFORMS
	for (int i = 0; i < 14; i++){
		GameObjects.AddObject(plFactory.Spawn(platformID++, (float)(i * 149), (SCREEN_HEIGHT / 3.35f), 1));//bot
		GameObjects.AddObject(plFactory.Spawn(platformID++, (float)(i * 149), -(SCREEN_HEIGHT / 3.35f), 2));
		GameObjects.AddObject(plFactory.Spawn(platformID++, (float)(-i * 149), (SCREEN_HEIGHT / 3.35f), 1));//bot
		GameObjects.AddObject(plFactory.Spawn(platformID++, (float)(-i * 149), -(SCREEN_HEIGHT / 3.35f), 2));
	}
	

	//well colliders
	GameObjects.AddObject(mpFactory.Spawn(WallID++, (float)(-1800), 0, 0));
	GameObjects.AddObject(mpFactory.Spawn(WallID++, (float)(1800), 0, 0));
	

	//GameObjects.AddObject(psFactory.Spawn((508000), (float)(-110), 0, 0));

	//BASES
	rightBase = mbFactory.Spawn(baseID++, -975, 0, 0, TEAM_YELLOW);
	leftBase = mbFactory.Spawn(baseID++, 975, 0, 0, TEAM_PURPLE);
	GameObjects.AddObject(rightBase);
	GameObjects.AddObject(leftBase);

	//WELLS
	//GameObjects.AddObject(wellFactory.Spawn(wellID++, -1850, (SCREEN_HEIGHT / 5.8f), 0, TEAM_YELLOW));
	//GameObjects.AddObject(wellFactory.Spawn(wellID++, 1850, -(SCREEN_HEIGHT / 5.8f), 0, TEAM_PURPLE));
	GameObjects.AddObject(wellFactory.Spawn(wellID++, -1800, 0, 0, TEAM_YELLOW));
	GameObjects.AddObject(wellFactory.Spawn(wellID++, 1800, 0, 0, TEAM_PURPLE));


	//LAUNCHERS
	GameObjects.AddObject(launchFactory.Spawn(launcherID++, -1450, (SCREEN_HEIGHT / 4.0f), 0, TEAM_YELLOW));
	GameObjects.AddObject(launchFactory.Spawn(launcherID++, 1450, -(SCREEN_HEIGHT / 4.0f), 0, TEAM_PURPLE));
	//GameObjects.AddObject(launchFactory.Spawn(launcherID++, -1450, 0, 0, TEAM_YELLOW));
	//GameObjects.AddObject(launchFactory.Spawn(launcherID++, 1450, 0, 0, TEAM_PURPLE));

	//FANS                                 ID,     POSX, POSY, ANGLE
	GameObjects.AddObject(fanFactory.Spawn(fanID++, -350, -150, 60, TEAM_YELLOW)); //left top
	GameObjects.AddObject(fanFactory.Spawn(fanID++, -350, 150, -60, TEAM_PURPLE)); //left bot
	GameObjects.AddObject(fanFactory.Spawn(fanID++, 350, -150, 120,TEAM_PURPLE)); //right top
	GameObjects.AddObject(fanFactory.Spawn(fanID++, 350, 150, -120, TEAM_YELLOW)); //right bot

	//Mid Bird
	GameObjects.AddObject(midBirdFactory.Spawn(birdID, 0, (SCREEN_HEIGHT / 4.0f))); //right bot

}

// Loads player Objects from session arguments (instantiated player list).
// Chara selections are transfered into object factory calls. 

void GameSession::LoadPlayers(){
	
}

void GameSession::LoadHUD(GameObject* player, SystemUIObjectQueue queue){
	//initialize HUD info for the player. Should only be called once
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	//SystemUIObjectQueue queue;
	UIObjectFactory HUDFactory;

	renderMan->setBackground("Space-Muscle-Beach__0011_Sky.png");

	std::vector<UIObject*> UIObjs;

	//add the birdseed reference to player logic
	UIObject* birdseedMeter = HUDFactory.Spawn(BIRDSEED_BAR, 30, 30);
	UIObjs.push_back(birdseedMeter);
	queue.AddObject(birdseedMeter);
	UIObject* birdseedShell = HUDFactory.Spawn(BIRDSEED_SHELL, 30, 30);
	UIObjs.push_back(birdseedShell);
	queue.AddObject(birdseedShell);
	PlayerLogicComponent* playerLogic = dynamic_cast<PlayerLogicComponent*>(player->GetComponent(COMPONENT_LOGIC));
	PlayerUIComponent* playerUI = dynamic_cast<PlayerUIComponent*>(player->GetComponent(COMPONENT_UI));
	playerUI->birdseedHUD = dynamic_cast<UIRenderComponent*>(birdseedMeter->GetComponent(COMPONENT_RENDER))->objRef;
	playerUI->defaultRect = playerUI->birdseedHUD->renderRect;

	//add a timer to top of screen
	UIObject* countdownTimer = HUDFactory.Spawn(TIMER, SCREEN_WIDTH - 200, 30);
	UIObjs.push_back(countdownTimer);
	queue.AddObject(countdownTimer);
	playerUI->timerHUD = dynamic_cast<UIRenderComponent*>(countdownTimer->GetComponent(COMPONENT_RENDER))->objRef;

	PlayerRenderComponent* playerRender = dynamic_cast<PlayerRenderComponent*>(player->GetComponent(COMPONENT_RENDER));

	//add ui components to show player kills
	
	std::vector<std::pair<SDLRenderObject*, clock_t>> killHUD;
	for (int i = 0; i < 5; i++){
		UIObject* currKillHUD = HUDFactory.Spawn(KILL_NOTIFICATION,100,200+i*30);
		SDLRenderObject* currKillObj = dynamic_cast<UIRenderComponent*>(currKillHUD->GetComponent(COMPONENT_RENDER))->objRef;
		killHUD.push_back(std::pair<SDLRenderObject*, clock_t>(currKillObj, clock()));
		UIObjs.push_back(currKillHUD);
	}
	playerUI->killHUD = killHUD;
	playerUI->UIObjs = UIObjs;
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
	SystemUIUpdater sysUI;

	/// ENTITIES
	PlayerObjectFactory pFactory;
	MinionObjectFactory mFactory;
	FeatherObjectFactory fFactory;
	PlatformObjectFactory plFactory;
	MidPlatObjectFactory mpFactory;

	numPlayers = NetworkManager::sInstance->GetPlayerCount();
	
	//std::cout << NetworkManager::sInstance->GetLobbyId() << std::endl;
	/*for (const auto& iter : NetworkManager::sInstance->lobbyInfoMap){
		std::cout << iter.first << std::endl;
		std::cout << "\tClass:" << iter.second.classType << std::endl;
	}*/

	GameObject * player = NULL;
	Stats stats;
	/// try to join a game and give each user a unique character in the game
	unordered_map< uint64_t, PlayerInfo > lobby = NetworkManager::sInstance->getLobbyInfoMap();
	Stats::resetStats();
	int i = 0;
	bool local = true;
	for (auto &iter : lobby){
		int classType = iter.second.classType;
		std::cout << "classType: " << classType << std::endl;
		if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
			player = GameObjects.AddObject(pFactory.Spawn(iter.first, (classType % 50) + 1, (i % 2) + 1, local));
			stats.setLocalTeam((i % 2) + 1);
			Stats::addPlayer(iter.first, (i % 2) + 1);
		}
		else{
			GameObjects.AddObject(pFactory.Spawn(iter.first, (classType % 50) + 1, (i % 2) + 1, !local));
			Stats::addPlayer(iter.first, (i % 2) + 1);
		}
		++i;
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
	audioMan->playByName("bgmBAAGameplay.ogg");
	bool gameEndMusic = false;
	int mousecounter = 5;
	renderMan->zoom = 0.6f;
	
	SystemUIObjectQueue queue;

	//World Loading
	GameSession::LoadWorld();
	GameSession::LoadPlayers();
	GameSession::LoadHUD(player, queue);

	///*auto spawning minion variables
	int minionCounter = 10000;

	//crosshair variables
	SDLRenderObject * crosshair = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 1109, -1000, -1000, -0.05f);
	SDLRenderObject * crosshairCharging = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 1111, -1000, -1000, -0.05f);
	crosshairCharging->visible = false;
	PlayerLogicComponent* playerLogic = dynamic_cast<PlayerLogicComponent*>(player->GetComponent(COMPONENT_LOGIC));
	PlayerRenderComponent* playerRend = dynamic_cast<PlayerRenderComponent*>(player->GetComponent(COMPONENT_RENDER));

	//midway fountain
	/*
	SDLRenderObject * fount = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 101004, 40, 150, 0.005f);
	fount->setScale(0.5f);
	list<motion> motions;
	motions.push_back(makeMotion(keyframeAnimate(fount, 0, 15), 0, 1));
	Animation * runWater = new Animation(100, motions);
	int aniCounter = 0;
	*/
	LoadBackgroundProps();

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


	SDLRenderObject * leftbaseHUDicon = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 7005, 0, 0, true);
	leftbaseHUDicon->setPos(-150, 600);

	string leftBaseHealth = "";
	SDLRenderObject * leftbaseHUD = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	leftbaseHUD->setResourceObject(renderMan->renderText(leftBaseHealth.c_str(), 255, 0, 0, 60, "VT323-Regular"));
	leftbaseHUD->setPos(25, 650);

	SDLRenderObject * rightbaseHUDicon = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 7006, 0, 0, true);
	rightbaseHUDicon->setPos(1214, 600);

	string rightBaseHealth = "";
	SDLRenderObject * rightbaseHUD = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	rightbaseHUD->setResourceObject(renderMan->renderText(rightBaseHealth.c_str(), 255, 0, 0, 60, "VT323-Regular"));
	rightbaseHUD->setPos(1291, 650);


	

	renderMan->toggleCursor(0);

	/////////////Flip screen if needed/////////////////

	if (player->team == TEAM_PURPLE){
		std::cout << "flip the screen" << std::endl;
		renderMan->flippedScreen = true;
	}
	//////////////////////////////////////////////////

	bool gameEnd = false;
	inGameStatsRenderComponent inGameStats;

	while (gameloop) {
		current_ticks = clock();


		if (input->isKeyDown(KEY_TAB)){
			inGameStats.updateText();
			inGameStats.toggleOn(true);
		}
		else{
			inGameStats.toggleOn(false);
		}

		//std::cout << NetworkManager::sInstance->GetState() << std::endl;
		
	

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
				/*int mousePos = input->getMouseX();
				int wid, hei;
				renderMan->getWindowSize(&wid, &hei);
				float xRatio = (mousePos - wid / 2) / float(wid / 2);
				float xPlus = (float)(wid / 4) - 20;
				//std::cout << xRatio << std::endl;
				renderMan->setCameraPoint(player->posX + xRatio*xPlus, 0);*/
				float mouseX, mouseY;
				renderMan->windowCoordToWorldCoord(mouseX, mouseY, input->getMouseX(), input->getMouseY());
				float cameraX = (player->posX + mouseX) / 2;
				//next line makes the camera favor staying closer to the player
				cameraX = (player->posX + cameraX) / 2;
				renderMan->setCameraPoint(cameraX, 0);

			}
		}
		int length = 20;
		float loop = (float)(var % length);

		//crosshair updating
		float crossX, crossY;
		renderMan->windowCoordToWorldCoord(crossX, crossY, input->getMouseX(), input->getMouseY());
		crosshair->posX = crosshairCharging->posX = crossX;
		crosshair->posY = crosshairCharging->posY = crossY;
		float attackCDPercent = Timing::sInstance.GetAttackCooldownRemaining();
		float chargePercent = 1.0f - (playerLogic->currChargePercentage > 0.75f ? 0.75f : playerLogic->currChargePercentage);
		if (chargePercent != 1.0f){ //sets scale during charge
			//crosshair->setScale(chargePercent);
			crosshairCharging->visible = false;
			crosshair->visible = true;
			playerRend->crosshairRef = crosshair;
		}
		else if (chargePercent == 1.0f && Timing::sInstance.AttackCooldownEnded()) {
			crosshairCharging->visible = false;
			crosshair->visible = true;
			crosshair->setScale(1.0f);
			playerRend->crosshairRef = crosshair;
		}
		else {//if(attackCDPercent < 1.0f) { //sets scale during attack cooldown
			crosshairCharging->setScale(attackCDPercent);
			crosshairCharging->visible = true;
			crosshair->visible = false;
			playerRend->crosshairRef = crosshairCharging;
		} 
		

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
		sysUI.UIUpdate(queue.alive_objects);

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
			GameObjects.AddObject(mFactory.Spawn(minionCounter++, -900, 0, TEAM_YELLOW));
			GameObjects.AddObject(mFactory.Spawn(minionCounter++, 900, 0, TEAM_PURPLE));

		}
		input->update();
		sceneMan->AssembleScene();

		//triggers endgame screen
		if (Timing::sInstance.GetTimeRemainingS() <= 0) {
			gameEnd = true;//so the mouse stops registering 
			int myTeam;
			for (unsigned int i = 0; i < players.size(); i++){
				if (GamerServices::sInstance->GetLocalPlayerId() == players[i]->playerId){
					myTeam = players[i]->team;
				}
			}

			std::cout << "END REACHED " << std::endl;
		  //GameEnd end = GameEnd::GameEnd();
		  //end.runGameEnd(myTeam, leftBase, rightBase);
		  gameloop = false;
		}

		if (Timing::sInstance.GetTimeRemainingS() <= 30 && !gameEndMusic){
			gameEndMusic = true;
			audioMan->stopByName("bgmBAAGameplay.ogg");
			audioMan->playByName("bgmBAAGameEnd.ogg");
		}

		firstTime = false;

		delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;
		//std::cout <<" FPS : " << fps << std::endl;
		fpscounter = std::to_string(fps);
		
		//leftBase->health


		//renderMan->renderText(fpscounter.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular");
		fpsHUD->setResourceObject(renderMan->renderText(fpscounter.c_str(), 0, 20, 240, 20, "VT323-Regular"));
		leftBaseHealth = std::to_string(Stats::baseHealth_purple());

	//	leftBaseHealth = std::to_string(leftBase->health);
		leftbaseHUD->setResourceObject(renderMan->renderText(leftBaseHealth.c_str(), 250, 165, 10, 75, "BowlbyOneSC-Regular"));
		rightBaseHealth = std::to_string(Stats::baseHealth_yellow());

	//	rightBaseHealth = std::to_string(rightBase->health);
		rightbaseHUD->setResourceObject(renderMan->renderText(rightBaseHealth.c_str(), 160, 32, 240, 75, "BowlbyOneSC-Regular"));


	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	audioMan->stopByName("bgmBAAGameEnd.ogg");
	std::cout << renderMan << std::endl;
	std::cout << renderMan << std::endl;

	log->close();

	//delete surf;
	//delete fount;
	//delete runWater;

	GameWorld::getInstance()->~GameWorld();
	return SCENE_GAMEOVER;
}