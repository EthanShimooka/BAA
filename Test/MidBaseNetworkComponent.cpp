#include "MidBaseNetworkComponent.h"
#include "SystemGameObjectQueue.h"


MidBaseNetworkComponent::MidBaseNetworkComponent(GameObject* base)
{
	gameObjectRef = base;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
}


MidBaseNetworkComponent::~MidBaseNetworkComponent()
{
}


void MidBaseNetworkComponent::Update(){
	while (!incomingPackets.empty()){
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;

		packet.Read(mCommand);
		switch (mCommand){
		case BASE_NET::BASE_HEALTH:
			HandleBaseHealth(packet);
			break;
		case BASE_NET::BASE_INVALID:
			break;
		}

		incomingPackets.pop();
	}

	while (!outgoingPackets.empty()){
		OutputMemoryBitStream* outData = outgoingPackets.front();
		NetworkManager::sInstance->sendPacketToAllPeers(*outData);
		outgoingPackets.pop();
		delete outData;
	}
}

void MidBaseNetworkComponent::SendBaseHealth(){
	OutputMemoryBitStream* packet = new OutputMemoryBitStream();
	packet->Write(NetworkManager::sInstance->kPosCC);
	packet->Write(gameObjectRef->ID);
	packet->Write((int)BASE_HEALTH);
	packet->Write(Stats::baseHealth(gameObjectRef->team));
	outgoingPackets.push(packet);
}

void MidBaseNetworkComponent::HandleBaseHealth(InputMemoryBitStream& packet){
	int health;
	packet.Read(health);
	Stats::setBaseHealth(gameObjectRef->team, health);
	gameObjectRef->health = health;
	if (gameObjectRef->team == GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->team){
		RenderManager* renderMan = RenderManager::getRenderManager();
		renderMan->ShakeScreen(0.3f, 0.2f);
	}
}