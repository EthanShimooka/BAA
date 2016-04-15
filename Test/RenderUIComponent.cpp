#include "RenderUIComponent.h"


RenderUIComponent::RenderUIComponent(){
	visible = true;
}


RenderUIComponent::~RenderUIComponent(){
}


/// Assign a Diffrent SDL render Object
void RenderUIComponent::AssignSprite(SDLRenderObject* rend){

	objRef = rend;
}


/// Updates SDL render Object from Move Data in game

void RenderUIComponent::Update(){

	//Updates the related SDLRenderObject with the player's values
	//The SDLRenderObject is was is showed on screen, but is only 
	//a 'figurehead' for the player object 
	if (uiObjectRef->ID == PLAYER_SLOT && uiObjectRef->changePicture){
		ResourceManager* ResMan = ResourceManager::GetResourceManager();
		objRef->setResourceObject((RenderResource*)ResMan->findResourcebyID(uiObjectRef->ID));
	}

	if (uiObjectRef->ID == PLAYER_SLOT && uiObjectRef->hoverPicture){
		ResourceManager* ResMan = ResourceManager::GetResourceManager();
		objRef->setResourceObject((RenderResource*)ResMan->findResourcebyID(uiObjectRef->ID));
	}
	else if (uiObjectRef->ID == PLAYER_SLOT && !uiObjectRef->hoverPicture){
		ResourceManager* ResMan = ResourceManager::GetResourceManager();
		objRef->setResourceObject((RenderResource*)ResMan->findResourcebyID(28));
	}

	objRef->posX = uiObjectRef->posX;
	objRef->posY = uiObjectRef->posY;
	objRef->rotation = uiObjectRef->rotation;
	objRef->visible = uiObjectRef->visible;
	objRef->setScale(uiObjectRef->scale);

	//there is most likely more attributes to send over. update as needed
}


