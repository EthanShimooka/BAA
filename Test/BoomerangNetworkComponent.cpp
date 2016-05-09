#include "BoomerangNetworkComponent.h"


BoomerangNetworkComponent::BoomerangNetworkComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	updateClock = clock();
}


BoomerangNetworkComponent::~BoomerangNetworkComponent(){
}

void BoomerangNetworkComponent::sendTargetPacket(){
	//std::cout << "boomerangnetwork: send position update packet" << std::endl;
	InputManager* input = InputManager::getInstance();
	OutputMemoryBitStream *outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	//outData->Write((int)CM_ABILITY); // have to uncomment and add in corrent command
	outData->Write(gameObjectRef->ID);
	outData->Write(input->getMouseX());
	outData->Write(input->getMouseX());
	outgoingPackets.push(outData);
}

void BoomerangNetworkComponent::handleTargetPacket(InputMemoryBitStream& fPacket){
	BoomerangPhysicsComponent* physicsComp = dynamic_cast<BoomerangPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	int destX, destY;
	fPacket.Read(destX);
	fPacket.Read(destY);
	physicsComp->targetDest = b2Vec2(destX, destY);
}

void BoomerangNetworkComponent::Update(){
	double elapsedTime = (clock() - updateClock)/(CLOCKS_PER_SEC/1000);
	//send update packet every half second
	if (elapsedTime > 500){
		sendTargetPacket();
		updateClock = clock();
	}
}