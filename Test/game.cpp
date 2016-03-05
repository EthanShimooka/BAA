#include "game.h"

Game::Game(){

}

Game::~Game(){

}

UIType Game::mainMenu(InputManager* input, RenderManager* renderMan, SceneManager* sceneMan){

	SystemInputUpdater sysInput;
	UIObjectFactory uFactory;
	SystemUIUpdater sysUI;
	SystemUIObjectQueue queue;
	UIObjectFactory playButton;
	UIObjectFactory joinButton;
	
	queue.AddObject(playButton.Spawn(PLAY_BUTTON));
	queue.AddObject(joinButton.Spawn(JOIN_BUTTON));

	//UIObjects.AddObject(uFactory.Spawn(PLAY_BUTTON));
	//UIObjects.AddObject(uFactory.Spawn(JOIN_BUTTON));

	while (true){

		renderMan->zoom = 0.5;
		input->update();

		if (input->isKeyDown(KEY_0))
			break;

			sysUI.UIUpdate(queue.alive_objects);
			sysInput.InputUpdate(queue.alive_objects);

		input->update();

		sceneMan->AssembleScene();
	}
	queue.DeleteObjects();
	return PLAY_BUTTON;
}