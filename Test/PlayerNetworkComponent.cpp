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
	outgoingPackets.push(featherPacket);
}

void PlayerNetworkComponent::createMovementPacket(){
	OutputMemoryBitStream* outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_MOVE);
	//outData.Write(testNum++);
	outData->Write(gameObjectRef->posX);
	outData->Write(gameObjectRef->posY);
	outgoingPackets.push(outData);
}

void PlayerNetworkComponent::createDeathPacket(){
	OutputMemoryBitStream* outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_DIE);
	outgoingPackets.push(outData);
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


void PlayerNetworkComponent::handleMovementPacket(InputMemoryBitStream& mPacket){
	//int t;
	//packet.Read(t);
	//if (testNum < t){
	float x;
	mPacket.Read(x);
	if (gameObjectRef->posX != x) render->setAnimation("walk");
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

void PlayerNetworkComponent::handleDeathPacket(){
	logic->becomeEgg();
}

void PlayerNetworkComponent::handleAbilityPacket(InputMemoryBitStream& aPacket){

}


void PlayerNetworkComponent::Update(){
	while (!incomingPackets.empty()){
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
			handleAbilityPacket(packet);
			break;
		case COMMAND_TYPE::CM_DIE:
			handleDeathPacket();
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