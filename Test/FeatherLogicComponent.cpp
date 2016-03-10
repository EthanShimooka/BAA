#include "FeatherLogicComponent.h"
#include <math.h> 

FeatherLogicComponent::FeatherLogicComponent(GameObject* feather, float posX, float posY, float dx, float dy)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	init(posX, posY, dx, dy);
}


FeatherLogicComponent::~FeatherLogicComponent()
{
}

void FeatherLogicComponent::Update(){
	gameObjectRef->setPos(gameObjectRef->posX + x/15, gameObjectRef->posY + y/15);
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

void FeatherLogicComponent::init(float posX, float posY, float dx, float dy){
	RenderManager* ren = RenderManager::getRenderManager();
	float ex = 0;
	float ey = 0;
	ren->windowCoordToWorldCoord(ex, ey, dx, dy);
	//dx -= 800; // manually set on screen size
	//dy -= 450; // manually set on screen size
	x = (ex - posX);
	y = (ey - posY);
	gameObjectRef->rotation = atan(y / x) / M_PI * 180;
	gameObjectRef->flipH = (x > 0) ? false : true;
}