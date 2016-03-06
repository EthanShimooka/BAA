// TODO:
// map other keys in inputmap.h
// read up on https://wiki.libsdl.org/CategoryGameController SDL's equivalent of xinput?

#pragma once
#include "include\InputManager.h"
// #include "LogManager.h"

using namespace std;
const int JOYSTICK_DEAD_ZONE = 6000;
InputManager* InputManager::inputInstance = nullptr;

// constructor
InputManager::InputManager() :keyboardState(nullptr), mouseState(0),
mouseX(0), mouseY(0), locked(false) {
	mouseDown.resize(MOUSE_SIZE);
	mouseUp.resize(MOUSE_SIZE);
	controller = new Controller();
};

InputManager* InputManager::getInstance() {
	// if InputManager is nullptr
	if (!inputInstance) {
		inputInstance = new InputManager();
	}
	return inputInstance;
}

// updates at every frame for new input
void InputManager::update() {
	controller->update();
	// reset mouse to neutral state, continue polling for up/down events
	for (int i = 0; i < MOUSE_SIZE; i++) {
		this->mouseDown[i] = 0;
		this->mouseUp[i] = 0;
	}
	for (int i = 0; i < JOYSTICK_MAX; i++) {
		controller->joystickButtonPressed[i] = false;
		controller->joystickButtonReleased[i] = false;
	}
	for (int i = 0; i < controller->joystickDPad.size()-1; i++){
		controller->joystickDPad[i] = false;
	}
	// poll for mouse events
	// http://wiki.libsdl.org/SDL_Event for case types
	//	int index;
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT:
			cout << "quit the game" << endl;
			break;
			// SDL_MouseButtonEvent
		case SDL_MOUSEBUTTONDOWN:
			if (ev.button.button == SDL_BUTTON_LEFT) {
				cout << "left" << endl;
				this->mouseDown[MOUSE_LEFT] = 1;
			}
			else if (ev.button.button == SDL_BUTTON_MIDDLE) {
				this->mouseDown[MOUSE_MIDDLE] = 1;
			}
			else if (ev.button.button == SDL_BUTTON_RIGHT) {
				this->mouseDown[MOUSE_RIGHT] = 1;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (ev.button.button == SDL_BUTTON_LEFT) {
				this->mouseUp[MOUSE_LEFT] = 1;
			}
			else if (ev.button.button == SDL_BUTTON_MIDDLE) {
				this->mouseUp[MOUSE_MIDDLE] = 1;
			}
			else if (ev.button.button == SDL_BUTTON_RIGHT) {
				this->mouseUp[MOUSE_RIGHT] = 1;
			}
			break;
			// SDL_MouseWheelEvent
		case SDL_MOUSEWHEEL:
			break;
			// SDL_MouseMotionEvent
		case SDL_MOUSEMOTION:
			// store mouse location
			this->mouseX = ev.motion.x;
			this->mouseY = ev.motion.y;
			break;
		case SDL_JOYBUTTONDOWN:
			controller->joystickButtonPressed[ev.jbutton.button] = true;
			controller->joystickButtonHeld[ev.jbutton.button] = true;
			break;
		case SDL_JOYBUTTONUP:
			controller->joystickButtonReleased[ev.jbutton.button] = true;
			controller->joystickButtonHeld[ev.jbutton.button] = false;
			break;
		case SDL_JOYAXISMOTION:
			//X axis motion
			if (ev.jaxis.axis == 0){
				//out of dead zone
				if (abs(ev.jaxis.value) > JOYSTICK_DEAD_ZONE){
					controller->joystickAnalogs[0] = ev.jaxis.value / 32767.0;
				}
				else controller->joystickAnalogs[0] = 0;
			}//Y axis motion
			
			for (int i = 0; i < SDL_JoystickNumAxes(controller->joystick); i++){
				if (ev.jaxis.axis == i){
					//Below of dead zone
					if (abs(ev.jaxis.value) > JOYSTICK_DEAD_ZONE){
						controller->joystickAnalogs[i] = ev.jaxis.value / 32767.0;
					}
					else controller->joystickAnalogs[i] = 0;
				}
			}

			break;
		case SDL_JOYHATMOTION:  /* Handle DPAD Input */
			if (ev.jhat.value == JOYSTICK_DPAD_UP)controller->joystickDPad[JOYSTICK_DPAD_UP]=true;
			if (ev.jhat.value == JOYSTICK_DPAD_RIGHTUP)controller->joystickDPad[JOYSTICK_DPAD_RIGHTUP] = true;
			if (ev.jhat.value == JOYSTICK_DPAD_RIGHT)controller->joystickDPad[JOYSTICK_DPAD_RIGHT] = true;
			if (ev.jhat.value == JOYSTICK_DPAD_RIGHTDOWN)controller->joystickDPad[JOYSTICK_DPAD_RIGHTDOWN] = true;
			if (ev.jhat.value == JOYSTICK_DPAD_DOWN)controller->joystickDPad[JOYSTICK_DPAD_DOWN] = true;
			if (ev.jhat.value == JOYSTICK_DPAD_LEFTDOWN)controller->joystickDPad[JOYSTICK_DPAD_LEFTDOWN] = true;
			if (ev.jhat.value == JOYSTICK_DPAD_LEFT)controller->joystickDPad[JOYSTICK_DPAD_LEFT] = true;
			if (ev.jhat.value == JOYSTICK_DPAD_LEFTUP)controller->joystickDPad[JOYSTICK_DPAD_LEFTUP] = true;
			break;
		default:
			break;
		}
	}
	keyboardState = SDL_GetKeyboardState(nullptr);
}

// return true if keydown
bool InputManager::isKeyDown(int key) {
	if (this->locked) {
		return false;
	}
	if (key < 0 || key >= KEYBOARD_SIZE) {
		return false;
	}
	return this->keyboardState[key] ? true : false;
}

// return true if keyup
bool InputManager::isKeyUp(int key) {
	if (this->locked) {
		return false;
	}
	if (key < 0 || key >= KEYBOARD_SIZE) {
		return false;
	}
	return this->keyboardState[key] ? true : false;
}

// return true if mousedown
bool InputManager::isMouseDown(int b) {
	if (this->locked) {
		return false;
	}
	if (b < 0 || b >= MOUSE_SIZE) {
		return false;
	}
	return this->mouseDown[b] ? true : false;
}

// return true if mouseup
bool InputManager::isMouseUp(int b) {
	if (this->locked) {
		return false;
	}
	if (b < 0 || b >= MOUSE_SIZE) {
		return false;
	}
	return this->mouseUp[b] ? true : false;
}

int InputManager::getMouseX() {
	return this->mouseX;
}

int InputManager::getMouseY() {
	return this->mouseY;
}

void InputManager::lock() {
	this->locked = true;
}

void InputManager::unlock() {
	this->locked = false;
}


