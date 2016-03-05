#include "UIInputComponent.h"

UIInputComponent::UIInputComponent(){
}


UIInputComponent::~UIInputComponent(){
}

void UIInputComponent::Update(){

	InputManager* input = InputManager::getInstance();
	

	switch (uiObjectRef->ID){
	case PLAY_BUTTON:
		if (isButtonPressed(input)){
			std::cout << "Play Single!" << std::endl;
			uiObjectRef->visible = uiObjectRef->visible ? false : true;
		}
		
		break;
	case CANCEL_BUTTON:
		break;
	case BACK_BUTTON:
		break;
	case JOIN_BUTTON:
		if (isButtonPressed(input)){
			std::cout << "Join Lobby!" << std::endl;
		}
		break;
	case SCORE:
		break;
	case TIMER:
		break;
			
	}
}

bool UIInputComponent::isButtonPressed(InputManager* input){
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