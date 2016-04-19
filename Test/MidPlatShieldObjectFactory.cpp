#include "MidPlatShieldObjectFactory.h"


MidPlatShieldObjectFactory::MidPlatShieldObjectFactory()
{



}


MidPlatShieldObjectFactory::~MidPlatShieldObjectFactory()
{


}


GameObject * MidPlatShieldObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length){

	GameObject* platform = new GameObject();

	platform->ID = PID;
	platform->setPos(posX, posY);
	platform->isAlive = true;
	platform->type = GAMEOBJECT_TYPE::OBJECT_SWITCH;

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	MidPlatShieldRenderComponent* rend = new MidPlatShieldRenderComponent(platform);

	MidPlatShieldPhysicsComponent* physics = new MidPlatShieldPhysicsComponent(platform);

	return platform;



}