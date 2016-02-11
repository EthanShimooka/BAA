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
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");

	InputManager* input = InputManager::getInstance();
	InputListener* listen = new InputListener();

	Square* player = new Square();
	player->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"),2,100, 100);


	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;

	while (gameloop) {
	
		listen->getInput();

		player->x += listen->input_x;
		player->y += listen->input_y;

		player->update();

		if (input->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		input->update();
		update();

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


void update() {




}


void render(RenderManager* renderMan) {
	renderMan->update();
}

long double getCurrentTime(){
	long double sysTime = time(0);
	long double sysTimeMS = sysTime * 1000;

	return sysTimeMS;
}