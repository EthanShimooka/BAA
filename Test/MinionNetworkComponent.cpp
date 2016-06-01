#include "MinionNetworkComponent.h"


MinionNetworkComponent::MinionNetworkComponent(GameObject* minion)
{
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	physComp = dynamic_cast<MinionPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	interval = 500;
	if (NetworkManager::sInstance->IsMasterPeer()){
		SendSpawnMinion(gameObjectRef->ID, gameObjectRef->team);
	}
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
		case COMMAND::MIN_HIT:
			HandleBaseHit(packet);
			break;
		case COMMAND::MIN_POS:
			HandleMinionPos(packet);
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

void MinionNetworkComponent::SendBaseHit(int teamHit, uint64_t minionID, uint64_t baseID){//Or pass it yellowScore & purpleScore
	OutputMemoryBitStream* hitPacket = new OutputMemoryBitStream();
	hitPacket->Write(NetworkManager::sInstance->kPosCC);
	hitPacket->Write(gameObjectRef->ID);
	hitPacket->Write((int)MIN_HIT);
	hitPacket->Write(teamHit);
	hitPacket->Write(minionID);
	hitPacket->Write(baseID);
	outgoingPackets.push(hitPacket);
}

void MinionNetworkComponent::HandleBaseHit(InputMemoryBitStream& packet){
	int teamHit = -1;
	uint64_t minionID = 0;
	uint64_t baseID = 0;
	packet.Read(teamHit);
	packet.Read(minionID);
	packet.Read(baseID);
	GameObjects.GetGameObject(baseID)->health++;
	MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(GameObjects.GetGameObject(minionID)->GetComponent(COMPONENT_LOGIC));
	logicComp->MinionDeath();
	//Only shake if our own base is being attacked
	if (GameObjects.GetGameObject(minionID)->team != GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->team){
		RenderManager* renderMan = RenderManager::getRenderManager();
		renderMan->ShakeScreen(0.3f, 0.2f);
	}
	if (teamHit == TEAM_YELLOW){
		Stats::incBaseHealth_yellow();
	}
	else if (teamHit == TEAM_PURPLE){
		Stats::incBaseHealth_purple();
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
		physComp->mBody->SetTransform(b2Vec2(x / worldScale, y / worldScale), 0);
		physComp->mBody->SetLinearVelocity(b2Vec2(velX, velY));
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

void MinionNetworkComponent::SendSpawnMinion(uint64_t ID, uint8_t team){
	OutputMemoryBitStream* packet = new OutputMemoryBitStream();
	packet->Write(NetworkManager::sInstance->kPosCC);
	packet->Write((uint8_t)-1);
	packet->Write(ID);
	packet->Write(team);
	outgoingPackets.push(packet);

}