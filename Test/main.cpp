#include "main.h"
#include <functional>
//#include <crtdbg.h>


#include "MainMenu.h"
#include "LobbyMenu.h"
#include "GameOver.h"
#include "Stats.h"
//#include "include\network\NetIncludes.h"


using namespace std;

void update();


int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	int nextScene = SCENE_MENU;
	bool game = true;
	Scene* scene;
	GameSession* scn;

	LogManager::GetLogManager()->create("log.txt");
	SceneManager::GetSceneManager()->loadFromXMLFile("SceneTree.xml");
	ResourceManager::GetResourceManager()->loadFromXMLFile("source.xml");
	InputManager::getInstance()->update();
	RenderManager::getRenderManager()->init(SCREEN_WIDTH, SCREEN_HEIGHT, false, "Birds At Arms");
	AudioManager* audioMan = AudioManager::getAudioInstance();

	if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit()){
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";
	}

	while (game){
		switch (nextScene){
		case SCENE_MENU:
			audioMan->loadAllAudio();
			audioMan->playByName("bgmBAALobby.ogg");
			scene = new MainMenu();
			nextScene = scene->runScene();
			delete scene;
			break;
		case SCENE_LOBBY:
			scene = new LobbyMenu();
			nextScene = scene->runScene();
			delete scene;
			audioMan->stopByName("bgmBAALobby.ogg");
			break;
		case SCENE_GAME:
			scn = new GameSession();
			nextScene = scn->Run();
			delete scn;
			break;
		case SCENE_GAMEOVER:
			scene = new GameOver();
			nextScene = scene->runScene();
			delete scene;
			break;
		case SCENE_END:
			game = false;
			break;
		}
	}


	LogManager::GetLogManager()->close();

	return 0;
}