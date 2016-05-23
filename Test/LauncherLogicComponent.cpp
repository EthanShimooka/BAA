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
	//render->allObjs["launcher1"]->setVisible(true);
	//render->objRef = render->allObjs["launcher1"];
	launchable = true;
}

void LauncherLogicComponent::triggerButton()
{
	LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	//render->allObjs["launcher2"]->setVisible(false);
	timeSinceToggle = clock();

}

void LauncherLogicComponent::hideButton()
{
	LauncherRenderComponent * render = dynamic_cast<LauncherRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	//render->allObjs["launcher2"]->setVisible(false);
	//render->allObjs["launcher1"]->setVisible(false);
	//render->objRef = render->allObjs["base"];
	timeSinceToggle = 0;
	clockDiff = 0;

	launchable = false;
}


void LauncherLogicComponent::Update()
{
	/*
	clockDiff++;
	clockDiff = clockDiff - timeSinceToggle;
	//std::cout << "Clock DIFF : " << clockDiff << std::endl;

	if (launchable){
		unsigned timeElapsed = clockDiff / (CLOCKS_PER_SEC / 1000);
		//std::cout << "time elapsed : " << timeElapsed << std::endl;
		if (timeElapsed > 10000){
			hideButton();
		}
	}
	*/
}

//void Launch