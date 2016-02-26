#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	visible = true;

}


RenderComponent::~RenderComponent()
{
}


void RenderComponent::AssignSprite(SDLRenderObject* rend){

	objRef = rend;
}


void RenderComponent::Update(MovementComponent move){

	//Updates the related SDLRenderObject with the player's values
	//The SDLRenderObject is was is showed on screen, but is only 
	//a 'figurehead' for the player object 

	objRef->posX = move.posX;
	objRef->posY = move.posY;
	objRef->rotation = move.rotation;
	objRef->visible = visible;

	//there is most likely more attributes to send over. update as needed
}


