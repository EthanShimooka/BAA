#include "InputListener.h"

void InputListener::getInput(){
	InputManager* input = InputManager::getInstance();

	if (input->isKeyDown(KEY_RIGHT)) {
		input_x = 2.0;

	}	else if (input->isKeyDown(KEY_LEFT)) {
		input_x = -2.0;

	}	else if (input->isKeyDown(KEY_UP)) {
		input_y = -2.0;

	}	else if (input->isKeyDown(KEY_DOWN)) {
		input_y = 2.0;

	} 
	
	else{
		input_x = 0.0;
		input_y = 0.0;

     }
}

