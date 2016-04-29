#include "UIObjectFactory.h"

UIObjectFactory::UIObjectFactory(){
}

UIObjectFactory::~UIObjectFactory(){
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

	UITypeComponent* rend = new UITypeComponent();
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
	case OPTIONS_BUTTON:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(OPTIONS_BUTTON);
		break;
	case JOIN_BUTTON:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(JOIN_BUTTON);
		break;
	case TIMER:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(TIMER);
		break;
	case LOBBY_TIMER:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(LOBBY_TIMER);
		break;
	case BIRDSEED_BAR:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(BIRDSEED_BAR);
		break;
	case BIRDSEED_SHELL:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(BIRDSEED_SHELL);
		break;
	case CROSSHAIR:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(CROSSHAIR);
		break;
	case CHARGE_BAR:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(CHARGE_BAR);
		break;
	case CHARGE_SHELL:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(CHARGE_SHELL);
		break;
	case CANCEL_BUTTON:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(CANCEL_BUTTON);
		break;
	case BACK_BUTTON:
		rend->uiObjectRef->setPos((float)x, (float)y);
		rend->createUIType(BACK_BUTTON);
		break;
	}

	uiObject->AddComponent(COMPONENT_RENDER, rend);

	return uiObject;
}