#include "FeatherObjectFactory.h"


FeatherObjectFactory::FeatherObjectFactory()
{
}


FeatherObjectFactory::~FeatherObjectFactory()
{
}

/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* FeatherObjectFactory::Spawn(GameObject* owner, uint64_t PID, float posX, float posY, float dx, float dy, float speed)
{
	GameObject* feather;
	FeatherRenderComponent* rend;
	FeatherLogicComponent* logic;
	FeatherPhysicsComponent* physics;
	//FeatherNetworkComponent* net;
	
	//std::cout << "owner: " << owner->ID << std::endl;

	if (GameObjects.dead_feathers.empty()){ //pool not large enough, add new feather
		feather = new GameObject();
		if (owner->isLocal)
			feather->isLocal = true;
		feather->ID = PID;
		feather->isAlive = true;
		feather->type = GAMEOBJECT_TYPE::OBJECT_FEATHER;
		feather->team = owner->team;
		feather->setPos(posX, posY);

		rend = new FeatherRenderComponent(feather);
		logic = new FeatherLogicComponent(feather);

		physics = new FeatherPhysicsComponent(feather, posX, posY, dx, dy, speed);
		logic->owner = owner;

	} else { //reuse feather from pool
		feather = GameObjects.dead_feathers.back();
		GameObjects.dead_feathers.pop_back();
		//std::cout << "Feather Pool Reusing " << feather->ID << " as " << PID << std::endl;
		feather->isLocal = (owner->isLocal) ? true : false;
		feather->ID = PID;
		feather->isAlive = true;
		feather->setPos(posX, posY);
		feather->team = owner->team;
		dynamic_cast<FeatherPhysicsComponent*>(feather->GetComponent(COMPONENT_PHYSICS))->init(posX, posY, dx, dy, speed);
		dynamic_cast<FeatherLogicComponent*>(feather->GetComponent(COMPONENT_LOGIC))->owner = owner;
	}

	//std::cout << feather->isLocal << std::endl;
	// Feather Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	

	return feather;
}