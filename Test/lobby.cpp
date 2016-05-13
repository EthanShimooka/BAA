#include "lobby.h"

vector<player*> players;

Lobby::Lobby(): playersReady(0), inLobbyNow(0), readyCount(0){
	numPlayers = NetworkManager::sInstance->GetPlayerCount();
	yellow = 0;
	purple = 0;
	me = new player();
}


Lobby::~Lobby(){
	delete me;
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

	uint64_t myId = NetworkManager::sInstance->GetMyPlayerId();
	//player* me = new player();
	addSlots(queue);
	assignPlayers();
	for (unsigned int i = 0; i < players.size(); i++){
		if (players[i]->playerId == myId)
			me = players[i];
	}
	
	drawBirds(birdQueue);


	createButtons(queue);

	NetworkManager::sInstance->UpdateLobbyPlayers();
	inLobbyNow = NetworkManager::sInstance->GetPlayerCount();

	//while loop running lobby
	while (NetworkManager::sInstance->GetState() < NetworkManager::sInstance->NMS_Starting){

		input->update();

		pickTeam();

		if (input->isKeyDown(KEY_P)){
			std::cout << yellow << " " << purple << std::endl;
		}

		GamerServices::sInstance->Update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		NetworkManager::sInstance->SendOutgoingPackets();
		NetworkManager::sInstance->UpdateLobbyPlayers();
		numPlayers = NetworkManager::sInstance->GetPlayerCount();

		//check for new players joining.
		if (numPlayers > inLobbyNow){
			addNewPlayers();
			NetworkManager::sInstance->UpdateLobbyPlayers();
			NetworkManager::sInstance->SendTeamToPeers(me->team);
			inLobbyNow = NetworkManager::sInstance->GetPlayerCount();
			auto& iter = NetworkManager::sInstance->lobbyInfoMap.find(GamerServices::sInstance->GetLocalPlayerId());
			if (iter->second.classType)
				NetworkManager::sInstance->SendSelectPacket(iter->second.classType);
		}

		//handles players dropping
		//std::cout << yellow << " " << purple << std::endl;
		updateLobby();
		
		//check if i am ready, change bird image, send over wire
		checkMyReady();

		//check if peers have selected team or bird class
		checkPlayerInfo();
		if (input->isKeyDown(KEY_ESCAPE))
			break; 
		//start game if ready, change state to NMS_Starting if ready
		if (me->ready && NetworkManager::sInstance->IsMasterPeer() && readyCount == numPlayers){
			deleteBirds(birdQueue);
			beginGame(queue);
		}
		if (NetworkManager::sInstance->GetState() == NetworkManager::NMS_MainMenu){
			break;
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


	//starting countdown
	if (NetworkManager::sInstance->GetState() >= NetworkManager::NMS_Starting){
		if (!NetworkManager::sInstance->IsMasterPeer()){
			deleteBirds(birdQueue);
		}
		countdown(queue);
	}

	cleanUP(queue);

	//if we are starting
	if (NetworkManager::sInstance->GetState() >= NetworkManager::NMS_Starting){
		GameSession session = GameSession::GameSession();
		AudioManager* audioMan = AudioManager::getAudioInstance();

		audioMan->stopByName("bgmBAALobby.ogg");

		session.Run(players);
	}
	//else return to main menu and clean up lobby
	else{
		GamerServices::sInstance->LeaveLobby(NetworkManager::sInstance->GetLobbyId());
	}
	deletePlayers();
}

void Lobby::checkMyReady(){
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
}

void Lobby::beginGame(SystemUIObjectQueue &q){
	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;

	rendMan->getWindowSize(&w, &h);
	UIObjectFactory* buttons = new UIObjectFactory();
	UIObject* playButton = buttons->Spawn(PLAY_BUTTON, w / 2 - 50, h / 2);

	q.AddObject(playButton);
	delete buttons;
}

void Lobby::checkPlayerInfo(){
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
}

void Lobby::deletePlayers(){
	for (unsigned int i = 0; i < players.size(); i++){
		if (players[i]->playerId != me->playerId){
			delete players[i];
		}
	}
	players.clear();
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
	UIObjectFactory* buttons = new UIObjectFactory();
	UIObject* inviteButton = buttons->Spawn(INVITE_BUTTON, 0, h / 2);
	//UIObject* backButton = buttons->Spawn(BACK_BUTTON, 0, h / 2 + 75);

	teamYellow = NULL;
	teamPurple = NULL;

	teamYellow = buttons->Spawn(YELLOW_BUTTON, w / 2 - 150, h / 2 + 200);
	q.AddObject(teamYellow);

	teamPurple = buttons->Spawn(PURPLE_BUTTON, w / 2 + 50, h / 2 + 200);
	q.AddObject(teamPurple);
	


	q.AddObject(inviteButton);
	//q.AddObject(backButton);
	delete buttons;
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
	UIObject* timer = countdown.Spawn(LOBBY_TIMER, 30, 30);

	q.AddObject(timer);
	Timing::sInstance.SetLobbyCountdown();
	Timing::sInstance.SetCountdownStart();

	SDLRenderObject* timerHUD = dynamic_cast<UIRenderComponent*>(timer->GetComponent(COMPONENT_RENDER))->objRef;

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

		std::string title = minutes + ":" + seconds;
		timerHUD->setResourceObject(renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular"));
		//renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular", timerHUD->renderResource);

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
	UIObjectFactory* allBirds = new UIObjectFactory();

	UIObject* bird = allBirds->Spawn(CHICKEN, x - 33, y);
	x += bird->getWidth();
	UIObject* bird2 = allBirds->Spawn(PEACOCK, x, y);
	x += bird2->getWidth();
	UIObject* bird3 = allBirds->Spawn(QUAIL, x, y);
	x += bird3->getWidth();
	UIObject* bird4 = allBirds->Spawn(TURKEY, x, y);
	x += bird4->getWidth();
	UIObject* bird5 = allBirds->Spawn(FLAMINGO, x, y);


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
	delete allBirds;
}

void Lobby::addSlots(SystemUIObjectQueue &queue){

	UIObjectFactory* slot = new UIObjectFactory();
	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;
	rendMan->getWindowSize(&w, &h);
	int x = w / 4;

	for (int i = 0; i < maxPlayers; i++){
		player *p = new player();
		p->playerId = NULL;
		p->name = "";
		if (i % 2 == 0){
			p->x = 0 + x;
			p->y = 0;
		}
		else{
			p->x = 0 + x;
			p->y = h - 25;
			x += w / 2;
			p->bottom = true;
		}

		p->team = TEAM_NEUTRAL;
		
		p->playerSlot = slot->Spawn(PLAYER_SLOT, p->x, p->y);
		p->visible = false;
		p->playerSlot->visible = p->visible;
		queue.AddObject(p->playerSlot);
		p->playerSlot->bottom = p->bottom;
		players.push_back(p);	
	}
	delete slot;
}

void Lobby::assignPlayers(){


	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
	NetworkManager::sInstance->ProcessIncomingPackets();
	int i = 0;
	for (const auto& iter : NetworkManager::sInstance->lobbyInfoMap){
		if (players[i]->playerId == NULL){
			players[i]->visible = true;
			players[i]->playerId = iter.first;
			players[i]->name = GamerServices::sInstance->GetRemotePlayerName(iter.first);
			players[i]->playerSlot->player = iter.first;
			players[i]->playerSlot->visible = players[i]->visible;  
			players[i]->team = (TEAM)iter.second.team;
			if (players[i]->team == TEAM_PURPLE){
				purple++;
			}
			else if (players[i]->team == TEAM_YELLOW){
				yellow++;
			}
			i++;
		}
	}
}

void Lobby::updateLobby(){

	//used or players dropping
	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
	for (unsigned int i = 0; i < players.size(); i++){
		if (players[i]->playerId != NULL){
			std::map<uint64_t, string>::iterator it;
			it = lobby.find(players[i]->playerId);
			if (it == lobby.end()){
				players[i]->playerId = NULL;
				players[i]->name = "";
				players[i]->ready = false;
				players[i]->visible = false;
				players[i]->playerSlot->visible = players[i]->visible;
				if (players[i]->team == TEAM_PURPLE){
					purple--;
					players[i]->team = TEAM_NEUTRAL;
				}
				else if (players[i]->team == TEAM_YELLOW){
					yellow--;
					players[i]->team = TEAM_NEUTRAL;
				}
				NetworkManager::sInstance->UpdateLobbyPlayers();
				inLobbyNow--;
			}
		}
	}

	if (yellow >= maxPlayers / 2){
		UIInputComponent* in = dynamic_cast<UIInputComponent*>(teamYellow->GetComponent(COMPONENT_INPUT));
		in->isClickable = false;
	}
	else{
		UIInputComponent* in = dynamic_cast<UIInputComponent*>(teamYellow->GetComponent(COMPONENT_INPUT));
		in->isClickable = true;
	}
	if (purple >= maxPlayers / 2){
		UIInputComponent* in = dynamic_cast<UIInputComponent*>(teamPurple->GetComponent(COMPONENT_INPUT));
		in->isClickable = false;
	}
	else{
		UIInputComponent* in = dynamic_cast<UIInputComponent*>(teamPurple->GetComponent(COMPONENT_INPUT));
		in->isClickable = true;
	}

	int y = 0, p = 0;
	//updates team choice just in case peers change it
	for (unsigned int i = 0; i < players.size(); i++){
		std::unordered_map<uint64_t, PlayerInfo> lobby = NetworkManager::sInstance->lobbyInfoMap;
		const auto& iter = lobby.find(players[i]->playerId);
		if (players[i]->playerId != me->playerId && players[i]->playerId != NULL){
			if (iter != lobby.end()){
				players[i]->team = (TEAM)iter->second.team;
				if ((TEAM)iter->second.team == TEAM_YELLOW){
					y++;
				}
				else if ((TEAM)iter->second.team == TEAM_PURPLE){
					p++;
				}
			}
		}
	}

	//used for keeping track of # on team
	if (y != yellow){
		yellow = y;
	}
	if (p != purple){
		purple = p;
	}

}

void Lobby::addNewPlayers(){

	bool found = false;

	for (const auto& iter : NetworkManager::sInstance->lobbyInfoMap){

		for (unsigned int i = 0; i < players.size(); i++){
			if (players[i]->playerId == iter.first){
				found = true;
			}
		}
		if (!found){
			for (unsigned int i = 0; i < players.size(); i++){
				if (players[i]->playerId == NULL){
					players[i]->visible = true;
					players[i]->playerId = iter.first;
					players[i]->name = GamerServices::sInstance->GetRemotePlayerName(iter.first);
					players[i]->playerSlot->player = iter.first;
					players[i]->playerSlot->visible = players[i]->visible;
					players[i]->team = (TEAM)iter.second.team;
					break;
				}
			}
		}
		else{
			found = false;
		}
	}
}

void Lobby::pickTeam(){

	if (teamPurple != NULL && teamPurple->teamPicked){
		if (me->team == TEAM_YELLOW){
			teamYellow->teamPicked = false;
		}
		else{
			teamPurple->teamPicked = true;
		}
		purple++;
		me->team = TEAM_PURPLE;
	}
	if (teamYellow != NULL && teamYellow->teamPicked){
		if (me->team == TEAM_PURPLE){
			teamPurple->teamPicked = false;
		}
		else{
			teamYellow->teamPicked = true;
		}
		yellow++;
		me->team = TEAM_YELLOW;
	}
}