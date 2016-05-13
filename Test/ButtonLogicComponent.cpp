#include "ButtonLogicComponent.h"


ButtonLogicComponent::ButtonLogicComponent(GameObject* button, int _width, int _height, std::string _sound)
{
	gameObjectRef = button;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	input = InputManager::getInstance();
	width = _width;
	height = _height;
	sound = _sound;
}


ButtonLogicComponent::~ButtonLogicComponent()
{
}

void ButtonLogicComponent::Update(){
	AudioManager* audioMan = AudioManager::getAudioInstance();
	if (isButtonPressed()){
		if (sound != "")
			audioMan->playByName(sound);

		switch (gameObjectRef->ID){
		case _PLAY_BUTTON:
			NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_SinglePlayer);
			break;
		case _CANCEL_BUTTON:
			break;
		case _BACK_BUTTON:
			break;
		case _JOIN_BUTTON:
			NetworkManager::sInstance->StartLobbySearch();
			break;
		case _READY_BUTTON:
			break;
		case _INVITE_BUTTON:
			GamerServices::sInstance->InviteFriendsFromOverlay();
			break;
		}
	}

	//case CHICKEN:
	//	if (isButtonPressed()){
	//		//std::cout << "click" << std::endl;
	//		
	//		audioMan->playByName(sound);
	//		uiObjectRef->ready = true;
	//	}
	//	if (isMouseHovering()){
	//		//std::cout << "hovering" << std::endl;
	//		uiObjectRef->hoverPicture = true;
	//	}
	//	else{
	//		uiObjectRef->hoverPicture = false;
	//	}
	//	break;
	//case EAGLE:
	//case TURKEY:
	//	if (isButtonPressed()){
	//		//std::cout << "click" << std::endl;
	//		AudioManager* audioMan = AudioManager::getAudioInstance();
	//		audioMan->playByName("turkeysfx.ogg");
	//		uiObjectRef->ready = true;
	//	}
	//	if (isMouseHovering()){
	//		//std::cout << "hovering" << std::endl;
	//		uiObjectRef->hoverPicture = true;
	//	}
	//	else{
	//		uiObjectRef->hoverPicture = false;
	//	}
	//	break;
	//case QUAIL:
	//	if (isButtonPressed()){
	//		//std::cout << "click" << std::endl;
	//		AudioManager* audioMan = AudioManager::getAudioInstance();
	//		audioMan->playByName("quailsfx.ogg");
	//		uiObjectRef->ready = true;
	//	}
	//	if (isMouseHovering()){
	//		//std::cout << "hovering" << std::endl;
	//		uiObjectRef->hoverPicture = true;
	//	}
	//	else{
	//		uiObjectRef->hoverPicture = false;
	//	}
	//	break;
	//case FLAMINGO:
	//	if (isButtonPressed()){
	//		//std::cout << "click" << std::endl;
	//		AudioManager* audioMan = AudioManager::getAudioInstance();
	//		audioMan->playByName("flamingosfx.ogg");
	//		uiObjectRef->ready = true;
	//	}
	//	if (isMouseHovering()){
	//		//std::cout << "hovering" << std::endl;
	//		uiObjectRef->hoverPicture = true;
	//	}
	//	else{
	//		uiObjectRef->hoverPicture = false;
	//	}
	//	break;
	//case PEACOCK:
	//	if (isButtonPressed()){
	//		//std::cout << "click" << std::endl;
	//		AudioManager* audioMan = AudioManager::getAudioInstance();
	//		audioMan->playByName("peacocksfx.ogg");
	//		uiObjectRef->ready = true;
	//	}
	//	if (isMouseHovering()){
	//		//std::cout << "hovering" << std::endl;
	//		uiObjectRef->hoverPicture = true;
	//	}
	//	else{
	//		uiObjectRef->hoverPicture = false;
	//	}
	//	break;
	//}
}

bool ButtonLogicComponent::isButtonPressed(){
	if (input->isMouseDown(MOUSE_LEFT)){
		//get mouse position
		int x, y;
		x = input->getMouseX();
		y = input->getMouseY();

		// returns true if mouse within bounds
		if (x <= gameObjectRef->posX && x + width >= gameObjectRef->posX && y <= gameObjectRef->posY && y + height >= gameObjectRef->posY)
			return true;
		return false;
	}
}

bool ButtonLogicComponent::isMouseHovering(){
	int x, y;
	x = input->getMouseX();
	y = input->getMouseY();

	if (x <= gameObjectRef->posX && x + width >= gameObjectRef->posX && y <= gameObjectRef->posY && y + height >= gameObjectRef->posY)
		return true;
	return false;
}