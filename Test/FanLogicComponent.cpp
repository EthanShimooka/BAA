#include "FanLogicComponent.h"


FanLogicComponent::FanLogicComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


FanLogicComponent::~FanLogicComponent()
{
}

void FanLogicComponent::Update(){
	//Check timing for peacock ability
	if (Timing::sInstance.EndPeacockAbilityTimer()){
		std::cout << "INSIDE THE IF!!!!!" << std::endl;
		gameObjectRef->isAlive = false;
	}
	std::cout << "OUTSIDE THE IF!!!!!" << std::endl;
}