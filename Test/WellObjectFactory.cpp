#include "WellObjectFactory.h"


WellObjectFactory::WellObjectFactory()
{
}


WellObjectFactory::~WellObjectFactory()
{
}


GameObject * WellObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length, int team){

	GameObject* well = new GameObject();

	well->ID = PID;
	well->setPos(posX, posY);
	well->isAlive = true;
	well->health = 5;
	well->team = team;
	well->type = GAMEOBJECT_TYPE::OBJECT_BASE; // 

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate welld on flag

	WellRenderComponent* rend = new WellRenderComponent(well, team);
	if (team == TEAM_YELLOW){
		well->flipV = false;
		well->flipH = false;
	}
	else{
		well->flipV = true;
		well->flipH = true;
	}
	//	WellPhysicsComponent* physics = new WellPhysicsComponent(well);

	//MidwellLogicComponent* logic = new MidwellLogicComponent(well);

	return well;
}