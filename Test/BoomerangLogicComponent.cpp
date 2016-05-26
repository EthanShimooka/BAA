#include "BoomerangLogicComponent.h"


BoomerangLogicComponent::BoomerangLogicComponent(GameObject* boomerang){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this); 
}


BoomerangLogicComponent::~BoomerangLogicComponent(){
}
void BoomerangLogicComponent::Update(){
	//automatically return if flying for more that 4 seconds
	if (!returning){
		double flightTime = (clock() - flightClock) / (CLOCKS_PER_SEC / 1000);
		if (flightTime > 4000){
			returning = true;
			dynamic_cast<BoomerangPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS))->returning = true;
		}
	}
	//update the target of the boomerang while still in flight
	double elapsedTime = (clock() - updateClock) / (CLOCKS_PER_SEC / 1000);
	//send update packet every half second
	if (elapsedTime > updateInterval){
		//set the target to be new
		float newX, newY;
		RenderManager* renderMan = RenderManager::getRenderManager();
		InputManager* inputMan = InputManager::getInstance();
		renderMan->windowCoordToWorldCoord(newX, newY, inputMan->getMouseX(), inputMan->getMouseY());
		dynamic_cast<BoomerangPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS))->targetDest = b2Vec2(newX / worldScale, newY / worldScale);
		//send the update command over the wire
		dynamic_cast<BoomerangNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->sendTargetPacket();
		updateClock = clock();
	}
}