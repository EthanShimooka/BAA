/**
*  UIInputComponent.h
*  Authors: Ethan Shimooka, Vincent Moudy
*  Date 2/29/2016
*  Description :
InputComponent represents the abstreact base class from which all other
imput Components are derived.


*/
#pragma once

#ifndef UIINPUTCOMPONENT_H_INCLUDED
#define UIINPUTCOMPONENT_H_INCLUDED


#include "InputUIComponent.h"

class UIInputComponent : public InputUIComponent
{
public:
	UIInputComponent();
	~UIInputComponent();

	void Update();

};

#endif