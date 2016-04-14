#include "MineRenderComponent.h"


MineRenderComponent::MineRenderComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
}


MineRenderComponent::~MineRenderComponent(){
}

void MineRenderComponent::Update(){

}