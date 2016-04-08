#include "SystemClassUpdater.h"


SystemClassUpdater::SystemClassUpdater()
{
}


SystemClassUpdater::~SystemClassUpdater()
{
}

void SystemClassUpdater::ClassUpdate(std::vector<GameObject*> obj)
{

	for (unsigned int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_CLASS);

	}
}