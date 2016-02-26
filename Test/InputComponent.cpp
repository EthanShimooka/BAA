#include "InputComponent.h"


InputComponent::InputComponent()
{
}


InputComponent::~InputComponent()
{
}


void InputComponent::Update(MovementComponent move) {
	//use the input manager to update the player
	//most of this function is prototype code

	InputManager* input = InputManager::getInstance();

	if (input->isKeyDown(KEY_RIGHT)) {
		move.posX += 2.0;

	}
	else if (input->isKeyDown(KEY_LEFT)) {
		move.posX += -2.0;

	}
	else if (input->isKeyDown(KEY_UP)) {
		move.posY += -2.0;

	}
	else if (input->isKeyDown(KEY_DOWN)) {
		move.posY += 2.0;
	}


}