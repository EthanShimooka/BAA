#include "PlatformObjectFactory.h"


PlatformObjectFactory::PlatformObjectFactory()
{
}


PlatformObjectFactory::~PlatformObjectFactory()
{
}

/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* PlatformObjectFactory::Spawn(uint64_t PID)
{

	GameObject* platform = new GameObject();

	platform->ID = PID;

	platform->type = GAMEOBJECT_TYPE::OBJECT_PLATFORM;

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	PlatformRenderComponent* rend = new PlatformRenderComponent(platform);
	//rend->gameObjectRef = minion; //set components container refrence to this gameObject
	//minion->AddComponent(COMPONENT_RENDER, rend);

	PlatformPhysicsComponent* physics = new PlatformPhysicsComponent(platform);
	//physics->gameObjectRef = minion; //set components container refrence to this gameObject
	//physics->init();
	//minion->AddComponent(COMPONENT_PHYSICS, physics);

	return platform;
}