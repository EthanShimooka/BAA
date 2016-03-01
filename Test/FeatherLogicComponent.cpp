#include "FeatherLogicComponent.h"
#include <math.h> 

FeatherLogicComponent::FeatherLogicComponent(float posX, float posY, float dx, float dy)
{
	dx -= 350;
	dy -= 350;
	x = (dx - posX);
	y = (dy - posY);
}


FeatherLogicComponent::~FeatherLogicComponent()
{
}

void FeatherLogicComponent::Update(){
	gameObjectRef->setPos(gameObjectRef->posX + x/15, gameObjectRef->posY + y/15);
	gameObjectRef->rotation = atan(y / x) / M_PI * 180;
	gameObjectRef->flipH = (x > 0) ? false : true;
}