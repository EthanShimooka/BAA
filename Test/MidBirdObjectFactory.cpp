#include "MidBirdObjectFactory.h"


MidBirdObjectFactory::MidBirdObjectFactory()
{
}


MidBirdObjectFactory::~MidBirdObjectFactory()
{
}



GameObject* MidBirdObjectFactory::Spawn(uint64_t PID, float posX, float posY, int team)
{

	GameObject* bird = new GameObject();

	bird->ID = PID;
	bird->setPos(posX, posY);
	bird->isAlive = true;
	//bird->type = GAMEOBJECT_TYPE::OBJECT_WELL;
	if (team == TEAM_PURPLE)
		bird->flipV = true;


	MidBirdRenderComponent* rend = new MidBirdRenderComponent(bird);

	return bird;
}