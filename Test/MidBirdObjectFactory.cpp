#include "MidBirdObjectFactory.h"


MidBirdObjectFactory::MidBirdObjectFactory()
{
}


MidBirdObjectFactory::~MidBirdObjectFactory()
{
}



GameObject* MidBirdObjectFactory::Spawn(uint64_t PID, float posX, float posY)
{

	GameObject* bird = new GameObject();

	bird->ID = PID;
	bird->setPos(posX, posY);
	bird->isAlive = true;
	//bird->type = GAMEOBJECT_TYPE::OBJECT_WELL;

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	MidBirdRenderComponent* rend = new MidBirdRenderComponent(bird);

	return bird;
}