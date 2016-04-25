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

	log->create("log.txt");
	renderMan->setBackground("Menu_bg.png");

	resourceMan->loadFromXMLFile("source.xml");
	renderMan->zoom = 0.25;

	audioMan->loadAllAudio();
	audioMan->playByName("bgmBAALobby.ogg");
	std::cout << audioMan->audioObjects.size() << std::endl;
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");
	input->update();

	SystemInputUpdater sysInput;
	SystemRenderUpdater sysRend;
	UIObjectFactory uFactory;
	SystemUIUpdater sysUI;
	SystemUIObjectQueue queue;
	UIObjectFactory playButton;
	UIObjectFactory joinButton;

	NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_MainMenu);

	queue.AddObject(playButton.Spawn(OPTIONS_BUTTON));
	queue.AddObject(joinButton.Spawn(JOIN_BUTTON));

	while (NetworkManager::sInstance->GetState() == NetworkManager::sInstance->NMS_MainMenu){

		renderMan->zoom = 0.5;
		input->update();

		if (input->isKeyDown(KEY_K)){
			NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_SinglePlayer);
		}

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