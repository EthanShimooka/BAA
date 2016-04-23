#include "lobby.h"

vector<player*> players;

Lobby::Lobby(): playersReady(0), teamRed(0), inLobbyNow(0){
	numPlayers = NetworkManager::sInstance->GetPlayerCount();
}


Lobby::~Lobby(){
}

void Lobby::runLobby(){
	//std::cout << numPlayers << std::endl;
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();

	renderMan->setBackground("Lobby_bg.png");


	SceneManager* sceneMan = SceneManager::GetSceneManager();

	SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	UIObjectFactory uFactory;
	SystemUIUpdater sysUI;
	SystemUIObjectQueue queue;
	SystemUIObjectQueue birdQueue;

	addSlots(queue);
	drawBirds(birdQueue);

	uint64_t myId = NetworkManager::sInstance->GetMyPlayerId();
	player* me = new player();

	assignPlayers();
		
	for (unsigned int i = 0; i < players.size(); i++){
		if (players[i]->playerId == myId)
			me = players[i];
	}

	createButtons(queue);

	NetworkManager::sInstance->UpdateLobbyPlayers();
	inLobbyNow = NetworkManager::sInstance->GetPlayerCount();
	int readyCount = 0;

	//while loop running lobby
	while (NetworkManager::sInstance->GetState() < NetworkManager::sInstance->NMS_Starting){
		/*std::cout << "lobby count: " << NetworkManager::sInstance->GetPlayerCount()<< std::endl;
		std::cout << "master: " << NetworkManager::sInstance->IsMasterPeer() << std::endl;*/
		input->update();

		GamerServices::sInstance->Update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		NetworkManager::sInstance->SendOutgoingPackets();
		NetworkManager::sInstance->UpdateLobbyPlayers();
		numPlayers = NetworkManager::sInstance->GetPlayerCount();

		//check for new players joining.
		if (numPlayers > inLobbyNow){
			addNewPlayers();
			NetworkManager::sInstance->UpdateLobbyPlayers();
			inLobbyNow = NetworkManager::sInstance->GetPlayerCount();
			auto& iter = NetworkManager::sInstance->lobbyInfoMap.find(GamerServices::sInstance->GetLocalPlayerId());
			if (iter->second.classType)
				NetworkManager::sInstance->SendSelectPacket(iter->second.classType);
		}

		updateLobby();
		
		if (!me->ready){
			for (unsigned int i = 0; i < Birds.size(); i++){
				if (Birds[i]->ready){
					me->playerChoice = Birds[i]->ID;
					me->playerSlot->changePicture = true;
					me->playerSlot->changeTo = Birds[i]->ID;
					NetworkManager::sInstance->SendSelectPacket((int)Birds[i]->ID);
					me->ready = true;
					readyCount++;
					break;
				}
				if (Birds[i]->hoverPicture){
					me->playerSlot->hoverPicture = true;
					me->playerSlot->changeTo = Birds[i]->ID;
					break;
				}
				else{
					me->playerSlot->hoverPicture = false;
				}
			}
		}

		for (const auto& iter : NetworkManager::sInstance->lobbyInfoMap){
			for (const auto& player : players){
				if (player->playerId == iter.first){
					if (iter.second.classType != (int)player->playerSlot->changeTo && iter.second.classType != -1){
						//std::cout << "TYPE: " << iter.first << ", " << (UIType)iter.second.classType << ", " << iter.second.classType << std::endl;
						player->playerChoice = (UIType)iter.second.classType;
						player->playerSlot->changePicture = true;
						player->playerSlot->changeTo = (UIType)iter.second.classType;
						player->ready = true;
						readyCount++;
					}
				}
			}
		}

		if (me->ready && NetworkManager::sInstance->IsMasterPeer() && readyCount == numPlayers){
			NetworkManager::sInstance->TryReadyGame();
		}

		sysUI.UIUpdate(queue.alive_objects);
		sysInput.InputUpdate(queue.alive_objects);
		sysRend.RenderUpdate(queue.alive_objects);
		sysUI.UIUpdate(birdQueue.alive_objects);
		sysInput.InputUpdate(birdQueue.alive_objects);
		sysRend.RenderUpdate(birdQueue.alive_objects);

		input->update();
		
		sceneMan->AssembleScene();

	}

	if (NetworkManager::sInstance->GetState() >= NetworkManager::NMS_Starting){
		deleteBirds(birdQueue);
		countdown(queue);
	}

	cleanUP(queue);

	GameSession session = GameSession::GameSession();
	session.Run(players);
}

void Lobby::deleteBirds(SystemUIObjectQueue &queue){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	SystemRenderUpdater sysRend;
	for (unsigned int i = 0; i < queue.alive_objects.size(); i++){
		queue.alive_objects[i]->visible = false;
	}
	sysRend.RenderUpdate(queue.alive_objects);
	sceneMan->AssembleScene();
	queue.DeleteObjects();
	Birds.clear();
}

void Lobby::createButtons(SystemUIObjectQueue &q){

	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;

	rendMan->getWindowSize(&w, &h);
	UIObjectFactory* invite = new UIObjectFactory();
	UIObject* inviteButton = invite->Spawn(INVITE_BUTTON, 0, h/2);
	q.AddObject(inviteButton);
}

void Lobby::cleanUP(SystemUIObjectQueue &q){

	SceneManager* sceneMan = SceneManager::GetSceneManager();
	SystemRenderUpdater sysRend;

	for (unsigned int i = 0; i < q.alive_objects.size(); i++){
		q.alive_objects[i]->visible = false;
	}

	sysRend.RenderUpdate(q.alive_objects);
	sceneMan->AssembleScene();
	q.DeleteObjects();
}

void Lobby::countdown(SystemUIObjectQueue &q){

	RenderManager* renderMan = RenderManager::getRenderManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	SystemRenderUpdater sysRend;
	UIObjectFactory countdown;
	UIObject* timer = countdown.Spawn(LOBBY_TIMER);

	q.AddObject(timer);
	Timing::sInstance.SetLobbyCountdown();
	Timing::sInstance.SetCountdownStart();

	SDLRenderObject* timerHUD = new SDLRenderObject();
	timerHUD = dynamic_cast<UIRenderComponent*>(timer->GetComponent(COMPONENT_RENDER))->objRef;

	while (true){

		sysRend.RenderUpdate(q.alive_objects);
		sceneMan->AssembleScene();

		int timeRemaininginSeconds = Timing::sInstance.GetTimeRemainingS();
		string minutes = Timing::sInstance.GetMinutesLeftAsString(timeRemaininginSeconds);
		string seconds = Timing::sInstance.GetSecondsLeftAsString(timeRemaininginSeconds);

		if (seconds.length() == 1){
			seconds = "0" + seconds;
		}

		if (timeRemaininginSeconds == 0){
			Timing::sInstance.SetGamePlayCountdown();
			return;
		}

		std::string title = minutes + ":" + seconds; //concat on the time remaining here!
		timerHUD->setResourceObject(renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular"));
	}
}

void Lobby::drawBirds(SystemUIObjectQueue &queue){
	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;

	rendMan->getWindowSize(&w, &h);
	int x, y;

	x = w / 5;
	y = h / 2;
	//build class slots
	UIObjectFactory* chx = new UIObjectFactory();
	UIObjectFactory* pCock = new UIObjectFactory();
	UIObjectFactory* quail = new UIObjectFactory();
	UIObjectFactory* turkey = new UIObjectFactory();
	UIObjectFactory* flamingo = new UIObjectFactory();
	UIObject* bird = chx->Spawn(CHICKEN, x - 33, y);
	x += bird->getWidth();
	UIObject* bird2 = pCock->Spawn(PEACOCK, x, y);
	x += bird2->getWidth();
	UIObject* bird3 = quail->Spawn(QUAIL, x, y);
	x += bird3->getWidth();
	UIObject* bird4 = turkey->Spawn(TURKEY, x, y);
	x += bird4->getWidth();
	UIObject* bird5 = flamingo->Spawn(FLAMINGO, x, y);


	Birds.push_back(bird);
	Birds.push_back(bird2);
	Birds.push_back(bird3);
	Birds.push_back(bird4);
	Birds.push_back(bird5);

	queue.AddObject(bird);
	queue.AddObject(bird2);
	queue.AddObject(bird3);
	queue.AddObject(bird4);
	queue.AddObject(bird5);
}

void Lobby::addSlots(SystemUIObjectQueue &queue){

	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;
	rendMan->getWindowSize(&w, &h);
	int x = w / 4;

	for (int i = 0; i < maxPlayers; i++){
		player *p = new player();
		p->playerId = NULL;
		p->name = "";
		if (i % 2 == 1){
			p->x = 0 + x;
			p->y = 0;
			if (NetworkManager::sInstance->IsMasterPeer()){
				p->team = TEAM_YELLOW;
			}
			else{
				p->team = TEAM_NEUTRAL;
			}
		}
		else{
			p->x = 0 + x;
			p->y = h - 25;
			x += w / 2;
			if (NetworkManager::sInstance->IsMasterPeer()){
				p->team = TEAM_PURPLE;
			}
			else{
				p->team = TEAM_NEUTRAL;
			}
			p->bottom = true;
		}
		
		UIObjectFactory* slot = new UIObjectFactory();
		p->playerSlot = slot->Spawn(PLAYER_SLOT, p->x, p->y);
		p->visible = false;
		p->playerSlot->visible = p->visible;
		p->playerSlot->bottom = p->bottom;
		queue.AddObject(p->playerSlot);
		players.push_back(p);
	}
}

void Lobby::assignPlayers(){

	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();

	int i = 0;
	for (std::map<uint64_t, string>::iterator it = lobby.begin(); it != lobby.end(); it++){
		if (players[i]->playerId == NULL){
			players[i]->visible = true;
			players[i]->playerId = it->first;
			players[i]->name = it->second;
			players[i]->playerSlot->player = it->first;
			players[i]->playerSlot->visible = players[i]->visible;
			i++;
		}
	}
}

void Lobby::updateLobby(){

	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
	for (unsigned int i = 0; i < players.size(); i++){
		std::map<uint64_t, string>::iterator it;
		it = lobby.find(players[i]->playerId);
		if (it == lobby.end()){
			players[i]->playerId = NULL;
			players[i]->name = "";
			players[i]->ready = false;
			players[i]->visible = false;
			players[i]->playerSlot->visible = players[i]->visible;
			NetworkManager::sInstance->UpdateLobbyPlayers();
			inLobbyNow--;
		}
	}
}

void Lobby::addNewPlayers(){

	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
	std::map<uint64_t, string>::iterator it = lobby.begin();
	bool found = false;

	for (it; it != lobby.end(); it++){

		for (unsigned int i = 0; i < players.size(); i++){
			if (players[i]->playerId == it->first){
				found = true;
			}
		}
		if (!found){
			for (unsigned int i = 0; i < players.size(); i++){
				if (players[i]->playerId == NULL){
					players[i]->visible = true;
					players[i]->playerId = it->first;
					players[i]->name = it->second;
					players[i]->playerSlot->player = it->first;
					players[i]->playerSlot->visible = players[i]->visible;
					int team = players[i]->team;
					NetworkManager::sInstance->SendTeamInfo(team, it->first);
					break;
				}
			}
		}
		else{
			found = false;
		}
	}
}