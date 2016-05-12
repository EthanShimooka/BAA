#include "ButtonObjectFactory.h"


ButtonObjectFactory::ButtonObjectFactory()
{
}


ButtonObjectFactory::~ButtonObjectFactory()
{
}


GameObject* ButtonObjectFactory::Spawn(uint64_t PID, float posX, float posY, int type){
	GameObject* button = new GameObject();
	button->ID = PID;
	button->isAlive = true;
	button->setPos(posX, posY);
	ButtonLogicComponent* buttLog = new ButtonLogicComponent(button);
	ButtonRenderComponent* buttRend = new ButtonRenderComponent(button, 19);

	return button;
}