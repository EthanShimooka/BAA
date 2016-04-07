#include "PlayerLogicComponent.h"


PlayerLogicComponent::PlayerLogicComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


PlayerLogicComponent::~PlayerLogicComponent()
{
}


void PlayerLogicComponent::Update(){
	InputManager* input = InputManager::getInstance();
	/*if (input->isMouseLeftPressed()){
		isChargingAttack = true;
	}
	if (isChargingAttack && input->isMouseLeftReleased()){
		double chargeTime = input->getMousePressDuration();
		std::cout << "Charge time: " << chargeTime << std::endl;
	}*/
	//check if on top or bottom of screen
	if (gameObjectRef->posY < 0)gameObjectRef->flipV = true;
	else gameObjectRef->flipV = false;
}

/// For spawning local feathers
uint64_t PlayerLogicComponent::spawnFeather(int dx, int dy, float chargeTime, float speed){
	GameObject* newFeather = fFactory.Spawn(featherNum++, gameObjectRef->posX, gameObjectRef->posY, dx, dy, chargeTime, speed);
	GameObjects.AddObject(newFeather);
	return featherNum - 1;
}

/// For spawning networked feathers
void PlayerLogicComponent::spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY, float chargeTime, float speed){
	GameObjects.AddObject(fFactory.Spawn(ID, initialX, initialY, destX, destY, chargeTime, speed));
}


void PlayerLogicComponent::spawnShield(){

	GameObjects.AddObject(sFactory.Spawn(featherNum++, gameObjectRef->posX + 93, (gameObjectRef->posY - 120), false));

}