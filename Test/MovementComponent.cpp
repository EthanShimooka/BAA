#include "MovementComponent.h"


MovementComponent::MovementComponent()
{

}


MovementComponent::~MovementComponent()
{
}


void MovementComponent::Update()
{
}



void MovementComponent::SetPos(float x, float y){

	gameObjectRef->posX = x;
	gameObjectRef->posY = y;

}