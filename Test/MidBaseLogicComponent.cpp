#include "MidBaseLogicComponent.h"
#include "MidBasePhysicsComponent.h"



MidBaseLogicComponent::MidBaseLogicComponent(GameObject * base)
{

}


MidBaseLogicComponent::~MidBaseLogicComponent()
{
}

void MidBaseLogicComponent::health(){

	

}


void MidBaseLogicComponent::attacked()
{

		base_health--;
	

}

void MidBaseLogicComponent::Update(){

	if (base_health == 0){
		gameObjectRef->isAlive = false;
	}

}