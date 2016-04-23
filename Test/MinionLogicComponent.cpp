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

}

void MinionLogicComponent::DestroyMinion(uint64_t ID){

	if (gameObjectRef->ID == ID){
		gameObjectRef->setPos(-10000, 0);
		gameObjectRef->isAlive = false;
	}
}