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

class Controller{
public:
	std::vector<bool>joystickButtonPressed;
	std::vector<bool>joystickButtonHeld;
	std::vector<bool>joystickButtonReleased;
	std::vector<double> joystickAnalogs;

	Controller();
	~Controller();

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
};

#endif