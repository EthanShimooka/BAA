#include "UIInputComponent.h"

UIInputComponent::UIInputComponent(){
}


UIInputComponent::~UIInputComponent(){
}

void UIInputComponent::Update(){	

	switch (uiObjectRef->ID){
	case PLAY_BUTTON:
		if (isButtonPressed()){
			std::cout << "Play!" << std::endl;
			NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_SinglePlayer);
		}
		else if (isMouseHovering()){
			std::cout << "Hovering!" << std::endl;
		}
		break;
	case CANCEL_BUTTON:
		break;
	case BACK_BUTTON:
		break;
	case JOIN_BUTTON:
		if (isButtonPressed()){
			std::cout << "Join!" << std::endl;
			NetworkManager::sInstance->startLobbySearch();
			while (NetworkManager::sInstance->GetState() != NetworkManager::sInstance->NMS_Lobby){
				GamerServices::sInstance->Update();
			}
		}
		else if (isMouseHovering()){
			uiObjectRef->scale = .5f;
			std::cout << "Hovering!" << std::endl;
		}
		break;
	case SCORE:
		break;
	case TIMER:
		break;
			
	}
}

bool UIInputComponent::isButtonPressed(){

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
		else if (x > uiObjectRef->posX + BUTTON_WIDTH)
			return false;
		//mouse above the button
		else if (y < uiObjectRef->posY)
			return false;
		//mouse below the button
		else if (y > uiObjectRef->posY + BUTTON_HEIGHT)
			return false;
		else{
			return true;
		}
	}
}

bool UIInputComponent::isMouseHovering(){

	InputManager* input = InputManager::getInstance();

	int x, y;
	x = input->getMouseX();
	y = input->getMouseY();

	if (x < uiObjectRef->posX)
		return false;
	//mouse is right of the button
	else if (x > uiObjectRef->posX + BUTTON_WIDTH)
		return false;
	//mouse above the button
	else if (y < uiObjectRef->posY)
		return false;
	//mouse below the button
	else if (y > uiObjectRef->posY + BUTTON_HEIGHT)
		return false;
	else{
		return true;
	}
}