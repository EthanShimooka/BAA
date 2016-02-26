#include "SystemLogicUpdater.h"


SystemLogicUpdater::SystemLogicUpdater()
{
}


SystemLogicUpdater::~SystemLogicUpdater()
{
}


void SystemLogicUpdater::LogicUpdate(std::vector<GameObject*> obj)
{

	for (int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_LOGIC);

	}
}