#include "FeatherLogicComponent.h"
#include <math.h> 

FeatherLogicComponent::FeatherLogicComponent(GameObject* feather, float posX, float posY, float dx, float dy)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	dx -= 350;
	dy -= 350;
	x = (dx - posX);
	y = (dy - posY);
	gameObjectRef->rotation = atan(y / x) / M_PI * 180;
	gameObjectRef->flipH = (x > 0) ? false : true;
}


FeatherLogicComponent::~FeatherLogicComponent()
{
}

void FeatherLogicComponent::Update(){
	gameObjectRef->setPos(gameObjectRef->posX + x/15, gameObjectRef->posY + y/15);
	if (gameObjectRef->posX > 350 || gameObjectRef->posX < -350){
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
	}
	if (gameObjectRef->posY > 350 || gameObjectRef->posY < -350){
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
	}
}