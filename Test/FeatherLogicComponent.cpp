#include "FeatherLogicComponent.h"
#include <math.h> 

FeatherLogicComponent::FeatherLogicComponent(GameObject* feather, float posX, float posY, float dx, float dy)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	dx -= 800; // manually set on screen size
	dy -= 450; // manually set on screen size
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
	if (gameObjectRef->posX > 800 || gameObjectRef->posX < -800){ // manually set on screen size
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
	}
	if (gameObjectRef->posY > 450 || gameObjectRef->posY < -450){ // manually set on screen size
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
	}
}