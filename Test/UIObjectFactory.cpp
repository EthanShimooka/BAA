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
		rend->uiObjectRef->setPos((float)w / 2 + 25, (float)h / 2 - 25);
		rend->createUIType(PLAY_BUTTON);
		break;
	case JOIN_BUTTON:
		rend->uiObjectRef->setPos((float)w / 2 - 125, (float)h / 2 - 25);
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
		rend->uiObjectRef->setPos((float)w / 2 + 25, (float)h / 2 - 25);
		rend->createUIType(OPTIONS_BUTTON);
		break;
	case TIMER:
		rend->createUIType(TIMER);
		break;
	case LOBBY_TIMER:
		rend->createUIType(LOBBY_TIMER);
		break;
	case BIRDSEED_BAR:
		rend->createUIType(BIRDSEED_BAR);
		break;
	case BIRDSEED_SHELL:
		rend->createUIType(BIRDSEED_SHELL);
		break;
	case CROSSHAIR:
		rend->createUIType(CROSSHAIR);
		break;
	case CHARGE_BAR:
		rend->createUIType(CHARGE_BAR);
		break;
	case CHARGE_SHELL:
		rend->createUIType(CHARGE_SHELL);
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
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(READY_BUTTON);
		break;
	case PLAYER_SLOT:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(PLAYER_SLOT);
		break;
	case CHICKEN:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(CHICKEN);
		break;
	case PEACOCK:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(PEACOCK);
		break;
	case TURKEY:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(TURKEY);
		break;
	case QUAIL:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(QUAIL);
		break;
	case FLAMINGO:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(FLAMINGO);
		break;
	case EAGLE:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(EAGLE);
		break;
	case MENU_NAME:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(MENU_NAME);
		break;
	case INVITE_BUTTON:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(INVITE_BUTTON);
		break;
	}

	uiObject->AddComponent(COMPONENT_RENDER, rend);

	return uiObject;
}