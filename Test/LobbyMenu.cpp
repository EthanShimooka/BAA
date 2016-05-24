#include "LobbyMenu.h"

LobbyMenu::LobbyMenu() : numPlayersReady(0){
	NetworkManager::sInstance->StartLobbySearch();
	numPlayers = NetworkManager::sInstance->GetPlayerCount();
	buttonID = 1;
	tutorialID = 100;
	ready = false;
	selected = -1;

	RenderManager::getRenderManager()->setBackground("Lobby_bg.png");

	// number of players in lobby
	createPlayerCount();

	// creating buttons
	createButtons();
	createClassButts();
	createSlots();
	SceneManager::GetSceneManager()->AssembleScene();
}


LobbyMenu::~LobbyMenu(){
	removeAllButtons();
	removePlayerCount();
	SceneManager::GetSceneManager()->AssembleScene();
}

int LobbyMenu::runScene(){
	int buttonPressed = -2;

	while (true){
		updateLobby();
		buttonPressed = checkButtons();
		changePlayerSelectionImage();


		// back button is pressed
		if (buttonPressed == BUTTON_BACK){
			return SCENE_GAMEOVER;
		}

		// try to start the game if everyone is ready
		if (numPlayers == numPlayersReady) {
			NetworkManager::sInstance->TryReadyGame();
		}

		// start the game
		if (NetworkManager::sInstance->GetState() >= NetworkManager::NMS_Starting){
			return SCENE_GAME;
		}
	}
}

void LobbyMenu::createButtons(){
	RenderManager* renderMan = RenderManager::getRenderManager();

	int w, h;
	float x, y;
	renderMan->getWindowSize(&w, &h);

	// ready button
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(7 / 8.0)), (int)(h*(48 / 100.0)));
	readyButt = bFactory.Spawn(buttonID++, x, y, 25, 75.0f, 75.0f, 0.75f);
	GameObjects.AddObject(readyButt);

	// back button 
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(7 / 8.0)), (int)(h*(90 / 100.0)));
	backButt = bFactory.Spawn(buttonID++, x, y, 23, 75.0f, 75.0f, 0.75f);
	GameObjects.AddObject(backButt);
}

void LobbyMenu::createClassButts(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GameObject* button;
	GameObject* tutorial;

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
		// chicken tutorial
	tutorial = tFactory.Spawn(tutorialID++, 50, x, y - 70);
	tutorials.push_back(tutorial);
	// peacock button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 51, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("peacocksfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
		// peacock tutorial
	tutorial = tFactory.Spawn(tutorialID++, 51, x, y - 70);
	tutorials.push_back(tutorial);
	// flamingo button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 52, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("flamingosfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
		// flamingo tutorial
	tutorial = tFactory.Spawn(tutorialID++, 52, x, y - 70);
	tutorials.push_back(tutorial);
	// quail button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 53, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("quailsfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
		// quail tutorial
	tutorial = tFactory.Spawn(tutorialID++, 53, x, y - 70);
	tutorials.push_back(tutorial);
	// turkey button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	button = bFactory.Spawn(buttonID++, x, y, 54, 75.0f, 75.0f, 0.75f);
	dynamic_cast<ButtonLogicComponent*>(button->GetComponent(COMPONENT_LOGIC))->setSound("turkeysfx.ogg");
	classButt.push_back(button);
	GameObjects.AddObject(button);
	offset += w * (1 / 9.0f);
		// turkey tutorial
	tutorial = tFactory.Spawn(tutorialID++, 54, x, y - 70);
	tutorials.push_back(tutorial);
}

int LobbyMenu::checkButtons(){
	InputManager::getInstance()->update();
	for (size_t i = 0; i < classButt.size(); ++i){
		// if pressed 
		if (dynamic_cast<ButtonLogicComponent*>(classButt[i]->GetComponent(COMPONENT_LOGIC))->isButtonPressed()){
			int selection = dynamic_cast<ButtonRenderComponent*>(classButt[i]->GetComponent(COMPONENT_RENDER))->getCurrImage();
			playerSelection(selection);
			selected = selection;
			return i+10;
		}
		// if hovering over show images of the tutorials
		if (dynamic_cast<ButtonLogicComponent*>(classButt[i]->GetComponent(COMPONENT_LOGIC))->isMouseHovering()){
			dynamic_cast<TutorialRenderComponent*>(tutorials[i]->GetComponent(COMPONENT_RENDER))->toggleImage(true);
		}
		else {
			dynamic_cast<TutorialRenderComponent*>(tutorials[i]->GetComponent(COMPONENT_RENDER))->toggleImage(false);
		}
	}
	if (selected != -1 && readyButt && dynamic_cast<ButtonLogicComponent*>(readyButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed()){
		ready = !ready;
		AudioManager* audioMan = AudioManager::getAudioInstance();
		audioMan->playByName("readyupsfx.ogg");
		playerReady(ready);
		return BUTTON_READY;
	}
	if (dynamic_cast<ButtonLogicComponent*>(backButt->GetComponent(COMPONENT_LOGIC))->isButtonPressed()){
		return BUTTON_BACK;
	}
	return BUTTON_NONE;
}

void LobbyMenu::playerSelection(int classType){
	NetworkManager::sInstance->SendSelectPacket(classType);
}

void LobbyMenu::playerReady(int value){
	NetworkManager::sInstance->SendRdyUpPacket(value);
}

void LobbyMenu::changePlayerSelectionImage(){
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

void LobbyMenu::removeButtons(){
	//remove class buttons
	for (size_t i = 0; i < classButt.size(); ++i){
		GameObjects.DeleteObject(classButt[i]->ID);
	}
	//remove ready button
	GameObjects.DeleteObject(readyButt->ID);
}

void LobbyMenu::createSlots(){
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

void LobbyMenu::removeSlots(){
	for (size_t i = 0; i < slots.size(); ++i){
		GameObjects.DeleteObject(slots[i]->ID);
	}
	for (size_t i = 0; i < readySlots.size(); ++i){
		GameObjects.DeleteObject(readySlots[i]->ID);
	}
}

void LobbyMenu::updateLobby(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GamerServices::sInstance->Update();
	NetworkManager::sInstance->ProcessIncomingPackets();
	if (playersInLobby)
		playersInLobby->setResourceObject(renderMan->renderText(std::to_string(numPlayers).c_str(), 255, 0, 0, 50, "VT323-Regular"));
	SceneManager::GetSceneManager()->AssembleScene();
}

void LobbyMenu::createPlayerCount(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	playersInLobby = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 5, 0, true);
	playersInLobby->setPos(0, 0);
}

void LobbyMenu::removePlayerCount(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	if (playersInLobby){
		// this has to change later (removeObject doesn't work on text)
		playersInLobby->setVisible(false);
		sceneMan->RemoveObject(playersInLobby, sceneMan->findLayer("layer1"));
	}
}

void LobbyMenu::removeAllButtons(){
	GameObjects.DeleteObjects();
}

void LobbyMenu::setFreeSlotsToDefault(int firstSlot){
	for (size_t i = firstSlot; i < readySlots.size(); ++i){
		dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->setToDefault();
		dynamic_cast<ButtonRenderComponent*>(readySlots[i]->GetComponent(COMPONENT_RENDER))->toggleSprites(1);
	}
}