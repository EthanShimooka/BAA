#include "SystemRenderUpdater.h"


SystemRenderUpdater::SystemRenderUpdater()
{
}


SystemRenderUpdater::~SystemRenderUpdater()
{
}

void SystemRenderUpdater::RenderUpdate(std::vector<GameObject*> rend)
{

	for (unsigned int i = 0; i < rend.size(); i++){
		rend[i]->UpdateComponentByType(COMPONENT_RENDER);

	}
}

void SystemRenderUpdater::RenderUpdate(std::vector<UIObject*> rend)
{

	for (unsigned int i = 0; i < rend.size(); i++){
		rend[i]->UpdateComponentByType(COMPONENT_RENDER);

	}
}