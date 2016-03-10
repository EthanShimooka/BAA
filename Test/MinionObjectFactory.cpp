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

	GameObject* minion;

	MinionRenderComponent* rend;
	MinionLogicComponent* logic;
	MinionPhysicsComponent* physics;
	MinionNetworkComponent* net;

	if (GameObjects.dead_minions.empty()) { //pool not large enough, add new minion
		minion = new GameObject();
		minion->ID = PID;
		minion->isAlive = true;
		minion->type = GAMEOBJECT_TYPE::OBJECT_MINION;
		minion->setPos(posX, posY);
		rend = new MinionRenderComponent(minion);
		logic = new MinionLogicComponent(minion, posX, posY, length, direction);
		physics = new MinionPhysicsComponent(minion);
		net = new MinionNetworkComponent(minion);
	} else { //reuse minion from pool
		minion = GameObjects.dead_minions.back();
		GameObjects.dead_minions.pop_back();
		std::cout << "Minion Pool Reusing " << minion->ID << " as " << PID << std::endl;
		minion->ID = PID;
		minion->isAlive = true;
		minion->type = GAMEOBJECT_TYPE::OBJECT_MINION;
		minion->setPos(posX, posY);
	}
	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	

	return minion;
}