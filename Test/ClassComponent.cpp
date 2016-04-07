#include "ClassComponent.h"


ClassComponent::ClassComponent()
{
	speed = 15;
	width = 2.7;
	height = 2.7;
	seedRequired = 5;
	featherSpeed = 1.0 / 7.0;
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