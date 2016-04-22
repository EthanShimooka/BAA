#include "MidPlatShieldLogicComponent.h"


MidPlatShieldLogicComponent::MidPlatShieldLogicComponent()
{

}


MidPlatShieldLogicComponent::~MidPlatShieldLogicComponent()
{
}



void MidPlatShieldLogicComponent::ToggleShield()
{
	AudioManager* audioMan = AudioManager::getAudioInstance();
	audioMan->playByName("SFX_Shield.wav");



}