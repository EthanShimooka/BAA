#include "SystemUIUpdater.h"


SystemUIUpdater::SystemUIUpdater()
{
}


SystemUIUpdater::~SystemUIUpdater()
{
}

void SystemUIUpdater::UIUpdate(std::vector<UIObject*> obj)
{

	for (unsigned int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_UI);
	}
}