#include "ButtonObjectFactory.h"


ButtonObjectFactory::ButtonObjectFactory()
{
}


ButtonObjectFactory::~ButtonObjectFactory()
{
}


GameObject* ButtonObjectFactory::Spawn(uint64_t PID, float posX, float posY, int imageID, float width, float height, float scale){
	GameObject* button = new GameObject();
	button->type = GAMEOBJECT_TYPE::OBJECT_BUTTON;
	button->ID = PID;
	button->isAlive = true;
	button->setPos(posX, posY);
	ButtonLogicComponent* buttLog = new ButtonLogicComponent(button, (int)width, (int)height);
	ButtonRenderComponent* buttRend = new ButtonRenderComponent(button, imageID, scale);
	

	return button;
}