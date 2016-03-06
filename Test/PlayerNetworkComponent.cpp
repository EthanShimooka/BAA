#include "PlayerNetworkComponent.h"


PlayerNetworkComponent::PlayerNetworkComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	//PlayerLogicComponent *
	//logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
}


PlayerNetworkComponent::~PlayerNetworkComponent()
{
}

void PlayerNetworkComponent::createFeatherPacket(uint64_t ID, int finalX, int finalY){
	OutputMemoryBitStream *featherPacket = new OutputMemoryBitStream();
	featherPacket->Write(NetworkManager::sInstance->kPosCC);
	featherPacket->Write(gameObjectRef->ID);
	featherPacket->Write((int)CM_ATTACK);
	featherPacket->Write(ID);
	featherPacket->Write(gameObjectRef->posX);
	featherPacket->Write(gameObjectRef->posY);
	featherPacket->Write(finalX);
	featherPacket->Write(finalY);
	//cout << 0 << ", " << gameObjectRef->posX << ", " << gameObjectRef->posY << ", " << input->getMouseX() << ", " << input->getMouseY() << endl;
	outgoingPackets.push(featherPacket);
}

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

void PlayerNetworkComponent::Update(){
	while (!incomingPackets.empty()){
		PlayerLogicComponent *logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;

		packet.Read(mCommand);
		switch (mCommand){
		case COMMAND_TYPE::CM_INVALID:
			//handle 
			break;
		case COMMAND_TYPE::CM_MOVE:
			//handle movement
			//int t;
			//packet.Read(t);
			//if (testNum < t){
			float x;
			packet.Read(x);
			
			if (gameObjectRef->posX > x){
				gameObjectRef->flipH = true;
			}
			else if (gameObjectRef->posX < x){
				gameObjectRef->flipH = false;
			}
			gameObjectRef->posX = x;
			//packet.Read(gameObjectRef->posX);
			packet.Read(gameObjectRef->posY);
			//testNum = t;
			//}
			break;
		case COMMAND_TYPE::CM_ATTACK:
			uint64_t ID;
			float initialX, initialY;
			int destX, destY;
			packet.Read(ID);
			packet.Read(initialX);
			packet.Read(initialY);
			packet.Read(destX);
			packet.Read(destY);
			logic->spawnFeather(ID, initialX, initialY, destX, destY);
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

	while (!outgoingPackets.empty()){
		OutputMemoryBitStream* outData = outgoingPackets.front();
		NetworkManager::sInstance->sendPacketToAllPeers(*outData);
		delete outData;
		outgoingPackets.pop();
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