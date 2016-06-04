#include "PlayerNetworkComponent.h"
#include "Stats.h"


PlayerNetworkComponent::PlayerNetworkComponent(GameObject* player, PlayerUIComponent** _localUI){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	interval = 10;
	logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
	//UIComp = dynamic_cast<PlayerUIComponent*>(gameObjectRef->GetComponent(COMPONENT_UI));
	localUI = _localUI;

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
	/*OutputMemoryBitStream* outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_MOVE);
	outData->Write(sequence++);
	outData->Write(gameObjectRef->posX);
	outData->Write(gameObjectRef->posY);
	outgoingPackets.push(outData);*/
	OutputMemoryBitStream* posPacket = new OutputMemoryBitStream();
	posPacket->Write(NetworkManager::sInstance->kPosCC);
	posPacket->Write(gameObjectRef->ID);
	posPacket->Write((int)CM_MOVE);
	posPacket->Write(sequence++);
	posPacket->Write(gameObjectRef->posX);
	posPacket->Write(gameObjectRef->posY);
	b2Vec2 vel = physComp->mBody->GetLinearVelocity();
	//std::cout << vel.x << ", " << vel.y << std::endl;
	posPacket->Write(vel.x);
	posPacket->Write(vel.y);
	outgoingPackets.push(posPacket);
}

void PlayerNetworkComponent::createDeathPacket(uint64_t shooter, int playerClass, uint64_t deadPlayerID){
	Stats::incPlayerDied(deadPlayerID, shooter);
	OutputMemoryBitStream* outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_DIE);
	outData->Write(shooter);
	outData->Write(playerClass);
	outData->Write(deadPlayerID);
	outgoingPackets.push(outData);
}

void PlayerNetworkComponent::handleMovementPacket(InputMemoryBitStream& mPacket){
	/*uint32_t seq;
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
	}*/
	float x, y, velX, velY;
	uint32_t seq;
	mPacket.Read(seq);
	if (sequence < seq){
		mPacket.Read(x);
		mPacket.Read(y);
		mPacket.Read(velX);
		mPacket.Read(velY);
		gameObjectRef->setPos(x, y);
		physComp->mBody->SetTransform(b2Vec2(x / worldScale, y / worldScale), physComp->mBody->GetAngle());
		physComp->mBody->SetLinearVelocity(b2Vec2(velX, velY));
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
	uint64_t shooterID, deadPlayerID;
	int playerClass;
	dPacket.Read(shooterID);
	dPacket.Read(playerClass);
	dPacket.Read(deadPlayerID);
	Stats::incPlayerDied(deadPlayerID, shooterID);
	//std::cout << GamerServices::sInstance->GetRemotePlayerName(shooterID) << " KILLED " << GamerServices::sInstance->GetRemotePlayerName(gameObjectRef->ID) << std::endl;
	//UIComp = dynamic_cast<PlayerUIComponent*>(gameObjectRef->GetComponent(COMPONENT_UI));
	//if(UIComp)
	(*localUI)->addToKillList(shooterID, gameObjectRef->ID);
	PlayerLogicComponent* deadPlayerLogic = dynamic_cast<PlayerLogicComponent*>(GameObjects.GetGameObject(deadPlayerID)->GetComponent(COMPONENT_LOGIC));
	deadPlayerLogic->death = true;
	logicComp->playDeathSFX(playerClass, deadPlayerID);
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
	if (gameObjectRef->ID == NetworkManager::sInstance->GetMyPlayerId() && canSend()){
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

void PlayerNetworkComponent::setPointersToComps(){
	logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	physComp = dynamic_cast<PlayerPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
	//UIComp = dynamic_cast<PlayerUIComponent*>(gameObjectRef->GetComponent(COMPONENT_UI));
}