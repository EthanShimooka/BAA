#include "PlayerObjectFactory.h"


PlayerObjectFactory::PlayerObjectFactory()
{
}


PlayerObjectFactory::~PlayerObjectFactory()
{
}


GameObject* PlayerObjectFactory::Spawn(int PID)
{
	GameObject* player = new GameObject();

	player->ID = PID;


	InputComponent* input = new InputComponent();
	player->AddComponent(input);
	MovementComponent* move = new MovementComponent();
	player->AddComponent(move);
	PlayerRenderComponent* rend = new PlayerRenderComponent();
	player->AddComponent(rend);
	
	return player;
}