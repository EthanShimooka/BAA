#include "ButtonLogicComponent.h"


ButtonLogicComponent::ButtonLogicComponent(GameObject* button, int _width, int _height, std::string _sound)
{
	gameObjectRef = button;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	input = InputManager::getInstance();
	width = _width;
	height = _height;
	sound = _sound;
}


ButtonLogicComponent::~ButtonLogicComponent()
{
}


bool ButtonLogicComponent::isButtonPressed(){
	if (input->isMouseLeftReleased()){
		//get mouse position
		float x, y;

		RenderManager::getRenderManager()->windowCoordToWorldCoord(x, y, input->getMouseX(), input->getMouseY());
		x -= width / 2;
		y -= height / 2;
		std::cout << "top bottom left right " << gameObjectRef->posY << ", " << gameObjectRef->posY + height << ", " << gameObjectRef->posX << ", " << gameObjectRef->posX + width << std::endl;
		std::cout << "x: " << x << ", y: " << y << std::endl;// << ", " << gameObjectRef->posX << ", " << gameObjectRef->posY << ", " << width << ", " << height << std::endl;
		// returns true if mouse within bounds
		if (x <= gameObjectRef->posX && x + width >= gameObjectRef->posX &&
			y <= gameObjectRef->posY && y + height >= gameObjectRef->posY){
			if (sound != "")
				AudioManager::getAudioInstance()->playByName(sound);
			return true;
		}
	}
	return false;
}

bool ButtonLogicComponent::isMouseHovering(){
	float x, y;

	RenderManager::getRenderManager()->windowCoordToWorldCoord(x, y, input->getMouseX(), input->getMouseY());
	x -= width / 2;
	y -= height / 2;
	//std::cout << "top bottom left right " << gameObjectRef->posY << ", " << gameObjectRef->posY + height << ", " << gameObjectRef->posX << ", " << gameObjectRef->posX + width << std::endl;
	//std::cout << "x: " << x << ", y: " << y << std::endl;// << ", " << gameObjectRef->posX << ", " << gameObjectRef->posY << ", " << width << ", " << height << std::endl;
	// returns true if mouse within bounds
	if (x <= gameObjectRef->posX && x + width >= gameObjectRef->posX &&
		y <= gameObjectRef->posY && y + height >= gameObjectRef->posY)
		return true;
	return false;
}

void ButtonLogicComponent::setSound(std::string _sound){
	sound = _sound;
}

void ButtonLogicComponent::setNavButtons(GameObject* _up, GameObject* _down, GameObject* _left, GameObject* _right){
	//Must passing in a GameObjects refering to other buttons
	navMap.up = dynamic_cast<ButtonLogicComponent*>(_up->GetComponent(COMPONENT_LOGIC));
	navMap.down = dynamic_cast<ButtonLogicComponent*>(_down->GetComponent(COMPONENT_LOGIC));
	navMap.left = dynamic_cast<ButtonLogicComponent*>(_left->GetComponent(COMPONENT_LOGIC));
	navMap.right = dynamic_cast<ButtonLogicComponent*>(_right->GetComponent(COMPONENT_LOGIC));
}

void ButtonLogicComponent::Update(){
	if (selected){
		//this button is the one currently 'hovered' over by the controller
		
	}
}