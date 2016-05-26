#pragma once

#ifndef BUTTONLOGICCOMPONENT_H_INCLUDED
#define BUTTONLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "ButtonObjectFactory.h"
#include "include\network\NetIncludes.h"


/// This struct contains a list of neighboring pointers to which buttons 
/// can be navigated across using a controller.
class ButtonLogicComponent;

struct UINavMap{
	ButtonLogicComponent* up;
	ButtonLogicComponent* down;
	ButtonLogicComponent* left;
	ButtonLogicComponent* right;
};

class ButtonLogicComponent :
	public LogicComponent
{
public:
	ButtonLogicComponent(GameObject* button, int _width = 100, int _height = 50, std::string _sound = "");
	~ButtonLogicComponent();
	void Update();
	bool isMouseHovering();
	bool isButtonPressed();
	int width;
	int height;
	std::string sound;
	void setSound(std::string _sound);

	InputManager* input;

	UINavMap navMap;
	bool selected = false;
	void setNavButtons(GameObject* _up, GameObject* _down, GameObject* _left, GameObject* _right);
	void selectButton();
	void unselectButton();
};

#endif