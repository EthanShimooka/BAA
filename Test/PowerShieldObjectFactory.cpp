#include "PowerShieldObjectFactory.h"


PowerShieldObjectFactory::PowerShieldObjectFactory()
{
}


PowerShieldObjectFactory::~PowerShieldObjectFactory()
{
}


GameObject* PowerShieldObjectFactory::Spawn(uint64_t PID, float posX, float posY, bool direction, int team)
{

	GameObject* shield = new GameObject();

	shield->ID = PID;
	shield->setPos(posX, posY);
	shield->isAlive = true;
	shield->team = team;
	shield->type = GAMEOBJECT_TYPE::OBJECT_POWERSHIELD;

	// Shield Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag

	/// Instantiate new render component
	PowerShieldRenderComponent* rend = new PowerShieldRenderComponent(shield);
	/// Instantiate new network component
	PowerShieldNetworkComponent* net = new PowerShieldNetworkComponent(shield);
	/// Instantiate new logic component
	PowerShieldLogicComponent* logic = new PowerShieldLogicComponent(shield);
	/// Instantiate new physics component
	PowerShieldPhysicsComponent* physics = new PowerShieldPhysicsComponent(shield);
	
	// return GameObject pointer
	return shield;
}