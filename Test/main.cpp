#include "main.h"
#include <functional>
#include <crtdbg.h>

//#include "include\network\NetIncludes.h"


using namespace std;

void update();

//implement somewhere in config later
int SCREEN_HEIGHT = 450;
int SCREEN_WIDTH = 800;


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

	game session = game::game();
	session.run();


	/////////////////////////////////////////////////////
	// Loop freeing memoru
	for (unsigned int i = 0; i < GameObjects.alive_objects.size(); i++){
		GameObjects.DeleteObjects(GameObjects.alive_objects[i]->ID);
	}

	log->close();
	printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");

	return 0;
}