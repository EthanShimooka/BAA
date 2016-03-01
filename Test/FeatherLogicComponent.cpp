#include "FeatherLogicComponent.h"


FeatherLogicComponent::FeatherLogicComponent(float posX, float posY, float dx, float dy)
{
	x = (dx - posX) / 15;
	y = (dy - posY) / 15;
	//cout << "d: " << dx << ", " << dy << endl;
	//cout << " : " << x << ", " << y << endl;
}


FeatherLogicComponent::~FeatherLogicComponent()
{
}

void FeatherLogicComponent::Update(){
	gameObjectRef->setPos(gameObjectRef->posX + x, gameObjectRef->posY + y);
}