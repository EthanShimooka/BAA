#include "PlayerLogicComponent.h"


PlayerLogicComponent::PlayerLogicComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	fFactory = FeatherObjectFactory::FeatherObjectFactory();
}


PlayerLogicComponent::~PlayerLogicComponent()
{
}


void PlayerLogicComponent::Update(){
	InputManager* input = InputManager::getInstance();
	if (input->isMouseLeftPressed()){
		isChargingAttack = true;
	}
	if (isChargingAttack&&input->isMouseLeftReleased()){
		double chargeTime = input->getMousePressDuration();
		std::cout << chargeTime << std::endl;
	}
}


uint64_t PlayerLogicComponent::spawnFeather(int dx, int dy){
	GameObjects.AddObject(fFactory.Spawn(gameObjectRef, featherNum++, gameObjectRef->posX, gameObjectRef->posY, dx, dy));
	return featherNum - 1;
}

void PlayerLogicComponent::spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY){
	GameObjects.AddObject(fFactory.Spawn(gameObjectRef, ID, initialX, initialY, destX, destY));
}

void PlayerLogicComponent::takeDamage(int damage) {
	// if player is alive, check for health > 0, if health reaches 0, disable the player
	if (playerAlive) {

	} else {

	}
}