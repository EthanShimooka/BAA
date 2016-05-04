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

	log->create("log.txt");
	renderMan->setBackground("Menu_bg.png");

	resourceMan->loadFromXMLFile("source.xml");
	renderMan->zoom = 0.25;

	/*audioMan->loadAllAudio();
	audioMan->playByName("bgmBAALobby.ogg");*/
	//std::cout << audioMan->audioObjects.size() << std::endl;
	resourceMan->setCurrentScope(0);
	//std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");
	input->update();

	int w, h;
	renderMan->getWindowSize(&w, &h);

	SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	SystemUIUpdater sysUI;
	SystemUIObjectQueue queue;
	UIObjectFactory menuButtons;

	NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_MainMenu);
	
	queue.AddObject(menuButtons.Spawn(OPTIONS_BUTTON, (float)w - 125, (float)h - 150 ));
	queue.AddObject(menuButtons.Spawn(JOIN_BUTTON, (float)w - 125, (float)h - 75));

	while (NetworkManager::sInstance->GetState() == NetworkManager::sInstance->NMS_MainMenu){

		renderMan->zoom = 0.5;
		input->update();

		sysUI.UIUpdate(queue.alive_objects);
		sysInput.InputUpdate(queue.alive_objects);
		sysRend.RenderUpdate(queue.alive_objects);

		input->update();

		sceneMan->AssembleScene();
	}

	for (unsigned int i = 0; i < queue.alive_objects.size(); i++){
		queue.alive_objects[i]->visible = false;
	}
	sysRend.RenderUpdate(queue.alive_objects);
	sceneMan->AssembleScene();
	queue.DeleteObjects();

	Lobby lobby;
	lobby.runLobby();
}