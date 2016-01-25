#pragma once
#include "InputManager.h"
// #include "LogManager.h"

using namespace std;

InputManager* InputManager::instance = nullptr;

// constructor
InputManager::InputManager() :keyboard(nullptr), mouse(0), mouseX(0), 
	mouseY(0), locked(false), numKeysPressed(0), numMousePressed(0){
	// set keyboard and mouse arrays (should these be vectors?)
	for (int i = 0; i < KEYBOARD_SIZE; i++) {
		this->keyDown[i] = false;
		this->keyUp[i] = false;
	}
	for (int i = 0; i < MOUSE_SIZE; i++) {
		this->mouseDown[i] = false;
		this->mouseUp[i] = false;
	}
};

InputManager* InputManager::getInstance() {
	// if InputManager is nullptr
	if (!instance) {
		instance = new InputManager();
	}
	return instance;
}

// updates at every frame for new input
void InputManager::update() {
	// poll for keyboard and mouse events
	// http://wiki.libsdl.org/SDL_Event for case types
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			// SDL_QuitEvent has SDL_QUIT
			case SDL_QUIT:
				// todo
				break;
			// SDL_KeyboardEvents has SDL_KEYDOWN and SDL_KEYUP
			// event fields accessed through ev.key.(x)
			case SDL_KEYDOWN:
				cout << "Keypress" << endl;
				break;
			case SDL_KEYUP:
				cout << "Keyrelease" << endl;
				break;
			// SDL_MouseButtonEvent
			case SDL_MOUSEBUTTONDOWN:
				cout << "Mousepress" << endl;
				break;
			case SDL_MOUSEBUTTONUP:
				cout << "Mouserelease" << endl;
				break;
			// SDL_MouseWheelEvent
			case SDL_MOUSEWHEEL:
				break;
			// SDL_MouseMotionEvent
			case SDL_MOUSEMOTION:
				cout << ev.motion.x << " " << ev.motion.y << endl;
				break;
			default:
				break;
		}
	}
	// for now just printf states of key presses and mouse presses
	// cout << numKeysPressed << " " << numMousePressed << endl;
}

// return true if keydown
bool InputManager::isKeyDown(int key) {
	if (this->locked) {
		return false;
	}
	if (key < 0 || key >= KEYBOARD_SIZE) {
		return false;
	}
	return this->keyDown[key];
}

// return true if keyup
bool InputManager::isKeyUp(int key) {
	if (this->locked) {
		return false;
	}
	if (key < 0 || key >= KEYBOARD_SIZE) {
		return false;
	}
	return this->keyUp[key];
}

// functions to check mouse and key status
bool InputManager::isMouseDown(MouseButton b) {
	if (this->locked) {
		return false;
	}
	return this->mouseDown[b];
}

bool InputManager::isMouseUp(MouseButton b) {
	if (this->locked) {
		return false;
	}
	return this->mouseUp[b];
}

bool InputManager::isKeyPressed(KeyboardKeys k) {
	// TODO
	return false;
}

bool InputManager::isMousePressed(MouseButton b) {
	// TODO
	return false;
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