#include "Controller.h"


Controller::Controller(){
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	if (joystick){
		joystickAnalogs.resize(SDL_JoystickNumAxes(joystick));
		joystickButtonHeld.resize(SDL_JoystickNumButtons(joystick));
		joystickButtonPressed.resize(SDL_JoystickNumButtons(joystick));
		joystickButtonReleased.resize(SDL_JoystickNumButtons(joystick));
		joystickDPad.resize(13);
		;
	}

}


Controller::~Controller(){}


bool Controller::isJoystickPressed(int b) {
	if (b < 0 || b >= joystickButtonPressed.size()-1) return false;
	return this->joystickButtonPressed[b];
}

bool Controller::isJoystickReleased(int b) {
	if (b < 0 || b >= joystickButtonReleased.size()-1) return false;
	return this->joystickButtonReleased[b];
}

bool Controller::isJoystickUp(int b) {
	if (b < 0 || b >= joystickButtonHeld.size()-1) return false;
	return !joystickButtonHeld[b];
}

bool Controller::isJoystickDown(int b) {
	if (b < 0 || b >= joystickButtonHeld.size()-1) return false;
	return this->joystickButtonHeld[b];
}

bool Controller::isDPadPressed(int pad){
	if (pad>joystickDPad.size() - 1)return false;
	return joystickDPad[pad];
}

double Controller::getLeftThumbX(){
	if (joystickAnalogs.size() < 1)return 0;
	return joystickAnalogs[0];
}
double Controller::getLeftThumbY(){
	if (joystickAnalogs.size() < 2)return 0;
	return joystickAnalogs[1];
}

double Controller::getRightThumbX(){
	if (joystickAnalogs.size() < 4)return 0;
	return joystickAnalogs[3];
}
double Controller::getRightThumbY(){
	if (joystickAnalogs.size() < 5)return 0;
	return joystickAnalogs[4];
}

double Controller::getLeftTrigger(){
	if (joystickAnalogs.size() < 3)return 0;
	return joystickAnalogs[2];
}
double Controller::getRightTrigger(){
	if (joystickAnalogs.size() < 6)return 0;
	return joystickAnalogs[5];
}

bool Controller::getLeftBumper(){
	return SDL_JoystickGetButton(joystick, JOYSTICK_LEFTSHOULDER);
}

// get  value of right trigger
bool Controller::getRightBumper(){
	return SDL_JoystickGetButton(joystick, JOYSTICK_RIGHTSHOULDER);
}

void Controller::update(){
	if (!joystick&&SDL_NumJoysticks()==1){
		//initialize controller
		joystick = SDL_JoystickOpen(0);
		if (joystick) joystickAnalogs.resize(SDL_JoystickNumAxes(joystick));

	}
	if (joystick&&SDL_NumJoysticks() == 0){
		//possible data loss. joystick is just a pointer, make sure
		//what it's referencing is actually freed
		joystick = NULL;
	}
}

void Controller::free(){
	SDL_JoystickClose(joystick);
	joystickAnalogs.clear();
	joystickButtonHeld.clear();
	joystickButtonPressed.clear();
	joystickButtonReleased.clear();
	joystickDPad.clear();
}