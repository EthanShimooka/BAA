#include "LauncherLogicComponent.h"


LauncherLogicComponent::LauncherLogicComponent(GameObject * launcher)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


LauncherLogicComponent::~LauncherLogicComponent()
{
}


//void Launch