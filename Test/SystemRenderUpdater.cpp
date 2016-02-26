#include "SystemRenderUpdater.h"


SystemRenderUpdater::SystemRenderUpdater()
{
}


SystemRenderUpdater::~SystemRenderUpdater()
{
}

void SystemRenderUpdater::RenderUpdate(std::vector<GameObject*> rend)
{

	for (int i = 0; i < rend.size(); i++){
		rend[i]->UpdateComponentByType(COMPONENT_RENDER);

	}

}