#include "UIRenderComponent.h"
#include "config.h"



UIRenderComponent::UIRenderComponent(){
}

UIRenderComponent::~UIRenderComponent(){
}

void UIRenderComponent::Update(){

	//Updates the related SDLRenderObject with the player's values
	//The SDLRenderObject is was is showed on screen, but is only 
	//a 'figurehead' for the player object 
	if (uiObjectRef->changePicture && uiObjectRef->ID == PLAYER_SLOT){
		ResourceManager* ResMan = ResourceManager::GetResourceManager();
		objRef->setResourceObject((RenderResource*)ResMan->findResourcebyID(uiObjectRef->changeTo));
	}
	else if (uiObjectRef->hoverPicture && uiObjectRef->ID == PLAYER_SLOT){
		ResourceManager* ResMan = ResourceManager::GetResourceManager();
		RenderManager* rendMan = RenderManager::getRenderManager();
		int w, h;
		rendMan->getWindowSize(&w, &h);
		objRef->setResourceObject((RenderResource*)ResMan->findResourcebyID(uiObjectRef->changeTo));
		if (uiObjectRef->bottom){
			objRef->posY = h - objRef->getHeight();
		}
		else{
			objRef->posY = uiObjectRef->posY;
		}
	}
	else if (!uiObjectRef->hoverPicture && uiObjectRef->ID == PLAYER_SLOT){
		ResourceManager* ResMan = ResourceManager::GetResourceManager();
		objRef->setResourceObject((RenderResource*)ResMan->findResourcebyID(28));
		objRef->posY = uiObjectRef->posY;
	}
	else{
		objRef->posY = uiObjectRef->posY;
	}
	objRef->posX = uiObjectRef->posX;
	objRef->rotation = uiObjectRef->rotation;
	objRef->visible = uiObjectRef->visible;
	objRef->setScale(uiObjectRef->scale);
	//std::cout << "dude: " << objRef->getScaleX() << std::endl;

	//there is most likely more attributes to send over. update as needed
}
