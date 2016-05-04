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
	if (Timing::sInstance.EndPeacockAbilityTimer()){
		std::cout << "INSIDE THE IF!!!!!" << std::endl;
		PeacockClassComponent* peacockComp = dynamic_cast<PeacockClassComponent*>(GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->GetComponent(COMPONENT_CLASS));
		std::cout << "BEFORE LOOP!" << std::endl;
		for (auto i = peacockComp->fanIDs.begin(); i != peacockComp->fanIDs.end(); i++){
			std::cout << "BEFORE GETGAMEOBJCT CALL!" << std::endl;
			GameObjects.GetGameObject(*i)->isAlive = false;
			std::cout << "AFTER GETGAMEOBJCT CALL!" << std::endl;
		}
	}
	std::cout << "OUTSIDE THE IF!!!!!" << std::endl;
}