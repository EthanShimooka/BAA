#include "MidBaseLogicComponent.h"


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
	
	std::cout << "ded /n" << std::endl;
	gameObjectRef->isAlive = false;

}

void MidBaseLogicComponent::Update(){



}