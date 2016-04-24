#include "Controller.h"


Controller::Controller(){
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_Init(SDL_INIT_HAPTIC);
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	if (joystick){
		joystickAnalogs.resize(SDL_JoystickNumAxes(joystick));
		joystickButtonHeld.resize(SDL_JoystickNumButtons(joystick));
		joystickButtonPressed.resize(SDL_JoystickNumButtons(joystick));
		joystickButtonReleased.resize(SDL_JoystickNumButtons(joystick));
		joystickDPad.resize(13);
		haptic = SDL_HapticOpenFromJoystick(joystick);
		if (SDL_HapticRumbleSupported(haptic) == SDL_TRUE){
			SDL_HapticRumbleInit(haptic);
			rumbleSupport = true;
		}
		else rumbleSupport = false;
	}
	
}


Controller::~Controller(){}

bool Controller::isControllerOn(){
	return joystick ? true : false;
}


bool Controller::isJoystickPressed(int b) {
	if (b < 0 || (unsigned int)b >= joystickButtonPressed.size()-1||!joystick) return false;
	return this->joystickButtonPressed[b];
}

bool Controller::isJoystickReleased(int b) {
	if (b < 0 || (unsigned int)b >= joystickButtonReleased.size() - 1 || !joystick) return false;
	return this->joystickButtonReleased[b];
}

bool Controller::isJoystickUp(int b) {
	if (b < 0 || (unsigned int)b >= joystickButtonHeld.size() - 1 || !joystick) return false;
	return !joystickButtonHeld[b];
}

bool Controller::isJoystickDown(int b) {
	if (b < 0 || (unsigned int)b >= joystickButtonHeld.size() - 1 || !joystick) return false;
	return this->joystickButtonHeld[b];
}

bool Controller::isDPadPressed(int pad){
	if ((unsigned int)pad>joystickDPad.size() - 1 || !joystick)return false;
	return joystickDPad[pad];
}

double Controller::getLeftThumbX(){
	if (joystickAnalogs.size() < 1 || !joystick)return 0;
	return joystickAnalogs[0];
}
double Controller::getLeftThumbY(){
	if (joystickAnalogs.size() < 2 || !joystick)return 0;
	return joystickAnalogs[1];
}

double Controller::getRightThumbX(){
	if (joystickAnalogs.size() < 4 || !joystick)return 0;
	return joystickAnalogs[3];
}
double Controller::getRightThumbY(){
	if (joystickAnalogs.size() < 5 || !joystick)return 0;
	return joystickAnalogs[4];
}

double Controller::getLeftTrigger(){
	if (joystickAnalogs.size() < 3 || !joystick)return 0;
	return joystickAnalogs[2];
}
double Controller::getRightTrigger(){
	if (joystickAnalogs.size() < 6 || !joystick)return 0;
	return joystickAnalogs[5];
}

bool Controller::getLeftBumper(){
	if (!joystick)return false;
	return SDL_JoystickGetButton(joystick, JOYSTICK_LEFTSHOULDER)?true:false;
}

// get  value of right trigger
bool Controller::getRightBumper(){
	if (!joystick)return false;
	return SDL_JoystickGetButton(joystick, JOYSTICK_RIGHTSHOULDER)?true:false;
}

double Controller::getRightTriggerDuration(){
	if (getRightTrigger() < 0.75)return 0;
	return (clock() - rightTriggerHoldClock) / (CLOCKS_PER_SEC / 1000);
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
	if (getRightTrigger() > 0.75&&lastRightTriggerValue < 0.75){
		rightTriggerHoldClock = clock();
	}
	lastRightTriggerValue= getRightTrigger();
}

void Controller::rumble(float strength, int duration){
	//Strength parameter is a float between 0 and 1 to determine how strong
	//the vibration is. Duration is time in milliseconds to vibrate controller.
	if (rumbleSupport)SDL_HapticRumblePlay(haptic, strength, duration);
	else std::cout << "rumble not supported" << std::endl;
}

void Controller::free(){
	SDL_JoystickClose(joystick);
	joystickAnalogs.clear();
	joystickButtonHeld.clear();
	joystickButtonPressed.clear();
	joystickButtonReleased.clear();
	joystickDPad.clear();
	if (haptic){
		SDL_HapticClose(haptic);
	}
}