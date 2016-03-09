#include "MinionObjectFactory.h"


MinionObjectFactory::MinionObjectFactory()
{
}


MinionObjectFactory::~MinionObjectFactory()
{
}


/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* MinionObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length, bool direction)
{

	GameObject* minion = new GameObject();

	minion->ID = PID;
	minion->isAlive = true;
	minion->type = GAMEOBJECT_TYPE::OBJECT_MINION;
	minion->setPos(posX, posY);

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	MinionRenderComponent* rend = new MinionRenderComponent(minion);

	MinionNetworkComponent* net = new MinionNetworkComponent(minion);

	MinionLogicComponent* logic = new MinionLogicComponent(minion);

	MinionPhysicsComponent* physics = new MinionPhysicsComponent(minion, posX, posY, length, direction);

	return minion;
}