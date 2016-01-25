#pragma once
#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <SDL.h> // includes SDL keycodes	
#include "InputMap.h" // include mapped key definitions
// #include <LogManager.h>

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport)
#else
#define SQUADIO_API __declspec(dllimport)
#endif

class InputManager {
public:
	// returns this instance of InputManager
	static InputManager* getInstance();

	// updates at every frame for new input
	void update();

	// return true if keydown
	bool isKeyDown(int key);

	// return true if keyup
	bool isKeyUp(int key);

	// functions to check mose and key status
	bool isMouseDown(MouseButton b);

	bool isMouseUp(MouseButton b);

	bool isKeyPressed(KeyboardKeys k);

	bool isMousePressed(MouseButton b);

	// get mouse x and y positions
	int getMouseX();
	int getMouseY();

	// lock and unlock input
	void lock();
	void unlock();

protected:
	// constructor only called by getInstance()
	InputManager();
	InputManager(InputManager const&) {};
	void operator=(InputManager const&) {};

	// single instance of InputManager
	static InputManager* instance;

private:
	// keyboard and mouse states
	const uint8_t* keyboard;
	uint8_t mouse;

	// x and y positions of mouse
	int mouseX, mouseY;

	bool keyDown[KEYBOARD_SIZE];
	bool keyUp[KEYBOARD_SIZE];

	bool mouseDown[MOUSE_SIZE];
	bool mouseUp[MOUSE_SIZE];

	bool locked;

	// test variables for keydown
	int numKeysPressed;
	int numMousePressed;
};

#endif // INPUTMANAGER_H_INCLUDED