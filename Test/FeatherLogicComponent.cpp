#include "FeatherLogicComponent.h"
#include <math.h> 

FeatherLogicComponent::FeatherLogicComponent(GameObject* feather)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	init();
}


FeatherLogicComponent::~FeatherLogicComponent()
{
}

void FeatherLogicComponent::Update(){
	if (gameObjectRef->posX > 800 || gameObjectRef->posX < -800){ // manually set on screen size
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
		GameObjects.dead_feathers.push_back(gameObjectRef);
	}
	if (gameObjectRef->posY > 450 || gameObjectRef->posY < -450){ // manually set on screen size
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
		GameObjects.dead_feathers.push_back(gameObjectRef);
	}
}

void FeatherLogicComponent::init(){

}