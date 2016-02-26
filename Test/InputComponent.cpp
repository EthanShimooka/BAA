#include "InputComponent.h"


InputComponent::InputComponent()
{
}


InputComponent::~InputComponent()
{
}


void InputComponent::Update() {
	//use the input manager to update the player
	//most of this function is prototype code

	InputManager* input = InputManager::getInstance();

	if (input->isKeyDown(KEY_RIGHT)) {
		gameObjectRef->posX += 2.0;

	}
	else if (input->isKeyDown(KEY_LEFT)) {
		gameObjectRef->posX += -2.0;

	}
	else if (input->isKeyDown(KEY_UP)) {
		gameObjectRef->posY += -2.0;

	}
	else if (input->isKeyDown(KEY_DOWN)) {
		gameObjectRef->posY += 2.0;
	}


}