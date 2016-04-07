#include "FeatherObjectFactory.h"


FeatherObjectFactory::FeatherObjectFactory()
{
}


FeatherObjectFactory::~FeatherObjectFactory()
{
}

/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* FeatherObjectFactory::Spawn(uint64_t PID, float posX, float posY, float dx, float dy, float chargeTime, float speed)
{
	GameObject* feather;
	FeatherRenderComponent* rend;
	FeatherLogicComponent* logic;
	FeatherPhysicsComponent* physics;
	//FeatherNetworkComponent* net;

	if (GameObjects.dead_feathers.empty()){ //pool not large enough, add new feather
		feather = new GameObject();
		feather->ID = PID;
		feather->isAlive = true;
		feather->type = GAMEOBJECT_TYPE::OBJECT_FEATHER;
		feather->setPos(posX, posY);
		rend = new FeatherRenderComponent(feather);
		logic = new FeatherLogicComponent(feather);
		physics = new FeatherPhysicsComponent(feather, posX, posY, dx, dy, chargeTime, speed);
		//net = new FeatherNetworkComponent(feather);
	
	} else { //reuse feather from pool
		feather = GameObjects.dead_feathers.back();
		GameObjects.dead_feathers.pop_back();
		std::cout << "Feather Pool Reusing " << feather->ID << " as " << PID << std::endl;
		feather->ID = PID;
		feather->isAlive = true;
		feather->setPos(posX, posY);
		dynamic_cast<FeatherPhysicsComponent*>(feather->GetComponent(COMPONENT_PHYSICS))->init(posX, posY, dx, dy, chargeTime, speed);
	}

	// Feather Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	

	return feather;
}