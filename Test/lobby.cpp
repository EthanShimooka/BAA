#include "lobby.h"


Lobby::Lobby(): playersReady(0){
	numPlayers = NetworkManager::sInstance->GetPlayerCount();
	runLobby();
}


Lobby::~Lobby(){
}

void Lobby::runLobby(){
	//std::cout << numPlayers << std::endl;
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	UIObjectFactory uFactory;
	SystemUIUpdater sysUI;
	SystemUIObjectQueue queue;

	int inLobbyNow = 0;

	addPlayers(queue);
	drawBirds(queue);
	assignPlayers(sceneMan, renderMan);

	while (NetworkManager::sInstance->GetState() == NetworkManager::sInstance->NMS_Lobby){

		input->update();

		numPlayers = NetworkManager::sInstance->GetPlayerCount();
		//all players ready and teams are even
		if (playersReady == numPlayers && playersReady % 2 == 0){
			NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_Starting);
		}
		
		sysUI.UIUpdate(queue.alive_objects);
		sysInput.InputUpdate(queue.alive_objects);
		sysRend.RenderUpdate(queue.alive_objects);

		input->update();

		sceneMan->AssembleScene();

	}

}

void Lobby::drawBirds(SystemUIObjectQueue &queue){
	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;
	int classSize = 6;

	rendMan->getWindowSize(&w, &h);
	int x, y;
	x = w / 4;
	y = h / 2;
	for (int i = 0; i < classSize; i++){
		//build class slots
		UIObjectFactory* birdClass = new UIObjectFactory();
		queue.AddObject(birdClass->Spawn(BIRD, x, y));
		x += 75;
	}
}

void Lobby::addPlayers(SystemUIObjectQueue &queue){

	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;
	rendMan->getWindowSize(&w, &h);
	int x = w / 5;
	for (int i = 0; i < maxPlayers; i++){
		player *p = new player();
		p->playerId = NULL;
		p->name = "";
		p->team = NOTEAM;
		if (i % 2 == 0){
			p->x = 0 + x;
			p->y = 0;
		}
		else{
			p->x = 0 + x;
			p->y = h - 25;
			x += w / 5;
		}
		
		/*UIObjectFactory name;
		queue.AddObject(name.Spawn(MENU_NAME, w / 2, w / 2));*/
		queue.AddObject(p->playerSlot->Spawn(PLAYER_SLOT, p->x, p->y));
		players.push_back(p);
	}
}

void Lobby::assignPlayers(SceneManager* sceneMan, RenderManager* renderMan){
	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();

	int w, h;
	renderMan->getWindowSize(&w, &h);

	int i = 0;
	for (std::map<uint64_t, string>::iterator it = lobby.begin(); it != lobby.end(); it++){
		if (players[i]->playerId == NULL){
			players[i]->playerId = it->first;
			players[i]->name = it->second;
			players[i]->playerSlot->player = it->first;
			players[i]->readyButton->player = it->first;
			i++;
		}
	}
}

void Lobby::updateLobby(){
	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
	for (int i = 0; i < players.size(); i++){
		std::map<uint64_t, string>::iterator it;
		it = lobby.find(players[i]->playerId);
		if (it == lobby.end()){
			players[i]->playerId = NULL;
			players[i]->name = "";
			players[i]->team = NOTEAM;
			players[i]->ready = false;
		}
	}
}