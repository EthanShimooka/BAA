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
	//update orientation
	if (gameObjectRef->posY < 0)gameObjectRef->flipV = true;
	else gameObjectRef->flipV = false;
	//update HUD
	int w, h;
	birdseedHUD->getSize(w, h);
	float meterPercent = (currBirdseed / (float)maxsBirdseed);
	SDL_Rect rect = birdseedHUD->getRenderRect();
	SDL_Rect seedRect = { defaultRect.x, defaultRect.x, defaultRect.w, defaultRect.h*meterPercent };
	birdseedHUD->setRenderRect(seedRect);
	rect = birdseedHUD->getRenderRect();
}

/// For spawning local feathers
uint64_t PlayerLogicComponent::spawnFeather(int dx, int dy, float chargeTime){
	GameObject* newFeather = fFactory.Spawn(gameObjectRef, featherNum++, gameObjectRef->posX, gameObjectRef->posY, dx, dy, chargeTime);
	GameObjects.AddObject(newFeather);
	return featherNum - 1;
}

/// For spawning networked feathers
void PlayerLogicComponent::spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY, float chargeTime){
	GameObjects.AddObject(fFactory.Spawn(gameObjectRef, ID, initialX, initialY, destX, destY, chargeTime));
}


void PlayerLogicComponent::spawnShield(){

	GameObjects.AddObject(sFactory.Spawn(featherNum++, gameObjectRef->posX + 93, (gameObjectRef->posY - 120), false));

}