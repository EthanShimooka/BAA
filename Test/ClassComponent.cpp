#include "ClassComponent.h"


ClassComponent::ClassComponent()
{
	speed = 15;
	width = 2.7f;
	height = 2.7f;
	seedRequired = 5;
	featherSpeed = 1.0f / 7.0f;
	featherWidth = 1;
	featherHeight = 1;
	abilityCooldown = 15;
}


ClassComponent::~ClassComponent()
{
}


void ClassComponent::Update()
{

}

void ClassComponent::animation(SDLRenderObject* objRef, map_obj& allObjs, map_anim& animations){

}