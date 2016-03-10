#include "MinionLogicComponent.h"


MinionLogicComponent::MinionLogicComponent(GameObject* minion)
{
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


MinionLogicComponent::~MinionLogicComponent()
{
}

void MinionLogicComponent::Update(){
	
	/*if (!walkRight && gameObjectRef->posX <= initialX) //walk back and forth code
		walkRight = true;
	else if (walkRight && gameObjectRef->posX >= initialX + length)
		walkRight = false;

	float speed = (walkRight) ? 2.5 : -2.5;
	gameObjectRef->flipH = (walkRight) ? false : true;

	gameObjectRef->posX += speed;*/
	gameObjectRef->posX += 2.5;
	
}