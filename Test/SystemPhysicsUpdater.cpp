#include "SystemPhysicsUpdater.h"


SystemPhysicsUpdater::SystemPhysicsUpdater()
{
}


SystemPhysicsUpdater::~SystemPhysicsUpdater()
{
}

void SystemPhysicsUpdater::PhysicsUpdate(std::vector<GameObject*> obj)
{

	for (int i = 0; i < obj.size(); i++){
		obj[i]->UpdateComponentByType(COMPONENT_PHYSICS);

	}
}