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
	int numPlayers = 0;
	int classSize = 6;

	numPlayers = NetworkManager::sInstance->GetPlayerCount();

	for (int i = 0; i < 8; i++){
		//build lobby player slots
	
	}

	for (int i = 0; i < classSize; i++){
		//build class slots

	}

	while (NetworkManager::sInstance->GetState() == NetworkManager::sInstance->NMS_Lobby){

		numPlayers = NetworkManager::sInstance->GetPlayerCount();
		//all players ready and teams are even
		if (playersReady == numPlayers && playersReady % 2 == 0){
			NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_Starting);
		}

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