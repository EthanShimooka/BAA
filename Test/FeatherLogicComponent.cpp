#include "FeatherLogicComponent.h"
#include "PlayerLogicComponent.h"
#include "AbsorbParticle.h"
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
	if (gameObjectRef->posX > 2000 || gameObjectRef->posX < -2000){ // manually set on screen size
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
		/*for (int i = 0; i < GameObjects.alive_objects.size(); i++){
			if (GameObjects.alive_objects[i] == gameObjectRef){
				GameObjects.alive_objects.erase(GameObjects.alive_objects.begin() + i);
				break;
			}
		}
		GameObjects.dead_feathers.push_back(gameObjectRef);*/
	}
	if (gameObjectRef->posY > 1000 || gameObjectRef->posY < -1000){ // manually set on screen size
		gameObjectRef->isAlive = false;
		gameObjectRef->setPos(-10000, 0);
		/*for (int i = 0; i < GameObjects.alive_objects.size(); i++){
			if (GameObjects.alive_objects[i] == gameObjectRef){
				GameObjects.alive_objects.erase(GameObjects.alive_objects.begin() + i);
				break;
			}
		}
		GameObjects.dead_feathers.push_back(gameObjectRef);*/
	}
}


void FeatherLogicComponent::init(){
}

void FeatherLogicComponent::giveBirdseed(int numSeeds) {
	ClassComponent* classComp = dynamic_cast<ClassComponent*>(owner->GetComponent(COMPONENT_CLASS));
	if (classComp->currBirdseed + numSeeds <= classComp->maxsBirdseed){
		classComp->currBirdseed += numSeeds;
		createAbsorbParticle(gameObjectRef, owner, classComp->currBirdseed, 0, 0);
	}
	else classComp->currBirdseed = classComp->maxsBirdseed;
}