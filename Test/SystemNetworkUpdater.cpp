#include "SystemNetworkUpdater.h"
#include "NetworkComponent.h"
#include "include/network/NetworkManager.h"


SystemNetworkUpdater::SystemNetworkUpdater()
{
}


SystemNetworkUpdater::~SystemNetworkUpdater()
{
}

void SystemNetworkUpdater::NetworkUpdate(std::vector<GameObject*> obj)
{
	for (unsigned int i = 0; i < NetworkManager::sInstance->test.size(); ++i){
		uint64_t UID;
		NetworkManager::sInstance->test.front().Read(UID);

		// if trying to spawn minion
		if (UID == -1){
			uint64_t id;
			uint8_t team;
			NetworkManager::sInstance->test.front().Read(id);
			NetworkManager::sInstance->test.front().Read(team);
			float xPos = (team == TEAM_PURPLE) ? 900 : -900;
			GameObjects.AddObject(mFactory.Spawn(id, xPos, 0, (int)team));
			continue;
		}
		// update other entities
		for (unsigned int i = 0; i < obj.size(); ++i){
			if (obj[i]->ID == UID){
				NetworkComponent* net = dynamic_cast<NetworkComponent*>(obj[i]->GetComponent(COMPONENT_NETWORK));
				if (net)
					net->incomingPackets.push(NetworkManager::sInstance->test.front());
			}
		}
		NetworkManager::sInstance->test.pop();
	}


	for (unsigned int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_NETWORK);
	}
}