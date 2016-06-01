#include "LobbyMenu.h"

LobbyMenu::LobbyMenu() : numPlayersReady(0){
	RenderManager::getRenderManager()->setCameraPoint(0, 0);
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
	SystemRenderUpdater sysRenderer;
	SystemLogicUpdater sysLogic;
	while (true){
		updateLobby();
		buttonPressed = checkButtons();
		changePlayerSelectionImage();


		// back button is pressed
		if (buttonPressed == BUTTON_BACK){
			GamerServices::sInstance->LeaveLobby(NetworkManager::sInstance->GetLobbyId());
			return SCENE_MENU;
		}

		// try to start the game if everyone is ready
		if (numPlayers == numPlayersReady) {
			NetworkManager::sInstance->TryReadyGame();
		}

		// start the game
		if (NetworkManager::sInstance->GetState() >= NetworkManager::NMS_Starting){
			return SCENE_GAME;
		}
		sysRenderer.RenderUpdate(GameObjects.alive_objects);
		sysLogic.LogicUpdate(GameObjects.alive_objects);
	}
}

void LobbyMenu::createButtons(){
	RenderManager* renderMan = RenderManager::getRenderManager();

	int w, h;
	float x, y;
	renderMan->getWindowSize(&w, &h);

	// ready button
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(0.9f)), (int)(h*(90 / 100.0)));
	readyButt = bFactory.Spawn(buttonID++, x, y, 25, 75.0f, 75.0f, 0.30f,BUTTON_ICON);
	ButtonRenderComponent* readyRender = dynamic_cast<ButtonRenderComponent*>(readyButt->GetComponent(COMPONENT_RENDER));
	readyRender->addSecondSprite(34);
	
	GameObjects.AddObject(readyButt);

	// back button 
	renderMan->windowCoordToWorldCoord(x, y, (int)(w*(0.1f)), (int)(h*(90 / 100.0)));
	backButt = bFactory.Spawn(buttonID++, x, y, 23, 75.0f, 75.0f, 0.30f);

	ButtonRenderComponent*backRender = dynamic_cast<ButtonRenderComponent*>(backButt->GetComponent(COMPONENT_RENDER));
	backRender->addSecondSprite(33);
	GameObjects.AddObject(backButt);
}

void LobbyMenu::createClassButts(){
	RenderManager* renderMan = RenderManager::getRenderManager();
	GameObject* tutorial;

	int w, h;
	float midHeight, offset;
	float x, y;

	renderMan->getWindowSize(&w, &h);
	// height for the character class buttons
	midHeight = h * (1 / 1.5f);
	// finding the offset of the slots
	offset = w * (1 / 14.0f);

	// chicken button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);

	GameObject* chickButton = bFactory.Spawn(buttonID++, x, y + 10, 9150, 50.0f, 50.0f, 0.30f);
	ButtonLogicComponent* chickLogic = dynamic_cast<ButtonLogicComponent*>(chickButton->GetComponent(COMPONENT_LOGIC));
	ButtonRenderComponent* chickRender = dynamic_cast<ButtonRenderComponent*>(chickButton->GetComponent(COMPONENT_RENDER));
	chickRender->addSecondSprite(27);
	chickLogic->setSound("chickensfx.ogg");
	classButt.push_back(chickButton);
	GameObjects.AddObject(chickButton);
	offset += w * (1 / 12.0f);

		// chicken tutorial
	tutorial = tFactory.Spawn(tutorialID++, 9150, 80, 0);
	tutorials.push_back(tutorial);

	// peacock button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);

	GameObject* peaButton = bFactory.Spawn(buttonID++, x, y, 9151, 50.0f, 50.0f, 0.5);
	ButtonLogicComponent* peaLogic = dynamic_cast<ButtonLogicComponent*>(peaButton->GetComponent(COMPONENT_LOGIC));
	ButtonRenderComponent* peaRender = dynamic_cast<ButtonRenderComponent*>(peaButton->GetComponent(COMPONENT_RENDER));
	peaRender->addSecondSprite(27);
	peaLogic->setSound("peacocksfx.ogg");
	classButt.push_back(peaButton);
	GameObjects.AddObject(peaButton);
	offset += w * (1 / 11.0f);

		// peacock tutorial
	tutorial = tFactory.Spawn(tutorialID++, 9151,80, 0);
	tutorials.push_back(tutorial);

	// flamingo button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);
	GameObject* flamButton = bFactory.Spawn(buttonID++, x, y - 70, 9152, 59.0f, 59.0f, 0.4f);
	ButtonLogicComponent* flamLogic = dynamic_cast<ButtonLogicComponent*>(flamButton->GetComponent(COMPONENT_LOGIC));
	ButtonRenderComponent* flamRender = dynamic_cast<ButtonRenderComponent*>(flamButton->GetComponent(COMPONENT_RENDER));
	flamRender->addSecondSprite(27);
	flamLogic->setSound("flamingosfx.ogg");
	classButt.push_back(flamButton);
	GameObjects.AddObject(flamButton);
	offset += w * (1 / 12.0f);


		// flamingo tutorial
	tutorial = tFactory.Spawn(tutorialID++, 9152, 80, 0);
	tutorials.push_back(tutorial);

	// quail button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);

	GameObject* quaButton = bFactory.Spawn(buttonID++, x, y + 20, 9153, 50.0f, 50.0f, 0.3f);
	ButtonLogicComponent* quaLogic = dynamic_cast<ButtonLogicComponent*>(quaButton->GetComponent(COMPONENT_LOGIC));
	ButtonRenderComponent* quaRender = dynamic_cast<ButtonRenderComponent*>(quaButton->GetComponent(COMPONENT_RENDER));
	quaRender->addSecondSprite(27);
	quaLogic->setSound("quailsfx.ogg");
	classButt.push_back(quaButton);
	GameObjects.AddObject(quaButton);
	offset += w * (1 / 8.0f);

		// quail tutorial
	tutorial = tFactory.Spawn(tutorialID++, 9153, 80, 0);
	tutorials.push_back(tutorial);

	// turkey button
	renderMan->windowCoordToWorldCoord(x, y, (int)offset, (int)midHeight);

	GameObject* turkButton = bFactory.Spawn(buttonID++, x, y, 9154, 50.0f, 50.0f, 0.6f);
	ButtonLogicComponent* turkLogic = dynamic_cast<ButtonLogicComponent*>(turkButton->GetComponent(COMPONENT_LOGIC));
	ButtonRenderComponent* turkRender = dynamic_cast<ButtonRenderComponent*>(turkButton->GetComponent(COMPONENT_RENDER));
	turkRender->addSecondSprite(27);
	turkLogic->setSound("turkeysfx.ogg");
	classButt.push_back(turkButton);
	GameObjects.AddObject(turkButton);
	offset += w * (1 / 11.0f);

		// turkey tutorial
	tutorial = tFactory.Spawn(tutorialID++, 9154, 80, 0);
	tutorials.push_back(tutorial);


	//Now assing all the controller mapping stuff
	chickLogic->setNavButtons(NULL, backButt, NULL, peaButton);
	peaLogic->setNavButtons(flamButton, backButt, chickButton, flamButton);
	flamLogic->setNavButtons(NULL, backButt, peaButton, quaButton);
	quaLogic->setNavButtons(flamButton, backButt, flamButton, turkButton);
	turkLogic->setNavButtons(NULL, backButt, quaButton, readyButt);
	ButtonLogicComponent* readyLogic = dynamic_cast<ButtonLogicComponent*>(readyButt->GetComponent(COMPONENT_LOGIC));
	readyLogic->setNavButtons(turkButton, backButt, NULL, NULL);
	readyLogic->selectButton();
	ButtonLogicComponent* backLogic = dynamic_cast<ButtonLogicComponent*>(backButt->GetComponent(COMPONENT_LOGIC));
	backLogic->setNavButtons(readyButt, NULL, turkButton, NULL);

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


//TODO: fix placeholders



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
				dynamic_cast<ButtonRenderComponent*>(slots[i]->GetComponent(COMPONENT_RENDER))->changeSprite(iter.second.classType + 100);
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
		sceneMan->RemoveObject(playersInLobby);
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