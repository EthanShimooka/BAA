#include "UIInputComponent.h"

UIInputComponent::UIInputComponent(){
}


UIInputComponent::~UIInputComponent(){
}

void UIInputComponent::Update(){

	InputManager* input = InputManager::getInstance();

	if (uiObjectRef->ID == UIType::BUTTON){
		if (input->isMouseDown(MouseButton::MOUSE_LEFT)){
			//get mouse position
			int x, y;
			x = input->getMouseX();
			y = input->getMouseY();
			bool inside = true;

			//mouse is left of button
			if (x < uiObjectRef->posX)
				inside = false;
			//mouse is right of the button
			else if (x > uiObjectRef->posX + BUTTON_WIDTH)
				inside = false;
			//mouse above the button
			else if (y < uiObjectRef->posY)
				inside = false;
			//mouse below the button
			else if (y > uiObjectRef->posY + BUTTON_HEIGHT){
				inside = false;
			}

			if (inside){
				std::cout << "Click!" << std::endl;
			}
		}
	}
}