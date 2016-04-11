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
	int classSize = 6;

	addPlayers(queue);
	assignPlayers();

	/*for (int i = 0; i < classSize / 2; i++){
		//build class slots
		int x, y;
		x = w / 2;
		y = h / 2;
		h -= 100;
		UIObjectFactory* birdClass = new UIObjectFactory();
		queue.AddObject(birdClass->Spawn(BIRD, x, y));
	}

	h = z;
	for (int i = 0; i < classSize / 2; i++){
		//build class slots
		int x, y;
		x = w / 2;
		y = h / 2;
		h -= 100;
		UIObjectFactory* birdClass = new UIObjectFactory();
		queue.AddObject(birdClass->Spawn(BIRD, x + 50, y));
	}*/

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

void Lobby::addPlayers(SystemUIObjectQueue &queue){

	RenderManager* rendMan = RenderManager::getRenderManager();
	int w, h;
	rendMan->getWindowSize(&w, &h);
	int z = h;

	for (int i = 0; i < maxPlayers; i++){
		player *p = new player();
		p->playerId = NULL;
		p->name = "";
		p->team = NOTEAM;
		if (i % 2 == 0){
			p->x = w / 4;
			p->y = z / 2;
			z -= 100;
		}
		else{
			p->x = (3 * w) / 4;
			p->y = h / 2;
			h += 100;
		}
		queue.AddObject(p->playerSlot->Spawn(PLAYER_SLOT, p->x, p->y));
		queue.AddObject(p->readyButton->Spawn(READY_BUTTON, p->x + 50, p->y));
		players.push_back(p);
	}
}

void Lobby::assignPlayers(){
	std::map<uint64_t, string> lobby = NetworkManager::sInstance->getLobbyMap();
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