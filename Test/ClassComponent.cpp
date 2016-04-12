#include "ClassComponent.h"

ClassComponent::ClassComponent()
{
	speed = 15;
	width = 1.33f;
	height = 1.35f;
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

//void ClassComponent::animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations){
//
//}