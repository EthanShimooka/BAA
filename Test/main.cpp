#include "main.h"
#include <functional>
#include <crtdbg.h>

//#include "include\network\NetIncludes.h"


using namespace std;

void update();

//implement somewhere in config later
<<<<<<< HEAD
int SCREEN_HEIGHT = 900;
int SCREEN_WIDTH = 1600;

=======
int SCREEN_HEIGHT = 800;
int SCREEN_WIDTH = 1200;
>>>>>>> origin/Ricardo-text


int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	
	
	RenderManager* renderMan = RenderManager::getRenderManager();
	renderMan->init(SCREEN_WIDTH, SCREEN_HEIGHT, false, "Birds At Arms");


	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	int numPlayers = 1;
	if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit()){
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";
	}

	// don't need to change this line
	int numLobbyPlayer = 0;

	/////////////////////////////////////////////////////
	//  GAME CALL

	GameSession session = GameSession::GameSession();
	session.Run();


	/////////////////////////////////////////////////////
	// Loop freeing memory NOW MOVED TO DESTRUCTOROF SYSTEMGAMEOBJECTQUEUE
	//for (unsigned int i = 0; i < GameObjects.alive_objects.size(); i++){
		//GameObjects.DeleteObjects(GameObjects.alive_objects[i]->ID);
	//}

	log->close();

	return 0;
}