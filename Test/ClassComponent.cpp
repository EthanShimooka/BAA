#include "ClassComponent.h"

ClassComponent::ClassComponent()
{
	speed = 20;
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

int ClassComponent::useAbility(){
	return 0;
}

int ClassComponent::getClass(){
	return 0;
}

//void ClassComponent::animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations){
//
//}