#include "ClassComponent.h"

ClassComponent::ClassComponent()
{
	isChicken = false;
	isEagle = false;
	isQuail = false;
	isPeacock = false;
	isTurkey = false;
	isFlamingo = false;
	speed = 16;
	jumpSpeed = 16;
	width = 1.33f;
	height = 1.35f;
	seedRequired = 8;
	featherSpeed = 70.0f;
	featherWidth = 1;
	featherHeight = 1;
	abilityCooldown = 15;
}

ClassComponent::~ClassComponent()
{
	std::cout << "destructing base class" << std::endl;
}


void ClassComponent::Update()
{

}

int ClassComponent::useAbility(){
	return 0;
}

void ClassComponent::writeNetAbility(){
	std::cout << "class write" << std::endl;
}

void ClassComponent::readNetAbility(InputMemoryBitStream& aPacket){
	std::cout << "class read" << std::endl;
}


int ClassComponent::getClass(){
	return 0;
}
