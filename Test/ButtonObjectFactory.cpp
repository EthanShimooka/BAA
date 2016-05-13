#include "ButtonObjectFactory.h"


ButtonObjectFactory::ButtonObjectFactory()
{
}


ButtonObjectFactory::~ButtonObjectFactory()
{
}


GameObject* ButtonObjectFactory::Spawn(uint64_t PID, float posX, float posY, int imageID, float width, float height){
	GameObject* button = new GameObject();
	button->ID = PID;
	button->isAlive = true;
	button->setPos(posX, posY);
	ButtonLogicComponent* buttLog = new ButtonLogicComponent(button, width, height);
	ButtonRenderComponent* buttRend = new ButtonRenderComponent(button, imageID);

	return button;
}