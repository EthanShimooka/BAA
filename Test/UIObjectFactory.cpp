#include "UIObjectFactory.h"

UIObjectFactory::UIObjectFactory(){
}


UIObjectFactory::~UIObjectFactory(){
}

UIObject* UIObjectFactory::Spawn(UIType PID)
{

	UIObject* uiObject = new UIObject();

	uiObject->ID = PID;
	uiObject->setPos(0, 0);

	// Input Component nessasary for Local only.
	// Will need to differentiate eventually

	UIComponent* comp = new UIComponent();
	comp->uiObjectRef = uiObject;
	uiObject->AddComponent(COMPONENT_UI, comp);

	UIInputComponent* input = new UIInputComponent();
	input->uiObjectRef = uiObject;
	uiObject->AddComponent(COMPONENT_INPUT, input);

	// Player Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	UIRenderComponent* rend = new UIRenderComponent();
	rend->uiObjectRef = uiObject; //set components container refrence to this uiObject
	uiObject->AddComponent(COMPONENT_RENDER, rend);

	return uiObject;
}