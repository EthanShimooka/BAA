#include "PowerShieldLogicComponent.h"


PowerShieldLogicComponent::PowerShieldLogicComponent(GameObject* shield)
{
	gameObjectRef = shield;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);


}


PowerShieldLogicComponent::~PowerShieldLogicComponent()
{
}


void PowerShieldLogicComponent::Update(){
	/*if (Timing::sInstance.EndChickenAbilityTimer()){
		gameObjectRef->isAlive = false;
	}*/
}

void PowerShieldLogicComponent::spawnShield(int xpos, int ypos){

}

void PowerShieldLogicComponent::spawnShield(uint64_t ID, float initialX, float initialY, int destX, int destY){



}