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
	

	for (int i = 0; i < 8; i++){
		//build lobby player slots 
		int x = (w / 2 + (w * 0.1f)) * i;
		int y = (h / 2 + (h * 0.1f)) * i;
		UIObjectFactory* playerSlot = new UIObjectFactory();
		queue.AddObject(playerSlot->Spawn(PLAYER_SLOT, x, y));
	}



	for (int i = 0; i < classSize; i++){
		//build class slots
		//UIObjectFactory* readyButton;

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