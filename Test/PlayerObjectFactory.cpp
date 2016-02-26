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
	player->AddComponent(input);

	// Movement Component nessasary for all objects that move
	// Player moves, therefore, it is included

	MovementComponent* move = new MovementComponent();
	player->AddComponent(move);

	// Player Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	PlayerRenderComponent* rend = new PlayerRenderComponent();
	player->AddComponent(rend);
	
	return player;
}