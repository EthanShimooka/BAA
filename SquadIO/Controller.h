#pragma once
#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport)
#else
#define SQUADIO_API __declspec(dllimport)
#endif

#include "include\sdl2\SDL.h"
#include "include\InputMap.h"
#include <vector>
#include <iostream>

class Controller{
public:
	std::vector<bool>joystickDPad;
	std::vector<bool>joystickButtonPressed;
	std::vector<bool>joystickButtonHeld;
	std::vector<bool>joystickButtonReleased;
	std::vector<double> joystickAnalogs;
	SDL_Joystick *joystick;
	SDL_Haptic *haptic;
	bool rumbleSupport;
	Controller();
	~Controller();

	// return true if joystick input up
	SQUADIO_API bool isControllerOn();

	// return true if joystick input up
	SQUADIO_API bool isJoystickUp(int b);

	// return true if joystick input up
	SQUADIO_API bool isJoystickDown(int b);

	/// return true on first frame pressed
	SQUADIO_API bool isJoystickPressed(int b);

	/// return true on first frame released
	SQUADIO_API bool isJoystickReleased(int b);

	// get x and y positions of left thumbstick
	SQUADIO_API double getLeftThumbX();
	SQUADIO_API double getLeftThumbY();

	// get x and y positions of right thumbstick
	SQUADIO_API double getRightThumbX();
	SQUADIO_API double getRightThumbY();

	// get the value of left trigger
	SQUADIO_API double getLeftTrigger();

	// get the value of right trigger
	SQUADIO_API double getRightTrigger();

	// get the value of left trigger
	SQUADIO_API bool getLeftBumper();

	// get the value of right trigger
	SQUADIO_API bool getRightBumper();

	SQUADIO_API void rumble(float strength, int duration);

	SQUADIO_API bool isDPadPressed(int pad);

	// check if a controller was just plugged in. If so, start accepting input from it.
	SQUADIO_API void update();

	// free memory allocated to controller
	SQUADIO_API void free();
};

#endif