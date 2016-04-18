#include "MineLogicComponent.h"


MineLogicComponent::MineLogicComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


MineLogicComponent::~MineLogicComponent(){
}

void MineLogicComponent::blowUp(){
	gameObjectRef->isAlive=false;
}

void MineLogicComponent::Update(){
	std::cout << "posx=" << gameObjectRef->posX << " posy=" << gameObjectRef->posY;
	std::cout << " spawnerX=" << spawner->posX << " spawnerY=" << spawner->posY << std::endl;

}