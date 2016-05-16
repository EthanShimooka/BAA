#pragma once

#include "LogicComponent.h"
#include "ButtonObjectFactory.h"
#include "include\network\NetIncludes.h"

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
};

