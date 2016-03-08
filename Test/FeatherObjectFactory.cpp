#include "FeatherObjectFactory.h"


FeatherObjectFactory::FeatherObjectFactory()
{
}


FeatherObjectFactory::~FeatherObjectFactory()
{
}

/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* FeatherObjectFactory::Spawn(uint64_t PID, float posX, float posY, float dx, float dy)
{

	GameObject* feather = new GameObject();

	feather->ID = PID;
	feather->isAlive = true;
	feather->type = GAMEOBJECT_TYPE::OBJECT_FEATHER;
	feather->setPos(posX, posY);

	// Feather Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	FeatherRenderComponent* rend = new FeatherRenderComponent(feather);

	FeatherNetworkComponent* net = new FeatherNetworkComponent(feather);

	FeatherLogicComponent* logic = new FeatherLogicComponent(feather, posX, posY, dx, dy);

	FeatherPhysicsComponent* physics = new FeatherPhysicsComponent(feather);

	return feather;
}