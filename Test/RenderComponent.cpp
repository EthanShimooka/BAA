#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	visible = true;
	lasttime = clock();
	progress = 0;

}


RenderComponent::~RenderComponent()
{
}

/// Assign a Diffrent SDL render Object

void RenderComponent::AssignSprite(SDLRenderObject* rend){

	objRef = rend;
}


/// Sets the next animation given a string value found in a hashtable

void RenderComponent::setAnimation(string name){
	if (animations.count(name)){
		nextAnimation = animations[name];
	}
}

/// The general animation function, that alters the object's

void RenderComponent::animate(){
	unsigned int currenttime = clock();
	if (currentAnimation){
		progress += currenttime - lasttime;
		while (progress >= currentAnimation->duration){
			progress -= currentAnimation->duration;
			if (nextAnimation){
				currentAnimation = nextAnimation;
				//queue next animation through a switch statement
			}
			else{
				currentAnimation = animations["idle"];
			}
		}
		float curr = currentAnimation->lengthConversion(progress);
		auto len = currentAnimation->duration;
		currentAnimation->animate(curr);
	}
	lasttime = currenttime;
}

/// Updates SDL render Object from Move Data in game

void RenderComponent::Update(){

	//Updates the related SDLRenderObject with the player's values
	//The SDLRenderObject is was is showed on screen, but is only 
	//a 'figurehead' for the player object 

	objRef->posX = gameObjectRef->posX;
	objRef->posY = gameObjectRef->posY;
	objRef->flipH = gameObjectRef->flipH;
	objRef->flipV = gameObjectRef->flipV;
	objRef->rotation = gameObjectRef->rotation;
	objRef->visible = visible;

	//there is most likely more attributes to send over. update as needed
}


