#include "test.h"
#include <functional>

//#include "include\network\NetIncludes.h"


using namespace std;

void update();
void render(RenderManager*);
long double getCurrentTime();

typedef float(*ease_function)(float);

int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	int numPlayers = 1;
	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit())
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";

	while (true){
		GamerServices::sInstance->Update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		//cout << "state: " << NetworkManager::sInstance->GetState() << endl;
		if (NetworkManager::sInstance->GetState() == 4)
			break;
		if (NetworkManager::sInstance->GetPlayerCount() == numPlayers){
			//NetworkManager::sInstance->GetAllPlayersInLobby();
			NetworkManager::sInstance->TryReadyGame();
		}
	}

	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");
	renderMan->zoom = 0.25;
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");

	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

	///  SYSTEMS

	SystemNetworkUpdater sysNetwork;
	SystemRenderUpdater sysRenderer;
	SystemInputUpdater sysInput;
	SystemLogicUpdater sysLogic;
	SystemPhysicsUpdater sysPhysics;


	//SystemGameObjectQueue world;

	/// ENTITIES
	PlayerObjectFactory pFactory;

	map< uint64_t, string > loby = NetworkManager::sInstance->getLobbyMap();

	SDLRenderObject* base = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 0, 0, 0);
	base->anchor = { 0.5, 0.5 };
	//base->setVisible(false);
	SDLRenderObject* leg = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 103, -5, 30);
	leg->anchor = { 42 / float(leg->renderRect.w), 2 / float(leg->renderRect.h) };
	SDLRenderObject* armor = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 101, 0, 0);
	armor->anchor = { 0.5, 0.5 };
	SDLRenderObject* arm = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 102, 31, 43);
	arm->anchor = { 14 / float(arm->renderRect.w), 3 / float(arm->renderRect.h) };

	leg->setParent(base);
	armor->setParent(base);
	arm->setParent(armor);

	SDLRenderObject* tenta1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 151, 0, 50);
	tenta1->anchor = { 74 / float(tenta1->getWidth()), 200 / float(tenta1->getHeight()) };
	tenta1->setScale(0.25);

	SDLRenderObject* tenta2 = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 151, 0 , tenta1->getHeight() - 200);
	tenta2->anchor = { 74 / float(tenta2->getWidth()), 200 / float(tenta2->getHeight()) };
	tenta2->setScale(0.90);
	tenta2->setParent(tenta1);


	SDLRenderObject* tenta3 = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 151, 0, tenta2->getHeight() - 200);
	tenta3->anchor = { 74 / float(tenta3->getWidth()), 200 / float(tenta3->getHeight()) };
	tenta3->setScale(0.90);
	tenta3->setParent(tenta2);


	SDLRenderObject* tenta4 = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 151, 0, tenta3->getHeight() - 200);
	tenta4->anchor = { 74 / float(tenta4->getWidth()), 200 / float(tenta4->getHeight()) };
	tenta4->setScale(0.90);
	tenta4->setParent(tenta3);

	SDLRenderObject* tenta[4];
	tenta[0] = tenta1;
	tenta[1] = tenta2;
	tenta[2] = tenta3;
	tenta[3] = tenta4;
	animation squirm;
	for (SDLRenderObject * iter : tenta){
		squirm.push(rotateTransform(iter, 90, -90), 0, 1, ease_QuadInOut);
	}
	for (auto &iter : loby){
		bool local = false;
		if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
			local = true;
			cout << "Local Player ID: " << iter.second << ", " << iter.first << endl;
		}
		GameObjects.AddObject(pFactory.Spawn(iter.first, local));
	}
	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	int var = 0;

	auto up = rotateTransform(arm, 0, 180);
	auto down = rotateTransform(arm, 180, 0);

	auto arcarm = moveEllipseArc(arm, 12, 14, 0, 4, -180, 360);
	auto arcbody = moveEllipseArc(armor, 0, 0, 5, 2, 0, -360);
	renderMan->zoom = 0.5;
	float size = 6;
	float ratio = 0.7;
	int armswing = size;
	int moveSpd = 1;
	int pressed = 0;
	int pressedTime = 3;
	int rotation = 0;
	while (gameloop) {
		var += 1;
		input->update();
		if (var % 40 < 20){
			squirm.animate(float(var % 40) / 20);
		}
		else{
			squirm.animate(2-float(var % 40) / 20);
		}
		//inputMan->update();
		//listen->getInput();
		NetworkManager::sInstance->ProcessIncomingPackets();
		NetworkManager::sInstance->UpdateDelay();

		//arm->rotation = var * 2;
		//base->posX += listen->input_x;
		//base->posY += listen->input_y;

		if (input->isKeyDown(KEY_DOWN)){
			base->posY += moveSpd;
		}
		if (input->isKeyDown(KEY_UP)){
			base->posY -= moveSpd;
		}
		if (input->isKeyDown(KEY_LEFT)){
			base->posX -= moveSpd;
		}
		if (input->isKeyDown(KEY_RIGHT)){
			base->posX += moveSpd;
		}
		if (input->isKeyDown(KEY_A) && !pressed){
			renderMan->flippedScreen = !renderMan->flippedScreen;
			pressed = pressedTime;
		}
		if (input->isKeyDown(KEY_Q) && !pressed){
			//base->setVisible(!base->isVisible());
			base->setFlippedH(!base->isFlippedH());
			pressed = pressedTime;
		}
		if (input->isKeyDown(KEY_W) && !pressed){
			//base->setVisible(!base->isVisible());
			base->setFlippedV(!base->isFlippedV());
			pressed = pressedTime;
		}
		if (pressed > 0)pressed--;
		if (input->isKeyDown(KEY_1)){
			base->setRotation(++rotation);
		}
		if (input->isKeyDown(KEY_2)){
			base->setRotation(--rotation);
		}
		if (input->isKeyDown(KEY_3)){
			base->setScale(2.0);
		}
		else if (input->isKeyDown(KEY_4)){
			base->setScale(0.5);
		}
		else if (input->isKeyDown(KEY_5)){
			base->setScale(2.0, 1.0);
		}
		else base->setScale(1.0);
		if (armswing > size && input->isKeyDown(KEY_Z)){
			armswing = 0;
		}
		if (armswing <= size){
			if (armswing < size*ratio)up(ease_QuadIn(float(armswing) / (size*ratio)));
			else down(ease_QuadOut(float(armswing - (size*ratio)) / (size*(1 - ratio))));
			cout << float(armswing) << endl;
			armswing += 1;
		}
		else{
			arcarm(float(var % 12) / 12);
		}
		arcbody(float(var % 12) / 12);

		//arm->posX = 31 + armor->posX;
		//arm->posY = 43 + armor->posY;

		int length = 20;
		float loop = (var % length);

		sysInput.InputUpdate(GameObjects.alive_object);
		sysRenderer.RenderUpdate(GameObjects.alive_object);
		sysLogic.LogicUpdate(GameObjects.alive_object);
		sysNetwork.NetworkUpdate(GameObjects.alive_object);
		sysPhysics.PhysicsUpdate(GameObjects.alive_object);


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