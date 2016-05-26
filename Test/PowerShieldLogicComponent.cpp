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
}

void PowerShieldLogicComponent::spawnShield(int xpos, int ypos){

}

void PowerShieldLogicComponent::spawnShield(uint64_t ID, float initialX, float initialY, int destX, int destY){



}

void PowerShieldLogicComponent::playShieldCollisionSFX(){
	//Need shield object
	PowerShieldRenderComponent* rendComp = dynamic_cast<PowerShieldRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	RenderManager* renderMan = RenderManager::getRenderManager();
	if (renderMan->isObjOnScreen(rendComp->objRef)){
		AudioManager* audioMan = AudioManager::getAudioInstance();
		audioMan->playByName("chickenshieldsfx.ogg");
	}
}