#include "PlayerObjectFactory.h"

PlayerObjectFactory::PlayerObjectFactory()
{
}


PlayerObjectFactory::~PlayerObjectFactory()
{
}


/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* PlayerObjectFactory::Spawn(uint64_t PID, bool local)
{

	GameObject* player = new GameObject();
	player->ID = PID;
	player->isAlive = true;
	player->type = GAMEOBJECT_TYPE::OBJECT_PLAYER;

	// Input Component nessasary for Local only.
	// Will need to differentiate eventually

	if (local){
		PlayerInputComponent* input = new PlayerInputComponent(player);
		//input->gameObjectRef = player;
		//player->AddComponent(COMPONENT_INPUT, input);
	}

	// Movement Component nessasary for all objects that move
	// Player moves, therefore, it is included

	//MovementComponent* move = new MovementComponent();
	//move->gameObjectRef = player; //set components container refrence to this gameObject
	//player->AddComponent(COMPONENT_MOVEMENT,move);

	// Player Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	PlayerRenderComponent* rend = new PlayerRenderComponent(player);
	//rend->gameObjectRef = player; //set components container refrence to this gameObject
	//player->AddComponent(COMPONENT_RENDER,rend);


	


	PlayerLogicComponent* logic = new PlayerLogicComponent(player);
	//logic->gameObjectRef = player; //set components container refrence to this gameObject
	//player->AddComponent(COMPONENT_LOGIC, logic);

	PlayerPhysicsComponent* physics = new PlayerPhysicsComponent(player);
	//physics->gameObjectRef = player; //set components container refrence to this gameObject
	//player->AddComponent(COMPONENT_PHYSICS, physics);

	PlayerNetworkComponent* net = new PlayerNetworkComponent(player);
	//net->gameObjectRef = player; //set components container refrence to this gameObject
	//player->AddComponent(COMPONENT_NETWORK, net);

	
	return player;
}