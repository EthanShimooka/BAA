#include "PlayerNetworkComponent.h"


PlayerNetworkComponent::PlayerNetworkComponent()
{
}


PlayerNetworkComponent::~PlayerNetworkComponent()
{
}


void PlayerNetworkComponent::Update(){
	while (!incomingPackets.empty()){
		InputMemoryBitStream packet = incomingPackets.front();
		int mCommand;

		PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));


		packet.Read(mCommand);
		switch (mCommand){
		case CM_INVALID:
			//handle 
			break;
		case CM_MOVE:
			//handle movement
			//int t;
			//packet.Read(t);
			//if (testNum < t){
			packet.Read(gameObjectRef->posX);
			packet.Read(gameObjectRef->posY);
			//testNum = t;
			//}
			break;
		case CM_ATTACK:
			uint64_t ID;
			float initialX, initialY;
			int destX, destY;
			packet.Read(ID);
			packet.Read(initialX);
			packet.Read(initialY);
			packet.Read(destX);
			packet.Read(destY);
			//
			logic->spawnFeather(ID, initialX, initialY, destX, destY);;
			break;
		case CM_ABILITY:
			//handle 
			break;
		case CM_DIE:
			//handle 
			break;
		case CM_JUMP:
			//handle 
			break;
		default:
			cout << gameObjectRef->ID << ", " << mCommand << ": There is no such command!!" << endl;
		}

		incomingPackets.pop();
	}

	while (!outgoingPackets.empty()){
		OutputMemoryBitStream* outData = outgoingPackets.front();
		NetworkManager::sInstance->sendPacketToAllPeers(*outData);
		outgoingPackets.pop();
	}

	if (gameObjectRef->ID == NetworkManager::sInstance->GetMyPlayerId()){
		OutputMemoryBitStream outData;
		outData.Write(NetworkManager::sInstance->kPosCC);
		outData.Write(gameObjectRef->ID);
		outData.Write(1);
		//outData.Write(testNum++);
		outData.Write(gameObjectRef->posX);
		outData.Write(gameObjectRef->posY);
		NetworkManager::sInstance->sendPacketToAllPeers(outData);
	}
}