#include "test.h"
#include <functional>

//#include "include\network\NetIncludes.h"


using namespace std;


void render(RenderManager*);
typedef float(*ease_function)(float);

int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit())
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";

		/*while (true){
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
*/
	int numPlayers = 1;

	if (numPlayers != 1){
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
	}
	

	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	renderMan->setBackground("tempbackground.png");
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
	SystemUIUpdater sysUI;


	//SystemGameObjectQueue world;

	/// ENTITIES
	PlayerObjectFactory pFactory;
	MinionObjectFactory mFactory;
	FeatherObjectFactory fFactory;
	UIObjectFactory uFactory;

	/**/UIObjects.AddObject(uFactory.Spawn(BUTTON));

	while (true){

		input->update();

		if (input->isKeyDown(KEY_0))
			break;

		sysUI.UIUpdate(UIObjects.alive_objects);
		sysInput.InputUpdate(UIObjects.alive_objects);
		

		input->update();

		sceneMan->AssembleScene();
	}

	if (numPlayers != 1){
		map< uint64_t, string > loby = NetworkManager::sInstance->getLobbyMap();

		for (auto &iter : loby){
			bool local = false;
			if (iter.first == NetworkManager::sInstance->GetMyPlayerId()){
				local = true;
				cout << "Local Player ID: " << iter.second << ", " << iter.first << endl;
			}
			GameObjects.AddObject(pFactory.Spawn(iter.first, local));
		}
	}
	else{
		GameObjects.AddObject(pFactory.Spawn(10000, true));
	}

	for (uint64_t i = 0; i < 4; ++i){
		GameObjects.AddObject(mFactory.Spawn(i))->setPos(i * 50, i * 50);
	}

	for (uint64_t i = 0; i < 4; ++i) {
		GameObjects.AddObject(mFactory.Spawn(i))->setPos(i * 50, i * 50);
		GameObjects.AddObject(fFactory.Spawn(i * 4))->setPos(i * 50 + 5, i * 50 + 5);
	}
	



	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;
	int ID = -1;

	/*while (gameloop) {
		NetworkManager::sInstance->ProcessIncomingPackets();
		listen->getInput();
		

		localPlayer->x += listen->input_x;
		localPlayer->y += listen->input_y;

		//cout << player1->obj->posX << "," << player2->obj->posX<< endl;

		localPlayer->update();

		OutputMemoryBitStream outData;
		outData.Write(NetworkManager::sInstance->kPosCC);
		localPlayer->Write(outData);
		NetworkManager::sInstance->sendPacketToAllPeers(outData);
		//cout << "test size: " << NetworkManager::sInstance->test.size() << endl;
		for (int i = 0; i < NetworkManager::sInstance->test.size(); ++i){
			NetworkManager::sInstance->test.front().Read(ID);
			//cout << ID << endl;
			for (int j = 0; j < players.size(); ++j){
				if (ID == players[j]->ID){
					players[j]->Read(NetworkManager::sInstance->test.front());
					players[j]->update();
					NetworkManager::sInstance->test.pop();
				}
			}
		}
	
	int var = 0;
	/*
	auto up = rotateTransform(arm, 0, 180);
	auto down = rotateTransform(arm, 180, 0);

	auto arcarm = moveEllipseArc(arm, 12, 14, 0, 4, -180, 360);
	auto arcbody = moveEllipseArc(armor, 0, 0, 5, 2, 0, -360);
	*/
	renderMan->zoom = 0.5;
	float size = 6;
	float ratio = 0.7;
	int armswing = size;
	int moveSpd = 1;
	int pressed = 0;
	int pressedTime = 3;
	int rotation = 0;
	while (gameloop) {
		input->update();
		if (numPlayers != 1)  NetworkManager::sInstance->UpdateDelay();

		//arm->rotation = var * 2;
		//base->posX += listen->input_x;
		//base->posY += listen->input_y;
		/*
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
		float loop = (var % length);*/

		sysInput.InputUpdate(GameObjects.alive_objects);
		sysRenderer.RenderUpdate(GameObjects.alive_objects);
		sysLogic.LogicUpdate(GameObjects.alive_objects);
		if (numPlayers != 1) sysNetwork.NetworkUpdate(GameObjects.alive_objects);
		sysPhysics.PhysicsUpdate(GameObjects.alive_objects);


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