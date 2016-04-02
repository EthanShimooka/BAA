#include "UIObjectFactory.h"

UIObjectFactory::UIObjectFactory(){
}


UIObjectFactory::~UIObjectFactory(){
}

UIObject* UIObjectFactory::Spawn(UIType PID)
{

	UIObject* uiObject = new UIObject();

	uiObject->ID = PID;

	// Input Component nessasary for Local only.
	// Will need to differentiate eventually
	RenderManager* rendMan = RenderManager::getRenderManager();

	int w, h;
	rendMan->getWindowSize(&w, &h);

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
	switch (PID){
	case PLAY_BUTTON:
		rend->uiObjectRef->setPos(w / 2 - 125, h / 2 - 25);
		rend->createUIType(PLAY_BUTTON);
		break;
	case JOIN_BUTTON:
		rend->uiObjectRef->setPos(w / 2 - 125, h / 2 - 25);
		rend->createUIType(JOIN_BUTTON);
		// in here we will want to add some functionallity to
		// join a lobby or set a flag to join a lobby.
		break;
	case CANCEL_BUTTON:
		rend->createUIType(CANCEL_BUTTON);
		break;
	case BACK_BUTTON:
		rend->createUIType(BACK_BUTTON);
		break;
	case OPTIONS_BUTTON:
		//change when button is created
		rend->uiObjectRef->setPos(w / 2 - 125, h / 2 - 25);
		rend->createUIType(OPTIONS_BUTTON);
		break;
	case SCORE:
		break;
	case TIMER:
		break;
	}
	uiObject->AddComponent(COMPONENT_RENDER, rend);

	return uiObject;
}

UIObject* UIObjectFactory::Spawn(UIType PID, int x, int y){

	UIObject* uiObject = new UIObject();

	uiObject->ID = PID;

	// Input Component nessasary for Local only.
	// Will need to differentiate eventually
	RenderManager* rendMan = RenderManager::getRenderManager();

	int w, h;
	rendMan->getWindowSize(&w, &h);

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

	switch (PID){
	case READY_BUTTON:
		rend->uiObjectRef->setPos(x, y);
		rend->createUIType(READY_BUTTON);
		break;
	case PLAYER_SLOT:
		rend->uiObjectRef->setPos(x, y);
		rend->createUIType(PLAYER_SLOT);
		break;
	}

	uiObject->AddComponent(COMPONENT_RENDER, rend);

	return uiObject;
}