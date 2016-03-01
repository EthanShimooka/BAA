#include "FeatherLogicComponent.h"
#include <math.h> 

FeatherLogicComponent::FeatherLogicComponent(GameObject* feather, float posX, float posY, float dx, float dy)
{
	gameObjectRef = feather;
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
}