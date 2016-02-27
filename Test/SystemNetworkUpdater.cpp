#include "SystemNetworkUpdater.h"


SystemNetworkUpdater::SystemNetworkUpdater()
{
}


SystemNetworkUpdater::~SystemNetworkUpdater()
{
}

void SystemNetworkUpdater::NetworkUpdate(std::vector<GameObject*> obj)
{

	for (unsigned int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_NETWORK);

	}
}