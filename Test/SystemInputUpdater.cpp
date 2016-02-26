#include "SystemInputUpdater.h"


SystemInputUpdater::SystemInputUpdater()
{
}


SystemInputUpdater::~SystemInputUpdater()
{
}


void SystemInputUpdater::InputUpdate(std::vector<GameObject*> obj)
{

	for (int i = 0; i < obj.size(); i++){
		
		obj[i]->UpdateComponentByType(COMPONENT_INPUT);

	}

}