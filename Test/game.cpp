#include "game.h"

Game::Game(){
}

Game::~Game(){
}

void Game::mainMenu(InputManager* input, RenderManager* renderMan, SceneManager* sceneMan){

	SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	UIObjectFactory uFactory;
	SystemUIUpdater sysUI;
	SystemUIObjectQueue queue;
	UIObjectFactory playButton;
	UIObjectFactory joinButton;

	NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_MainMenu);
	
	queue.AddObject(playButton.Spawn(PLAY_BUTTON));
	queue.AddObject(joinButton.Spawn(JOIN_BUTTON));

	//UIObjects.AddObject(uFactory.Spawn(PLAY_BUTTON));
	//UIObjects.AddObject(uFactory.Spawn(JOIN_BUTTON));

	while (NetworkManager::sInstance->GetState() == NetworkManager::sInstance->NMS_MainMenu){

		renderMan->zoom = 0.5;
		input->update();

		sysUI.UIUpdate(queue.alive_objects);
		sysInput.InputUpdate(queue.alive_objects);

		//sysRend.RenderUpdate(queue.alive_objects);

		input->update();

		sceneMan->AssembleScene();
	}
	queue.DeleteObjects();
}

void Game::play(){
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

}

void Game::inLobby(){
	std::cout << GamerServices::sInstance->GetLocalPlayerName() << std::endl;
	std::cout << GamerServices::sInstance->GetLocalPlayerAvatar() << std::endl;
}