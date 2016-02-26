#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	visible = true;

}


RenderComponent::~RenderComponent()
{
}


/// Assign a Diffrent SDL render Object

void RenderComponent::AssignSprite(SDLRenderObject* rend){

	objRef = rend;
}


/// Updates SDL render Object from Move Data in game

void RenderComponent::Update(){

	//Updates the related SDLRenderObject with the player's values
	//The SDLRenderObject is was is showed on screen, but is only 
	//a 'figurehead' for the player object 

	objRef->posX = gameObjectRef->posX;
	objRef->posY = gameObjectRef->posY;
	objRef->rotation = gameObjectRef->rotation;
	objRef->visible = visible;

	//there is most likely more attributes to send over. update as needed
}


