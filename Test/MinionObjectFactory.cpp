#include "MinionObjectFactory.h"


MinionObjectFactory::MinionObjectFactory()
{
}


MinionObjectFactory::~MinionObjectFactory()
{
}


/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* MinionObjectFactory::Spawn(uint64_t PID, float posX, float posY, int team)
{

	GameObject* minion;

	MinionRenderComponent* rend;
	MinionLogicComponent* logic;
	MinionPhysicsComponent* physics;
	MinionNetworkComponent* net;

	//if (GameObjects.dead_minions.empty()) { //pool not large enough, add new minion
		minion = new GameObject();
		minion->ID = PID;
		minion->isAlive = true;
		minion->type = GAMEOBJECT_TYPE::OBJECT_MINION;
		minion->setPos(posX, posY);
		minion->team = team;
		//std::cout << "Value of our \ : " << minion->team << "\n" << std::endl;

		rend = new MinionRenderComponent(minion, team);
		logic = new MinionLogicComponent(minion);
		physics = new MinionPhysicsComponent(minion, posX, posY, team);
		net = new MinionNetworkComponent(minion);
	//} else { //reuse minion from pool
	//	minion = GameObjects.dead_minions.back();
	//	GameObjects.dead_minions.pop_back();
	//	std::cout << "Minion Pool Reusing " << minion->ID << " as " << PID << std::endl;
	//	minion->ID = PID;
	//	minion->isAlive = true;
	//	minion->type = GAMEOBJECT_TYPE::OBJECT_MINION;
	//	minion->setPos(posX, posY);
	//}
	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

/*	MinionRenderComponent* rend = new MinionRenderComponent(minion);

	MinionNetworkComponent* net = new MinionNetworkComponent(minion);

	MinionLogicComponent* logic = new MinionLogicComponent(minion);

	MinionPhysicsComponent* physics = new MinionPhysicsComponent(minion, posX, posY, length, direction);*/


	return minion;
}