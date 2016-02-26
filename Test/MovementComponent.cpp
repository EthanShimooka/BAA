#include "MovementComponent.h"


MovementComponent::MovementComponent()
{
	posX = 0.0;
	posY = 0.0;
}


MovementComponent::~MovementComponent()
{
}


void MovementComponent::Update()
{
}



void MovementComponent::SetPos(float x, float y){

	posX = x;
	posY = y;

}