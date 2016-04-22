#include "PlayerNetworkComponent.h"


PlayerNetworkComponent::PlayerNetworkComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	render = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
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
	//cout << 0 << ", " << gameObjectRef->posX << ", " << gameObjectRef->posY << ", " << input->getMouseX() << ", " << input->getMouseY() << endl;
	outgoingPackets.push(featherPacket);
}

//void PlayerNetworkComponent::createAbilityPacket(uint64_t ID, int finalX, int finalY, float speed){
//	OutputMemoryBitStream *featherPacket = new OutputMemoryBitStream();
//	featherPacket->Write(NetworkManager::sInstance->kPosCC);
//	featherPacket->Write(gameObjectRef->ID);
//	featherPacket->Write((int)CM_ATTACK);
//	featherPacket->Write(ID);
//	featherPacket->Write(gameObjectRef->posX);
//	featherPacket->Write(gameObjectRef->posY);
//	featherPacket->Write(finalX);
//	featherPacket->Write(finalY);
//	featherPacket->Write(speed);
//	//cout << 0 << ", " << gameObjectRef->posX << ", " << gameObjectRef->posY << ", " << input->getMouseX() << ", " << input->getMouseY() << endl;
//	outgoingPackets.push(featherPacket);
//}

void PlayerNetworkComponent::createMovementPacket(float x, float y){
	OutputMemoryBitStream* outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_MOVE);
	//outData.Write(testNum++);
	outData->Write(gameObjectRef->posX);
	outData->Write(gameObjectRef->posY);
	outgoingPackets.push(outData);
}

void PlayerNetworkComponent::handleMovementPacket(InputMemoryBitStream& mPacket){
	//int t;
	//packet.Read(t);
	//if (testNum < t){
	float x;
	mPacket.Read(x);
	if (gameObjectRef->posX != 0) render->setAnimation("walk");
	else render->setAnimation("idle");
	if (gameObjectRef->posX > x){
		gameObjectRef->flipH = true;
	}
	else if (gameObjectRef->posX < x){
		gameObjectRef->flipH = false;
	}
	gameObjectRef->posX = x;
	//packet.Read(gameObjectRef->posX);
	mPacket.Read(gameObjectRef->posY);
	//testNum = t;
	//}
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
	logic->spawnFeather(ID, initialX, initialY, destX, destY, speed);
}

void PlayerNetworkComponent::Update(){
	while (!incomingPackets.empty()){
		//PlayerLogicComponent *logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		//PlayerRenderComponent *render = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;

		packet.Read(mCommand);
		switch (mCommand){
		case COMMAND_TYPE::CM_INVALID:
			//handle 
			break;
		case COMMAND_TYPE::CM_MOVE:
			handleMovementPacket(packet);
			break;
		case COMMAND_TYPE::CM_ATTACK:
			handleFeatherPacket(packet);
			break;
		case COMMAND_TYPE::CM_ABILITY:
			//handle 
			break;
		case COMMAND_TYPE::CM_DIE:
			//handle 
			break;
		case COMMAND_TYPE::CM_JUMP:
			//handle 
			break;
		default:
			std::cout << gameObjectRef->ID << ", " << mCommand << ": There is no such command!!" << std::endl;
		}

		incomingPackets.pop();
	}

	// send outgoing packets
	while (!outgoingPackets.empty()){
		OutputMemoryBitStream* outData = outgoingPackets.front();
		NetworkManager::sInstance->sendPacketToAllPeers(*outData);
		outgoingPackets.pop();
		delete outData;
	}

	if (gameObjectRef->ID == NetworkManager::sInstance->GetMyPlayerId()){
		OutputMemoryBitStream outData;
		outData.Write(NetworkManager::sInstance->kPosCC);
		outData.Write(gameObjectRef->ID);
		outData.Write((int)CM_MOVE);
		//outData.Write(testNum++);
		outData.Write(gameObjectRef->posX);
		outData.Write(gameObjectRef->posY);
		NetworkManager::sInstance->sendPacketToAllPeers(outData);
	}
}