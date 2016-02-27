// TODO:
// map other keys in inputmap.h
// read up on https://wiki.libsdl.org/CategoryGameController SDL's equivalent of xinput?

#pragma once
#include "include\InputManager.h"
// #include "LogManager.h"

using namespace std;

InputManager* InputManager::inputInstance = nullptr;

// constructor
InputManager::InputManager() :keyboardState(nullptr), mouseState(0),
	mouseX(0), mouseY(0), locked(false) {
	mouseDown.resize(MOUSE_SIZE);
	mouseUp.resize(MOUSE_SIZE);
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
	// reset mouse to neutral state, continue polling for up/down events
	for (int i = 0; i < MOUSE_SIZE; i++) {
		this->mouseDown[i] = 0;
		this->mouseUp[i] = 0;
	}
	// poll for mouse events
	// http://wiki.libsdl.org/SDL_Event for case types
//	int index;
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			// SDL_MouseButtonEvent
			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button == SDL_BUTTON_LEFT) {
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
