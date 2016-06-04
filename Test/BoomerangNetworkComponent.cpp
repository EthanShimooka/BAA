#include "BoomerangNetworkComponent.h"


BoomerangNetworkComponent::BoomerangNetworkComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
}


BoomerangNetworkComponent::~BoomerangNetworkComponent(){
}

void BoomerangNetworkComponent::sendTargetPacket(){
	std::cout << "boomerangnetwork: send position update packet" << std::endl;
	InputManager* input = InputManager::getInstance();
	OutputMemoryBitStream *outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	//outData->Write((int)CM_ABILITY); // have to uncomment and add in corrent command
	outData->Write(gameObjectRef->ID);
	BoomerangPhysicsComponent* physicsComp = dynamic_cast<BoomerangPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	outData->Write((float)physicsComp->targetDest.x);
	outData->Write((float)physicsComp->targetDest.y);

	std::cout << physicsComp->targetDest.x << ", " << physicsComp->targetDest.y << std::endl;
	outgoingPackets.push(outData);
}


void BoomerangNetworkComponent::handleTargetPacket(InputMemoryBitStream& fPacket){
	std::cout << "boomerangnetwork: handle position update packet" << std::endl;
	BoomerangPhysicsComponent* physicsComp = dynamic_cast<BoomerangPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	float destX, destY;
	fPacket.Read(destX);
	fPacket.Read(destY);
	physicsComp->targetDest = b2Vec2(destX, destY);
}

void BoomerangNetworkComponent::Update(){
	while (!incomingPackets.empty()){
		InputMemoryBitStream packet = incomingPackets.front();
		handleTargetPacket(packet);
		incomingPackets.pop();
	}

	// send outgoing packets
	while (!outgoingPackets.empty()){
		OutputMemoryBitStream* outData = outgoingPackets.front();
		NetworkManager::sInstance->sendPacketToAllPeers(*outData);
		outgoingPackets.pop();
		delete outData;
	}
}