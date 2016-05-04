#include "BoomerangLogicComponent.h"


BoomerangLogicComponent::BoomerangLogicComponent(GameObject* boomerang){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this); 
}


BoomerangLogicComponent::~BoomerangLogicComponent(){
}
