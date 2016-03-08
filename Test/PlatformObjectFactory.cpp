#include "PlatformObjectFactory.h"


PlatformObjectFactory::PlatformObjectFactory()
{
}


PlatformObjectFactory::~PlatformObjectFactory()
{
}

/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* PlatformObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length)
{

	GameObject* platform = new GameObject();

	platform->ID = PID;
	platform->setPos(posX, posY);
	platform->isAlive = true;
	platform->type = GAMEOBJECT_TYPE::OBJECT_PLATFORM;

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	PlatformRenderComponent* rend = new PlatformRenderComponent(platform);

	PlatformPhysicsComponent* physics = new PlatformPhysicsComponent(platform);

	return platform;
}