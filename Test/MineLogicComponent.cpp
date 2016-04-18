#include "MineLogicComponent.h"


MineLogicComponent::MineLogicComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


MineLogicComponent::~MineLogicComponent(){
}

void MineLogicComponent::blowUp(GameObject* victim){
	gameObjectRef->isAlive=false;
}

void MineLogicComponent::Update(){

}