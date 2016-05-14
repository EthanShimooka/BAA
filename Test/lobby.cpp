#include "lobby.h"

vector<player*> players;

Lobby::Lobby() : numPlayersReady(0){
	numPlayers = NetworkManager::sInstance->GetPlayerCount();
}


Lobby::~Lobby(){
}

void Lobby::runLobby(){
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	int lobbyInput;

	renderMan->setBackground("Lobby_bg.png");

	// number of players in lobby
	createPlayerCount();


	// creating buttons
	createClassButts();
	createSlots();

	
	while (true){
		updateLobby();
		lobbyInput = checkButtons();
		changePlayerSelectionImage();
		/// testing
		updateLobby();
		///
		if (numPlayers == numPlayersReady) {
			GameSession game;
			game.Run();
			removeButtons();
			removeSlots();
			break;
		}
		
	}
}


void Lobby::createClassButts(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GameObject* button;
	uint64_t buttonID = 11;

	int w, h;
	float midHeight, offset;
	float x, y;

	renderMan->getWindowSize(&w, &h);
	// height for the character class buttons
	midHeight = h * (1 / 2.0);
	// finding the offset of the slots
	offset = w * (1 / 4.0);

	// chicken button
	renderMan->windowCoordToWorldCoord(x, y, offset, midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 50, 75.0f, 75.0f, 0.75f);
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0);
	// peacock button
	renderMan->windowCoordToWorldCoord(x, y, offset, midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 51, 75.0f, 75.0f, 0.75f);
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0);
	// flamingo button
	renderMan->windowCoordToWorldCoord(x, y, offset, midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 52, 75.0f, 75.0f, 0.75f);
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0);
	// quail button
	renderMan->windowCoordToWorldCoord(x, y, offset, midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 53, 75.0f, 75.0f, 0.75f);
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0);
	// turkey button
	renderMan->windowCoordToWorldCoord(x, y, offset, midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 54, 75.0f, 75.0f, 0.75f);
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0);
}

int Lobby::checkButtons(){
	InputManager::getInstance()->update();
	for (int i = 0; i < classButt.size(); ++i){
		if (dynamic_cast<ButtonLogicComponent*>(classButt[i]->GetComponent(COMPONENT_LOGIC))->isButtonPressed()){
			playerSelection(dynamic_cast<ButtonRenderComponent*>(classButt[i]->GetComponent(COMPONENT_RENDER))->currentImage);
			return i;
		}
	}
	return -1;
}

void Lobby::playerSelection(int classType){
	NetworkManager::sInstance->SendSelectPacket(classType);
	
}

void Lobby::changePlayerSelectionImage(){
	if (NetworkManager::sInstance->lobbyUpdated()){
		unordered_map< uint64_t, PlayerInfo > lobby_m = NetworkManager::sInstance->getLobbyInfoMap();
		numPlayersReady = 0;
		int i = 0;
		for (const auto& iter : lobby_m){
			if (iter.second.classType != -1) {
				dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->changeSprite(iter.second.classType);
				++numPlayersReady;
			}
			else {
				dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->setToDefault();
			}
			/*if (iter.second.ready)
				++numPlayersReady;*/
			++i;
		}
	}
}

void Lobby::removeButtons(){
	for (int i = 0; i < classButt.size(); ++i){
		SceneManager::GetSceneManager()->RemoveObject(dynamic_cast<ButtonRenderComponent*>(classButt[i]->GetComponent(COMPONENT_RENDER))->objRef,
			SceneManager::GetSceneManager()->findLayer("layer1"));
		GameObjects.DeleteObject(classButt[i]->ID);
	}
}

void Lobby::createSlots(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GameObject* slot;
	uint64_t slotID = 1;
	int w, h;
	float topH, bottH, offset;
	float x, y;

	renderMan->getWindowSize(&w, &h);
	// height for the slots on the top half
	topH = h * (1 / 10.0);
	// height for the slots on the bottom half
	bottH = h * (9 / 10.0);
	// finding the offset of the slots
	offset = w * (1 / 6.0);

	for (int i = 0; i < 8; ++i){
		if (i % 2){
			h = bottH;
		}
		else {
			h = topH;
			offset += w * (1 / 8.0);
		}
		renderMan->windowCoordToWorldCoord(x, y, offset, h);
		slot = bFactory.Spawn(slotID++, x, y, 28);
		slots.push_back(slot);
		GameObjects.AddObject(slot);
	}
}

void Lobby::removeSlots(){
	for (int i = 0; i < slots.size(); ++i){
		SceneManager::GetSceneManager()->RemoveObject(dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->objRef,
			SceneManager::GetSceneManager()->findLayer("layer1"));
		GameObjects.DeleteObject(slots[i]->ID);
	}
}

void Lobby::updateLobby(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GamerServices::sInstance->Update();
	NetworkManager::sInstance->ProcessIncomingPackets();
	playerCount = std::to_string(numPlayers);
	playersInLobby->setResourceObject(renderMan->renderText(playerCount.c_str(), 255, 0, 0, 50, "VT323-Regular"));
	SceneManager::GetSceneManager()->AssembleScene();
	numPlayers = NetworkManager::sInstance->GetPlayerCount();
}



void Lobby::createPlayerCount(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	playerCount = std::to_string(numPlayers);
	playersInLobby = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	playersInLobby->setPos(0, 0);
}


















































//void Lobby::waitForTeam(){
//
//}
//
//void Lobby::deletePlayers(){
//	for (unsigned int i = 0; i < players.size(); i++){
//		delete players[i];
//	}
//	players.clear();
//}
//
//void Lobby::deleteBirds(SystemUIObjectQueue &queue){
//	SceneManager* sceneMan = SceneManager::GetSceneManager();
//	SystemRenderUpdater sysRend;
//	for (unsigned int i = 0; i < queue.alive_objects.size(); i++){
//		queue.alive_objects[i]->visible = false;
//	}
//	sysRend.RenderUpdate(queue.alive_objects);
//	sceneMan->AssembleScene();
//	queue.DeleteObjects();
//	Birds.clear();
//}
//
//void Lobby::createButtons(SystemUIObjectQueue &q){
//
//	RenderManager* rendMan = RenderManager::getRenderManager();
//	int w, h;
//
//	rendMan->getWindowSize(&w, &h);
//	UIObjectFactory* invite = new UIObjectFactory();
//	UIObject* inviteButton = invite->Spawn(INVITE_BUTTON, 0, h/2);
//	q.AddObject(inviteButton);
//}
//
//void Lobby::cleanUP(SystemUIObjectQueue &q){
//
//	SceneManager* sceneMan = SceneManager::GetSceneManager();
//	SystemRenderUpdater sysRend;
//
//	for (unsigned int i = 0; i < q.alive_objects.size(); i++){
//		q.alive_objects[i]->visible = false;
//	}
//
//	sysRend.RenderUpdate(q.alive_objects);
//	sceneMan->AssembleScene();
//	q.DeleteObjects();
//}
//
//void Lobby::countdown(SystemUIObjectQueue &q){
//
//	RenderManager* renderMan = RenderManager::getRenderManager();
//	SceneManager* sceneMan = SceneManager::GetSceneManager();
//
//	SystemRenderUpdater sysRend;
//	UIObjectFactory countdown;
//	UIObject* timer = countdown.Spawn(LOBBY_TIMER, 30, 30);
//
//	q.AddObject(timer);
//	Timing::sInstance.SetLobbyCountdown();
//	Timing::sInstance.SetCountdownStart();
//
//	SDLRenderObject* timerHUD = dynamic_cast<UIRenderComponent*>(timer->GetComponent(COMPONENT_RENDER))->objRef;
//
//	while (true){
//
//		sysRend.RenderUpdate(q.alive_objects);
//		sceneMan->AssembleScene();
//
//		int timeRemaininginSeconds = Timing::sInstance.GetTimeRemainingS();
//		string minutes = Timing::sInstance.GetMinutesLeftAsString(timeRemaininginSeconds);
//		string seconds = Timing::sInstance.GetSecondsLeftAsString(timeRemaininginSeconds);
//
//		if (seconds.length() == 1){
//			seconds = "0" + seconds;
//		}
//
//		if (timeRemaininginSeconds == 0){
//			Timing::sInstance.SetGamePlayCountdown();
//			return;
//		}
//
//		std::string title = minutes + ":" + seconds; //concat on the time remaining here!
//		timerHUD->replaceResourceObject(renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular"));
//		//renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular", timerHUD->renderResource);
//
//	}
//}
//
//void Lobby::drawBirds(SystemUIObjectQueue &queue){
//	RenderManager* rendMan = RenderManager::getRenderManager();
//	int w, h;
//
//	rendMan->getWindowSize(&w, &h);
//	int x, y;
//
//	x = w / 5;
//	y = h / 2;
//	//build class slots
//	UIObjectFactory* allBirds = new UIObjectFactory();
//
//	UIObject* bird = allBirds->Spawn(CHICKEN, x - 33, y);
//	x += bird->getWidth();
//	UIObject* bird2 = allBirds->Spawn(PEACOCK, x, y);
//	x += bird2->getWidth();
//	UIObject* bird3 = allBirds->Spawn(QUAIL, x, y);
//	x += bird3->getWidth();
//	UIObject* bird4 = allBirds->Spawn(TURKEY, x, y);
//	x += bird4->getWidth();
//	UIObject* bird5 = allBirds->Spawn(FLAMINGO, x, y);
//
//
//	Birds.push_back(bird);
//	Birds.push_back(bird2);
//	Birds.push_back(bird3);
//	Birds.push_back(bird4);
//	Birds.push_back(bird5);
//
//	queue.AddObject(bird);
//	queue.AddObject(bird2);
//	queue.AddObject(bird3);
//	queue.AddObject(bird4);
//	queue.AddObject(bird5);
//}
//
//void Lobby::addSlots(SystemUIObjectQueue &queue){
//
//	RenderManager* rendMan = RenderManager::getRenderManager();
//	int w, h;
//	rendMan->getWindowSize(&w, &h);
//	int x = w / 4;
//
//	for (int i = 0; i < maxPlayers; i++){
//		player *p = new player();
//		p->playerId = NULL;
//		p->name = "";
//		if (i % 2 == 0){
//			p->x = 0 + x;
//			p->y = 0;
//			p->team = TEAM_YELLOW;
//		}
//		else{
//			p->x = 0 + x;
//			p->y = h - 25;
//			x += w / 2;
//			p->team = TEAM_PURPLE;
//			p->bottom = true;
//		} 
//		
//		UIObjectFactory* slot = new UIObjectFactory();
//		p->playerSlot = slot->Spawn(PLAYER_SLOT, p->x, p->y);
//		p->visible = false;
//		p->playerSlot->visible = p->visible;
//		p->playerSlot->bottom = p->bottom;
//		queue.AddObject(p->playerSlot);
//		players.push_back(p);
//	}
//}
//
//void Lobby::assignPlayers(){
//
//	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
//
//	int i = 0;
//	for (std::map<uint64_t, string>::iterator it = lobby.begin(); it != lobby.end(); it++){
//		if (players[i]->playerId == NULL){
//			players[i]->visible = true;
//			players[i]->playerId = it->first;
//			players[i]->name = it->second;
//			players[i]->playerSlot->player = it->first;
//			players[i]->playerSlot->visible = players[i]->visible;  
//			i++;
//		}
//	}
//}
//
//void Lobby::updateLobby(){
//
//	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
//	for (unsigned int i = 0; i < players.size(); i++){
//		std::map<uint64_t, string>::iterator it;
//		it = lobby.find(players[i]->playerId);
//		if (it == lobby.end()){
//			players[i]->playerId = NULL;
//			players[i]->name = "";
//			players[i]->ready = false;
//			players[i]->visible = false;
//			players[i]->playerSlot->visible = players[i]->visible;
//			NetworkManager::sInstance->UpdateLobbyPlayers();
//			inLobbyNow--;
//		}
//	}
//}
//
//void Lobby::addNewPlayers(){
//
//	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
//	std::map<uint64_t, string>::iterator it = lobby.begin();
//	bool found = false;
//
//	for (it; it != lobby.end(); it++){
//
//		for (unsigned int i = 0; i < players.size(); i++){
//			if (players[i]->playerId == it->first){
//				found = true;
//			}
//		}
//		if (!found){
//			for (unsigned int i = 0; i < players.size(); i++){
//				if (players[i]->playerId == NULL){
//					players[i]->visible = true;
//					players[i]->playerId = it->first;
//					players[i]->name = it->second;
//					players[i]->playerSlot->player = it->first;
//					players[i]->playerSlot->visible = players[i]->visible;
//					TEAM team = players[i]->team;
//					SendTeamPacket(it->first, team);
//					break;
//				}
//			}
//		}
//		else{
//			found = false;
//		}
//	}
//}
//
//void Lobby::SendTeamPacket(uint64_t ID, TEAM team){
//	NetworkManager::sInstance->SendTeamToPeers(ID, team);
//}

//SystemInputUpdater sysInput;
//SystemRenderUpdater sysRend;
//UIObjectFactory uFactory;
//SystemUIUpdater sysUI;
//SystemUIObjectQueue queue;
//SystemUIObjectQueue birdQueue;

//addSlots(queue);
//drawBirds(birdQueue);

//uint64_t myId = NetworkManager::sInstance->GetMyPlayerId();
//player* me = new player();

////if (NetworkManager::sInstance->IsMasterPeer()){
//	assignPlayers();
////}
////wait for master peer to assigne us a team
///*else{
//	waitForTeam();
//}*/
//	
//for (unsigned int i = 0; i < players.size(); i++){
//	if (players[i]->playerId == myId)
//		me = players[i];
//}

//createButtons(queue);

//NetworkManager::sInstance->UpdateLobbyPlayers();
//inLobbyNow = NetworkManager::sInstance->GetPlayerCount();
//int readyCount = 0;

////while loop running lobby
//while (NetworkManager::sInstance->GetState() < NetworkManager::sInstance->NMS_Starting){
//	/*std::cout << "lobby count: " << NetworkManager::sInstance->GetPlayerCount()<< std::endl;
//	std::cout << "master: " << NetworkManager::sInstance->IsMasterPeer() << std::endl;*/
//	input->update();

//	GamerServices::sInstance->Update();
//	NetworkManager::sInstance->ProcessIncomingPackets();
//	NetworkManager::sInstance->SendOutgoingPackets();
//	NetworkManager::sInstance->UpdateLobbyPlayers();
//	numPlayers = NetworkManager::sInstance->GetPlayerCount();

//	//check for new players joining.
//	if (numPlayers > inLobbyNow /*&& NetworkManager::sInstance->IsMasterPeer()*/){
//		addNewPlayers();
//		NetworkManager::sInstance->UpdateLobbyPlayers();
//		inLobbyNow = NetworkManager::sInstance->GetPlayerCount();
//		auto& iter = NetworkManager::sInstance->lobbyInfoMap.find(GamerServices::sInstance->GetLocalPlayerId());
//		if (iter->second.classType)
//			NetworkManager::sInstance->SendSelectPacket(iter->second.classType);
//	}

//	updateLobby();
//	
//	if (!me->ready){
//		for (unsigned int i = 0; i < Birds.size(); i++){
//			if (Birds[i]->ready){
//				me->playerChoice = Birds[i]->ID;
//				me->playerSlot->changePicture = true;
//				me->playerSlot->changeTo = Birds[i]->ID;
//				NetworkManager::sInstance->SendSelectPacket((int)Birds[i]->ID);
//				me->ready = true;
//				readyCount++;
//				break;
//			}
//			if (Birds[i]->hoverPicture){
//				me->playerSlot->hoverPicture = true;
//				me->playerSlot->changeTo = Birds[i]->ID;
//				break;
//			}
//			else{
//				me->playerSlot->hoverPicture = false;
//			}
//		}
//	}

//	for (const auto& iter : NetworkManager::sInstance->lobbyInfoMap){
//		for (const auto& player : players){
//			if (player->playerId == iter.first){
//				if (iter.second.classType != (int)player->playerSlot->changeTo && iter.second.classType != -1){
//					//std::cout << "TYPE: " << iter.first << ", " << (UIType)iter.second.classType << ", " << iter.second.classType << std::endl;
//					player->playerChoice = (UIType)iter.second.classType;
//					player->playerSlot->changePicture = true;
//					player->playerSlot->changeTo = (UIType)iter.second.classType;
//					player->ready = true;
//					readyCount++;
//				}
//			}
//		}
//	}

//	if (me->ready && NetworkManager::sInstance->IsMasterPeer() && readyCount == numPlayers){
//		NetworkManager::sInstance->TryReadyGame();
//	}

//	sysUI.UIUpdate(queue.alive_objects);
//	sysInput.InputUpdate(queue.alive_objects);
//	sysRend.RenderUpdate(queue.alive_objects);
//	sysUI.UIUpdate(birdQueue.alive_objects);
//	sysInput.InputUpdate(birdQueue.alive_objects);
//	sysRend.RenderUpdate(birdQueue.alive_objects);

//	input->update();
//	
//	sceneMan->AssembleScene();

//}

//if (NetworkManager::sInstance->GetState() >= NetworkManager::NMS_Starting){
//	deleteBirds(birdQueue);
//	countdown(queue);
//}

//cleanUP(queue);

//GameSession session = GameSession::GameSession();
//AudioManager* audioMan = AudioManager::getAudioInstance();
//audioMan->stopByName("bgmBAALobby.ogg");

//session.Run(players);

//deletePlayers();