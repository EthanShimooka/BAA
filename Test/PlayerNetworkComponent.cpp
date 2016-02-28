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
		case CM_ABILITY:
			//handle 
			break;
		case CM_ATTACK:
			//handle 
			break;
		case CM_DIE:
			//handle 
			break;
		case CM_JUMP:
			//handle 
			break;
		default:
			cout << gameObjectRef->ID << ": There is no such command!!" << endl;
		}

		incomingPackets.pop();
	}

	/*while (!outgoingPackets.empty()){
		OutputMemoryBitStream outData = outgoingPackets.front();
		NetworkManager::sInstance->sendPacketToAllPeers(outData);
		outgoingPackets.pop();
	}*/

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