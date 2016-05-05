#include "LauncherLogicComponent.h"


LauncherLogicComponent::LauncherLogicComponent(GameObject * launcher)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


LauncherLogicComponent::~LauncherLogicComponent()
{
}

void LauncherLogicComponent::showButton()
{
	LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	render->allObjs["launcher"]->visible = true;
	std::cout << "shiggle buzz" << std::endl;


}

void LauncherLogicComponent::triggerButton()
{

}

void LauncherLogicComponent::Update()
{

}

//void Launch