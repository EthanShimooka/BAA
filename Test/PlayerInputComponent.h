/**
*  PlayerInputComponent.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
InputComponent represents the abstreact base class from which all other
imput Components are derived.

Only the local player GameObject should have this component.

*/
#pragma once

#ifndef PLAYERINPUTCOMPONENT_H_INCLUDED
#define PLAYERINPUTCOMPONENT_H_INCLUDED


#include "InputComponent.h"
class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent();
	~PlayerInputComponent();

	void Update();

};

#endif