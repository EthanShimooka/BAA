#include "MidPlatObjectFactory.h"


MidPlatObjectFactory::MidPlatObjectFactory()
{
}


MidPlatObjectFactory::~MidPlatObjectFactory()
{
}


GameObject * MidPlatObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length){

	GameObject* platform = new GameObject();

	platform->ID = PID;
	platform->setPos(posX, posY);
	platform->isAlive = true;
	platform->type = GAMEOBJECT_TYPE::OBJECT_PLATFORM;

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	MidPlatRenderComponent* rend = new MidPlatRenderComponent(platform);

	MidPlatPhysicsComponent* physics = new MidPlatPhysicsComponent(platform);


	return platform;


}