#include "ButtonLogicComponent.h"


ButtonLogicComponent::ButtonLogicComponent(GameObject* button, int _width, int _height, std::string _sound, int type)
{
	gameObjectRef = button;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	input = InputManager::getInstance();
	width = _width;
	height = _height;
	sound = _sound;
	buttonType = type;
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
	//Must passing in a GameObjects refering to other buttons. If there is now button in the specificed
	//direction, assign it to NULL
	navMap.up = _up ? dynamic_cast<ButtonLogicComponent*>(_up->GetComponent(COMPONENT_LOGIC)) : NULL;
	navMap.down = _down ? dynamic_cast<ButtonLogicComponent*>(_down->GetComponent(COMPONENT_LOGIC)) : NULL;
	navMap.left = _left ? dynamic_cast<ButtonLogicComponent*>(_left->GetComponent(COMPONENT_LOGIC)) : NULL;
	navMap.right = _right ? dynamic_cast<ButtonLogicComponent*>(_right->GetComponent(COMPONENT_LOGIC)) : NULL;
}

void ButtonLogicComponent::selectButton(){
	selected = true;
	//gameObjectRef->posY += 20;
	dynamic_cast<ButtonRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER))->toggleSprites();
}

void ButtonLogicComponent::unselectButton(){
	selected = false;
	//gameObjectRef->posY -= 20;
	dynamic_cast<ButtonRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER))->toggleSprites();
}

void ButtonLogicComponent::Update(){
	Controller* controller = input->controller;
	if (selected){
		//this button is the one currently 'hovered' over by the controller
		//listen for d-pad and arrow input to navigate to next button
		if ((input->isKeyDown(KEY_UP) || controller->isDPadPressed(JOYSTICK_DPAD_UP)) && navMap.up){
			this->unselectButton();
			navMap.up->selectButton();
			//maybe something else needs to be updated here (and the other directions too)
		}
		else if ((input->isKeyDown(KEY_DOWN) || controller->isDPadPressed(JOYSTICK_DPAD_DOWN)) && navMap.down){
			this->unselectButton();
			navMap.down->selectButton();
		}
		else if ((input->isKeyDown(KEY_LEFT) || controller->isDPadPressed(JOYSTICK_DPAD_LEFT)) && navMap.left){
			this->unselectButton();
			navMap.left->selectButton();
		}
		else if ((input->isKeyDown(KEY_RIGHT) || controller->isDPadPressed(JOYSTICK_DPAD_RIGHT)) && navMap.right){
			this->unselectButton();
			navMap.right->selectButton();
		}
	}
	//if the button is currently selected, and the enter key
	//or A key on controller has been pressed, activate the button
	if (selected){
		if (controller->isJoystickPressed(JOYSTICK_A) || input->isKeyDown(KEY_RETURN)){
			//activate the button here
			std::cout << "activate the button here" << std::endl;
		}
	}
	if (buttonType == BUTTON_ICON){
		//do something special for the icon buttons like make them jump or something
	}
}