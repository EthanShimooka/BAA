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
		PeacockClassComponent* peacockComp = dynamic_cast<PeacockClassComponent*>(GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->GetComponent(COMPONENT_CLASS));
		for (auto i = peacockComp->fanIDs.begin(); i != peacockComp->fanIDs.end(); i++){
			//if (isCorrectID){//Need to find a way to check if it's the correct timer ending
				GameObjects.GetGameObject(*i)->isAlive = false;
				peacockComp->fanIDs.erase(i);
				break;
			//}
		}
	}
}