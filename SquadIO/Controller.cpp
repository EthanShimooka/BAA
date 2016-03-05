#include "Controller.h"


Controller::Controller(){
	joystickButtonHeld.resize(JOYSTICK_MAX);
	joystickButtonPressed.resize(JOYSTICK_MAX);
	joystickButtonReleased.resize(JOYSTICK_MAX);
	joystickAnalogs.resize(4);
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
}


Controller::~Controller(){}


bool Controller::isJoystickPressed(int b) {
	if (b < 0 || b >= JOYSTICK_MAX) return false;
	return this->joystickButtonPressed[b];
}

bool Controller::isJoystickReleased(int b) {
	if (b < 0 || b >= JOYSTICK_MAX) return false;
	return this->joystickButtonReleased[b];
}

bool Controller::isJoystickUp(int b) {
	if (b < 0 || b >= JOYSTICK_MAX) return false;
	return !joystickButtonHeld[b];
}

bool Controller::isJoystickDown(int b) {
	if (b < 0 || b >= JOYSTICK_MAX) return false;
	return this->joystickButtonHeld[b];
}

double Controller::getLeftThumbX(){
	return joystickAnalogs[0];
}
double Controller::getLeftThumbY(){
	return joystickAnalogs[1];
}

double Controller::getRightThumbX(){
	return 0;
}
double Controller::getRightThumbY(){
	return 0;
}

void Controller::update(){
	if (!joystick&&SDL_NumJoysticks()==1){
		joystick = SDL_JoystickOpen(0);
		std::cout << "Joystick plugged in" << std::endl;
	}
	if (joystick&&SDL_NumJoysticks() == 0){
		//possible data loss. joystick is just a pointer, make sure
		//what it's referencing is actually freed
		joystick = NULL;
		std::cout << "Joystick unplugged" << std::endl;
	}
}