#include "ClassComponent.h"

ClassComponent::ClassComponent()
{
	birdseedFullPlayed = false;
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
	if (currBirdseed == seedRequired && !birdseedFullPlayed) {
		AudioManager* audioMan = AudioManager::getAudioInstance();
		audioMan->playByName("birdseedfullsfx.ogg");
		birdseedFullPlayed = true;
		//Possible need to call superclass's Update in each individual ClassComponent's Update
	}
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

void ClassComponent::playAbilityUseSound(){
	AudioManager* audioMan = AudioManager::getAudioInstance();
	audioMan->playByName("abilityusesfx.ogg");
}

void ClassComponent::birdseedFullPlayed(){
	AudioManager* audioMan = AudioManager::getAudioInstance();
	audioMan->playByName("birdseedfullsfx.ogg");
}

int ClassComponent::getClass(){
	return 0;
}

void ClassComponent::setTimer(){
	timer = ((float)clock()) / CLOCKS_PER_SEC + timerLength;
}

bool ClassComponent::endTimer(){
	// if timer is 0 no need to find the difference
	if (timer == 0) return true;
	if (timer <= ((float)clock()) / CLOCKS_PER_SEC){
		timer = 0;
		return true;
	}
	return false;
}