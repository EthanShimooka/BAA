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
	if (NetworkManager::sInstance->IsMasterPeer() && canSend())
		SendMinionPos();

	while (!incomingPackets.empty()){
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;

		packet.Read(mCommand);
		switch (mCommand){
		case COMMAND::MIN_DIE:
			HandleMinionDeath();
			break;
		case COMMAND::MIN_POS:
			HandleMinionPos(packet);
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

void MinionNetworkComponent::SendMinionDeath(){
	OutputMemoryBitStream* deathPacket = new OutputMemoryBitStream();
	deathPacket->Write(NetworkManager::sInstance->kPosCC);
	deathPacket->Write(gameObjectRef->ID);
	deathPacket->Write((int)MIN_DIE);
	outgoingPackets.push(deathPacket);
}

void MinionNetworkComponent::HandleMinionDeath(){
	physComp->DestroyMinion();
}

void MinionNetworkComponent::HandleMinionPos(InputMemoryBitStream& packet){
	float x, y, velX, velY;
	uint32_t seq;
	packet.Read(seq);
	if (sequence < seq){
		packet.Read(x);
		packet.Read(y);
		packet.Read(velX);
		packet.Read(velY);
		gameObjectRef->setPos(x, y);
		physComp->mBody->SetTransform(b2Vec2(velX, velY), 0);
		sequence = seq;
	}
}

void MinionNetworkComponent::SendMinionPos(){
	OutputMemoryBitStream* posPacket = new OutputMemoryBitStream();
	posPacket->Write(NetworkManager::sInstance->kPosCC);
	posPacket->Write(gameObjectRef->ID);
	posPacket->Write((int)MIN_POS);
	posPacket->Write(sequence++);
	posPacket->Write(gameObjectRef->posX);
	posPacket->Write(gameObjectRef->posY);
	b2Vec2 vel = physComp->mBody->GetLinearVelocity();
	//std::cout << vel.x << ", " << vel.y << std::endl;
	posPacket->Write(vel.x);
	posPacket->Write(vel.y);
	outgoingPackets.push(posPacket);
}


bool MinionNetworkComponent::canSend(){
	clock_t difference = clock() - packetInterval;
	unsigned time = difference / (CLOCKS_PER_SEC / 1000);
	if (time >= 2000){
		packetInterval = clock();
		return true;
	}
	return false;
}