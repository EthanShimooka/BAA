#include "MinionNetworkComponent.h"


MinionNetworkComponent::MinionNetworkComponent(GameObject* minion)
{
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	physComp = dynamic_cast<MinionPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
}


MinionNetworkComponent::~MinionNetworkComponent()
{
}

void MinionNetworkComponent::Update(){
	while (!incomingPackets.empty()){
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;

		packet.Read(mCommand);
		switch (mCommand){
		case COMMAND::MIN_DIE:
			HandleMenionDeath();
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

void MinionNetworkComponent::SendMenionDeath(){
	OutputMemoryBitStream* deathPacket = new OutputMemoryBitStream();
	deathPacket->Write(NetworkManager::sInstance->kPosCC);
	deathPacket->Write(gameObjectRef->ID);
	deathPacket->Write((int)MIN_DIE);
	outgoingPackets.push(deathPacket);
}

void MinionNetworkComponent::HandleMenionDeath(){
	physComp->DestroyMinion();
}