#include "SystemNetworkUpdater.h"


SystemNetworkUpdater::SystemNetworkUpdater()
{
}


SystemNetworkUpdater::~SystemNetworkUpdater()
{
}

void SystemNetworkUpdater::NetworkUpdate(std::vector<GameObject*> obj)
{

	for (int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_NETWORK);

	}
}