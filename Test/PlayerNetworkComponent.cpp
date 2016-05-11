#include "PlayerNetworkComponent.h"


PlayerNetworkComponent::PlayerNetworkComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
}


PlayerNetworkComponent::~PlayerNetworkComponent()
{
}

void PlayerNetworkComponent::createFeatherPacket(uint64_t ID, int finalX, int finalY, float speed){
	OutputMemoryBitStream *featherPacket = new OutputMemoryBitStream();
	featherPacket->Write(NetworkManager::sInstance->kPosCC);
	featherPacket->Write(gameObjectRef->ID);
	featherPacket->Write((int)CM_ATTACK);
	featherPacket->Write(ID);
	featherPacket->Write(gameObjectRef->posX);
	featherPacket->Write(gameObjectRef->posY);
	featherPacket->Write(finalX);
	featherPacket->Write(finalY);
	featherPacket->Write(speed);
	outgoingPackets.push(featherPacket);
}

void PlayerNetworkComponent::createMovementPacket(){
	OutputMemoryBitStream* outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_MOVE);
	outData->Write(sequence++);
	outData->Write(gameObjectRef->posX);
	outData->Write(gameObjectRef->posY);
	outgoingPackets.push(outData);
}

void PlayerNetworkComponent::createDeathPacket(uint64_t shooter, int playerClass){
	OutputMemoryBitStream* outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_DIE);
	outData->Write(shooter);
	outData->Write(playerClass);
	outgoingPackets.push(outData);
}

void PlayerNetworkComponent::handleMovementPacket(InputMemoryBitStream& mPacket){
	uint32_t seq;
	mPacket.Read(seq);
	if (sequence < seq){
		float x;
		mPacket.Read(x);
		if (gameObjectRef->posX != x) renderComp->setAnimation("walk");
		else renderComp->setAnimation("idle");
		if (gameObjectRef->posX > x){
			gameObjectRef->flipH = true;
		}
		else if (gameObjectRef->posX < x){
			gameObjectRef->flipH = false;
		}
		gameObjectRef->posX = x;
		mPacket.Read(gameObjectRef->posY);
		sequence = seq;
	}
}

void PlayerNetworkComponent::handleFeatherPacket(InputMemoryBitStream& fPacket){
	uint64_t ID;
	float initialX, initialY;
	int destX, destY;
	float speed;
	fPacket.Read(ID);
	fPacket.Read(initialX);
	fPacket.Read(initialY);
	fPacket.Read(destX);
	fPacket.Read(destY);
	fPacket.Read(speed);
	logicComp->spawnFeather(ID, initialX, initialY, destX, destY, speed);
}

void PlayerNetworkComponent::handleDeathPacket(InputMemoryBitStream& dPacket){
	uint64_t shooterID;
	int playerClass;
	dPacket.Read(shooterID);
	dPacket.Read(playerClass);
	std::cout << GamerServices::sInstance->GetRemotePlayerName(shooterID) << " KILLED " << GamerServices::sInstance->GetRemotePlayerName(gameObjectRef->ID) << std::endl;
	logicComp->addToKillList(shooterID,GamerServices::sInstance->GetLocalPlayerId());
	//trigger death audio here for other 7 players
	//Write function in logic component which takes a references to the player class and plays appropriate noise
	logicComp->playDeathSFX(playerClass);
	logicComp->becomeEgg();
}

void PlayerNetworkComponent::handleAbilityPacket(InputMemoryBitStream& aPacket){
	classComp->readNetAbility(aPacket);
}


void PlayerNetworkComponent::Update(){
	while (!incomingPackets.empty()){
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;

		packet.Read(mCommand);
		switch (mCommand){
		case COMMAND_TYPE::CM_MOVE:
			handleMovementPacket(packet);
			break;
		case COMMAND_TYPE::CM_ATTACK:
			handleFeatherPacket(packet);
			break;
		case COMMAND_TYPE::CM_ABILITY:
			handleAbilityPacket(packet);
			break;
		case COMMAND_TYPE::CM_DIE:
			handleDeathPacket(packet);
			break;
		case COMMAND_TYPE::CM_JUMP:
			//handle 
			break;
		case COMMAND_TYPE::CM_INVALID:
			//handle 
			break;
		default:
			std::cout << gameObjectRef->ID << ", " << mCommand << ": There is no such command!!" << std::endl;
		}

		incomingPackets.pop();
	}

	// creating a movement packet
	if (gameObjectRef->ID == NetworkManager::sInstance->GetMyPlayerId()){
		createMovementPacket();
	}

	// send outgoing packets
	while (!outgoingPackets.empty()){
		OutputMemoryBitStream* outData = outgoingPackets.front();
		NetworkManager::sInstance->sendPacketToAllPeers(*outData);
		outgoingPackets.pop();
		delete outData;
	}
}