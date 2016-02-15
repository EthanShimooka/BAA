#include "test.h"



//#include "include\network\NetIncludes.h"

using namespace std;

void update();
void render(RenderManager*);
long double getCurrentTime();


int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){

	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	/*if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit())
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";

	while (true){
		GamerServices::sInstance->Update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		cout << "state: " << NetworkManager::sInstance->GetState() << endl;
		if (NetworkManager::sInstance->GetState() == 4)
			break;
		if (NetworkManager::sInstance->GetPlayerCount() == 2){
			NetworkManager::sInstance->GetAllPlayersInLobby();
			NetworkManager::sInstance->TryReadyGame();
		}
	}*/

	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");

	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");

	InputListener* listen = new InputListener();


	Square* player1 = new Square(100, 100, 1);
	player1->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2, player1->x, player1->y);
	Square* player2 = new Square(200, 200, 2);
	player2->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, player2->x, player2->y);

	struct point{
		int x = 0;
		int y = 0;
	}center;
	//center = {};
	Square* leg = new Square(14+center.x, 60+center.y, 3);
	leg->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 103, leg->x, leg->y);
	leg->obj->anchor = { 42 / float(leg->obj->renderRect.w), 2 / float(leg->obj->renderRect.h) };
	Square* armor = new Square(0+center.x, 0+center.y, 4);
	armor->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 101, armor->x, armor->y);
	armor->obj->anchor = {0,0};
	Square* arm = new Square(31+center.x, 43+center.y, 5);
	arm->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 102, arm->x, arm->y);
	arm->obj->anchor = { 14 / float(arm->obj->renderRect.w), 3 / float(arm->obj->renderRect.h) };
	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;

	int var = 0;
	while (gameloop) {
		var += 1;
		//NetworkManager::sInstance->ProcessIncomingPackets();
		listen->getInput();

		//arm->obj->rotation = var * 2;
		center.x += listen->input_x;
		center.y += listen->input_y;
		armor->obj->posX = 0 + center.x;
		armor->obj->posY = 0 + center.y;
		leg->obj->posX = 14 + armor->obj->posX;
		leg->obj->posY = 60 + armor->obj->posY;
		arm->obj->posX = 31 + armor->obj->posX;
		arm->obj->posY = 43 + armor->obj->posY;

		//cout << player1->obj->posX << "," << player2->obj->posX<< endl;

		player2->update();

		if (input->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		input->update();
		

		sceneMan->AssembleScene();

		//render(renderMan);
	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	std::cout << renderMan << endl;

	log->close();
	return 0;
}


void init(){

}





void render(RenderManager* renderMan) {
	renderMan->update();
}

long double getCurrentTime(){
	long double sysTime = time(0);
	long double sysTimeMS = sysTime * 1000;

	return sysTimeMS;
}