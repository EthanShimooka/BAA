#include "lobby.h"

vector<player*> players;

Lobby::Lobby() : numPlayersReady(0){
	NetworkManager::sInstance->StartLobbySearch();
	numPlayers = NetworkManager::sInstance->GetPlayerCount();
	buttonID = 1;
	ready = false;
	selected = -1;
}


Lobby::~Lobby(){
}

int Lobby::runScene(){
	RenderManager::getRenderManager()->setBackground("Lobby_bg.png");

	// number of players in lobby
	createPlayerCount();

	// creating buttons
	createButtons();
	createClassButts();
	createSlots();

	
	while (true){
		updateLobby();
		checkButtons();
		changePlayerSelectionImage();
		// try to start the game if everyone is ready
		if (numPlayers == numPlayersReady) {
			NetworkManager::sInstance->TryReadyGame();
		}
		// start the game
		if (NetworkManager::sInstance->GetState() >= NetworkManager::NMS_Starting){
			removeAllButtons();
			SceneManager::GetSceneManager()->AssembleScene();
			return SCENE_GAME;
		}
	}
}

void Lobby::createButtons(){
	RenderManager* renderMan = RenderManager::getRenderManager();

	int w, h;
	float x, y;
	renderMan->getWindowSize(&w, &h);

	// ready button
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(7/8.0f)), (int)(h*(48/100.0f)));
	readyButt = bFactory.Spawn(buttonID++, x, y, 25, 75.0f, 75.0f, 0.75f);
	GameObjects.AddObject(readyButt);

	// back button 
}

void Lobby::createClassButts(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GameObject* button;

	int w, h;
	float midHeight, offset;
	float x, y;

	renderMan->getWindowSize(&w, &h);
	// height for the character class buttons
	midHeight = h * (1 / 2.0f);
	// finding the offset of the slots
	offset = w * (1 / 4.0f);

	// chicken button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 50, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("chickensfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
	// peacock button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 51, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("peacocksfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
	// flamingo button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 52, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("flamingosfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
	// quail button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 53, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("quailsfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
	// turkey button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 54, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("turkeysfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
}

int Lobby::checkButtons(){
	InputManager::getInstance()->update();
	for (size_t i = 0; i < classButt.size(); ++i){
		if (dynamic_cast<ButtonLogicComponent*>(classButt[i]->GetComponent(COMPONENT_LOGIC))->isButtonPressed()){
			int selection = dynamic_cast<ButtonRenderComponent*>(classButt[i]->GetComponent(COMPONENT_RENDER))->getCurrImage();
			playerSelection(selection);
			selected = selection;
			return static_cast<int>(i);
		}
	}
	if (selected && readyButt && dynamic_cast<ButtonLogicComponent*>(readyButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed()){
		ready = !ready;
		playerReady(ready);
		return BUTTON_READY;
	}
	return BUTTON_BACK;
}

void Lobby::playerSelection(int classType){
	NetworkManager::sInstance->SendSelectPacket(classType);
}

void Lobby::playerReady(int value){
	NetworkManager::sInstance->SendRdyUpPacket(value);
}

void Lobby::changePlayerSelectionImage(){
	if (NetworkManager::sInstance->lobbyUpdated()){
		
		if (numPlayers != NetworkManager::sInstance->GetPlayerCount()){
			numPlayers = NetworkManager::sInstance->GetPlayerCount();
			// send class and ready packet if someone joins the game
			playerSelection(selected);
			playerReady(ready);
		}
		unordered_map< uint64_t, PlayerInfo > lobby_m = NetworkManager::sInstance->getLobbyInfoMap();
		numPlayersReady = 0;
		int i = 0;
		for (const auto& iter : lobby_m){
			std::cout << iter.first << std::endl;
			if (iter.second.classType != -1) {
				dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->changeSprite(iter.second.classType + 5);
			}
			else {
				dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->setToDefault();
			}
			if (iter.second.ready){
				dynamic_cast<ButtonRenderComponent*>(readySlots[i]->GetComponent(COMPONENT_RENDER))->toggleSprites(2);
				++numPlayersReady;
			}
			else{
				dynamic_cast<ButtonRenderComponent*>(readySlots[i]->GetComponent(COMPONENT_RENDER))->toggleSprites(1);
			}
			++i;
		}
		setFreeSlotsToDefault(i);
	}
}

void Lobby::removeButtons(){
	//remove class buttons
	for (size_t i = 0; i < classButt.size(); ++i){ 
		GameObjects.DeleteObject(classButt[i]->ID);
	}
	//remove ready button
	GameObjects.DeleteObject(readyButt->ID);
	//remove back button
	GameObjects.DeleteObject(backButt->ID);
}

void Lobby::createSlots(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GameObject* slot, *readySlot;
	ButtonRenderComponent* br;
	int w, h;
	float topH, bottH, offset;
	float x, y;

	renderMan->getWindowSize(&w, &h);
	// height for the slots on the top half
	topH = h * (1 / 10.0f);
	// height for the slots on the bottom half
	bottH = h * (9 / 10.0f);
	// finding the offset of the slots
	offset = w * (1 / 6.0f);

	for (int i = 0; i < 8; ++i){
		if (i % 2){
			h = (int)bottH;
		}
		else {
			h = (int)topH;
			offset += w * (1 / 8.0f);
		}
		renderMan->windowCoordToWorldCoord(x, y, (int)offset, h);
		// ready slots
		readySlot = bFactory.Spawn(buttonID++, x, y, 28);
		br = dynamic_cast<ButtonRenderComponent*>(readySlot->GetComponent(COMPONENT_RENDER));
		br->addSecondSprite(30);
		readySlots.push_back(readySlot);
		GameObjects.AddObject(readySlot);
		// slots
		slot = bFactory.Spawn(buttonID++, x, y, 28);
		br = dynamic_cast<ButtonRenderComponent*>(slot->GetComponent(COMPONENT_RENDER));
		br->changeLayer("layer2");
		slots.push_back(slot);
		GameObjects.AddObject(slot);
	}
}

void Lobby::removeSlots(){
	for (unsigned i = 0; i < slots.size(); ++i){
		GameObjects.DeleteObject(slots[i]->ID);
	}
	for (unsigned i = 0; i < readySlots.size(); ++i){
		GameObjects.DeleteObject(readySlots[i]->ID);
	}
}

void Lobby::updateLobby(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GamerServices::sInstance->Update();
	NetworkManager::sInstance->ProcessIncomingPackets();
	if (playersInLobby)
		playersInLobby->setResourceObject(renderMan->renderText(std::to_string(numPlayers).c_str(), 255, 0, 0, 50, "VT323-Regular"));
	SceneManager::GetSceneManager()->AssembleScene();
}

void Lobby::createPlayerCount(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	playersInLobby = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	playersInLobby->setPos(0, 0);
}

void Lobby::removePlayerCount(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	if (playersInLobby){
		// this has to change later (removeObject doesn't work on text)
		playersInLobby->setVisible(false);
		sceneMan->RemoveObject(playersInLobby, sceneMan->findLayer("layer1"));
	}
}

void Lobby::removeAllButtons(){
	GameObjects.DeleteObjects();
}

void Lobby::setFreeSlotsToDefault(int firstSlot){
	for (unsigned i = firstSlot; i < readySlots.size(); ++i){
		dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->setToDefault();
		dynamic_cast<ButtonRenderComponent*>(readySlots[i]->GetComponent(COMPONENT_RENDER))->toggleSprites(1);
	}
}