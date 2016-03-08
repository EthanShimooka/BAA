#pragma once
#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <time.h>
#include "sdl2\SDL.h" // includes SDL keycodes	
#include "InputMap.h" // include mapped key definitions
#include "Controller.h"

//using namespace std;

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport)
#else
#define SQUADIO_API __declspec(dllimport)
#endif

class InputManager {
public:
	Controller* controller;
	// returns this instance of InputManager
	SQUADIO_API static InputManager* getInstance();

	// updates at every frame for new input
	SQUADIO_API void update();

	// return true if keydown
	SQUADIO_API bool isKeyDown(int key);

	// return true if keyup
	SQUADIO_API bool isKeyUp(int key);

	// return true if mousedown
	SQUADIO_API bool isMouseDown(int b);

	// return true if mouseup
	SQUADIO_API bool isMouseUp(int b);

	// get mouse x and y positions
	SQUADIO_API int getMouseX();
	SQUADIO_API int getMouseY();

	// lock and unlock input
	SQUADIO_API void lock();
	SQUADIO_API void unlock();

	// if mouse was pressed this frame
	SQUADIO_API bool isMouseLeftPressed();

	// if mouse was released this frame
	SQUADIO_API bool isMouseLeftReleased();

	// returns the duration of the last left mouse press in milliseconds
	SQUADIO_API double getMousePressDuration();

protected:
	// constructor only called by getInstance()
	InputManager();
	InputManager(InputManager const&) {};
	void operator=(InputManager const&) {};

	// single instance of InputManager
	static InputManager* inputInstance;

private:
	// keyboard state
	const uint8_t* keyboardState;

	// mouse state
	uint8_t mouseState;

	// x and y positions of mouse
	int mouseX, mouseY;

	// mouse states
	std::vector<int> mouseDown;
	std::vector<int> mouseUp;

	clock_t mousePressClock;
	double mousePressTime;

	bool mouseLeftPressed;
	bool mouseLeftReleased;

	// keyboard input allowed or not
	bool locked;
};

#endif // INPUTMANAGER_H_INCLUDED