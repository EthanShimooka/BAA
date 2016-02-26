#include "PlayerObjectFactory.h"

PlayerObjectFactory::PlayerObjectFactory()
{
}


PlayerObjectFactory::~PlayerObjectFactory()
{
}


/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* PlayerObjectFactory::Spawn(int PID)
{

	GameObject* player = new GameObject();

	player->ID = PID;

	// Input Component nessasary for Local only.
	// Will need to differentiate eventually

	InputComponent* input = new InputComponent();
	input->gameObjectRef = player;
	player->AddComponent(COMPONENT_INPUT,input);

	// Movement Component nessasary for all objects that move
	// Player moves, therefore, it is included

	MovementComponent* move = new MovementComponent();
	move->gameObjectRef = player;
	player->AddComponent(COMPONENT_MOVEMENT,move);

	// Player Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	PlayerRenderComponent* rend = new PlayerRenderComponent();
	rend->gameObjectRef = player;
	player->AddComponent(COMPONENT_RENDER,rend);
	
	return player;
}