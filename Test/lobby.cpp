#include "lobby.h"


Lobby::Lobby(){
	runLobby();
}


Lobby::~Lobby(){
}

void Lobby::runLobby(){
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	UIObjectFactory uFactory;
	SystemUIUpdater sysUI;
	SystemUIObjectQueue queue;

	bool isReady = false;
	int playersReady = 0;
	int numPlayers = NetworkManager::sInstance->GetPlayerCount();
	int classSize = 6;

	numPlayers = NetworkManager::sInstance->GetPlayerCount();

	RenderManager* rendMan = RenderManager::getRenderManager();

	int w, h;
	rendMan->getWindowSize(&w, &h);
	int z = h;
	std::cout << NetworkManager::sInstance->GetLobbyId() << std::endl;

	for (int i = 0; i < 4; i++){
		//build lobby player slots 
		int x, y;
		x = w / 4;
		y = h / 2;
		h -= 100;
		UIObjectFactory* playerSlot = new UIObjectFactory();
		UIObjectFactory* readyButton = new UIObjectFactory();
		queue.AddObject(playerSlot->Spawn(PLAYER_SLOT, x, y));
		queue.AddObject(readyButton->Spawn(READY_BUTTON, x + 50, y));
	}

	h = z;
	for (int i = 0; i < 4; i++){
		//build lobby player slots
		int x, y;
		x = (3 * w) / 4;
		y = h / 2;
		h += 100;
		UIObjectFactory* playerSlot = new UIObjectFactory();
		UIObjectFactory* readyButton = new UIObjectFactory();
		queue.AddObject(playerSlot->Spawn(PLAYER_SLOT, x, y));
		queue.AddObject(readyButton->Spawn(READY_BUTTON, x + 50, y));
	}

	h = z;
	for (int i = 0; i < classSize / 2; i++){
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
	}

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

/*void lobby::(){
	switch (NetworkManager::sInstance->GetState()){
	case NetworkManager::NMS_Searching:
		while (NetworkManager::sInstance->GetState() != NetworkManager::sInstance->NMS_Lobby){
			GamerServices::sInstance->Update();
		}
		std::cout << "In lobby" << std::endl;
		inLobby();
		break;
	case NetworkManager::NMS_SinglePlayer:
		break;
	}

}*/