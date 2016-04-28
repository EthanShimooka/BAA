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


void MidBaseLogicComponent::launchPlayer(GameObject * player){

	///apply logic  animation for throwing in this fucntion

	//std::cout << "this line was reached " << std::endl;

	//PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(player->GetComponent(COMPONENT_LOGIC));


}


void MidBaseLogicComponent::Update(){

	if (gameObjectRef->health < 1){
		gameObjectRef->isAlive = false;
		//Call function to end game
	}

}