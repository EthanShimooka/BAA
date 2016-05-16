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

void ButtonLogicComponent::Update(){

}

bool ButtonLogicComponent::isButtonPressed(){
	if (input->isMouseLeftReleased()){
		if (sound != "")
			AudioManager::getAudioInstance()->playByName(sound);

		//get mouse position
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