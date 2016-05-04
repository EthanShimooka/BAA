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

#include "SystemUIObjectQueue.h"
#include "UIComponent.h"
#include "UIRenderComponent.h"

class UIInputComponent : public UIComponent
{
public:
	/// Constructor
	UIInputComponent();
	/// Destructor
	~UIInputComponent();

	/// Updates the UI object
	void Update();

	/// Determines if UI button has been pressed, returns true if pressed.
	bool isButtonPressed(int x, int y);
	/// Determines if mouse is hovering over UI element
	bool isMouseHovering(int x, int y);

};

#endif