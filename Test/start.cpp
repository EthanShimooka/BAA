#include "start.h"


Start::Start(){	
}

Start::~Start(){
}

void Start::mainMenu(){
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	AudioManager* audioMan = AudioManager::getAudioInstance();
	LogManager* log = LogManager::GetLogManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();

	/*resMan->loadFromXMLFile("source.xml");
	resMan->setCurrentScope(0);
	sceneMan->loadFromXMLFile("SceneTree.xml");*/
	input->update();
	log->create("log.txt");
	renderMan->setBackground("Menu_bg.png");
	resourceMan->loadFromXMLFile("source.xml");
	renderMan->zoom = 0.5;

	/*audioMan->loadAllAudio();
	audioMan->playByName("bgmBAALobby.ogg");*/
	std::cout << audioMan->audioObjects.size() << std::endl;
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");
	

	int w, h;
	renderMan->getWindowSize(&w, &h);

	/*SystemGameObjectQueue sysQueue;
	ButtonObjectFactory bFactory;
	SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	SystemLogicUpdater sysLogic;*/
	Lobby lobby;

	// making buttons
	playButt = bFactory.Spawn(3521, 200, 150, _PLAY_BUTTON);
	GameObjects.AddObject(playButt);

	int startInput = waitForInput();

	switch (startInput){
	case 1:
		removeButtons();
		NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_SinglePlayer);
		lobby.runLobby();
		break;
	}


	//UIObjectFactory uFactory;
	//SystemUIUpdater sysUI;
	//SystemUIObjectQueue queue;
	//UIObjectFactory menuButtons;

	//NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_MainMenu);

	//queue.AddObject(menuButtons.Spawn(OPTIONS_BUTTON, w / 2 + 25, h / 2 - 25));
	//queue.AddObject(menuButtons.Spawn(JOIN_BUTTON, w / 2 - 125, h / 2 - 25));

	//while (NetworkManager::sInstance->GetState() == NetworkManager::sInstance->NMS_MainMenu){

	//	renderMan->zoom = 0.5;
	//	input->update();

	//	if (input->isKeyDown(KEY_K)){
	//		NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_SinglePlayer);
	//	}

	//	sysUI.UIUpdate(queue.alive_objects);
	//	sysInput.InputUpdate(queue.alive_objects);
	//	sysRend.RenderUpdate(queue.alive_objects);
	//	////////
	//	sysRend.RenderUpdate(GameObjects.alive_objects);
	//	sysLogic.LogicUpdate(GameObjects.alive_objects);
	//	////////
	//	input->update();

	//	sceneMan->AssembleScene();
	//}

	//for (unsigned int i = 0; i < queue.alive_objects.size(); i++){
	//	queue.alive_objects[i]->visible = false;
	//}
	//sysRend.RenderUpdate(queue.alive_objects);
	//sceneMan->AssembleScene();
	//queue.DeleteObjects();

	//Lobby lobby;
	//lobby.runLobby();
}


int Start::waitForInput(){
	while (true){
		sysRend.RenderUpdate(GameObjects.alive_objects);
		sysLogic.LogicUpdate(GameObjects.alive_objects);
		InputManager::getInstance()->update();
		SceneManager::GetSceneManager()->AssembleScene();
		if (dynamic_cast<ButtonLogicComponent*>(playButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed()){
			return 1;
		}
	}
}

void Start::removeButtons(){
	SceneManager::GetSceneManager()->RemoveObject(dynamic_cast<ButtonRenderComponent*>(playButt->GetComponent(COMPONENT_RENDER))->objRef, 
													SceneManager::GetSceneManager()->findLayer("layer1"));
	GameObjects.DeleteObjects();
	SceneManager::GetSceneManager()->AssembleScene();
}