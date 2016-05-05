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
	/*
	LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	render->allObjs["launcher"]->visible = true;


	*/

	launchable = true;

}

void LauncherLogicComponent::triggerButton()
{
	LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	render->allObjs["launcher2"]->setVisible(false);

}

void LauncherLogicComponent::hideButton()
{
	LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	render->allObjs["launcher2"]->setVisible(false);
	render->allObjs["launcher1"]->setVisible(false);
	render->objRef = render->allObjs["base"];

}


void LauncherLogicComponent::Update()
{

	if (launchable){
		LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
		render->allObjs["launcher1"]->setVisible(true);
		render->objRef = render->allObjs["launcher1"];
	}	else{
		LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));

		render->allObjs["launcher1"]->setVisible(false);
		render->objRef = render->allObjs["base"];

	}

}

//void Launch