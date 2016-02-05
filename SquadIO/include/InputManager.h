#pragma once
#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string>
#include "sdl2\SDL.h" // includes SDL keycodes	
#include "InputMap.h" // include mapped key definitions
// #include <LogManager.h>

using namespace std;

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport)
#else
#define SQUADIO_API __declspec(dllimport)
#endif

class InputManager {
public:
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
	vector<int> mouseDown;
	vector<int> mouseUp;

	// keyboard input allowed or not
	bool locked;
};

#endif // INPUTMANAGER_H_INCLUDED
