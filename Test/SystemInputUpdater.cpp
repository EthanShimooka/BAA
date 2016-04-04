#include "SystemInputUpdater.h"


SystemInputUpdater::SystemInputUpdater()
{
}


SystemInputUpdater::~SystemInputUpdater()
{
}


void SystemInputUpdater::InputUpdate(std::vector<GameObject*> obj)
{

	for (unsigned int i = 0; i < obj.size(); i++){	
		obj[i]->UpdateComponentByType(COMPONENT_INPUT);

	}
}

void SystemInputUpdater::InputUpdate(std::vector<UIObject*> obj)
{

	for (unsigned int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_INPUT);

	}
}