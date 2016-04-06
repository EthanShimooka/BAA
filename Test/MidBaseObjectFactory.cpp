#include "MidBaseObjectFactory.h"


MidBaseObjectFactory::MidBaseObjectFactory()
{
}


MidBaseObjectFactory::~MidBaseObjectFactory()
{
}


GameObject * MidBaseObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length){

	GameObject* base = new GameObject();

	base->ID = PID;
	base->setPos(posX, posY);
	base->isAlive = true;
	base->type = GAMEOBJECT_TYPE::OBJECT_PLATFORM;

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	MidBaseRenderComponent* rend = new MidBaseRenderComponent(base);

	MidBasePhysicsComponent* physics = new MidBasePhysicsComponent(base);

	MidBaseLogicComponent* logic = new MidBaseLogicComponent(base);



	return base;




}