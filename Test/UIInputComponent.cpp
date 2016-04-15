#include "UIInputComponent.h"

UIInputComponent::UIInputComponent(){
}


UIInputComponent::~UIInputComponent(){
}

void UIInputComponent::Update(){	

	uint64_t me = NetworkManager::sInstance->GetMyPlayerId();
	switch (uiObjectRef->ID){
	case PLAY_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			std::cout << "Play!" << std::endl;
			NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_SinglePlayer);
		}
		break;
	case CANCEL_BUTTON:
		break;
	case BACK_BUTTON:
		break;
	case JOIN_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			std::cout << "Join!" << std::endl;
			NetworkManager::sInstance->StartLobbySearch();
		}
		break;
	case SCORE:
		break;
	case TIMER:
		break;
	case READY_BUTTON:
		if (isButtonPressed(READY_BUTTON_WIDTH, READY_BUTTON_HEIGHT)){
			//std::cout << "click" << std::endl;
		}
		break;
	case CHICKEN:
		if (isButtonPressed(66, 67)){
			std::cout << "click" << std::endl;
			uiObjectRef->ready = true;
			
		}
		if (isMouseHovering(66, 67)){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	case PEACOCK:
		if (isButtonPressed(66, 67)){
			std::cout << "click" << std::endl;
			uiObjectRef->ready = true;

		}
		if (isMouseHovering(66, 67)){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	}
}

bool UIInputComponent::isButtonPressed(int width, int height){

	InputManager* input = InputManager::getInstance();
	if (input->isMouseDown(MOUSE_LEFT)){
		//get mouse position
		int x, y;
		x = input->getMouseX();
		y = input->getMouseY();

		//mouse is left of button
		if (x < uiObjectRef->posX)
			return false;
		//mouse is right of the button
		else if (x > uiObjectRef->posX + width)
			return false;
		//mouse above the button
		else if (y < uiObjectRef->posY)
			return false;
		//mouse below the button
		else if (y > uiObjectRef->posY + height)
			return false;
		else{
			return true;
		}
	}
	return false;
}

bool UIInputComponent::isMouseHovering(int width, int height){

	InputManager* input = InputManager::getInstance();

	int x, y;
	x = input->getMouseX();
	y = input->getMouseY();

	if (x < uiObjectRef->posX)
		return false;
	//mouse is right of the button
	else if (x > uiObjectRef->posX + width)
		return false;
	//mouse above the button
	else if (y < uiObjectRef->posY)
		return false;
	//mouse below the button
	else if (y > uiObjectRef->posY + height)
		return false;
	else{
		return true;
	}
}