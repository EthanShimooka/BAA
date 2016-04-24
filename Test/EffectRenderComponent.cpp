#include "EffectRenderComponent.h"

EffectRenderComponent::EffectRenderComponent(GameObject* effect, int effectType){
	gameObjectRef = effect;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	//Can put in an enum passed in and switch on the enum here to instantiate different resource ID's
	switch (effectType)
	{
	case EFFECT_EXPLOSION:
		objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 4001, gameObjectRef->posX, gameObjectRef->posY);
		allObjs["base"] = objRef;
		//Start timer with DestroyEffect call here
		//Still need to use Timing.cpp to wait for 1 second then destroy object
		Timing::sInstance.StartExplosionTimer();
		explosionTriggered = true;
		break;
	case EFFECT_PLACEHOLDER:
		//throwaway enum, can delete once we have different effects to put in
		break;
	default:
		break;
	}
	

}

EffectRenderComponent::~EffectRenderComponent(){

}

void EffectRenderComponent::Update(){
	RenderComponent::Update();
	if (explosionTriggered){
		if (Timing::sInstance.ExplosionTimerEnded()){
			DestroyEffect();
			explosionTriggered = false;
		}
	}
}

void EffectRenderComponent::DestroyEffect(){
	gameObjectRef->isAlive = false;
}