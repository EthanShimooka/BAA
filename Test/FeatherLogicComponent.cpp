#include "FeatherLogicComponent.h"
#include <math.h> 

FeatherLogicComponent::FeatherLogicComponent(float posX, float posY, float dx, float dy)
{
	dx -= 350;
	dy -= 350;
	x = (dx - posX);
	y = (dy - posY);
	//cout << "d: " << dx << ", " << dy << endl;
	//cout << " : " << x << ", " << y << endl;
}


FeatherLogicComponent::~FeatherLogicComponent()
{
}

void FeatherLogicComponent::Update(){
	gameObjectRef->setPos(gameObjectRef->posX + x/15, gameObjectRef->posY + y/15);
	gameObjectRef->rotation = atan(y / x) / M_PI * 180;
	//gameObjectRef->flip
	
}