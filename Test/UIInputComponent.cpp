#include "UIInputComponent.h"

UIInputComponent::UIInputComponent(){
}


UIInputComponent::~UIInputComponent(){
}

void UIInputComponent::Update(){	

	UIRenderComponent* rend = dynamic_cast<UIRenderComponent*>(uiObjectRef->GetComponent(COMPONENT_RENDER));

	uint64_t me = NetworkManager::sInstance->GetMyPlayerId();

	switch (uiObjectRef->ID){
	case PLAY_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_SinglePlayer);
		}
		break;
	case CANCEL_BUTTON:
		break;
	case BACK_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			std::cout << "Click!" << std::endl;
			//NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_MainMenu);
		}
		break;
	case JOIN_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			NetworkManager::sInstance->StartLobbySearch();
		}
		break;
	case READY_BUTTON:
		if (isButtonPressed(READY_BUTTON_WIDTH, READY_BUTTON_HEIGHT)){
			//std::cout << "click" << std::endl;
		}
		break;
	case INVITE_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			//std::cout << "click" << std::endl;
			GamerServices::sInstance->InviteFriendsFromOverlay();
		}
		break;
	case CHICKEN:
	case EAGLE:
	case TURKEY:
	case QUAIL:
	case FLAMINGO:
	case PEACOCK:
		if (isButtonPressed(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "click" << std::endl;
			uiObjectRef->ready = true;
		}
		if (isMouseHovering(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	case YELLOW_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			rend->ChangeSprite(YELLOW_BUTTON2);
			uiObjectRef->teamPicked = true;
		}
		if (isMouseHovering(BUTTON_WIDTH, BUTTON_HEIGHT)){
			rend->ChangeSprite(YELLOW_BUTTON2);
		}
		else{
			rend->ChangeSprite(YELLOW_BUTTON);
		}
		break;
	case PURPLE_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			rend->ChangeSprite(PURPLE_BUTTON2);
			uiObjectRef->teamPicked = true;
		}
		if (isMouseHovering(BUTTON_WIDTH, BUTTON_HEIGHT)){	
			rend->ChangeSprite(PURPLE_BUTTON2);
		}
		else{
			rend->ChangeSprite(PURPLE_BUTTON);
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