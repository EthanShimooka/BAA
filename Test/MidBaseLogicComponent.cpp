#include "MidBaseLogicComponent.h"
#include "MidBasePhysicsComponent.h"



MidBaseLogicComponent::MidBaseLogicComponent(GameObject * base)
{
	gameObjectRef = base;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);

}


MidBaseLogicComponent::~MidBaseLogicComponent()
{
}

//void MidBaseLogicComponent::health(){

	

//}


void MidBaseLogicComponent::attacked()
{
	
//	base_health--;
	std::cout << "Base health now = " << gameObjectRef->health << std::endl;

}

void MidBaseLogicComponent::Update(){

	if (gameObjectRef->health < 1){
		gameObjectRef->isAlive = false;
		std::cout << "TRIGGERED!!!!!!!!!!" << std::endl;
		//Call function to end game
	}

}