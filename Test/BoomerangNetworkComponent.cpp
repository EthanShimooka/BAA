#include "BoomerangNetworkComponent.h"


BoomerangNetworkComponent::BoomerangNetworkComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
}


BoomerangNetworkComponent::~BoomerangNetworkComponent(){
}

void BoomerangNetworkComponent::sendTargetPacket(){
	//std::cout << "boomerangnetwork: send position update packet" << std::endl;
	InputManager* input = InputManager::getInstance();
	OutputMemoryBitStream *outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	//outData->Write((int)CM_ABILITY); // have to uncomment and add in corrent command
	outData->Write(gameObjectRef->ID);
	float destX, destY;
	RenderManager* renderMan = RenderManager::getRenderManager();
	renderMan->windowCoordToWorldCoord(destX, destY, input->getMouseX(), input->getMouseY());
	outData->Write(destX / worldScale);
	outData->Write(destY / worldScale);
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
	while (!incomingPackets.empty()){
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;
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