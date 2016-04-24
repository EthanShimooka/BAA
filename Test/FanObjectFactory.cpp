#include "FanObjectFactory.h"


FanObjectFactory::FanObjectFactory()
{
}


FanObjectFactory::~FanObjectFactory()
{
}

GameObject* FanObjectFactory::Spawn(uint64_t PID, float posX, float posY, double rotation){
	GameObject* fan = new GameObject();
	fan->ID = PID;
	fan->isAlive = true;
	fan->setPos(posX, posY);
	fan->rotation = rotation; //set this in the physics component
	fan->team = TEAM::TEAM_NEUTRAL;
	fan->type = GAMEOBJECT_TYPE::OBJECT_FAN;

	FanRenderComponent* rendComp = new FanRenderComponent(fan);
	FanPhysicsComponent* physicsComp = new FanPhysicsComponent(fan);
	FanLogicComponent* logicComp = new FanLogicComponent(fan);

	return fan;
}